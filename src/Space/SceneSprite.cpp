#include <stdlib.h>
#include "Def.h"

#include "T3d/T3dLoadImg.h"
#include "T3d/T3dColor.h"

#include "O3d/O3dObjPrim.h"

#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/World.h"
#include "Sprite3d/Random.h"


#include "SceneSprite.h"
#include "ShipsMaker.h"
#include "AsteroidesMaker.h"
#include "WorldGame.h"


#include <iostream>
//**************************************
SceneSprite::SceneSprite( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3& lPos,
			  float pInterval, float  pH, float pV )
:Scene( pName, pHardness, pInterval, pH, pV ),
cTypeAsteroide(pTypeAsteroide)
{

  //===== Initialisation des props du generateur =====
  Float4 mat1(   0.8, 0.4, 0.5, 1.0 );

  caPropsGen = new O3dObjProps;
  caPropsGen->ObjPropsFloat4::set( MATERIAL, mat1 );


	caGenTexture = WorldGame::LoadTextureConfig( "Asteroids.Texture1"  );
  caPropsGen->setTexture( caGenTexture );
  setObjProps( caPropsGen );

  //=============================================


  //======= Positionnement spacial du Generateur ====
  getTransf().TransfDouble3::set( POS, lPos );
  SpriteFloat::set( SPRITE_TIMER1, WorldControler::GetTime());

  Double3 spin( 5.0, 8.0, 10.0 );
  SpriteDouble3::set( SPRITE_SPIN, spin );

  cInteractDef = cInteractAtt = 0;
}
//------------------------
GLboolean SceneSprite::leaveWorld()
{
  return GL_FALSE;
}
