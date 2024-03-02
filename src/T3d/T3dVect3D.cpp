#include "T3dVect3D.h"

#include <stdlib.h>
#include <stdio.h>


#include "T3dBox.h"

/*---------------------------------------------------------------------*/
/*    T3dVect3D::T3dVect3D ...                                       */
/*---------------------------------------------------------------------*/

T3dVect3D::T3dVect3D(long pSz)
	:cVectPt( NULL ), cNbPoint( 0 ), cSz(0)
{
	if( pSz )
		resize( pSz );
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::~T3dVect3D ...                                      */
/*---------------------------------------------------------------------*/

T3dVect3D::~T3dVect3D()
{
	drop();
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::drop ...                                             */
/*---------------------------------------------------------------------*/

void
T3dVect3D::drop()
{
	if( cVectPt )
		delete[] cVectPt;

	cVectPt =  NULL;
	cSz = 0;
	cNbPoint = 0;	
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::clear ...                                            */
/*---------------------------------------------------------------------*/

void
T3dVect3D::clear()
{
	cNbPoint =0;
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::resize ...                                           */
/*---------------------------------------------------------------------*/

void
T3dVect3D::resize( long pNb )
{
	if( pNb < cSz )
		return;

	if( cSz == 0 )
	{
//		cVectPt = (Double3*)malloc(  sizeof(Double3)*pNb );
	    cVectPt = new Double3[pNb];
		cSz = pNb;
	}
	else
	{
//		cVectPt = (Double3*)realloc( cVectPt, sizeof(Double3)*pNb );
 	    Double3 *lTmp = new Double3[ pNb ];
		for( int i = 0; i < cNbPoint; i++ )
			lTmp[ i ] = cVectPt[ i ];

		delete[] cVectPt;
		cVectPt = lTmp;
		cSz = pNb;
	}
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::add ...                                              */
/*---------------------------------------------------------------------*/

void
T3dVect3D::add( GLdouble pX, GLdouble pY, GLdouble pZ )
{	
	resize( cNbPoint + 1 );
	cVectPt[ cNbPoint ][0] = pX;
	cVectPt[ cNbPoint ][1] = pY;
	cVectPt[ cNbPoint ][2] = pZ;
	cNbPoint++;
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::add ...                                              */
/*---------------------------------------------------------------------*/

void
T3dVect3D::add( Double3 & pVal )
{
	resize( cNbPoint + 1 );

	cVectPt[ cNbPoint ][ 0 ] = pVal[ 0 ];
	cVectPt[ cNbPoint ][ 1 ] = pVal[ 1 ];
	cVectPt[ cNbPoint ][ 2 ] = pVal[ 2 ];

	cNbPoint++;
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::add ...                                              */
/*---------------------------------------------------------------------*/

void
T3dVect3D::add( T3dVect3D & pVect )
{
	resize( cNbPoint+pVect.cNbPoint  );
	for( int i = 0; i < pVect.getNbPoint(); i++ )
	{
		add( pVect.get(i) );
	}
}

/*---------------------------------------------------------------------*/
/*    T3dVect3D::set ...                                              */
/*---------------------------------------------------------------------*/

void 
T3dVect3D::set( long pPos, Double3 & pVal )
{
	resize( pPos + 1 );

	if( cNbPoint < pPos + 1 )
		cNbPoint = pPos+1;

	cVectPt[ pPos ][ 0 ] = pVal[ 0 ];
	cVectPt[ pPos ][ 1 ] = pVal[ 1 ];
	cVectPt[ pPos ][ 2 ] = pVal[ 2 ];

}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::get ...                                              */
/*---------------------------------------------------------------------*/

void
T3dVect3D::get( long pPos, GLdouble *pX, GLdouble *pY, GLdouble *pZ )
{
	if( pPos>= cNbPoint || pPos >= cSz )
	{
		printf( "Error T3dVect3D::get pos:%ld max:%ld Sz:%ld\n", pPos, cNbPoint, cSz);
	}

	*pX = cVectPt[ pPos ][0];
	*pY = cVectPt[ pPos ][1];
	*pZ = cVectPt[ pPos ][2];
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::get ...                                              */
/*---------------------------------------------------------------------*/

Double3&
T3dVect3D::get( long pPos )
{
	return cVectPt[pPos];
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D:doGlVertex3d ...                                      */
/*---------------------------------------------------------------------*/

void
T3dVect3D::doGlVertex3dPoint( long pPos )
{
	glVertex3dv( cVectPt[pPos] );
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D:doGlVertex3d ...                                      */
/*---------------------------------------------------------------------*/

void
T3dVect3D::doGlVertex3d()
{
	for( long i = 0; i < cNbPoint; i++ )
	{
		glVertex3dv( cVectPt[ i ] ); 
	}
}
/*---------------------------------------------------------------------*/
/*    T3dVect3D::makeMinMaxBox ...                                    */
/*---------------------------------------------------------------------*/

void
T3dVect3D::makeMinMaxBox( T3dBox& pMinMax )
{
	for( long i = 0; i < cNbPoint; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			if( pMinMax.cMin[ j ]>cVectPt[ i ][ j ] )
				pMinMax.cMin[ j ] = cVectPt[ i ][ j ];
			if( pMinMax.cMax[ j ]<cVectPt[ i ][ j ] )
				pMinMax.cMax[ j ] = cVectPt[ i ][ j ];
		}
	}
}
