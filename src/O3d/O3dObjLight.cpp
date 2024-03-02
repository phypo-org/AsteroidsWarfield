
#include "O3dObjLight.h"
#include "O3dObjProps.h"
#include "T3d/T3dColor.h"



/*---------------------------------------------------------------------*/
/*    O3dObjLight::O3dObjLight ...                                     */
/*---------------------------------------------------------------------*/

O3dObjLight::O3dObjLight(GLenum pLight)
{	
	cDiffuse[0] = cSpecular[0] = cAmbient[ 0 ] = 0.5;
	cDiffuse[1] = cSpecular[1] = cAmbient[ 1 ] = 0.5;
	cDiffuse[2] = cSpecular[2] = cAmbient[ 2 ] = 0.5;
	cDiffuse[3] = cSpecular[3] = cAmbient[ 3 ] = 0.5;

	cAmbient[0] = 0.2;
	cAmbient[1] = 0.2;
	cAmbient[2] = 0.2;
	cAmbient[3] = 1.0;	
}
/*---------------------------------------------------------------------*/
/*    O3dObjLight::drawObj ...                                         */
/*---------------------------------------------------------------------*/

void
O3dObjLight::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	pObjProps->setPointsProps();

	glDisable( GL_LIGHTING );

	T3dColor::Yellow();
	glPointSize( 5 );

	glBegin( GL_POINTS );
	cData.doGlVertex3d();
	glEnd();
	glEnable( GL_LIGHTING );

	Double3 & lPos = cData.get(0);
	Float3 lF;
	lF[ 0 ] = lPos[ 0 ];
	lF[ 1 ] = lPos[ 1 ];
	lF[ 2 ] = lPos[ 2 ];
	
	glLightfv( cLight, GL_POSITION, lF );
	glLightfv( cLight, GL_AMBIENT, cAmbient);
	glLightfv( cLight, GL_DIFFUSE, cDiffuse);
	glLightfv( cLight, GL_SPECULAR, cSpecular);
}
