#ifndef h_Sky_h
#define h_Sky_h


#include <Sprite3d/Sprite3d.h>

//***************************

class Sky: public Sprite3d
{
	Double3 cTab[ 1000 ];
	int cNb;

public:
	Sky( float pRadius, int pNb );
	virtual void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps);	
};
//***************************


#endif
