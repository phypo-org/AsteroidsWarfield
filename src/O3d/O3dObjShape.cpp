
#include <T3d/T3dCalcul.h>
#include <T3d/T3dPrimitiv.h>
#include <T3d/T3dColor.h>


#include "O3dObjProps.h"
#include "O3dObjShape.h"


#include <stdio.h>

/*---------------------------------------------------------------------*/
/*    O3dObjShape::O3dObjShape ...                                     */
/*---------------------------------------------------------------------*/

O3dObjShape::O3dObjShape(  long pU, long pV )
:O3dObjPoint( pU*pV ), cU(pU), cV(pV )
{
	cUseList = GL_TRUE;
}
/*---------------------------------------------------------------------*/
/*    O3dObjShape::getVal ...                                         */
/*---------------------------------------------------------------------*/

Double3&  
O3dObjShape::getVal( int pU, int pV )
{
	return  cData.get(  pV *cU + pU );
}
/*-------------------------*/

void O3dObjShape::print()
{
	printf( "\n" );
	for( int u = 0; u < cU; u++ )
	{
		printf(" u:%d", u);
		for( int v = 0; v < cV; v++ )
		{
			Double3 &pt = cData.get( v *cU + u );
			printf( " %f,%f,%f\t", pt[0], pt[1], pt[2] );
		}
	printf( "\n" );
	}
}

/*---------------------------------------------------------------------*/
/*    AX3dShape::getIndidePn ...                                       */
/*---------------------------------------------------------------------*/

inline int O3dObjShape::getIndiceP1( int pu, int pv )
{
	return  pv *cU + pu;
}
inline int O3dObjShape::getIndiceP2( int pu, int pv )
{
	return   pv *cU + pu + 1;
}
inline int O3dObjShape::getIndiceP3( int pu, int pv )
{
	return (pv + 1)*cU + pu + 1 ;
}
inline int O3dObjShape::getIndiceP4( int pu, int pv )
{
	return  (pv + 1)*cU + pu;
}
inline int O3dObjShape::getIndiceQuad(int pu, int pv)
{
	return getIndiceP1( pu, pv );
}
inline int O3dObjShape::getNbQuad()
{
	return cU*cV;
}
/*---------------------------------------------------------------------*/
/*    O3dObjShape::getQuad ...                                        */
/*---------------------------------------------------------------------*/

Double3&
O3dObjShape::getP1( int pU, int pV )
{
	return  cData.get( getIndiceP1( pU, pV ) );
}
Double3&
O3dObjShape::getP2( int pU, int pV )
{
	return  cData.get( getIndiceP2( pU, pV ) );
}
Double3&
O3dObjShape::getP3( int pU, int pV )
{
	return  cData.get( getIndiceP3( pU, pV ) );
}
Double3&
O3dObjShape::getP4( int pU, int pV )
{
	return  cData.get( getIndiceP4( pU, pV ) );
}
/*---------------------------------------------------------------------*/
/*    O3dObjShape::drawObj ...                                           */
/*---------------------------------------------------------------------*/

void
O3dObjShape::drawObj(  O3dViewProps& pVProps, O3dObjProps* pObjProps)
{

	if( pVProps.ViewPropsBool::get(DRAW_POINT))
	{
		glDisable( GL_LIGHTING );
		pObjProps->setPointsProps();

		glBegin( GL_POINTS );
		cData.doGlVertex3d();
		glEnd();

		glEnable( GL_LIGHTING );
	}

	if( pVProps.ViewPropsBool::get( DRAW_LINE ) )
	{
		glDisable( GL_LIGHTING );

		pObjProps->setLinesProps();


		pVProps.beginSelect( cId, SELECT_PATCH );

		for( long v = 0; v < cV - 1; v++ )
		{
			pVProps.beginSelect( cId, v );

			for( long u = 0; u < cU-1; u++ )
			{
				pVProps.beginSelect( cId,  u );

				Double3& p1 = getP1( u, v );
				Double3& p2 = getP2( u, v );
 				Double3& p3 = getP3( u, v );
 				Double3& p4 = getP4( u, v );

				glBegin( GL_LINE_LOOP );

				glVertex3dv( p1 );
				glVertex3dv( p2 );
				glVertex3dv( p3 );
				glVertex3dv( p4 );

				glEnd();

				pVProps.endSelect( cId, u );
			}
			pVProps.endSelect(cId, v );
		}
		glEnable(GL_LIGHTING);
		pVProps.endSelect( cId, SELECT_PATCH );
	} 

		
	if( pVProps.ViewPropsBool::get(DRAW_SURF ) )
	{
		pVProps.beginSelect( cId, SELECT_PATCH );

		if( pVProps.ViewPropsBool::get( DRAW_LINE ) )
		{
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 3.0, 3.0);
		}

		DoFacetteColor lDoFacCol(*this);
		DoFacette lDoFacNorm;

		DoFacette* lDoFac = &lDoFacNorm;
		if( pVProps.ViewPropsBool::get( NORMALIZE_COLORZ ) == GL_TRUE )
		{
			lDoFac =&lDoFacCol; 
		}

		for( long v = 0; v < cV - 1; v++ )
		{
			pVProps.beginSelect( cId, v );

			for( long u = 0; u < cU-1; u++ )
			{
				pVProps.beginSelect( cId,  u );

				Double3 lNorm;

				Double3& p1 = getP1( u, v );
				Double3& p2 = getP2( u, v );
 				Double3& p3 = getP3( u, v );
				Double3& p4 = getP4( u, v );
				
				T3dPrimitiv::Subdivide4( *lDoFac, p1, p2, p3, p4, 2 ); 
				
				pVProps.endSelect( cId,  u );
			}

			pVProps.endSelect( cId,  v );
		}
		glDisable( GL_POLYGON_OFFSET_FILL );

		pVProps.endSelect( cId, SELECT_PATCH);
	}

}
/*---------------------------------------------------------------------*/
/*    O3dObjShape::makeNormal ...                                     */
/*---------------------------------------------------------------------*/
// Attention BUG
//--------------------------------
DoFacetteColor::DoFacetteColor( O3dObj& pObj)
:cObj( pObj )
{		

}
//--------------------------------
void DoFacetteColor::doTriangle( Double3 & v1, Double3 & v2,  Double3 & v3 )
{
	Double3 lNorm;
    T3dCalcul::Normal( v1, v2, v3, lNorm );

	glBegin( GL_POLYGON );
		glNormal3dv( lNorm );
		doColor(v1);
		glVertex3dv( v1 );		
		glNormal3dv( lNorm);
		doColor(v2);
		glVertex3dv( v2 );
		glNormal3dv( lNorm);
		doColor(v3);
		glVertex3dv( v3 );
	glEnd();
}
//--------------------------------
void DoFacetteColor::doSquare( Double3 & v1, Double3 & v2,  Double3 & v3, Double3 & v4)
{
	Double3 lNorm;

	glBegin( GL_POLYGON );
	    T3dCalcul::Normal( v4, v1, v2, lNorm );
		glNormal3dv( lNorm );		
		doColor(v1);
		glVertex3dv( v1 );

	    T3dCalcul::Normal( v1, v2, v3, lNorm );
		glNormal3dv( lNorm);
		doColor(v2);
		glVertex3dv( v2 );

	    T3dCalcul::Normal( v2, v3, v4, lNorm );
		glNormal3dv( lNorm);
		doColor(v3);
		glVertex3dv( v3 );

	    T3dCalcul::Normal( v3, v4, v1, lNorm );
		glNormal3dv( lNorm);
		doColor(v4);
		glVertex3dv( v4 );
	glEnd();
}
//--------------------------------
void DoFacetteColor::doColor( Double3 & v )
{
	// Normalisation 
	double lD = (v[ 1 ]-cObj.getMinMaxBox().getMin()[1]) / (cObj.getMinMaxBox().getMax()[ 1 ]-cObj.getMinMaxBox().getMin()[ 1 ]);

	Float4 lRes;
	if( lD <= 0.5 )
	{
		if( lD <= 0.25 ) 
		{
			// Bleue
			T3dPrimitiv::Degrade( Blue4, Green4, lD*4.0, lRes );
			glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lRes );
		}
		else
		{
			// Vert
			T3dPrimitiv::Degrade( Green4, Yellow4, (lD-0.25)*4.0, lRes );
			glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lRes );
		}
	}
	else
	{
		if( lD <= 0.75 )
		{
			// Jaune
			T3dPrimitiv::Degrade( Yellow4, Red4, (lD-0.50)*4.0, lRes );
			glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lRes );

		}
		else
		{
			//	Rouge
			T3dPrimitiv::Degrade( Red4, Blue4, (lD-0.75)*4.0, lRes );
			glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lRes );
		}
	}
}

