
#ifndef h_World_h
#define h_World_h

#include <stdlib.h>
#include <stdio.h>

#include <T3d/T3dBox.h>
#include <O3d/O3dObjProps.h>
#include <O3d/O3dKamera.h>

#include <Sprite3d/ObjVect.h>
#include <Sprite3d/Collision.h>

#include <T3d/T3dFont.h>


#include <string>
#include <map>



class Sprite3d;

class O3dKamera;
class Sprite3dPilot;

class WorldControler;

//**************************************

class World
{
protected:
	ObjVect cLiveObj;
	std::vector <Sprite3d*> cServiceSprite;

	std::vector <Sprite3d*> cNewSprite;    // les sprite nouvellement creé
	std::vector <Sprite3d*> cLiveSprite;

	std::vector <int> cFreeLivePosition;

	//	std::vector <Sprite3d*> cDeadSprite;

	O3dObjProps    *cProps;
	Sprite3dPilot  *cPilot;
	WorldControler *cMyControler;
	O3dKamera      * cKamera;
	GLboolean cOverlayOpen;

	T3dBox cBox; // The size of this world !

	Array3d< std::vector<Sprite3d*> >* cZonesDetectCollision; //Detection de collision par zone

public:

	World( WorldControler* pControl, O3dKamera* pKamera, Double3& pMax, O3dObjProps *pProps=NULL);
	virtual~World();

	void setProps( O3dObjProps *pProps ) {cProps = pProps; }
	O3dObjProps *getProps() {return cProps; }


	void killSprite( Sprite3d *pSp );
	

	int cNbLiveSprite;
	int getSizeLiveSprite() { return cLiveSprite.size(); }
	int getNbLiveSprite() { return cNbLiveSprite ; }
	void removeLiveSprite( VSprite3d::iterator& pIterLive );
	void removeSprite(  Sprite3d *pSp );

	bool deleteSprite( Sprite3d* pSprite);

	void killAllSprite();

	virtual void add( O3dObj *pObj ){ cLiveObj.push_back( pObj ); }
	virtual void add( Sprite3d *pSprite );

	virtual void saveStateToFile( const char* pName ){;};

	WorldControler * getMyControler() { return cMyControler;}
	void setMyControler(WorldControler *pControl) { cMyControler=pControl;}


	T3dBox & getBox()	{ return cBox; 	}

	virtual void setPilot( Sprite3dPilot *pPilot )	{		cPilot = pPilot;	}
	virtual Sprite3dPilot *getPilot() { return cPilot; }
	virtual void setKamera( O3dKamera *pKamera )   	{ cKamera= pKamera;	}
	virtual O3dKamera* getKamera() {return cKamera; }

	Sprite3d *isSpriteIntersect( Double3 pPos, float pRadius, unsigned int pMmask_Att );
	//	Sprite3d *isSpriteIntersectXY( Double3 pPos, float pRadius, unsigned int pMmask_Att );


	GLboolean initOverlay();
	GLboolean asOverlay() { return cOverlayOpen; }



	virtual const char* getInfoLeveL() { return "";}

	// Draw

	virtual void drawWorld();


	// Animate
	virtual void animateWorld();
	virtual void animateLiveSprite();
	virtual void drawLiveSprite();


	// Event
	virtual void mouseMove( int pX, int pY );
	virtual void mouseButton( int pButton, int pState, int pX, int pY );
	virtual void key( unsigned char pKey, int pX, int pY );
	virtual void setPilot( int pX, int pY );
	virtual void setPilotKey(unsigned char pKey, int pX, int pY  );
	virtual void setPilotKeyUp(unsigned char pKey, int pX, int pY  );
	virtual void setPilotSpecialKey(unsigned char pKey, int pX, int pY  );


	virtual GLboolean initStart(int pNiveau=0, const char* pFileNameSav=NULL)=0;
	virtual void freeRessources() {;}
	virtual void empty();
	virtual void gameOver();
	virtual void gameWinner();

	virtual int userEvent( void* pUserData ) { return 0; }

	virtual void enterWorld( int pWidth, int pHeight){;}
	virtual void leaveWorld(){;}
	virtual void reshapeWorld(int pWidth, int pHeight);


	static GLboolean GetDistPilot( Sprite3d *pSprite,  Double3 & pDist );
	static GLboolean GetPositionWithoutCollision( int pInteract,Double3& pPos, int pSize, int pLimitX, int pLimitY=0, int pLimitZ=0, int pNbTry=10, float pMarge=1.5 );

	static long sNbDetect;

	

	static World* sTheWorld
;

	static std::map< std::string, std::string> sConfig;
	static std::string              sIniFile;


public:
	static int sFlagCollision3d;
	static int sThresholdDetection3d;
 

protected:
};
//**************************************



#endif
