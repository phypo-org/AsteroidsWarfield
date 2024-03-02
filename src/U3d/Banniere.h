#ifndef H__BANNIERE__H
#define H__BANNIERE__H




#include <Sprite3d/Sprite3dObj.h>
#include <Sprite3d/AutoPtr.h>


//*************************************************

class Banniere: public Sprite3d
{
protected:
	O3dObjProps cProps;
	AutoPtr<T3dTexture>  caTex;

public:
	Banniere( const char* pStr, Float4& pColor );
	void drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps );

};

//*************************************************


#endif
