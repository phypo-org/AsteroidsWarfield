#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"

#include "SceneChaos.h"

#include "ShipsMaker.h"
#include "MinesMaker.h"
#include "AsteroidesMaker.h"
#include "WorldGame.h"

#include "U3d/BonusMaker.h"

#include <iostream>


SceneChaos *SceneChaos::TheSceneChaos = NULL;

//**************************************
SceneChaos::SceneChaos( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3& lPos, 
                        float pInterval, float pIntervalParoi, int pSizeParoi, float  pH, float pV )
  :SceneSprite( pName, pTypeAsteroide, pHardness, lPos, pInterval, pH, pV ),
   cIntervalParoi( pIntervalParoi ),
   cSizeParoi( pSizeParoi),
   cFirstTime(GL_TRUE)
{
  TheSceneChaos = this;  

}


//------------------------
void 
SceneChaos::makeAsteroide(  Double3& pPos, int pSz, GLboolean pIndestructible, float pVY ){
  Sprite3d *sp;

  int lFacette = rand()%2+1;

  //	std::cout << "X:" << pPos[0] << " Y:" << pPos[1] << std::endl;

  Double3 lAngle(randf(360), randf(360), randf(360));
  Double3 lScale( 1.0+randf(0.6), 1.0+randf(0.6), 1.0+randf(0.6));
	
  sp = TheAsteroidesMaker->makeSpriteAsteroide( cTypeAsteroide, pSz, lFacette );

  Double3 lSpin3( randf( 75 ), randf( 75 ), randf( 75 ));
  sp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );

  if( pIndestructible == GL_TRUE )
    {
      // Dans ce cas la grotte est indestructible !!
      sp->SpriteFloat::set( SPRITE_LIFE_POINT, 9999999 );
      sp->setAction( SPRITE_ACTION_COLLISION, NULL );
    }
	
  sp->getTransf().TransfDouble3::set( POS,   pPos );
  sp->getTransf().TransfDouble3::set( ANGLE, lAngle );
  sp->getTransf().TransfDouble3::set( SCALE, lScale );
	
  Double3 lD3 ( WorldGame::GlobalScroll, pVY, 0);
  sp->SpriteDouble3::set( SPRITE_SPEED, lD3); 
  WorldControler::Add( sp  );	
}
//------------------------
void 
SceneChaos::makeFloor( int pH ){

  int lSz = (rand() % cSizeParoi) + cSizeParoi;
	
  Double3 lPos(  getTransf().TransfDouble3::get(POS)[0]+(lSz>>1), pH+(lSz>>1), 0 );	
  makeAsteroide( lPos, (int)(lSz+randf(1)), GL_TRUE, 0 );
}
//------------------------
void 
SceneChaos::makeWall(int pMin, int pMax, GLboolean pIndestructible, float pSpeedX, float pDeltaX, float pAleaX ){

  float cX=0;

  float vY = randf(WorldGame::GlobalScroll*0.2f);

  for( int i=pMax;;){


    if( pMin < pMax ) {
      if( i <= pMin )
        break; 
      i -=cSizeParoi>>1 ;
    }
    else {
      if( i >= pMin )
        break;
      i +=cSizeParoi>>1 ;
    }
		
    int lSz = (int) randf(cSizeParoi>>2) + cSizeParoi;
    Double3 lPos(  getTransf().TransfDouble3::get(POS)[0]+cX+(lSz>>2), i+(lSz>>2), randf(lSz>>2) );	

    cX += pSpeedX + randf( pAleaX );
    pSpeedX += pDeltaX ;
		
    makeAsteroide( lPos, lSz, pIndestructible, vY );
  }
}

//------------------------
void 
SceneChaos::makeArtefact() {
	
  int sz = 25;
	
  Double3 pos;
  pos[0] = getTransf().TransfDouble3::get(POS)[0];
  pos[ 1 ] = cH;
  pos[ 2 ] = 0;
	 
  std::cout << "SceneChaos::makeArtefact " << std::endl;
	
  SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime() );
	
  if( World::GetPositionWithoutCollision( InteractObstacle, pos, sz, 0, (int)cH ) == GL_FALSE){
    std::cout << "SceneChaos::makeArtefact collision" << std::endl;
    return;
  }
  std::cout << "SceneChaos::makeArtefact ok" << std::endl;


  Sprite3d	*sp = NULL;

  float p = randp( 100 );
  //	std::cout << "p:" << p << std::endl;
  if( p<= 20 )
    {
      Double3 lD3( randf( 75 ), randf( 75 ), randf( 75 ));
      sp = TheBonusMaker->makeSpriteBonus( CONTAINER, 
                                           InteractBonus, InteractBonus, 1);
			
      sp->SpriteDouble3::set( SPRITE_SPIN, lD3);
    }
  else 	if( p <= 40 )
    sp = MAKE_MINE_1;
  else 	if( p <= 50 )
    sp = MAKE_MINE_LASER;
  else 	if( p <= 60 )
    sp = MAKE_MINE_ION;


  if( sp ) {
    Double3 lD3 ( WorldGame::GlobalScroll, 0, 0);
    sp->SpriteDouble3::set( SPRITE_SPEED, lD3); 
    sp->getTransf().TransfDouble3::set( POS, pos );
	
    WorldControler::Add( sp  );
  }



}
//------------------------
GLboolean 
SceneChaos::animate() {

  Scene::animate();
	
  float lCurrentTime = WorldControler::GetTime();
	
  // generation des parois de la grotte

	
  if( ( lCurrentTime-SpriteFloat::get( SPRITE_TIMER2)) < cIntervalParoi )
    {
      return GL_FALSE;
    }
  /*
    if( cFirstTime ){
    makeWall(  (cH>>2)+cSizeParoi,  cH, GL_TRUE,  -8, 1, 2 );
    makeWall( (-cH>>2)-cSizeParoi, -cH, GL_TRUE,  -8, 1, 2 );
    cFirstTime = GL_FALSE; 
				
    SpriteFloat::set( SPRITE_TIMER3, lCurrentTime+3 + randp(2));
    }
  */	

  if( ( lCurrentTime-SpriteFloat::get( SPRITE_TIMER3)) >= 0 )
    {
      SpriteFloat::set( SPRITE_TIMER3, lCurrentTime+2 + randf(2));	
				

      float lHauteur = randp( cH-cSizeParoi*4 )+cSizeParoi;
				
      float lDeriveX = randf( 2 );

      float lCorrectX = randf( 1 );

      if( randf(1)< 0 )				
        makeWall( (int)( -lHauteur*1.2),  (int) (randp(cH)+cH*0.5), GL_FALSE, lDeriveX, lCorrectX, randf(5) );
      else
        makeWall( (int)( lHauteur*1.2),  (int)  -(randp(cH)+cH*0.5), GL_FALSE, lDeriveX, lCorrectX, randf(5) );								
    }

  //		makeFloor( cH );
  //		makeFloor( -cH );
  SpriteFloat::set( SPRITE_TIMER2,  WorldControler::GetTime() );
  //	}
		
	
  if( ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_TIMER1)) < cInterval )
    return GL_FALSE;
	
	
  makeArtefact();

  return GL_FALSE;
}
//------------------------
GLboolean SceneChaos::leaveWorld()
{
  makeWall(  (((int) cH)>>2) + cSizeParoi, (int)cH, 6, -1, 2 );
  makeWall( -((((int) cH)>>2) - cSizeParoi), (int)-cH, 6, -1, 2 );

  return GL_FALSE;
}
//**************************************

