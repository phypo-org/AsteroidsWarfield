#include <stdlib.h>

#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Sprite3d.h"
#include "Sprite3d/Utils3d.h"
#include "Sprite3d/Collision.h"
#include "Sprite3d/ObjText2d.h"
#include "Sprite3d/Random.h"
#include "Sprite3d/ObjOdron.h"

#include "WorldGame.h"

#include "U3d/SpriteExplosion.h"

#include "T3d/T3dLoadImg.h"

#include "AsteroidesMaker.h"
#include "Space/Def.h"

AsteroidesMaker* TheAsteroidesMaker=NULL;

#define ASTEROIDE_TYPE   SPRITE_USER1


// **********************************************************
AsteroidesMaker::AsteroidesMaker()
  :cColorGrey(  0.5, 0.5, 0.5, 1.0 ),
   cColorSnow(  0.6, 0.6, 1.0, 1.0 ),
   cColorIce(  0.6, 0.6, 1.0, 0.5),
   cColorCristal(  0.3, 0.4, 0.8, 0.05),
   cColorPlasmaSolaire1(  0.8, 0.4, 0.2, 0.05),
   cColorPlasmaSolaire2(  0.8, 0.5, 0.8, 0.15)
{
  TheAsteroidesMaker = this;


  cPropsSnow.ObjPropsFloat4::set( MATERIAL, cColorSnow );
  cPropsIce.ObjPropsFloat4::set( MATERIAL, cColorIce );

  cPropsCristal.ObjPropsFloat4::set( MATERIAL, cColorCristal );

  cPropsPlasmaSolaire1.ObjPropsFloat4::set( MATERIAL, cColorPlasmaSolaire1 );
  cPropsPlasmaSolaire2.ObjPropsFloat4::set( MATERIAL, cColorPlasmaSolaire2 );


  // cPropsLune.ObjPropsFloat4::set( MATERIAL, cColorGrey );
  std::string lName;


  T3dLoadImage imgLune( WorldGame::GetPathConfig( lName, WorldGame::PathType::TEXTURE, "Asteroids.TextureLune") );
  caTexLune = new T3dTexture( imgLune.width, imgLune.height, imgLune.makeRGBA() );
  cPropsLune.setTexture( caTexLune );

  T3dLoadImage imgMars( WorldGame::GetPathConfig( lName, WorldGame::PathType::TEXTURE, "Asteroids.TextureMars") );
  caTexMars = new T3dTexture( imgMars.width, imgMars.height, imgMars.makeRGBA() );
  cPropsMars.setTexture( caTexMars );

  T3dLoadImage imgWater( WorldGame::GetPathConfig( lName, WorldGame::PathType::TEXTURE, "Asteroids.TextureWater") );
  caTexWater = new T3dTexture( imgWater.width, imgWater.height, imgWater.makeRGBA() );
  cPropsWater.ObjPropsFloat4::set( MATERIAL, cColorIce );
  cPropsWater.setTexture( caTexWater );

}
//---------------------------------------
O3dObj*
AsteroidesMaker::makeAsteroide( float pSz, int pFacette )
{
  O3dObj * lObj =  new ObjOdron( pSz, pFacette );
  lObj->setRadius( pSz );
  return lObj;
}
//---------------------------------------
ObjVect*
AsteroidesMaker::makeAsteroideSnow(float pSz, int pFacette )
{
  ObjVect* lOvect = new ObjVect;
  O3dObj * lObj;

  lOvect->push_back( (lObj=new ObjOdron(  pSz, pFacette) ));

  for( int i=0; i< pSz*0.2; i++)
    {
      lOvect->push_back( (lObj=new ObjOdron( randp( pSz-3)+3, (int) randp( pFacette-2)+2 )));
      Double3 lD3( randf(pSz), randf(pSz),randf(pSz));
      lObj->getTransf().TransfDouble3::set( POS, lD3 );
    }

  lOvect->setRadius( pSz );
  lOvect->setObjProps( &cPropsSnow);
  return lOvect;
}

//---------------------------------------
ObjVect*
AsteroidesMaker::makeAsteroideCristal(float pSz, int pFacette )
{
  ObjVect* lOvect = new ObjVect;
  O3dObj * lObj;



  for( int i =3; i < pSz+2; i +=2)
    {
      lOvect->push_back( (lObj=new ObjOdron(  -i, pFacette) ));
      lObj->setObjProps( &cPropsCristal);
      Double3 lD3( randf(360), randf(360),randf(360));
      lObj->getTransf().TransfDouble3::set( ANGLE, lD3 );
    }
 
  lOvect->setRadius( pSz );
  lOvect->setObjProps( &cPropsCristal);
  return lOvect;
}
//----------------------------------------------
ObjVect*
AsteroidesMaker::makePlasmaSolaire(float pSz, int pFacette )
{
  ObjVect* lOvect = new ObjVect;
  O3dObj * lObj;



  for( int i =3; i < pSz+2; i +=2)
    {
      lOvect->push_back( (lObj=new ObjOdron(  -i, pFacette) ));
      lObj->setObjProps( &cPropsPlasmaSolaire1);
      Double3 lD3( randf(360), randf(360),randf(360));
      lObj->getTransf().TransfDouble3::set( ANGLE, lD3 );
    }

  lOvect->setRadius( pSz );
  lOvect->setObjProps( &cPropsPlasmaSolaire2);
  return lOvect;
}

//---------------------------------------
O3dObj*
AsteroidesMaker::makeAsteroideIce( float pSz, int pFacette )
{
  O3dObj * lObj = new ObjOdron(  pSz, pFacette);

  lObj->setRadius( pSz );
  lObj->setObjProps( &cPropsIce);
  return lObj;
}
//----------------------------------------------
Sprite3d*
AsteroidesMaker::makeSpriteAsteroide( EnumAsteroides pType, float pSz, int pFacette )
{
  Sprite3dObj *sp ;

  switch( pType )
    {
    case ASTEROIDE_PIERRE:
      sp = new Sprite3dObj( makeAsteroide( pSz, pFacette));
      sp->getObj()->setObjProps( &cPropsLune );
      break;
    case ASTEROIDE_MARS:
      sp = new Sprite3dObj( makeAsteroide( pSz, pFacette));
      sp->getObj()->setObjProps( &cPropsMars );
      break;
    case ASTEROIDE_WATER:
      sp = new Sprite3dObj( makeAsteroide( pSz, pFacette));
      sp->getObj()->setObjProps( &cPropsWater );
      break;
    case ASTEROIDE_SNOW:
      sp  = new Sprite3dObj( makeAsteroideSnow( pSz, pFacette));
      break;
    case ASTEROIDE_CRISTAL:
      sp  = new Sprite3dObj( makeAsteroideCristal( pSz, pFacette));
      break;
    case PLASMA_SOLAIRE:
      sp  = new Sprite3dObj( makePlasmaSolaire( pSz, pFacette));
      break;
    case ASTEROIDE_ICE:
    default:
      sp  = new Sprite3dObj( makeAsteroideIce( pSz, pFacette));
    }
  sp->SpriteFloat::set( ASTEROIDE_TYPE, pType );

  // Comme chaque object est unique il doit etre detruit a la mort du sprite
  sp->setDeepDestroy(GL_TRUE);

  //  sp->setMask( InteractObstacle, InteractObstacle );
  sp->setMask( InteractObstacleIn, InteractObstacleOut );

  sp->setAction( SPRITE_ACTION_COLLISION, this);
  sp->SpriteFloat::set( SPRITE_LIFE_POINT, pSz*2 );
  sp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, pSz*2 );
  sp->SpriteFloat::set( SPRITE_DESTROY_POINT, 1+pSz/4 );
  sp->SpriteLong::set ( SPRITE_TYPE, ASTEROIDE );

  return sp;
}
//------------------------------------------------
GLboolean
AsteroidesMaker::collision( Sprite3d &pMySprite, Sprite3d &pSprite, void *pParam )
{

  if( pSprite.getDefMask() == InteractObstacle )
    {
           std::cout  << "BUG AsteroidesMaker::collision" << std::endl;
      return GL_TRUE; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      if(  pMySprite.getObjectId() != pSprite.cLastColId
           || pSprite.getObjectId() != pMySprite.cLastColId)
        {
          Double3 speed1( pMySprite.SpriteDouble3::get( SPRITE_SPEED ));
          Double3 speed2( pSprite.SpriteDouble3::get( SPRITE_SPEED ) );

          pMySprite.getTransf().TransfDouble3::get( POS ) -= speed1;
          pSprite.getTransf().TransfDouble3::get( POS ) -= speed2;

          // On revient en vitesse par seconde !!!!!
          speed1 /= WorldControler::GetRatio();
          speed2 /= WorldControler::GetRatio();


          pSprite.cLastColId = pMySprite.getObjectId();
          pMySprite.cLastColId = pSprite.getObjectId();

          pMySprite.SpriteDouble3::set( SPRITE_SPEED, speed1 );
          pSprite.SpriteDouble3::set( SPRITE_SPEED, speed2 );

        }
      return GL_TRUE;
    }

  pMySprite.SpriteFloat::set( SPRITE_LIFE_POINT,
                              pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT )-pSprite.SpriteFloat::get( SPRITE_DESTROY_POINT ));


  if( pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
    {
      int max = static_cast<long>(randp(pMySprite.getRadius()*0.4)+1.0);
      for( int j=0; j< max; j++)
        {
          SpriteExplosion *sp = new SpriteExplosion( 1.3+randp(pMySprite.getRadius()), 0.3+randp(0.3) );
          sp->setTransf( pMySprite.getTransf() );
          sp->setObjProps( SpriteExplosion::caExplosionProps );
          WorldControler::Add( sp );
        }

      int pSz = static_cast< int>(pMySprite.getRadius()*0.6);
      if( pSz > 30 )
        {
          //		std::cout << "***************** pSz=" << pSz << std::endl;
          pSz = 30;
        }

      //	Double3 lSpinMother( pMySprite.SpriteDouble3::get(SPRITE_SPIN  ));


      int lNbDebris = pSz >>1;
      for( int i = 0; i < lNbDebris; i++ )
        {
          float sz = randp(pSz);

          if( sz < 1.0 )
            continue;


          int w = rand()%2+1;

          long lType = (long)pMySprite.SpriteFloat::get( ASTEROIDE_TYPE );

          Sprite3d *sp = makeSpriteAsteroide( (EnumAsteroides)lType, sz, w );

          sp->setTransf( pMySprite.getTransf() );

          Double3 v3( randf(WorldGame::GlobalScroll)+WorldGame::GlobalScroll , randf(WorldGame::GlobalScroll), 0.0 );
          sp->SpriteDouble3::set( SPRITE_SPEED, v3 );

          Double3 lSpin3( randf( 75 ), randf( 75 ), randf( 75 ));
          sp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3);
          //sp->SpriteDouble3::set( SPRITE_SPIN,  lSpinMother);


          sp->Sprite3d::animate();
          sp->Sprite3d::animate();
          sp->Sprite3d::animate();

          WorldControler::Add( sp );
        }
      WorldControler::KillSprite( &pMySprite );
    }
  else
    {
      pMySprite.SpriteDouble3::get( SPRITE_SPEED)[0] =  pMySprite.SpriteDouble3::get( SPRITE_SPEED )[0]*0.90;
      pMySprite.SpriteDouble3::get( SPRITE_SPEED)[1] =  pMySprite.SpriteDouble3::get( SPRITE_SPEED )[1]*0.90;
      pMySprite.SpriteDouble3::get( SPRITE_SPEED)[2] =  pMySprite.SpriteDouble3::get( SPRITE_SPEED )[2]*0.90;
    }
  return GL_TRUE;
}
//**************************
