
#ifndef _O3dObjBSpline_h_
#define _O3dObjBSpline_h_


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <O3d/O3dObjLine.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjBSpline ...                                          */
/*---------------------------------------------------------------------*/

class O3dObjBSpline : public O3dObjLine
{
	T3dVect3D cPole;

public:	
	virtual void drawObj(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	void makePoles();
	virtual const char *getObjTypeStr()		{ return "Courbe BSpline";		}

};

#endif
