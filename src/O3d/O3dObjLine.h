
#ifndef _O3dObjLine_h_
#define _O3dObjLine_h_

#include <O3d/O3dObjPoint.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjLine ...                                            */
/*---------------------------------------------------------------------*/

class O3dObjLine : public O3dObjPoint
{

public:
	O3dObjLine( long pSz = 0 );

	virtual void drawObj(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual const char *getObjTypeStr()		{ return "Brise";		}

};





#endif
