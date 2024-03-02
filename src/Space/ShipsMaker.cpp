#include <stdlib.h>

#include "ShipsMaker.h"

#include "T3d/T3dLoadImg.h"

#include "Sprite3d/World.h"
#include "Sprite3d/ObjOdron.h"

#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Sprite3d.h"
#include "Sprite3d/Utils3d.h"
#include "Sprite3d/Collision.h"
#include "Sprite3d/ObjText2d.h"
#include "Sprite3d/Random.h"

#include "U3d/Tourelle.h"
#include "U3d/WeaponsMaker.h"
#include "U3d/SpriteExplosion.h"
#include "U3d/BonusMaker.h"

#include "Space/Def.h"
#include "WorldGame.h"

#include <math.h>

ShipsMaker* TheShipsMaker=NULL;

//**********************************************************
ShipsMaker::ShipsMaker()
:cColorBody( 0.1, 0.7, 0.7, 1.0),
 cColorGrid( 0.8, 0.8, 0.8, 1.0 ),
 //cColorModul( 0.9, 0.8, 0, 1.0 ),
 //cColorSoute( 0.2, 0.8, 0.3, 1.0),
 //cColorFan( 0.3, 0.3, 0.5, 1.0),
 cColorModul( 0.2, 0.5, 0.6, 1.0 ),
 cColorSoute( 0.1, 0.8, 0.8, 1.0),
 cColorFan( 0.3, 0.9, 0.7, 1.0),
 cColorFire( 0.3, 0.2, 0.3, 0.1),
 cColorDome( 0.3, 0.5, 0.6, 0.3 )
{
	TheShipsMaker = this;


	caTexMod  = WorldGame::LoadTextureConfig("Ships.TexMod");
	caTexBody = WorldGame::LoadTextureConfig("Ships.TexBody"); // new T3dTexture("textures/25.gif" );

	caTexBlindage =  WorldGame::LoadTextureConfig("Ships.TexBlindage"); //new T3dTexture("textures/9.gif" );
	cPropsBlindage.setTexture( caTexBlindage );


	caTexSpin =  WorldGame::LoadTextureConfig("Ships.TexSpin"); //new T3dTexture("textures/32.gif" );
	cPropsSpin.setTexture( caTexSpin );

	caTexBleue =  WorldGame::LoadTextureConfig("Ships.TexBlue"); //new T3dTexture("textures/32.gif" );
	cPropsBleue.setTexture( caTexBleue );

	caTexMaille = WorldGame::LoadTextureConfig("Ships.TexMaille"); // new T3dTexture("textures/49.gif" );
	cPropsMaille.setTexture( caTexMaille );

	caTexEcail = WorldGame::LoadTextureConfig("Ships.TexEcaille"); // new T3dTexture("textures/53.gif" );
	cPropsEcail.setTexture( caTexEcail );

	caTexFlamme =  WorldGame::LoadTextureConfig("Ships.TexFlamme"); //new T3dTexture("textures/38.gif" );
	cPropsFlamme.setTexture( caTexFlamme );

	caTexDalle =  WorldGame::LoadTextureConfig("Ships.TexDalle"); //new T3dTexture("textures/63.gif" );
	cPropsDalle.setTexture( caTexDalle );

	caTexEmail =  WorldGame::LoadTextureConfig("Ships.TexCristal"); //new T3dTexture("textures/25.gif" );
	cPropsEmail.setTexture( caTexEmail );

	cPropsDome.ObjPropsFloat4::set( MATERIAL, cColorDome );
	cPropsDome.ObjPropsFloat4::set( EMISSION, cColorDome );
	cPropsDome.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
		cPropsDome.ObjPropsBool::set(DRAW_OBJ_SOLID, 1);


	cPropsBody.ObjPropsFloat4::set( MATERIAL, cColorBody );
	cPropsBody.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);

	cPropsGrid.ObjPropsFloat4::set( MATERIAL, cColorGrid );
	cPropsGrid.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
	cPropsGrid.ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

	cPropsModul.ObjPropsFloat4::set( MATERIAL, cColorModul );
	cPropsModul.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);



	cPropsSoute.ObjPropsFloat4::set( MATERIAL, cColorSoute );
	cPropsSoute.ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);


	cPropsFan.ObjPropsFloat4::set( MATERIAL, cColorFan);

	cPropsFire.ObjPropsFloat4::set( MATERIAL, cColorFire );

	//	cPropsModul.setTexture( lTex );
	///  cPropsSoute.setTexture( lTex );

}

//----------------------------------------------
O3dObj*
ShipsMaker::makeReactor( float pSz )
{
	ObjVect *lVect = new ObjVect;

	O3dObj*lCone = new O3dObjPrim( O3dObjPrim::PrimCone, pSz, 5, 5, pSz*1.5 );
	lCone->setObjProps( &cPropsBody );
	lVect->add( lCone );


	O3dObj *lJet = new O3dObjPrim( O3dObjPrim::PrimCone, pSz/2, 5, 5, pSz*15 );
	lJet->MkGetANGLE()[1] = 180;

	lJet->setObjProps( &cPropsFire );
	lVect->add( lJet );

	O3dObj *lJet2 = new O3dObjPrim( O3dObjPrim::PrimCone, pSz/3, 4, 4, pSz*5 );
	lJet2->MkGetANGLE()[1] = 180;
	lJet2->setObjProps( &cPropsFire );
	lVect->add( lJet2 );

	return lVect;
}
//----------------------------------------------
O3dObj*
ShipsMaker::makeGrid( float pH, float pL )
{
	O3dObj *lGrid = new O3dObjPrim( O3dObjPrim::PrimCylinder, pH, 5, 5, pL, pH );
	lGrid->setObjProps( &cPropsGrid );
	return lGrid;
}
//----------------------------------------------
Tourelle*
ShipsMaker::makeModul( float pSz )
{
	Tourelle *lTourelle = new Tourelle();

	O3dObj *lMod = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 5, 5 );
	lMod->setObjProps( &cPropsModul );
	lTourelle->add( lMod );
	return lTourelle;
}
//----------------------------------------------
O3dObj*
ShipsMaker::makeSoute( float pH, float pL )
{
	O3dObj *lSoute = new O3dObjPrim( O3dObjPrim::PrimCylinder, pH, 5, 5, pL, pH );
	lSoute->setObjProps( &cPropsSoute );
	return lSoute;
}
//----------------------------------------------
O3dObj*
ShipsMaker::makeFan( float pL, float pH, int pFacette )
{
	O3dObj *lFan = new O3dObjPrim( O3dObjPrim::PrimDisk, pH, pFacette, pFacette, pL );
	lFan->setObjProps( &cPropsFan );
	return lFan;
}

//----------------------------------------------
ObjVect*
ShipsMaker::makeShip1( float pSz, Sprite3dObj* pSp, EnumWeapons pWeapon, int pNiveau )
{
	ObjVect *lVect = new ObjVect;
	float lLg = pSz*3;

	O3dObj* lGrid1 = makeGrid( pSz*0.5,  lLg );
	lGrid1->getTransf().TransfDouble3::get( POS )[2] = -lLg*1.2;
	lVect->add( lGrid1 );

	Tourelle* lMod1 = makeModul( pSz );
	T3dBox lBox( -150, -30, -100, 0, 30,  100 );
	lMod1->set( pSp, 0.5, FIRE_FRONT, pWeapon,  lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut );

//	lMod1->getTransf().TransfDouble3::get( POS )[2] = lLg*0.8;
	lVect->add( lMod1 );


	O3dObj* lReact;
	lVect->add( (lReact = makeReactor( pSz)) );
	lReact->getTransf().TransfDouble3::get( POS )[2] = -lLg*1.4;


	lVect->getTransf().TransfDouble3::get( ANGLE ) [1] = -90;
	lVect->setRadius( pSz*3 );

	return lVect;
}
//----------------------------------------------
ObjVect*
ShipsMaker::makeShip2( float pSz, Sprite3dObj* pSp, int pNiveau )
{
	EnumWeapons lWeapon1 = WEAPON_MICRO_PLASMA;

	if( pNiveau == 1 ){
		lWeapon1 = WEAPON_PLASMA;
	} else
	if( pNiveau >=  2 ){
		lWeapon1 = WEAPON_PLASMA2;
	}




	ObjVect *lVect = makeShip1( pSz, pSp, lWeapon1, pNiveau );
	float lLg = pSz*1.8;

	O3dObj* lSoute = makeSoute( pSz*0.5,  lLg );
	lSoute->MkGetPOS()[2] = -lLg*1.6;
	lSoute->MkGetPOS()[1] = pSz*0.7;
	lVect->add( lSoute );

	lSoute = makeSoute( pSz*0.5,  lLg );
	lSoute->MkGetPOS()[2] = -lLg*1.6;
	lSoute->MkGetPOS()[1] = -pSz*0.7;
	lVect->add( lSoute );

	return lVect;
}
//----------------------------------------------
ObjVect*
ShipsMaker::makeShip3( float pSz, Sprite3dObj* pSp, int pNiveau )
{
	EnumWeapons lWeapon1 = WEAPON_MICRO_PLASMA;
	EnumWeapons lWeapon2 = WEAPON_SMALL_ROCKET;

	if( pNiveau == 1 ){
		lWeapon1 = WEAPON_PLASMA;
		lWeapon2 = WEAPON_ROCKET;
	} else
	if( pNiveau ==  2 ){
		lWeapon1 = WEAPON_PLASMA2;
		lWeapon2 = WEAPON_BIG_ROCKET;
	} else
	if( pNiveau >=  3 ){
		lWeapon1 = WEAPON_PLASMA_RED;
		lWeapon2 = WEAPON_SMALL_MISSILE;
	}


	ObjVect *lVect = makeShip1( pSz, pSp, lWeapon1, pNiveau );
	float lLg = pSz*4;

	O3dObj* lGrid1 = makeGrid( pSz*0.5,  lLg );
	lGrid1->MkGetPOS()[2] = -lLg*0.5;
	lGrid1->MkGetPOS()[0] = -lLg*0.5;
	lGrid1->MkGetANGLE()[1] = 90;
	lVect->add( lGrid1 );



	Tourelle* lMod1  = makeModul( pSz*0.8 );
	T3dBox lBox( -100, -100, -100,0,   100, 100 );
	lMod1->set( pSp,  0.7,  FIRE_DIRECT, lWeapon2,
							lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);

	lMod1->MkGetPOS()[2] = -lLg*0.5;
	lMod1->MkGetPOS()[0] = -lLg*0.5;
	lVect->add( lMod1 );

	Tourelle* lMod2  = makeModul( pSz*0.8 );
	lMod2->set( pSp, 0.71,  FIRE_DIRECT, lWeapon2,
							lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);

	lMod2->MkGetPOS()[2] = -lLg*0.5;
	lMod2->MkGetPOS()[0] =  lLg*0.5;
	lVect->add( lMod2 );


	return lVect;
}
//----------------------------------------------
ObjVect*
ShipsMaker::makeInterceptor( float pSz, Sprite3dObj* pSp, int pNiveau )
{
	EnumWeapons lWeapon1 = WEAPON_MICRO_PLASMA;

	if( pNiveau == 1 ){
		lWeapon1 = WEAPON_PLASMA;
	} else
	if( pNiveau >=  2 ){
		lWeapon1 = WEAPON_PLASMA2;
	}

	ObjVect *lVect = new ObjVect();

	O3dObj* lFan1 = makeFan(pSz, 0, 6);
	lFan1->MkGetPOS()[2] = pSz;

	lVect->add( lFan1 );

	O3dObj* lFan2 = makeFan( pSz, 0, 6);
	lFan2->MkGetPOS()[2] = -pSz;
	lVect->add( lFan2 );

	O3dObj* lGrid1 = makeGrid( pSz*0.2,  2*pSz );
	lGrid1->MkGetPOS()[2] = -pSz;
	lVect->add( lGrid1 );

	O3dObj* lGrid2 = makeGrid( pSz*0.2,  2*pSz );
	lGrid2->MkGetANGLE() [1] = 90;
	lGrid2->MkGetPOS()[0] = -pSz;
	lVect->add( lGrid2 );

	O3dObj* lReact = makeReactor( pSz*0.5);
	lReact->MkGetANGLE() [1] = 90;
	lReact->MkGetPOS()[0] = -pSz;
	lVect->add( lReact  );


	Tourelle* lMod1 = makeModul( pSz*0.4 );
	T3dBox lBox( -150, -20,  -100, 0, 20,   100 );
	lMod1->set( pSp, 0.2, FIRE_FRONT, lWeapon1,
							lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);
	lMod1->MkGetPOS()[0] = pSz;


	lVect->add( lMod1 );
	lVect->setRadius( pSz*2 );

	lVect->MkGetANGLE()[1] = 180;


	return lVect;
}
//----------------------------------------------
ObjVect*
ShipsMaker::makeTorpilleur( float pSz, Sprite3dObj* pSp, int pNiveau )
{
	EnumWeapons lWeapon1 = WEAPON_MICRO_PLASMA;
	EnumWeapons lWeapon2 = WEAPON_SMALL_ROCKET;

	if( pNiveau == 1 ){
		lWeapon1 = WEAPON_PLASMA;
	} else
	if( pNiveau >=  2 ){
		lWeapon1 = WEAPON_PLASMA2;
	}


	ObjVect *lVect = new ObjVect();

	O3dObj*lCone = new O3dObjPrim( O3dObjPrim::PrimCone, pSz*0.5, 5, 5, pSz*0.5*1.5 );
	lCone->setObjProps( &cPropsBody );
	lVect->add( lCone );
	O3dObj*lCone2 = new O3dObjPrim( O3dObjPrim::PrimCone, pSz*0.4, 6, 6, pSz*0.4*1.5 );
	lCone2->setObjProps( &cPropsGrid );
	//	lCone2->MkGetPOS()[2] = -pSz*0.5;
	lCone2->MkGetANGLE()[1] = 180;
	lVect->add( lCone2 );

	O3dObj*lCone3 = new O3dObjPrim( O3dObjPrim::PrimCone, pSz*0.4, 6, 5, pSz*0.8 );
	lCone3->setObjProps( &cPropsGrid );
	lCone3->MkGetPOS()[2] = -pSz*1.4;
	lVect->add( lCone3 );



	O3dObj* lSoute = makeSoute( pSz*0.2,  pSz*1.2 );
	lSoute->MkGetPOS()[2] = -pSz;
	//	lSoute->MkGetPOS()[1] = pSz*0.7;
	lVect->add( lSoute );

	O3dObj* lReact1 = makeReactor( pSz*0.35);
	lReact1->MkGetPOS()[0] = -pSz*0.45;
	lReact1->MkGetPOS()[2] = -pSz*1.5;
	lVect->add( lReact1  );

	O3dObj* lReact2 = makeReactor( pSz*0.35);
	lReact2->MkGetPOS()[0] = pSz*0.45;
	lReact2->MkGetPOS()[2] = -pSz*1.5;
	lVect->add( lReact2  );


	Tourelle* lMod1 = makeModul( pSz*0.25 );
	T3dBox lBox( -150, -20,  -100, 0, 20,   100 );
	lMod1->set( pSp, 0.4, FIRE_FRONT, lWeapon1,
							lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);

	lMod1->MkGetPOS()[1] = -pSz*0.3;
	lMod1->MkGetPOS()[2] = -pSz*0.3;

	lVect->add( lMod1  );

	Tourelle* lMod2 = makeModul( pSz*0.25 );
	lMod2->set( pSp, 0.4, FIRE_FRONT, lWeapon1,
							lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);

	if( pNiveau >= 2 ){
		Tourelle* lMod3 = makeModul( pSz*0.3 );
		lMod3->set( pSp, 0.4, FIRE_FRONT, lWeapon2,
								lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut);
		lMod3->MkGetPOS()[1] = pSz*0.3;
		lMod3->MkGetPOS()[2] = pSz*0.3;
	}


	lMod2->MkGetPOS()[1] = pSz*0.3;
	lMod2->MkGetPOS()[2] = -pSz*0.3;

	lVect->add( lMod2  );



	lVect->setRadius( pSz*1.5 );

		lVect->MkGetANGLE()[1] = -90;
		//	lVect->MkGetANGLE()[2] = 90;


	return lVect;
}
//----------------------------------------------
ObjVect*
ShipsMaker::makeMegaCroiseur(float pSz, Sprite3dObj* pSp, int pNiveau)
{
	EnumWeapons lWeapon0 = WEAPON_MICRO_PLASMA;
	EnumWeapons lWeapon1 = WEAPON_PLASMA_RED;
	EnumWeapons lWeapon2 = WEAPON_SMALL_ROCKET;
	EnumWeapons lWeapon3 = WEAPON_SMALL_MISSILE;

 	if( pNiveau == 1 ){
		lWeapon0 = WEAPON_PLASMA;
		lWeapon1 = WEAPON_PLASMA_GREEN;
		lWeapon2 = WEAPON_ROCKET;
		lWeapon3 = WEAPON_MISSILE;
	} else
	if( pNiveau >=  2 ){
		lWeapon0 = WEAPON_PLASMA2;
		lWeapon1 = WEAPON_PLASMA_BLUE;
		lWeapon2 = WEAPON_BIG_ROCKET;
		lWeapon3 = WEAPON_BIG_MISSILE;
	}

	ObjVect *lVect = new ObjVect();
	lVect->setObjProps( &cPropsFlamme );



	// Cores

	O3dObj* lCore = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 12, 15 );
	lCore->MkGetSCALE()[0] =2;
	lCore->MkGetSCALE()[1] =0.5;
	lCore->MkGetSCALE()[2] =0.5;
	lVect->add( lCore );

	O3dObj* lCore2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 12, 15 );
	lCore2->MkGetSCALE()[0] =1.5;
	lCore2->MkGetSCALE()[1] =0.4;
	lCore2->MkGetSCALE()[2] =1.0;
	lCore2->MkGetPOS()[0] = pSz*0.3;
	lVect->add( lCore2 );

	O3dObj* lCore3 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 9, 12 );
	lCore3->MkGetSCALE()[0] =1.0;
	lCore3->MkGetSCALE()[1] =1.0;
	lCore3->MkGetSCALE()[2] =0.5;
	lCore3->MkGetPOS()[0] = pSz*0.3;
	lCore3->MkGetPOS()[1] = -pSz*0.4;
	lVect->add( lCore3 );

	lCore3 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 9, 12 );
	lCore3->MkGetSCALE()[0] =1.0;
	lCore3->MkGetSCALE()[1] =1.0;
	lCore3->MkGetSCALE()[2] =0.5;
	lCore3->MkGetPOS()[0] = pSz*0.3;
	lCore3->MkGetPOS()[1] = pSz*0.4;
	lVect->add( lCore3 );

// Tourelles
	T3dBox lBoxFire( -120, -120, -120, 120,  120,  120 );
	Tourelle* lTour ;

    lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 0.5, FIRE_FRONT, lWeapon0,
							lBoxFire, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[0] = -pSz*2;
	lVect->add(  lTour );
    lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 0.5, FIRE_FRONT, lWeapon0,
							lBoxFire, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[1] = pSz;
	lVect->add(  lTour );
    lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 0.5, FIRE_FRONT, lWeapon0,
							lBoxFire, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[1] = pSz*1.5;
	lVect->add(  lTour );


    lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 1.0, FIRE_DIRECT, lWeapon1,
							lBoxFire, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[0] = -pSz;
	lTour->MkGetPOS()[1] = -pSz;
	lVect->add(  lTour );


    lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 1.5, FIRE_FRONT, lWeapon2,
							lBoxFire, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[0] = pSz;
	lVect->add(  lTour );


    lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 1.5, FIRE_DIRECT, lWeapon3,
							lBoxFire, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[0] = pSz;
	lTour->MkGetPOS()[1] = pSz;
	lVect->add(  lTour );






	// Domes

	O3dObj* lDome = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*0.3, 7, 7 );
	lDome->setObjProps( &cPropsDome );
	lDome->MkGetSCALE()[0] =1.5;
	lDome->MkGetPOS()[0] = pSz*0.5;
	lDome->MkGetPOS()[1] = pSz*0.3;
	lDome->MkGetPOS()[2] = pSz*0.6;
	lVect->add( lDome );

	lDome = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*.3, 7, 7 );
	lDome->setObjProps( &cPropsDome );
	lDome->MkGetSCALE()[0] =1.5;
	lDome->MkGetPOS()[0] = pSz*0.5;
	lDome->MkGetPOS()[1] = pSz*0.3;
	lDome->MkGetPOS()[2] = -pSz*0.6;
	lVect->add( lDome );


	lDome = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*.3, 7, 7 );
	lDome->setObjProps( &cPropsDome );
	lDome->MkGetSCALE()[0] =1.5;
	lDome->MkGetPOS()[0] = -pSz*1.2;
	lDome->MkGetPOS()[1] = -pSz*0.3;
	lDome->MkGetPOS()[2] = 0;
	lVect->add( lDome );

	lDome = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*0.5, 7, 7 );
	lDome->setObjProps( &cPropsDome );
	lDome->MkGetSCALE()[0] =1.5;
	lDome->MkGetSCALE()[2] =2;
	lDome->MkGetPOS()[0] = pSz*0.3;
	lDome->MkGetPOS()[1] = -pSz*0.7;
	lDome->MkGetPOS()[2] = 0;
	lVect->add( lDome );

	lDome = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*.3, 7, 7 );
	lDome->setObjProps( &cPropsDome );
	lDome->MkGetSCALE()[0] =1.5;
	lDome->MkGetPOS()[0] = pSz*0.4;
	lDome->MkGetPOS()[1] = pSz*0.3;
	lDome->MkGetPOS()[2] = pSz*-0.4;
	lVect->add( lDome );                     // phi 20111123 modif
	////	lVect->add( lDome );

	// Quilles

	O3dObj* lQuille = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 10, 13 );
	lQuille->MkGetSCALE()[0] =1.5;
	lQuille->MkGetSCALE()[1] =0.5;
	lQuille->MkGetSCALE()[2] =0.2;

	lQuille->MkGetANGLE() [2] = -120;
	lQuille->MkGetPOS()[0] = pSz*0.5;
	lQuille->MkGetPOS()[1] = -pSz*1.3;

	lVect->add( lQuille );

	O3dObj* lQuille2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz/2, 8, 11 );
	lQuille2->MkGetSCALE()[0] =1;
	lQuille2->MkGetSCALE()[1] =0.2;
	lQuille2->MkGetSCALE()[2] =0.5;

	//	lQuille->MkGetANGLE() [2] = 120;
	lQuille2->MkGetPOS()[0] = 0;
	lQuille2->MkGetPOS()[1] = -pSz*2.2;
	lVect->add( lQuille2 );



	lQuille = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 10, 13 );
	lQuille->MkGetSCALE()[0] =1.5;
	lQuille->MkGetSCALE()[1] =0.5;
	lQuille->MkGetSCALE()[2] =0.2;

	lQuille->MkGetANGLE() [2] = 120;
	lQuille->MkGetPOS()[0] = pSz*0.5;
	lQuille->MkGetPOS()[1] = pSz*1.3;

	lVect->add( lQuille );

    lQuille2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz/2, 8, 11 );
	lQuille2->MkGetSCALE()[0] =1;
	lQuille2->MkGetSCALE()[1] =-0.2;
	lQuille2->MkGetSCALE()[2] =0.5;

	//	lQuille->MkGetANGLE() [2] = 120;
	lQuille2->MkGetPOS()[0] = 0;
	lQuille2->MkGetPOS()[1] = pSz*2.2;
	lVect->add( lQuille2 );




	lVect->setRadius( pSz*2);

	lVect->MkGetANGLE()[0] = randp(180);
	lVect->MkGetSCALE()[0] =1.1;
	lVect->MkGetSCALE()[1] =0.9;
	lVect->MkGetSCALE()[2] =0.9;


	return lVect;

}
//----------------------------------------------
// Vaiseau lenticulaire tres reactif fortement arme

ObjVect*
ShipsMaker::makeCroiseur( float pSz, Sprite3dObj* pSp, int pNiveau)
{
	EnumWeapons lWeapon1 = WEAPON_PLASMA_RED;
	EnumWeapons lWeapon2 = WEAPON_SMALL_ROCKET;

	ObjVect *lVect = new ObjVect();

	O3dObj* lCore = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 9, 12 );
	lCore->MkGetSCALE()[1] =0.25;
	lCore->MkGetSCALE()[0] =1.25;
	lVect->add( lCore );

	lCore->setObjProps( &cPropsSpin );

	if( pNiveau <= 1 ){
		lWeapon1 = WEAPON_PLASMA_GREEN;
		lCore->setObjProps( &cPropsMaille );
	} else
	if( pNiveau >= 5  ){
		lWeapon1 = WEAPON_ION;
		lWeapon2 = WEAPON_MISSILE;
		lCore->setObjProps( &cPropsBlindage );
	} else
	if( pNiveau >= 4  ){
		lWeapon1 = WEAPON_ION;
		lWeapon2 = WEAPON_SMALL_MISSILE;
		lCore->setObjProps( &cPropsBlindage );
	} else
	if( pNiveau >= 3  ){
		lWeapon1 = WEAPON_PLASMA_BLUE;
		lWeapon2 = WEAPON_ROCKET;
		lCore->setObjProps( &cPropsBlindage );
	} else
	if( pNiveau >=  2 ){
		lWeapon1 = WEAPON_PLASMA_BLUE;
		lCore->setObjProps( &cPropsBlindage );
	} 



//	O3dObj* lCore2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz+2, 9, 12 );
//	lCore2->setObjProps( &cPropsDome );
//	lCore2->MkGetSCALE()[1] =0.25;
//	lCore2->MkGetSCALE()[0] =1.25;
//	lVect->add( lCore2 );


	T3dBox lBox2( -120, -120, -120, 120,  120,  120 );

	Tourelle* lMod1 = makeModul( pSz*0.15 );
	lMod1->set( pSp, 1.0, FIRE_DIRECT, lWeapon1,
							lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lMod1->MkGetPOS()[2] = pSz;
	lVect->add(  lMod1 );

	if( pNiveau > 1 ){
		Tourelle* lMod2 = makeModul( pSz*0.2);
		lMod2->set( pSp, 0.8, FIRE_DIRECT, lWeapon1,
								lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lMod2->MkGetPOS()[2] = -(pSz);
		lVect->add(  lMod2 );
	}
	if( pNiveau > 2 ){
		Tourelle* lMod2 = makeModul( pSz*0.3);
		lMod2->set( pSp, 0.7, FIRE_DIRECT, lWeapon2,
								lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lMod2->MkGetPOS()[0] = -(pSz);
		lVect->add(  lMod2 );
	}

	lVect->setRadius( pSz +2);


	return lVect;
}
//----------------------------------------------
// Plus lent mais mieux arme que le torpilleur
// et protege par un champ de force

ObjVect*
ShipsMaker::makeCuirasse( float pSz, Sprite3dObj* pSp, int pNiveau)
{
	EnumWeapons lWeapon1 = WEAPON_PLASMA_RED;
	EnumWeapons lWeapon2 = WEAPON_SMALL_MISSILE;

	if( pNiveau == 1 ){
		lWeapon1 = WEAPON_PLASMA_GREEN;
		lWeapon2 = WEAPON_MISSILE;
	} else
	if( pNiveau ==  2 ){
		lWeapon1 = WEAPON_PLASMA_BLUE;
		lWeapon2 = WEAPON_BIG_MISSILE;
	}
	else
	if( pNiveau >=  2 ){
		lWeapon1 = WEAPON_ION;
		lWeapon2 = WEAPON_BIG_MISSILE;
	}

	ObjVect *lVect = new ObjVect();

	O3dObj* lCore = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz, 9, 12 );
	lCore->setObjProps( &cPropsBlindage );
	lCore->MkGetANGLE()[1] = 90;
	lVect->add( lCore );

	O3dObj* lCore2 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz+2, 9, 12 );
	lCore2->setObjProps( &cPropsGrid );
	lCore2->MkGetANGLE()[1] = 90;
	lVect->add( lCore2 );

	O3dObj* lCore3 = new O3dObjPrim( O3dObjPrim::PrimSphere, pSz+3, 9, 12 );
	lCore3->setObjProps( &cPropsDome );
	lVect->add( lCore3 );


	T3dBox lBox2( -100, -100, -100, 100,  100,  100 );
	T3dBox lBox3( -60, -60, -60, 60,  60,  60 );

	Tourelle* lTour = makeModul( pSz*0.1 );
	lTour->set( pSp, 0.4, FIRE_DIRECT, lWeapon1,
							lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->MkGetPOS()[0] = pSz;
	lVect->add(  lTour );

	if( pNiveau > 0  && pNiveau <= 2 ){
		lTour = makeModul( pSz*0.1 );
		lTour->set( pSp, 0.4, FIRE_DIRECT, lWeapon1,
								lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[0] = -pSz;
		lTour->MkGetPOS()[0] = -pSz;
		lVect->add(  lTour );
	}

	if( pNiveau > 1 && pNiveau <= 2 ){ 
		lTour = makeModul( pSz*0.15 );
		lTour->set( pSp, 1.0, FIRE_DIRECT, lWeapon2,
							lBox3, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
		lTour->MkGetPOS()[0] = -pSz;
		lVect->add(  lTour );
	}

	if( pNiveau > 1 && pNiveau < 3 ){
		lTour = makeModul( pSz*0.15 );
		lTour->set( pSp, 1.0, FIRE_DIRECT, lWeapon2,
								lBox3, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
		lTour->MkGetPOS()[0] = -pSz;
		lVect->add(  lTour );
	}
	if( pNiveau > 2  && pNiveau <= 3  ){
		lTour = makeModul( pSz*0.15 );
		lTour->set( pSp, 1.0, FIRE_DIRECT, lWeapon2,
								lBox3, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
		lTour->MkGetPOS()[0] = -pSz;
		lVect->add(  lTour );

	if( pNiveau >= 3 ){
		lTour = makeModul( pSz*0.15 );
		lTour->set( pSp, 1.0, FIRE_DIRECT, lWeapon2,
								lBox3, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
		lTour->MkGetPOS()[0] = -pSz;
		lVect->add(  lTour );
	}
	if( pNiveau >= 4 ){
		lTour = makeModul( pSz*0.15 );
		lTour->set( pSp, 1.0, FIRE_DIRECT, lWeapon2,
								lBox3, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
		lTour->MkGetPOS()[0] = -pSz;
		lVect->add(  lTour );
	}
	}

//	lVect->MkGetANGLE()[0] = 90;

	lVect->setRadius( pSz+3 );

	return lVect;
}
//----------------------------------------------------
// Tres lourdement arme et protege par un champ de force !!!

ObjVect*
ShipsMaker::makeBaseTore( float pSz, Sprite3dObj* pSp, int pNiveau)
{
	EnumWeapons lWeapon1 = WEAPON_MICRO_PLASMA;
	EnumWeapons lWeapon2 = WEAPON_PLASMA_RED;
	EnumWeapons lWeapon3 = WEAPON_SMALL_MISSILE;

	if( pNiveau == 1 ){
		lWeapon1 = WEAPON_PLASMA;
		lWeapon2 = WEAPON_PLASMA_GREEN;
		lWeapon3 = WEAPON_MISSILE;
	} else
		if( pNiveau >=  3 ){
		lWeapon1 = WEAPON_ION;
		lWeapon2 = WEAPON_PLASMA_BLUE;
		lWeapon3 = WEAPON_BIG_MISSILE;
	 }
		else
			if( pNiveau >=  2 ){
		lWeapon1 = WEAPON_PLASMA2;
		lWeapon2 = WEAPON_PLASMA_BLUE;
		lWeapon3 = WEAPON_BIG_MISSILE;
	}
	



	ObjVect *lVect = new ObjVect();

	O3dObj* lTore = new O3dObjPrim( O3dObjPrim::PrimTorus, pSz, 9, 20, pSz*0.2 );
	lTore->setObjProps( &cPropsGrid );
	lVect->add( lTore );

	O3dObj* lTore2 = new O3dObjPrim( O3dObjPrim::PrimTorus, pSz*0.96, 9, 20, pSz*0.1 );
	lTore2->setObjProps( &cPropsModul );
	lVect->add( lTore2 );




	O3dObj *lGrid = new O3dObjPrim( O3dObjPrim::PrimCylinder, pSz*0.1, 5, 5, pSz, pSz*0.1);
	lGrid->setObjProps( &cPropsGrid );
	lGrid->MkGetANGLE()[0] = 90;
	lVect->add( lGrid);

	O3dObj *lGrid2 = new O3dObjPrim( O3dObjPrim::PrimCylinder, pSz*0.03, 5, 5, pSz, pSz*0.1);
	lGrid2->setObjProps( &cPropsSoute );
	lGrid2->MkGetANGLE()[0] = 90;
	lVect->add( lGrid2 );
//	lSoute->MkGetPOS()[0] = pSz;

	T3dBox lBox( -150, -150, -100, 150,  150,  100 );
	T3dBox lBox2( -100, -100, -100, 100,  100,  100 );

	Tourelle *lTour = new Tourelle();
	lTour->add( new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*0.3, 7, 7 ));
	lTour->setObjProps( &cPropsModul );
	lTour->set( pSp,  0.5, FIRE_DIRECT, lWeapon1,
							 lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lVect->add( lTour );

	lTour = new Tourelle();
	lTour->add( new O3dObjPrim( O3dObjPrim::PrimSphere, pSz*0.3, 7, 7 ));
	lTour->setObjProps( &cPropsModul );
	lTour->set( pSp,  0.5, FIRE_DIRECT, lWeapon1,
							 lBox, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->getTransf().TransfDouble3::get( POS )[0] = -pSz;
	lVect->add( lTour );


	lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 0.2, FIRE_DIRECT, lWeapon2,
							lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
	lVect->add(  lTour );


	lTour = makeModul( pSz*0.2 );
	lTour->set( pSp, 0.2, FIRE_DIRECT, lWeapon3,
							lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
	lTour->getTransf().TransfDouble3::get( POS )[0] = -pSz;
	lTour->getTransf().TransfDouble3::get( POS )[1] = -pSz;
	lVect->add(  lTour );

	if( pNiveau >= 2 ){
		lTour = makeModul( pSz*0.2 );
		lTour->set( pSp, 0.2, FIRE_DIRECT, lWeapon1,
								lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = pSz;
		lVect->add(  lTour );
	}
	if( pNiveau >= 3 ){
		lTour = makeModul( pSz*0.2 );
		lTour->set( pSp, 0.2, FIRE_DIRECT, lWeapon3,
								lBox2, InteractWeaponEnemyIn, InteractWeaponEnemyOut );
		lTour->getTransf().TransfDouble3::get( POS )[1] = pSz;
		lVect->add(  lTour );
	}

	lVect->setRadius( pSz );

	return lVect;
}
//--------------------------------------------------
//---------------- Creation Haut niveau ------------
//--------------------------------------------------
Sprite3d*
ShipsMaker::makeShip( ShipType pShipType, int pMaxLife, float  pSpin,
											float pMaxSpeed, float pMaxDeltaV, float pReactivity, int pNiveau,
											ShipAction pShipAction )
{
	Double3 lSpin( pSpin, 0, 0);

	Sprite3dObj* lSp = new Sprite3dObj();

	O3dObj* lObj=NULL;
	switch( pShipType  )
		{
		case SHIP1 : lObj =  makeShip1( 3, lSp, WEAPON_PLASMA, pNiveau  );
			break;

		case SHIP2 : lObj =  makeShip2( 3, lSp, pNiveau );
			break;

		case SHIP3 : lObj =  makeShip3( 3, lSp, pNiveau );
			break;

		case INTERCEPTOR : lObj =  makeInterceptor( 3, lSp, pNiveau );
			break;

		case TORPILLEUR : lObj =  makeTorpilleur( 6+pNiveau*0.5, lSp, pNiveau );
			break;

		case CROISEUR : lObj =  makeCroiseur( 5+pNiveau, lSp, pNiveau );
			break;

		case CUIRASSE : lObj  =  makeCuirasse( 9+pNiveau*2, lSp, pNiveau );
			break;

		case BASE_TORE : lObj =  makeBaseTore( 16+pNiveau, lSp, pNiveau );
			break;

		case MEGA_CROISEUR : lObj =  makeMegaCroiseur( 10+pNiveau, lSp, pNiveau );
		lSpin[0]= pSpin*4;
			break;


		default:
			std::cout << "ShipsMaker::makeShip Unkonw type " << pShipType << std::endl;
			exit(1);
		}
	lSp->setO3dObj( lObj );

	lSp->setMask( InteractWeaponEnemyIn, InteractWeaponEnemyOut);
	lSp->setAction( SPRITE_ACTION_COLLISION, TheShipsMaker );
	lSp->setAction( SPRITE_ACTION_ANIMATE, TheShipsMaker );


	lSp->SpriteFloat::set( SPRITE_LIFE_POINT, pMaxLife );
	lSp->SpriteFloat::set( SPRITE_MAX_LIFE_POINT, pMaxLife );
	lSp->SpriteFloat::set( SPRITE_DESTROY_POINT, pMaxLife/1.5 );

	lSp->SpriteLong::set(  SPRITE_TYPE, ALIEN_SHIP );
	lSp->SpriteDouble3::set( SPRITE_SPIN, lSpin  );

	lSp->SpriteFloat::set( SHIP_MAX_SPEED,   pMaxSpeed );
	lSp->SpriteFloat::set( SHIP_MAX_DELTA_V, pMaxDeltaV );
	lSp->SpriteFloat::set( SHIP_REACTIVITY,  pReactivity );

	lSp->SpriteFloat::set( SHIP_ACTION, pShipAction );


	lSp->setDeepDestroy(GL_TRUE);

	return lSp;
}

//**************************
