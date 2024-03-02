
#include "O3dKamera.h"

#ifdef WIN32
#include <FL/glu.H>
#endif

//---------------------------------------------------------------------

O3dKamera::O3dKamera()
:cPersFlag(GL_TRUE)
{
	O3dKamera::reset();
}		
//---------------------------------------------------------------------
void
O3dKamera::reset()
{
	T3dTransf::raz();
	KameraDouble::set( PERS_FOVY, 45.0 );
	KameraDouble::set( PERS_ASPECT, 1.0 );
	KameraDouble::set( PERS_ZNEAR, 0.1 ); 
	KameraDouble::set( PERS_ZFAR, 100000.0 );

	// pour Viewer
 	T3dTransf::get( POS )[2]= 30.0;

	Double3 lTmp( 0.1, 0.1, 0.1);
	T3dTransf::set( SCALE, lTmp );

//////////T3dTransf::get( POS)[ 2 ] = -100;
}
//---------------------------------------------------------------------
void O3dKamera::setAspectRatio( int pWidth, int pHeight)
{
  double lRatio = ((double)pWidth)/((double)pHeight);
  std::cout << "************************** setAspectRatio W:" << pWidth << " H:" << pHeight << " R:" <<  lRatio << std::endl;
  KameraDouble::set( PERS_ASPECT, lRatio);
  std::cout << "************************** KameraDouble : " <<  KameraDouble::get( PERS_ASPECT );

  double lVal = pWidth/1280.0f;
  
  Double3 lTmp( 0.1*lVal, 0.1*lVal, 0.1*lVal);
  T3dTransf::set( SCALE, lTmp );
}
//---------------------------------------------------------------------
void
O3dKamera::exec()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


  
  double cRatioWH = KameraDouble::get( PERS_ASPECT );
 
  /* 
     static int i=0;
 if(i++ %1000 == 0 )
  {
	std::cout << "RatioWH="<<  cRatioWH<< std::endl;
  }
  */
	if( cPersFlag == GL_TRUE )
	{
		gluPerspective( KameraDouble::get( PERS_FOVY), KameraDouble::get(PERS_ASPECT), KameraDouble::get(PERS_ZNEAR), KameraDouble::get(PERS_ZFAR) );
	}
	else		
	  //		glOrtho( -1000,  + 1000, -1000,  +1000, -100000, 100000 );//KameraDouble::get(PERS_ZNEAR), KameraDouble::get(PERS_ZFAR));
		glOrtho( -cRatioWH*1000,  + cRatioWH*1000, -1000,  +1000, -100000, 100000 );//KameraDouble::get(PERS_ZNEAR), KameraDouble::get(PERS_ZFAR));
		


// Inversion car c est l utilisteur 
		glTranslated( -T3dTransf::get(POS)[ 0 ], -T3dTransf::get(POS)[1], -T3dTransf::get(POS)[2] );

		glRotated( -T3dTransf::get(ANGLE)[0], 1.0, 0.0, 0.0 );
		glRotated( -T3dTransf::get(ANGLE)[1], 0.0, 1.0, 0.0 );
		glRotated( -T3dTransf::get(ANGLE)[2], 0.0, 0.0, 1.0 );

		// ATTENTION POUR VIEW SEUL SCALEX EST UTILISE !!!!!!!
		glScaled( T3dTransf::get(SCALE)[0], T3dTransf::get(SCALE)[0], T3dTransf::get(SCALE)[0] );


    	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();  

}
/*---------------------------------------------------------------------*/
/*    O3dKamera::getUnProject ...                                  */
/*---------------------------------------------------------------------*/

GLboolean
O3dKamera::getUnProject(  const Double3& pPos, Double3 & pPtResult )
{
	GLint lViewport[ 4 ];
	GLdouble lMvMatrix[ 16 ];
	GLdouble lProjMatix[ 16 ];

	exec();

	glGetIntegerv( GL_VIEWPORT, lViewport );
	glGetDoublev( GL_MODELVIEW_MATRIX, lMvMatrix );
	glGetDoublev( GL_PROJECTION_MATRIX, lProjMatix );

	Double3 lTmpPos( pPos  );
	lTmpPos[1] = lViewport[3] - lTmpPos[1] -1;


	if( gluUnProject( (GLdouble)lTmpPos[0], (GLdouble)lTmpPos[1], (GLdouble)lTmpPos[2],
				  lMvMatrix, lProjMatix, lViewport,
				  &pPtResult[ 0 ], &pPtResult[ 1 ], &pPtResult[ 2 ] )
		 == GL_FALSE )
		return GL_FALSE;


	return GL_TRUE;
}
/*---------------------------------------------------------------------*/
/*    O3dKamera::getProject ...                                        */
/*---------------------------------------------------------------------*/

GLboolean
O3dKamera::getProject( const Double3& pPos, Double3 & pPtResult )
{
	GLint lViewport[ 4 ];
	GLdouble lMvMatrix[ 16 ];
	GLdouble lProjMatix[ 16 ];

	exec();

	glGetIntegerv( GL_VIEWPORT, lViewport );
	glGetDoublev( GL_MODELVIEW_MATRIX, lMvMatrix );
	glGetDoublev( GL_PROJECTION_MATRIX, lProjMatix );

	
	if( gluProject( (GLdouble)pPos[0], (GLdouble)pPos[1], (GLdouble)pPos[2],
 					 lMvMatrix, lProjMatix, lViewport,
					&pPtResult[ 0 ], &pPtResult[ 1 ], &pPtResult[ 2 ] ) == GL_FALSE )
		return GL_FALSE;


	return GL_TRUE;
}
/*---------------------------------------------------------------------*/
/*    O3dKamera::setPick ...                                       */
/*---------------------------------------------------------------------*/

void 
O3dKamera::setPick(  int pX, int pY, float pWidht, float pHeight )
{
	// Code for picking
	GLint lViewport[ 4 ];
	glGetIntegerv( GL_VIEWPORT, lViewport );


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Code for picking
	gluPickMatrix( (GLdouble)pX, 
				   (lViewport[ 3 ]-pY - 1), pWidht, pHeight, lViewport );



	if( cPersFlag == GL_TRUE )
	{
		gluPerspective( KameraDouble::get( PERS_FOVY), KameraDouble::get(PERS_ASPECT), KameraDouble::get(PERS_ZNEAR), KameraDouble::get(PERS_ZFAR) );
	}
	else
		glOrtho( -1000,  + 1000, -1000,  +1000, -100000, 100000 );//KameraDouble::get(PERS_ZNEAR), KameraDouble::get(PERS_ZFAR));



// Inversion car c est l utilisteur 
		glTranslated( -T3dTransf::get(POS)[ 0 ], -T3dTransf::get(POS)[1], -T3dTransf::get(POS)[2] );

		glRotated( -T3dTransf::get(ANGLE)[0], 1.0, 0.0, 0.0 );
		glRotated( -T3dTransf::get(ANGLE)[1], 0.0, 1.0, 0.0 );
		glRotated( -T3dTransf::get(ANGLE)[2], 0.0, 0.0, 1.0 );

		// ATTENTION POUR VIEW SEUL SCALEX EST UTILISE !!!!!!!
		glScaled( T3dTransf::get(SCALE)[0], T3dTransf::get(SCALE)[0], T3dTransf::get(SCALE)[0] );


    	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();  	
}
