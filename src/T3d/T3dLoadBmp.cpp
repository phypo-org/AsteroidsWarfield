
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>


#include "T3dLoadImg.h"



#ifdef PC_WINDOWS
#define INT32 long
#define DEBUG if(0)
#else
#define INT32 int
#define DEBUG if(0)
#endif

/* comments on error handling:
   a truncated file is not considered a Major Error.  The file is loaded, the
   rest of the pic is filled with 0's.

   a file with garbage characters in it is an unloadable file.  All allocated
   stuff is tossed, and LoadPBM returns non-zero

   not being able to malloc is a Fatal Error.  The program is aborted. */


#define BI_RGB  0
#define BI_RLE8 1
#define BI_RLE4 2


static long filesize;
static INT32 loadBMP1(FILE *, byte *, INT32, INT32);
static INT32 loadBMP4(FILE *, byte *, INT32, INT32, INT32);
static INT32 loadBMP8(FILE *, byte *, INT32, INT32, INT32);
static unsigned INT32 getshort(FILE *);
static unsigned INT32 getint(FILE *);

/*******************************************/
int LoadBMP(T3dLoadImage& context, const char* pStr)
/*******************************************/
{
  FILE         *fp;
  INT32          i, c, c1, rv;
  unsigned INT32 bfSize, bfOffBits, biSize, biWidth, biHeight, biPlanes;
  unsigned INT32 biBitCount, biCompression, biSizeImage, biXPelsPerMeter;
  unsigned INT32 biYPelsPerMeter, biClrUsed, biClrImportant;
  byte         *pic;
  INT32          os2File;

  /* returns '1' on success */

  pic = NULL;
  fp=fopen(pStr,"r");
  if (!fp) {  std::cerr << "Couldn't open file"; return T3dLoadImage::T3D_IMG_ERROR; }

  fseek(fp, 0L, 2);      /* figure out the file size */
  filesize = ftell(fp);
  fseek(fp, 0L, 0);

  /* read the file type (first two bytes) */
  c = getc(fp);  c1 = getc(fp);
  if (c!='B' || c1!='M') { std::cout << "Not a BM file"; goto ERROR; }

  bfSize = getint(fp);
  getshort(fp);         /* reserved and ignored */
  getshort(fp);
  bfOffBits = getint(fp);

  biSize          = getint(fp);
  if (biSize > 12) { // OS2 BMP file
    os2File = 0;
    biWidth         = getint(fp);
    biHeight        = getint(fp);
    biPlanes        = getshort(fp);
    biBitCount      = getshort(fp);
    biCompression   = getint(fp);
    biSizeImage     = getint(fp);
    biXPelsPerMeter = getint(fp);
    biYPelsPerMeter = getint(fp);
    biClrUsed       = getint(fp);
    biClrImportant  = getint(fp);
  } else { // OS2 BMP file
    os2File = 1;
    biWidth         = getshort(fp);
    biHeight        = getshort(fp);
    biPlanes        = getshort(fp);
    biBitCount      = getshort(fp);
    biCompression   = BI_RGB;
    biSizeImage     = 0; // unused
    biXPelsPerMeter = 0; // unused
    biYPelsPerMeter = 0; // unused
    biClrUsed       = 1 << biBitCount;
    biClrImportant  = 0;
  }

  DEBUG {
    fprintf(stderr,"\nLoadBMP:\tbfSize=%d, bfOffBits=%d\n",bfSize,bfOffBits);
    fprintf(stderr,"\t\tbiSize=%d, biWidth=%d, biHeight=%d, biPlanes=%d\n",
	    biSize, biWidth, biHeight, biPlanes);
    fprintf(stderr,"\t\tbiBitCount=%d, biCompression=%d, biSizeImage=%d\n",
	    biBitCount, biCompression, biSizeImage);
    fprintf(stderr,"\t\tbiX,YPelsPerMeter=%d,%d  biClrUsed=%d, biClrImp=%d\n",
	    biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant);
  }

  if (ferror(fp))
    { std::cout << "Error reading file"; goto ERROR; }

  /* error checking */
  if ((biBitCount!=1 && biBitCount!=4 && biBitCount!=8 && biBitCount!=24) ||
      biPlanes!=1 || biCompression>BI_RLE4) {
    std::cout << "File format error.";
    goto ERROR;
  }

  if (((biBitCount==1 || biBitCount==24) && biCompression != BI_RGB) ||
      (biBitCount==4 && biCompression==BI_RLE8) ||
      (biBitCount==8 && biCompression==BI_RLE4)) {
    std::cout <<"File format error.";
    goto ERROR;
  }

  /* skip ahead to colormap, using biSize */
  if (biSize > 12) {
    c = biSize - 40;    /* 40 bytes read from biSize to biClrImportant */
    for (i=0; i<c; i++) getc(fp);
  }

  /* load up colormap, if any */
  if (biBitCount != 24) {
    INT32 i, cmaplen;

    cmaplen = 1 << biBitCount;
    context.numcols = biClrUsed ? biClrUsed : cmaplen;
    context.bitmap = 0;
    for (i=0; i < cmaplen; i++) {
      context.b[i] = getc(fp);
      context.g[i] = getc(fp);
      context.r[i] = getc(fp);
      if (!os2File) getc(fp);         /* unused */
    }

    if (ferror(fp))
      { std::cout << "Error reading file"; goto ERROR; }
  }

  /* create pic */
  if (biBitCount==24) {
		std::cout << "Can't load 24 bits images" ;
    pic = 0;
  } else {
    pic = new byte[biWidth * biHeight];
    memset(pic, 0, biWidth * biHeight);
    if (!pic) {
			std::cout << "Not enough memory";
      goto ERROR;
    }
  }

  /* load up the image */
  switch(biBitCount) {
   case 1:
    rv = loadBMP1(fp,pic,biWidth,biHeight);
    break;
   case 4:
    rv = loadBMP4(fp,pic,biWidth,biHeight,biCompression);
    break;
   case 8:
    rv = loadBMP8(fp,pic,biWidth,biHeight,biCompression);
    break;
   default:
    rv = 0;
    break;
  }
if (rv) std::cout << "File appears truncated.";
  fclose(fp);

  context.pic = pic;
  context.width = biWidth;
  context.height = biHeight;

  return (pic ? T3dLoadImage::T3D_IMG_BMP : T3dLoadImage::T3D_IMG_ERROR);

 ERROR:
  fclose(fp);
  return T3dLoadImage::T3D_IMG_ERROR;
}


/*******************************************/
static INT32 loadBMP1(FILE *fp, byte *pic, INT32 w, INT32 h)
{
  INT32   i,j,c,bitnum,padw;
  byte *pp;

  c = 0;
  padw = ((w + 31)/32) * 32;  /* 'w', padded to be a multiple of 32 */

  for (i=h-1; i>=0; i--) {
    pp = pic + (i * w);
    for (j=bitnum=0; j<padw; j++,bitnum++) {
      if ((bitnum&7) == 0) { /* read the next byte */
	c = getc(fp);
	bitnum = 0;
      }

      if (j<w) {
	*pp++ = (c & 0x80) ? 1 : 0;
	c <<= 1;
      }
    }
    if (ferror(fp)) break;
  }

  return (ferror(fp));
}



/*******************************************/
static INT32 loadBMP4(FILE *fp, byte *pic, INT32 w, INT32 h, INT32 comp)
{
  INT32   i,j,c,c1,x,y,nybnum,padw,rv;
  byte *pp;


  rv = 0;
  c = c1 = 0;

  if (comp == BI_RGB) {   /* read uncompressed data */
    padw = ((w + 7)/8) * 8; /* 'w' padded to a multiple of 8pix (32 bits) */

    for (i=h-1; i>=0; i--) {
      pp = pic + (i * w);

      for (j=nybnum=0; j<padw; j++,nybnum++) {
	if ((nybnum & 1) == 0) { /* read next byte */
	  c = getc(fp);
	  nybnum = 0;
	}

	if (j<w) {
	  *pp++ = (c & 0xf0) >> 4;
	  c <<= 4;
	}
      }
      if (ferror(fp)) break;
    }
  }

  else if (comp == BI_RLE4) {  /* read RLE4 compressed data */
    x = y = 0;
    pp = pic + x + (h-y-1)*w;

    while (y<h) {
      c = getc(fp);  if (c == EOF) { rv = 1;  break; }

      if (c) {                                   /* encoded mode */
	c1 = getc(fp);
	for (i=0; i<c; i++,x++,pp++)
	  *pp = (i&1) ? (c1 & 0x0f) : ((c1>>4)&0x0f);
      }

      else {    /* c==0x00  :  escape codes */
	c = getc(fp);  if (c == EOF) { rv = 1;  break; }

	if      (c == 0x00) {                    /* end of line */
	  x=0;  y++;  pp = pic + x + (h-y-1)*w;
	}

	else if (c == 0x01) break;               /* end of pic */

	else if (c == 0x02) {                    /* delta */
	  c = getc(fp);  x += c;
	  c = getc(fp);  y += c;
	  pp = pic + x + (h-y-1)*w;
	}

	else {                                   /* absolute mode */
	  for (i=0; i<c; i++, x++, pp++) {
	    if ((i&1) == 0) c1 = getc(fp);
	    *pp = (i&1) ? (c1 & 0x0f) : ((c1>>4)&0x0f);
	  }

	  if (((c&3)==1) || ((c&3)==2)) getc(fp);  /* read pad byte */
	}
      }  /* escape processing */
      if (ferror(fp)) break;
    }  /* while */
  }

  else {
    std::cout << "Unknown BMP compression type";
  }

  if (ferror(fp)) rv = 1;
  return rv;
}



/*******************************************/
static INT32 loadBMP8(FILE *fp, byte *pic, INT32 w, INT32 h, INT32 comp)
{
  INT32   i,j,c,c1,padw,x,y,rv;
  byte *pp;

  rv = 0;

  if (comp == BI_RGB) {   /* read uncompressed data */
    padw = ((w + 3)/4) * 4; /* 'w' padded to a multiple of 4pix (32 bits) */

    for (i=h-1; i>=0; i--) {
      pp = pic + (i * w);

      for (j=0; j<padw; j++) {
	c = getc(fp);  if (c==EOF) rv = 1;
	if (j<w) *pp++ = c;
      }
      if (ferror(fp)) break;
    }
  }

  else if (comp == BI_RLE8) {  /* read RLE8 compressed data */
    x = y = 0;
    pp = pic + x + (h-y-1)*w;

    while (y<h) {
      c = getc(fp);  if (c == EOF) { rv = 1;  break; }

      if (c) {                                   /* encoded mode */
	c1 = getc(fp);
	for (i=0; i<c; i++,x++,pp++) *pp = c1;
      }

      else {    /* c==0x00  :  escape codes */
	c = getc(fp);  if (c == EOF) { rv = 1;  break; }

	if      (c == 0x00) {                    /* end of line */
	  x=0;  y++;  pp = pic + x + (h-y-1)*w;
	}

	else if (c == 0x01) break;               /* end of pic */

	else if (c == 0x02) {                    /* delta */
	  c = getc(fp);  x += c;
	  c = getc(fp);  y += c;
	  pp = pic + x + (h-y-1)*w;
	}

	else {                                   /* absolute mode */
	  for (i=0; i<c; i++, x++, pp++) {
	    c1 = getc(fp);
	    *pp = c1;
	  }

	  if (c & 1) getc(fp);  /* odd length run: read an extra pad byte */
	}
      }  /* escape processing */
      if (ferror(fp)) break;
    }  /* while */
  }

  else {
    std::cout <<  "Unknown BMP compression type";
  }

  if (ferror(fp)) rv = 1;
  return rv;
}

/*******************************************/
static unsigned INT32 getshort(FILE *fp)
{
  INT32 c, c1;
  c = getc(fp);  c1 = getc(fp);
  return ((unsigned INT32) c) + (((unsigned INT32) c1) << 8);
}


/*******************************************/
static unsigned INT32 getint(FILE *fp)
{
  INT32 c, c1, c2, c3;
  c = getc(fp);  c1 = getc(fp);  c2 = getc(fp);  c3 = getc(fp);
  return ((unsigned INT32) c) +
         (((unsigned INT32) c1) << 8) +
	 (((unsigned INT32) c2) << 16) +
	 (((unsigned INT32) c3) << 24);
}



