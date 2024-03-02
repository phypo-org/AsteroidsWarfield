
#include "O3dObjBezier.h"

#include "O3dObjProps.h"

/*---------------------------------------------------------------------*/
/*    O3dObjBezier::drawObj ...                                          */
/*---------------------------------------------------------------------*/

void
O3dObjBezier::drawObj(O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	
	glDisable( GL_LIGHTING );
	pObjProps->setLinesProps();


	if( pVProps.ViewPropsBool::get( DRAW_POINT) )
	{
		glBegin( GL_POINTS );
		cData.doGlVertex3d();
		glEnd();
	}

	glEnable( GL_MAP1_VERTEX_3 );
	glMap1d( GL_MAP1_VERTEX_3, 0.0, 1.0, 3, cData.getNbPoint(), (double*)cData.getAll() );

	glBegin(  GL_LINE_STRIP );
	for( int i = 0; i <= 30; i++ )
		glEvalCoord1f( (GLfloat)i/30.0 );
	glEnd();

	glEnable(GL_LIGHTING);
}
