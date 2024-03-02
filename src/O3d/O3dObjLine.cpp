
#include "O3dObjLine.h"
#include "O3dObjProps.h"


#include <T3d/T3dColor.h>

/*---------------------------------------------------------------------*/
/*    O3dObjLine::O3dObjLine ...                                     */
/*---------------------------------------------------------------------*/

O3dObjLine::O3dObjLine( long pSz )
:O3dObjPoint( pSz )
{
}
/*---------------------------------------------------------------------*/
/*    O3dObjLine::drawObj ...                                            */
/*---------------------------------------------------------------------*/

void
O3dObjLine::drawObj(  O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	glDisable( GL_LIGHTING );

	pObjProps->setLinesProps();
	T3dColor::Green();

	glBegin( GL_LINE_STRIP );
	cData.doGlVertex3d();
	glEnd();

	glEnable(GL_LIGHTING);
}
