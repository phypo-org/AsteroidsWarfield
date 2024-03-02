
#ifndef h_Sprite3dObj_h
#define h_Sprite3dObj_h

#include <Sprite3d/Sprite3d.h>

//**************************************
class Sprite3dObj:public Sprite3d
{
protected:
	O3dObj *cObj;
	GLboolean cDeepDestroy;

public:
	Sprite3dObj( O3dObj *pObj=NULL, float pLifeTime = -1.0 );
	virtual ~Sprite3dObj();

	void setO3dObj( O3dObj *pObj )	{ cObj = pObj; }
	O3dObj* getObj() { return cObj; }
	void      setDeepDestroy(GLboolean pFlag )  { cDeepDestroy = pFlag; }
	GLboolean getDeepDestroy( )                 { return cDeepDestroy; }

	virtual float getRadius() { return cObj->getRadius(); }
	virtual GLboolean animate();
	virtual void draw(  O3dViewProps& pVProps, O3dObjProps* pObjProps);
	virtual void drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps )	{		;	}



private:
	static std::vector <Sprite3dObj*> sFreeSpriteVect;
public:
	void* operator new( size_t pSz );
	void  operator delete( void* pSp, size_t pSz);

};
//**************************************


#endif
