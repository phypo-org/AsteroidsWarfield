
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>


#include "T3dLoadImg.h"

/*
 * xvgif.c  -  GIF loading code for 'xv'.  Based strongly on...
 *
 * gif2ras.c - Converts from a Compuserve GIF (tm) image to a Sun Raster image.
 *
 * Copyright (c) 1988, 1989 by Patrick J. Naughton
 *
 * Author: Patrick J. Naughton
 * naughton@wind.sun.com
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 *
 */

/*
 * Copyright 1989, 1990, 1991, 1992 by John Bradley and
 *                       The University of Pennsylvania
 *
 * Permission to use, copy, and distribute for non-commercial purposes,
 * is hereby granted without fee, providing that the above copyright
 * notice appear in all copies and that both the copyright notice and this
 * permission notice appear in supporting documentation.
 *
 * The software may be modified for your own purposes, but modified versions
 * may not be distributed.
 *
 * This software is provided "as is" without any expressed or implied warranty.
 *
 * The author may be contacted via:
 *    US Mail:   John Bradley
 *               GRASP Lab, Room 301C
 *               3401 Walnut St.
 *               Philadelphia, PA  19104
 *
 *    Phone:     (215) 898-8813
 *    EMail:     bradley@cis.upenn.edu
 */


#include <stdio.h>
#include <string.h>
#include <iostream>

/*************/

#ifdef PC_WINDOWS
#define INT32 long
#define DEBUG if(0)
#else
#define INT32 int
#define DEBUG if(0)
#endif

typedef int boolean;

#define NEXTBYTE (*ptr++)
#define EXTENSION     0x21
#define IMAGESEP      0x2c
#define TRAILER       0x3b
#define INTERLACEMASK 0x40
#define COLORMAPMASK  0x80

static
FILE *fp;

static
INT32 BitOffset = 0,		// Bit Offset of next code
      XC = 0, YC = 0,		// Output X and Y coords of current pixel
      Pass = 0,			// Used by output routine if interlaced pic
      OutCount = 0,		// Decompressor output 'stack count'
      RWidth, RHeight,		// screen dimensions
      Width, Height,		// image dimensions
      LeftOfs, TopOfs,		// image offset
      BitsPerPixel,		// Bits per pixel, read from GIF header
      ColorMapSize,		// number of colors
      Background,		// background color
      CodeSize,			// Code size, read from GIF header
      InitCodeSize,		// Starting code size, used during Clear
      Code,			// Value returned by ReadCode
      MaxCode,			// limiting value for current code size
      ClearCode,		// GIF clear code
      EOFCode,			// GIF end-of-information code
      CurCode, OldCode, InCode,	// Decompressor variables
      FirstFree,		// First free code, generated per GIF spec
      FreeCode,			// Decompressor,next free slot in hash table
      FinChar,			// Decompressor variable
      BitMask,			// AND mask for data size
      ReadMask,			// Code AND mask for current code size
      Misc;                     // miscellaneous bits (interlace, local cmap)

static
boolean Interlace, HasColormap;

static byte *RawGIF;			// The heap array to hold it, raw
static byte *Raster;			// The raster data stream, unblocked

    /* The hash table used by the decompressor */
static INT32 Prefix[4096];
static INT32 Suffix[4096];

    /* An output array used by the decompressor */
static INT32 OutCode[4097];

static int   gif89 = 0;
static const char *id87 = "GIF87a";
static const char *id89 = "GIF89a";

static INT32 EGApalette[16][3] = {
  {0,0,0},       {0,0,128},     {0,128,0},     {0,128,128},
  {128,0,0},     {128,0,128},   {128,128,0},   {200,200,200},
  {100,100,100}, {100,100,255}, {100,255,100}, {100,255,255},
  {255,100,100}, {255,100,255}, {255,255,100}, {255,255,255} };

static INT32 ReadCode();
static void DoInterlace(T3dLoadImage&, byte);

static long filesize;

/*****************************/
int LoadGIF(T3dLoadImage& context, const char* lName)
/*****************************/
{
   byte ch, ch1;
   byte *ptr, *ptr1, *picptr;
   INT32 i, block;
  long npixels, maxpixels, aspect;
  long nbread=0;

  /* initialize variables */
  BitOffset = XC = YC = Pass = OutCount = npixels = maxpixels = 0;
  RawGIF = Raster = context.pic = NULL;
  gif89 = 0;

  fp = fopen(lName, "rb");
  if (!fp)
    return T3dLoadImage::LoadImageError("Unable to open file");

  /* find the size of the file */
  fseek(fp, 0L, 2);
  filesize = ftell(fp);
  fseek(fp, 0L, 0);


  /* the +256's are so we can read truncated GIF files without fear of
     segmentation violation */
  if (!(ptr = RawGIF = new byte[filesize+256]))
    return T3dLoadImage::LoadImageError("not enough memory to read gif file");

  if (!(Raster = new byte[filesize+256])) {
    T3dLoadImage::LoadImageError( "not enough memory to read gif file");
    goto ERROR;
  }

  if ((nbread=fread((char*)ptr, (int) filesize, 1, fp)) != 1) {
		std::cout << nbread << std::endl;
    T3dLoadImage::LoadImageError("GIF data read failed");
    goto ERROR;
  }

  if      (strncmp((char *) ptr, id87, 6)==0) gif89 = 0;
  else if (strncmp((char *) ptr, id89, 6)==0) gif89 = 1;
  else    {
    T3dLoadImage::LoadImageError( "not a GIF file");
    goto ERROR;
  }

  ptr += 6;

  /* Get variables from the GIF screen descriptor */

  ch = NEXTBYTE;
  RWidth = ch + 0x100 * NEXTBYTE;	/* screen dimensions... not used. */
  ch = NEXTBYTE;
  RHeight = ch + 0x100 * NEXTBYTE;

  ch = NEXTBYTE;
  HasColormap = ((ch & COLORMAPMASK) ? 1 : 0);

  BitsPerPixel = (ch & 7) + 1;
  context.numcols = ColorMapSize = 1 << BitsPerPixel;
  BitMask = ColorMapSize - 1;

  Background = NEXTBYTE;		/* background color... not used. */

  aspect = NEXTBYTE;
  if (aspect) {
    if (!gif89) {
      T3dLoadImage::LoadImageError( "Corrupt GIF file (screen descriptor)");
      goto ERROR;
    }
    else {}//normaspect = (float) (aspect + 15) / 64.0;   /* gif89 aspect ratio */
//    DEBUG cerr << "GIF89 aspect = " << normaspect << endl;
  }

  /* Read in global colormap. */
  context.bitmap = 0;
  if (HasColormap)
    for (i=0; i<ColorMapSize; i++) {
      context.r[i] = NEXTBYTE;
      context.g[i] = NEXTBYTE;
      context.b[i] = NEXTBYTE;
    }
  else {  /* no colormap in GIF file */
    /* put std EGA palette (repeated 16 times) into colormap, for lack of
       anything better to do */

    context.numcols = 256;

    for (i=0; i<256; i++) {
      context.r[i] = EGApalette[i&15][0];
      context.g[i] = EGApalette[i&15][1];
      context.b[i] = EGApalette[i&15][2];
    }
  }

  /* possible things at this point are:
   *   an application extension block
   *   a comment extension block
   *   an (optional) graphic control extension block
   *       followed by either an image
   *	   or a plaintext extension
   */

  while (1) {
    block = NEXTBYTE;

    if (block == EXTENSION) {  /* parse extension blocks */
      INT32 i, fn, blocksize, aspnum, aspden;

      /* read extension block */
      fn = NEXTBYTE;

			//  DEBUG cerr << "GIF extension type 0x" << hex << fn << dec << endl;

      if (fn == 'R') {                  /* GIF87 aspect extension */
	blocksize = NEXTBYTE;
	if (blocksize == 2) {
	  aspnum = NEXTBYTE;
	  aspden = NEXTBYTE;
	  if (aspden>0 && aspnum>0)
	    ;//	    normaspect = (float) aspnum / (float) aspden;
	  else {/* normaspect = 1.0; */ aspnum = aspden = 1; }

// 	  DEBUG cerr << "GIF87 aspect extension: " << aspnum << ":" << aspden
// 	    << " = " << normaspect << endl;
	}
	else {
	  for (i=0; i<blocksize; i++) (void) NEXTBYTE;
	}
      }

      else if (fn == 0xFE) {  /* Comment Extension.  just eat it */
	INT32 ch, j, sbsize;

	DEBUG std::cerr << "Comment extension:  ";
	/* read (and ignore) data sub-blocks */
	do {
	  j = 0;  sbsize = NEXTBYTE;
	  while (j<sbsize) {
	    ch = NEXTBYTE;  j++;
	    DEBUG std::cerr << char(ch);
	  }
	} while (sbsize);
	DEBUG std::cerr << std::endl;
      }

      else if (fn == 0x01) {  /* PlainText Extension */
	INT32 j,sbsize,ch;
	INT32 tgLeft, tgTop, tgWidth, tgHeight, cWidth, cHeight, fg, bg;

	sbsize   = NEXTBYTE;
	tgLeft   = NEXTBYTE;  tgLeft   += (NEXTBYTE)<<8;
	tgTop    = NEXTBYTE;  tgTop    += (NEXTBYTE)<<8;
	tgWidth  = NEXTBYTE;  tgWidth  += (NEXTBYTE)<<8;
	tgHeight = NEXTBYTE;  tgHeight += (NEXTBYTE)<<8;
	cWidth   = NEXTBYTE;
	cHeight  = NEXTBYTE;
	fg       = NEXTBYTE;
	bg       = NEXTBYTE;
	i=12;
	for ( ; i<sbsize; i++) (void) NEXTBYTE;   /* read rest of first subblock */

	DEBUG std::cerr << "PlainText: tgrid=" << tgLeft << "," << tgTop << " " <<
	  tgWidth << "x" << tgHeight << " cell=" << cWidth << "x" << cHeight <<
	    "  col=" << fg << "," << bg << std::endl;

	/* read (and ignore) data sub-blocks */
	do {
	  j = 0;
	  sbsize = NEXTBYTE;
	  while (j<sbsize) {
	    ch = NEXTBYTE;  j++;
	    DEBUG std::cerr << char(ch);
	  }
	} while (sbsize);
	DEBUG std::cerr << std::endl;
      }


      else if (fn == 0xF9) {  /* Graphic Control Extension */
	INT32 j, sbsize;

	DEBUG std::cerr << "Graphic Control extension" << std::endl;

	/* read (and ignore) data sub-blocks */
	do {
	  j = 0; sbsize = NEXTBYTE;
	  while (j<sbsize) { (void) NEXTBYTE;  j++; }
	} while (sbsize);
      }


      else { /* unknown extension */
	INT32 j, sbsize;

	//	DEBUG std::cerr << "unknown GIF extension 0x" << hex << fn << dec << std::endl;

	/* read (and ignore) data sub-blocks */
	do {
	  j = 0; sbsize = NEXTBYTE;
	  while (j<sbsize) { (void) NEXTBYTE;  j++; }
	} while (sbsize);
      }
    }

    else if (block == IMAGESEP) break;   /* read an image */

    else if (block == TRAILER) {
      T3dLoadImage::LoadImageError( "No image data found in GIF file");
      goto ERROR;
    }

    else {
      T3dLoadImage::LoadImageError( "Unknown block type found in file.");
      goto ERROR;
    }
  }


  /* read in values from the image descriptor */

  ch = NEXTBYTE;
  LeftOfs = ch + 0x100 * NEXTBYTE;
  ch = NEXTBYTE;
  TopOfs = ch + 0x100 * NEXTBYTE;
  ch = NEXTBYTE;
  Width = ch + 0x100 * NEXTBYTE;
  ch = NEXTBYTE;
  Height = ch + 0x100 * NEXTBYTE;

  Misc = NEXTBYTE;
  Interlace = ((Misc & INTERLACEMASK) ? 1 : 0);

  if (Misc & 0x80) {
    for (i=0; i < (1 << ((Misc&7)+1)); i++) {
      context.r[i] = NEXTBYTE;
      context.g[i] = NEXTBYTE;
      context.b[i] = NEXTBYTE;
    }
  }


  if (!HasColormap && !(Misc&0x80)) {
    /* no global or local colormap */
  }

  /* Start reading the raster data. First we get the intial code size
   * and compute decompressor constant values, based on this code size.
   */

  CodeSize = NEXTBYTE;

  ClearCode = (1 << CodeSize);
  EOFCode = ClearCode + 1;
  FreeCode = FirstFree = ClearCode + 2;

  /* The GIF spec has it that the code size is the code size used to
   * compute the above values is the code size given in the file, but the
   * code size used in compression/decompression is the code size given in
   * the file plus one. (thus the ++).
   */

  CodeSize++;
  InitCodeSize = CodeSize;
  MaxCode = (1 << CodeSize);
  ReadMask = MaxCode - 1;

  /* UNBLOCK:
   * Read the raster data.  Here we just transpose it from the GIF array
   * to the Raster array, turning it from a series of blocks into one long
   * data stream, which makes life much easier for ReadCode().
   */

  ptr1 = Raster;
  do {
    ch = ch1 = NEXTBYTE;
    while (ch--) { *ptr1 = NEXTBYTE; ptr1++; }
    if ((ptr - RawGIF) > filesize) {
      break;
    }
  } while(ch1);
  delete[] RawGIF;	 RawGIF = NULL; 	/* We're done with the raw data now */
  if (ptr1 <= Raster+filesize+256)
    *ptr1 = 0; // just to avoid uninitialized memory read

  DEBUG {
    std::cerr << "LoadGIF() - picture is " << Width << "x" << Height
      << " , " << BitsPerPixel << " bits, " <<
	(Interlace ? "" : "non-") << "interlaced" << std::endl;
  }

  /* Allocate the 'pic' */
  context.width = Width;
  context.height = Height;
  maxpixels = Width*Height;
  picptr = context.pic = new byte[maxpixels];

  if (!context.pic) {
    T3dLoadImage::LoadImageError( "not enough memory for 'pic'");
    goto ERROR;
  }

  /* Decompress the file, continuing until you see the GIF EOF code.
   * One obvious enhancement is to add checking for corrupt files here.
   */

  Code = ReadCode();
  while (Code != EOFCode) {
    /* Clear code sets everything back to its initial value, then reads the
     * immediately subsequent code as uncompressed data.
     */

    if (Code == ClearCode) {
      CodeSize = InitCodeSize;
      MaxCode = (1 << CodeSize);
      ReadMask = MaxCode - 1;
      FreeCode = FirstFree;
      Code = ReadCode();
      CurCode = OldCode = Code;
      FinChar = CurCode & BitMask;
      if (!Interlace) *picptr++ = FinChar;
         else DoInterlace(context, FinChar);
      npixels++;
    }
    else {
      /* If not a clear code, must be data: save same as CurCode and InCode */

      /* if we're at maxcode and didn't get a clear, stop loading */
      if (FreeCode>=4096) { /* printf("freecode blew up\n"); */ break; }

      CurCode = InCode = Code;

      /* If greater or equal to FreeCode, not in the hash table yet;
       * repeat the last character decoded
       */

      if (CurCode >= FreeCode) {
	CurCode = OldCode;
	if (OutCount > 4096) {  /* printf("outcount1 blew up\n"); */ break; }
	OutCode[OutCount++] = FinChar;
      }

      /* Unless this code is raw data, pursue the chain pointed to by CurCode
       * through the hash table to its end; each code in the chain puts its
       * associated output code on the output queue.
       */

      while (CurCode > BitMask) {
	if (OutCount > 4096) break;   /* corrupt file */
	OutCode[OutCount++] = Suffix[CurCode];
	CurCode = Prefix[CurCode];
      }

      if (OutCount > 4096) { /* printf("outcount blew up\n"); */ break; }

      /* The last code in the chain is treated as raw data. */

      FinChar = CurCode & BitMask;
      OutCode[OutCount++] = FinChar;

      /* Now we put the data out to the Output routine.
       * It's been stacked LIFO, so deal with it that way...
       */

      /* safety thing:  prevent exceeding range of 'pic' */
      if (npixels + OutCount > maxpixels) OutCount = maxpixels-npixels;

      npixels += OutCount;
      if (!Interlace) for (i=OutCount-1; i>=0; i--) *picptr++ = OutCode[i];
                else  for (i=OutCount-1; i>=0; i--) DoInterlace(context, OutCode[i]);
      OutCount = 0;

      /* Build the hash table on-the-fly. No table is stored in the file. */

      Prefix[FreeCode] = OldCode;
      Suffix[FreeCode] = FinChar;
      OldCode = InCode;

      /* Point to the next slot in the table.  If we exceed the current
       * MaxCode value, increment the code size unless it's already 12.  If it
       * is, do nothing: the next code decompressed better be CLEAR
       */

      FreeCode++;
      if (FreeCode >= MaxCode) {
	if (CodeSize < 12) {
	  CodeSize++;
	  MaxCode *= 2;
	  ReadMask = (1 << CodeSize) - 1;
	}
      }
    }
    Code = ReadCode();
    if (npixels >= maxpixels) break;
  }
  delete[] Raster;  Raster = NULL;

  if (npixels != maxpixels) {
    if (!Interlace)
      memset(context.pic+npixels, 0, maxpixels-npixels);  /* clear to EOBuffer */
  }

  fclose(fp);
  return 0;

 ERROR:
  fclose(fp);
  delete[] RawGIF;
  delete[] Raster;
  delete[] context.pic;
  return -1;
}


/* Fetch the next code from the raster data stream.  The codes can be
 * any length from 3 to 12 bits, packed into 8-bit bytes, so we have to
 * maintain our location in the Raster array as a BIT Offset.  We compute
 * the byte Offset into the raster array by dividing this by 8, pick up
 * three bytes, compute the bit Offset into our 24-bit chunk, shift to
 * bring the desired code to the bottom, then mask it off and return it.
 */

static INT32 ReadCode()
{
  unsigned INT32 RawCode, ByteOffset;

  ByteOffset = BitOffset / 8;
  RawCode = Raster[ByteOffset] | (unsigned INT32) (((unsigned INT32) Raster[ByteOffset + 1]) << 8);
  if (CodeSize >= 8)
    RawCode |= (unsigned INT32) (((unsigned INT32) Raster[ByteOffset + 2]) << 16l);
  RawCode >>= (BitOffset % 8);
  BitOffset += CodeSize;

  return (RawCode & ReadMask);
}


/***************************/
static void DoInterlace(T3dLoadImage& context, byte Index)
{
  static byte *ptr = NULL;
  static INT32 oldYC = -1;

  if (oldYC != YC) {  ptr = context.pic + YC * Width;  oldYC = YC; }

  if (YC<Height)
    *ptr++ = Index;

  /* Update the X-coordinate, and if it overflows, update the Y-coordinate */

  if (++XC == Width) {

    /* deal with the interlace as described in the GIF
     * spec.  Put the decoded scan line out to the screen if we haven't gone
     * past the bottom of it
     */

    XC = 0;

    switch (Pass) {
    case 0:
      YC += 8;
      if (YC >= Height) { Pass++; YC = 4; }
      break;

    case 1:
      YC += 8;
      if (YC >= Height) { Pass++; YC = 2; }
      break;

    case 2:
      YC += 4;
      if (YC >= Height) { Pass++; YC = 1; }
      break;

    case 3:
      YC += 2;  break;

    default:
      break;
    }
  }
}

/*****************************/

