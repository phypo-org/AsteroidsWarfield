#ifndef _O3dObjPrim_h
#define _O3dObjPrim_h


#include <O3d/O3dObj.h>


/*---------------------------------------------------------------------*/
/*    class O3dObjPrim ...                                             */
/*---------------------------------------------------------------------*/

class O3dObjPrim : public O3dObj
{
	public:

	enum EnumObjPrim
	{
	PrimPoint,
	PrimCube,
	PrimSphere,
	PrimTorus,
	PrimCone,
	PrimCylinder,
	PrimDisk,
	PrimPartialDisk,
	PrimTeapot
	};


	protected:

	EnumObjPrim cObjType;


	float cInRadius;
	int cSlices;
	int cStacks;
	float cTop;
	float cEnd;


	public:
		O3dObjPrim( EnumObjPrim pObjType, float pRadius, int  pSlices=1, int pStacks=1, float pInRadius=1.0, float pTop=0.0, float pEnd=0.0 )
		:O3dObj( pRadius ),
		cObjType(pObjType),
		cInRadius( pInRadius ),
        cSlices( pSlices ),
		cStacks( pStacks ),
		cTop( pTop ),
		cEnd( pEnd )
		{
			cUseList = GL_TRUE;
		}
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);

};


#endif
