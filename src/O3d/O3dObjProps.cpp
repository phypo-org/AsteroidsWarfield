
#include "O3dObjProps.h"

#include "T3d/T3dColor.h"

#include <GL/gl.h>



/*---------------------------------------------------------------------*/
/*    O3dObjProps::O3dObjProps ...                                   */
/*---------------------------------------------------------------------*/

O3dObjProps::O3dObjProps() 
:cTex( NULL ),
cToClose(GL_FALSE)
{
	ObjPropsInt::set( POINT_SIZE, 2 );
	ObjPropsInt::set( LINE_WIDTH, 1 );

	ObjPropsFloat4::set( COLOR_POINT, Green4 );
	ObjPropsFloat4::set( COLOR_LINE, Green4 );
	ObjPropsFloat4::set( COLOR_SKELETON, White4 );
	
	ObjPropsFloat4::set( MATERIAL, Grey4 );

	ObjPropsBool::set( DRAW_OBJ_SOLID, GL_TRUE );
}
/*---------------------------------------------------------------------*/
/*    O3dObjProps::setPointsColor ...                                 */
/*---------------------------------------------------------------------*/

void 
O3dObjProps::setPointsProps()
{
	glColor4fv( ObjPropsFloat4::get( COLOR_POINT ));
	glPointSize( ObjPropsInt::get( POINT_SIZE ) );
}
/*---------------------------------------------------------------------*/
/*    O3dObjProps::setColorSkeleton ...                               */
/*---------------------------------------------------------------------*/

void 
O3dObjProps::setLinesProps()
{
	glColor4fv( ObjPropsFloat4::get( COLOR_SKELETON ));
	glLineWidth( ObjPropsInt::get( LINE_WIDTH) );
}
/*---------------------------------------------------------------------*/
/*    O3dObjProps::setMaterial ...                                    */
/*---------------------------------------------------------------------*/

void 
O3dObjProps::setSurfProps()
{
	if(  ObjPropsFloat4::getFlag( MATERIAL) )
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ObjPropsFloat4::get( MATERIAL )  );
}
/*---------------------------------------------------------------------*/
/*    O3dObjProps::open ...                                           */
/*---------------------------------------------------------------------*/
#include <iostream>
void
O3dObjProps::open()

{
	// Gestion des transparences
	if( (ObjPropsFloat4::getFlag( MATERIAL )
		 && ObjPropsFloat4::get( MATERIAL )[ 3 ] < 1.0 )
		|| ( ObjPropsFloat4::getFlag( EMISSION )
 		 && ObjPropsFloat4::get( EMISSION )[3] < 1.0))
	{
		glEnable( GL_BLEND );
		glDepthMask( GL_FALSE );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );
		cToClose = GL_TRUE;
	}
	else
	{
		cToClose = GL_FALSE;
	}

	if( ObjPropsFloat4::getFlag( MATERIAL ))
	{
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ObjPropsFloat4::get( MATERIAL ) );
	}

	if( ObjPropsFloat4::getFlag( EMISSION ))
	{
		glMaterialfv( GL_FRONT, GL_EMISSION, ObjPropsFloat4::get( EMISSION ) );						
	}
}
/*---------------------------------------------------------------------*/
/*    O3dObjProps::close ...                                          */
/*---------------------------------------------------------------------*/
void
O3dObjProps::close()
{
	if( cToClose == GL_TRUE )
	{
		glDepthMask( GL_TRUE );
		glDisable( GL_BLEND );
		cToClose = GL_FALSE;
	}

		glMaterialfv( GL_FRONT, GL_EMISSION, Black4);			
}
