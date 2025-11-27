#include <FL/glut.H>

#include "O3d/O3dKamera.h"
#include "T3d/T3dPrimitiv.h"
#include "T3d/T3dColor.h"
#include "T3d/T3dFont.h"
#include "T3d/T3dFontRaster.h"

#include <iostream>

#include "World.h"
#include "WorldControler.h"
#include "ObjOdron.h"
#include "Sprite3d.h"
#include "Collision.h"
#include "Sprite3dPilot.h"
#include "SoundControler.h"

#include <FL/Fl.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/glut.H>

WorldControler *WorldControler::WC = NULL;


#ifdef PUI_WIN
GLboolean	WorldControler::PuiInUse = GL_FALSE;
#endif


float WorldControler::sTime = 0.0;




float WorldControler::sRatio=1.0/25.0;
int   WorldControler::sMicroRate=static_cast<int>(1000/25.0);
T3dFont* WorldControler::sCurrentFont=NULL;

int   WorldControler::sDifficultyLevel=2;

int WorldControler::sDebug =0;

int   WorldControler::sKeyModifiers=0;
int   WorldControler::sOldKeyModifiers=0;



//--------------------------------
// Pas au point ! -> plantage



void saveLastLevel()
{
  Fl_Native_File_Chooser fnfc;
  fnfc.title("Pick a file for write");
  fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
  fnfc.filter("AF\t*.sav\n"
	      "3D Files\t*.{sav}");
  fnfc.directory(".");           // default directory to use
  // Show native chooser
  switch ( fnfc.show() )
    {
    case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
    case  1: printf("CANCEL\n");                      break;  // CANCEL
    default:
      {
	if( WorldControler::WC != NULL && WorldControler::GetGameWorld() != NULL)
	  WorldControler::GetGameWorld()->saveStateToFile( fnfc.filename());						
      }	
    }
}
//**************************************
WorldControler::WorldControler(int pWidth, int pHeight, bool pFullScreen)
  :cCurrentWorld( NULL),
   cMainWorld(NULL),
   cGame(NULL),
   cPause(0),
   cFullScreen(pFullScreen),
   cLeftButtonDown(GL_FALSE),
   cMiddleButtonDown (GL_FALSE),
   cRightButtonDown( GL_FALSE),
   cMouseX(-1),
   cMouseY(-1),
   cWidth(pWidth),
   cHeight(pHeight)
{
  sCurrentFont = T3dFont::DefaultFont;
  WC = this;

  if(cFullScreen)
    glutFullScreen();

}
//--------------------------------
WorldControler::~WorldControler()
{
  delete cGame;
  delete cMainWorld;
  // 2025-11-19 Antigravity: Fix memory leak
  delete cHelpWorld;
}
//--------------------------------
void
WorldControler::Add( Sprite3d* pSprite) {
  WC->cCurrentWorld->add( pSprite );
}
//--------------------------------
void WorldControler::setCurrent( World*pCurrent)
{
  if( cCurrentWorld )
    cCurrentWorld->leaveWorld();
  
  cCurrentWorld = pCurrent;
  
  int W = glutGet(GLUT_WINDOW_WIDTH);
  int H = glutGet(GLUT_WINDOW_HEIGHT);
  
  //  std::cout << "******************* call setSize W:" << W << " H:" << H << std::endl;
  setSize( W, H );
  
  if( cCurrentWorld )
    cCurrentWorld->enterWorld( cWidth, cHeight);
  
  cCurrentWorld->getKamera()->setAspectRatio(  cWidth, cHeight );           	     
} 
//--------------------------------
void
WorldControler::setSize( int pWidth, int pHeight)
{
  cWidth = pWidth;
  cHeight = pHeight;
  
  glViewport(0, 0, (GLsizei) pWidth, (GLsizei) pHeight);
  
  if( cCurrentWorld )
    cCurrentWorld->getKamera()->setAspectRatio(  cWidth, cHeight );
}
//--------------------------------
void
WorldControler::quit()
{
  if( cCurrentWorld == cMainWorld || cMainWorld == NULL )
    exit(0);
  
  setCurrent(cMainWorld);
}
//--------------------------------
void
WorldControler::mainWorld()
{
  if( cCurrentWorld == cGame || cCurrentWorld == cHelpWorld || cCurrentWorld == NULL )
    setCurrent(cMainWorld);

}
//--------------------------------
void
WorldControler::helpWorld()
{
  if( cCurrentWorld == cGame || cCurrentWorld == cMainWorld || cCurrentWorld == NULL )
    setCurrent(cHelpWorld);

}
//--------------------------------
void
WorldControler::resume()
{
  if( cCurrentWorld == cMainWorld|| cCurrentWorld == cHelpWorld  )
    setCurrent(cGame);
}
//--------------------------------
bool
WorldControler::start( int pLevel, const char* pFileNameSav)
{
  if( cCurrentWorld == cMainWorld )
    {
      cGame->freeRessources();
      if( cGame->initStart( pLevel, pFileNameSav) == GL_FALSE )
        return GL_FALSE;
      setCurrent( cGame );
      return GL_TRUE;
    }
  return GL_FALSE;
}
//------------------------------------------------------
//-------------------- STATIC --------------------------
//------------------------------------------------------

void WorldControler::MouseMove( int pX, int pY )
{
  //	std::cout << "<<<WorldControler::MouseMove " << sTime  << std::endl;

  //	sOldKeyModifiers = sKeyModifiers;
  //	sKeyModifiers = glutGetModifiers();

#ifdef PUI_WIN
  /*
    if( PuiInUse )
    {
    if( puMouse ( pX, pY ) )
    {
    glutPostRedisplay () ;
    return;
    }
    }
  */
#endif


	
	
  WC->cMouseX = pX;
  WC->cMouseY = pY;
  if( WC->cCurrentWorld )
    WC->cCurrentWorld->setPilot( pX, pY );

  //	std::cout << "WorldControler::MouseMove " << sTime  << " >>>" << std::endl;
}
//--------------------------------
void WorldControler::MouseButton( int pButton, int pState, int pX, int pY )
{
  //	std::cout << "<<<WorldControler::MouseButton " << sTime  << std::endl;

  /*
    #ifdef PUI_WIN
    if( PuiInUse )
    {
    if( puMouse ( pButton, pState, pX, pY ) )
    {
    glutPostRedisplay () ;
    return;
    }
    }
    #endif
  */

  sOldKeyModifiers = sKeyModifiers;
  sKeyModifiers = glutGetModifiers();

  WC->cMouseX = pX;
  WC->cMouseY = pY;

  switch( pButton )
    {
    case GLUT_LEFT_BUTTON:
      if( pState == GLUT_DOWN )
	WC->cLeftButtonDown = GL_TRUE;
      else
	WC->cLeftButtonDown = GL_FALSE;
      break;

    case GLUT_MIDDLE_BUTTON:
      if( pState == GLUT_DOWN )
	WC->cMiddleButtonDown = GL_TRUE;
      else
	WC->cMiddleButtonDown = GL_FALSE;
      break;

    case GLUT_RIGHT_BUTTON:
      if( pState == GLUT_DOWN )
	WC->cRightButtonDown = GL_TRUE;
      else
	WC->cRightButtonDown = GL_FALSE;
      break;

    default:;
    }
  WC->cCurrentWorld->mouseButton( pButton, pState, pX, pY );

  //	std::cout << "WorldControler::MouseButton " << sTime  << " >>>"  << std::endl;
}
//--------------------------------

void
WorldControler::SpecialKey( int pKey, int pX, int pY )
{
  //	std::cout << "<<<WorldControler::SpecialKey " << sTime  << std::endl;
  /*
    #ifdef PUI_WIN
    if( PuiInUse )
    {
    if( 	puKeyboard ( pKey, PU_DOWN ) )
    {
    glutPostRedisplay () ;
    return ;
    }
    }
    #endif
  */
	
  sOldKeyModifiers = sKeyModifiers;
  sKeyModifiers = glutGetModifiers();

  //	std::cout << "SpecialKey:" << pKey << ":" << (int)pKey << '(' << pX << ',' << pY <<')'<< " " << sKeyModifiers << std::endl;


  switch( pKey )
    {
    case GLUT_KEY_F1 :
      WC->helpWorld();
      break;

    case GLUT_KEY_LEFT:
      World::sFlagCollision3d = false;
      break;

    case GLUT_KEY_RIGHT:
      World::sFlagCollision3d = true;
      break;

    }

  WC->cCurrentWorld->setPilotSpecialKey( pKey, pX, pY );


  //	std::cout << "WorldControler::SpecialKey " << sTime  << " >>>" << std::endl;
}
//--------------------------------
void
WorldControler::KeyUp( unsigned char pKey, int pX, int pY )
{
  //	std::cout << "<<< WorldControler::KeyUp " << sTime  << std::endl;

  //	sOldKeyModifiers = sKeyModifiers;
  //	sKeyModifiers = glutGetModifiers();

  //	std::cout << "KeyUp:" << pKey << ":" << (int)pKey << '(' << pX << ',' << pY <<')'<< " " << sKeyModifiers << std::endl;

  WC->cCurrentWorld->setPilotKeyUp( pKey, pX, pY );

  //	std::cout << "WorldControler::KeyUp " << sTime  << " >>>" << std::endl;
}
//--------------------------------
void
WorldControler::Key( unsigned char pKey, int pX, int pY )
{
  //	std::cout << "<<< WorldControler::Key " << sTime  << std::endl;

  O3dKamera& lKam= *(WC->cCurrentWorld->getKamera());

  sOldKeyModifiers = sKeyModifiers;
  sKeyModifiers = glutGetModifiers();

  //	std::cout << "Key:" << pKey << ":" << (int)pKey << '(' << pX << ',' << pY <<')' << " " << sKeyModifiers <<std::endl;


  switch( pKey )
    {
    case 'q':
    case 'Q':
    case 27:
      WC->quit();
      break;;

    case 'p':
    case 'P':
      if( WC->cCurrentWorld == WC->cGame )
	WC->cPause ^= 1;
      break;

    case 'M':
    case 'm':
      WC->mainWorld();
      break;

    case 'H':
    case 'h':
      WC->helpWorld();
      break;


    case 'F':
    case 'f':
      if( WC->cFullScreen == 0)
	{
	  WC->cFullScreen = 1;
	  glutFullScreen(	);
	}
      else
	{
	  glutReshapeWindow(WC->cWidth, WC->cHeight );
	  WC->cFullScreen = 0;
	}
      break;
			
    case 'S':
    case 's':
      if( SoundControler::sMute == GL_TRUE )
	SoundControler::sMute = GL_FALSE;
      else
	SoundControler::sMute = GL_TRUE;
      break;
			

    case 'R':
    case 'r':
      if( WC->cCurrentWorld == WC->cMainWorld )
	WC->resume();
      break;

    case 'N':
    case 'n':
      if( WC->cCurrentWorld == WC->cMainWorld )
	WC->start();
      break;

    default:
      if( WC->cCurrentWorld == WC->cMainWorld )
	{
	  WC->selectNewGame( pKey, pX, pY );
	}
    }


  if( sDebug )
    switch( pKey )
      {
      case 'X':
	lKam.TransfDouble3::get( ANGLE )[0] += 15;
	break;
      case 'x':
	lKam.TransfDouble3::get( ANGLE )[0] -= 15;
	break;
      case 'Y':
	lKam.TransfDouble3::get( ANGLE )[1] += 15;
	break;
      case 'y':
	lKam.TransfDouble3::get( ANGLE )[1] -= 15;
	break;
      case 'Z':
	lKam.TransfDouble3::get( ANGLE )[2] += 15;
	break;
      case 'z':
	lKam.TransfDouble3::get( ANGLE )[2] -= 15;
	break;
      }




  WC->cCurrentWorld->setPilotKey( pKey, pX, pY );

  //	std::cout << "WorldControler::Key " << sTime  << " >>>" << std::endl;
}

//--------------------------------
void WorldControler::Display()
{
  //	std::cout << "<<< WorldControler::Display " << sTime  << " >>>" << std::endl;

  Redraw(0);

}
//--------------------------------
void WorldControler::Redraw( int p)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f( 1, 0, 0 );




  if(WC->cCurrentWorld)
    WC->cCurrentWorld->drawWorld();


  /*
    #ifdef PUI_WIN
    if( PuiInUse )
    {
    puDisplay () ;
    }
    #endif
    //	std::cout << "WorldControler::Display " << sTime  << " >>>" << std::endl;
    */
  glutSwapBuffers();

}
//----------------------------------
void WorldControler::Visibility( int pState )
{
  if (pState == GLUT_VISIBLE)
    WC->cPause = 0;
  else
    WC->cPause = 1;
}
//----------------------------------
void WorldControler::Reshape(int pWidth, int pHeight  )
{
  WC->setSize( pWidth, pHeight );
}
void WorldControler::Animate( int p)
{


  //	std::cout << "Timer WorldControler::Animate <" << sMicroRate << " " << sTime << std::endl;

  if( WC->cPause == 1)
    {
      glutTimerFunc( sMicroRate, Animate, 0 );
      //	std::cout << " PAUSE Timer WorldControler::Animate " << sMicroRate << " " << sTime<< " >>>> " << std::endl;
      return;
    }

  sTime += sRatio;

  if( WC->cCurrentWorld)
    WC->cCurrentWorld->animateWorld();

  Redraw( 0 );

  //	cout << "Rate:" << sMicroRate << " ration:" << sRatio << endl;

  glutTimerFunc( sMicroRate, Animate, 0 );
  //	std::cout << " Timer WorldControler::Animate " << sMicroRate << " " << sTime << " >>>> " << std::endl;

}
//--------------------------------
void WorldControler::Idle()
{
  //  std::cout << "Idle" << std::endl;
}
//--------------------------------
void WorldControler::InitCallback()
{
  /* set callbacks */
  glutSpecialFunc( SpecialKey );
  glutKeyboardFunc(Key);
  glutIdleFunc(Idle);
  //	glutKeyboardUpFunc( KeyUp );

  //#ifndef PC_WINDOWS  || LINUX
  glutReshapeFunc( Reshape );
  //#endif

  glutVisibilityFunc( Visibility );
  glutDisplayFunc(Display);
  glutMouseFunc(MouseButton);
  glutMotionFunc(MouseMove);
  glutPassiveMotionFunc(MouseMove);

  glutTimerFunc( 500, Animate, 0 );

  /*
    #ifdef PUI_WIN
    puInit () ;
    #endif
  */
}
//--------------------------------
void
WorldControler::GameOver( )
{
  WC->cCurrentWorld->gameOver();

  WC->cGame->freeRessources();
  WC->cGame->initStart();
  WC->mainWorld();
}
//--------------------------------
void
WorldControler::GameWinner( )
{
  WC->cCurrentWorld->gameWinner();

  WC->cCurrentWorld->freeRessources();
  WC->cCurrentWorld->initStart();
  WC->mainWorld();

}
//--------------------------------
int
WorldControler::userEvent( void* pUserData )
{
  //	std::cout << "WorldControler::userEvent  " << std::endl;
  return WC->cCurrentWorld->userEvent( pUserData );
}
