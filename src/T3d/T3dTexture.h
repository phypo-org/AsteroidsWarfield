
#ifndef _T3dTexture_h
#define _T3dTexture_h


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dType.h>

/*---------------------------------------------------------------------*/
/*    class T3dTexture ...                                             */
/*---------------------------------------------------------------------*/

class T3dTexture
{
protected:
	GLuint cTexName;

public:
	T3dTexture( int pWidth, int pHeight, unsigned char * pBuffer, GLenum pFilter = GL_NEAREST ); //GL_LINEAR );
	T3dTexture( const char* pName, GLenum pFilter = GL_NEAREST ); //GL_LINEAR );
	virtual~T3dTexture()
	{
		glDeleteTextures( 1, &cTexName );
	}

	void setCurrent()
	{
		glBindTexture( GL_TEXTURE_2D, cTexName );
	}
};



#endif
