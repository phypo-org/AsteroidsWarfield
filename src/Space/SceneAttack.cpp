#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"

#include "SceneAttack.h"
#include "ShipsMaker.h"
#include "WorldGame.h"

#include "U3d/BonusMaker.h"


#include <iostream>

//*****************************************
SceneAttack::SceneAttack( const char* pName,  int pHardness, Double3& lPos, 
                          float pInterval, float  pH, float pV )
  :SceneSprite( pName, ASTEROIDE_CRISTAL, pHardness, lPos, pInterval, pH, pV )
{

}
//------------------------
SceneAttack::~SceneAttack()
{
}
//------------------------
GLboolean SceneAttack::animate()
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
  else if( p <= 30)
    {
      sp = MAKE_SHIP1(cHardness);
    }
  else	if( p <= 40 ) 
    {
      sp = MAKE_SHIP2(cHardness);
    }
  else	if( p <= 50 )
    {
      sp = MAKE_SHIP3(cHardness);
    }
  else	if( p <= 60 )
    {
      sp = MAKE_TORPILLEUR_ATTACK(cHardness);
    }
  else	if( p <= 70)
    {
      sp = MAKE_INTERCEPTOR_ATTACK(cHardness) ;	
    }
  else if( p <= 90)
    {
      if( cHardness < 3 )
        sp = MAKE_TORPILLEUR1;	
      else 	if( cHardness < 4 )
        sp = MAKE_TORPILLEUR2;	
      else 	if( cHardness < 5 )
        sp = MAKE_TORPILLEUR3;	
      else 	if( cHardness < 6 )
        sp = MAKE_TORPILLEUR4;	
      else 	if( cHardness < 7 )
        sp = MAKE_TORPILLEUR5;	
    }
  else	if( p <= 110)	
    {
      if( cHardness < 3 )
        sp = MAKE_CROISEUR1;	
      else 	if( cHardness < 4 )
        sp = MAKE_CROISEUR2;
      else if( cHardness < 5 )					
        sp = MAKE_CROISEUR3;						
      else if( cHardness < 6 )
        sp = MAKE_CROISEUR4;						
      else
        sp = MAKE_CROISEUR5;						
    }
  else 						
    {
      if( cHardness < 4 )
        sp = MAKE_CUIRASSE1;
      else
        if( cHardness < 6 )
          sp = MAKE_CUIRASSE2;
        else 
          if( cHardness < 7 )
            sp = MAKE_CUIRASSE3;
      if(  cHardness < 8 )
        sp = MAKE_CUIRASSE4;
      else
        sp = MAKE_CUIRASSE5;
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

