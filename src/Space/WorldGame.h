#ifndef h_WorldGame_h
#define h_WorldGame_h


#include <Sprite3d/World.h>

#include <Sprite3d/SceneManager.h>




//**************************************

class WorldGame:public World
{
  int cSize;
  int cLevel;

  char cInfoLevel[512];
	
public: 
  enum class PathType{
    SOUND,
    TEXTURE,
    FONT
  };

public:
  SceneManager* cSceneManager;

  WorldGame( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,  O3dObjProps *pProps=NULL);
  ~WorldGame();
  virtual GLboolean initStart( int pNiveau=0, const char* pNameFile =NULL  );
  void freeRessources();
  virtual void gameOver();
  virtual int userEvent( void* pUserData );

  SceneManager* getSceneManager() { return cSceneManager; }
  virtual const char* getInfoLeveL();
  Sprite3d* makeBanniere( const char* pName, Float4 pColor, float pLiveTime );
  virtual void saveStateToFile( const char* pName );

public:
  static bool InitSound( const char* pSoundPath );
  static void InitSprite(  );

  static float GlobalScroll;
  static float XSizeWorld ;
  static float YSizeWorld ;

  static WorldGame *TheWorldGame;

  static std::string sDataRootPath;
  static void SetDataRootPath( const std::string & iPath ) { sDataRootPath = iPath; }
  
  static const char*      GetPathConfig( std::string& pName, WorldGame::PathType pPath, const char* pKey );
  static T3dTexture*      LoadTextureConfig( const char* pKey, GLenum pFilter = GL_NEAREST  );
};
//**************************************



#endif
