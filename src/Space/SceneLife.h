#ifndef _SceneLife_h
#define _SceneLife_h


#include <Sprite3d/AutoPtr.h>
#include <Sprite3d/Sprite3dObj.h>


#include <Space/Scene.h>

//**************************************
class SceneLife : public Scene
{
	GLboolean cFirstTime;
public:
	SceneLife(Double3& lPos, float pH, float pV);

	virtual GLboolean animate();
};
//**************************************

#endif

