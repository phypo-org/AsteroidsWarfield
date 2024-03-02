
#ifndef _T3dVect3D_h_
#define _T3dVect3D_h_

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/


#include <T3d/T3dType.h>





/*---------------------------------------------------------------------*/
/*    class T3dVect3D ...                                             */
/*---------------------------------------------------------------------*/
class T3dBox;


class T3dVect3D
{
	protected:
		Double3 *cVectPt;
		long cNbPoint;
		long cSz;
public:
	T3dVect3D(long pSz=0);
	virtual ~T3dVect3D();



public:
	void drop();
	void clear();
	void resize( long pSz );

	long getNbPoint() { return cNbPoint; }
	
	void add( GLdouble pX, GLdouble pY, GLdouble pZ );
	void add( Double3 & pVal3 );
	void add( T3dVect3D & pVect );

//	void set( long pPos, GLdouble pX, GLdouble pY, GLdouble pZ );
	void set( long pPos, Double3& pVal );
//	void ins( long pPos, GLdouble pX, GLdouble pY, GLdouble pZ );
	void get( long pPos, GLdouble *pX, GLdouble *pY, GLdouble *pZ );
	Double3 & get( long pPos );
	Double3 *getAll()	{  return cVectPt;	}
//	void del( long pPos );

	void doGlVertex3dPoint( long pPos );
	void doGlVertex3d();


	void makeMinMaxBox( T3dBox & pMinMax );
};

#endif
