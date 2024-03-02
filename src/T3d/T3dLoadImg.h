#ifndef _H_T3dLoadImg
#define _H_T3dLoadImg


typedef unsigned char byte;

// *******************************************

struct T3dLoadImage {

public:
	enum T3D_IMG_TYPE{ T3D_IMG_ERROR=-1, T3D_IMG_UNKNOWN=0, T3D_IMG_GIF, T3D_IMG_PM, T3D_IMG_PNM, T3D_IMG_XBM, T3D_IMG_SUNRAS, T3D_IMG_UTAHRLE, T3D_IMG_XPM, T3D_IMG_BMP, T3D_IMG_PIMG };

  byte *pic;				// picture data
  int width, height;			// width, height
  byte  r[256], g[256], b[256];		// red, green, blue values
  byte grey[256];			// grey value
  int numcols;				// number of colors
  char bitmap;				// is it a binary image? If so, we may want to
					// modify color map according to window
					// foreground/background...
  char deletable;			// do we have to dispose of pic ?
  char sysDepend; // system dependant format in pic ?

  byte* cRGBA;
  
  // METHODS
  T3dLoadImage(const  char *name);
  ~T3dLoadImage();
  void setBits(int w, int h, byte *bits); // set bitmap (XBM format)
  void freeze();			// set undeletable
  void get(T3dLoadImage& c);		// copy everything but name

 int loadImage( const char *pStr );
 unsigned char* makeRGBA();

static int GetImageType( const char * filename );
static int LoadImageError( const char *st);
};

// *******************************************


extern int LoadBMP(T3dLoadImage& loader, const char* pStr );
extern int LoadGIF(T3dLoadImage& context, const char* pStr);


#endif /* of multiple inclusion */
