#ifndef H__MINESMAKER__H
#define H__MINESMAKER__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>

#include <Space/ActionsShip.h>
#include <U3d/WeaponsMaker.h>


	enum MineType{
		MINE_1,
		MINE_LASER,
		MINE_ION,
		MAX_MIN_TYPE
	};

class Tourelle;

//**********************************************
class MinesMaker:public Action{

protected:
	Float4 cColorMine;
	Float4 cColorMineField;

	O3dObjProps cPropsMine;
	O3dObjProps cPropsMineField;

public:
	MinesMaker();
	Sprite3d* makeMine( MineType pMineType, int pMaxLife, 
											float  pSpin, 
											float pMaxSpeed=0.0f, float pMaxDeltaV=0.0f, float pReactivity=0.0f );

protected:

	ObjVect* makeMine1( float pSz, Sprite3dObj* pSp, EnumWeapons pWeapon );
	ObjVect* makeMine2( float pSz, Sprite3dObj* pSp );

	GLboolean collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam );
	GLboolean animate( Sprite3d &pMySprite, void * pParam );
	Tourelle* makeModul( float pSz );
};

extern MinesMaker * TheMinesMaker;

//**********************************************

#define MAKE_MINE_1 TheMinesMaker->makeMine( MINE_1, 5, 10, 5, 5, 5 )
#define MAKE_MINE_LASER TheMinesMaker->makeMine( MINE_LASER, 20, 15, 5, 5, 5 )
#define MAKE_MINE_ION TheMinesMaker->makeMine( MINE_ION, 5, 40, 5, 5, 5 )

#endif
