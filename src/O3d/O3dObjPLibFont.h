#ifndef _O3dObjPLibFont_h_
#define _O3dObjPLibFont_h_

#include <O3d/O3dObjPoint.h>

#include <string>
#include <vector>

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/names.h>

//****************************************
class O3dObjPLibFont : public O3dObj 
{
  Fl_Font     cFont;
	Fl_Fontsize cSize;
	std::string cStr;

public:	
	O3dObjPLibFont( Fl_Font pFont, Fl_Fontsize pSize, const char *pStr ) 
		: cFont(pFont), cSize(pSize), cStr(pStr){;}

	virtual void        drawObj(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual const char *getObjTypeStr()		{ return "Text";		}
	void                setStr( const char* pStr )  { cStr = pStr; }

	Fl_Font     getFont() { return cFont; } 
	Fl_Fontsize getSize() { return cSize; }

};
//****************************************


#endif
