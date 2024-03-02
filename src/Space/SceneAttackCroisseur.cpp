#include <stdlib.h>
#include "Def.h" 

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"

#include "SceneAttackCroisseur.h"
#include "ShipsMaker.h"
#include "WorldGame.h"

#include "U3d/BonusMaker.h"


#include <iostream>

//*****************************************
SceneAttackCroisseur::SceneAttackCroisseur( const char* pName,  int pHardness, Double3& lPos, 
													 float pInterval, float  pH, float pV )
:SceneSprite( pName, ASTEROIDE_CRISTAL, pHardness, lPos, pInterval, pH, pV )
{

   cInteractDef = cInteractAtt = 0;
}
//------------------------
SceneAttackCroisseur::~SceneAttackCroisseur()
{
}
//------------------------
GLboolean SceneAttackCroisseur::animate()
{
  Sprite3d::animate();


  if( ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_TIMER1)) < cInterval )
	  return GL_FALSE;

	 
  SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());

  Double3 pos;
  pos[0] = getTransf().TransfDouble3::get(POS)[0]-40;
  pos[ 2 ] = 0;
  pos[ 1 ] = (rand() % (((int)cH) << 1))-((int)cH);
 

  Sprite3d *sp=NULL;

  float p = randp( 100 + cHardness*5 );
	
	if( p <= 2 )
		{
		Double3 lD3( randf( 150 ), randf( 150 ), randf( 150 ));
		sp = TheBonusMaker->makeSpriteBonus( CONTAINER, 
																				 InteractBonus, InteractBonus, 1);
		sp->SpriteDouble3::set( SPRITE_SPIN, lD3);
  }			
	
	if( p < 70 ){
	sp = MAKE_INTERCEPTOR_ATTACK(cHardness) ;	
		}
	else 
		{
			if( cHardness < 3 )
				sp = MAKE_MEGA_CROISEUR1;	
			else 	if( cHardness < 5 )
				sp = MAKE_MEGA_CROISEUR2;	
			else 	
				sp = MAKE_MEGA_CROISEUR3;	
		}
						
  if( sp )
		{
			Double3 lD3 ( WorldGame::GlobalScroll, 0, 0);
			sp->SpriteDouble3::set( SPRITE_SPEED, lD3); 
			sp->getTransf().TransfDouble3::set( POS, pos );
			
			WorldControler::Add( sp  );
		}
  return GL_FALSE;
}
//**************************************

