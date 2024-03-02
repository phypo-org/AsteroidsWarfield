
#ifndef _T3dCalcul_h_
#define _T3dCalcul_h_



/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dType.h>

/*---------------------------------------------------------------------*/
/*    class T3dCalcul ...                                              */
/*---------------------------------------------------------------------*/

class T3dCalcul
{
public:

	static void GetMiddle(  const Double3 &p1, const Double3 &p2, Double3 &pRes );
	static void Normal( Double3 &p1, Double3 &p2, Double3 &p3, Double3 & pNorm );
	static void Thomas ( GLdouble noeuds[],  GLdouble poles[], int nb);
	static void ConvBezier (GLdouble src[], GLdouble dest[], int nb);
};

#endif
