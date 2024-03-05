#include "SceneManager.h"
#include "Sprite3d/WorldControler.h"

//#include <Sprite3d/Scene.h>
#include "Space/Pilot.h"

#include <fstream>
#include <sstream>
#include <iomanip>

#include "Utils/PPFile.h"

// **************************************
SceneManager::SceneManager()
  :cCurScene(0),
   cWorld(NULL)
{
  cStrInfo[0] = '\0';


}

//------------------------------
SceneManager::~SceneManager()
{
  // Bug ! (les scene sont peut deja detruite ?
  //std::cout << "~SceneManager " << cSceneVect.size() << std::endl;
  //	for( unsigned int i=0; i<  cSceneVect.size(); i++ )
  //{
  //	std::cout << "~SceneManager " << i << " " << cSceneVect[i]->getStrName() << std::endl;
  //	if( cSceneVect[i] != NULL ){
  //		delete cSceneVect[i];
  //		cSceneVect[i] = NULL;
  //		}
  //		}
  //	std::cout << "~SceneManager end" << std::endl;

  cSceneVect.clear();
}
//------------------------------
const char*
SceneManager::getInfoScene(){
  return cStrInfo;
}
//------------------------------
void SceneManager::addScene( Sprite3d *pSprite, float pLiveTime )
{
  pSprite->setDeleteControler(this);
  pSprite->setAction( SPRITE_ACTION_KILL,        this );
  pSprite->setAction( SPRITE_ACTION_LEAVE_WORLD, this );


  if( pLiveTime != -1 )
    pSprite->SpriteFloat::set( SPRITE_LIFETIME, pLiveTime  );


  cSceneVect.push_back( pSprite );
}
//------------------------------
// Pour laisser du temps entre deux scenes

void SceneManager::addSceneTempo( float pLiveTime, GameFinish cGameFinish )
{
  Sprite3d* lSprite = new Sprite3d(0.00001, pLiveTime);
  lSprite->setDeleteControler(this);
  lSprite->setAction( SPRITE_ACTION_KILL, this );

  lSprite->MkSetUSER5( static_cast<float>(cGameFinish ));

  cSceneVect.push_back( lSprite );
}
//------------------------------
// Pour laisser du temps entre deux scenes

void SceneManager::setCurrentSceneTempo( float pLiveTime, GameFinish cGameFinish )
{
  if( cCurScene == cSceneVect.size() )
    {
      return;
    }

  cSceneVect[cCurScene]->SpriteFloat::set( SPRITE_LIFETIME, pLiveTime );
  cSceneVect[cCurScene]->MkSetUSER5( static_cast<float>(cGameFinish ));
}
//----------------------------------------------------------
static const char* sStrLevel = "(Level";
static const char* sStrScene = "Scene";
static const char* sStrTime  = "Time";
static const char* sStrDifficulty  = "Difficulty";
static const char* sStrNumSav  = "NumSav";

//-------------
std::string SceneManager::sDirSavPath  = "";
const char* SceneManager::sDirSav      = "sav";
static const char* sAutoSavFile = "autosave";
static int sSavNum=1;
//-------------

void
SceneManager::write( std::ostream & pOs){

  pOs << sStrLevel << ' '
      << sStrScene << ' ' << cCurScene  << ' '
      << sStrTime << ' ' << (long)WorldControler::sTime << ' '
      << sStrDifficulty << ' ' << WorldControler::sDifficultyLevel << ' '
      << sStrNumSav << ' ' << sSavNum << ' '
      << ')';

}
//-------------
bool
SceneManager::read( std::istream & pIs ){

  std::string lTmpStr;

  long lCurScene = 0;
  long lTime =0;

  pIs >> lTmpStr;
  std::cout << "read <" << lTmpStr << ">" <<std::endl;
		

  if( lTmpStr.compare( sStrLevel ) != 0 )
    return false;


  pIs >> lTmpStr;
  std::cout << "read <" << lTmpStr << ">" <<std::endl;
  if( lTmpStr.compare( sStrScene ) != 0 )
    return false;
  pIs >> lCurScene;


  pIs >> lTmpStr;
  std::cout << "read <" << lTmpStr << ">" <<std::endl;
  if( lTmpStr.compare( sStrTime ) != 0 )
    return false;
  pIs >> lTime;


  pIs >> lTmpStr;
  std::cout << "read <" << lTmpStr << ">" <<std::endl;
  if( lTmpStr.compare( sStrDifficulty ) != 0 )
    return false;

  pIs >> WorldControler::sDifficultyLevel;

  pIs >> lTmpStr;
  std::cout << "read <" << lTmpStr << ">" <<std::endl;
  if( lTmpStr.compare( sStrNumSav ) != 0 )
    return false;

  pIs >> sSavNum;


  pIs >> lTmpStr; // la parenthese

  cCurScene = lCurScene;
  ////// !!!!!!!!!!!    WorldControler::sTime = lTime;

  return true;
}

//-------------
GLboolean
SceneManager::restoreStateFromFile( World* pWorld,  const char* pName ){

 

  std::cout << "*** restoreStateFromFile " << pName << std::endl;

  if( Pilot::ThePilot == NULL )
    return GL_FALSE;

  std::ifstream lFis( pName );
  if( lFis.fail()){
    std::cout << "Opening " << pName << " failed !" << std::endl;
    return GL_FALSE;
  }

  if( read( lFis )== false ){
    std::cout << "read scene fail" << std::endl;
    return GL_FALSE;
  }

  if( Pilot::ThePilot->read(lFis)== false ){
    std::cout << "read pilot fail" << std::endl;
    return GL_FALSE;
  }


  lFis.close();


  internalGo( pWorld );
  return GL_TRUE;
}
//-------------
GLboolean
SceneManager::saveStateToFile( const char* pName ){

  std::cout << "SceneManager::saveStateToFile " << pName << std::endl;

  std::ostringstream lStrFile;
  if( sDirSavPath.size() )
    {
      lStrFile << sDirSavPath << '/';
    }
  lStrFile << sDirSav;
  if( PPu::PPFile::DoMkdir( lStrFile.str()  ) == false)
    {
      std::cerr << "*** Error : SceneManager::saveStateToFile failed to create directory <<<"
                << lStrFile.str() << ">>>" << std::endl;
      return GL_FALSE;
    }
  //  else
  //   {
      //     std::cerr << "*** Info : SceneManager::saveStateToFile  create directory <<<"
  //              << lStrFile.str() << ">>>" << std::endl;
 
  //   }
          
  lStrFile  <<'/'<< pName;
  lStrFile << '_';
  lStrFile << std::setfill('0') << std::setw(3) <<  sSavNum++;
  lStrFile << ".sav" ;


  std::cout << "\tsaveStateToFile " << lStrFile.str() << std::endl;

  if( Pilot::ThePilot == NULL )
    return GL_FALSE;

  std::ofstream lFos( lStrFile.str().c_str());
  if( lFos.bad())
    return GL_FALSE;

  std::cout << "\tsaveStateToFile ok " << lStrFile.str() << std::endl;

  write( lFos );
  lFos << std::endl;

  Pilot::ThePilot->write(lFos);
  lFos << std::endl;

  lFos.close();
  return GL_TRUE;
}
//-----------------------------------------------------------
// Lance la premiere scene du scenario, c'est la fin
// de la scene (kill -> endScene ) qui provoque
// l'execution de la scene suivante
// la fin de la derniere scene provoque la fin du scenario
// et donc la victoire

void
SceneManager::internalGo(World* pWorld)
{

  std::cout << "SceneManager::go " << cCurScene << '/' <<  cSceneVect.size() << ' ' <<  cSceneVect[cCurScene]->getStrInfo() << std::endl;

  sprintf( cStrInfo, "%d/%lu | %s", cCurScene, cSceneVect.size(), cSceneVect[cCurScene]->getStrInfo() );
  cSceneVect[cCurScene]->resetLife();  // remet a jour l heure de creation
  pWorld->add(cSceneVect[cCurScene]);
}
//------------------------------
void
SceneManager::go(World* pWorld)
{
  sSavNum =1;

  internalGo( pWorld);

}
//------------------------------
void
SceneManager::resetCurrentSceneFromBegin( Sprite3dPilot* pPilot )
{
  cWorld = WorldControler::GetCurrentWorld();

  if( cWorld )
    {
      cWorld->removeSprite( (Sprite3d*) pPilot );
      cWorld->removeSprite( cSceneVect[cCurScene] );

      cWorld->killAllSprite();

      cSceneVect[cCurScene]->resetLife();  // remet a jour l heure de creation

      cWorld->add( (Sprite3d*) pPilot );
      cWorld->add( cSceneVect[cCurScene]   );
    }
}
//------------------------------
int
SceneManager::endScene()
{
  std::cout << "SceneManager::endScene" << std::endl;
  // le Sprite est elimine par World qui appele execDelete

  cSceneVect[cCurScene]->leaveWorld();
  cCurScene++;

  if( cCurScene == cSceneVect.size() )
    {
      sprintf( cStrInfo, "Finish");
      WorldControler::WC->userEvent(NULL);
      return  0;
    }

  if( cSceneVect[cCurScene]->getSpriteType() < 0 )
    {
      std::ostringstream lOs ;
      lOs << sAutoSavFile << '_'
	  << cSceneVect[cCurScene]->getStrInfo() << '_'
	  << WorldControler::sDifficultyLevel;
      //     saveStateToFile(sAutoSavFile);
      saveStateToFile(lOs.str().c_str());
    }

  sprintf( cStrInfo, "%d/%lu | %s", cCurScene, cSceneVect.size(), cSceneVect[cCurScene]->getStrInfo());
  cSceneVect[cCurScene]->resetLife();

  if( WorldControler::GetCurrentWorld())
    WorldControler::Add(cSceneVect[cCurScene]);


  return 0;
}
//------------------------------
GLboolean
SceneManager::leaveWorld( Sprite3d &pMySprite, void*pParam )
{
  return GL_FALSE;  // Pour empecher la detruction, passage par kill oubligee
}
//------------------------------
GLboolean SceneManager::kill( Sprite3d &pMySprite, void *pParam )
{
  std::cout << "SceneManager::kill" << std::endl;

  endScene();

  switch( static_cast<int>(pMySprite.MkGetUSER5())  )
    {
    case GameOver:
      ::strcpy( cStrInfo, "Game Over" );
      WorldControler::GameOver();
      return GL_TRUE;

    case GameWinner:
      ::strcpy( cStrInfo, "Win " );
      WorldControler::GameWinner();
      return GL_TRUE;
    }
  return GL_TRUE;
}

//------------------------------------------------
bool
SceneManager::execDelete( Sprite3d* pToDel )
{
  bool lFlagDel = false;
  for( unsigned int i=0; i<  cSceneVect.size(); i++ )
    {
      if( cSceneVect[i] == pToDel )
        {
          delete cSceneVect[i];
          lFlagDel = true;
          cSceneVect[i] = NULL;					
        }
    }

  if( lFlagDel )
    return true;

  return false;
}




