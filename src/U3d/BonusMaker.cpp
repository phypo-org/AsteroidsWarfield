#include "BonusMaker.h"


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


BonusMaker* TheBonusMaker=NULL;


//**********************************************************
BonusMaker::BonusMaker()
  :cColorErg(0.3, 0.3, 0.1, 0.5 ),
   cColorRocket(0.1, 0.1, 0.4, 0.5),
   cColorField(0.3, 0., 0.3, 0.5 ),
   cColorLife(0.8, 0.2, 0.2, 0.5 ),
   cColorGold(0.4, 0.4, 0.4, 0.5 ),
   cColorUpgrad(1, 1, 1, 0.9 ),
   cColorUpgradField( 0.5, 0.5, 0., 0.2 )
{
  TheBonusMaker = this;
	
  cPropsErg.ObjPropsFloat4::set( MATERIAL, cColorErg );
  cPropsErg.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	
  cPropsRocket.ObjPropsFloat4::set(  MATERIAL, cColorRocket );
  cPropsRocket.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);

  cPropsField.ObjPropsFloat4::set( MATERIAL, cColorField);
  cPropsField.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);

  cPropsGold.ObjPropsFloat4::set( MATERIAL, cColorGold);
  cPropsGold.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	
  cPropsLife.ObjPropsFloat4::set( MATERIAL, cColorLife);
  cPropsLife.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
		
  cPropsUpgrad.ObjPropsFloat4::set( MATERIAL, cColorUpgrad);
  cPropsUpgrad.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);

  cPropsSkeleton.ObjPropsFloat4::set( MATERIAL, Yellow4);
  cPropsSkeleton.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
  cPropsSkeleton.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

  cPropsUpgradField.ObjPropsFloat4::set( MATERIAL, cColorUpgradField);

  for( int i=0; i<MAX_BONUS;i++)
    cObjBonus[i] = makeBonus( 2+i );
	
  for( int i=0; i<MAX_BONUS;i++)
    cObjUpgrad[i] = makeUpgrad( 3+i );
}
//---------------------------------------
ObjVect*
BonusMaker::makeBonus( float pSz )
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
//---------------------------------------
ObjVect*
BonusMaker::makeUpgrad( float pSz )
{
  ObjVect* lObjVect = new ObjVect();

  O3dObj* lObj0= new O3dObjPrim( O3dObjPrim::PrimCube, pSz*0.5 );
  //	lObj0->setObjProps( &cPropsUpgrad);
  lObjVect->push_back( lObj0);	

  O3dObj* lObj1= new O3dObjPrim( O3dObjPrim::PrimCube, pSz );
  lObj1->setObjProps( &cPropsSkeleton);

  O3dObj* lObj2 = new O3dObjPrim( O3dObjPrim::PrimCube, pSz*0.75 );
	
  lObjVect->push_back( lObj1);	
  lObjVect->push_back( lObj2 );	

  O3dObj* lField = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*1.2, 6, 8 );
  lField->setObjProps( &cPropsUpgradField );
  lObjVect->add( lField );


  // Pourquoi setUseList( GL_FALSE) ? Couleurs ???? 
	
  lObj1->setUseList( GL_FALSE);
  lObj2->setUseList( GL_FALSE);
  lField->setUseList( GL_FALSE);
  lObjVect->setUseList( GL_FALSE);
	
  lObjVect->setRadius( pSz);
  return lObjVect;
}
//----------------------------------------------
Sprite3d*
BonusMaker::makeSpriteBonus( int cObjType, EnumBonus pType,  unsigned int pMaskObj, unsigned int pMaskInteract, int pVal, int pVal2 )
{
  pVal/=2;     // phipo 20131105

  if( pVal <= 0 )
    pVal = 1;

  if( pVal >= MAX_BONUS )
    pVal= MAX_BONUS-1;

  Sprite3d *sp;

  if( pType == CONTAINER_UPGRAD )
    sp = new Sprite3dObj( cObjUpgrad[pVal] );
  else
    sp = new Sprite3dObj( cObjBonus[pVal] );

  sp->setMask( pMaskObj, pMaskInteract);
  //  sp->setMask( InteractBonus, InteractBonus );
 

  sp->SpriteFloat::set( CONTAINER_TYPE, pType );
 
  switch( pType)
    {
    case CONTAINER_ERG:
      sp->SpriteFloat::set( CONTAINER_VALUE, 100*pVal );
      sp->setObjProps( &cPropsErg );
      break;

    case CONTAINER_ROCKET:
      sp->SpriteFloat::set( CONTAINER_VALUE, 10*pVal);
      sp->setObjProps( &cPropsRocket);
      break;

    case CONTAINER_FIELD :
      sp->SpriteFloat::set( CONTAINER_VALUE, 10*pVal );
      sp->setObjProps( &cPropsField );
      break;

    case CONTAINER_GOLD :
      sp->SpriteFloat::set( CONTAINER_VALUE, 10*pVal );
      sp->setObjProps( &cPropsGold );
      break;

    case CONTAINER_UPGRAD :
      sp->SpriteFloat::set( CONTAINER_VALUE, pVal );
      switch( pVal ){
      case UPGRAD_ERG :   sp->setObjProps( &cPropsErg); break;
      case UPGRAD_ROCKET: sp->setObjProps( &cPropsRocket); break;
      case UPGRAD_FIELD:  sp->setObjProps( &cPropsField); break;
				
      case UPGRAD_PHASER:   sp->setObjProps( &cPropsErg); break;
      case UPGRAD_LAUNCHER: sp->setObjProps( &cPropsRocket); break;
      case UPGRAD_MOTOR:    sp->setObjProps( &cPropsLife); break;
      default:
        sp->setObjProps( &cPropsGold);
      }
      break;

    case CONTAINER_LIFE :
    default:;
      sp->SpriteFloat::set( CONTAINER_VALUE, pVal );
      sp->setObjProps( &cPropsLife );
      break;
    }
  sp->SpriteFloat::set( CONTAINER_VALUE2, pVal2 );

  sp->SpriteFloat::set( SPRITE_LIFE_POINT,  10*pVal);
  sp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, 10*pVal);
  sp->SpriteFloat::set( SPRITE_DESTROY_POINT, 0 );
  sp->SpriteLong::set( SPRITE_TYPE, cObjType );

  Double3 lSpin3( randf( 150 ), randf( 150 ), randf( 150 ));
  sp->SpriteDouble3::set( SPRITE_SPIN,  lSpin3 );

  return sp;
}
//----------------------------------------------
Sprite3d*
BonusMaker::makeSpriteBonus( int cObjType, unsigned int pMaskObj, unsigned int pMaskInteract, int pVal )
{

  static long sTypeUpgrad = (long)randp(  MAX_UPGRAD );

  float lAlea = randp(100);

  if( WorldControler::sDebug > 1 ){		
    if( lAlea < 10 )
      return makeSpriteBonus( cObjType, CONTAINER_ERG, pMaskObj, pMaskInteract, pVal );
    else		
      if( lAlea < 20 )
        return makeSpriteBonus( cObjType, CONTAINER_ROCKET, pMaskObj, pMaskInteract, pVal );
      else		
        if( lAlea < 30 )
          return makeSpriteBonus( cObjType, CONTAINER_FIELD, pMaskObj, pMaskInteract, pVal );
        else		
          //					if( lAlea < 40 )
          //						return makeSpriteBonus( cObjType, CONTAINER_GOLD, pMaskObj, pMaskInteract, pVal );
          //					else
          if( lAlea < 90 )
            return makeSpriteBonus( cObjType, CONTAINER_UPGRAD, pMaskObj, pMaskInteract, pVal, rand()%MAX_UPGRAD );
				
    return makeSpriteBonus( cObjType, CONTAINER_LIFE, pMaskObj, pMaskInteract, pVal );
  }
	
  /*
    if( lAlea < 35 )
    return makeSpriteBonus( cObjType, CONTAINER_ERG, pMaskObj, pMaskInteract, pVal );
    else		
    if( lAlea < 60 )
    return makeSpriteBonus( cObjType, CONTAINER_ROCKET, pMaskObj, pMaskInteract, pVal );
    else		
    if( lAlea < 90 )
    return makeSpriteBonus( cObjType, CONTAINER_FIELD, pMaskObj, pMaskInteract, pVal );
    else		
    if( lAlea < 95 )
    return makeSpriteBonus( cObjType, CONTAINER_GOLD, pMaskObj, pMaskInteract, pVal );
    else
    if( lAlea <= 100 )
    return makeSpriteBonus( cObjType, CONTAINER_UPGRAD, pMaskObj, pMaskInteract, pVal, (sTypeUpgrad++)%MAX_UPGRAD );
    return makeSpriteBonus( cObjType, CONTAINER_LIFE, pMaskObj, pMaskInteract, pVal );
  */
	
  if( lAlea < 40 )
    return makeSpriteBonus( cObjType, CONTAINER_ERG, pMaskObj, pMaskInteract, pVal );
  else		
    if( lAlea < 60 )
      return makeSpriteBonus( cObjType, CONTAINER_ROCKET, pMaskObj, pMaskInteract, pVal );
    else		
      if( lAlea < 99 ) // 95
        return makeSpriteBonus( cObjType, CONTAINER_FIELD, pMaskObj, pMaskInteract, pVal );
	
	
  return makeSpriteBonus( cObjType, CONTAINER_UPGRAD, pMaskObj, pMaskInteract, pVal, (sTypeUpgrad++)%MAX_UPGRAD ); 
}
