
#ifndef _O3dObjBezier_h_
#define _O3dObjBezier_h_

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/


#include <O3d/O3dObjLine.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjBezier ...                                          */
/*---------------------------------------------------------------------*/

class O3dObjBezier : public O3dObjLine
{
public:
	
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);
	virtual const char *getObjTypeStr()		{ return "Courbe Bezier";		}
};

#endif
