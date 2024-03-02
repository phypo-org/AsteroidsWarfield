#include "Text2d.h"
#include <stdio.h>



//***************************************
Text2d::Text2d( T3dFont *pFont, int pW, int pH, const char *pStr )
:cString( pStr ),
cFont(pFont),
cW( pW ),
cH( pH )
{
}
//------------------------------------
void Text2d::display( GLdouble pX, GLdouble pY, GLdouble pZ )
{
	const char *lData = cString.data();
	int lSz = cString.size();

	const char *lLigne = lData;
	int x = 0;
	int y = 0;
	for( int i = 0; i < lSz; i++ )
	{
		if( (lData[ i ] == '\n') || (x >= cW) )
		{
			cFont->displayAt( pX, pY - cFont->getHeight()*y, 50, lLigne, x );
			x = 0;
			y++;
			lLigne = &lData[ i+1 ];
		}
		else	x++;
	}
}
//***************************************
