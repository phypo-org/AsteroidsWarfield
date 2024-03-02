#ifndef H__TOURELLE__H
#define H__TOURELLE__H


#include <Sprite3d/AnimatObj.h>

//#include <ActionsShip.h>
#include <U3d/WeaponsMaker.h>


//**************************************
class Tourelle: public AnimatObj
{
protected:
	FireMode    cFireMode;
	EnumWeapons cWeapon;
	T3dBox      cFireBox;
	unsigned int cMaskObj;
	unsigned int cMakInteract;

public:
	Tourelle( Sprite3d* pSprite, float pFireDelay, 
						FireMode pFireMode, 
						EnumWeapons pWeapon, 
						T3dBox& pFireBox, 
						unsigned int pMaskObj, unsigned int pMakInteract,
						O3dObj* pObj=NULL );

	Tourelle();

	virtual void set( Sprite3d* pSprite, float pFireDelay,
										FireMode pFireMode,
										EnumWeapons pWeapon, 
										T3dBox& pFireBox, 
										unsigned int pMaskObj, unsigned int pMakInteract,
										O3dObj* pObj=NULL );

	virtual void animateFinal();	
};
//**************************************




#endif
