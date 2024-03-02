#include "O3dObjText.h"
#include "O3dObjProps.h"

#include <iostream>
#include "T3d/T3dColor.h"
#include <stdlib.h>

//****************************************

O3dObjText::O3dObjText( T3dFont *pFont, const char *pStr )
  :cFont(pFont),
   cStr(pStr) 
{
}
//--------------------------------------
void 
O3dObjText::drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
  cFont->displayAt( 0, 0, 50, cStr.data(), cStr.size() );
}
//****************************************

O3dObjText2d::O3dObjText2d( T3dFont *pFont, int pW, int pH, const char *pStr )
  :cFont(pFont)
  ,cW( pW )
  ,cH( pH )
{
  if( pStr )
    push_back( new std::string(pStr) );
}
//--------------------------------------
O3dObjText2d::~O3dObjText2d()
{
  for( std::vector <std::string*>::iterator iter = begin(); iter != end(); ++iter )
    {
      delete (*iter);
    }
} 
//--------------------------------------
void 
O3dObjText2d::drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
  int y = 0;

  for( std::vector <std::string*>::iterator iter = end()-1; iter >= begin(); iter-- )
    {	
      const char *lData = (*iter)->data();
      int lSz = (*iter)->size();
      //		glTranslatef( 0, 10*y );
      //		glutStrokeCharacter( GLUT_STROKE_ROMAN, *lData );
      //		if( (x >= cW) )
      {
        cFont->displayAt( 0, cFont->getHeight()*y, 50, lData, lSz);
	
        //			cFont->displayAt( 0, cFont->getHeight()*y, 50, lData, lSz);
        //			cFont->displayAt( 0, y*20, 50, lData, lSz );
      }
      y++;
    }
}
//****************************************
