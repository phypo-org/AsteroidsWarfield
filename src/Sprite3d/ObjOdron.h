#ifndef h_ObjOdron_h
#define h_ObjOdron_h


#include <O3d/O3dObj.h>


//**************************************
class ObjOdron : public O3dObj
{
	int cDepth;

public:
	ObjOdron( float pRadius, int lDepth, GLboolean pUseList=GL_TRUE )
		:O3dObj( pRadius, pUseList ),
		cDepth( lDepth )
		{
			cUseList = GL_TRUE;
		}
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps );
	virtual float getRadius()	{ return cRadius; 	}
};
//**************************************

#endif
