
#include "T3dTexture.h"
#include "T3dLoadImg.h"

/*---------------------------------------------------------------------*/
/*    3DTexture::T3dTexture ...                                        */
/*---------------------------------------------------------------------*/

T3dTexture::T3dTexture( int pWidth, int pHeight, unsigned char * pBuffer, GLenum pFilter )
{
  glGenTextures( 1, &cTexName );              // create a new texture
  glBindTexture( GL_TEXTURE_2D, cTexName ); // active la texture

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pFilter );
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pFilter);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, pWidth, pHeight, 0,
	  GL_RGBA, GL_UNSIGNED_BYTE, pBuffer );
}

T3dTexture::T3dTexture( const char* pName, GLenum pFilter ) //GL_LINEAR );
{
 T3dLoadImage lImg( pName  );

  glGenTextures( 1, &cTexName );              // create a new texture
  glBindTexture( GL_TEXTURE_2D, cTexName ); // active la texture

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pFilter );
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pFilter);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, lImg.width, lImg.height, 0,
	  GL_RGBA, GL_UNSIGNED_BYTE, lImg.makeRGBA() );
}
