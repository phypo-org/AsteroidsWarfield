
#ifndef _O3dObjBSplineSurf_h_
#define _O3dObjBSplineSurf_h_


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <O3d/O3dObjShape.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjBSplineSurf ...                                          */
/*---------------------------------------------------------------------*/

class O3dObjBSplineSurf : public O3dObjShape
{
	long cPU, cPV;
	T3dVect3D cPoles;
	int cUMemMaille;
	int cVMemMaille;

public:
	O3dObjBSplineSurf( );
	virtual void drawObj(  O3dViewProps &pVProps, O3dObjProps *pObjProps );
	virtual void drawId(O3dViewProps& pVProps, O3dObjProps* pObjProps);

	void makePoles(O3dObjShape& pShape);
	virtual const char *getObjTypeStr()		{ return "Surf BSpline";		}
};

#endif
