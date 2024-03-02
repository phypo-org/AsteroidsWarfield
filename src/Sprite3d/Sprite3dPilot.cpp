#include "Sprite3dPilot.h"

#include <iostream>

#include "World.h"
#include "O3d/O3dKamera.h"
#include "Utils3d.h"

//**************************************
Sprite3dPilot::Sprite3dPilot( O3dObj *pObj )
:Sprite3dObj( pObj ),
 cMemX(-1), cMemY(-1),
	cManX(0.03), cManY(0.10)
{

}
//-----------------------------------
GLboolean Sprite3dPilot::animate()
{
	if(SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
		return GL_TRUE;

	Double3 lResult;
	T3dTransf &lTran = getTransf();
  
	WorldControler::GetCurrentWorld()->getKamera()->getProject( lTran.get( POS),  lResult );

	Double3 lPos(	WorldControler::GetMouseX(),	WorldControler::GetMouseY(),  	lResult[2] );

	WorldControler::GetCurrentWorld()->getKamera()->getUnProject( lPos, lResult );

//	lTran.set( T3dTransf::POS, lResult );

	
//	Kamera *lKam = World::sCurrentWorld->getKamera();
//	lResult[3] += 50;
//	lKam->getTransf().set( T3dTransf::POS, lResult );

	
	 Double3& lD = getTransf().TransfDouble3::get( POS);
//	 lD[0] += (lResult[0] - MkGetPOS()[0])*0.15;
//	 lD[1] += (lResult[1] - MkGetPOS()[1])*0.15;

	// ICI POUR CHANGER LA MANABILITE DU VAISSEAU
	 lD[0] += (lResult[0] - MkGetPOS()[0])*cManX;
	 lD[1] += (lResult[1] - MkGetPOS()[1])*cManY;
	 getTransf().TransfDouble3::set( POS, lD );

//	 getTransf().TransfDouble3::get( POS )[1]= lD[1];

//	set( Sprite3d::SPEED)[0] = (lResult[0] - get( T3dTransf::POS)[0]);
//	 get( Sprite3d::SPEED)[1] = (lResult[1] - get( T3dTransf::POS)[1]);

//	 Sprite3d::animate();	
//	lTran.cPos[ 0 ] += cSpeed[ 0 ];
//	lTran.cPos[ 1 ] += cSpeed[ 1 ];
	

//	cout << "Pos:" << lTran.cPos[ 0 ] << ", " << lTran.cPos[ 1 ] << "\tSpeed:" << cSpeed[ 0 ]  <<", " << cSpeed[ 1 ] <<endl;
	if( cObj != NULL )
		cObj->animate();

	return Sprite3d::animate();
}	

//--------------------------------
GLboolean Sprite3dPilot::leaveWorld()
{
	return GL_FALSE;
}
//--------------------------------
GLboolean Sprite3dPilot::collision( Sprite3d & pSprite )
{
	return Sprite3d::collision(pSprite);
//	return GL_FALSE;
}
//--------------------------------

void Sprite3dPilot::mouseMove( int pX, int pY )
{
}
//--------------------------------
void Sprite3dPilot::mouseButton( int pButton, int pState, int pX, int pY )
{
/*
  O3dObj *obj1 = new ObjSphere( 0.5, 4, 4 );
  Sprite3d *sp1 = new Sprite3d( obj1 );

  sp1->setTransf( getTransf() );
  Double3 f1 = { 0.0, 0.0, -30.0  };
  sp1->set( Sprite3d::SPEED, f1 );

  Float4 pr6 = {1, 0.5, 0.5, 0.8};
  Float4 pr7 = {0.3, 0.3, 0.3, 1};
  O3dObjProps* lProps = new O3dObjProps();
  lProps->set( O3dObjProps::PROPS_MATERIAL, pr6 );
  lProps->set( O3dObjProps::PROPS_EMISSION, pr7 );
  sp1->setProps( lProps );

  World::sCurrentWorld->add( sp1 );
*/
}
//--------------------------------
void Sprite3dPilot::keyUp( unsigned char key, int x, int y )
{
	std::cout << "keyUp:" << key <<std::endl;
}
//--------------------------------
void Sprite3dPilot::key( unsigned char key, int x, int y )
{
	std::cout << "key:" << key <<std::endl;
}
//--------------------------------
void Sprite3dPilot::specialKey( int  key, int x, int y )
{
	std::cout << "specialKey:" << key <<std::endl;
}


//**************************************
