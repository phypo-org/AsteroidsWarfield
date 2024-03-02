#ifndef h_ObjVect_h
#define h_ObjVect_h

#include <vector>
//#include <Sprite3d/TVectPtr.h>

#include <O3d/O3dObj.h>


typedef std::vector < O3dObj *> VO3dObj;

//typedef TVectPtr<O3dObj*> VO3dObj;
//**************************************
class ObjVect:public O3dObj, public VO3dObj
{
public:
	virtual GLboolean animate();	

	virtual void draw( O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual void drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual void drawId(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual void makeMinMaxBox();
	virtual void deleteAll();
	virtual void add( O3dObj* pObj) { push_back( pObj ); }

};
//**************************************

#endif
