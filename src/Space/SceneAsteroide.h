#ifndef _SceneAsteroide_h
#define _SceneAsteroide_h


#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3dObj.h>

#include <Space/AsteroidesMaker.h>

#include <Space/SceneSprite.h>

//**************************************
class SceneAsteroide : public SceneSprite
{

public:
	SceneAsteroide(const char* pName,  EnumAsteroides pTypeAsteroide, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);
	virtual~SceneAsteroide();

	virtual GLboolean animate();

	static SceneAsteroide *TheSceneAsteroide;
};
//**************************************

#endif

