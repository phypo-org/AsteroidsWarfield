
#include "T3dTransf.h"

#include "T3dBox.h"

/*---------------------------------------------------------------------*/
/*    T3dTransf::T3dTransf ...                                         */
/*---------------------------------------------------------------------*/

T3dTransf::T3dTransf()
{
	raz();
}
/*---------------------------------------------------------------------*/
/*    T3dTransf::raz ...                                                */
/*---------------------------------------------------------------------*/

void 
T3dTransf::raz()
{
	TransfDouble3::raz();
	Double3 lTmp( 1.0, 1.0, 1.0);
	set( SCALE, lTmp );
}
/*---------------------------------------------------------------------*/
/*    T3dTransf::exec ...                                               */
/*---------------------------------------------------------------------*/

void 
T3dTransf::exec()
{
	// ATTENTION A L ORDRE DES OPERATIONS
	glTranslated( get(POS)[ 0 ], get(POS)[1], get(POS)[2] );

	glRotated( get(ANGLE)[0], 1.0, 0.0, 0.0 );
	glRotated( get(ANGLE)[1], 0.0, 1.0, 0.0 );
	glRotated( get(ANGLE)[2], 0.0, 0.0, 1.0 );

	glScaled( get(SCALE)[0], get(SCALE)[1], get(SCALE)[2]);
}
/*---------------------------------------------------------------------*/
/*    AX3dTrans::exec ...                                              */
/*---------------------------------------------------------------------*/

void
T3dTransf::execBox( T3dBox & pBox )
{
	glTranslated( get(POS)[ 0 ], get(POS)[1], get(POS)[2] );

	Double3 lCenter;
	pBox.getCenter( lCenter );

	glTranslatef( lCenter[ 0 ], lCenter[ 1 ], lCenter[ 2 ] );

	glRotated( get(ANGLE)[0], 1.0, 0.0, 0.0 );
	glRotated( get(ANGLE)[1], 0.0, 1.0, 0.0 );
	glRotated( get(ANGLE)[2], 0.0, 0.0, 1.0 );

	glScaled( get(SCALE)[0], get(SCALE)[1], get(SCALE)[2]);


	glTranslatef( -lCenter[ 0 ], -lCenter[ 1 ], -lCenter[ 2 ] );	
}
/*---------------------------------------------------------------------*/
/*    T3dTransf::centerTo ...                                          */
/*---------------------------------------------------------------------*/
void
T3dTransf::centerTo( T3dBox& pBox)
{
	Double3 lCenter;
	pBox.getCenter( lCenter );

	for( int i= 0; i < 3; i++ )
		get(POS)[i] = -lCenter[i]; 
}
/*---------------------------------------------------------------------*/
/*    T3dTransf::scaleTo ...                                           */
/*---------------------------------------------------------------------*/

void
T3dTransf::scaleTo( T3dBox& pBox,  Double3& pSz )
{

	// ATTENTION AU DIVISION PAR ZERO ET DEPACEMENT DE CAPACITE !
	for( int i = 0; i < 3; i++ )
	{
		get(SCALE)[i]  = pSz[ i ] / (pBox.getMax()[ i ]-pBox.getMin()[ i ]);		
	}
}
/*---------------------------------------------------------------------*/
/*    T3dTransf::scaleTo ...                                           */
/*---------------------------------------------------------------------*/

void
T3dTransf::scaleTo( T3dBox& pBox, double pSz )
{
	double lMax=-1e10;

	// ATTENTION AU DIVISION PAR ZERO ET DEPACEMENT DE CAPACITE !
	for( int i = 0; i < 3; i++ )
	{
		if( (pBox.getMax()[ i ]-pBox.getMin()[ i ])>lMax)
			lMax = (pBox.getMax()[ i ]-pBox.getMin()[ i ]);		
	}

	get(SCALE)[0] =
	get(SCALE)[1] =
	get(SCALE)[2] = pSz / lMax;
}
