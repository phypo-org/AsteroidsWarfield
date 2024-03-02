
#include "O3d/O3dObj.h"
#include "T3d/T3dColor.h"
#include "T3d/T3dPrimitiv.h"

#include <stdio.h>
#include <math.h>


/*---------------------------------------------------------------------*/
/*    local variable ...                                               */
/*---------------------------------------------------------------------*/

long O3dObj::sId = 1;


/*---------------------------------------------------------------------*/
/*    O3dObj::O3dObj ...                                               */
/*---------------------------------------------------------------------*/

O3dObj::O3dObj(float pRadius, GLboolean pUseList)
  :cUseList( pUseList )
  ,cListId( 0)
  ,cId( sId++ )
  ,cRadius(pRadius)
  ,cObjProps( NULL )
  ,cSelect( GL_FALSE )
{
}
/*---------------------------------------------------------------------*/
/*    O3dObj::~O3dObj ...                                              */
/*---------------------------------------------------------------------*/

O3dObj::~O3dObj()
{
  if( cListId != 0 )
    {
      glDeleteLists( cListId, 1 );
      cListId=0;
    }
}
/*---------------------------------------------------------------------*/
/*    O3dObj::makeList ...                                             */
/*---------------------------------------------------------------------*/

// IL FAUDRAIT DEUX MODE UN AVEC PROPS L4AUTRE SENS
void
O3dObj::makeList( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
  if( cUseList == GL_TRUE )
    {
      if( cListId == 0 )
        cListId = glGenLists( 1 );

      if( cListId != 0 )
        {

          glNewList( cListId, GL_COMPILE );

          if( pObjProps )
            pObjProps->open();

          //			glNewList( cListId, GL_COMPILE );
          drawObj( pVProps, pObjProps );
          //			glEndList();

          if( pObjProps )
            pObjProps->close();

          glEndList();
        }
    }
}
/*---------------------------------------------------------------------*/
/*    O3dObj::draw ...                                                */
/*---------------------------------------------------------------------*/

void
O3dObj::draw( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
  // Condition d affichage change, ou objet sans liste
  // on refait les listes
  if( pVProps.ViewPropsBool::get( VIEW_REMAKE_LIST ) == GL_TRUE
      || ( cListId == 0 && cUseList == GL_TRUE ))
    {
      makeList( pVProps, pObjProps );
    }

  if( pVProps.ViewPropsBool::get( VIEW_REDRAW ) == GL_TRUE )
    {
      drawId( pVProps, pObjProps );
      if( cListId != 0 && pVProps.getSelector() == NULL )
        {
          glCallList( cListId );
        }
      else
        {
          if( pObjProps )
            pObjProps->open();
          drawObj( pVProps, pObjProps );
          if( pObjProps )
            pObjProps->close();
        }
    }
  if( pVProps.ViewPropsBool::get( DRAW_SELECTED_COMPONENT ))
    drawSelectedComponents( pVProps, pObjProps);
}
/*---------------------------------------------------------------------*/
/*    O3dObj::drawForSelectComponents ...                              */
/*                                                                     */
/* Par defaut on utilse l affichage normal drawObj                     */
/*                                                                     */
/*---------------------------------------------------------------------*/

void
O3dObj::drawForSelectComponents( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
  drawObj( pVProps, pObjProps );
}
/*---------------------------------------------------------------------*/
/*    O3dObj::getInfoStr ...                                           */
/*---------------------------------------------------------------------*/

const char*
O3dObj::getInfoStr( char* pStr)
{
  int lNb = sprintf( pStr, "%ld : %s", cId, getObjTypeStr() );
  return &pStr[lNb];
}
/*---------------------------------------------------------------------*/
/*    O3dObj::drawId ...                                               */
/*---------------------------------------------------------------------*/

void
O3dObj::drawId(  O3dViewProps & pVProps, O3dObjProps *pObjProps )
{	
  if( isSelect() )
    {
      glDisable(GL_LIGHTING);
      T3dColor::Red();
      T3dPrimitiv::DrawX( getTransf().TransfDouble3::get(POS)[0], 
                          getTransf().TransfDouble3::get(POS)[1],
                          getTransf().TransfDouble3::get( POS )[ 2 ], 10 );
      glEnable(GL_LIGHTING);
    }
  else
    T3dColor::Yellow();

  if( pVProps.ViewPropsBool::get( DRAW_ID ) == GL_FALSE)
    return;


  char tmp[33];
  sprintf( tmp, "%ld", cId );

  pVProps.getDefaultFont()->displayAtPoint( getTransf().TransfDouble3::get(POS), tmp );
}


//----------------------------------------------
void
O3dObj::GetNormDirection( Double3 & pVect )
{
  double lNorm = 1.0;

  double cRoot = sqrt( pVect[0]*pVect[0]
                       + pVect[1]*pVect[1]
                       + pVect[2]*pVect[2] );
  if( cRoot > 0.01 )
    lNorm = 1.0/cRoot;

  //	   cout << "pDx:" << pDx << " pDy:" << pDy << " Norm:" << lNorm ;

  pVect *= lNorm;
}
//----------------------------------------------
void
O3dObj::GetNormDirectionInv( Double3 & pVect )
{
  double lNorm = 1.0;

  double cRoot = sqrt( pVect[0]*pVect[0]
                       + pVect[1]*pVect[1]
                       + pVect[2]*pVect[2] );
  if( cRoot > 0.01 )
    lNorm = 1.0/cRoot;

  //	   cout << "pDx:" << pDx << " pDy:" << pDy << " Norm:" << lNorm ;

  pVect *= -lNorm;
}
//----------------------------------------------
void
O3dObj::GetObjectDistance( O3dObj* p1, O3dObj *p2, Double3 & pDist )
{
  pDist  = p1->getTransf().TransfDouble3::get(POS);
  pDist -= p2->getTransf().TransfDouble3::get(POS);
}

