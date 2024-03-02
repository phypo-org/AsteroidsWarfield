
#ifndef _O3dObjPoint_h_
#define _O3dObjPoint_h_


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <O3d/O3dObj.h>
#include <T3d/T3dVect3D.h>

/*---------------------------------------------------------------------*/
/*    class O3dObjPoint ...                                            */
/*---------------------------------------------------------------------*/

class O3dObjPoint : public O3dObj
{
	protected:
		T3dVect3D cData;

		long cSelectetPoint;

public:
	O3dObjPoint( long pSz = 0 );

	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);
	virtual void drawId( O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual void drawForSelectComponents( O3dViewProps &pVProps, O3dObjProps *pObjProps );
	virtual void drawSelectedComponents( O3dViewProps &pVProps, O3dObjProps *pObjProps);
	virtual void setSelectComponent( O3dSelector* pSelect=NULL );

	virtual void makeMinMaxBox();
	virtual void add( double pX, double pY, double pZ );
	virtual void add( Double3& pVect );
	virtual void add( T3dVect3D &pVect );
	virtual T3dVect3D &get() {return cData; }
};





#endif
