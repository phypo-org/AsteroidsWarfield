#include <stdlib.h>

#include <T3d/T3dLoadImg.h>
#include <T3d/T3dColor.h>

#include <O3d/O3dObjPrim.h>
#include <O3d/O3dObjText.h>

#include <Sprite3d/ObjOdron.h>
#include <Sprite3d/World.h>
#include <Sprite3d/ObjText2d.h>
#include <Sprite3d/ObjText.h>

#include <U3d/WeaponsMaker.h>



#include <Space/Pilot.h>
#include <Space/SceneAsteroide.h>
#include <Space/ShipsMaker.h>
#include <Space/Def.h>
#include <Space/WorldGame.h>
#include <U3d/Sky.h>

#include <iostream>

#include <U3d/Banniere.h>

#include "Help.h"


#include <O3d/O3dObjPLibFont.h>


//**************************************
Help::Help( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,
            O3dObjProps *pProps)
  :World(pControl, pKamera, pMax, pProps)	,
   cSize( pSize ),
   cColorTextNormal( 1.0, 1.0, 1.0, 1.0 )
{
  cPropsTextNormal.ObjPropsFloat4::set( MATERIAL, cColorTextNormal );
}
//-----------------------------
void
Help::mouseMove( int pX, int pY )
{
  //  std::cout << "Help::mouseMove" << std::endl;
}
//-----------------------------
void
Help::mouseButton( int pButton, int pState, int pX, int pY)
{
  /*
    Double3 lPos;
    Double3 lResult;
    WorldControler::GetCurrentWorld()->getKamera()->getProject( WorldControler::GetCurrentWorld()->getPilot()->getTransf().get( POS),  lPos );
    lPos[0] = pX;
    lPos[1] = pY;

    WorldControler::GetCurrentWorld()->getKamera()->getUnProject( lPos, lResult );

    std::cout << "Help::mouseButton:" << pX << " " << pY << " -> "
    <<  lResult[0] << "," << lResult[1] << "," << lResult[2] << std::endl;

    Sprite3d* lSprite =  isSpriteIntersect( lResult, 5, InteractObstacle );
    if( lSprite != NULL ) {
    std::cout << ">>>>Sprite:" << lSprite << std::endl;
    std::cout << lSprite->fireUserAction( (void*)1, (void*)2 )<< std::endl;
    }
  */
}
//-----------------------------
long
Help::userAction( Sprite3d &pMySprite, void*pParam0, void*pParam1, void*pParam2 )
{
  //	std::cout << "UserAction -> " << (char*) pParam0 << ":"<< (long) pParam1 << ":" <<  (long) pParam2 << std::endl;
  return 666;
}
//-----------------------------
/*void
  Help::AfficheLine( int pX, int pY, const char* pStr ){

  O3dObjText* lObjText = new O3dObjText( WorldControler::sCurrentFont, pStr );
  Sprite3dObj* lText = new  Sprite3dObj( lObjText );

  Double3 lPos( pX, pY, 0.0 );
  lText->getTransf().TransfDouble3::set( POS, lPos );

  lText->setObjProps( &cPropsTextNormal );
  add( lText );

  static fntTexFont  *sTimesRoman = NULL;

  if( sTimesRoman == NULL )
  sTimesRoman = new fntTexFont( "Times-Roman.txf" );

  O3dObjPLibFont* lObjText2 = new O3dObjPLibFont( *sTimesRoman, 4, pStr );

  //	O3dObjText2d* lObjText = new O3dObjText2d( WorldControler::sCurrentFont, 16, 3, pStr );
  Sprite3dObj* lText2 = new  Sprite3dObj( lObjText2 );yes


  Double3 lPos2( pX-30, pY, 0.0 );
  lText2->getTransf().TransfDouble3::set( POS, lPos2 );

  lText2->setObjProps( &cPropsTextNormal );
  add( lText2 );

  }
*/
//-----------------------------
void
Help::AfficheLine( int pX, int pY, const char* pStr ){

  //	std::string lName
 
	
  O3dObjPLibFont* lObjText = new O3dObjPLibFont(FL_HELVETICA_BOLD, 12, pStr );

  //	O3dObjText2d* lObjText = new O3dObjText2d( WorldControler::sCurrentFont, 16, 3, pStr );
  Sprite3dObj* lText = new  Sprite3dObj( lObjText );

  Double3 lPos( pX, pY, 0.0 );
  lText->getTransf().TransfDouble3::set( POS, lPos );

  cPropsTextNormal.ObjPropsFloat4::set( MATERIAL, cColorTextNormal );
  lText->setObjProps( &cPropsTextNormal );
  add( lText );
	
}
//-----------------------------
void
Help::makeAsteroide( EnumAsteroides pType, int pX, int pY, int pSz ){

  Sprite3d* lSp;
  Double3 lSpinAster( 10, -15, 5 );

  lSp=TheAsteroidesMaker->makeSpriteAsteroide( pType, pSz, 2 );
  lSp->MkSetSPIN( lSpinAster );
  lSp->MkGetPOS()[0] = pX;
  lSp->MkGetPOS()[1] = pY;
  lSp->MkGetPOS()[2] = 0;
  lSp->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Asteroide") );
  lSp->setAction( SPRITE_ACTION_COLLISION, NULL );
  lSp->setAction( SPRITE_ACTION_ANIMATE,   NULL );
  add( lSp );

}
//-----------------------------
void
Help::initSprite( Sprite3d* pSp, int pX, int pY )
{
  Double3 lTransfNull( 0, 0, 0 );

  pSp->MkSetSPEED( lTransfNull );
  Double3 pSpinAster( 10, 8, 9 );
  pSp->MkSetSPIN( pSpinAster );
  pSp->MkGetPOS()[0] = pX;
  pSp->MkGetPOS()[1] = pY;
  pSp->MkGetPOS()[2] = 0;
  //		pSp->setMask( InteractObstacle, InteractObstacle);
  pSp->setAction( SPRITE_ACTION_COLLISION, NULL );
  pSp->setAction( SPRITE_ACTION_ANIMATE, NULL );

  add( pSp );
}
//-----------------------------
void
Help::makeShip( ShipType pType, int pX, int pY, int pSz )
{
  Sprite3d* 	lSp = TheShipsMaker->makeShip( pType, 40, 100, 0, 0, 0, 1 );
  //		pSp->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Croiseur") );
  initSprite( lSp, pX, pY );
}
//-----------------------------
void
Help::makeBonus( EnumBonus pType, int pX, int pY, int pSz )
{
  Sprite3d* lSp = TheBonusMaker->makeSpriteBonus( 2, pType, 0, 0, 1);
  initSprite( lSp, pX, pY );
}
//-----------------------------
void
Help::makeMine( MineType pType, int pX, int pY, int pSz )
{
  Sprite3d* lSp = TheMinesMaker->makeMine( pType, 5, 0);
  initSprite( lSp, pX, pY );
}
//-----------------------------
void
Help::makeWeapon( EnumWeapons pType, int pX, int pY, int pSz )
{
  T3dTransf lTransfNull;

  Sprite3d* lSp = TheWeaponsMaker->makeSprite( &lTransfNull, pType, 0, 0 );
  initSprite( lSp, pX, pY );
}
//-----------------------------
GLboolean Help::initStart(int pNiveau, const char* pFile)
{
  add( new Sky( 10*cSize, cSize*100 ) );

  //	Sprite3d* lSp;



  int pX = -115;
  int pX2 = -40;
  int pY = 70 ; // 90;
  int lYStep = -25 ; //-30;
  int lXStep = 30;

  //	AfficheLine( pX, pY, "<<< All Object >>>" );
  //	pY += lYStep;

  {
    AfficheLine( pX, pY, "Asteroides" );


    int lSz= 10;
    int lX = pX2;

    makeAsteroide( ASTEROIDE_WATER, lX, pY, lSz );
    lX += lXStep;
    makeAsteroide( ASTEROIDE_ICE, lX, pY, lSz );
    lX += lXStep;
    makeAsteroide( ASTEROIDE_SNOW, lX, pY, lSz );
    lX += lXStep;
    makeAsteroide( ASTEROIDE_MARS, lX, pY, lSz );
    lX += lXStep;
    makeAsteroide( ASTEROIDE_PIERRE, lX, pY, lSz );
  }

  pY += lYStep;

  {
    int lX = pX2;
    AfficheLine( pX, pY, "Interceptor,Transport," );
    AfficheLine( pX, pY-6, "Escort, Destroyer," );
    AfficheLine( pX, pY-12, "Torpedo boat" );

    makeShip( INTERCEPTOR, lX, pY, 0 );
    lX += lXStep;
    makeShip( SHIP1, lX, pY, 0 );
    lX += lXStep;
    makeShip( SHIP2, lX, pY, 0 );
    lX += lXStep;
    makeShip( SHIP3, lX, pY, 0 );
    lX += lXStep;
    makeShip( TORPILLEUR, lX, pY, 0 );
  }

  pY += lYStep*1.5;

  {
    int lX = pX2;

    AfficheLine( pX, pY, "Cruiser,Dreadnought," );
    AfficheLine( pX, pY-6, "Starbase" ); //, Mother ship" );

    makeShip( CROISEUR, lX, pY, 0 );
    lX += lXStep*1.2;
    makeShip( CUIRASSE, lX, pY, 0 );
    lX += lXStep*1.6;
    makeShip( BASE_TORE, lX, pY, 0 );
    //		lX += lXStep*1.8;
    //		makeShip( MEGA_CROISEUR, lX, pY, 0 );
  }

  pY += lYStep;

  {
    int lX = pX2;
    AfficheLine( pX, pY, "Bonus : Energy,Rocket," );
    AfficheLine( pX, pY-6, "        Field,Upgrade" );
    makeBonus( CONTAINER_ERG, lX, pY, 0 );
    lX += lXStep/2;
    makeBonus( CONTAINER_ROCKET, lX, pY, 0 );
    lX += lXStep/2;
    makeBonus( CONTAINER_FIELD, lX, pY, 0 );
    lX += lXStep/2;
    makeBonus( CONTAINER_UPGRAD, lX, pY, 0 );
  }
  pY += lYStep;

  {
    int lX = pX2;
    AfficheLine( pX, pY, "Mines" );
    makeMine( MINE_1, lX, pY, 0 );
    lX += lXStep;
    makeMine( MINE_ION, lX, pY, 0 );
    lX += lXStep;
  }
  pY += lYStep;
  {
    int lX = pX2;
    AfficheLine( pX, pY, "Weapons" );
    makeWeapon( WEAPON_MICRO_PLASMA, lX, pY, 0 );
    lX += lXStep/3;
    makeWeapon( WEAPON_PLASMA, lX, pY, 0 );
    lX += lXStep/3;
    makeWeapon( WEAPON_PLASMA2, lX, pY, 0 );
    lX += lXStep/3;
    makeWeapon( WEAPON_PLASMA_RED, lX, pY, 0 );
    lX += lXStep/3;
    makeWeapon( WEAPON_PLASMA_GREEN, lX, pY, 0 );
    lX += lXStep/3;
    makeWeapon( WEAPON_PLASMA_BLUE, lX, pY, 0 );
    lX += lXStep/3;
    makeWeapon( WEAPON_ION, lX, pY, 0 );
    lX += lXStep>>1;
    makeWeapon( WEAPON_SMALL_ROCKET, lX, pY, 0 );
    lX += lXStep>>1;
    makeWeapon( WEAPON_ROCKET, lX, pY, 0 );
    lX += lXStep>>1;
    makeWeapon( WEAPON_BIG_ROCKET, lX, pY, 0 );
    lX += lXStep>>1;
  }


  //----- PILOT ----
  /*
    Sprite3dPilot *lPilot = new Sprite3dPilot(NULL) ; //Pilot();
    lPilot->getTransf().TransfDouble3::get(POS)[ 0 ] = -100;
    //  Double3 lGrow( 4, 4, 4 );
    //  lPilot->MkSetSCALE( lGrow );
    lPilot->setAction( SPRITE_ACTION_ANIMATE, NULL );
    lPilot->setAction( SPRITE_ACTION_COLLISION, NULL );
    lPilot->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Pilot") );
    lPilot->SpriteFloat::set( SPRITE_LIFE_POINT, 999999999 ); // Pour neutraliser les deplacement

    add( lPilot );
    setPilot( lPilot );
  */
  return GL_TRUE;
}

//**************************************

