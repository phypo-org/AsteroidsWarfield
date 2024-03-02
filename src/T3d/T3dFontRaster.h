
#ifndef _T3dFontRaster_h
#define _T3dFontRaster_h



/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dFont.h>



/*---------------------------------------------------------------------*/
/*    class T3dFontRaster ...                                          */
/*---------------------------------------------------------------------*/

class T3dFontRaster : public T3dFont
{
	GLuint cFontOffset;
	int cBegin;
	int cEnd;
	int cWidth;
	int cHeight;

public:

	T3dFontRaster();
	T3dFontRaster( GLubyte  pRaster[][13], int pW, int pH, int pBegin, int pEnd );

protected:
	virtual void init( GLubyte  pRaster[][13], int pW, int pH, int pBegin, int pEnd );

public:
	virtual~T3dFontRaster();

	virtual void display(  char c );
	virtual void display(  const char* pStr, int pSz=-1 );
	virtual void displayAt( GLdouble pX, GLdouble pY, GLdouble pZ, const char *pStr, int pSz=-1 );

	virtual int getTextWidth( const char *str, long ln = -1 )
	{
		if( ln == -1 ) ln = strlen(str);
		return ln*getMaxWidth();
	}
	virtual int getMaxWidth(  )	{ return cWidth+2; 	}
	virtual int getHeight( ) 	{ return cHeight; 	}
};



#endif

