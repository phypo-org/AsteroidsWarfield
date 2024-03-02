#ifndef h_WorldControler_h
#define h_WorldControler_h


#include <T3d/T3dBox.h>
#include <O3d/O3dObjProps.h>
#include <O3d/O3dKamera.h>

#include <Sprite3d/ObjVect.h>
#include <T3d/T3dFont.h>


class O3dKamera;
class Sprite3dPilot;
class Sprite3d;
class Collision;

class World;

//**************************************
class WorldControler{

protected:
	World* cCurrentWorld;
	World* cMainWorld;
	World* cHelpWorld;
	World* cGame;
	int cPause;
	int cFullScreen;

public:
	WorldControler( int pWidth, int pHeight, bool pFullScreen );
	virtual ~WorldControler();
	virtual void quit();
	virtual void mainWorld();
	virtual void helpWorld();
	virtual void start( int pLevel=0, const char* pFileNameSav = NULL);
	virtual void resume();

	void setGame( World* pGame ) { cGame = pGame; cGame->setMyControler(this);}
	void setMainWorld( World* pMainWorld ) { cMainWorld = pMainWorld; cMainWorld->setMyControler(this);}
	void setHelpWorld( World* pHelpWorld ) { cHelpWorld = pHelpWorld; cHelpWorld->setMyControler(this);}

    void write( std::ostream & pOs);
    bool read( std::istream & pIs );

	virtual void closeWindows(){;}
	virtual void openWindows() {;}
    void setSize( int pWidth, int pHeight);
//private:
  void setCurrent( World*pCurrent);

  World* getCurrentWorld() { return  cCurrentWorld; }

protected:
	GLboolean cLeftButtonDown;
	GLboolean cMiddleButtonDown;
	GLboolean cRightButtonDown;

	int cMouseX;
	int cMouseY;
	int cWidth;
	int cHeight;

public:
	static float sTime;
	static float sRatio;
	static int   sMicroRate;
	static int   sDifficultyLevel;

	static int   sKeyModifiers;
	static int   sOldKeyModifiers;
	static T3dFont *sCurrentFont;

	static World* GetCurrentWorld() { return WC->cCurrentWorld; }
	static World* GetGameWorld() { return WC->cGame; }
	static World* GetMainWorld() { return WC->cMainWorld; }
	static World* GetHelpWorld() { return WC->cHelpWorld; }
	static GLboolean IsLeftButtonDown()   { return WC->cLeftButtonDown;}
	static GLboolean IsMiddleButtonDown() { return WC->cMiddleButtonDown;}
	static GLboolean IsRightButtonDown() {return WC->cRightButtonDown; }
	static int GetMouseX(){ return WC->cMouseX;}
	static int GetMouseY(){return WC->cMouseY; }


	static  float GetTime()     { return sTime; }
	static	float GetRatio()	{ return sRatio; }
	static	void SetRate( float pRate )
	{
		sMicroRate = static_cast<int>(1000.0 / pRate);
		sRatio = 1.0/pRate;
	}


	virtual void selectNewGame( unsigned char pKey, int pX, int pY ) {;}


	static int sDebug;

	// Static
	static void MouseMove( int pX, int pY );
	static void MouseButton( int pButton, int pState, int pX, int pY );
	static void KeyUp( unsigned char pKey, int pX, int pY );
	static void Key( unsigned char pKey, int pX, int pY );
	static void SpecialKey( int pKey, int pX, int pY );

	static void Redraw(int p);
	static void Display();
	static void Animate(int p);
	static void InitCallback();
	static void Visibility( int pState );
	static void Idle();
	static void Reshape(int pWidth, int pHeight );


	static void Add( Sprite3d* pSprite);
	static void KillSprite( Sprite3d* pSprite) { WC->cCurrentWorld->killSprite( pSprite ); }
	static void GameOver( );
	static void GameWinner( );

	static int  GetKeyModifiers()    { return sKeyModifiers; }
	static int  GetOldKeyModifiers() { return sOldKeyModifiers; }

	static WorldControler * WC;

	// for user
	virtual int userEvent( void* pUserData );

	int getFullScreen() { return cFullScreen; }
	int getWidth()  { return  cWidth; }
	int getHeight() { return  cHeight;}




friend class World;
};

//**************************************

#define GETSAMPLE(SOUND) WorldControler::WC->getCurrentWorld()->getMySoundLibrary()->getSample(SOUND)
#define GETSOUNDLIBRARY WorldControler::WC->getCurrentWorld()->getMySoundLibrary()

#endif
