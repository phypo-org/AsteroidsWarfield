#ifndef _SceneSprite_h
#define _SceneSprite_h


#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3dObj.h>
#include <Space/AsteroidesMaker.h>


#include <Space/Scene.h>

//**************************************
class SceneSprite : public Scene
{
protected:
	EnumAsteroides cTypeAsteroide;

	AutoPtr<O3dObjProps> caPropsGen;
	AutoPtr<T3dTexture>  caGenTexture;

public:
	SceneSprite(const char* pName,  EnumAsteroides pTypeHammerAnvil, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);

	virtual GLboolean animate() =0;
        virtual GLboolean subAnimate(int pSens){ return GL_FALSE;}
	virtual GLboolean leaveWorld();
};
//**************************************

#endif

