#ifndef _SceneAttackCroisseur_h
#define _SceneAttackCroisseur_h


#include <Sprite3d/AutoPtr.h>


#include <Sprite3d/Sprite3dObj.h>
 
#include <Space/SceneSprite.h>


//**************************************
class SceneAttackCroisseur : public SceneSprite
{
       
public:
	SceneAttackCroisseur( const char* pName, int pHardness, Double3 & lPos, float  pInterval, float pH, float pV);
	virtual ~SceneAttackCroisseur();

	virtual GLboolean animate();
};
//**************************************

#endif

