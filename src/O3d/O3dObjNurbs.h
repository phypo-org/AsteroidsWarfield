
#ifndef _O3dObjNurbs_h_
#define _O3dObjNurbs_h_

#include <O3d/O3dObjLine.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjNurbs ...                                            */
/*---------------------------------------------------------------------*/

class O3dObjNurbs : public O3dObjLine
{
	
public:
	O3dObjNurbs( long pSz = 0 );

	virtual void drawObj(O3dViewProps& pVProps, O3dObjProps* pObjProps);


	public:
	static GLUnurbsObj* sTheNurb;
};





#endif
