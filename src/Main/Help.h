#ifndef h_Help_h
#define h_Help_h


#include <Sprite3d/AutoPtr.h>
#include <Sprite3d/Sprite3dObj.h>

#include <U3d/BonusMaker.h>
#include <U3d/WeaponsMaker.h>

#include <Space/AsteroidesMaker.h>
#include <Space/ShipsMaker.h>
#include <Space/MinesMaker.h>


//**************************************
class Help : public World, public Action
{
	int cSize;

	float cInterval;
	int   cH;
	float cV;
	AutoPtr<O3dObjProps> caPropsGen;
	ObjVect cObjVect;
	Float4 cColorTextNormal;
	O3dObjProps  cPropsTextNormal;

public:
	Help( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,  O3dObjProps *pProps=NULL);

	void mouseMove( int pX, int pY );
	void mouseButton( int pButton, int pState, int pX, int pY);

	GLboolean initStart(int pNiveau=1, const char*pFile=NULL);
	long userAction( Sprite3d &pMySprite, void*pParam0, void*pParam1, void*pParam2 );
	void AfficheLine( int pX, int pY, const char* pStr );

	void initSprite( Sprite3d* pSp, int pX, int pY );

	void makeAsteroide( EnumAsteroides pType, int pX, int pY, int pSz );
	void makeShip( ShipType pType, int pX, int pY, int pSz );
	void makeBonus( EnumBonus pType, int pX, int pY, int pSz );
	void makeMine( MineType pType, int pX, int pY, int pSz );
	void makeWeapon( EnumWeapons pType, int pX, int pY, int pSz );
};
//**************************************

#endif

