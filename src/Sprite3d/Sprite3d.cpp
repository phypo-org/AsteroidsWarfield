#include "Sprite3d.h"

#include <iostream>
#include <typeinfo>

#include "World.h"
#include "Action.h"
#include "Sprite3dPilot.h"






//**************************************
Sprite3d::Sprite3d( float cRadius, float pLifeTime )
:cInteractDef(InteractNull),
cInteractAtt(InteractNull),
 cDeleteControler(NULL),
 cLastColId(-1),

 cDestroy( false )
{
	SpriteFloat::set( SPRITE_LIFETIME, pLifeTime);

	SpriteFloat::set( SPRITE_BIRTHTIME, WorldControler::GetTime());
	SpriteLong::set( SPRITE_TYPE, 0 );

	for( int a = 0; a < MAX_SPRITE_ACTION; a++ )
	{
		cVectAction[ a ] = NULL;
		cVectActionParam[ a ] = NULL;
	}
}
//----------------------------------
Sprite3d::~Sprite3d(){
}
//----------------------------------
void 
Sprite3d::resetLife()
{
	SpriteFloat::set( SPRITE_BIRTHTIME, WorldControler::GetTime());
}

//----------------------------------
void Sprite3d::resetRatio( float pOldRatio )
{	
	for( int j = 0; j < MAX_SPRITE_DOUBLE3; j++ )
		if( SpriteDouble3::getFlag( (EnumSpriteDouble3)j ) == GL_TRUE )
		{
			SpriteDouble3::get(  (EnumSpriteDouble3)j ) /= pOldRatio;
			SpriteDouble3::get(  (EnumSpriteDouble3)j ) *= WorldControler::GetRatio();
		}
}
//-----------------------------------
void Sprite3d::makeDraw(O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	O3dObjProps* lCurProps = pObjProps;

	if( getObjProps() )
		lCurProps = getObjProps();
 
		
	glPushMatrix();

	pushTransf();

//	lCurProps->open();
	draw( pVProps, lCurProps );
//	lCurProps->close();

	glPopMatrix();
}
//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
GLboolean Sprite3d::animate()
{
	if( SpriteFloat::get( SPRITE_LIFETIME) != -1.0 && ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_BIRTHTIME)) >= SpriteFloat::get( SPRITE_LIFETIME) )
		{
			if( cVectAction[SPRITE_ACTION_KILL] )
				cVectAction[SPRITE_ACTION_KILL]->kill(*this, cVectActionParam[SPRITE_ACTION_KILL] );
			
			WorldControler::GetCurrentWorld()->killSprite( this );
			return GL_FALSE;
		}

	if( SpriteDouble3::getFlag( SPRITE_SPEED ) )
		getTransf().TransfDouble3::get( POS )   += SpriteDouble3::get( SPRITE_SPEED  );

	if( SpriteDouble3::getFlag( SPRITE_SPIN ) )
		getTransf().TransfDouble3::get( ANGLE ) += SpriteDouble3::get( SPRITE_SPIN  );

	if( SpriteDouble3::getFlag( SPRITE_GROW ) )
		getTransf().TransfDouble3::get( SCALE ) += SpriteDouble3::get( SPRITE_GROW  );

	
	if( SpriteDouble3::getFlag( SPRITE_DELTA_V) == GL_TRUE )
		SpriteDouble3::get( SPRITE_SPEED ) += SpriteDouble3::get( SPRITE_DELTA_V );


	if( cVectAction[SPRITE_ACTION_ANIMATE] )
		return cVectAction[SPRITE_ACTION_ANIMATE]->animate(*this, cVectActionParam[SPRITE_ACTION_ANIMATE] );


	return GL_TRUE;
}
//-----------------------------------
GLboolean  Sprite3d::leaveWorld()
{
	if( cVectAction[SPRITE_ACTION_LEAVE_WORLD] )
		return cVectAction[SPRITE_ACTION_LEAVE_WORLD]->leaveWorld(*this, cVectActionParam[SPRITE_ACTION_LEAVE_WORLD]);

	return GL_TRUE;
}
//-----------------------------------
GLboolean Sprite3d::collision( Sprite3d & pSprite )
{
//	cout << "collision " << cId << " "  << pSprite.cId << endl;
	
	if( cVectAction[ SPRITE_ACTION_COLLISION ] )
	{
		return cVectAction[SPRITE_ACTION_COLLISION]->collision( *this, pSprite, cVectActionParam[SPRITE_ACTION_COLLISION] );
	}

	return GL_TRUE;
}
//-----------------------------------
long Sprite3d::fireUserAction( void*pParam1,  void*pParam2 )
{
	if( cVectAction[ SPRITE_USER_ACTION ] )
	{
		return cVectAction[SPRITE_USER_ACTION]->userAction( *this, cVectActionParam[SPRITE_USER_ACTION], pParam1, pParam2 );
	}
	return 0;
}
//-----------------------------------
GLboolean
Sprite3d::intersect( Double3 pPos, float pRadius )
{
	Double3 lDist( getTransf().get( POS ));

	//	std::cout << lDist[ 0 ] << "," << lDist[ 1 ] << "," << lDist[ 2 ] << " -> " ;

	lDist -= pPos;


	double lRadius = getRadius() + pRadius;


	//	std::cout << lDist[ 0 ]*lDist[ 0 ] + lDist[ 1 ]*lDist[ 1 ] + lDist[ 2 ]*lDist[ 2 ] << std::endl;

	if( (lDist[ 0 ]*lDist[ 0 ] + lDist[ 1 ]*lDist[ 1 ] + lDist[ 2 ]*lDist[ 2 ]) < (lRadius *lRadius) )
		return GL_TRUE;

	return GL_FALSE;
}
//-----------------------------------
GLboolean
Sprite3d::intersectXY( Double3 pPos, float pRadius )
{
	Double3 lDist( getTransf().get( POS ));

	//	std::cout << lDist[ 0 ] << "," << lDist[ 1 ] << " -> " ;

	lDist -= pPos;


	float lRadius = getRadius() + pRadius;


	//	std::cout << lDist[ 0 ]*lDist[ 0 ] + lDist[ 1 ]*lDist[ 1 ] << std::endl;

	if( (lDist[ 0 ]*lDist[ 0 ] + lDist[ 1 ]*lDist[ 1 ] ) < (lRadius *lRadius) )
		return GL_TRUE;

	return GL_FALSE;
}
//----------------------------------------------
void
Sprite3d::VerifSpeedDelta( double& pV, double& pDV, double pMaxV, double pMaxDV )
{
	if( pDV > 0 )
	{
		if( pDV > pMaxDV )
			pDV = pMaxDV;
	}
	else
	{
		if( pDV < -pMaxDV )
			pDV = -pMaxDV;
	}

	double lFutur = pV+pDV;
	if( lFutur > 0 )
	{
		if(lFutur > pMaxV )
		{
		  pV = pMaxV;
		  pDV =0;
		}
	}
	else
	if(lFutur < -pMaxV)
	{
	  pV = -pMaxV;
	  pDV =0;
	}
}
//--------------------------------
#include  <math.h>

// remplacer par une table si pas besoin de precision

double 
Sprite3d::GetAngle( double pCos, double pSin  )
{
	//	std::cout << "sin:" << pSin << " cos:" << pCos ;

	/*
	if( pCos > 1.0 || pCos < -1.0 )
		return 0;

	double lAngle = acos( pCos );

	if( pSin < 0 )
		lAngle = -lAngle;

	double lAngle2 = lAngle*(180/3.14159265358979323846);

	//	cout << "sin:" << pSin << " cos:" << pCos << " = " << lAngle  << " = " << lAngle2 <<   " s:" << sin( lAngle) << " c:" << cos( lAngle) << endl;
	return lAngle2;
	*/

	if( pCos > 1.0 || pCos < -1.0 )
		{
			//			std::cout << " ++++++++ ELIMINATION ----------:"  << std::endl;
			return 0;
		}

	double lAngle = acos( pCos );


	double lAngle2 = lAngle*(180/3.14159265358979323846);
	if( pSin < 0 )
		lAngle2 = 360-lAngle2;
	
	// 	std::cout <<  " -> " << lAngle  << " = " << lAngle2 
	//						<<   " s:" << sin( lAngle) << " c:" << cos( lAngle) << std::endl;
	return lAngle2;
}


//**************************************
