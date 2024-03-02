#include "WeaponsMaker.h"



#include "Sprite3d/World.h"
#include "Sprite3d/ObjOdron.h"

#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Sprite3d.h"
#include "Sprite3d/Utils3d.h"
#include "Sprite3d/Collision.h"
#include "Sprite3d/ObjText2d.h"
#include "Sprite3d/Random.h"
#include "Sprite3d/SoundControler.h"

#include "O3d/O3dObjPrim.h"

//#include "Def.h"
//#include "Global.h"
#include "SpriteExplosion.h"
#include "Sprite3d/World.h"

#include "Space/Def.h"


#include <iomanip>

WeaponsMaker* TheWeaponsMaker=NULL;


//*************************************************
 PSoundId WeaponsMaker::sSoundWeaponExplode          =PBadSoundId;
 PSoundId WeaponsMaker::sSoundWeaponExplodePlasma    =PBadSoundId;
 PSoundId WeaponsMaker::sSoundWeaponExplodePlasmaG   =PBadSoundId;


 PSoundId WeaponsMaker::sSoundExplosionBig    =PBadSoundId;
 PSoundId WeaponsMaker::sSoundExplosion1      =PBadSoundId;
 PSoundId WeaponsMaker::sSoundExplosion2      =PBadSoundId;
 PSoundId WeaponsMaker::sSoundExplosion3      =PBadSoundId;
 PSoundId WeaponsMaker::sSoundExplosion4      =PBadSoundId;

bool
WeaponsMaker::InitSound( )
{

	sSoundWeaponExplode        = SoundControler::LoadSampleConfig("WeaponsMaker.SoundWeaponExplode" );
	sSoundWeaponExplodePlasma  = SoundControler::LoadSampleConfig("WeaponsMaker.SoundWeaponExplodePlasma");
	sSoundWeaponExplodePlasmaG = SoundControler::LoadSampleConfig("WeaponsMaker.SoundWeaponExplodePlasmaG" );


	sSoundExplosion1   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion1" ); 
	sSoundExplosion2   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion2" ); 
	sSoundExplosion3   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion3" ); 
	sSoundExplosion4   = SoundControler::LoadSampleConfig( "ActionsShip.SoundExplosion4" ); 

	return true;
}
//**********************************************************
WeaponsMaker::WeaponsMaker()
	:cColorPlasma( 0.1, 0.7, 0.7, 0.3), // bleue
	 cColorPlasma2( 1, 0.7, 0.0, 0.5),  // Orange
	 cColorPlasmaRed( 0.8, 0.0, 0, 0.4),  // Green
	 cColorPlasmaGreen( 0, 0.8, 0, 0.4),  // Green
	 cColorPlasmaBlue( 0, 0.0, 0.8, 0.4),  // Green
	 cColorIon( 0.3, 0.3, 1, 0.5 ),     // bleue, clair
	 cColorRocket( 0.4, 0.4, 1.0, 0.95 ), // gris bleu
	 cColorFire( 0.3, 0.2, 0.3, 0.1)
{
	TheWeaponsMaker = this;

	cPropsPlasma.ObjPropsFloat4::set( MATERIAL, cColorPlasma );
	cPropsPlasma.ObjPropsFloat4::set( EMISSION, cColorPlasma );

	cPropsPlasmaRed.ObjPropsFloat4::set( EMISSION, cColorPlasmaRed );
	cPropsPlasmaRed.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	cPropsPlasmaRed.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

	cPropsPlasmaGreen.ObjPropsFloat4::set( EMISSION, cColorPlasmaGreen );
	cPropsPlasmaGreen.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	cPropsPlasmaGreen.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

	cPropsPlasmaBlue.ObjPropsFloat4::set( EMISSION, cColorPlasmaBlue );
	cPropsPlasmaBlue.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	cPropsPlasmaBlue.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

	cPropsPlasma2.ObjPropsFloat4::set( MATERIAL, cColorPlasma2);

	cPropsFire.ObjPropsFloat4::set( MATERIAL, cColorFire);


	cPropsIon.ObjPropsFloat4::set( MATERIAL, cColorIon );
	cPropsIon.ObjPropsFloat4::set( EMISSION, cColorIon );
	cPropsIon.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	cPropsIon.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

	cPropsRocket.ObjPropsFloat4::set( MATERIAL, cColorRocket );

	caObjMicroPlasma  = makePlasma(0.4);

	caObjPlasma  = makePlasma(0.7);
	caObjPlasma2 = makePlasma2(0.7);

	caObjPlasmaRed   = makeBigPlasma(2, &cPropsPlasmaRed);
	caObjPlasmaGreen = makeBigPlasma(2, &cPropsPlasmaGreen);
	caObjPlasmaBlue  = makeBigPlasma(2, &cPropsPlasmaBlue);

	caObjIon     = makeIon( 2.0 );
	caObjSmallRocket  = makeRocket( 1.0 );
	caObjRocket  = makeRocket( 1.4 );
	caObjBigRocket  = makeRocket( 1.8 );


	caObjSmallMissile  = makeMissile( 1.0 );
	caObjMissile  = makeMissile( 1.4 );
	caObjBigMissile  = makeMissile( 1.8 );
}
//----------------------------------------------
O3dObj*
WeaponsMaker::makePlasma( float pSize)
{
	O3dObj* lObj = new O3dObjPrim( O3dObjPrim::PrimSphere, pSize, 4, 4 );
	lObj->setObjProps( &cPropsPlasma );

	return lObj;
}
//----------------------------------------------
O3dObj*
WeaponsMaker::makePlasma2(float pSize)
{
	O3dObj* lObj =  new O3dObjPrim( O3dObjPrim::PrimSphere, pSize, 4, 4 );
	lObj->setObjProps( &cPropsPlasma2 );

	return lObj;
}
//----------------------------------------------
O3dObj*
WeaponsMaker::makeRocket(float pSize)
{
	ObjVect * lObjVect = new ObjVect();

	O3dObj* lObj =  new O3dObjPrim( O3dObjPrim::PrimCone, pSize, 3, 3, 3 );
	lObj->setObjProps( &cPropsRocket );
	lObj->getTransf().TransfDouble3::get( ANGLE)[1] = 90;
	lObjVect->add( lObj );

	O3dObj *lJet = new O3dObjPrim( O3dObjPrim::PrimCone, pSize/2, 5, 5, pSize*15);
	//	lJet->MkGetANGLE()[1] = 270;
	lJet->getTransf().TransfDouble3::get( ANGLE)[1] = 270;
	lJet->getTransf().TransfDouble3::get( POS )[0] = -pSize*1.5;
	lJet->setObjProps( &cPropsFire );
	lObjVect->add( lJet );

	lJet = new O3dObjPrim( O3dObjPrim::PrimCone, pSize/2, 5, 5, pSize*5);
	lJet->getTransf().TransfDouble3::get( ANGLE)[1] = 270;
	lJet->getTransf().TransfDouble3::get( POS )[0] = -pSize*1.5;
	lJet->setObjProps( &cPropsFire );
	lObjVect->add( lJet );

	lObjVect->getTransf().TransfDouble3::get( ANGLE ) [2] = 180;

	return lObjVect;
}
//----------------------------------------------
O3dObj*
WeaponsMaker::makeMissile(float pSize)
{
	ObjVect * lObjVect = new ObjVect();

	O3dObj* lObj =  new O3dObjPrim( O3dObjPrim::PrimCone, pSize, 3, 3, 3 );
	lObj->setObjProps( &cPropsRocket );
	lObj->getTransf().TransfDouble3::get( ANGLE)[1] = 90;
	lObj->getTransf().TransfDouble3::get( POS )[0] = pSize/2;
	lObjVect->add( lObj );

	lObj = new O3dObjPrim( O3dObjPrim::PrimCylinder, pSize, 5, 5, pSize, pSize );
	lObj->setObjProps( &cPropsRocket );
	lObj->getTransf().TransfDouble3::get( ANGLE)[1] = 90;
	lObjVect->add( lObj );

	O3dObj *lJet = new O3dObjPrim( O3dObjPrim::PrimCone, pSize/2, 5, 5, pSize*10);
	//	lJet->MkGetANGLE()[1] = 270;
	lJet->getTransf().TransfDouble3::get( ANGLE)[1] = 270;
	lJet->getTransf().TransfDouble3::get( POS )[0] = -pSize*1.5;
	lJet->setObjProps( &cPropsFire );
	lObjVect->add( lJet );

	lJet = new O3dObjPrim( O3dObjPrim::PrimCone, pSize/2, 5, 5, pSize*3);
	lJet->getTransf().TransfDouble3::get( ANGLE)[1] = 270;
	lJet->getTransf().TransfDouble3::get( POS )[0] = -pSize*1.5;
	lJet->setObjProps( &cPropsFire );
	lObjVect->add( lJet );

	lObjVect->getTransf().TransfDouble3::get( ANGLE ) [2] = 180;

	return lObjVect;
}
//----------------------------------------------
ObjVect*
WeaponsMaker::makeBigPlasma(float pSize, O3dObjProps* pProps)
{
	ObjVect * lObjVect = new ObjVect();

	O3dObj* lObj1 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSize, 4, 4);
	lObj1->setObjProps( pProps );
	lObjVect->add( lObj1 );

	O3dObj* lObj2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSize*0.5, 3, 3);
	lObj2->setObjProps( pProps );
	lObjVect->add( lObj2);

	lObjVect->setRadius( pSize );
	return lObjVect;
}
//----------------------------------------------
ObjVect*
WeaponsMaker::makeIon(float pSize)
{
	O3dObj* lObj1 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSize, 4, 4);
	lObj1->setObjProps( &cPropsIon );
	O3dObj* lObj2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSize*0.5, 4, 4);
	lObj2->setObjProps( &cPropsPlasma2 );
	ObjVect * lObjVect = new ObjVect();
	lObjVect->add( lObj1 );
	lObjVect->add( lObj2);
	lObjVect->setRadius( pSize );

	return lObjVect;
}
//----------------------------------------------
void
WeaponsMaker::set( Sprite3d *pSp, float pDestroyPoint, float pSpeed, float pSpin )
{
	pSp->SpriteFloat::set( SPRITE_DESTROY_POINT, pDestroyPoint  );

	Double3 lSpeed3( pSpeed, 0, 0 );
	pSp->SpriteDouble3::set( SPRITE_SPEED, lSpeed3 );


	Double3 lSpin3( randf(pSpin), randf(pSpin), randf(pSpin) );
	pSp->SpriteDouble3::set( SPRITE_SPIN, lSpin3 );
}
//----------------------------------------------
// Creer un tir multiple de la meme arme (vitesse decale)
void
WeaponsMaker::makeMultipleSameWeapon( int& pCurrent, Sprite3d* pSpProj[32], int pNbWeapon, T3dTransf* pTransf, EnumWeapons pType,
																			unsigned int pMaskObj, unsigned int pMakInteract)
{

	float lVitesse = 1.0f;
	for( int i=0; i<pNbWeapon; i++, pCurrent++)
		{

			pSpProj[pCurrent] = makeSprite( pTransf, pType, pMaskObj, pMakInteract );
			if( i > 0 )
				{
					lVitesse += 0.05;
					pSpProj[pCurrent]->SpriteDouble3::get( SPRITE_SPEED )[0] *= lVitesse;
				}

		}

}
//----------------------------------------------
// Creer un tir lateral double multiple de la meme arme
void
WeaponsMaker::makeMultipleSameWeaponDiag( int& pCurrent, Sprite3d* pSpProj[32], int pNbWeapon, float pDiag, T3dTransf* pTransf, EnumWeapons pType,
																			unsigned int pMaskObj, unsigned int pMakInteract)
{
	int pCurrentSav = pCurrent;
	makeMultipleSameWeapon( pCurrent, pSpProj, pNbWeapon, pTransf, pType, pMaskObj, pMakInteract );


	for( int i=pCurrentSav; i<pCurrent; i++ )
		{
			Double3 lSpeed3 = pSpProj[i]->SpriteDouble3::get( SPRITE_SPEED );
			lSpeed3[1] += lSpeed3[0]*pDiag;
			lSpeed3[0] -= lSpeed3[0]*pDiag;

			// rotation de la munition
			Double3 lDist(lSpeed3 ) ;
			O3dObj::GetNormDirectionInv( lDist );
			double lAngle = Sprite3d::GetAngle( lDist[0], lDist[1] );
			pSpProj[i]->getTransf().TransfDouble3::get( ANGLE )[2] = lAngle;///3.14159265358979323846;


			// On revient en vitesse par seconde !!!!!
			lSpeed3 /=WorldControler::GetRatio();

			pSpProj[i]->SpriteDouble3::set( SPRITE_SPEED, lSpeed3);
		}


	pCurrentSav = pCurrent;
	makeMultipleSameWeapon( pCurrent, pSpProj, pNbWeapon, pTransf, pType, pMaskObj, pMakInteract );
	for( int i=pCurrentSav; i<pCurrent; i++ )
		{
			Double3 lSpeed3 = pSpProj[i]->SpriteDouble3::get( SPRITE_SPEED );
			lSpeed3[1] -= lSpeed3[0]*pDiag;
			lSpeed3[0] -= lSpeed3[0]*pDiag;


			// rotation de la munition
			Double3 lDist(lSpeed3 ) ;
			O3dObj::GetNormDirectionInv( lDist );
			double lAngle = Sprite3d::GetAngle( lDist[0], lDist[1] );
			pSpProj[i]->getTransf().TransfDouble3::get( ANGLE )[2] = lAngle;///3.14159265358979323846;




			// On revient en vitesse par seconde !!!!!
			lSpeed3 /=WorldControler::GetRatio();

			pSpProj[i]->SpriteDouble3::set( SPRITE_SPEED, lSpeed3);
		}
}
//----------------------------------------------
Sprite3d*
WeaponsMaker::makeSprite( T3dTransf* pTransf, EnumWeapons pType,  unsigned int pMaskObj, unsigned int pMakInteract)
{
	// ON POURRAIT FAIRE HERITER LE PROJECTILE DE LA VITESSE DU TIREUR(ce serait logique !)

	Sprite3d* lSp = NULL;
	switch( pType )
		{
		case WEAPON_MICRO_PLASMA:
			lSp = new Sprite3dObj( caObjMicroPlasma );
			set( lSp, 1, -120.0, 150.0 );
			break;

		case WEAPON_PLASMA:
			lSp =  new Sprite3dObj( caObjPlasma );
			set( lSp, 2.0, -80.0, 150.0 );
			break;

		case WEAPON_PLASMA2:
			lSp = new Sprite3dObj( caObjPlasma2 );
			set( lSp, 3, -80.0, 150.0 );
			break;


		case WEAPON_PLASMA_RED:
			lSp =  new Sprite3dObj( caObjPlasmaRed );
			set( lSp, 6.0, -60.0, 100.0 );
			break;

		case WEAPON_PLASMA_GREEN:
			lSp =  new Sprite3dObj( caObjPlasmaGreen );
			set( lSp, 8.0, -65.0, 100.0 );
			break;

		case WEAPON_PLASMA_BLUE:
			lSp =  new Sprite3dObj( caObjPlasmaBlue );
			set( lSp, 10.0, -70.0, 100.0 );
			break;

		case WEAPON_ION:
			lSp = new Sprite3dObj( caObjIon );
			set( lSp, 20.0, -40.0, 1000.0 );
			break;


		case WEAPON_SMALL_ROCKET:
			lSp = new Sprite3dObj( caObjSmallRocket );
			set( lSp, 5.0, -70.0, 0.0 );
			break;

		case WEAPON_ROCKET:
			lSp = new Sprite3dObj( caObjRocket );
			set( lSp, 10.0, -80.0, 0.0 );
			break;

		case WEAPON_BIG_ROCKET:
			lSp = new Sprite3dObj( caObjBigRocket );
			set( lSp, 30, -85.0, 0.0 );
			break;

			// AJOUTER DES MISSILES A TETES CHERCHEUSES !!!!!
		case WEAPON_SMALL_MISSILE:
			lSp = new Sprite3dObj( caObjSmallMissile );
			set( lSp, 6.0, -80.0, 0.0 );
			lSp->SpriteFloat::set( WEAPON_MAX_SPEED,    80 );
			lSp->SpriteFloat::set( WEAPON_MAX_DELTA_V,  30 );
			lSp->SpriteFloat::set( WEAPON_REACTIVITY,   0.5 );
			lSp->SpriteFloat::set( WEAPON_DEAD_DELAY,   1.5 );
			lSp->SpriteFloat::set( WEAPON_ACTION_DELAY, 0.05 );
			lSp->SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());
			lSp->SpriteFloat::set( SPRITE_TIMER2,  WorldControler::GetTime());
			lSp->setAction( SPRITE_ACTION_ANIMATE,   TheWeaponsMaker );
			break;
		case WEAPON_MISSILE:
			lSp = new Sprite3dObj( caObjMissile );
			set( lSp, 12.0, -70.0, 0.0 );
			lSp->SpriteFloat::set( WEAPON_MAX_SPEED,    70 );
			lSp->SpriteFloat::set( WEAPON_MAX_DELTA_V,  30 );
			lSp->SpriteFloat::set( WEAPON_REACTIVITY,   0.45 );
			lSp->SpriteFloat::set( WEAPON_DEAD_DELAY,   2 );
			lSp->SpriteFloat::set( WEAPON_ACTION_DELAY, 0.08 );
			lSp->SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());
			lSp->SpriteFloat::set( SPRITE_TIMER2,  WorldControler::GetTime());
			lSp->setAction( SPRITE_ACTION_ANIMATE,   TheWeaponsMaker );
			break;
		case WEAPON_BIG_MISSILE:
			lSp = new Sprite3dObj( caObjBigMissile );
			set( lSp, 40.0, -60.0, 0.0 );
			lSp->SpriteFloat::set( WEAPON_MAX_SPEED,    60 );
			lSp->SpriteFloat::set( WEAPON_MAX_DELTA_V,  30 );
			lSp->SpriteFloat::set( WEAPON_REACTIVITY,   0.4 );
			lSp->SpriteFloat::set( WEAPON_DEAD_DELAY,   2.5 );
			lSp->SpriteFloat::set( WEAPON_ACTION_DELAY, 0.1 );
			lSp->SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());
			lSp->SpriteFloat::set( SPRITE_TIMER2,  WorldControler::GetTime());
			lSp->setAction( SPRITE_ACTION_ANIMATE,   TheWeaponsMaker );
			break;

		case WEAPON_NO:
		default: ;
		}

	lSp->SpriteFloat::set( WEAPON_TYPE, pType );

	lSp->setAction( SPRITE_ACTION_COLLISION, TheWeaponsMaker );

	if( pTransf )
		{
			lSp->setTransf( *pTransf );
		}

		{
			//			lSp->setMask( InteractEnemy, InteractEnemyWeapon);
			//			lSp->SpriteDouble3::get( SPRITE_SPEED )[0] *= pSens;
		}
		{
			//			lSp->setMask( InteractAllied, InteractAlliedWeapon );
		}

	lSp->setMask( pMaskObj, pMakInteract );

	return lSp;
}
//----------------------------------------------
GLboolean
WeaponsMaker::animate( Sprite3d &pMySprite, void * pParam )
{
	//	std::cout << "WeaponsMaker::animate" << std::endl;

	if(  pMySprite.SpriteFloat::getFlag( WEAPON_DEAD_DELAY )
			 && ( WorldControler::GetTime()-pMySprite.SpriteFloat::get( SPRITE_TIMER2 )) >= pMySprite.SpriteFloat::get(WEAPON_DEAD_DELAY ) )
		{
			destruction( pMySprite );
			return GL_TRUE;
		}

	if( (WorldControler::GetTime()-pMySprite.SpriteFloat::get( SPRITE_TIMER1)) < pMySprite.SpriteFloat::get( WEAPON_ACTION_DELAY) )
	  return GL_TRUE;



	//	std::cout << "WeaponsMaker::animate2  " << (int)pMySprite.SpriteFloat::get( WEAPON_TYPE ) << std::endl;

	switch( (int)pMySprite.SpriteFloat::get( WEAPON_TYPE ) )
		{
		case WEAPON_SMALL_MISSILE:
		case WEAPON_MISSILE:
		case WEAPON_BIG_MISSILE:
			return searchTarget( pMySprite );
		default: ;
		}
	return GL_TRUE;
}
//----------------------------------------------

GLboolean
WeaponsMaker::searchTarget( Sprite3d &pMySprite )
{

	//	std::cout << ">>>>> WeaponsMaker::animateNormal" << std::endl;


	// On recupere le vecteur entre le sprite et ca cible (Pilot)
	Double3 lDist;


	pMySprite.SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());


	// A MODIFIER EN FONCTION DU CAMP !
	// pour le joueur detecter l'objet enemei le plus proche dans le cone de vise et se
	// verouiller sur lui !
	if( World::GetDistPilot( &pMySprite, lDist) == GL_FALSE )
		return GL_FALSE;

	// Mettre un timer de validite (au bout de temps de temps le missile explose
	// ou continue sur ca lancee !


	Double3 lSpeed(  pMySprite.SpriteDouble3::get( SPRITE_SPEED ));
	Double3 lDeltaV( pMySprite.SpriteDouble3::get( SPRITE_DELTA_V )) ;

	lSpeed  /= WorldControler::GetRatio();
	lDeltaV /= WorldControler::GetRatio();


	float lMaxSpeed   = pMySprite.SpriteFloat::get( WEAPON_MAX_SPEED );
	float lMaxDeltaV  = pMySprite.SpriteFloat::get( WEAPON_MAX_DELTA_V );
	float lReactivity = pMySprite.SpriteFloat::get( WEAPON_REACTIVITY );

	lDeltaV[1] = lDist[1] * lReactivity;
	Sprite3d::VerifSpeedDelta( lSpeed[1], lDeltaV[1], lMaxSpeed, lMaxDeltaV );


	lDeltaV[0] = lDist[0] * lReactivity;
	Sprite3d::VerifSpeedDelta( lSpeed[0], lDeltaV[0], lMaxSpeed, lMaxDeltaV );

	O3dObj::GetNormDirectionInv( lDist );

	double lAngle = Sprite3d::GetAngle( lDist[0], lDist[1] );
	pMySprite.getTransf().TransfDouble3::get( ANGLE )[2] = lAngle;

	pMySprite.SpriteDouble3::set( SPRITE_SPEED, lSpeed );
	pMySprite.SpriteDouble3::set( SPRITE_DELTA_V, lDeltaV );

	return GL_TRUE;
}

//----------------------------------------------
void
WeaponsMaker::destruction( Sprite3d &pMySprite )
{
	float lDestroy = pMySprite.SpriteFloat::get( SPRITE_DESTROY_POINT );

	for( int i=0; i<3+lDestroy/3; i++)
		{
			SpriteExplosion *sp = new SpriteExplosion( 3.0+randp(lDestroy), 0.2+randf(0.3) );

			sp->setTransf( pMySprite.getTransf() );
			// APPELER ExplodeMaker
			switch( (int)pMySprite.SpriteFloat::get( WEAPON_TYPE ))
			{
			case WEAPON_PLASMA_GREEN:
				sp->setObjProps( &cPropsPlasmaGreen );
				//			PLAY_SAMPLE( sSoundWeaponExplodePlasmaG );
				break;

			case WEAPON_PLASMA:
			case WEAPON_MICRO_PLASMA:
			case WEAPON_PLASMA2:
				sp->setObjProps( SpriteExplosion::caExplosionPlasmaProps );
				//			PLAY_SAMPLE( sSoundWeaponExplodePlasma );
				break;

			case WEAPON_ION:
			case WEAPON_SMALL_ROCKET:
			case WEAPON_ROCKET:
			case WEAPON_BIG_ROCKET:
			case WEAPON_SMALL_MISSILE:
			case WEAPON_MISSILE:
			case WEAPON_BIG_MISSILE:
			default:
				sp->setObjProps( SpriteExplosion::caExplosionProps );
				//			PLAY_SAMPLE( sSoundWeaponExplode );

			}
			WorldControler::Add( sp );
		}


				switch( rand( )%5)
					{
					case 0: PLAY_SAMPLE( sSoundExplosion1 ); break;
					case 1: PLAY_SAMPLE( sSoundExplosion2 ); break;
					case 2: PLAY_SAMPLE( sSoundExplosion3 ); break;
					case 3: PLAY_SAMPLE( sSoundExplosion4 ); break;
					case 4: PLAY_SAMPLE( sSoundWeaponExplode ); break;
				default:
						PLAY_SAMPLE( sSoundExplosion4 ); break;
					}

	WorldControler::KillSprite( &pMySprite );
}
//----------------------------------------------
GLboolean
WeaponsMaker::collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam )
{

	if( pSprite.SpriteLong::get(  SPRITE_TYPE  ) == CONTAINER  ){

		// Encore faudrait il comprendre pourquoi ils interragissent ?
		// car normalement leurs masques ne corresponde pas !

		//		std::cout << "*** Weapon:" <<  std::hex << pMySprite.getInteract() 
		//							<< " Bonus:" << std::hex <<  pSprite.getInteract() << std::endl;
 
		return GL_FALSE;
	}

	destruction( pMySprite );

	return GL_TRUE;
}
