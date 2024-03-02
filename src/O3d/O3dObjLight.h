
#ifndef _O3dObjLight_h_
#define _O3dObjLight_h_

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/
#include <O3d/O3dObjPoint.h>


/*---------------------------------------------------------------------*/
/*    class O3dObjLight ...                                            */
/*---------------------------------------------------------------------*/
class O3dObjLight : public O3dObjPoint
{
public:
	Float4 cAmbient;
	Float4 cDiffuse;
	Float4 cSpecular;

	GLenum   cLight;
	

public:
	O3dObjLight( GLenum pLight );
	virtual void drawObj(  O3dViewProps& pVProps, O3dObjProps* pObjProps);

	virtual void enable()	{ glEnable( cLight );	}
	virtual void disable()  { glDisable( cLight );	}
};


#endif
