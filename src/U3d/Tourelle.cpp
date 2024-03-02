#include "Tourelle.h"

#include <math.h>


//*************************************************
Tourelle::Tourelle( Sprite3d* pSprite, float pDelay,  
                    FireMode pFireMode, EnumWeapons pWeapon, 
                    T3dBox& pFireBox, unsigned int pMaskObj, 
                    unsigned int pMakInteract,
                    O3dObj* pObj )
  :AnimatObj( pSprite, pDelay, pObj ),
   cFireMode( pFireMode ),
   cWeapon( pWeapon ),
   cFireBox( pFireBox ),
   cMaskObj(pMaskObj),
   cMakInteract(pMakInteract)
{
	
}
//-----------------------------------------------
Tourelle::Tourelle( )
  :cFireMode( FIRE_STOPPED ),
   cWeapon( WEAPON_NO )
{
	
}
//-----------------------------------------------
// Appeler en fonction de la variable pDelay

void
Tourelle::animateFinal()
{
  if( cFireMode == FIRE_STOPPED )
    return;

  Double3 lDist;
  if( World::GetDistPilot( cMySprite, lDist) == GL_FALSE )
    return;
	
  // est il dans la zone de tir 
  if( cFireBox.isInto( lDist ) == GL_FALSE )
    return ;
		
  Sprite3d *lSp = WeaponsMaker::MakeSprite( &cMySprite->getTransf(), cWeapon, cMaskObj, cMakInteract	);
	
  // On essaye de bien positioner le point de depart

  //	if( cFireMode == FIRE_FRONT )
  //		{
  //			if( lDist[1] < 0 )
  //				return ;
  //		}
	
  lSp->getTransf().TransfDouble3::get( POS ) 
    += this->getTransf().TransfDouble3::get( POS );
  lSp->MkGetPOS()[2]=0.0;
	
	 
  if( cFireMode == FIRE_DIRECT )
    {
      O3dObj::GetNormDirectionInv( lDist );
			
      Double3 lSpeed( lSp->SpriteDouble3::get( SPRITE_SPEED ));
      lSpeed /= WorldControler::GetRatio();

      float lVal = -sqrt( lSpeed[0]*lSpeed[0] + lSpeed[1]*lSpeed[1] );

		
      lSpeed[0]=lDist[0]*lVal;
      lSpeed[1]=lDist[1]*lVal;
      lSpeed[2] =0;

      // ajout pour les missiles
      double lAngle = Sprite3d::GetAngle( lDist[0], lDist[1] );
      lSp->getTransf().TransfDouble3::get( ANGLE )[2] = lAngle;///3.14159265358979323846;
			
			
      lSp->SpriteDouble3::set( SPRITE_SPEED, lSpeed );
    }

	
  WorldControler::Add( lSp );	
}
//-----------------------------------------------
void 
Tourelle::set( Sprite3d* pSprite, float pFireDelay,
               FireMode pFireMode, EnumWeapons pWeapon, 
               T3dBox& pFireBox, 
               unsigned int pMaskObj, unsigned int pMakInteract,
               O3dObj* pObj )
{
  AnimatObj::set( pSprite, pFireDelay, pObj );

  cFireMode = pFireMode;
  cWeapon   = pWeapon;
  cFireBox  = pFireBox;
  cMaskObj  = pMaskObj;
  cMakInteract =  pMakInteract;
}


//*************************************************
