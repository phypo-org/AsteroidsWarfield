#include <FL/glut.H>
#include "Pilot.h"

#include "T3d/T3dColor.h"
#include "T3d/T3dLoadImg.h"


#include "O3d/O3dObjPrim.h"
#include "O3d/O3dObjText.h"
#include "O3d/O3dObjPLibFont.h"

#include "Sprite3d/World.h"
#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Random.h"
#include "Sprite3d/WorldControler.h"
#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/SoundControler.h"

#include "U3d/WeaponsMaker.h"
#include "U3d/SpriteExplosion.h"
#include "U3d/BonusMaker.h"
#include "U3d/ObjPrimPart.h"

#include "Sprite3d/World.h"
#include "Sprite3d/ObjPart.h"
#include "Sprite3d/Random.h"
#include "Sprite3d/WorldControler.h"
#include "Sprite3d/ObjOdron.h"
#include "Sprite3d/SoundControler.h"

#include "U3d/WeaponsMaker.h"
#include "U3d/SpriteExplosion.h"
#include "U3d/BonusMaker.h"
#include "U3d/ObjPrimPart.h"
#include "U3d/Banniere.h"


#include "Space/WorldGame.h"

#include "WorldGame.h"
#include "Def.h"
#include <stdio.h>

#include <FL/Fl.H>

#define MAX_WEAPON_IN_USE 256

Pilot* Pilot::ThePilot = NULL;


//*************************************************

// Pour ne pas avoir a modifier le .h a chaque ajout de son
PSoundId Pilot::sSoundWarp          =PBadSoundId;
PSoundId Pilot::sSoundLaser         =PBadSoundId;
PSoundId Pilot::sSoundFireMissile   =PBadSoundId;
PSoundId Pilot::sSoundMotor =PBadSoundId;

// PAS FAIT
PSoundId Pilot::sSoundWarpFailed    =PBadSoundId;
PSoundId Pilot::sSoundCollision     =PBadSoundId;
PSoundId Pilot::sSoundFinalExplosion=PBadSoundId;
PSoundId Pilot::sSoundNextLife      =PBadSoundId;
PSoundId Pilot::sSoundBonus         =PBadSoundId;

//static PSoundId sMusicGameOver=PBadSoundId;

//-----------------------------------
bool
Pilot::InitSound()
{
  sSoundWarp        = SoundControler::LoadSampleConfig( "Pilot.SoundWarp" );
  sSoundLaser       = SoundControler::LoadSampleConfig( "Pilot.SoundLaser" );
  sSoundFireMissile = SoundControler::LoadSampleConfig( "Pilot.SoundFireMissile" );

  sSoundMotor = SoundControler::LoadSampleConfig( "Pilot.SoundMotor" );

  sSoundWarpFailed     = SoundControler::LoadSampleConfig( "Pilot.SoundWarpFailed" );
  sSoundCollision      = SoundControler::LoadSampleConfig( "Pilot.SoundCollision" );
  sSoundFinalExplosion = SoundControler::LoadSampleConfig( "Pilot.SoundFinalExplosion" );
  sSoundNextLife       = SoundControler::LoadSampleConfig( "Pilot.SoundNextLife" );
  sSoundBonus          = SoundControler::LoadSampleConfig( "Pilot.SoundBonus" );

  return true;
}
//-----------------------------------
static const char* sStrPilot = "(Pilot";
static const char* sStrLevPhaser ="LevelPhaser";
static const char* sStrLevLauncher ="LevelLauncher";
static const char* sStrLevField ="LevelField"; // lMaxField
static const char* sStrLevMotor ="LevelMotor";
static const char* sStrMaxErg ="MaxErg";
static const char* sStrMaxRocket ="MaxRocket";
static const char* sStrLife ="Life";
static const char* sStrField ="Field";
static const char* sStrErg ="Erg";
static const char* sStrRocket ="Rocket";
static const char* sStrScore ="Score";
static const char* sStrMoney ="Money";
//-----------------------------------

void Pilot::write( std::ostream & pOs){

  int lField = SpriteFloat::get( SPRITE_LIFE_POINT );
  int lMaxField = SpriteFloat::get( SPRITE_MAX_LIFE_POINT );


  pOs << sStrPilot << ' '
      << sStrLevPhaser << ' ' << cLevelPhaser << ' '
      << sStrLevLauncher << ' ' << cLevelLauncher << ' '
      << sStrLevField << ' '     << lMaxField << ' '
      << sStrLevMotor << ' ' << cLevelMotor << ' '
      << sStrMaxErg << ' ' << cMaxErg<< ' '
      << sStrMaxRocket << ' ' << cMaxRocket << ' '
      << sStrLife      << ' ' << cNbLife << ' '
      << sStrField << ' ' << lField << ' '
      << sStrRocket << ' ' << cRocket<< ' '
      << sStrErg     << ' ' << cErg<< ' '
      << sStrScore   << ' ' << cScore << ' '
      << sStrMoney   << ' ' << cGold << ' '
      << ")";
}
//-----------------------------------
bool Pilot::read( std::istream & pIs ){

  std::string lTmpStr;

  long  lErg=0;
  long  lRocket=0;
  long  lNbLife=0;
  //	long  lGold=0;
  long  lField=0;

  long  lMaxErg=0;
  long  lMaxRocket=0;

  long  lLevelPhaser=0;
  long  lLevelLauncher=0;

  long  lMaxField=0;
  long  lLevelMotor=0;
  long  lScore = 0;


  long  lMoney = 0;
  //	long  lLevelWarp;

  pIs >> lTmpStr;

  //    std::cout << "read [" << lTmpStr << ']' << std::endl;

  if( lTmpStr.compare( sStrPilot ) != 0 ){
    //			std::cout << "read Pilot header fail" << std::endl;
    return false;
  }

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrLevPhaser ) != 0 ){
    //			std::cout << "read Pilot LevelPhaser fail" << std::endl;
    return false;
  }
  pIs >> lLevelPhaser;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrLevLauncher ) != 0 ){
    //			std::cout << "read Pilot LevelLauncher fail" << std::endl;
    return false;
  }
  pIs >> lLevelLauncher;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrLevField ) != 0 ){
    //			std::cout << "read Pilot LevelField fail" << std::endl;
    return false;
  }
  pIs >> lMaxField;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrLevMotor ) != 0 ){
    //			std::cout << "read Pilot LevelMotor fail" << std::endl;
    return false;
  }
  pIs >> lLevelMotor;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrMaxErg ) != 0 ){
    //			std::cout << "read Pilot MaxErg fail" << std::endl;
    return false;
  }
  pIs >> lMaxErg;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrMaxRocket ) != 0 ){
    //			std::cout << "read Pilot MaxRocket fail" << std::endl;
    return false;
  }
  pIs >> lMaxRocket;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrLife ) != 0 ){
    //			std::cout << "read Pilot fail" << std::endl;
    return false;
  }
  pIs >> lNbLife;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrField ) != 0 ){
    //			std::cout << "read Pilot Field fail" << std::endl;
    return false;
  }
  pIs >> lField;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrRocket ) != 0 ){
    //			std::cout << "read Pilot Rocket fail" << std::endl;
    return false;
  }
  pIs >> lRocket;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrErg ) != 0 ){
    //			std::cout << "read Pilot fail" << std::endl;
    return false;
  }
  pIs >> lErg;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrScore ) != 0 ){
    //			std::cout << "read Pilot Score fail" << std::endl;
    return false;
  }
  pIs >> lScore;

  pIs >> lTmpStr;
  if( lTmpStr.compare( sStrMoney ) != 0 ){
    //			std::cout << "read Pilot Money fail" << std::endl;
    return false;
  }
  pIs >> lMoney;


  cErg =lErg;
  cRocket = lRocket;
  cNbLife = lNbLife;
  //cGold;

  SpriteFloat::set( SPRITE_LIFE_POINT, lField );

  cMaxErg = lMaxErg;
  cMaxRocket = lMaxRocket;

  cLevelPhaser = lLevelPhaser;
  cLevelLauncher = lLevelLauncher;

  SpriteFloat::set( SPRITE_MAX_LIFE_POINT, lMaxField );

  cLevelMotor = lLevelMotor;
  //cLevelWarp;

  cScore = lScore;

  cGold = lMoney;

  return true;
}
//**********************************************
Pilot::Pilot( )
  :Sprite3dPilot( NULL ),
   cErg(500),
   cRocket(100),
   cNbLife(3),
   cGold(0),
   cMaxErg(1000),
   cMaxRocket(200),

   cLevelPhaser(0),
   cLevelLauncher(0),
   cLevelField(0),
   cLevelMotor(0),
   cLevelWarp(0),
   cScore(0),

   cWarpBegin(GL_FALSE),
   cXDecalKamera(0.0),
   cYDecalKamera(0.0)
{




  Float4 colorWarp (0.3, 0.05, 0.5, 0.5);
  caPropsWarp= new O3dObjProps();
  caPropsWarp->ObjPropsFloat4::set( MATERIAL, colorWarp );
  caPropsWarp->ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);




  float lSz = 6.0f;

  setMask( InteractShipAlliedIn, InteractShipAlliedOut );
  SpriteFloat::set( SPRITE_LIFE_POINT,       200 );
  SpriteFloat::set( SPRITE_MAX_LIFE_POINT,   200 );

  SpriteFloat::set( SPRITE_DESTROY_POINT,    2.0 );
  SpriteLong::set(  SPRITE_TYPE, FRIEND_SHIP );


  setAction( SPRITE_ACTION_COLLISION, this );


  caObjVect = new ObjVect();
  this->setO3dObj( caObjVect );
  caObjVect->setRadius( lSz*0.9 );




  caTexCore = WorldGame::LoadTextureConfig("Pilot.TextureShip" ); // 38 9  53 63





  if( WorldControler::sDifficultyLevel != 2 )
    {
      switch( WorldControler::sDifficultyLevel )
        {
        case 0:
          cRocket *=4;
          cNbLife = 6;
          cErg=2000;
          cMaxErg=2000;
          cLevelPhaser=2;
          cLevelLauncher=2;
          cLevelField=2;
          cLevelMotor=2;
          SpriteFloat::set( SPRITE_LIFE_POINT,       600 );
          SpriteFloat::set( SPRITE_MAX_LIFE_POINT,   600 );
          break;
        case 1:
          cRocket *=2;
          cNbLife = 4;
          cErg=1000;
          cMaxErg=1000;
          cLevelPhaser=1;
          cLevelLauncher=1;
          cLevelField=1;
          cLevelMotor=1;
          SpriteFloat::set( SPRITE_LIFE_POINT,       400 );
          SpriteFloat::set( SPRITE_MAX_LIFE_POINT,   400 );
          break;
        case 3:
          cRocket /= 2;
          cNbLife = 1;
          break;
        case 4:
          cRocket /= 4;
          cNbLife = 0;
          break;
        default: ;
        }
    }





  // ========== SHIP =============
  Float4 p2 (0.3, 0.5, 0.9, 1.0);
  caPropsShip = new O3dObjProps();

  caPropsShip->setTexture( caTexCore );

  caPropsShip->ObjPropsFloat4::set( MATERIAL, p2 );
  //	caPropsShip->ObjPropsBool::set(DRAW_OBJ_SKELETON, 0);



  //	caObjShip = new O3dObjPrim(  O3dObjPrim::PrimSphere, 2, 5,  );
  //    caObjShip= new O3dObjPrim( O3dObjPrim::PrimCone, 5.0, 5, 5, 6.0 );

  O3dObj* lObj;
  ObjVect* lObjVectShip = new ObjVect();
  caObjShip = lObjVectShip;
  caSpriteShip = new Sprite3dObj( caObjShip );
  caObjVect->push_back( caSpriteShip );

  Double3 lSpin( 150, 0, 0);
  caSpriteShip->SpriteDouble3::set( SPRITE_SPIN,  lSpin );
  caSpriteShip->setObjProps( caPropsShip );



  lObj = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz, 9, 12 );
  lObj->MkGetSCALE()[1] =0.20;
  lObj->MkGetSCALE()[2] =0.9;
  lObjVectShip->push_back( lObj );


  Float4 p4 ( 0.8, 0.8, 1.0, 0.3);
  caPropsShield2 = new O3dObjProps();
  caPropsShield2->ObjPropsFloat4::set( MATERIAL, p4 );
  caPropsShield2->ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
  caPropsShield2->ObjPropsBool::set(DRAW_OBJ_SOLID, 1);


  lObj = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*0.3, 8, 8 );
  lObj->setObjProps( caPropsShield2 );
  lObj->MkGetSCALE()[2] =0.7;
  lObj->getTransf().TransfDouble3::get(POS)[0] = -lSz*0.4;
  lObj->getTransf().TransfDouble3::get(POS)[2] = lSz*0.7;
  lObjVectShip->push_back( lObj );

  lObj = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*0.3, 8, 8 );
  lObj->setObjProps( caPropsShield2 );
  lObj->MkGetSCALE()[2] =0.7;
  lObj->getTransf().TransfDouble3::get(POS)[0] = -lSz*0.4;
  lObj->getTransf().TransfDouble3::get(POS)[2] = -lSz*0.7;
  lObjVectShip->push_back( lObj );


  lObj = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*0.35, 8, 8 );
  lObj->setObjProps( caPropsShield2 );
  lObj->MkGetSCALE()[1] =0.8;
  lObj->MkGetSCALE()[2] =0.7;
  lObj->getTransf().TransfDouble3::get(POS)[0] = +lSz*0.8;
  lObjVectShip->push_back( lObj );

  lObj = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*0.65, 10, 6 );
  //	lObj->setObjProps( caPropsShield2 );
  lObj->getTransf().TransfDouble3::get(POS)[0] = -lSz*0.5;
  lObj->MkGetSCALE()[2] =0.5;
  lObjVectShip->push_back( lObj );




  // =========== FIRE ========== 
  caObjFire = new ObjPart( 1 );

  Double3 pos(5, 3, 3);
  caObjFire->ObjPartDouble3::set( PART_POSITION_RAND, pos );
  Double3 speed1(WorldGame::GlobalScroll, 0.5, 0.5);
  caObjFire->ObjPartDouble3::set( PART_SPEED, speed1 );
  Double3 speed2( 4, 0.5, 0.5 );
  caObjFire->ObjPartDouble3::set( PART_SPEED_RAND, speed2 );

  Double3 acc1( 0, 0, 0);
  caObjFire->ObjPartDouble3::set( PART_ACCELERATION, acc1 );
  Double3 acc2( 0.1, 0.1, 0.1);
  caObjFire->ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );

  caObjFire->ObjPartFloat::set( PART_SIZE_RAND, 1.5);
  caObjFire->ObjPartFloat::set( PART_GROW, -5);
  caObjFire->ObjPartFloat::set( PART_GROW_RAND, -3.5 );
  caObjFire->ObjPartInt::set( PART_GEN_NUMBER, 80 );

  Float4 color1( 0.1, 0.1, 0.9, 0.4 );
  Float4 color2( -0.1, -0.1, 0.15, -0.3);
  Float4 color3( 0.1, 0.1, 0.1, 0.2 );
  caObjFire->ObjPartFloat4::set( PART_COLOR, color1 );
  caObjFire->ObjPartFloat4::set( PART_COLOR_CHG, color2 );
  caObjFire->ObjPartFloat4::set( PART_COLOR_RAND, color3 );

  caObjFire->init( 1, 5.0, 6);
  caObjFire->getTransf().TransfDouble3::get( POS )[ 0 ] = -lSz*1.2;
  caSpriteFire = new Sprite3dObj(caObjFire);
  Double3 lSpin3( -50, 0, 0);
  caSpriteFire->SpriteDouble3::set( SPRITE_SPIN,  lSpin3);

  caObjVect->push_back( caSpriteFire );




  // =========== SHIELD =============
  Float4 p3 ( 0.1, 0.1, .1, 0.1);
  caPropsShield = new O3dObjProps();
  //	caPropsShield->ObjPropsFloat4::set( MATERIAL, p3 );
  caPropsShield->ObjPropsFloat4::set( EMISSION, p3 );

  caObjShield = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*1.2, 20, 15 );
  caObjShield->setObjProps( caPropsShield );
  caObjShield->setUseList( GL_FALSE);
  caObjVect->push_back( caObjShield );


  //	caPropsShield->ObjPropsFloat4::set( MATERIAL, p3 );
  /*
    Float4 p4 ( 0.0, 0.0, 1.0, 0.05);
    caPropsShield2->ObjPropsFloat4::set( EMISSION, p4 );
    caPropsShield2->ObjPropsBool::set(DRAW_OBJ_SKELETON, 1);
    caPropsShield2->ObjPropsBool::set(DRAW_OBJ_SOLID, 0);

    caObjShield2 = new O3dObjPrim( O3dObjPrim::PrimSphere, lSz*1.2, 6, 6 );
    caObjShield2->setObjProps( caPropsShield2 );
    caObjShield2->setUseList( GL_FALSE);
    caObjShield2->getTransf().TransfDouble3::get( ANGLE)[1] = 90;
    caObjShield2	->MkGetSCALE()[1] =0.20;
    caObjShield2	->MkGetSCALE()[2] =0.9;


    caSpriteShield = new Sprite3dObj( caObjShield2 );
    Double3 lD3( 0, 0, 360);
    caSpriteShield->SpriteDouble3::set( SPRITE_SPIN, lD3  );
    caSpriteShield->setUseList( GL_FALSE);
    caSpriteShield->SpriteDouble3::set( SPRITE_SPIN,  lSpin3);
    caObjVect->push_back( caSpriteShield );
  */

  ThePilot = this;



  //	 SoundControler::sTheSoundControler->playSample( sSoundMotor, 100, 1.0f, 1.0f, true);

  static bool sAlreadyPlay = false;
  if( sAlreadyPlay == false )
    {
      playSoundSource( sSoundMotor, 100, 1.0f, 1.0f, true);
      sAlreadyPlay= true;
    }


}
//------------------------

void
Pilot::scrollKamera()
{
  Double3& lD = getTransf().TransfDouble3::get( POS);
  O3dKamera& lKam= *(WorldControler::GetCurrentWorld()->getKamera());


  //  float lXThreshold = WorldGame::XSizeWorld*0.6;
  // float lYThreshold = WorldGame::YSizeWorld*0.35; // 
  float lXThreshold = WorldGame::XSizeWorld*0.7;
  float lYThreshold = WorldGame::YSizeWorld*0.3; 
  
  
  //  float lYLimit = 0.8;
  float lYLimit = 20;
  float lXLimitLeft  =-20; //  -2;
  float lXLimitRight = 20; // = 1;

  cXDecalKamera = 0.0;
  cYDecalKamera = 0.0;

  // si 0.1 vaisseau immobile !
  if( lD[0] > lXThreshold )
    cXDecalKamera = lD[0] - lXThreshold;
  else
    {
    if( lD[0] < -lXThreshold )
      cXDecalKamera = lD[0] + lXThreshold;
    }

  if( lD[1] >lYThreshold  )
    cYDecalKamera = lD[1] - lYThreshold;
  else
    {
    if( lD[1] < -lYThreshold )
      cYDecalKamera = lD[1] + lYThreshold;
    }
  
  //  std::cout << "111 decal lYThreshold:" <<lYThreshold << "  x:" << lD[0]<< "->" << cXDecalKamera  <<  "   y:" << lD[1] << "->" <<cYDecalKamera << std::endl;

  //  cXDecalKamera = lD[0]*0.01;
  // cYDecalKamera = lD[1]*0.01;
  cXDecalKamera *= 0.05;
  cYDecalKamera *= 0.05;


  if( cXDecalKamera > lXLimitRight )
    cXDecalKamera = lXLimitRight ;
  else
    if( cXDecalKamera < lXLimitLeft )
      cXDecalKamera = lXLimitLeft;

  if( cYDecalKamera > lYLimit )
    cYDecalKamera = lYLimit;
  else
    if( cYDecalKamera < -lYLimit)
      cYDecalKamera = -lYLimit;

  lKam.TransfDouble3::get( POS )[0] = cXDecalKamera;
  lKam.TransfDouble3::get( POS )[1] = cYDecalKamera;

  //   if( cXDecalKamera != 0 || cYDecalKamera != 0)
  //   std::cout << "222 decal x:" << lD[0]<< "->" << cXDecalKamera  <<  "   y:" << lD[1] << "->" <<cYDecalKamera << std::endl;

}
//------------------------
GLboolean
Pilot::animate()
{
  if(SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
    return GL_TRUE;

  cManX = 0.05;
  cManY = 0.15;

  {  //===== Rechargement de base pour l'energie =====
    static float sMemTime = WorldControler::sTime; // fist time

    float lTime = WorldControler::sTime;
    if( lTime - sMemTime >= 1 ){
      sMemTime +=  lTime - sMemTime;

      cErg += 10;
      if( cErg > cMaxErg )
        cErg = cMaxErg;
    }
  } //================================================



  if(cWarpBegin == GL_FALSE )
    Sprite3dPilot::animate();
  else {
    // Pour eviter les deplacements intempestifs pendant le warp
    if( cObj != NULL )
      cObj->animate();
    Sprite3d::animate();
  }


  caObjFire->animate();

  float p =SpriteFloat::get( SPRITE_LIFE_POINT )/SpriteFloat::get( SPRITE_MAX_LIFE_POINT );


  Float4 p3 ( p*0.5+0.3, p*p*0.7+0.1, p*p*p, 0.3);
  caPropsShield->ObjPropsFloat4::set( MATERIAL, p3 );
  caPropsShield->ObjPropsFloat4::set( EMISSION, p3 );

  scrollKamera();

  drawControl();

  setSoundSourcesPositionAndSpeed(  getTransf().TransfDouble3::get(POS),  SpriteDouble3::get( SPRITE_SPEED) );


  return GL_TRUE;
}
//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------
void
Pilot::transfertErgToField()
{
  float lLife    = SpriteFloat::get( SPRITE_LIFE_POINT);
  float lMaxLife = SpriteFloat::get( SPRITE_MAX_LIFE_POINT);

  float lDiff = lMaxLife - lLife;

  if( cErg <= lDiff * 10 ) // facteur de conversion de 10 !!!
    {
      lDiff = cErg / 10;
    }

  cErg -=  (long)lDiff*10;
  SpriteFloat::set( SPRITE_LIFE_POINT, lDiff+lLife );
}
//--------------------------------
void
Pilot::warp()
{
  /////	std::cout << "warp" << std::endl;

  if(SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
    return;



  Double3 lResult;
  T3dTransf &lTran = getTransf();

  WorldControler::GetCurrentWorld()->getKamera()->getProject( lTran.get( POS),  lResult );

  Double3 cPos(	WorldControler::GetMouseX(),	WorldControler::GetMouseY(),  	lResult[2] );

  WorldControler::GetCurrentWorld()->getKamera()->getUnProject( cPos, lResult );



  // Position du Vaisseau
  Double3& lD = getTransf().TransfDouble3::get( POS);

  Double3 lDist;
  lDist[0] = (lResult[0] - MkGetPOS()[0]);
  lDist[1] = (lResult[1] - MkGetPOS()[1]);
  lDist[2] = 0.0;


  int lCout = (int) ((MAX( lDist[0], -lDist[0] ) + MAX( lDist[1], -lDist[1] ))/5.0);  // IL FAUDRAIT RAPPORTER A LA TAILLE TOTALE ????

  if( lCout > cErg )
    {
      SoundSource* lSoundSrc=    PLAY_SAMPLE( sSoundWarpFailed );
      lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );

      SpriteExplosion *sp = new SpriteExplosion( getRadius(), 0.3, 0 );
      sp->setTransf( lTran  );
      sp->setObjProps( caPropsWarp );
      WorldControler::Add( sp );

      return;
    }

  //    SoundControler::sTheSoundControler->playSample(
  //     WorldControler::WC->getCurrentWorld()->getMySoundLibrary()->getSample(sSoundWarp));


  if( cWarpBegin == GL_FALSE )
    {
      SoundSource* lSoundSrc=   PLAY_SAMPLE_PRIO(  sSoundWarp, 5 );
      lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );
    }


  SpriteExplosion *sp = new SpriteExplosion( getRadius(), 0.3, 0 );
  sp->setTransf( lTran  );
  sp->setObjProps( caPropsWarp );
  WorldControler::Add( sp );

  cErg -= lCout;
  lD[0] += lDist[0];
  lD[1] += lDist[1];

  getTransf().TransfDouble3::set( POS, lD );

  sp = new SpriteExplosion( getRadius(), 0.3, 0 );
  sp->setTransf( lTran  );
  sp->setObjProps( caPropsWarp );
  WorldControler::Add( sp );

  /////////	std::cout << "warp ok" << std::endl;

}
//--------------------------------
void
Pilot::firePhaser()
{
  const int lMaxWeapon=9;

  if( cErg <= 0)	return;

  int lCurrent=0;
  Sprite3d* lSpProj[MAX_WEAPON_IN_USE];
  for( int i=0; i<MAX_WEAPON_IN_USE; i++ )		lSpProj[i] = NULL;


  int lVal = cLevelPhaser;

  if( lVal >= lMaxWeapon*3)
    lVal = lMaxWeapon;


  if( lVal >= lMaxWeapon*4)
    lVal = lMaxWeapon*4 -1;



  EnumWeapons  lWeapon1 = WEAPON_PLASMA;
  EnumWeapons  lWeapon2 = WEAPON_PLASMA2;
  EnumWeapons  lWeapon = lWeapon1;

  int lNbWeapon = 1;

  int lCout = 1;
  int lCoutTotal = 0;

  switch( lVal / lMaxWeapon )
    {
    case 0 : break;
    case 1:
      lCout  =2;
      lNbWeapon = 2;
      lWeapon1 = WEAPON_PLASMA;
      lWeapon2 = WEAPON_PLASMA_RED;
      break;
    case 2:
      lCout  =3;
      lNbWeapon = 2;
      lWeapon1 = WEAPON_PLASMA2;
      lWeapon2 = WEAPON_PLASMA_GREEN;
      break;
    case 3:
    default:
      lCout  =4;
      lNbWeapon = 2;
      lWeapon1 = WEAPON_PLASMA2;
      lWeapon2 = WEAPON_PLASMA_BLUE;
      break;
    }

  double lLateral=0.7;
  double lEtendue=0.3;
 
  int lTirDevant  = GL_TRUE;
  int lTirEtendue = GL_FALSE;
  int lTirLateral = GL_FALSE;

  //	if(  WorldControler::GetKeyModifiers() &  GLUT_ACTIVE_SHIFT )
  if(   Fl::event_shift() )
    {
      lTirDevant  = GL_FALSE;
      lTirLateral = GL_TRUE;
    }
  //	if(  WorldControler::GetKeyModifiers() & GLUT_ACTIVE_CTRL  )
  if(  Fl::event_ctrl() )
    {
      lTirDevant  = GL_FALSE;
      lTirEtendue = GL_TRUE;
    }
  //	if(  WorldControler::GetKeyModifiers() &  GLUT_ACTIVE_ALT )
  if(  Fl::event_alt() )
    {
      lTirDevant  = GL_TRUE;
      lTirEtendue = GL_TRUE;
      lTirLateral = GL_TRUE;
    }

  if( lTirEtendue && lTirLateral )
    lTirDevant = GL_TRUE;



  //	std::cout << lVal% 9 << "  lTirDevant:" << lTirDevant << "\tTirLateral: " << lTirLateral << " " << lLateral << std::endl;


  for( int i=0; i<lNbWeapon; i++)
    {
      if( i == 0 )
        lWeapon = lWeapon1;
      else
        lWeapon = lWeapon2;


      switch( lVal%lMaxWeapon ){
      case 0:  // NORMAL
        if( lTirDevant )
          {
            lCoutTotal+=lCout;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 1,           &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*2;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*2;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }
        break;

      case 1:  // DOUBLE
        if( lTirDevant )
          {
            lCoutTotal += lCout*2;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 2,           &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*4;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }


        if( lTirLateral )
          {
            lCoutTotal += lCout*4;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        break;

      case 2:  // TRIPLE
        if( lTirDevant )
          {
            lCoutTotal += lCout*3;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,           &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*6;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*6;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        break;


      case 3: // TRIPLE + 1 lateral
        if( lTirDevant )
          {
            lCoutTotal += lCout*4;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*8;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,    &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*8;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        break;

      case 4: // TRIPLE + double Lateral
        if( lTirDevant )
          {
            lCoutTotal += lCout*5;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*10;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue ,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*10;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }
        break;

      case 5:
        if( lTirDevant )
          {
            lCoutTotal += lCout*6;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.04, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*12;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3,lEtendue ,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*12;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        break;

      case 6:
        if( lTirDevant )
          {
            lCoutTotal += lCout*7;
            TheWeaponsMaker->makeMultipleSameWeapon    ( lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.04, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*14;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*14;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        break;

      case 7:
        if( lTirDevant )
          {
            lCoutTotal += lCout*8;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.04, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*16;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*16;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }
        break;

      case 8:
      default:
        if( lTirDevant )
          {
            lCoutTotal += lCout*9;
            TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.04, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirEtendue )
          {
            lCoutTotal += lCout*18;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }

        if( lTirLateral )
          {
            lCoutTotal += lCout*18;
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
            TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
          }
        break;
      }
    }


  cErg -=  lCoutTotal; // lNbWeapon * lCoutTotal;
  if( cErg < 0 )
    cErg = 0;


  for( int i=0; i<lCurrent; i++ )
    {
      if( lSpProj[i] == NULL )
        break;

      lSpProj[i]->SpriteDouble3::get( SPRITE_SPEED )[0] *= -1;
      lSpProj[i]->SpriteDouble3::get( SPRITE_SPIN )[1] = 0;
      WorldControler::Add( lSpProj[i] );
    }

  // Mettre un son differend selon la puissance du tir !
  SoundSource* lSoundSrc=  PLAY_SAMPLE_PRIO(  sSoundLaser, 10 );
  lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );
}
//--------------------------------
void
Pilot::fireRocket()
{
  const int lMaxWeapon=8;

  if( cRocket <= 0) return ;

  int lCurrent=0;
  Sprite3d* lSpProj[MAX_WEAPON_IN_USE];
  for( int i=0; i<MAX_WEAPON_IN_USE; i++ )		lSpProj[i] = NULL;

  int lVal = cLevelLauncher;

  if( lVal >= lMaxWeapon*3)
    lVal = lMaxWeapon*3-1;


  int lCout = 1;
  int lCoutTotal = 0;


  EnumWeapons  lWeapon = WEAPON_SMALL_ROCKET;
  if( lVal /lMaxWeapon  == 1 )
    lWeapon = WEAPON_ROCKET;
  else
    if( lVal /lMaxWeapon  >= 2 )
      lWeapon = WEAPON_BIG_ROCKET;



  double lLateral=0.7;
  double lEtendue=0.3;

  int lTirDevant  = GL_TRUE;
  int lTirEtendue = GL_FALSE;
  int lTirLateral = GL_FALSE;


  //	if(  WorldControler::GetKeyModifiers() &  GLUT_ACTIVE_SHIFT )
  if(   Fl::event_shift() )
    {
      lTirDevant  = GL_FALSE;
      lTirLateral = GL_TRUE;
    }
  //	if(  WorldControler::GetKeyModifiers() & GLUT_ACTIVE_CTRL  )
  if(  Fl::event_ctrl() )
    {
      lTirDevant  = GL_FALSE;
      lTirEtendue = GL_TRUE;
    }
  //	if(  WorldControler::GetKeyModifiers() &  GLUT_ACTIVE_ALT )
  if(  Fl::event_alt() )
    {
      lTirDevant  = GL_TRUE;
      lTirEtendue = GL_TRUE;
      lTirLateral = GL_TRUE;
    }

  if( lTirEtendue && lTirLateral )
    lTirDevant = GL_TRUE;




  switch( lVal%lMaxWeapon ){
  case 0:  // NORMAL
    if(  lTirDevant ){

      lCoutTotal+=lCout;
      TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 1,  &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }

    if( lTirEtendue ){
      lCoutTotal+=lCout*2;
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }

    if( lTirLateral ){
      lCoutTotal+=lCout*2;
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    break;

  case 1:  // DOUBLE
    if( lTirDevant ){
      lCoutTotal+=lCout*2;
      TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 2,            &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    if( lTirEtendue ){
      lCoutTotal+=lCout*4;
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2,  lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    if( lTirLateral ){
      lCoutTotal+=lCout*4;
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2,  lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    break;

  case 2:  // TRIPLE
    if( lTirDevant ){
      lCoutTotal+=lCout*3;
      TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,           &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    if( lTirEtendue ){
      lCoutTotal+=lCout*6;
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3,  lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    if( lTirLateral ){
      lCoutTotal+=lCout*6;
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    }
    break;


  case 3: // TRIPLE + 1 lateral
    if( lTirDevant )
      {
        lCoutTotal+=lCout*4;
        TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirEtendue )
      {
        lCoutTotal+=lCout*8;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.15+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirLateral )
      {
        lCoutTotal+=lCout*8;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.15+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    break;

  case 4: // TRIPLE + double Lateral
    if( lTirDevant )
      {
        lCoutTotal+=lCout*5;
        TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirEtendue )
      {
        lCoutTotal+=lCout*10;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.15+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirLateral )
      {
        lCoutTotal+=lCout*10;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3,   lLateral,   &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.15+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    break;

  case 5:
    if( lTirDevant )
      {
        lCoutTotal+=lCout*6;
        TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.03, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirEtendue )
      {
        lCoutTotal+=lCout*12;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirLateral )
      {
        lCoutTotal+=lCout*12;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    break;

  case 6:
    if( lTirDevant )
      {
        lCoutTotal+=lCout*7;
        TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.03, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirEtendue )
      {
        lCoutTotal+=lCout*14;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirLateral )
      {
        lCoutTotal+=lCout*14;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    break;
  default:
  case 7:
    if( lTirDevant )
      {
        lCoutTotal+=lCout*8;
        TheWeaponsMaker->makeMultipleSameWeapon(     lCurrent,  lSpProj, 3,      &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.02, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.03, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirEtendue )
      {
        lCoutTotal+=lCout*16;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lEtendue,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.2+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.4+lEtendue, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    if( lTirLateral )
      {
        lCoutTotal+=lCout*16;
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, lLateral,     &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.2+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
        TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 3, 0.4+lLateral, &getTransf(), lWeapon, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      }
    break;
  }

  if( lTirDevant )
    cRocket -= lCoutTotal;


  if( cRocket < 0 )
    cRocket = 0;


  for( int i=0; i<lCurrent; i++ )
    {
      if( lSpProj[i] == NULL )
        break;

      lSpProj[i]->SpriteDouble3::get( SPRITE_SPEED )[0] *= -1;
      lSpProj[i]->MkGetANGLE()[1] = 180;

      WorldControler::Add( lSpProj[i] );

    }


  // PLAYSAM	// Mettre un son differend selon la puissance du tir !
  SoundSource* lSoundSrc= PLAY_SAMPLE_PRIO( sSoundFireMissile, 10 );
  lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );


  //	TheWeaponsMaker->makeSprite(  &getTransf(), cLevelLauncher, WEAPON_ROCKET, InteractAllied ,  InteractWeaponAlliedOut);
}
//--------------------------------
void
Pilot::fireMine()
{
  if( cErg <= 15)	return;


  int lCurrent=0;
  Sprite3d* lSpProj[MAX_WEAPON_IN_USE];
  for( int i=0; i<MAX_WEAPON_IN_USE; i++ )		lSpProj[i] = NULL;

  int lVal = cLevelPhaser;
  if( lVal > 11 )
    lVal = 11;

  cErg -= (lVal+1)*15;

  switch( lVal ){
  case 0:  // NORMAL
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 1,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 1:  // DOUBLE
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 2,      &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 2:  // TRIPLE
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 3:  // DOUBLE pour 1 Lateral
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 2,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.2, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 4: // TRIPLE + 1 lateral
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.2, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 5: // TRIPLE + double Lateral
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 6:
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.4, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

  case 7:
    TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
    break;

    /*
      case 11 :
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.1  &getTransf(), WEAPON_PLASMA, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      case 10:
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 1, 0.3  &getTransf(), WEAPON_PLASMA, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      case 9:
      TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_PLASMA, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      case 8:
      TheWeaponsMaker->makeMultipleSameWeapon( lCurrent,  lSpProj, 3,          &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.2, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);
      TheWeaponsMaker->makeMultipleSameWeaponDiag( lCurrent,  lSpProj, 2, 0.4, &getTransf(), WEAPON_ION, InteractWeaponAlliedIn, InteractWeaponAlliedOut);;
      break;
    */

  default:
    break;
  }



  for( int i=0; i<MAX_WEAPON_IN_USE; i++ )
    {
      if( lSpProj[i] == NULL )
        break;

      lSpProj[i]->SpriteDouble3::get( SPRITE_SPEED )[0] *= -1;
      WorldControler::Add( lSpProj[i] );
    }

  //	TheWeaponsMaker->makeSprite( lSpProj, &getTransf(), cLevelPhaser, WEAPON_ION, InteractAllied ,  InteractWeaponAlliedOut);
}
//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------
void
Pilot::mouseButton( int pButton, int pState, int pX, int pY )
{
  switch( pButton )
    {
    case GLUT_LEFT_BUTTON:
      if( pState == GLUT_DOWN )
        firePhaser();
      break;

    case GLUT_MIDDLE_BUTTON:
      if( pState == GLUT_DOWN ){
        cWarpBegin = GL_TRUE;
      }
      else if( pState == GLUT_UP ) {
        cWarpBegin = GL_FALSE;
        warp();
      }
      break;

    case GLUT_RIGHT_BUTTON:
      if( pState == GLUT_DOWN )
        fireRocket();
      break;
    }
}
//------------------------------------------------------------------
GLboolean Pilot::collision( Sprite3d &pMySprite, Sprite3d &pSprite, void *pParam)
{
  if( pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT ) < 0 )
    return GL_TRUE;


  switch( pSprite.SpriteLong::get( SPRITE_TYPE ) )
    {
    case CONTAINER :
      return collisionBonus( pSprite, pParam );

    default:;
    }

  float lDestroy = pSprite.SpriteFloat::get( SPRITE_DESTROY_POINT );



  if( WorldControler::sDebug == 0 ) {
    pMySprite.SpriteFloat::set( SPRITE_LIFE_POINT,
                                pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT )-lDestroy);
  }


  for( int j=0; j< 3; j++)
    {
      SpriteExplosion *sp = new SpriteExplosion( 1.5+randp(pMySprite.getRadius()), 0.3+randp(0.3) );
      sp->setTransf( pMySprite.getTransf() );
      sp->setObjProps( SpriteExplosion::caExplosionProps );
      WorldControler::Add( sp );

    }
  SoundSource* lSoundSrc=  PLAY_SAMPLE( sSoundCollision );
  lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );

  if( pMySprite.SpriteFloat::get( SPRITE_LIFE_POINT ) <= 0 )
    {

      if( cNbLife <= 0 )
        {
          SoundSource* lSoundSrc= 	PLAY_SAMPLE( sSoundFinalExplosion );
          lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );
          //				PLAYMUSIC(  GETSAMPLE( sMusicGameOver ));

          int max = static_cast<long>(randp(30)+2.0);
          for( int j=0; j< max+1; j++)
            {
              SpriteExplosion *sp = new SpriteExplosion( 1.5+randp(5), 0.3+randp(10) );
              sp->setTransf( pMySprite.getTransf() );
              sp->setObjProps( SpriteExplosion::caExplosionProps );
              WorldControler::Add( sp );
            }
          pSprite.SpriteFloat::set( SPRITE_LIFETIME, 3 );

          Sprite3dObj* lSpriteEx = new Sprite3dObj( new ObjExplosion( 500, 6 ) );
          lSpriteEx->setTransf( pMySprite.getTransf() );
          lSpriteEx->SpriteFloat::set( SPRITE_LIFETIME, 7 );

          WorldControler::Add( lSpriteEx );



          Float4 lBanColor( 0.6, 0.6, 0.9, 0.5 ) ;

          Sprite3d* lSpBan = new Banniere( "Game.TextureGameOver", lBanColor ); // "textures/game_over.gif", lBanColor );

          Double3 lPosBan( 0, 0, 20 );
          Double3 lSpeed( 0, 0, 20 );
          Double3 lScale( 40, 40, 40 );
          Double3 lSpin(25, 15, 15);

          lSpBan->MkSetPOS(   lPosBan  );
          lSpBan->MkSetSPEED( lSpeed  );
          lSpBan->MkSetSCALE( lScale  );
          lSpBan->MkSetSPIN(  lSpin );



          WorldControler::Add( lSpBan );




          ////////////		std::cout << " Pilot::collision ->  GAME-OVER" << std::endl;
          // GAME-OVER
          ((WorldGame*)WorldControler::GetGameWorld())->getSceneManager()->setCurrentSceneTempo( 30, SceneManager::GameOver );
        }
      else
        {
          ////////				WorldGame::TheWorldGame->cSceneManager->resetCurrentSceneFromBegin( this );
          SoundSource* lSoundSrc=  PLAY_SAMPLE(  sSoundNextLife );
          lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );

          cNbLife--;

          cRocket = cMaxRocket;
          cErg    = cMaxErg;
          SpriteFloat::set( SPRITE_LIFE_POINT, SpriteFloat::get( SPRITE_MAX_LIFE_POINT ));

          // Un super effet WARP !!!
          SpriteExplosion *sp = new SpriteExplosion( getRadius()*10, 1, 0 );
          sp->setTransf( getTransf() );
          sp->setObjProps( caPropsWarp );
          WorldControler::Add( sp );
        }

      //		World::sCurrentWorld->setPilot(NULL);
      //		World::sCurrentWorld->killSprite( &pMySprite );
    }

  return GL_TRUE;
}
//------------------------------------------------------------------
GLboolean
Pilot::kill( Sprite3d &pMySprite, void*pParam )
{
  ////	std::cout << "Pilot::kill" << std::endl;

  WorldControler::WC->GameOver();

  return GL_TRUE;
}
//------------------------------------------------------------------


void
Pilot::drawControl()
{

  glDisable(GL_LIGHTING);


  char tmp[512];

  //    if( cXDecalKamera != 0 || cYDecalKamera != 0)
      //     std::cout << " decal x:"  << cXDecalKamera  <<  "   y:" <<cYDecalKamera << std::endl;

  float lX = -110;
  float lY =  110;
  float lZ =  10;
  
  lX = -120+cXDecalKamera*6.33;  // MAUVAIS il faudrait etre independant de la camera
  lY =  75+cYDecalKamera*6.33;
  lZ =  10;
  float lStep=25;


  T3dColor::Yellow();
  sprintf( tmp, "Fuel %ld", cErg );
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
  lX += lStep;
  //	lY -= 10;

  T3dColor::LightBlue();
  sprintf(tmp, "Rocket %ld", cRocket );
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
  lX += lStep;
  //	lY -= 10;

  T3dColor::Pink();
  sprintf(tmp, "Shield %ld", (long)SpriteFloat::get( SPRITE_LIFE_POINT ));
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
  lX += lStep;


  T3dColor::Red();
  sprintf(tmp,"Life:%ld", cNbLife);
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
  lX += lStep;
  //	lY -= 10;

  T3dColor::White();
  sprintf(tmp,"Score:%ld", cScore);
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
  lX +=lStep;
  //	lY -= 10;

  T3dColor::Yellow();
  sprintf(tmp,"$:%ld", cGold);
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);

  lX += lStep;
  lX += lStep;
//  lY -= 3;

  
  T3dColor::White();
  sprintf(tmp,"%s %ld", WorldControler::WC->getCurrentWorld()->getInfoLeveL(),
          (long)WorldControler::sTime);
  WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
  //  lY -= 3;

  
  //	lY -= 10;


  /*
    lY -= 10;
    lY -= 8;
    lX = -120;
    T3dColor::Green();
    ///////// DEBUG 	sprintf(tmp,"Sprite:%d %d", WorldGame::TheWorldGame->getSizeLiveSprite(), WorldGame::TheWorldGame->getNbLiveSprite() );

    //	std::cout << "Sprite:" <<   WorldGame::TheWorldGame->getNbLiveSprite()
    //						<<  " " <<  WorldGame::TheWorldGame->getNbRealLiveSprite() << std::endl;

    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);

  */
  lY -= 10;


  lY -= 8;
  lX = -120;


  if( WorldControler::sDebug ){

    T3dColor::White();
    sprintf(tmp,"Detect:%ld", World::sNbDetect );
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::Yellow();
    sprintf(tmp,"%ld", cMaxErg );
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::Blue();
    sprintf(tmp,"%ld", cMaxRocket);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::Yellow();
    sprintf(tmp,"%ld", cLevelPhaser);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::LightBlue();
    sprintf(tmp,"%ld", cLevelLauncher);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::Pink();
    sprintf(tmp,"%ld", cLevelField);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::White();
    sprintf(tmp,"M%ld", cLevelMotor);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;
    T3dColor::White();
    sprintf(tmp,"W%ld", cLevelWarp);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::White();
    sprintf(tmp,"%1.2f", cManX);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;

    T3dColor::White();
    sprintf(tmp,"%1.2f", cManY);
    WorldControler::sCurrentFont->displayAt( lX, lY, lZ, tmp);
    lY -= 10;
  }
  glEnable(GL_LIGHTING);

}
//------------------------------------------------------------------
GLboolean
Pilot::collisionBonus( Sprite3d &pSprite, void *pParam)
{
  if( pSprite.SpriteFloat::get( SPRITE_LIFETIME) == -1)
    {
      int val =  static_cast<int> (pSprite.SpriteFloat::get( CONTAINER_TYPE ));
      int val2 = static_cast<int> (pSprite.SpriteFloat::get( CONTAINER_VALUE ));


      char* cText = NULL;
      char lTmpStr[512];

      O3dObjProps* lBonusProps=NULL;

      switch(val )
        {
        case CONTAINER_ERG:
          cErg += val2;
          if( cErg > cMaxErg ){
            cGold += (cErg-cMaxErg)/100;
            cErg = cMaxErg;
          }

          sprintf( lTmpStr, "E+%d", val2 );
          cText = lTmpStr;
          break;

        case CONTAINER_ROCKET:
          cRocket += val2;
          if( cRocket > cMaxRocket ){

            cGold +=  cRocket- cMaxRocket;

            cRocket = cMaxRocket;
          }

          sprintf( lTmpStr, "M+%d", val2 );
          cText = lTmpStr;
          break;
        case CONTAINER_FIELD :
          SpriteFloat::set( SPRITE_LIFE_POINT,  (SpriteFloat::get( SPRITE_LIFE_POINT) + val2) );

          if( SpriteFloat::get( SPRITE_LIFE_POINT)>SpriteFloat::get( SPRITE_MAX_LIFE_POINT)){
            cGold +=   SpriteFloat::get( SPRITE_LIFE_POINT)-SpriteFloat::get( SPRITE_MAX_LIFE_POINT);
            SpriteFloat::set( SPRITE_LIFE_POINT, SpriteFloat::get( SPRITE_MAX_LIFE_POINT));
          }

          sprintf( lTmpStr, "F+%d", val2 );
          cText = lTmpStr;
          break;

        case CONTAINER_LIFE:
          cNbLife += val2;
          break;

        case CONTAINER_GOLD:
          cGold += val2;
          break;

        case CONTAINER_UPGRAD:
          {
            int lVal3 = static_cast<int> (pSprite.SpriteFloat::get( CONTAINER_VALUE2 ));

            switch( lVal3 )
              {
              case UPGRAD_ERG:
                cMaxErg += 500;
                cErg = cMaxErg;

                cText = const_cast<char*>("Energy+500");
                lBonusProps = &TheBonusMaker->cPropsErg;
                break;
              case	UPGRAD_ROCKET:
                cMaxRocket += 100;
                cRocket = cMaxRocket;
                cText = const_cast<char*>("Rocket+100");
                lBonusProps = &TheBonusMaker->cPropsRocket;
                break;
              case UPGRAD_FIELD:
                SpriteFloat::set( SPRITE_MAX_LIFE_POINT,  (SpriteFloat::get( SPRITE_MAX_LIFE_POINT) + val2*10) );
                SpriteFloat::set( SPRITE_LIFE_POINT,      (SpriteFloat::get( SPRITE_MAX_LIFE_POINT)) );
                sprintf( lTmpStr, "Field+%d", val2*10 );
                cText = lTmpStr;
                lBonusProps = &TheBonusMaker->cPropsField;
                break;
              case UPGRAD_PHASER:
                cLevelPhaser += val2;
                sprintf( lTmpStr, "Phaser+%d", val2 );
                cText = lTmpStr;
                lBonusProps = &TheBonusMaker->cPropsErg;
                break;
              case UPGRAD_LAUNCHER:
                cLevelLauncher += val2;
                sprintf( lTmpStr, "Launcher+%d", val2 );
                cText = lTmpStr;
                lBonusProps = &TheBonusMaker->cPropsRocket;
                //								lColorText = T3dColor::Blue;
                break;
              case UPGRAD_MOTOR:
                cLevelMotor += val2;
                for( int i=0; i< val2; i++ ){
                  cManX *= 1.5;
                  cManY *= 1.5;
                  sprintf( lTmpStr, "Motor+%d", val2 );
                  cText = lTmpStr;
                }
                break;
              default: ;
              }
            break;
          }
        default:;
        }

      // On modifie le container
      pSprite.SpriteFloat::set( CONTAINER_VALUE, 0 );
      pSprite.SpriteFloat::set( SPRITE_LIFETIME, 2);

      if( cText != NULL )	{
        O3dObjPLibFont* lO3dText = new O3dObjPLibFont( FL_HELVETICA_BOLD, 12, cText  ); // 4

        Sprite3dObj *lSpriteText = new Sprite3dObj( lO3dText, 2 );
        //		Sprite3dObj *lSpriteText = new Sprite3dObj( new O3dObjPrim( O3dObjPrim::PrimSphere, 20, 8, 8 ), 2);
        lSpriteText->setDeepDestroy(GL_TRUE);
        lSpriteText->setTransf( getTransf() );
        if( lBonusProps == NULL )
          lO3dText->setObjProps(  pSprite.getObjProps() );
        else
          lO3dText->setObjProps( lBonusProps );


        Double3 lD3 ( WorldGame::GlobalScroll, 60, 7);
        lSpriteText->SpriteDouble3::set( SPRITE_SPEED, lD3 );

        WorldControler::Add( lSpriteText );
      }
    }


  SoundSource* lSoundSrc=   PLAY_SAMPLE(  sSoundBonus );
  lSoundSrc->setPosition(  getTransf().TransfDouble3::get(POS) );

  for( int i=0; i<8; i++)
    {
      SpriteExplosion *sp = new SpriteExplosion( 10.0+randp(4), 0.1); //+randp(0.1) );
      sp->setTransf( getTransf() );
      sp->setObjProps(  pSprite.getObjProps() );

      WorldControler::Add( sp );
    }

  WorldControler::KillSprite( &pSprite);
  // =========== RECHARGE ==========

  ////	SpriteFloat::set( SPRITE_LIFE_POINT,  1000.0) ;
  return GL_TRUE;
}
//--------------------------------
void
Pilot::key( unsigned char key, int x, int y )
{

  //	GLUT_ACTIVE_SHIFT
  //		GLUT_ACTIVE_CTRL
  //	GLUT_ACTIVE_ALT


  /////	std::cout << "Pilot::key:" << key  << ":" << (int) key << std::endl;
  switch( key )
    {
    case ' ':
      transfertErgToField();
      break;


    case 'q':
    case 'Q':
    case 'a':
    case 'A':
      if( cWarpBegin == GL_FALSE )
        cWarpBegin = GL_TRUE;
      else
        cWarpBegin = GL_FALSE;
      warp();
      break;

    case '1':
      firePhaser();
      break;
    case '2':
      fireRocket();
      break;
    case '3':
      fireMine();
      break;

    case '+':
      if( WorldControler::sDebug ){
        cLevelPhaser++;
        cLevelLauncher++;

        cErg = cMaxErg;
        cRocket = cMaxRocket;
        SpriteFloat::set( SPRITE_LIFE_POINT, SpriteFloat::get( SPRITE_MAX_LIFE_POINT));

        cNbLife++;
      }
    }
}


