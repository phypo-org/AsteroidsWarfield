#ifndef _SceneGrotte_h
#define _SceneGrotte_h


#include <Sprite3d/AutoPtr.h>


#include <Space/AsteroidesMaker.h>

#include <Space/SceneSprite.h>

//**************************************
class SceneGrotte : public SceneSprite
{
	float cIntervalParoi;
	int   cSizeParoi;

	GLboolean cFirstTime;


	void makeFloor( int pH );
	void makeArtefact();
	void makeWall(int pMin, int pMax, GLboolean pIndestructible, float pSpeed=0.0f, float pDeltaX=0.0f, float pAleaX=0.0f );
	void makeAsteroide(Double3& pPos, int pSz, GLboolean pIndestructible );

public:
	SceneGrotte( const char* pName, EnumAsteroides pTypeAsteroide, int pHardness, Double3 & lPos, float  pInterval, float  pIntervalParoi, int pSizeParoi, float pH, float pV);

	virtual GLboolean animate();
	virtual GLboolean leaveWorld();
	
	void      enterWorld(); 

	static SceneGrotte *TheSceneGrotte;
};
//**************************************

#endif

