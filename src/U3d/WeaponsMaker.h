#ifndef H__WEAPONS_MAKER__H
#define H__WEAPONS_MAKER__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>
#include <Sprite3d/SoundControler.h>

enum EnumWeapons{
	WEAPON_NO, 
	WEAPON_ION,
	WEAPON_MICRO_PLASMA,
	WEAPON_PLASMA,
	WEAPON_PLASMA2,
	WEAPON_PLASMA_RED,
	WEAPON_PLASMA_GREEN,
	WEAPON_PLASMA_BLUE,
	WEAPON_SMALL_ROCKET,
	WEAPON_ROCKET,
	WEAPON_BIG_ROCKET,
	
	WEAPON_SMALL_MISSILE,
	WEAPON_MISSILE,
	WEAPON_BIG_MISSILE,

	MAX_WEAPON
};


enum FireMode{
  	FIRE_STOPPED,
		FIRE_FRONT,
		FIRE_DIRECT
	};

#define	WEAPON_TYPE         SPRITE_USER1
#define	WEAPON_MAX_SPEED    SPRITE_USER2
#define	WEAPON_MAX_DELTA_V  SPRITE_USER3
#define	WEAPON_REACTIVITY   SPRITE_USER4
#define	WEAPON_ACTION_DELAY SPRITE_USER5
#define	WEAPON_DEAD_DELAY   SPRITE_USER6



class WeaponsMaker;
extern WeaponsMaker* TheWeaponsMaker;

//************************************************************
class WeaponsMaker : public Action
{
	Float4      cColorPlasma;
	Float4		  cColorPlasma2;
	Float4      cColorPlasmaRed;
	Float4      cColorPlasmaGreen;
	Float4      cColorPlasmaBlue;
	Float4      cColorIon;
	Float4      cColorRocket;
	Float4      cColorFire;

	O3dObjProps cPropsPlasma;
	O3dObjProps cPropsPlasma2;
	O3dObjProps cPropsPlasmaRed;
	O3dObjProps cPropsPlasmaGreen;
	O3dObjProps cPropsPlasmaBlue;

	O3dObjProps cPropsIon;
	O3dObjProps cPropsRocket;
	O3dObjProps cPropsFire;

public:		
	
	AutoPtr<O3dObj>  caObjPlasma;
	AutoPtr<O3dObj>  caObjMicroPlasma;
	AutoPtr<O3dObj>  caObjPlasma2;
	AutoPtr<O3dObj>  caObjPlasmaRed;
	AutoPtr<O3dObj>  caObjPlasmaGreen;
	AutoPtr<O3dObj>  caObjPlasmaBlue;
	AutoPtr<ObjVect> caObjIon;
	AutoPtr<O3dObj>  caObjSmallRocket;
	AutoPtr<O3dObj>  caObjRocket;
	AutoPtr<O3dObj>  caObjBigRocket;

	AutoPtr<O3dObj>  caObjSmallMissile;
	AutoPtr<O3dObj>  caObjMissile;
	AutoPtr<O3dObj>  caObjBigMissile;

public:
	WeaponsMaker();	

protected:
	O3dObj*   makePlasma(float pSz);
	O3dObj*   makePlasma2(float pSz);
	ObjVect*  makeIon(float pSz);
	ObjVect*  makeBigPlasma(float pSz, O3dObjProps* pProps);
	O3dObj*   makeRocket(float pSz);
	O3dObj*   makeMissile(float pSz);

	void      set( Sprite3d *pSp, float pDestroyPoint, float pSpeed, float pSpin );
	void      destruction( Sprite3d &pMySprite );
	GLboolean searchTarget( Sprite3d &pMySprite  );

	
public:
	Sprite3d* makeSprite( T3dTransf* pTransf, EnumWeapons pType, unsigned int pMaskObj, unsigned int pMakInteract );
	void makeSprite( Sprite3d* pSpProj[16], T3dTransf* pTransf, int pLevel, EnumWeapons pType,  unsigned int pMaskObj, unsigned int pMakInteract);
	
	static Sprite3d* MakeSprite( T3dTransf* pTransf, EnumWeapons pType, unsigned int pMaskObj, unsigned int pMakInteract)
	{ return TheWeaponsMaker->makeSprite( pTransf, pType, pMaskObj, pMakInteract ); }
	
	GLboolean collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam );
	GLboolean animate( Sprite3d &pMySprite, void * pParam );


	void makeMultipleSameWeapon( int& pCurrent, Sprite3d* pSpProj[32], int pNbWeapon,
															 T3dTransf* pTransf, EnumWeapons pType, 
															 unsigned int pMaskObj, unsigned int pMakInteract);

	void makeMultipleSameWeaponDiag( int& pCurrent, Sprite3d* pSpProj[32], int pNbWeapon,
																	 float pDiag, T3dTransf* pTransf, EnumWeapons pType, 
																	 unsigned int pMaskObj, unsigned int pMakInteract);


static PSoundId sSoundWeaponExplode   ;
static PSoundId sSoundWeaponExplodePlasma  ;
static PSoundId sSoundWeaponExplodePlasmaG  ;

static PSoundId sSoundExplosionBig ;
static PSoundId sSoundExplosion1  ;
static PSoundId sSoundExplosion2  ;
static PSoundId sSoundExplosion3  ;
static PSoundId sSoundExplosion4 ;

static bool InitSound( );

};


//************************************************************

#endif
