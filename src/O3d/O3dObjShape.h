
#ifndef _O3dObjShape_h_
#define _O3dObjShape_h_



#include <T3d/T3dPrimitiv.h>

#include <O3d/O3dObjPoint.h>

/*---------------------------------------------------------------------*/
/*    class DoFacetteColor ...                                         */
/*---------------------------------------------------------------------*/
 
class DoFacetteColor: public DoFacette
{
	O3dObj & cObj;
public:
	DoFacetteColor( O3dObj & pObj );

	virtual void doTriangle( Double3 &v1, Double3 &v2, Double3 &v3 );
	virtual void doSquare( Double3 &v1, Double3 &v2, Double3 &v3, Double3 &v4 );

	void doColor( Double3& v );
};

/*---------------------------------------------------------------------*/
/*    class O3dObjShape ...                                           */
/*---------------------------------------------------------------------*/

class O3dObjShape:public O3dObjPoint
{
	protected:
		long cU;
		long cV;

public:
	O3dObjShape(  long pU=0, long pV=0 );
	void setUV( long pU, long pV )
	{
		cU = pU;
		cV = pV;
	}
	virtual void drawObj( O3dViewProps&, O3dObjProps* pObjProps );
	virtual const char *getObjTypeStr()		{ return "Surf Shape";		}

	long getNbU()	{ return cU;	}
	long getNbV() {return cV; }
	Double3& getVal( int pU, int pV );

inline	int getIndiceP1( int pU, int pV );
inline	int getIndiceP2( int pU, int pV );
inline	int getIndiceP3( int pU, int pV );
inline	int getIndiceP4( int pU, int pV );
inline  int getIndiceQuad( int pu, int pv );
inline  int getNbQuad();
Double3& getP1( int pU, int pV );
Double3& getP2( int pU, int pV );
Double3& getP3( int pU, int pV );
Double3 & getP4( int pU, int pV );

void print();


};


#endif
