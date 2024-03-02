#include "O3dSelector.h"
#include "O3d/O3dViewProps.h"
#include "O3d/O3dKamera.h"

#include <stdio.h>


/*---------------------------------------------------------------------*/
/*    O3dSelector::O3dSelect ...                                    */
/*---------------------------------------------------------------------*/

O3dSelector::O3dSelector()
  :cNbSelect( 0 ),
   cFind(SELECT_NONE ),
   cViewProps( NULL ),
   cKamera( NULL ),
   cNbObj( 0 ),
   cNbComponent( 0 ),
   cDepth(0),
   cRestrictedObjectId( -1 )
{
}
/*---------------------------------------------------------------------*/
/*    O3dSelector::raz ...                                           */
/*---------------------------------------------------------------------*/
void
O3dSelector::raz()
{
  cNbSelect = 0 ;
  cFind = SELECT_NONE ;
  cNbObj = 0 ;
  cNbComponent = 0 ;
}
/*---------------------------------------------------------------------*/
/*    O3dSelector::open ...                                          */
/*---------------------------------------------------------------------*/

void
O3dSelector::begin( O3dViewProps* pViewProps, O3dKamera* pKamera, int pX, int pY, float pWidht, float pHeight)
{
  cViewProps = pViewProps;
  cKamera = pKamera;

  raz();


  glSelectBuffer( cSzBuf, cSelectBuf );
  glRenderMode( GL_SELECT );

  glInitNames();
  // glPushName( (GLuint)-1 );
  cKamera->setPick( pX, pY, pWidht, pHeight);
}
/*---------------------------------------------------------------------*/
/*    O3dSelector::finish ...                                        */
/*---------------------------------------------------------------------*/

void
O3dSelector::finish()
{
  glFlush();
  cNbSelect = glRenderMode( GL_RENDER );


  GLuint *ptr = &cSelectBuf[ 0 ];
  printf( "==== O3dSelector::NbSelect:%d ====\n", cNbSelect );

  for( int i= 0; i < cNbSelect; i++ )
    {
      GLuint lNames = *ptr;
      printf( " Select %d %d\n", i, *ptr) ;
      ptr++;

      //		 *ptr++; // z1
      //	 *ptr++; //z2

      //		GLuint mem = SELECT_NONE;

      // On ne prend que le dernier objets
      if( i == (cNbSelect - 1) )
        {
          GLuint mem =SELECT_NONE;

          for( unsigned int j = 0; j < lNames; j++ )
            {
              switch( mem )
                {
                case SELECT_OBJECT:
                  printf( " Object:%d\n", *ptr );
                  cObjId[ cNbObj++ ] = *ptr;
                  mem = *ptr;
                  break;

                case SELECT_POINT:
                case SELECT_SEGMENT:
                case SELECT_PATCH:
                  cTypeComponent = mem;
                  printf( "Component:%ld %d\n", (long)mem, *ptr );
                  cComponent[ cNbComponent++ ] = *ptr;
                  break;

                case SELECT_NONE:
                default:
                  mem = *ptr;
                  printf("mem:%d\n", mem );
                }
              ptr++;
            }
        }
      else
        for( unsigned int j = 0; j < lNames; j++ )
          {
            ptr++;
          }

    }
}
/*---------------------------------------------------------------------*/
/*	   O3dSelector::getSelectObject ...                              */
/*---------------------------------------------------------------------*/

long
O3dSelector::getSelectObject()
{
  if( cNbObj == 0 )
    return SELECT_NONE;
  return cObjId[ cNbObj-1];
}
/*---------------------------------------------------------------------*/
/*    O3dSelector::pushSelec ...                                       */
/*---------------------------------------------------------------------*/
void
O3dSelector::pushSelect( long pObjId, GLuint pFlag )
{
  if( cRestrictedObjectId != -1  && pObjId != cRestrictedObjectId )
    return;

  switch( pFlag )
    {
    case SELECT_OBJECT:
      // printf( "%d\tpushSelect SELECT_OBJECT %ld\n", cDepth, pObjId );

      glPushName( SELECT_OBJECT );
      glPushName( pObjId );
      cDepth+=2;
      break;

    case SELECT_POINT:
    case SELECT_SEGMENT:
    case SELECT_PATCH:
      // printf( "%d\tpushSelect SELECT_PATCH %ld\n", cDepth, pObjId );
      glPushName( pFlag );
      cDepth++;
      break;

    case SELECT_NONE:
      break;

    default:
      // printf( "%d\tpushSelect  %ld -> %ld\n", cDepth, pObjId, pFlag );
      glPushName( pFlag );
      cDepth++;
    }
}
/*---------------------------------------------------------------------*/
/*    O3dSelector::popSelect ...                                       */
/*---------------------------------------------------------------------*/

void
O3dSelector::popSelect( long pObjId, GLuint pFlag)
{
  if( cRestrictedObjectId != -1  && pObjId != cRestrictedObjectId )
    return;


  switch(  pFlag )
    {
    case SELECT_OBJECT:
      glPopName();
      glPopName();
      cDepth -= 2;
      // printf( "%d\tpopSelect SELECT_OBJECT %ld\n", cDepth, pObjId);
      break;

    case SELECT_POINT:
    case SELECT_SEGMENT:
    case SELECT_PATCH:
      glPopName();
      cDepth--;
      // printf( "%d\tpopSelect SELECT_PATCH %ld\n", cDepth, pObjId);
      break;

    case SELECT_NONE:
      glPopName();
      cDepth--;
      // printf( "%d\tpopSelect SELECT_NONE %ld\n", cDepth, pObjId);
      break;

    default:
      glPopName();
      cDepth--;
      // printf( "%d\tpopSelect SELECT_VAL %ld\n", cDepth, pObjId);
    }
}
/*---------------------------------------------------------------------*/
/*    O3dSelector::print ...                                        */
/*---------------------------------------------------------------------*/

void
O3dSelector::print()
{
  /*
    cout << "=======================================" <<endl;
    cout << cNbSelect << " Objects founds " << endl;
    GLuint *ptr = &cSelectBuf[ 0 ];

    for( int i= 0; i < cNbSelect; i++ )
    {
    GLuint lNames = *ptr;
    cout << "number of names for hit is " << lNames << endl;
    ptr++;
    cout << " z1=" << *ptr++;
    cout << " z2=" << *ptr++;
    cout << endl;

    for( unsigned int j = 0; j < lNames; j++ )
    {
    cout << " " << *ptr;
    ptr++;
    }
    cout << endl;
    cout << "-------------" << endl;
    }
    cout << "=======================================" << endl;
  */
}



/*---------------------------------------------------------------------*/
/*    O3dSelector::print2 ...                                       */
/*---------------------------------------------------------------------*/

void
O3dSelector::print2()
{
  /*
    cout << "=======================================" << endl;

    cout << "SelecteD objects:";

    for( int i = 0; i < cNbObj; i++ )
    cout << cObjId[ i ] << ", ";

    cout << endl;

    cout << "Selected component:" ;
    for( int j = 0; j < cNbComponent; j++ )
    cout << cComponent[ j ] << ", ";

    cout << endl;

    cout << "Found:" << getSelectObject() <<endl;
    cout << "=======================================" << endl;
  */
}


