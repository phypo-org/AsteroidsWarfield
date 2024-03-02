#ifndef _MainMenu_h
#define _MainMenu_h



#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Sprite3dObj.h>
// #ifdef  PUI_WIN
// #include <plib/pu.h>
// #include <plib/puAux.h>
// #endif


#ifndef MAX
#define MAX(A,B) ((A)>(B)?(A):(B))
#endif

#ifndef MIN
#define MIN(A,B) ((A)<(B)?(A):(B))
#endif



//**************************************
class MainMenu : public World, public Action
{
  int       cSize;

  float     cInterval;
  int       cH;
  float     cV;
  AutoPtr<O3dObjProps> caPropsGen;
  ObjVect      cObjVect;
  Float4       cColorTextNormal;
  O3dObjProps  cPropsTextNormal;

public:
  MainMenu( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,  O3dObjProps *pProps=NULL);
  virtual void mouseButton( int pButton, int pState, int pX, int pY);
  virtual void mouseMove( int pX, int pY );

  virtual GLboolean initStart(int pNiveau=1, const char*pFile=NULL);
  virtual long userAction( Sprite3d &pMySprite, void*pParam0, void*pParam1, void*pParam2 );
  void AfficheLine( int pX, int pY, const char* pStr );
  virtual void enterWorld(int pWidth, int pHeight);
  virtual void leaveWorld();
  virtual void reshapeWorld(int pWidth, int pHeight);
  
  void drawHelp();

protected:
  void MyReadFileCb();
  /*
    puOneShot* cReadAutoBox;
    static void MyReadFileCb( puObject * pObject);
    static void MyButtonCb( puObject * pObject);


    puOneShot* cGentileBox;
    puOneShot* cEasyBox;
    puOneShot* cMediumBox;
    puOneShot* cHardBox;
    puOneShot* cExtremeBox;

    puaFileSelector* cReadSavBox;

    puButton* cMuteSoundButton;

  */
  int  cDifficulty;
public:
  int getDifficulty() { return cDifficulty;}

  static MainMenu* TheMainMenu;
};
//**************************************

#endif

