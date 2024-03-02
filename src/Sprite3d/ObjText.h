#ifndef h_ObjText_h
#define h_ObjText_h

#include <O3d/O3dObj.h>


//*******************************************
class ObjText : public O3dObj {

const char*cStr;
		
public:
	ObjText( const char *pStr );
virtual void drawObj(  O3dViewProps& pVProps, O3dObjProps* pObjProps ); 
};
//*******************************************

#endif




