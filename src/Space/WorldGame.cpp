#include "Sprite3d/World.h"

#include "Sprite3d/SceneManager.h"
#include "U3d/Sky.h"

#include "Sprite3d/Random.h"
#include "Sprite3d/SoundControler.h"

#include "SceneAsteroide.h"
#include "SceneBase.h"
#include "SceneAttack.h"
#include "SceneAttackCroisseur.h"
#include "SceneGrotte.h"
#include "SceneLife.h"
#include "SceneHammerAnvil.h"
// #include "SceneArtifice.h"
#include "SceneChaos.h"


#include "Pilot.h"
#include "Def.h"
#include "WorldGame.h"
#include "ShipsMaker.h"
#include "MinesMaker.h"
#include "U3d/BonusMaker.h"
#include "U3d/WeaponsMaker.h"
#include "U3d/SpriteExplosion.h"
#include "U3d/ObjPrimPart.h"
#include "U3d/Banniere.h"

#include "WorldGame.h"
#include "ActionsShip.h"

#include <string>

float WorldGame::GlobalScroll = -20;
WorldGame *WorldGame::TheWorldGame = NULL;
float WorldGame::XSizeWorld = 150;
float WorldGame::YSizeWorld = 120;



//************************************************************
WorldGame::WorldGame( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,
                      O3dObjProps *pProps)
  :World(pControl, pKamera, pMax, pProps),
   cSize(pSize),
   cLevel(0),
   cSceneManager(NULL)
{
  TheWorldGame = this;
  cInfoLevel[0]='\0';
	
}
//---------------------------------------------------
WorldGame::~WorldGame()
{
  delete cSceneManager;
  TheWorldGame = NULL;
}
//---------------------------------------------------
const char*
WorldGame::getInfoLeveL(){
  strcpy(  cInfoLevel, cSceneManager->getInfoScene() );
  //	sprintf( cInfoLevel, cSceneManager->getInfoScene() );
  return cInfoLevel;
}
//---------------------------------------------------
// C'est la que l'on prepare l'ensemble des niveaux du jeu

GLboolean
WorldGame::initStart( int pNiveau, const char* pNameFileSav )
{
  //	std::cout << "WorldGame::initStart " << pNiveau << " " << pNameFileSav << std::endl;

  //  Double3 lGenPos( 160.0, 0.0, 0.0 );
  Double3 lGenPos( 220.0, 0.0, 0.0 );
  //  Double3 lGenPos2( 0.0, 130, 0.0 );
  Double3 lGenPos2( 0.0, 150, 0.0 );
  Float4 lBanColor( 0.6, 0.6, 0.9, 0.4 ) ;


  cSceneManager = new SceneManager();
  // Mettre une scene d'intro !!!
  int lDureGen = 20; //40;

  WorldGame::GlobalScroll = -20;  // la vitesse de scolling horizontal de base
	

  if( pNiveau == 0 )
    {
      if(  WorldControler::sDifficultyLevel >2 )
        {
          pNiveau = WorldControler::sDifficultyLevel*2;
          WorldGame::GlobalScroll -= pNiveau;
        }
    }	//			std::cout << "pNiveau:" << pNiveau << std::endl;

  int duree=1000;
  for( cLevel=pNiveau; cLevel< pNiveau+8+WorldControler::sDifficultyLevel; cLevel++ )	
    {

      //			std::cout << "pLevel:" << cLevel << std::endl;
      // Message NEXT LEVEL
      if( cLevel!= pNiveau )
        {
          cSceneManager->addSceneTempo(4);
          cSceneManager->addScene( makeBanniere( "Game.TextureNextLevel", lBanColor, 3), 4);
          cSceneManager->addSceneTempo(3);
          WorldGame::GlobalScroll -= 1;  // NE DOIT PAS MARCHER CAR GLOBAL IL FAUDRAIT METTRE UN SCROLL par Scene
          // Ou memoriser le GlobalScroll a la creation de chque scene puis ensuite celle ci le positionner
        }
      duree = lDureGen+cLevel*3;



      //		if( cLevel > 5 )
      //			cSceneManager->addScene( new SceneLife( lGenPos, YSizeWorld, 20.0f ),  0.5 );
			

      //*************************** WATER ***************************
      cSceneManager->addScene( new SceneAsteroide( "Asteroid field", ASTEROIDE_WATER, cLevel, lGenPos, 0.3f, YSizeWorld, 20.0f ),  duree );
      cSceneManager->addSceneTempo(5);

      if( cLevel == 0 )
        continue;

      cSceneManager->addScene( new SceneAttack( "Confrontation", cLevel, lGenPos, 1, YSizeWorld, 30.0f ), duree);
      cSceneManager->addSceneTempo(5);


      if( cLevel == 1 )
        continue;

      cSceneManager->addScene(new SceneGrotte( "Inside asteroid", ASTEROIDE_WATER, cLevel, lGenPos, 1, 0.4, 15, YSizeWorld, 50.0f ), duree );
      cSceneManager->addSceneTempo(5);
      //**************************************************************



      cSceneManager->addScene( new SceneAttack( "Confrontation",cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
      cSceneManager->addSceneTempo(5);



      //****************************  ICE  ***************************
      cSceneManager->addScene( new SceneAsteroide( "Asteroid field",ASTEROIDE_ICE, cLevel, lGenPos, 0.3, YSizeWorld, 20.0 ), duree);
      cSceneManager->addSceneTempo(5);
      if( cLevel == 2 )
        continue;

      cSceneManager->addScene(new SceneGrotte( "Inside asteroid", ASTEROIDE_ICE,  cLevel, lGenPos, 1.2, 0.7, 13, YSizeWorld, 50.0 ), duree);
      cSceneManager->addSceneTempo(5);
      //**************************************************************



      if( cLevel == 3 )
        continue;


      cSceneManager->addScene( new SceneAttack( "Confrontation",cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
      cSceneManager->addSceneTempo(5);



      //**************************** SNOW ***************************
      cSceneManager->addScene( new SceneAsteroide( "Asteroid field", ASTEROIDE_SNOW, cLevel, lGenPos, 0.3f, YSizeWorld, 20.0f ), duree);
      cSceneManager->addSceneTempo(5);
      cSceneManager->addScene(new SceneGrotte( "Inside asteroid", ASTEROIDE_SNOW, cLevel , lGenPos, 1.5, 0.6, 15, YSizeWorld, 50.0 ), duree);
      cSceneManager->addSceneTempo(5);
      //**************************************************************



      if( cLevel == 4 )
        continue;


      cSceneManager->addScene( new SceneAttack( "Confrontation", cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
      cSceneManager->addSceneTempo(5);


      //**************************** STONE ***************************

      cSceneManager->addScene( new SceneAsteroide( "Asteroide field", ASTEROIDE_MARS, cLevel, lGenPos, 0.3, (int)YSizeWorld, 20.0 ), duree );
      cSceneManager->addSceneTempo(5);
      cSceneManager->addScene(new SceneGrotte( "Into asteroide ", ASTEROIDE_MARS, cLevel , lGenPos, 0.9, 0.5, 14, YSizeWorld, 50.0 ), duree);
      cSceneManager->addSceneTempo(5);
      //**************************************************************

      if( cLevel == 5 )
        continue;


      cSceneManager->addScene( new SceneAttack( "Confrontation", cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
      cSceneManager->addSceneTempo(5);

      //**************************** CRISTAL ***************************

      cSceneManager->addScene( new SceneAsteroide( "Asteroide field", ASTEROIDE_CRISTAL, cLevel, lGenPos, 0.3, (int)YSizeWorld, 20.0 ), duree );
      cSceneManager->addSceneTempo(5);
      cSceneManager->addScene(new SceneGrotte( "Into asteroide ", ASTEROIDE_CRISTAL, cLevel , lGenPos, 0.9, 0.5, 14, YSizeWorld, 50.0 ), duree);

      cSceneManager->addSceneTempo(5);


      //**************************************************************


      if( cLevel == 6 )
        continue;


      cSceneManager->addScene( new SceneAttack( "Confrontation", cLevel, lGenPos, 1, YSizeWorld, 30.0 ), duree);
      cSceneManager->addSceneTempo(5);



      cSceneManager->addScene( new SceneLife( lGenPos, YSizeWorld, 20.0f ),  0.5 );
      cSceneManager->addSceneTempo(5);
      //  "Hammer and anvil"

      //*********************** PLASMA_SOLAIRE ***********************

      cSceneManager->addScene( new SceneAsteroide( "Coronal mass ejection", PLASMA_SOLAIRE, cLevel, lGenPos, 0.3, YSizeWorld, 20.0 ), duree );
      cSceneManager->addSceneTempo(5);

      cSceneManager->addScene( new SceneHammerAnvil( "Sun storm", PLASMA_SOLAIRE, cLevel, lGenPos2, 0.3f, YSizeWorld, 20.0f ),  duree );
      cSceneManager->addSceneTempo(5);


      cSceneManager->addScene( new SceneChaos( "Solar prominence",  PLASMA_SOLAIRE, cLevel, lGenPos, 1, 0.4, 15, YSizeWorld, 50.0f ), duree );

      cSceneManager->addScene(new SceneGrotte( "In the Plasma vortex", PLASMA_SOLAIRE,  cLevel, lGenPos, 1.1, 0.6, 14, YSizeWorld, 50.0 ), duree);

      cSceneManager->addScene( new SceneChaos( "Solar prominence",  PLASMA_SOLAIRE, cLevel, lGenPos, 1, 0.4, 15, YSizeWorld, 50.0f ), duree );
      cSceneManager->addScene( new SceneHammerAnvil( "Sun storm", PLASMA_SOLAIRE, cLevel, lGenPos2, 0.3f, YSizeWorld, 20.0f ),  duree );

      cSceneManager->addScene( new SceneAsteroide( "Coronal mass ejection", PLASMA_SOLAIRE, cLevel, lGenPos, 0.3, YSizeWorld, 20.0 ), duree );	

			
		
      cSceneManager->addScene( new SceneAttack( "Confrontation", cLevel, lGenPos, 3, YSizeWorld, 30.0), duree);



      if( cLevel == 7 )
        continue;

      cSceneManager->addScene( new SceneAttackCroisseur( "Confrontation", cLevel, lGenPos, 3, YSizeWorld, 30.0), duree);
			

      //		if( cLevel == 7 )
      //	continue;

      //	cSceneManager->addSceneTempo(10);
      //			cSceneManager->addScene( new SceneBase( "Base", cLevel, lGenPos, 1, YSizeWorld, 20.0, (int)MEGA_CROISEUR ), duree);

      // Mettre un vrai boss de niveau
      // Mettre une scene de fin de niveau !!!
      // Possiblite d'achat de materiel !!!
      /*
        {
        Sprite3d* sp = TheBonusMaker->makeSpriteBonus( CONTAINER_UPGRAD, CONTAINER_LIFE, InteractBonus, InteractBonus, 1 );

        Double3 lPos;
        lPos[0] =  randf(100);
        lPos[1] = -100;
        lPos[ 2 ] = 0;

        sp->getTransf().TransfDouble3::set( POS, lPos );


        Double3 lD3( randf( 150 ), randf( 150 ), randf( 150 ));
        sp->SpriteDouble3::set( SPRITE_SPIN, lD3);

        cSceneManager->addScene(sp);
        }
      */
    }

  cSceneManager->addScene( new SceneBase( "Last battle", cLevel, lGenPos, 1, YSizeWorld, 20.0, (int)BASE_TORE ), duree);



  Pilot *lPilot = new Pilot();
  lPilot->getTransf().TransfDouble3::get(POS)[ 0 ] = -YSizeWorld;

  add( lPilot );

  setPilot( lPilot );

  if( pNameFileSav != NULL )
    cSceneManager->restoreStateFromFile( this, pNameFileSav );
  else
    cSceneManager->go(this);



  add( new Sky( 10*cSize, cSize*100 ) );
  return GL_TRUE;
}
//---------------------------------------------------
void
WorldGame::freeRessources()
{
  empty();

  delete cSceneManager;
  cSceneManager = NULL;
}
//---------------------------------------------------
void
WorldGame::gameOver()
{
  //	std::cout << "WorldGame::gameOver" << std::endl;
  World::gameOver();

  Float4 lBanColor( 0.9, 0.9, 1.0, 0.5 ) ;

  Sprite3d* lSpBan = new Banniere( "Game.TextureGameOver", lBanColor );

  Double3 lPosBan( 0, 0, 20 );
  Double3 lSpeed( 0, 0, 20 );
  Double3 lScale( 40, 40, 40 );
  Double3 lSpin(25, 15, 15);

  lSpBan->MkSetPOS(   lPosBan  );
  lSpBan->MkSetSPEED( lSpeed  );
  lSpBan->MkSetSCALE( lScale  );
  lSpBan->MkSetSPIN(  lSpin );


  WorldControler::Add( lSpBan );



  ((WorldGame*)WorldControler::GetGameWorld())->getSceneManager()->addSceneTempo( 25, SceneManager::GameWinner  );

  // Faire qq chose !
}

//------------------------------<
// Pour laisser du temps entre deux scenes

Sprite3d*
WorldGame::makeBanniere( const char* pName, Float4 pColor, float pLiveTime )
{
  Sprite3d* lSpBan = new Banniere( pName, pColor );

  Double3 lPosBan( 0, 0, -100 );
  Double3 lScale( 20, 20, 20 );
  Double3 lSpeed( 0, 0, 80 );
  //  Double3 lSpin(0, 0, 20);
  //Double3 lSpeed(  randf(80),  randf(80), randf(80));
  Double3 lSpin(0, 0, randf(30));

  lSpBan->MkSetPOS(   lPosBan  );
  lSpBan->MkSetSPEED( lSpeed  );
  lSpBan->MkSetSCALE( lScale  );
  lSpBan->MkSetSPIN(  lSpin );
  lSpBan->SpriteFloat::set( SPRITE_LIFETIME, pLiveTime  );

  return lSpBan;
}
//---------------------------------------------------
int
WorldGame::userEvent( void *pUserData)
{
  //	std::cout << "WorldGame::gameWinner" << std::endl;
  World::gameWinner();

  // Mettre autre Sprite
  //	Sprite3dObj* lSpriteEx = new Sprite3dObj( new ObjDebris( 500, 20 ) );
  //	lSpriteEx->setTransf( cPilot->getTransf() );
  //	lSpriteEx->SpriteFloat::set( SPRITE_LIFETIME, 7 );

  // 	WorldControler::Add( lSpriteEx );

  Float4 lBanColor( 0.9, 0.9, 1.0, 0.5 ) ;

  Sprite3d* lSpBan = new Banniere( "Game.TextureYouWin", lBanColor );

  Double3 lPosBan( 0, 0, 20 );
  Double3 lSpeed( 0, 0, 20 );
  Double3 lScale( 40, 40, 40 );
  Double3 lSpin(25, 15, 15);

  lSpBan->MkSetPOS(   lPosBan  );
  lSpBan->MkSetSPEED( lSpeed  );
  lSpBan->MkSetSCALE( lScale  );
  lSpBan->MkSetSPIN(  lSpin );


  WorldControler::Add( lSpBan );



  ((WorldGame*)WorldControler::GetGameWorld())->getSceneManager()->addSceneTempo( 25, SceneManager::GameWinner  );

  return 1;
}
//---------------------------------------------------
void 
WorldGame::saveStateToFile( const char* pName ){
  if( cSceneManager != NULL )
    {
      cSceneManager->saveStateToFile( pName );
    }
}
//---------------------------------------------------
void
WorldGame::InitSprite()
{
  new ShipsMaker;
  new MinesMaker;
  new WeaponsMaker;
  new BonusMaker;
  new AsteroidesMaker;

  SpriteExplosion::Init();
}
//---------------------------------------------------

PSoundId sOceanSound=PBadSoundId;


bool
WorldGame::InitSound( const char* pPathSound)
{
  //	std::cout << "WorldGame::InitSound " << pPathSound << std::endl;
	
  new SoundControler( 20, pPathSound );

  WeaponsMaker::InitSound();
  ActionsShip::InitSound();
  Pilot::InitSound();

  /*
    WeaponsMaker::sSoundWeaponExplode         = LOAD_SAMPLE( "Explode.wav" );
    WeaponsMaker::sSoundWeaponExplodePlasma   = LOAD_SAMPLE( "ExplodePlasma.mp3" );
    WeaponsMaker::sSoundWeaponExplodePlasmaG  = LOAD_SAMPLE( "ExplodePlasmaG.wav" );


    ActionsShip::sSoundExplosion1   = LOAD_SAMPLE( "ActionExplosion1.wav" );
    ActionsShip::sSoundExplosion2   = LOAD_SAMPLE( "ActionExplosion2.wav" );
    ActionsShip::sSoundExplosion3   = LOAD_SAMPLE( "ActionExplosion3.wav" );
    ActionsShip::sSoundExplosion4   = LOAD_SAMPLE( "ActionExplosion4.wav" );
    ActionsShip::sSoundExplosionBig = LOAD_SAMPLE( "ActionExplosionBig.wav" );


    Pilot::sSoundWarp        = LOAD_SAMPLE( "PilotWarp.mp3" );
    Pilot::sSoundLaser       = LOAD_SAMPLE( "PilotLaser.wav" );
    *	Pilot::sSoundFireMissile = LOAD_SAMPLE( "PilotLaunchMissile.mp3" );

    */
  /*
    Pilot::sSoundWarpFailed     = LOAD_SAMPLE(""); 
    Pilot::sSoundCollision      = LOAD_SAMPLE(""); 
    Pilot::sSoundFinalExplosion = LOAD_SAMPLE(""); 
    Pilot::sSoundNextLife       = LOAD_SAMPLE(""); 
    Pilot::sSoundBonus          = LOAD_SAMPLE(""); 
  */
  return true;
}
//---------------------------------------------------
std::string WorldGame::sDataRootPath="";

const char*  
WorldGame::GetPathConfig( std::string & pName, WorldGame::PathType pPath, const char* pKey )
{
  std::map<std::string, std::string>::iterator lIterator = World::sConfig.find(pKey );
	
  if( lIterator == World::sConfig.end() )
    return NULL;

	
  std::map<std::string, std::string>::iterator lIteratorPath;

  switch( pPath )
    {
    case PathType::TEXTURE: lIteratorPath = World::sConfig.find( "Paths.Textures" );		break;
    case PathType::FONT   : lIteratorPath = World::sConfig.find( "Paths.Fonts" );		break;
    case PathType::SOUND  : lIteratorPath = World::sConfig.find( "Paths.Sounds" );		break;
    }
  pName = "";
  if( sDataRootPath.size() )
    {
      pName = sDataRootPath;         
    }
  
  if( lIteratorPath == World::sConfig.end() )
    pName += lIterator->second;
  else
    {
      
      pName +=  lIteratorPath->second ;
      pName += "/";
      pName +=  lIterator->second;
    }

  return pName.c_str();
}
//---------------------------------------------------

T3dTexture*
WorldGame::LoadTextureConfig( const char* pKey, GLenum pFilter  )
{
  std::cout << "WorldGame::LoadTextureConfig " << pKey << std::endl;


  std::string lName ;			
  GetPathConfig( lName, PathType::TEXTURE,  pKey );
		
  std::cout << "WorldGame::LoadTextureConfig" << pKey << " LOADING   >>>" << lName << std::endl;


  return  new T3dTexture( lName.c_str(), pFilter );

}
//---------------------------------------------------
