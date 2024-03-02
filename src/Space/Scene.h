#ifndef _Scene_h
#define _Scene_h


#include <Sprite3d/AutoPtr.h>


#include <string>

#include <Sprite3d/Sprite3dObj.h>


//**************************************
class Scene : public Sprite3dObj
{
protected:
	int   cHardness;
	float cInterval;
	float cH;
	float cV;	
	std::string cName;
	
	char  cStrInfo[81];
public:
	Scene( const char* pName, int pHardness, float  pInterval, float pH, float pV );
	virtual~Scene(){;}
	virtual int getSpriteType() { return -1; }

	virtual GLboolean animate();
	virtual GLboolean leaveWorld() { return GL_FALSE;}

	std::string& getName() { return cName; }
	int          getHardness() { return cHardness; }
	float        getInterval() { return cInterval; }
	virtual const char* getStrInfo();
};
//**************************************

#endif
