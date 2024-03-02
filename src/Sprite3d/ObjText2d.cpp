
#include "ObjText2d.h"
#include "T3d/T3dCalcul.h"


//**************************************
void ObjText2d::drawObj( O3dViewProps &pVProps, O3dObjProps *pObjProps )
{
	Text2d::display( 0, 0, 0);
	if( cCadre )
	{
	}
	if( cColorBackground )
	{
		Double3 A( 0, 0, 0 );
		Double3 B( cW, 0, 0 );
		Double3 C( cW, cH, 0 );
		Double3 D( 0, cH, 0 );
		
		Double3 lNorm;
		T3dCalcul::Normal(A,B,C, lNorm );
		
		glColor4fv( *cColorBackground );
		
		glBegin( GL_QUADS );
		glNormal3dv( lNorm);
		glVertex3dv( A);
		glNormal3dv( lNorm);
		glVertex3dv( B);
		glNormal3dv( lNorm);
		glVertex3dv( C);
		glNormal3dv( lNorm);
		glVertex3dv( D);
		glEnd();
	}
}
//**************************************
