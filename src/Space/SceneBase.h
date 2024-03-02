#ifndef _SceneBase_h
#define _SceneBase_h


#include <Sprite3d/AutoPtr.h>


#include <Sprite3d/Sprite3dObj.h>

#include <Space/SceneSprite.h>


//**************************************
class SceneBase : public SceneSprite
{	
    int cShipType;
public:
	SceneBase( const char* pName, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV,
               int pShipType);

	virtual GLboolean animate();
};
//**************************************

#endif
