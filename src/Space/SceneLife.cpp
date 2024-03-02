#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"


#include "SceneLife.h"
#include "WorldGame.h"

#include "U3d/BonusMaker.h"

#include <iostream>

//**************************************
SceneLife::SceneLife( Double3& lPos, float pH, float pV)
	:Scene( "Catch the life", 0, 0, pH, pV ),
 cFirstTime(GL_TRUE)
{
	getTransf().TransfDouble3::set( POS, lPos );
}
//------------------------
GLboolean SceneLife::animate()
{
	Sprite3d::animate();

	if( cFirstTime )
		{
			int sz = 25;

			Double3 pos;
			pos[0] = getTransf().TransfDouble3::get(POS)[0];
			pos[ 2 ] = 0;


			if( World::GetPositionWithoutCollision( InteractObstacle, pos, sz, 0, (int)cH ) == GL_FALSE){
				return GL_FALSE;
			}
			Sprite3d *sp;

			cFirstTime = GL_FALSE;

			Double3 lD3( randf( 75 ), randf( 75 ), randf( 75 ));
			sp = TheBonusMaker->makeSpriteBonus( CONTAINER, CONTAINER_LIFE,
																					 InteractBonus, InteractBonus, 1);
			
			sp->SpriteDouble3::set( SPRITE_SPIN, lD3);

			Double3 lV3 ( WorldGame::GlobalScroll, 0, 0);
			sp->SpriteDouble3::set( SPRITE_SPEED, lV3); 
			sp->getTransf().TransfDouble3::set( POS, pos );
	
			WorldControler::Add( sp  );
		}
	return GL_FALSE;
}
