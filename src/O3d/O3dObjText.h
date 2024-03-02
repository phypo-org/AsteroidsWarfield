#ifndef _O3dObjText_h_
#define _O3dObjText_h_

#include "O3d/O3dObjPoint.h"

#include <string>
#include <vector>


//****************************************
class O3dObjText : public O3dObj 
{
	T3dFont *cFont;
	std::string cStr;

public:
	O3dObjText( T3dFont *pFont, const char *pStr );	


	virtual void drawObj(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual const char *getObjTypeStr()		{ return "Text";		}
	void setStr( const char* pStr ){ cStr = pStr; }
};

//****************************************
class O3dObjText2d : public O3dObj, public std::vector<std::string*> 
{
	T3dFont *cFont;
	int cW;
	int cH;

public:
	O3dObjText2d( T3dFont *pFont, int pW, int pH, const char *pStr=NULL );	
	~O3dObjText2d();	

	virtual void drawObj(  O3dViewProps & pVProps, O3dObjProps *pObjProps );
	virtual const char *getObjTypeStr()		{ return "Text2d";		}

};

//****************************************

#endif
