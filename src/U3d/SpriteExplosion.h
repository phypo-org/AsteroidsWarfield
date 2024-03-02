#ifndef h_SpriteExplosion_h
#define h_SpriteExplosion_h

#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3d.h>
#include <O3d/O3dObj.h>

//***************************

class SpriteExplosion : public Sprite3d
{
	AutoPtr<O3dObj> caObj;


public:
	SpriteExplosion( float pRadius, float pLifeTime, float pDestroy=0.0 );
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);	

	static AutoPtr<O3dObjProps> caExplosionProps;
	static AutoPtr<O3dObjProps> caExplosionPlasmaProps;



	static void Init();

private:
	static std::vector <SpriteExplosion*> sFreeExploVect;
public:
	void* operator new( size_t pSz );
	void  operator delete( void* pSp,  size_t pSz);
};
//***************************


#endif
