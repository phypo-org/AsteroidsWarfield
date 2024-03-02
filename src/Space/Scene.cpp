#include <stdlib.h>
#include <stdio.h>

#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"

#include "Scene.h"

#include "ShipsMaker.h"
#include "U3d/BonusMaker.h"


#include <iostream>



//*****************************************
Scene::Scene( const char* pName, int pHardness,
							float pInterval,
							float  pH, float pV )
:Sprite3dObj(  new ObjOdron( 30, 0)),
 cHardness(pHardness),
 cInterval( pInterval ),
 cH( pH ),
 cV( pV ),
 cName(pName)
{
  sprintf( cStrInfo, "Hard:%d_Time:%5.2f_%s", cHardness, cInterval, cName.data() );
  
}
//------------------------
GLboolean
Scene::animate()
{
  Sprite3d::animate();
  return GL_FALSE;
}
//------------------------
const char*
Scene::getStrInfo(){
	return cStrInfo;
}
//*****************************************
