#ifndef H__ASTEROIDES_MAKER__H
#define H__ASTEROIDES_MAKER__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>

enum EnumAsteroides{
	ASTEROIDE_PIERRE,
	ASTEROIDE_SNOW,
	ASTEROIDE_ICE,
	ASTEROIDE_MARS,
	ASTEROIDE_WATER,
	ASTEROIDE_CRISTAL,
	PLASMA_SOLAIRE
};

//************************************************************
class AsteroidesMaker : public Action
{
	Float4               cColorGrey;
	Float4               cColorSnow;
	Float4               cColorIce;
	Float4               cColorCristal;
	Float4               cColorPlasmaSolaire1;
	Float4               cColorPlasmaSolaire2;


	AutoPtr<T3dTexture>  caTexLune;
	AutoPtr<T3dTexture>  caTexMars;
	AutoPtr<T3dTexture>  caTexWater;

	O3dObjProps cPropsLune;
	O3dObjProps cPropsMars;
	O3dObjProps cPropsWater;

	O3dObjProps cPropsSnow;
	O3dObjProps cPropsIce;

	O3dObjProps cPropsCristal;
	O3dObjProps cPropsPlasmaSolaire1;
	O3dObjProps cPropsPlasmaSolaire2;

	O3dObjProps cPropsGen;

public:
	AsteroidesMaker();

	O3dObj*  makeAsteroide( float pSz, int pFacette );
 	ObjVect*  makeAsteroideSnow( float pSz, int pFacette );
 	O3dObj* makeAsteroideIce( float pSz, int pFacette );
 	ObjVect* makeAsteroideCristal( float pSz, int pFacette );
 	ObjVect* makePlasmaSolaire( float pSz, int pFacette );
	Sprite3d* makeSpriteAsteroide( EnumAsteroides pType, float pSize, int pFacette );

	GLboolean collision( Sprite3d &pMySprite, Sprite3d &pSprite, void * pParam );
};

extern AsteroidesMaker* TheAsteroidesMaker;

//************************************************************

#endif
