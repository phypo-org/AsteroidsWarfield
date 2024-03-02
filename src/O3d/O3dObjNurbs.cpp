
#include "O3dObjNurbs.h"

#include "T3d/T3dType.h"



/*---------------------------------------------------------------------*/
/*    global ...                                                       */
/*---------------------------------------------------------------------*/

GLUnurbsObj* O3dObjNurbs::sTheNurb = NULL;

/*---------------------------------------------------------------------*/
/*    O3dObjNurbs::O3dObjNurbs ...                                     */
/*---------------------------------------------------------------------*/

O3dObjNurbs::O3dObjNurbs( long pSz )
:O3dObjLine( pSz )
{
	if( sTheNurb == NULL )
	{
		sTheNurb = gluNewNurbsRenderer();
   		gluNurbsProperty( sTheNurb, GLU_SAMPLING_TOLERANCE, 25.0);
		gluNurbsProperty( sTheNurb, GLU_DISPLAY_MODE, GLU_FILL );
	}	
}

/* faire un gluDeleteNurbsRenderer qq part */

/*---------------------------------------------------------------------*/
/*    O3dObjNurbs::drawObj ...                                            */
/*---------------------------------------------------------------------*/

void
O3dObjNurbs::drawObj(  O3dViewProps& pVProps,  O3dObjProps* pObjProps )
{

	// Predefined data, just for test
	GLfloat ctlpoints[4][4][3] = { {{-2, 2, 3}, {-1, 2, 0}, {1, 2, 0}, {2, 2, 3}},
                               {{-2, 1, 0}, {-1, 1, 0}, {1, 1, 0}, {2, 1, 0}},
                               {{-2, -1, 0}, {-1, -1, 0}, {1, -1, 0}, {2, -1, 0}},
                               {{-2, -2, 3}, {-1, -2, 0}, {1, -2, 0}, {2, -2, 3}}};
	GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};



    gluBeginSurface( sTheNurb);
	gluNurbsSurface( sTheNurb, 8, knots, 8, knots,
				 4 * 3, 3, &ctlpoints[0][0][0],
	             4, 4, GL_MAP2_VERTEX_3);
	gluEndSurface( sTheNurb );

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for(int i=0;i<4;i++)
      for(int j=0;j<4;j++)
		  glVertex3f( ctlpoints[ i ][ j ][ 0 ], ctlpoints[ i ][ j ][ 1 ], ctlpoints[ i ][ j ][ 2 ] );

    glEnd();
    glEnable(GL_LIGHTING);
}
