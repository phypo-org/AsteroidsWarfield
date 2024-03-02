#ifndef H__CONTAINERS_MAKER__H
#define H__CONTAINERS_MAKER__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>


enum EnumBonus{ CONTAINER_ERG, 
								CONTAINER_ROCKET, 
								CONTAINER_FIELD, 
								CONTAINER_LIFE, 
								CONTAINER_GOLD, 
								CONTAINER_UPGRAD, 
								CONTAINER_MAX};

enum EnumBonusUpgrad{ UPGRAD_ERG,
											UPGRAD_ROCKET,
											UPGRAD_FIELD,

											UPGRAD_PHASER,
											UPGRAD_LAUNCHER,
											UPGRAD_MOTOR,
											MAX_UPGRAD};

//************************************************************
class BonusMaker : public Action
{
public:
	Float4    cColorErg;
	Float4		cColorRocket;
	Float4		cColorField;
	Float4		cColorLife;
	Float4		cColorGold;
	Float4		cColorUpgrad;
	Float4		cColorUpgradField;

	O3dObjProps cPropsErg;
	O3dObjProps cPropsRocket;
	O3dObjProps cPropsField;
	O3dObjProps cPropsLife;
	O3dObjProps cPropsGold;
	O3dObjProps cPropsUpgrad;

	O3dObjProps cPropsSkeleton;
	O3dObjProps cPropsUpgradField;

	static const int MAX_BONUS=3;

public:		
	O3dObj* cObjBonus[MAX_BONUS];
	O3dObj* cObjUpgrad[MAX_BONUS];

public:
	BonusMaker();	

	ObjVect*  makeBonus( float pSz );
	ObjVect*  makeUpgrad( float pSz );
	Sprite3d* makeSpriteBonus( int cObjType, EnumBonus pType, unsigned int pMaskObj, unsigned int pMakInteract, int pVal, int pVal2=0 );
	Sprite3d* makeSpriteBonus( int cObjType, unsigned int pMaskObj, unsigned int pMakInteract, int pVal );
};

extern BonusMaker* TheBonusMaker;

#define	CONTAINER_TYPE     SPRITE_USER1
#define	CONTAINER_VALUE    SPRITE_USER2
#define	CONTAINER_VALUE2   SPRITE_USER3

//************************************************************
#endif
