
#include "T3dLoadImg.h"


#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <iostream>



/* The corresponding magic numbers */

struct ldimagic {
  const char *magicno;
  int fType;
};

static ldimagic mnos[] = {
  {"GIF87a", T3dLoadImage::T3D_IMG_GIF},
  {"GIF89a",T3dLoadImage::T3D_IMG_GIF},
  {"#define",T3dLoadImage::T3D_IMG_XBM},
  {"P1", T3dLoadImage::T3D_IMG_PNM},
  {"P2", T3dLoadImage::T3D_IMG_PNM},
  {"P4", T3dLoadImage::T3D_IMG_PNM},
  {"P5", T3dLoadImage::T3D_IMG_PNM},
  {"\131\246\152\225", T3dLoadImage::T3D_IMG_SUNRAS},
  {"BM", T3dLoadImage::T3D_IMG_BMP},
  {"PIMG", T3dLoadImage::T3D_IMG_PIMG },
  {0, T3dLoadImage::T3D_IMG_UNKNOWN}
};
//*******************************************************************
int T3dLoadImage::GetImageType( const char * filename )
{
  char magicno[8];
  FILE* fp = fopen( filename, "r");
  if (!fp) {
    std::cerr <<  "Can't open file " << filename << "." << std::endl;
    return T3dLoadImage::T3D_IMG_ERROR;
  }
  size_t lSz = fread(magicno,8,1,fp);  
  fclose(fp);
  if( lSz == 0 )
    return T3dLoadImage::T3D_IMG_UNKNOWN;


  int filetype = T3dLoadImage::T3D_IMG_UNKNOWN;
  {
    for (ldimagic *im = mnos; (im->fType != T3dLoadImage::T3D_IMG_UNKNOWN) && (filetype == T3dLoadImage::T3D_IMG_UNKNOWN); im++)
      if (strncmp((char *) magicno, im->magicno, strlen(im->magicno)) == 0)
				filetype = im->fType;
  }

  if (filetype == T3dLoadImage::T3D_IMG_UNKNOWN) {
    std::cerr  <<  filename<< " not in a recognized format." << std::endl;
    return T3dLoadImage::T3D_IMG_UNKNOWN;
  }


  return filetype;
}
//*******************************************************************
int T3dLoadImage::loadImage( const char* pStr)
{
	int filetype =T3dLoadImage::GetImageType( pStr );
	int i;

  switch (filetype) {
   case T3dLoadImage::T3D_IMG_GIF:
		 i = LoadGIF(*this, pStr);
    break;
/*
   case PNM:
		 i = LoadPNM(loader);
    break;

   case XBM:
     i = LoadXBM(loader);
    break;

   case SUNRAS:
	  i = LoadSunRas(loader);
    break;
*/
   case T3dLoadImage::T3D_IMG_BMP:
    i = LoadBMP(*this, pStr);
    break;

   default:
    i = -1;
    break;
  }
  if (!i  && !sysDepend) {
    // Create the grey scale
    for (int j = 0; j < numcols; j++)
      grey[j] = (r[j] + g[j] + b[j])/3;
  }
  return i;
}
//*******************************************************************
T3dLoadImage::T3dLoadImage(const char *name)
:pic( NULL ),
 cRGBA(NULL)
{
  pic = 0;
  deletable = 1;
  sysDepend = 0;
  loadImage( name );
}
// ------------------------------------
T3dLoadImage::~T3dLoadImage()
{
  if (deletable) 
		delete[]pic;

  delete [] cRGBA;
}
// ------------------------------------
void T3dLoadImage::setBits(int w, int h, byte *bits)
{
  width = w;
  height = h;

  pic = new byte[w*h];

  byte *p = pic;
  byte *bb = bits;
  for (int i = 0; i < h; i++, bb++)
    for (int j = 0, k = 0; j < w; j++) {
      if (k == 8) { k = 0; bb++; }
      *p++ = (*bb >> k++) & 1;
    }
  bitmap = 1;
  numcols = 2;
}
// ------------------------------------
void T3dLoadImage::freeze()
{
  deletable = 0;
}
// ------------------------------------
void T3dLoadImage::get(T3dLoadImage& c)
{
  width = c.width;
  height = c.height;
  pic = new byte[width*height];
  memcpy(pic, c.pic, width*height);
  memcpy(r, c.r, sizeof(r));
  memcpy(g, c.g, sizeof(g));
  memcpy(b, c.b, sizeof(b));
  memcpy(grey, c.grey, sizeof(grey));
  numcols = c.numcols;
  bitmap = c.bitmap;
  deletable = c.deletable;
}
// ------------------------------------
int T3dLoadImage::LoadImageError(const char *st)
{
  std::cerr << "Image loading -"  << st << std::endl;
  return -1;
}
// ------------------------------------
unsigned char* T3dLoadImage::makeRGBA()
{

	if( cRGBA == NULL )
	{
		long lMax = width *height;
		cRGBA = new unsigned char[ lMax *4 ];

		unsigned char *tmp = cRGBA;

		for( long i = 0; i < lMax; i++ )
			{
				*tmp++ = r[pic[i]];
				*tmp++ = g[pic[i]];
				*tmp++ = b[ pic[ i ] ];
				*tmp++ = 0xFF;
			}

	}

 return cRGBA;
}

