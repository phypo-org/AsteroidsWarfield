
#ifndef _T3dPrimitiv_h_
#define _T3dPrimitiv_h_




/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dType.h>
#include <T3d/T3dVect3D.h>


/*---------------------------------------------------------------------*/
/*    class DoPoint ...                                                */
/*---------------------------------------------------------------------*/

class DoPoint
{
 public:
	virtual ~DoPoint() {; }
	virtual void doIt( double pX, double pY, double pZ )	{ glVertex3d( pX, pY, pZ );	}
};

/*---------------------------------------------------------------------*/
/*    class StorePoint ...                                             */
/*---------------------------------------------------------------------*/

class StorePoint : public DoPoint 
{
	
 public:
	T3dVect3D & cData;

	StorePoint( T3dVect3D &pVect ):cData( pVect )	{;}
	virtual void doIt( double pX, double pY, double pZ )		{ cData.add( pX, pY, pZ ); }
};

/*---------------------------------------------------------------------*/
/*    class DoTriangle ...                                             */
/*---------------------------------------------------------------------*/

class DoFacette 
{
	public:
	virtual~DoFacette()	{;	}
	virtual void doTriangle( Double3 &v1, Double3 &v2, Double3 &v3 );
	virtual void doSquare( Double3 &v1, Double3 &v2, Double3 &v3,  Double3 &v4 );
	virtual void doTriangleTex( Double3 &v1, Double3 &v2, Double3 &v3, Float2& t1, Float2& t2,  Float2& t3 );
	virtual void doSquareTex( Double3 &v1, Double3 &v2, Double3 &v3,  Double3 &v4, Float2& t1, Float2& t2,  Float2& t3,  Float2& t4);
};

/*---------------------------------------------------------------------*/
/*    class T3dPrimitiv ...                                           */
/*---------------------------------------------------------------------*/


class T3dPrimitiv
{
public:
	enum T3dOrientation {T3d_VERTICAL, T3d_HORIZONTAL};
	enum T3dAxe {AXE_XY,AXE_YX, AXE_XZ, AXE_ZX, AXE_YZ,AXE_ZY};





	static void DrawChar(   float pX, float pY, float pZ, float pSz,  char pChar );
	static void DrawText( T3dOrientation pOrient, float pX, float pY, float pZ, float pSz, const char* pStr, int  pReverse=0  );
	static void DrawText( T3dOrientation pOrient,  Double3& pPt, float pSz, const char* pStr, int  pReverse=0  );

	static void DrawMinus( float pX, float pY, float pZ, float pSz );
	static void DrawX( float pX, float pY, float pZ, float pSz );
	static void DrawY( float pX, float pY, float pZ, float pSz );
	static void DrawZ( float pX, float pY, float pZ, float pSz );

 	static void DrawRepere( float pSz, int pNeg = 1 );
	static void DrawNappe2D( float pSz, int pNb );
	static void DrawGrid( float pSz, int pNb );
	static void DrawNappeT3d( float pSz, int pNb );

	static void DrawPyramid( float pX, float pY, float pZ, int pWidth, int pHeight);

	static void DrawTriangle( Double3 & v1, Double3 & v2,  Double3 & v3 );
	static void DrawSquare( Double3 & v1, Double3 & v2,  Double3 & v3, Double3 & v4);
	static void Subdivide3( DoFacette& pDo, Double3 &v1, Double3 &v2, Double3 &v3, long depth );
	static void Subdivide4( DoFacette & pDo, Double3 &v1, Double3 &v2, Double3 &v3, Double3 &v4, long depth );

	static void DrawTriangleTex( Double3 & v1, Double3 & v2,  Double3 & v3, Float2& t1, Float2& t2,  Float2& t3  );
	static void DrawSquareTex( Double3 & v1, Double3 & v2,  Double3 & v3, Double3 & v4, Float2& t1, Float2& t2,  Float2& t3);
	static void Subdivide3Tex( DoFacette& pDo, Double3 &v1, Double3 &v2, Double3 &v3, Float2& t1, Float2& t2,  Float2& t3, long depth );
	static void Subdivide4Tex( DoFacette& pDo, Double3 &v1, Double3 &v2, Double3 &v3, Double3 &v4, Float2& t1, Float2& t2,  Float2& t3,  Float2& t4, long depth );

	static void Degrade( float  &deb, float  & fin, float pPos, float  & res );
	static void Degrade( Float3 &deb, Float3 & fin, float pPos, Float3 & res );
	static void Degrade( Float4 &deb, Float4 & fin, float pPos, Float4 & res );

	static void MakePoles( Double3* pSrc, int pNb, T3dVect3D& pDest );
	static void InitYama (int pMaille, long pYa1[], long pYa2[]);
	static void MakeBSplinePoint( DoPoint& pDoPoint, int pMaille, Double3* pSrc, int pNb );


	static void BSplineSurf2Poles( T3dVect3D & pSrc, long pCU, long pCV, T3dVect3D & pDest, long &pU, long &pV );
	static void BSplinePoles2Surf( int pUMaille, int pVMaille, T3dVect3D& pSrc, long pCU, long pCV, T3dVect3D& pDest, long &pU, long &pV );

};



#endif

