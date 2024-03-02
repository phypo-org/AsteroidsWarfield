#ifndef H__ACTIONSSHIP__H
#define H__ACTIONSSHIP__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>

#include <U3d/WeaponsMaker.h>

enum ShipAction{
		SHIP_ACTION_NOMINAL,
		SHIP_ACTION_ATTACK,
		SHIP_ACTION_KAMIKAZE,
		SHIP_ACTION_TOURNOI,
		SHIP_ACTION_FUITE,

		SHIP_ACTION_MINE_PASSIVE,
		
		SHIP_ACTION_IN_DETRUCTION
	};


//**********************************************
class ActionsShip :public Action{

public:
		
protected:
	void getDirection( double& pDx, double& pDy );

	void verifSpeedDelta( double& pV, double& pDV, double pMaxV, double pMaxDV );
	void fire( Sprite3d &pMySprite, Double3 pDist, GLboolean pDirectionnel );

	GLboolean collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam );
	GLboolean kill( Sprite3d &pMySprite, void*pParam );
	
	GLboolean animate( Sprite3d &pMySprite, void * pParam );

	GLboolean getDistPilot( Sprite3d &pMySprite, Double3 & pDist  );

	GLboolean animateNormal( Sprite3d &pMySprite, void * pParam, GLboolean pMoveX, GLboolean pMoveY );
	GLboolean animateDestroy( Sprite3d &pMySprite, void * pParam );

public:
	static bool InitSound();

	static PSoundId sSoundExplosionBig ;
	static PSoundId sSoundExplosion1   ;
	static PSoundId sSoundExplosion2   ;
	static PSoundId sSoundExplosion3   ;
	static PSoundId sSoundExplosion4   ;
	static PSoundId sSoundDestroy   ;

};

#define	SHIP_MAX_SPEED    SPRITE_USER1
#define	SHIP_MAX_DELTA_V  SPRITE_USER2
#define	SHIP_REACTIVITY   SPRITE_USER3
#define	SHIP_ACTION       SPRITE_USER4
#define	SHIP_ACTION_DELAY SPRITE_USER5


#endif
