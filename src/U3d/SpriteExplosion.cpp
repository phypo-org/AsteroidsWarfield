#include <FL/glut.H>

#include "Sprite3d/World.h"
#include "Sprite3d/ObjOdron.h"

#include "SpriteExplosion.h"
#include <iostream>
#include <typeinfo>


// Creation de deux objets presistant et compilé pour toutes les explosions
AutoPtr<O3dObjProps> SpriteExplosion::caExplosionProps;
AutoPtr<O3dObjProps> SpriteExplosion::caExplosionPlasmaProps;

std::vector<SpriteExplosion*> SpriteExplosion::sFreeExploVect;

O3dObj* sObjExplosionPlasma = nullptr;
O3dObj* sObjExplosion = nullptr;

//----------------------------------

void* 
SpriteExplosion::operator new( size_t pSz )
{
	//	std::cout << "SpriteExplosion::operator new " << pSz << " sz:" << sFreeExploVect.size() << std::endl;

	if( pSz == sizeof( SpriteExplosion ) && sFreeExploVect.size() > 0 )
		{
			//			std::cout << "***SpriteExplosion::operator new  Vector !" << pSz << " sz:" << sFreeExploVect.size() << std::endl;
			SpriteExplosion* lTmp = sFreeExploVect.back();
			sFreeExploVect.pop_back();
			return lTmp;		
		}
	
	return ::operator new( pSz );
}
//----------------------------------
void 
SpriteExplosion::operator delete( void* pSp, size_t pSz) 
{	
	if( pSp == nullptr ) return;

	if( pSz != sizeof(SpriteExplosion ) )
		{
			//			std::cout << "SpriteExplosion::operator delete  External" << pSz<< std::endl;
			::operator delete( pSp );
			return;
		}
	
	//	std::cout << "***SpriteExplosion::operator delete Internal " << pSz  << " sz:" << sFreeExploVect.size()  << std::endl;

	sFreeExploVect.push_back( (SpriteExplosion*)pSp );
}

//***************************

void
SpriteExplosion::Init()
{
	Float4 pr(0.6, 0.2, 0.0, 0.2);
	caExplosionProps =  new O3dObjProps();
	caExplosionProps->ObjPropsFloat4::set( MATERIAL, pr );
	caExplosionProps->ObjPropsFloat4::set( EMISSION, pr );

	Float4 pr2(0.1, 0.7, 1.0, 0.1);
	caExplosionPlasmaProps =  new O3dObjProps();
	caExplosionPlasmaProps->ObjPropsFloat4::set( MATERIAL, pr2 );
	caExplosionPlasmaProps->ObjPropsFloat4::set( EMISSION, pr2 );


	sObjExplosion = new ObjOdron(  1.0f, 3, GL_TRUE );
	//	sObjExplosion->setObjProps( SpriteExplosion::caExplosionProps );

	sObjExplosionPlasma = new ObjOdron(  1.0f, 3, GL_TRUE );
	//	sObjExplosionPlasma->setObjProps( SpriteExplosion::caExplosionPlasmaProps );


	// Ajouter ODRON EN SHARED (modifier OedObj pour accepter shared)
}

// 2025-11-19 Antigravity: Clean up static resources
void SpriteExplosion::Free()
{
	delete sObjExplosion;
	sObjExplosion = nullptr;
	delete sObjExplosionPlasma;
	sObjExplosionPlasma = nullptr;

	for( auto* ptr : sFreeExploVect ) {
		::operator delete( ptr );
	}
	sFreeExploVect.clear();
}
//----------------------
SpriteExplosion::SpriteExplosion( float pRadius, float pLifeTime, float pDestroy )
:Sprite3d(  pRadius, pLifeTime  )
{
	cRadius = pRadius;
	SpriteFloat::set( SPRITE_DESTROY_POINT, pDestroy);

}
//----------------------
void SpriteExplosion::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{

	float lAvance = (WorldControler::GetTime()-SpriteFloat::get(SPRITE_BIRTHTIME))/SpriteFloat::get(SPRITE_LIFETIME);

	int val;
	if( lAvance < 0.5 )
		val = static_cast<int>((cRadius*2*lAvance )+1.0);
	else
		val = static_cast<int>((cRadius *2 *(1.0-lAvance)) + 1.0);

	Double3 lVal3( val, val, val);
	getTransf().TransfDouble3::set( SCALE, lVal3 );


	//	glutSolidSphere( val + 1.0, 6 + val, 6 + val );

	if( caObj.getPtr() != nullptr )
			caObj->draw( pVProps, pObjProps );
	else
		{
			// GROSS BIDOUILLE pour contourner pb sur compilation avec les props
			// et conserver deux type d'esplosion sans changer les appels

			if( pObjProps == SpriteExplosion::caExplosionProps.getPtr() )
				sObjExplosion->draw( pVProps, pObjProps );
			else
				sObjExplosionPlasma->draw( pVProps, pObjProps );			
		}
}
//***************************
