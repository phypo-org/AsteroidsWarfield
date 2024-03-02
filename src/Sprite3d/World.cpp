#include <FL/glut.H>

#include <O3d/O3dKamera.h>
#include <T3d/T3dPrimitiv.h>
#include <T3d/T3dColor.h>
#include <T3d/T3dFont.h>
#include <T3d/T3dFontRaster.h>


#include <iostream>

#include "World.h"
#include "WorldControler.h"
#include "ObjOdron.h"
#include "Sprite3d.h"
#include "Collision.h"
#include "Sprite3dPilot.h"

long World::sNbDetect = 0;
World*  World::sTheWorld = NULL;


std::string            World::sIniFile;
std::map<std::string, std::string> World::sConfig;
 
int  World::sFlagCollision3d  = 1; // automatique
int  World::sThresholdDetection3d = 100;

//--------------------------------
// Inefficace !


//**************************************

World::World( WorldControler *pControl, O3dKamera* pKamera, Double3& pMax, O3dObjProps*pProps )
  : 
  cProps( pProps ),
  cPilot( NULL ),
  cMyControler(pControl),
  cKamera(pKamera),
  cOverlayOpen( GL_FALSE ),
  cBox( pMax, pMax ),
  cNbLiveSprite(0)
{
  cServiceSprite.reserve(128);
  cNewSprite.reserve(2048);
  cLiveSprite.reserve(4096);
  cFreeLivePosition.reserve(4096);



  for( int i = 0; i < 3; i++ )
    {
      cBox.getMin()[i] = -cBox.getMax()[i] ;
    }

	
  std::cout << "============= World::World " << (*pMax) << std::endl;

  sTheWorld = this;


  //	Double3 lDiv( 32, 32, 32 ); 
  Double3 lDiv( 64, 32, 64 ); 
  cZonesDetectCollision = Collision::InitSpatialDetection3D( cBox, lDiv );

}
//--------------------------------
World::~World()
{
  empty();
}
//--------------------------------
void
World::add( Sprite3d *pSprite ){


  //	if( cNbLiveSprite >= 5000 ) // too many sprite 
  //		delete pSprite;
		
  // search a free spce in the vector
  /*
    for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
    {
    if( (*iter) == nullptr ) 
    {
    (*iter) = pSprite;
    return;
    }
    }
  */
  // First see in the free position vector
  if( cFreeLivePosition.size() ){

    int cLastPos = cFreeLivePosition.back();
    cFreeLivePosition.pop_back();
    cLiveSprite.at(cLastPos) =  pSprite;

    return ;
  }

  // no space free in the vector
  cNewSprite.push_back( pSprite );
}
//--------------------------------
void
World::empty()
{
  killAllSprite(); // y compris cPilot
  cPilot = NULL;
}
//--------------------------------
void
World::gameOver()
{
  //	cPilot = NULL;
}
//--------------------------------
void
World::gameWinner()
{
  //	cPilot = NULL;
}
//--------------------------------
GLboolean
World::initOverlay()
{

  //	glutInitDisplayMode(GLUT_SINGLE | GLUT_INDEX);
  int overlaySupport = glutLayerGet(GLUT_OVERLAY_POSSIBLE);

  if (overlaySupport)
    {
      glutEstablishOverlay();
      glutHideOverlay();
      int transparent = glutLayerGet(GLUT_TRANSPARENT_INDEX);
      glClearIndex(transparent);
      int red = (transparent + 1) % glutGet(GLUT_WINDOW_COLORMAP_SIZE);
      int white = (transparent + 2) % glutGet(GLUT_WINDOW_COLORMAP_SIZE);
      //			glutSetColor(red, 1.0, 0.0, 0.0);  /* Red. */
      //		glutSetColor(white, 1.0, 1.0, 1.0);  /* White. */
      ////////		glutOverlayDisplayFunc(redrawOverlay);
      ////////			glutReshapeFunc(reshape);
      cOverlayOpen = GL_TRUE;

    }
  else
    {
      std::cout << "Overlay failed" << std::endl;
    }

  return cOverlayOpen;
}
//--------------------------------
//----------- DRAW --------------
//--------------------------------
void World::drawWorld()
{
  if( cPilot )
    cPilot->drawControl();

  cKamera->exec();
  //	  T3dPrimitiv::DrawRepere( 120, 1 );
  //	T3dPrimitiv::DrawGrid( 100, 10 );

  // cLiveObj.drawObj( getProps() );
  drawLiveSprite();

}
//--------------------------------
void World::killSprite( Sprite3d *pSp )
{
  pSp->destroy();
}
//--------------------------------
void World::drawLiveSprite()
{
  O3dViewProps lViewProps( *getKamera() );
  lViewProps.setDefaultFont( T3dFont::DefaultFont );
  // IMPLEMENTER UNE POLICE !!!!!!
  lViewProps.ViewPropsBool::set( DRAW_ID, GL_FALSE);
  for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
    {
      if( *iter == nullptr ) continue;

      (*iter)->makeDraw( lViewProps, cProps );
    }
}
//-------------------------------------------------
void World::reshapeWorld(int pWidth, int pHeight)
{

}
//-------------------------------------------------
// Determine si un des sprites intersecte avec une zone

Sprite3d*
World::isSpriteIntersect( Double3 pPos, float pRadius, unsigned int pMmask_Att)
{
  for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
    {
      if( *iter == nullptr ) continue;

      unsigned int mask_Def = (*iter)->getDefMask();
      if( (mask_Def & pMmask_Att) )
        {

          if( (*iter)->intersect( pPos, pRadius ) == GL_TRUE )
            return (*iter);
        }
      else {
      }

    }
  return NULL;
}
//-------------------------------------------------
// Determine si un des sprites intersecte avec une zone
/*
  Sprite3d*
  World::isSpriteIntersectXY( Double3 pPos, float pRadius, unsigned int pMmask_Att)
  {
  for( std::vector <Sprite3d*>::iterator iter = cLiveSprite.begin(); iter != cLiveSprite.end(); ++iter )
  {
  if( *iter == nullptr ) continue;


  unsigned int mask_Def = (*iter)->getDefMask();
  if( (mask_Def & pMmask_Att) )
  {

  if( (*iter)->intersectXY( pPos, pRadius ) == GL_TRUE )
  return (*iter);
  }
  else {
  }

  }
  return NULL;
  }
*/
//--------------------------------
//----------- ANIMATE ------------
//--------------------------------
//extern int lNbCalcul;

void World::animateLiveSprite()
{
  //	std::cout << "World::animateLiveSprite " << cNewSprite.size() << std::endl;


  //	std::vector <Sprite3d*>::iterator iterLive = cLiveSprite.begin();
 
  //=========  Ajout des nouveau Sprite =============
  std::vector <Sprite3d*>::iterator iterLive;
  iterLive = cLiveSprite.begin();
	
  bool lSearchFreeSpace = true;
		
  for( std::vector <Sprite3d*>::iterator iterNew = cNewSprite.begin(); iterNew != cNewSprite.end(); ++iterNew )
    {
      Sprite3d* lSprite = *iterNew;


      if( lSearchFreeSpace ) 
        {
          // find a free space 
          for(;	iterLive != cLiveSprite.end();	++iterLive )
            {
              //	std::cout << "*** World::animateLiveSprite iter "<<  *iterLive  << std::endl;
              if( *iterLive == nullptr )
                {
                  //					std::cout << "*** World::animateLiveSprite add nex sprite nullptr "  << std::endl;
                  break;
                }
            }
		
          if( iterLive!=cLiveSprite.end() )
            {
              (*iterLive) = lSprite;
              ++iterLive;
              continue;
            }

          lSearchFreeSpace = false;
        }

		
      //		std::cout << "World::animateLiveSprite " << lSprite << std::endl;
      //	std::cout << "*** World::animateLiveSprite push_back "  << std::endl;
		
      cLiveSprite.push_back( lSprite ); // inactive iterLive
    }
  //=================================================


  cNewSprite.clear();



  //=============  Boucle d animation ===============
  //	std::cout << "animation:" << cLiveSprite.size() << " this:" << this << std::endl;

  cNbLiveSprite = 0;

  for( std::vector <Sprite3d*>::iterator iterLiveAnim = cLiveSprite.begin(); iterLiveAnim != cLiveSprite.end(); ++iterLiveAnim )
    {
      if( (*iterLiveAnim) == nullptr ) continue;


      (*iterLiveAnim)->animate();
      cNbLiveSprite++;
    }
  //=================================================




  //lNbCalcul = 0;

  // Detection et resolution des collisions
  //	  sNbDetect =  Collision::SimpleDetection( cLiveSprite  );
  if( sFlagCollision3d == 0) // automatique
    {
      if( getNbLiveSprite() > sThresholdDetection3d )
        {
          Collision::CleanSpatialDetection3D(	*cZonesDetectCollision );																																		
          sNbDetect = Collision::SpatialDetection3D( cLiveSprite, *cZonesDetectCollision );
        }
      else 
        {
          cZonesDetectCollision->desactivate();
          sNbDetect =  Collision::SimpleDetection( cLiveSprite  );
        }
    }
  else if( sFlagCollision3d == 1)
    {
      Collision::CleanSpatialDetection3D(	*cZonesDetectCollision );																																		
      sNbDetect = Collision::SpatialDetection3D( cLiveSprite, *cZonesDetectCollision );
    }
  else if( sFlagCollision3d == 2)
    {
      cZonesDetectCollision->desactivate();
      sNbDetect =  Collision::SimpleDetection( cLiveSprite  );
    }




  //=============   Elimination logique des Sprite sortie du monde =============  
  for( std::vector <Sprite3d*>::iterator iterLiveOut = cLiveSprite.begin(); iterLiveOut != cLiveSprite.end(); ++iterLiveOut )
    {
      if( (*iterLiveOut) == nullptr ) continue;

      if( cBox.isInto( (*iterLiveOut)->getTransf().TransfDouble3::get(POS)) == GL_FALSE
          && (*iterLiveOut)->leaveWorld() == GL_TRUE)
        {
          (*iterLiveOut)->destroy();
        }
    }
  //=================================================



  //============= Destroy ==========================
  // Elimination physique des Sprite morts

	
  for( VSprite3d::iterator iterLiveDestroy = cLiveSprite.begin(); iterLiveDestroy != cLiveSprite.end(); iterLiveDestroy++)
    {
      if( *iterLiveDestroy == nullptr ) continue;
			
      if( (*iterLiveDestroy)->isDestroy() )
        {
          removeLiveSprite( iterLiveDestroy );
          delete( *iterLiveDestroy );
        }
    }
	
  //=================================================

}
//--------------------------------
void
World::removeLiveSprite( VSprite3d::iterator& pIterLive )
{	
  *pIterLive = nullptr;
  cNbLiveSprite--;
  cFreeLivePosition.push_back(  pIterLive- cLiveSprite.begin() ); // On stocke la position libre				
}
//--------------------------------
// Inefficace, mais rare !

void
World::removeSprite(  Sprite3d *pSp )
{

  for( VSprite3d::iterator iterLive = cLiveSprite.begin(); iterLive != cLiveSprite.end(); iterLive++ )
    {
      if( *iterLive == pSp )
        {
          removeLiveSprite( iterLive );
          return;
        }
    }


  for( VSprite3d::iterator iterNew = cNewSprite.begin(); iterNew != cNewSprite.end(); iterNew++ )
    {
      if( *iterNew == pSp )
        cNewSprite.erase( iterNew );
    }
}

//--------------------------------
bool
World::deleteSprite( Sprite3d* pSprite)
{
  if(pSprite->getDeleteControler() == NULL) {
    delete pSprite;
    return true;
  }
  else
    return pSprite->getDeleteControler()->execDelete( pSprite );

  return false;
}

//--------------------------------
void World::killAllSprite()
{
  //#ifndef PC_WINDOWS

  for( std::vector < Sprite3d *> ::iterator iterNew = cNewSprite.begin(); iterNew != cNewSprite.end(); ++iterNew )
    if( *iterNew != nullptr )
      {
        deleteSprite( *iterNew );
      }


  for( std::vector < Sprite3d *> ::iterator iterLive = cLiveSprite.begin(); iterLive != cLiveSprite.end(); ++iterLive)
    {
      if(  *iterLive != nullptr )
        {
          if( deleteSprite( *iterLive ) )
            {
              removeLiveSprite( iterLive );
            }					
        }
    }

  //#endif

  cNewSprite.clear();
  cLiveSprite.clear();
  cFreeLivePosition.clear();
  cNbLiveSprite = 0;
}
//--------------------------------
void World::animateWorld()
{
  animateLiveSprite();
}
//--------------------------------
//---------- EVENT ---------------
//--------------------------------

void World::mouseMove( int pX, int pY )
{
  if( cPilot )
    cPilot->mouseMove( pX, pY );
}
//--------------------------------
void World::key( unsigned char pKey, int pX, int pY )
{
  if( cPilot )
    cPilot->key( pKey, pX, pY );
}
//--------------------------------
void World::mouseButton( int pButton, int pState, int pX, int pY)
{
  if( cPilot )
    cPilot->mouseButton( pButton, pState, pX, pY );
}
//--------------------------------
void
World::setPilot( int pX, int pY )
{
  if( cPilot )
    cPilot->mouseMove( pX, pY );
}

//--------------------------------
void
World::setPilotKey(unsigned char pKey, int pX, int pY  )
{
  if( cPilot )
    cPilot->key( pKey, pX, pY );
}
//--------------------------------
void
World::setPilotSpecialKey(unsigned char pKey, int pX, int pY  )
{
  if( cPilot )
    cPilot->key( pKey, pX, pY );
}
//--------------------------------
void
World::setPilotKeyUp(unsigned char pKey, int pX, int pY  )
{
  if( cPilot )
    cPilot->key( pKey, pX, pY );
}
//------------------------------------------------

GLboolean
World::GetDistPilot( Sprite3d *pSprite,  Double3 & pDist )
{
  Sprite3d* lPilot = WorldControler::GetCurrentWorld()->getPilot();
  if( lPilot == NULL )
    return GL_FALSE;

  O3dObj::GetObjectDistance( lPilot, pSprite, pDist );
  return GL_TRUE;
}
//------------------------
// Pas rapide du tout ! a optimiser
// mettre un tableau 2D et les sprites repartie dedans en fonction de leur position

GLboolean
World::GetPositionWithoutCollision( int pInteract, Double3& pPos, int pSize, int pLimitX, int pLimitY, int pLimitZ, int pNbTry, float pMarge ){

  
  int i;
  for( i = 0; i < pNbTry; i++ ) {
    if( pLimitX != 0 )
      pPos[ 0 ] = (rand()%(pLimitX << 1))-pLimitX;

    if( pLimitY != 0 )
      pPos[ 1 ] = (rand()%(pLimitY << 1))-pLimitY;

    if( pLimitZ != 0 )
      pPos[ 2 ] = (rand()%(pLimitZ << 1))-pLimitZ;

    if( WorldControler::GetCurrentWorld()->isSpriteIntersect( pPos, pSize*pMarge, pInteract ) == NULL ){
      return GL_TRUE;
    }
  }

  return GL_FALSE;
}


//**************************************

