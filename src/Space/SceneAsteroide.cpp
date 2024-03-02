#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"


#include "SceneAsteroide.h"
#include "ShipsMaker.h"
#include "AsteroidesMaker.h"
#include "WorldGame.h"


#include "U3d/BonusMaker.h"

#include "iostream"


SceneAsteroide *SceneAsteroide::TheSceneAsteroide = NULL;

//**************************************
SceneAsteroide::SceneAsteroide( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3& lPos, float pInterval, float  pH, float pV )
:SceneSprite( pName, pTypeAsteroide, pHardness, lPos, pInterval, pH, pV )
{
  TheSceneAsteroide = this;
}
//------------------------
SceneAsteroide::~SceneAsteroide()
{
}
//------------------------
GLboolean SceneAsteroide::animate()
{
   Sprite3d::animate();

	 //	std::cout << "SceneAsteroide::animate " << 0 << std::endl;

  if( ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_TIMER1)) < cInterval )
	  return GL_FALSE;

	//	std::cout << "SceneAsteroide::animate " << 1111 << std::endl;

	 
  SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());

 
  int sz = (rand() % 20) + 2; //10

  Double3 pos;
  pos[0] = getTransf().TransfDouble3::get(POS)[0];
  pos[ 2 ] = 0;

	if( World::GetPositionWithoutCollision( InteractObstacle, pos, sz, 0, cH ) == GL_FALSE){
		return GL_FALSE;
	}

  Sprite3d *sp;

  float lProba = randp( 100 );

	//	std::cout << "*** SceneAsteroide::animate " << lProba << std::endl;


  if( lProba <= 2 )
  {
	Double3 lD3( randf( 75 ), randf( 75 ), randf( 75 ));
	sp = TheBonusMaker->makeSpriteBonus( CONTAINER,
							InteractBonus, InteractBonus, 1);

	sp->SpriteDouble3::set( SPRITE_SPIN, lD3);
  }
  else
  if( lProba <= 13 )
	sp = MAKE_SHIP1(cHardness);
  else
	 if( lProba <= 21  )
	sp = MAKE_SHIP2(cHardness);
  else
	 if( lProba <= 23  )
	sp = MAKE_SHIP3(cHardness);
  else
	{
		int facette = rand()%2+1;

		sp = TheAsteroidesMaker->makeSpriteAsteroide( cTypeAsteroide, sz, facette );
		Double3 lSpin3( randf( 75 ), randf( 75 ), randf( 75 ));
		sp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );
	}

  Double3 lD3 ( WorldGame::GlobalScroll, 0, 0);
  sp->SpriteDouble3::set( SPRITE_SPEED, lD3); 
  sp->getTransf().TransfDouble3::set( POS, pos );

  WorldControler::Add( sp  );
  return GL_FALSE;
}
//**************************************

