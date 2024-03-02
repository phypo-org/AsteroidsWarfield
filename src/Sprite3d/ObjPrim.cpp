#include "ObjPrim.h"

#include <FL/glut.H>
#include "Utils3d.h"

#include <iostream>

//**************************************

void ObjPrim::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
//	cout << "ObjPrim::drawObj" << endl;

	GLboolean lSkeleton = pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON);
	GLboolean lSolid = pObjProps->ObjPropsBool::get( DRAW_OBJ_SKELETON );

	switch( cObjType )
	{
		case PrimPoint:
			glPointSize( cRadius );
			glBegin( GL_POINTS );
			glVertex3f( 0.0, 0.0, 0.0 );
			glEnd();
		break;

		case PrimSphere:
			if( lSkeleton )
				glutWireSphere( cRadius, cSlices, cStacks );
			if(lSolid)
				glutSolidSphere( cRadius, cSlices, cStacks );
		break;

		case PrimTorus:
			if( lSkeleton )
				glutWireTorus( cInRadius, cRadius, cSlices, cStacks );
			if(lSolid)
				glutSolidTorus( cInRadius, cRadius, cSlices, cStacks );
		break;

		case PrimCone:
			if( lSkeleton )
				glutWireCone( cRadius, cInRadius, cSlices, cStacks );
			if(lSolid)
				glutSolidCone( cInRadius, cRadius, cSlices, cStacks );
		break;

		case PrimCube:
			if( lSkeleton )
				glutWireCube(cRadius );
			if(lSolid)
				glutSolidCube(cRadius );
			break;

		case PrimTeapot :
			if( lSkeleton )
				glutWireTeapot( cRadius );
			if(lSolid)
				glutSolidTeapot( cRadius );
		break;
/*
		case PrimDodeca:
			if( lSkeleton )
			if(lSolid)
		break;



		case PrimOcta:
			if( lSkeleton )
			if(lSolid)
		break;

		case PrimTretra:
			if( lSkeleton )
			if(lSolid)
		break;
		case
			if( lSkeleton )
			if(lSolid)
		break;
		case
			if( lSkeleton )
			if(lSolid)
		break;

		case PrimIsoca :
			if( lSkeleton )
			if(lSolid)
		break;
*/

		default:;
	}
}


//**************************************
