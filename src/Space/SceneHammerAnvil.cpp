#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"


#include "SceneHammerAnvil.h"
#include "ShipsMaker.h"
#include "AsteroidesMaker.h"
#include "WorldGame.h"


#include "U3d/BonusMaker.h"

#include <iostream>


SceneHammerAnvil *SceneHammerAnvil::TheSceneHammerAnvil = NULL;

//**************************************
SceneHammerAnvil::SceneHammerAnvil( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3& lPos,
				    float pInterval, float  pH, float pV )
  :SceneSprite( pName, pTypeAsteroide, pHardness, lPos, pInterval, pH, pV )
{
  TheSceneHammerAnvil = this;
}

//------------------------
GLboolean SceneHammerAnvil::animate(){


  if( ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_TIMER1)) < cInterval )
	  return GL_FALSE;


  SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());

   Sprite3d::animate();

 	subAnimate (1);
	subAnimate(-1);
    return GL_TRUE;
}
//------------------------
GLboolean SceneHammerAnvil::subAnimate(int pSens)
{
  int sz = (rand() % 20) + 2; //10

  Double3 pos;
  pos[ 1 ] = getTransf().TransfDouble3::get(POS)[1]*pSens;  // coordonnees en Y
  pos[ 2 ] = 0;

	if( World::GetPositionWithoutCollision( InteractObstacle, pos, sz, cH ) == GL_FALSE){
		return GL_FALSE;
	}

  Sprite3d *sp;

  float p = randp( 10 );

	/*
  if( p<=0.2 )
  {
	Double3 lD3( randf( 75 ), randf( 75 ), randf( 75 ));
	sp = TheBonusMaker->makeSpriteBonus( CONTAINER,
																			 InteractBonus, InteractBonus, 1);

	sp->SpriteDouble3::set( SPRITE_SPIN, lD3);
  }
  else
  if( p <= 1.3 )
	sp = MAKE_SHIP1(cHardness);
  else
	 if( p <= 2.1  )
	sp = MAKE_SHIP2(cHardness);
  else
	 if( p <= 2.3  )
	sp = MAKE_SHIP3(cHardness);
  else
	*/
	{
		int facette = rand()%2+1;

		sp = TheAsteroidesMaker->makeSpriteAsteroide( cTypeAsteroide, sz, facette );
		Double3 lSpin3( randf( 75 ), randf( 75 ), randf( 75 ));
		sp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );
	}

  Double3 lD3 ( 0, WorldGame::GlobalScroll*pSens, 0);
  sp->SpriteDouble3::set( SPRITE_SPEED, lD3);
  sp->getTransf().TransfDouble3::set( POS, pos );

  WorldControler::Add( sp  );
  return GL_FALSE;
}
//**************************************

