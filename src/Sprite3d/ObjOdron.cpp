#include "ObjOdron.h"
#include "O3d/O3dObjProps.h"

#include "Utils3d.h"

#include <iostream>

#define T       1.73205080756887729

//**************************************

void ObjOdron::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	Float3 lData[ 4 ];

	lData[0][0]=T;
	lData[0][1]=T;
	lData[0][2]=T;

	lData[1][0]=T;
	lData[1][1]=-T;
	lData[1][ 2 ] = -T;

	lData[2][0]=-T;
	lData[2][1]=T;
	lData[2][2]=-T;

	lData[3][0]=-T;
	lData[3][1]=-T;
	lData[3][2]=T;


	Float2 lTexa[ 3 ];
	lTexa[ 0 ][ 0 ] = 0.5; 
	lTexa[ 0 ][ 1 ] = 1.0; //0.0

	lTexa[ 1 ][ 0 ] = 0.0;
	lTexa[ 1 ][ 1 ] = 0.0; //  1.0;

	lTexa[ 2 ][ 0 ] = 1.0;
	lTexa[ 2 ][ 1 ] = 0.0; //1.0


	GLubyte Texture[ 16 ] =
	{
	0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0
	};

	if( pObjProps && pObjProps->getTexture() != NULL  )
	{
		pObjProps->getTexture()->setCurrent();

	glEnable( GL_TEXTURE_2D );
	Utils3d::Subdivide3Tex( lData[0], lData[1], lData[3], lTexa[0], lTexa[1], lTexa[2], cDepth, cRadius );
    Utils3d::Subdivide3Tex( lData[2], lData[1], lData[0], lTexa[0], lTexa[1], lTexa[2], cDepth, cRadius );
    Utils3d::Subdivide3Tex( lData[3], lData[2], lData[0], lTexa[0], lTexa[1], lTexa[2], cDepth, cRadius );
    Utils3d::Subdivide3Tex( lData[1], lData[2], lData[3], lTexa[0], lTexa[1], lTexa[2], cDepth, cRadius );
	glDisable( GL_TEXTURE_2D );

	}
	else
	{
	Utils3d::Subdivide3( lData[0], lData[1], lData[3], cDepth, cRadius );
    Utils3d::Subdivide3( lData[2], lData[1], lData[0], cDepth, cRadius );
    Utils3d::Subdivide3( lData[3], lData[2], lData[0], cDepth, cRadius );
    Utils3d::Subdivide3( lData[1], lData[2], lData[3], cDepth, cRadius );
	}
}
//**************************************
