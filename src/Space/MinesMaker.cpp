#include <stdlib.h>

#include "MinesMaker.h"

#include "T3d/T3dLoadImg.h"

#include "Sprite3d/World.h"
#include "Sprite3d/ObjOdron.h"

#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Sprite3d.h"
#include "Sprite3d/Utils3d.h"
#include "Sprite3d/Collision.h"
#include "Sprite3d/ObjText2d.h"
#include "Sprite3d/Random.h"


#include "U3d/WeaponsMaker.h"
#include "U3d/SpriteExplosion.h"
#include "U3d/BonusMaker.h"
#include "U3d/Tourelle.h"

#include "Space/Def.h"

#include <math.h>


MinesMaker* TheMinesMaker=NULL;
//**********************************************************
MinesMaker::MinesMaker()
  :cColorMine( 0.3, 0.5, 0.6, 1.0 ),
   cColorMineField( 0.4, 0.5, 0, 0.1 )
{
  cPropsMine.ObjPropsFloat4::set( MATERIAL, cColorMine);
  cPropsMine.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
  cPropsMine.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);
  cPropsMineField.ObjPropsFloat4::set( MATERIAL, cColorMineField);
  TheMinesMaker = this;
}
//----------------------------------------------
Tourelle*
MinesMaker::makeModul( float pSz )
{
  Tourelle *lTourelle = new Tourelle();

  O3dObj *lMod = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 5, 5 );
  lMod->setObjProps( &cPropsMine );
  lTourelle->add( lMod );
  return lTourelle;
}
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
Sprite3d*
MinesMaker::makeMine( MineType pMineType, int pMaxLife, float  pSpin,
                      float pMaxSpeed, float pMaxDeltaV, float pReactivity )
{
  Double3 lSpin( pSpin, 0, 0);

  Sprite3dObj* lSp = new Sprite3dObj();
  ObjVect *lVect = new ObjVect();
  int lSz = 3;

  O3dObj* lObj=NULL;
  switch( pMineType  )
    {
    case MINE_LASER :
    case MINE_ION :
      {
        lSz = 4;

        T3dBox lBox( -70, -70, -70,  70,  70, 70 );

        Tourelle* lTour  = makeModul( lSz*0.3 );
        lTour->set( lSp,  0.6,  FIRE_DIRECT, (pMineType == MINE_LASER ? WEAPON_PLASMA_RED : WEAPON_ION ),
                    lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);
        lVect->add(  lTour );
        lObj =lVect;
      }
      break;

    case MINE_1 :
      {
        O3dObj* lCore = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz, 6, 8 );
        lCore->setObjProps( &cPropsMine );
        lVect->add( lCore );
        O3dObj* lField = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*2, 6, 8 );
        lField->setObjProps( &cPropsMineField );
        lVect->add( lField );
        lField = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*4, 6, 8 );
        lField->setObjProps( &cPropsMineField );
        lVect->add( lField );
        lVect->setRadius( lSz*4 );

        lObj =lVect;
      }
      break;


    default:
      std::cout << "MinesMaker::makeMine Unkonw type " << pMineType << std::endl;
      exit(1);
    }
  lSp->setO3dObj( lObj );

  lSp->setMask( InteractWeaponEnemyIn, InteractWeaponEnemyOut);
  lSp->setAction( SPRITE_ACTION_COLLISION, TheMinesMaker );
  lSp->setAction( SPRITE_ACTION_ANIMATE, TheMinesMaker );


  lSp->SpriteFloat::set( SPRITE_LIFE_POINT, pMaxLife );
  lSp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, pMaxLife );
  lSp->SpriteFloat::set( SPRITE_DESTROY_POINT, pMaxLife*5);

  lSp->SpriteLong::set(  SPRITE_TYPE, ALIEN_SHIP );
  lSp->SpriteDouble3::set( SPRITE_SPIN, lSpin  );


  lSp->setDeepDestroy(GL_TRUE);

  return lSp;
}

//----------------------------------------------
GLboolean
MinesMaker::collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam )
{
  //	std::cout << "MinesMaker::collision" << std::endl;

  ObjVect* lObjVect = (ObjVect*)((Sprite3dObj&)pMySprite).getObj();

  for( std::vector <O3dObj*>::iterator iter = lObjVect->begin(); iter != lObjVect->end(); ++iter )
    {
      //			std::cout << "-"  <<  std::flush;
      (*iter)->setAnimateOn( GL_FALSE ); // comme il est detruit c'est normal ! et il risque d'y avoir des ptr sur pMySprite
    }

  int max = static_cast<long>(randp(5)+3);
  for( int j=0; j< max; j++)
    {
      //			std::cout << j <<  std::endl;

      SpriteExplosion *sp = new SpriteExplosion( pMySprite.getRadius(), 0.6+randp(0.4), max );
      sp->setTransf( pMySprite.getTransf() );
      //			sp->setObjProps( SpriteExplosion::caExplosionProps );
      sp->setObjProps( &cPropsMineField );

      //		sp->setMask( InteractEnemy, InteractEnemyWeapon );

      WorldControler::Add( sp );
    }

  lObjVect->clear();

  WorldControler::KillSprite( &pMySprite );


  //	std::cout << "MinesMaker::collision fin" << std::endl;

  return GL_TRUE;
}
//----------------------------------------------
GLboolean
MinesMaker::animate( Sprite3d &pMySprite, void * pParam )
{
  ////	Float4 lColor	cPropsMineField.ObjPropsFloat4::get( MATERIAL );


  return GL_TRUE;
}
//----------------------------------------------
