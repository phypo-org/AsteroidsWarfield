#include <stdlib.h>
#include <time.h>

#include <T3d/T3dLoadImg.h>
#include <T3d/T3dColor.h>

#include <O3d/O3dObjPrim.h>
#include <O3d/O3dObjText.h>

#include <O3d/O3dObjPLibFont.h>

#include <Sprite3d/ObjOdron.h>
#include <Sprite3d/World.h>
#include <Sprite3d/ObjText2d.h>
#include <Sprite3d/ObjText.h>
#include <Sprite3d/Random.h>
#include <Sprite3d/SoundControler.h>

#include <U3d/WeaponsMaker.h>


#include "MainMenu.h"

#include <Space/Pilot.h>
#include <Space/SceneAsteroide.h>
#include <Space/ShipsMaker.h>
#include <Space/Def.h>
#include <Space/WorldGame.h>

#include <U3d/Sky.h>

#include <iostream>

#include <U3d/Banniere.h>

#include <FL/Fl.H>
#include <FL/glut.H>
#include <FL/Fl_Native_File_Chooser.H>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Hor_Nice_Slider.H>

#include "MyFlWidget.h"
#include "MySlider.h"
#include <memory>


#include "Utils/PPSingletonCrtp.h"


#define StartDiag StartDialog::Instance()

//**************************************

class StartDialog  : public virtual PPSingletonCrtp<StartDialog>{
	
  Fl_Double_Window* cMyWindow = nullptr;
	
  friend class PPSingletonCrtp;
	
  // std::unique_ptr<MyCheckbutton> cCheckMute; 
  MyCheckbutton    * cCheckMute;
  
  MainMenu * cMainMenu = nullptr;

public:
  StartDialog() {;}
   void init( MainMenu & rMainMenu );

  std::string cExecSavLevel;

  Fl_Double_Window* getMyWindow()  { return cMyWindow;}

protected:
	
  static void StartExtremCB( Fl_Widget*, void*pUserData );
  static void StartHardCB( Fl_Widget*, void*pUserData );
  static void StartMediumCB( Fl_Widget*, void*pUserData );
  static void StartEasyCB( Fl_Widget*, void*pUserData );
  static void StartGentileCB( Fl_Widget*, void*pUserData );

  static void ReadSavedLevelCB( Fl_Widget*, void*pUserData );
  static void ReadSaveFileCB ( Fl_File_Chooser *cFc,  void  *cData);
  static void QuitAll( Fl_Widget*, void* pUserData );

  static void CheckCB( Fl_Widget*, void*pUserData );

  void maj();

public:
  static bool IsAlreadyRunning() { return StartDiag.cMyWindow != nullptr; }

};
//----------------------------------------
 
void
StartDialog::init(MainMenu & rMainMenu)
{


  //  std::cout << "StartDialog::init " << std::endl;
  
  cMainMenu = & rMainMenu;
  int lX = 20;
  int lY= 20;


  int lW = 150;
  int lH = 25;
  int lYStep = 30;

  cMyWindow = new Fl_Double_Window(200, 330, "Asteroid Fighter");
  cMyWindow->position( 1000, 300 );
  cMyWindow->set_modal();
  //  cMyWindow->clear_border();
	
  //	cMyWindow->callback((Fl_Callback*)CancelCB, this);

	
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Start EXTREME ");
    o->callback((Fl_Callback*)StartExtremCB, this );
  } // Fl_Button* o
  lY += lYStep;;
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Start HARD");
    o->callback((Fl_Callback*)StartHardCB, this );
  } // Fl_Button* o
  lY += lYStep;;
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Start MEDIUM");
    o->callback((Fl_Callback*)StartMediumCB, this );
  } // Fl_Button* o
  lY += lYStep;;
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Start EASY");
    o->callback((Fl_Callback*)StartEasyCB, this );
  } // Fl_Button* o
  lY += lYStep;;
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Start GENTILE");
    o->callback((Fl_Callback*)StartGentileCB, this );
  } // Fl_Button* o
  lY += lYStep;;
  lY += lYStep;;
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Read saved level");
    o->callback((Fl_Callback*)ReadSavedLevelCB, this );
  } // Fl_Button* o
  lY += lYStep;
  cCheckMute = new MyCheckbutton( lX, lY, lW, lH, "Sound MUTE", CheckCB, this, 0 );
	
  if(	SoundControler::sMute == GL_FALSE )
    cCheckMute->value( 0 );
  else
    cCheckMute->value( 1 );

  lY += lYStep;
  lY += lYStep;
  { Fl_Button* o = new Fl_Button(lX, lY, lW, lH, "Quit game");
    o->callback((Fl_Callback*)QuitAll, this );
  } // Fl_Button* o
  lY += lYStep;
	
  cMyWindow->end();
		
  cMyWindow->show( 0, nullptr);
  maj();


  //long long i=0;   
 while (Fl::wait() && cMyWindow != nullptr )
   {
     //    if( i++ %500 == 0)
       //      std::cout << "." << std::flush;
   }

 //  std::cout << "*********************************** FIN DIALIOGUE **************************" << std::endl;

}

//----------------------------------------
void StartDialog::maj()
{	
  //  std::cout << "-- Sound Mute : " << SoundControler::sMute << std::endl;
  bool lFlagSoundMute          = (cCheckMute->value() != 0 );
		
  if( lFlagSoundMute )
    SoundControler::sMute = GL_TRUE;
  else
    SoundControler::sMute = GL_FALSE;

  //  std::cout << "++ Sound Mute : " << SoundControler::sMute << std::endl;
}
//----------------------------------------
void StartDialog::StartExtremCB( Fl_Widget*, void* pUserData ) {
    std::cout << "StartExtremCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);

  WorldControler::sDifficultyLevel = 4;

  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow = nullptr;						 
}
//----------------------------------------
void StartDialog::StartHardCB( Fl_Widget*, void* pUserData ) {
  std::cout << "StartHardCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);

  WorldControler::sDifficultyLevel = 3;


  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow = nullptr;						 
}
//----------------------------------------
void StartDialog::StartMediumCB( Fl_Widget*, void* pUserData ) {
  std::cout << "StartMediumCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);
	
  WorldControler::sDifficultyLevel = 2;


  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow = nullptr;						 
}
//----------------------------------------
void StartDialog::StartEasyCB( Fl_Widget*, void* pUserData ) {
  std::cout << "StartEasyCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);

  WorldControler::sDifficultyLevel = 1;


  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow = nullptr;						 
}
//----------------------------------------
void StartDialog::StartGentileCB( Fl_Widget*, void* pUserData ) {
  std::cout << "StartGentileCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);

  WorldControler::sDifficultyLevel = 0;


  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow = nullptr;						 
}
//----------------------------------------
void StartDialog::QuitAll( Fl_Widget*, void* pUserData ) {
  std::cout << "StartGentileCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);
	

	
  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow = nullptr;						 
  //lDialog->cMainMenu.getMyControler()->quit();
	
  ::exit(0);
}
//----------------------------------------
void  StartDialog::ReadSaveFileCB ( Fl_File_Chooser *iFc,  void  *iUserData)
{
  if( iFc->value()  )
    {
      std::string lFilename = iFc->value();
      StartDialog* lDialog = reinterpret_cast<StartDialog*>(iUserData);
      
      if( lFilename.length() > 0)
	{
	  std::cout << lFilename << std::endl;
	  lDialog->cExecSavLevel = lFilename;
	  
	  //	  Fl::delete_widget( lDialog->cMyWindow );
          //          lDialog->cMyWindow = nullptr;						 
	}
    }
}
//----------------------------------------
void StartDialog::ReadSavedLevelCB( Fl_Widget*, void* pUserData ) {
  std::cout << "ReadSavedLevelCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);

  
  std::string  lStrPath;
  if( SceneManager::sDirSavPath.size() )
    {
      lStrPath =  SceneManager::sDirSavPath;
      lStrPath += '/';
    }
  lStrPath +=  SceneManager::sDirSav;

  
  Fl_File_Chooser* lFc = new Fl_File_Chooser(lStrPath.c_str(), "*.sav",
                                             Fl_File_Chooser::SINGLE,
                                             "Open save file");
  lFc->type(FL_HOLD_BROWSER);
  //	lFc->filetype(Fl_File_Browser::FILES);
  lFc->filter("*.sav");

  lFc->callback( ReadSaveFileCB, pUserData );			 
  lFc->show();
  //  long long i=0;
  while (lFc->visible()) {
    Fl::wait();
    
    //  if( i++ %500 == 0)
    //      std::cout << ":" << std::flush;
  }
  std::cout << "fin ReadSavedLevelCB Window:" <<  lDialog->cMyWindow << std::endl;
  //  lDialog->cMyWindow->hide();
  
  Fl::delete_widget( lDialog->cMyWindow );
  lDialog->cMyWindow= nullptr;

  std::cout << std::endl << "Fin StartDialog::ReadSavedLevelCB " << std::endl;
}
//----------------------------------------
void StartDialog::CheckCB( Fl_Widget*, void*pUserData )
{
  std::cout << "CheckCB" << std::endl;
  StartDialog* lDialog = reinterpret_cast<StartDialog*>(pUserData);
	
  lDialog->maj(); 
}
//----------------------------------------
extern void CallStartDialog(  MainMenu & iMainMenu)
{
  //  std::cout << "CallStartDialog " <<std::endl;
  
  if( StartDiag.IsAlreadyRunning() == false )
    {
      StartDiag.init( iMainMenu );
    }
}
//****************************************************************************
//****************************************************************************
//****************************************************************************


MainMenu* MainMenu::TheMainMenu = NULL;

//**************************************
MainMenu::MainMenu( int pSize, WorldControler* pControl, O3dKamera* pKamera, Double3& pMax,
                    O3dObjProps *pProps)
  :World(pControl, pKamera, pMax, pProps)
  ,cSize( pSize )
  ,cColorTextNormal( 1.0, 1.0, 0.0, 1.0 )
   //,cMuteSoundButton( NULL )
{
  TheMainMenu = this;
}

//-----------------------------
void
MainMenu::mouseMove( int pX, int pY )
{
  //	std::cout << "MainMenu::mouseMove" << std::endl;
}
//-----------------------------
void
MainMenu::mouseButton( int pButton, int pState, int pX, int pY)
{

}
//-----------------------------
long
MainMenu::userAction( Sprite3d &pMySprite, void*pParam0, void*pParam1, void*pParam2 )
{
  //	std::cout << "UserAction -> " << (char*) pParam0 << ":"<< (long) pParam1 << ":" <<  (long) pParam2 << std::endl;
  return 666;
}
//-----------------------------
void
MainMenu::AfficheLine( int pX, int pY, const char* pStr ){
 	
	
  O3dObjPLibFont* lObjText = new O3dObjPLibFont( FL_HELVETICA_BOLD, 5, pStr );

  //	O3dObjText2d* lObjText = new O3dObjText2d( WorldControler::sCurrentFont, 16, 3, pStr );
  Sprite3dObj* lText = new  Sprite3dObj( lObjText );
  
  Double3 lPos( pX, pY, 0.0 );
  lText->getTransf().TransfDouble3::set( POS, lPos ); 
 
  cPropsTextNormal.ObjPropsFloat4::set( MATERIAL, cColorTextNormal );
  lText->setObjProps( &cPropsTextNormal );
  add( lText );  
	 
}

//-----------------------------
void MainMenu::drawHelp()
{
  int pX = -120;
  int pY =  60;
  int lStep = -5;
	
  T3dColor::White();

 

  AfficheLine( pX, pY, "****** Quick help* ******" );
  pY += lStep;	AfficheLine( pX, pY, "Quit Game           -> Q / Esc" );
  pY += lStep;	AfficheLine( pX, pY, "New game            -> N" );
  pY += lStep;	AfficheLine( pX, pY, "Main Menu           -> M" );
  pY += lStep;	AfficheLine( pX, pY, "Help                -> H / F1" );
  pY += lStep;	AfficheLine( pX, pY, "Pause               -> P" );
  pY += lStep;	AfficheLine( pX, pY, "Resume              -> R" );
  pY += lStep;	AfficheLine( pX, pY, "Full screen/Window  -> F" );

  pY += lStep;
  pY += lStep;

  pY += lStep;	AfficheLine( pX, pY, "Use mouse                       to move spaceship" );
  pY += lStep;	AfficheLine( pX, pY, "Use SPACEBAR                    to partial recharge field (use energy)" );
  pY += lStep;	AfficheLine( pX, pY, "Use middle mouse button or 'A'  to warp to cursor position(use energy)");
  pY += lStep;	AfficheLine( pX, pY, "Use left   mouse button or '1'  to fire with energy weapon" );
  pY += lStep;	AfficheLine( pX, pY, "Use right  mouse button or '2'  to fire with rocket weapon" );
  pY += lStep;	AfficheLine( pX, pY, "Use                        '3'  to fire with mine weapon" );
  pY += lStep;	
  pY += lStep;	AfficheLine( pX, pY, "Use CTRL      with mouse button for side fire" );
  pY += lStep;	AfficheLine( pX, pY, "Use SHIFT     with mouse button for top fire" );
  //	pY += lStep;	AfficheLine( pX, pY, "Use ALT   with mouse button for top, side and front fire" );
	



  add( new Sky( 10*cSize, cSize*100 ) );

  Sprite3d* lSp;

  Double3 lTransfNull( 0, 0, 0 );

  srand( ::time(NULL) );

  for( int i= 0; i< 20; i++ )
    {
      lSp=TheAsteroidesMaker->makeSpriteAsteroide( ASTEROIDE_PIERRE/*ASTEROIDE_CRISTAL*/, randp(9)+6, randp(2)+2 );
      //	Sprite3d* lAster=MAKE_INTERCEPTOR2;
      Double3 lSpinAster(  randf(20), randf(20), randf(20));
      lSp->MkSetSPIN( lSpinAster );
      lSp->MkGetPOS()[0] = randf(150 );
      lSp->MkGetPOS()[1] = randf(150 );
      lSp->MkGetPOS()[2] = randf( 20 )-100;
      lSp->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Asteroide") );

      add( lSp );
    }

	

  {
    lSp = TheShipsMaker->makeShip( BASE_TORE, 10, 20, 0, 0, 0, 1 );
    lSp->MkSetSPEED( lTransfNull );
    Double3 lSpinAster( 10, 8, 9 );
    lSp->MkSetSPIN( lSpinAster );
    Double3 lGrow( 1.6, 1.6, 1.6 );
    lSp->MkSetSCALE( lGrow );
    //		lSp->MkGetPOS()[0] = -100;
    //		lSp->MkGetPOS()[1] = 60;
    //		lSp->MkGetPOS()[2] = -40;
    lSp->MkGetPOS()[0] = 100;
    lSp->MkGetPOS()[1] = 60;
    lSp->MkGetPOS()[2] = -40;
    lSp->setMask( InteractObstacle, InteractObstacle);
    lSp->setAction( SPRITE_USER_ACTION, this, const_cast<char*>("Tore") );

    add( lSp );
  }

}
//-----------------------------
GLboolean
MainMenu::initStart(int pNiveau, const char* pFile)
{
  drawHelp();
  return GL_TRUE;
}
//------------------------------------------------
void
MainMenu::reshapeWorld(int pWidth, int pHeight)
{
  leaveWorld();
  enterWorld( pWidth,  pHeight );
}
//-----------------------------------------------
void
MainMenu::enterWorld( int pWidth, int pHeight)
{  
  CallStartDialog( *this );

  //  std::cout << "MainMenu::enterWorld " <<  StartDiag.cExecSavLevel.c_str()    
  //            << "  Win:" <<  (void*) StartDiag.getMyWindow() << std::endl;
  
  
  if( StartDiag.cExecSavLevel.length() )
    TheMainMenu->getMyControler()->start( 0, StartDiag.cExecSavLevel.c_str() );
  else
    TheMainMenu->getMyControler()->start();
}
//------------------------------------------------
void
MainMenu::leaveWorld()
{
	
}
//**************************************

