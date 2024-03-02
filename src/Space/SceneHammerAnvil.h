#ifndef _SceneHammerAnvil_h
#define _SceneHammerAnvil_h


#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3dObj.h>
#include <Space/AsteroidesMaker.h>


#include <Space/SceneSprite.h>

//**************************************
class SceneHammerAnvil : public SceneSprite
{

public:
	SceneHammerAnvil(const char* pName,  EnumAsteroides pTypeHammerAnvil, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);

	virtual GLboolean animate();
	virtual GLboolean subAnimate(int pSens);

	static SceneHammerAnvil *TheSceneHammerAnvil;
};
//**************************************

#endif

