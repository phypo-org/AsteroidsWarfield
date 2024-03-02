#include "T3d/T3dBox.h"

#include <stdio.h>

/*---------------------------------------------------------------------*/
/*    T3dBox::T3dBox ...                                 */
/*---------------------------------------------------------------------*/

T3dBox::T3dBox()
{
	for( int i = 0; i < 3; i++ )
	{
		cMin[ i ] = 1e10;
		cMax[ i ] = -1e10;
	}
}

/*---------------------------------------------------------------------*/
/*    T3dBox::getCenter ...                                     */
/*---------------------------------------------------------------------*/

void 
T3dBox::getCenter( Double3& pD3 )
{
	for( int i = 0; i < 3; i++ )
		pD3[i] = (cMin[i] + cMax[i]) * 0.5;
}
//---------------------------
Double3 
T3dBox::size()
{
	return Double3( (cMax[0] -cMin[0]),
									(cMax[1] -cMin[1]),
									(cMax[2] -cMin[2])
									);
}
//---------------------------
Double3 
T3dBox::center()
{
	return Double3( (cMin[0] + cMax[0])* 0.5,
									(cMin[1] + cMax[1])* 0.5,
									(cMin[2] + cMax[2])* 0.5);
}
/*---------------------------------------------------------------------*/
/*    T3dObj::getInfoStr ...                                          */
/*---------------------------------------------------------------------*/

char*
T3dBox::getInfoStr( char* pStr)
{
	int lNb = sprintf( pStr, "(%f, %f, %f : %f, %f, %f )",
		cMin[ 0 ], cMin[ 1 ], cMin[ 2 ], cMax[ 0 ], cMax[ 1 ], cMax[ 2 ] );

	return &pStr[lNb];
}
