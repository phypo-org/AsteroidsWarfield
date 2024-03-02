
#include "O3dObjFacet.h"
#include "T3d/T3dColor.h"

/*---------------------------------------------------------------------*/
/*    O3dObjFacet::O3dObjFacet ...                                     */
/*---------------------------------------------------------------------*/

O3dObjFacet::O3dObjFacet( long pSz )
	: O3dObjPoint( pSz )
{
}

/*---------------------------------------------------------------------*/
/*    O3dObjFacet::drawObj ...                                         */
/*---------------------------------------------------------------------*/
void
O3dObjFacet::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	glBegin( GL_POLYGON );
	cData.doGlVertex3d();
	glEnd();

	glDisable(GL_LIGHTING);	
	T3dColor::Red();

	glBegin( GL_POINT );
	cData.doGlVertex3d();		
	glEnd();

	glEnable(GL_LIGHTING);	
}
