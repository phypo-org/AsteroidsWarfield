#include "Sprite3dObj.h"

#include <FL/glut.H>

std::vector<Sprite3dObj*> Sprite3dObj::sFreeSpriteVect;


//**************************************
Sprite3dObj::Sprite3dObj(  O3dObj *pObj, float pLifeTime  )
:Sprite3d( (pObj == NULL ? 0 : pObj->getRadius()), pLifeTime),
 cObj( pObj ),
 cDeepDestroy(GL_FALSE)
{

}
//-----------------------------------
Sprite3dObj::~Sprite3dObj()
{
	if( cDeepDestroy )
	{
		cObj->deleteAll();
		delete cObj;
	}
}
//-----------------------------------
GLboolean Sprite3dObj::animate()
{
	if( cObj != NULL )
		cObj->animate();

	return Sprite3d::animate();
}
//-----------------------------------
void Sprite3dObj::draw(  O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	if( cObj == NULL )
		return;

	// Pas de glPushMatrix/glPopMatrix car l objet et seul dans le
	// Sprite et le Sprite fait glPushMatrix/glPopMatrix !

	cObj->pushTransf();

	if( cObj->getObjProps() )
		{
			cObj->getObjProps()->open();
			cObj->draw( pVProps, cObj->getObjProps() );
	//		glutWireSphere( cRadius, 8,  8);

			cObj->getObjProps()->close();
		}
	else 
		{
			cObj->draw( pVProps, pObjProps );
	//		glutWireSphere( cRadius, 8,  8);
		}
}
//----------------------------------
// Il faudrait mieux mettre une fonction alloc et free propre au Sprite32d se serait moins compliqué
// que ce bazar avec new et delete, en plus je ne suis pas sure que l'on gagne du temps !

void* 
Sprite3dObj::operator new( size_t pSz )
{
	//	std::cout << "Sprite3dObj::operator new " << pSz << " sz:" << sFreeSpriteVect.size() << std::endl;
	

	if( pSz == sizeof( Sprite3dObj) && sFreeSpriteVect.size() > 0 )
		{
			//			std::cout << "*** Sprite3dObj::operator new with vector "  << pSz << std::endl;

			Sprite3dObj* lTmp = sFreeSpriteVect.back();
			//		std::cout << "Sprite3dObj::operator pop : "  <<  lTmp<< std::endl;
			sFreeSpriteVect.pop_back();
			return lTmp;
		}

	//	std::cout << "Sprite3dObj::operator nex general"  << std::endl;


	
	return ::operator new( pSz );
}
//----------------------------------
void 
Sprite3dObj::operator delete( void* pSp, size_t pSz) 
 {
	//	std::cout << "Sprite3dObj::operator delete " << pSz << std::endl;

	if( pSp == nullptr ) return;

	if( pSz != sizeof( Sprite3dObj) )
		{
			::operator delete( pSp );
			return;
		}

	//	std::cout << "*** Sprite3dObj::operator delete " << pSz << " sz:" << sFreeSpriteVect.size() << std::endl;
	sFreeSpriteVect.push_back( (Sprite3dObj*)pSp );
}
	
/*
	std::cout << "Sprite3dObj::operator delete " << pSz << std::endl;

	sFreeSpriteVect.push_back( (Sprite3dObj*)pSp );

		try{
			Sprite3dObj* lSp3d =  reinterpret_cast<Sprite3dObj*>( pSp );

		if( typeid(*lSp3d) == typeid(Sprite3dObj)	){
				sFreeSpriteVect.push_back( (Sprite3dObj*)pSp );
				return;
		}
	}
	catch( ... ) {;}

	::operator delete( pSp );
}
*/

//**************************************
