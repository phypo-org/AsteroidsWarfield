#ifndef h_ObjText2d_h
#define h_ObjText2d_h

#include <O3d/O3dObj.h>
#include <Sprite3d/Text2d.h>


//**************************************
class ObjText2d:public O3dObj, public Text2d
{
	Float4 *cColorBackground;
	GLboolean cCadre;

public:
	ObjText2d( T3dFont *pFont, int pW, int pH, const char *pStr, GLboolean pCadre=GL_FALSE, Float4* pColorBackground=NULL)
	:Text2d( pFont, pW, pH, pStr ),
		cColorBackground( pColorBackground ),
		cCadre( pCadre )
	{
		
	}
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps );
	
};

//**************************************

#endif
