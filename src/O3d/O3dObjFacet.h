
#ifndef _O3dObjFacet_h_
#define _O3dObjFacet_h_



/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <O3d/O3dObjPoint.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjFacet ...                                            */
/*---------------------------------------------------------------------*/


class O3dObjFacet : public O3dObjPoint
{
public:
	O3dObjFacet(  long pSz = 0 );

	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);
};



#endif
