#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h" 
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"

#include "SceneBase.h"
#include "ShipsMaker.h"
#include "U3d/BonusMaker.h"


#include <iostream>

//*****************************************
SceneBase::SceneBase( const char* pName, int pHardness,  Double3& lPos, 
								float pInterval, float  pH, float pV, int pShipType )
  :SceneSprite( pName, ASTEROIDE_CRISTAL, pHardness, lPos, pInterval, pH, pV ),
cShipType( pShipType)
{


}

//------------------------
GLboolean SceneBase::animate()
{

  Sprite3d::animate();
	

  if( ( WorldControler::GetTime()-SpriteFloat::get( SPRITE_TIMER1)) < cInterval )
	  return GL_FALSE;


	 
  SpriteFloat::set( SPRITE_TIMER1,  WorldControler::GetTime());

  Double3 pos;
  pos[0] = getTransf().TransfDouble3::get(POS)[0]-40;
  pos[ 2 ] = 0;
  pos[ 1 ] = randf( cH -30 );

 	if( World::GetPositionWithoutCollision( InteractObstacle, pos, 10, 0, cH ) == GL_FALSE){
		return GL_FALSE;
	}

 
  Sprite3d *sp=NULL;

  float p = randp( 100+cHardness );

  if( p<=5 )
  {
	Double3 lD3( randf( 150 ), randf( 150 ), randf( 150 ));
	sp = TheBonusMaker->makeSpriteBonus( CONTAINER, InteractBonus, InteractBonus, 1);
	sp->SpriteDouble3::set( SPRITE_SPIN, lD3);
  }
	else	if( p <= 95){
		sp = MAKE_INTERCEPTOR_ATTACK(cHardness) ;	
	} 	
	/*	else	if( p <= 85)	
		{ 
			if( cHardness < 3 )
				sp = MAKE_CROISEUR1;	
			else 	if( cHardness < 4 )
				sp = MAKE_CROISEUR2;						
			else if( cHardness < 6 )
					sp = MAKE_CROISEUR2;						
		}
	else if( p <= 90)						
		{
			if( cHardness < 4 )
				sp = MAKE_CUIRASSE1;
			else
				if( cHardness < 7 )
					sp = MAKE_CUIRASSE2;
				else 
					sp = MAKE_CUIRASSE3;
		}
	*/
	else 
		{
			if( cShipType == BASE_TORE ) {
            
				if( cHardness < 5 )
					sp = MAKE_BASE1; 	
				else
					if( cHardness < 8 )
						sp = MAKE_BASE2; 	
					else 
						sp = MAKE_BASE3; 
			}
			else
				{
 			if( cHardness < 5 )
				sp = MAKE_MEGA_CROISEUR1; 	
			else
				if( cHardness < 8 )
					sp = MAKE_MEGA_CROISEUR2; 	
				else 
					sp = MAKE_MEGA_CROISEUR3; 
           }	
			sp->MkGetANGLE() [0] = randp(180);
		}
  if( sp )
	{
	  Double3 lD3 ( -15, 0, 0);
	  sp->SpriteDouble3::set( SPRITE_SPEED, lD3); 
	  sp->getTransf().TransfDouble3::set( POS, pos );


		WorldControler::Add( sp  );
	}
  return GL_FALSE;
}

//**************************************

