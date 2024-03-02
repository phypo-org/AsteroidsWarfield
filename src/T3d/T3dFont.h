
#ifndef _T3dFont_h
#define _T3dFont_h

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dType.h>



/*---------------------------------------------------------------------*/
/*    T3dFont ...                                                      */
/*---------------------------------------------------------------------*/

class T3dFont
{
public:

	T3dFont()
	{
		if( DefaultFont == NULL )
			Init();
 	}
	virtual~T3dFont() {; }

	virtual void display(  char c )=0;
	virtual void display(  const char* pStr, int pSz=-1 )=0;
	virtual void displayAt( GLdouble pX, GLdouble pY, GLdouble pZ, const char *pStr, int pSz=-1 )=0;
	virtual void displayAtPoint( Double3 & pPos, const char *pStr, int pSz=-1 )
	{
		displayAt( pPos[0], pPos[1], pPos[2], pStr, pSz );
	}

	virtual int getTextWidth( const char *str, long ln=-1 )=0;
	virtual int getMaxWidth( void )=0;
	virtual int getHeight( void ) = 0;


static T3dFont *DefaultFont;
static void Init();
};
#endif

