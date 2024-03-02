
#ifndef _O3dObj_h_
#define _O3dObj_h_



/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dBox.h>
#include <T3d/T3dTransf.h>

#include <O3d/O3dViewProps.h>
#include <O3d/O3dObjProps.h>




class O3dSelector;

/*---------------------------------------------------------------------*/
/*    class O3dObj ...                                                */
/*---------------------------------------------------------------------*/

class O3dObj
{
protected:
	static long sId;

	GLboolean cUseList;
	GLuint    cListId;

protected:
	long          cId; // unique id for object
	float   cRadius;          // Pour remplacer les MinMaxBox

	T3dTransf     cTransf;
	T3dBox cBox;
	O3dObjProps * cObjProps; // Proprietes associer a l objet


	GLboolean cSelect;

	virtual void makeList( O3dViewProps & pVProps, O3dObjProps *pObjProps );

public:
	O3dObj(float pRadius=0.0, GLboolean pUseList=GL_FALSE);
	virtual~O3dObj();

	long getObjectId()	{ return cId; 	}

	void setObjProps( O3dObjProps *pObjProps ){ cObjProps = pObjProps; }
	O3dObjProps *getObjProps() {return cObjProps; }


private:
	virtual void drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps ) = 0;
public:
	virtual void draw( O3dViewProps& pVProps, O3dObjProps* pObjProps);
	virtual void drawId( O3dViewProps &pVProps, O3dObjProps *pObjProps );
	virtual void drawForSelectComponents( O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual void drawSelectedComponents( O3dViewProps &pVProps, O3dObjProps *pObjProps)	{ (void)pVProps;(void)pObjProps;}

	virtual float getRadius()	{ return cRadius;	}
	virtual void setRadius( float pRadius ) { cRadius = pRadius; }

	void pushTransf() {cTransf.exec(); }
	void pushTransf( T3dBox &pBox )	{ cTransf.execBox(pBox);	}


	T3dTransf &getTransf() { return cTransf; }
	void setTransf( T3dTransf &pTransf ) { cTransf = pTransf; }

	virtual const char *getObjTypeStr()		{ return "No type";		}
	virtual const char *getInfoStr( char *pStr );

	T3dBox &getMinMaxBox(){ return cBox; }
	virtual GLboolean animate()	{ return GL_TRUE; }
	virtual void setAnimateOn(GLboolean pAnim=GL_TRUE){;}

	virtual void makeMinMaxBox()	{;	}
	virtual O3dObj *findObjectById( long pId )	{ if( pId == cId ) return this; return NULL; 	}
	virtual GLboolean removeObjectById( long pId )    { return GL_FALSE; }


	GLboolean isSelect() {return cSelect; }
	void setSelect( GLboolean pSelect = GL_TRUE ) {cSelect = pSelect; }
	virtual void setSelectComponent( O3dSelector *pSelect = NULL ) {; }

	virtual void deleteAll()	{;	}

    void setUseList( GLboolean pBool=GL_TRUE) { cUseList = pBool; }

	static void GetNormDirection( Double3 & pVect );
	static void GetNormDirectionInv( Double3 & pVect );
	static void GetObjectDistance( O3dObj* p1, O3dObj *p2, Double3 & pDist );
};

/*---------------------------------------------------------------------*/
/*    class O3dObjComponent ...                                        */
/*---------------------------------------------------------------------*/

class O3dObjComponent
{
protected:
	O3dObjComponent()	{;	}
virtual ~O3dObjComponent();
};





#define MkGetPOS()   getTransf().TransfDouble3::get( POS )
#define MkGetANGLE() getTransf().TransfDouble3::get( ANGLE )
#define MkGetSCALE() getTransf().TransfDouble3::get( SCALE )

#define MkSetPOS(A)   getTransf().TransfDouble3::set( POS, A )
#define MkSetANGLE(A) getTransf().TransfDouble3::set( ANGLE, A )
#define MkSetSCALE(A) getTransf().TransfDouble3::set( SCALE, A )


#endif

