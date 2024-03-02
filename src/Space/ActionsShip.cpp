#include <stdlib.h>

#include "ActionsShip.h"

#include "Sprite3d/World.h"
#include "Sprite3d/ObjOdron.h"

#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Sprite3d.h"
#include "Sprite3d/Utils3d.h"
#include "Sprite3d/Collision.h"
#include "Sprite3d/ObjText2d.h"
#include "Sprite3d/Random.h"
#include "Sprite3d/SoundControler.h"

#include "U3d/SpriteExplosion.h"
#include "U3d/WeaponsMaker.h"
#include "U3d/BonusMaker.h"

#include "Space/Pilot.h"

#include "Def.h"

#include "ShipsMaker.h"

#include <math.h>


 PSoundId ActionsShip::sSoundExplosionBig    =PBadSoundId;
 PSoundId ActionsShip::sSoundExplosion1      =PBadSoundId;
 PSoundId ActionsShip::sSoundExplosion2      =PBadSoundId;
 PSoundId ActionsShip::sSoundExplosion3      =PBadSoundId;
 PSoundId ActionsShip::sSoundExplosion4      =PBadSoundId;
 PSoundId ActionsShip::sSoundDestroy      =PBadSoundId;


//static PSoundId sMusicGameOver=PBadSoundId;

bool
ActionsShip::InitSound()
{

	sSoundExplosion1   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion1" ); 
	sSoundExplosion2   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion2" ); 
	sSoundExplosion3   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion3" ); 
	sSoundExplosion4   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion4" ); 

	sSoundDestroy   = SoundControler::LoadSampleConfig( "ActionsShip.SoundDestroy" ); 

	sSoundExplosionBig = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosionBig" );

	return true;
}

//----------------------------------------------
//--------------- Comportement -----------------
//----------------------------------------------
GLboolean
ActionsShip::collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam )
{
	pMySprite.SpriteFloat::set( SPRITE_LIFE_POINT,
	pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT )-pSprite.SpriteFloat::get( SPRITE_DESTROY_POINT ));


	if( pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
	{
    	ObjVect* lObjVect = (ObjVect*)((Sprite3dObj&)pMySprite).getObj();
		for( std::vector <O3dObj*>::iterator iter = lObjVect->begin(); iter != lObjVect->end(); ++iter )
		{
			(*iter)->setAnimateOn( GL_FALSE ); // comme il est detruit c'est normal ! et il risque d'y avoir des ptr sur pMySprite
		}
		/*
		switch( rand( )%4)
			{
			case 0: PLAY_SAMPLE( sSoundExplosion1 ); break;
			case 1: PLAY_SAMPLE( sSoundExplosion2 ); break;
			case 2: PLAY_SAMPLE( sSoundExplosion3 ); break;
			case 3: PLAY_SAMPLE( sSoundExplosion4 ); break;
			default:
				PLAY_SAMPLE( sSoundExplosion4 ); break;
		}
		*/

		int max = static_cast<long>(randp(pMySprite.getRadius()));
		for( int j=0; j< max+1; j++)
		{
			SpriteExplosion *sp = new SpriteExplosion( randp(pMySprite.getRadius()), 0.3+randp(0.3) );
			sp->setTransf( pMySprite.getTransf() );
			sp->setObjProps( SpriteExplosion::caExplosionProps );

			WorldControler::Add( sp );
		}
		pMySprite.SpriteFloat::set( SHIP_ACTION, SHIP_ACTION_IN_DETRUCTION );
		pMySprite.SpriteFloat::set( SHIP_ACTION_DELAY, randp(1.5) );

		Double3 lSpin3( randf( 150 ), randf( 150 ), randf( 150 ));
		pMySprite.SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );
	}

	return GL_TRUE;
}
//----------------------------------------------
GLboolean
ActionsShip::animate( Sprite3d &pMySprite, void * pParam )
{
	float pInterval = pMySprite.SpriteFloat::get( SHIP_ACTION_DELAY );

	if( ( WorldControler::GetTime()-pMySprite.SpriteFloat::get( SPRITE_TIMER1)) < pInterval )
	  return GL_FALSE;

	switch( (long)pMySprite.SpriteFloat::get( SHIP_ACTION ) )
		{
		case SHIP_ACTION_KAMIKAZE:
			return animateNormal( pMySprite, pParam, GL_TRUE, GL_FALSE);

		case SHIP_ACTION_TOURNOI:
			return animateNormal( pMySprite, pParam, GL_TRUE, GL_TRUE);

		case SHIP_ACTION_ATTACK:
			return animateNormal( pMySprite, pParam, GL_FALSE, GL_TRUE );

		case SHIP_ACTION_NOMINAL:
			return animateNormal( pMySprite, pParam, GL_FALSE, GL_FALSE );

		case SHIP_ACTION_IN_DETRUCTION:
			return animateDestroy( pMySprite, pParam );
		default: ;
		}
	return GL_TRUE;
}
//----------------------------------------------
/*
void
ActionsShip::fire( Sprite3d &pMySprite, Double3 pDist, GLboolean pDirectionnel )
{
	int lType = (int) pMySprite.SpriteFloat::get( SHIP_WEAPON );
	Sprite3d *lSp = TheWeaponsMaker->makeSprite( (EnumWeapons)lType, ALIEN_SHIP );

	if( lSp )
	{
	   lSp->setTransf( pMySprite.getTransf() );
	   lSp->getTransf().TransfDouble3::get( ANGLE )[1] = 180;

		if( pDirectionnel )
		 {
			 O3dObj::GetNormDirectionInv( pDist );

			 Double3 lSpeed( lSp->SpriteDouble3::get( SPRITE_SPEED ));

			 lSpeed /= WorldControler::GetRatio();
			 lSpeed[0]=pDist[0]*(lSpeed[0]+lSpeed[1]);
			 lSpeed[1]=pDist[1]*(lSpeed[0]+lSpeed[1]);

			 lSp->SpriteDouble3::set( SPRITE_SPEED, lSpeed );
		 }

	   WorldControler::Add( lSp );
	}
}
*/
//----------------------------------------------
GLboolean
ActionsShip::animateNormal( Sprite3d &pMySprite, void * pParam, GLboolean pMoveX, GLboolean pMoveY )
{
	// On recupere le vecteur entre le sprite et ca cible (Pilot)
	Double3 lDist;


	pMySprite.SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());

	if( World::GetDistPilot( &pMySprite, lDist) == GL_FALSE )
		return GL_FALSE;


	if( pMoveX || pMoveY )
		{
			Double3 lSpeed(  pMySprite.SpriteDouble3::get( SPRITE_SPEED ));
			Double3 lDeltaV( pMySprite.SpriteDouble3::get( SPRITE_DELTA_V )) ;

			lSpeed  /= WorldControler::GetRatio();
			lDeltaV /= WorldControler::GetRatio();

			float lMaxSpeed   = pMySprite.SpriteFloat::get( SHIP_MAX_SPEED );
			float lMaxDeltaV  = pMySprite.SpriteFloat::get( SHIP_MAX_DELTA_V );
			float lReactivity = pMySprite.SpriteFloat::get( SHIP_REACTIVITY );

			if( pMoveY )
				{
					lDeltaV[1] = lDist[1] * lReactivity;
					Sprite3d::VerifSpeedDelta( lSpeed[1], lDeltaV[1], lMaxSpeed, lMaxDeltaV );
				}


			if( pMoveX )
				{
					lDeltaV[0] = lDist[0] * lReactivity;
					Sprite3d::VerifSpeedDelta( lSpeed[0], lDeltaV[0], lMaxSpeed, lMaxDeltaV );
				}

			O3dObj::GetNormDirectionInv( lDist );

			if( pMoveX && pMoveY )
			{
				double lAngle = Sprite3d::GetAngle( lDist[0], lDist[1] );
				pMySprite.getTransf().TransfDouble3::get( ANGLE )[2] = lAngle;
			}

			pMySprite.SpriteDouble3::set( SPRITE_SPEED, lSpeed );
			pMySprite.SpriteDouble3::set( SPRITE_DELTA_V, lDeltaV );
		}


	return GL_TRUE;
}

//----------------------------------------------
GLboolean
ActionsShip::animateDestroy( Sprite3d &pMySprite, void * pParam )
{


	float lBonus = pMySprite.SpriteFloat::get( SPRITE_MAX_LIFE_POINT )/2;
	Pilot::AddScore( lBonus*2 );


	lBonus = sqrt( lBonus );
	int lNivBonus = (lBonus/4)+1;

	for( int i=0; i< lBonus; i++)
		{
			Sprite3d* lSp = TheBonusMaker->makeSpriteBonus( CONTAINER, InteractBonus, InteractBonus, lNivBonus);

			lSp->getTransf().TransfDouble3::set( POS, pMySprite.getTransf().TransfDouble3::get( POS) );
			Double3 lSpeed( pMySprite.SpriteDouble3::get( SPRITE_SPEED ));
			lSpeed /= WorldControler::GetRatio();
			lSpeed[1]=randf(lSpeed[0]*0.3);
			lSpeed[0]+=randf(lSpeed[0]*0.3);
			lSp->SpriteDouble3::set( SPRITE_SPEED,  lSpeed );

			WorldControler::Add( lSp );
		}

		PLAY_SAMPLE( sSoundDestroy );


	int max = static_cast<long>(randp(pMySprite.getRadius()/2)+1.0);
	if( max > 10 )
		max = 10;
	for( int j=0; j< max+1; j++)
	{
		SpriteExplosion *sp = new SpriteExplosion( 1+randp(pMySprite.getRadius()), 0.3+randp(0.3) );
		sp->setTransf( pMySprite.getTransf() );
		sp->setObjProps( SpriteExplosion::caExplosionProps );
	  	WorldControler::Add( sp );
	}

	// Demenbrement du vaisseau
	ObjVect* lObjVect = (ObjVect*)((Sprite3dObj&)pMySprite).getObj();

	pMySprite.getTransf().add( POS,   lObjVect->getTransf().get( POS ));
	pMySprite.getTransf().add( ANGLE, lObjVect->getTransf().get( ANGLE ));

	lObjVect->setAnimateOn( GL_FALSE );
	for( std::vector <O3dObj*>::iterator iter = lObjVect->begin(); iter != lObjVect->end(); ++iter )
	{
		(*iter)->setAnimateOn( GL_FALSE ); // comme il est detruit c'est normal ! et il risque d'y avoir des ptr sur pMySprite

		Sprite3dObj* lSp = new Sprite3dObj( (*iter) );

		// C'est a lSp de les detruire maintenant, plus a pMySprite
		lSp->setDeepDestroy(GL_TRUE);

		lSp->setMask( InteractObstacle, InteractObstacle );
		lSp->SpriteFloat::set( SPRITE_LIFE_POINT, 1);
		lSp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, 1);
		lSp->SpriteFloat::set( SPRITE_DESTROY_POINT, 1);

		lSp->setTransf(pMySprite.getTransf());

	//Normalement la transformation de O3dObj devrait etre preserve
		Double3 lSpin3( pMySprite.SpriteDouble3::get( SPRITE_SPIN ) );
	    lSpin3 += Double3( randf(20), randf(20), randf(20) );
		lSp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );

		Double3 lSpeed( pMySprite.SpriteDouble3::get( SPRITE_SPEED ));
		lSpeed += Double3( randf(10), randf(10), randf( 10 ) );

		lSp->SpriteDouble3::set( SPRITE_SPEED,  lSpeed );
		lSp->SpriteFloat::set( SPRITE_LIFETIME, randp(1.4));
		lSp->setAction( SPRITE_ACTION_KILL, this );

		 WorldControler::Add( lSp  );
	}

	// On a tout transferre
	lObjVect->clear();

	WorldControler::KillSprite( &pMySprite );

	return GL_TRUE;
}
//----------------------------------------------

GLboolean
ActionsShip::kill( Sprite3d &pMySprite, void*pParam )
{
	//	PLAY_SAMPLE(  sSoundExplosionBig );

	int max = static_cast<long>(randp(pMySprite.getRadius()*1.5));
	for( int j=0; j< max+1; j++)
	{
		SpriteExplosion *sp = new SpriteExplosion( 1+randp(pMySprite.getRadius()), 0.3+randp(0.3) );
		sp->setTransf( pMySprite.getTransf() );
		sp->setObjProps( SpriteExplosion::caExplosionProps );
		WorldControler::Add( sp );
	}

		return GL_TRUE;
}
