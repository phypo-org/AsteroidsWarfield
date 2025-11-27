#include "T3d/T3dCalcul.h"
#include <math.h>


/*---------------------------------------------------------------------*/
/*    define ...                                                       */
/*---------------------------------------------------------------------*/

#define MIN_ZERO 1.e-12


/*---------------------------------------------------------------------*/
/*    T3dCalcul::GetMiddle ...                                        */
/*---------------------------------------------------------------------*/

void
T3dCalcul::GetMiddle(  const Double3 &p1, const Double3 &p2, Double3 &pRes )
{	
	for( int i = 0; i < 3; i++ )
		pRes[ i ] = (p1[ i ] + p2[ i ])*0.5;

}
/*---------------------------------------------------------------------*/
/*    T3dCalcul::Normal ...                                           */
/*---------------------------------------------------------------------*/

void
T3dCalcul::Normal( Double3 &p1, Double3 &p2, Double3 &p3, Double3 & pNorm )
{
  double coa, cob, coc ;
  double px1, py1, pz1 ;
  double px2, py2, pz2 ;
  double px3, py3, pz3 ;
  
  double absvec ;
  
  px1 = p1[0] ;
  py1 = p1[1] ;
  pz1 = p1[2] ;
  
  px2 = p2[0] ;
  py2 = p2[1] ;
  pz2 = p2[2] ;
  
  px3 = p3[0] ;
  py3 = p3[1] ;
  pz3 = p3[2] ;
  
  coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
  cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
  coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;
  
 // Normalisation
  absvec = sqrt ((double)((coa *coa) + (cob *cob) + (coc *coc)));

  if( absvec == 0.0  )
	  pNorm[ 0 ] = absvec = 1.0;

  absvec = 1.0 / absvec;

  pNorm[0] = coa*absvec ;
  pNorm[1] = cob*absvec ;
  pNorm[2] = coc*absvec ;
}


/*---------------------------------------------------------------------*/
/*    T3dCalcul::Thomas ...                                           */
/*---------------------------------------------------------------------*/

long hi[ 10 ] = {1l, 5l, 19l, 71l, 265l, 989l, 3691l, 13775l, 51409l, 191861l};


void 
T3dCalcul::Thomas ( GLdouble noeuds[],  GLdouble poles[], int nb)
{
	GLdouble *Xi = new GLdouble[nb];

	int i;
	Xi[ 0 ] = (noeuds[ 0 ]*6) / 5;

	if ( nb <= 9 )              /* P0, ..., Pnb-1 */
	{
		for (  i=1; i<nb-1 ; i++ )
			Xi[ i ] = ((6 *noeuds[ i ]-Xi[ i - 1 ])*hi[ i ]) / hi[ i + 1 ];

		Xi[nb-1] = ((6 * noeuds[nb-1] - Xi[nb-2]) * hi[nb-1]) / (hi[nb-1] + hi[nb]) ;
	}
	else
	{

		for (  i=1; i<9; i++ )
			Xi[ i ] = ((6 *noeuds[ i ]-Xi[ i - 1 ])*hi[ i ]) / hi[ i + 1 ];

		for (  i=9; i<nb-1; i++ )
		   Xi[ i ] = ((6 *noeuds[ i ]-Xi[ i - 1 ])*51409l) / 191861l;

		Xi[nb-1] = ((6 * noeuds[nb-1] - Xi[nb-2]) * 51409l) /243270l ;
	}


	poles[ nb - 1 ] = Xi[ nb - 1 ];

	if ( nb > 9 )
	{
		for (  i=nb-1 ; i>7 ; i-- )
		   poles[ i - 1 ] = Xi[ i - 1 ]-((poles[ i ]*51409l) / 191861l);

 		for (  i=9 ; i>0 ; i-- )
			poles[ i - 1 ] = Xi[ i - 1 ]-((poles[ i ]*hi[ i - 1 ]) / hi[ i ]);

	}
	else
		for (  i=nb-1 ; i>0 ; i-- )
			poles[i-1] = Xi[i-1] - ((poles[i] * hi[i-1]) / hi[i]);

/*	poles[0] = poles[1] ;  */

	delete  []Xi;
}
/*---------------------------------------------------------------------*/
/*    T3dCalcul::ConvBezier  ...                                       */
/*---------------------------------------------------------------------*/

void
T3dCalcul::ConvBezier ( GLdouble src[],  GLdouble dest[], int nb)
{
	dest[0] = ( src[1] + 4 * src[2] +  src[3]  ) / 6.0;
	dest[1] = ( 2 * src[2]  +  src[3] ) / 3.0;
	dest[2] = ( src[2]  +  2 * src[3] ) / 3.0;
	dest[3] = ( src[2]  +  4 * src[3] +  src[4]  ) / 6.0;
}
/*  conserve les valeurs de U * F pour un pas de u = 1/maille             */

