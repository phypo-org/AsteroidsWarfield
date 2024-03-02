#ifndef h_Text2d_h
#define h_Text2d_h



#include <T3d/T3dFont.h>

#include <string>

//***************************************
class Text2d
{
protected:
	std::string cString;
	T3dFont *cFont;
	int cW;
	int cH;
	
public:
	Text2d( T3dFont *pFont, int pW, int pH, const char *pStr=NULL );
	std::string &getString() {return cString; }
	void display(GLdouble pX, GLdouble pY, GLdouble pZ);
};

//***************************************


#endif
