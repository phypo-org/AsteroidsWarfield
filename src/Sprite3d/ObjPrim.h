#ifndef h_ObjPrim_h
#define h_ObjPrim_h


#include <O3d/O3dObj.h>

//**************************************
enum EnumObjPrim
{
	PrimPoint,
	PrimCube,
	PrimSphere,
	PrimTorus,
	PrimCone,
	PrimTeapot
/*
	PrimDodeca,
	PrimOcta,
	PrimTretra,
	PrimIsoca,
*/
};


class ObjPrim:public O3dObj
{
	protected:
		EnumObjPrim cObjType;

		float cInRadius;
		int cStacks;
		int cSlices;
	
	public:
		ObjPrim( EnumObjPrim pObjType, float pRadius, int  pSlices=1, int pStacks=1, float pInRadius=1.0 )
		:O3dObj( pRadius ),
		cObjType(pObjType),
                 cInRadius( pInRadius ),
		cStacks( pStacks ),
		cSlices( pSlices )
		{
			cUseList = GL_TRUE;
		}
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);
		
};
//**************************************


#endif
