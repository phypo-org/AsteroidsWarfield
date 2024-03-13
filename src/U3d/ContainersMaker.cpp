#include "ContainersMaker.h"


#include "T3d/T3dColor.h"
#include "Sprite3d/World.h"
#include "Sprite3d/ObjOdron.h"

#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Sprite3d.h"
#include "Sprite3d/Utils3d.h"
#include "Sprite3d/Collision.h"
#include "Sprite3d/ObjText2d.h"
#include "Sprite3d/Random.h"
 
#include "SpriteExplosion.h"


ContainersMaker* TheContainersMaker=NULL;


//**********************************************************
ContainersMaker::ContainersMaker()
  :cColorErg(0.3, 0.3, 0.1, 0.5 ),
   cColorRocket(0.1, 0.1, 0.4, 0.5),
   cColorLife(0.3, 0., 0.3, 0.5 )
{
  TheContainersMaker = this;
	
  cPropsErg.ObjPropsFloat4::set( MATERIAL, cColorErg );
  cPropsErg.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	
  cPropsRocket.ObjPropsFloat4::set(  MATERIAL, cColorRocket );
  cPropsRocket.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	
  cPropsLife.ObjPropsFloat4::set( MATERIAL, cColorLife);
  cPropsLife.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
		
  cPropsSkeleton.ObjPropsFloat4::set( MATERIAL, Yellow4);
  cPropsSkeleton.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
  cPropsSkeleton.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

  cObjContainer = makeContainer( 4 );
}
//---------------------------------------
ObjVect*
ContainersMaker::makeContainer( float pSz )
{
  ObjVect* lObjVect = new ObjVect();

  O3dObj* lObj1= new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 4, 4 );
  lObj1->setObjProps( &cPropsSkeleton);
  O3dObj* lObj2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*0.75, 4, 4 );

  lObjVect->push_back( lObj1);	
  lObjVect->push_back( lObj2 );	

  // Pourquoi setUseList( GL_FALSE) ? Couleurs ???? 

  lObj1->setUseList( GL_FALSE);
  lObj2->setUseList( GL_FALSE);
  lObjVect->setUseList( GL_FALSE);

  lObjVect->setRadius( pSz);
  return lObjVect;
}
//----------------------------------------------
Sprite3d*
ContainersMaker::makeSpriteContainer( int cObjType, EnumContainers pType, unsigned int pMaskObj, unsigned int pMakInteract )
{
  Sprite3d *sp = new Sprite3dObj( cObjContainer );
  sp->setMask( pMaskObj, pMakInteract);
  //  sp->setMask( InteractContainer, InteractContainer );
 

  sp->SpriteFloat::set( CONTAINER_TYPE, pType );
 
  switch( pType)
    {
    case CONTAINER_ERG:
      sp->SpriteFloat::set( CONTAINER_VALUE, 100 );
      sp->setObjProps( &cPropsErg );
      break;

    case CONTAINER_ROCKET:
      sp->SpriteFloat::set( CONTAINER_VALUE, 10);
      sp->setObjProps( &cPropsRocket);
      break;

    case CONTAINER_LIFE :
    default:;
      sp->SpriteFloat::set( CONTAINER_VALUE, 10 );
      sp->setObjProps( &cPropsLife );
      break;

 
    }

  sp->SpriteFloat::set( SPRITE_LIFE_POINT,  10);
  sp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, 10);
  sp->SpriteFloat::set( SPRITE_DESTROY_POINT, 0 );
  sp->SpriteLong::set( SPRITE_TYPE, cObjType );

  Double3 lSpin3( randf( 150 ), randf( 150 ), randf( 150 ));
  sp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );

  return sp;
}
