#ifndef h_T3dBox_h
#define h_T3dBox_h


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/


#include "T3d/T3dType.h"
#include "T3d/T3dVect3D.h"

#include <string.h>


/*---------------------------------------------------------------------*/
/*    class T3dBox ...                                                 */
/*---------------------------------------------------------------------*/

class T3dBox
{
  Double3 cMin;
  Double3 cMax;

public:
  T3dBox();
  T3dBox( T3dBox& pBox )
    :cMin(pBox.cMin),
     cMax(pBox.cMax)			
  {
  }
  T3dBox( const Double3 & pMin, const Double3 &pMax )
    :cMin( pMin),
     cMax(pMax)
  {
  }
  T3dBox( double pxmin, double pymin, double pzmin,
          double pxmax, double pymax, double pzmax )
    :cMin(pxmin, pymin, pzmin ),
     cMax(pxmax, pymax, pzmax)
  {
  }

  T3dBox operator =(const T3dBox & iVal )
  {
    cMin = iVal.cMin;
    cMax = iVal.cMax;
    return *this;
  }

  Double3 &getMin()
  {
    return cMin;
  }
  Double3  &getMax()
  {
    return cMax;
  }

  Double3 size();
  Double3 center();
  void getCenter( Double3& pD3);

  virtual char *getInfoStr( char *pStr );

  GLboolean isInto( Double3 & pPt )
  {
    for( int i = 0; i < 3; i++ )
      {
        if( pPt[ i ] < cMin[ i ]
            ||  pPt[ i ]>cMax[ i ] )
          return GL_FALSE;
      }
    return GL_TRUE;
  }

  std::ostream& print( std::ostream& os)
  {
    os << '[';
    cMin.print( os ) << " ";
    cMax.print( os )<< '[';

    return os;
  }

  friend class T3dVect3D;
};



#endif
