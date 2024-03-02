#include "Utils3d.h"

#include <FL/glut.H>

#include "World.h"
#include "WorldControler.h"
#include <stdio.h>
#include <math.h>
#include "O3d/O3dKamera.h"

#include <iostream>

//**************************************

void Utils3d::Init(const char *pName, int argc, char **argv, int pWidth, int pHeight )
{
	/////// FLTK   glutInit(&argc, argv);

  glutInitWindowSize( pWidth, pHeight );
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(pName);


  T3dFont::Init();
	/*
#if GL_EXT_polygon_offset
  if (!glutExtensionSupported("GL_EXT_polygon_offset")) {
    printf("Warning: "
      "GL_EXT_polygon_offset not supported on this machine... "
      "trying anyway\n");
  }
#else
  printf("Warning: not compiled with GL_EXT_polygon_offset support.\n");
#endif
	*/


  static float ambient[] =
  {0.0, 0.0, 0.0, 1.0};
  static float diffuse[] =
  {1.0, 1.0, 1.0, 1.0};
  static float position[] =
//  {90.0, 90.0, -150.0, 0.0};
  {100.0, 100.0, 0.0, 0.0};
  static float lmodel_ambient[] =
  {0.5, 0.5, 0.5, 0.5};

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  gluPerspective(40.0, 1.0, 2.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


  glEnable( GL_POINT_SMOOTH );

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable( GL_DEPTH_TEST );

//  glEnable( GL_TEXTURE_2D );

  glEnable(GL_AUTO_NORMAL);
  glEnable( GL_NORMALIZE );
  glFrontFace(GL_CCW);

  glClearColor( 0.10, 0.10, 0.2, 0.0 );



  glutReshapeFunc(Reshape);
  

}
//--------------------------------
void Utils3d::Reshape( int pWidth, int pHeight )
{
 // int size = (pWidth < pHeight?pWidth:pHeight);

  //  std::cout << "Utils3d::Reshape" << std::endl;
  
  //glViewport((width - size) / 2, (height - size) / 2, size, size);
  glViewport( 0, 0, pWidth, pHeight);

  if( WorldControler::WC == nullptr )
    return ;
  
  WorldControler::WC->setSize( pWidth, pHeight );

  if(	WorldControler::WC->getFullScreen() == 0 ) // suite bug FullScreen sur windows
  {
      glutReshapeWindow( pWidth, pHeight);
      glutPostRedisplay();
  }
}
//--------------------------------
void Utils3d::Loop()
{
  glutMainLoop();
}
//--------------------------------
void Utils3d::Normal( Float3 &p1, Float3 &p2, Float3 &p3, Float3 & pNorm )
{
  float coa, cob, coc ;
  float px1, py1, pz1 ;
  float px2, py2, pz2 ;
  float px3, py3, pz3 ;

  float absvec ;

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
  absvec = sqrt ((float)((coa *coa) + (cob *cob) + (coc *coc)));

  if( absvec == 0.0  )
	  pNorm[ 0 ] = absvec = 1.0;

  absvec = 1.0 / absvec;

  pNorm[0] = coa*absvec ;
  pNorm[1] = cob*absvec ;
  pNorm[2] = coc*absvec ;
}
//--------------------------------
void Utils3d::Crossprod(Float3 &v1, Float3& v2, Float3& prod)
{
  prod[0] = v1[1] * v2[2] - v2[1] * v1[2];
  prod[1] = v1[2] * v2[0] - v2[2] * v1[0];
  prod[2] = v1[0] * v2[1] - v2[0] * v1[1];
}
//--------------------------------
void Utils3d::Normalize(Float3& v, float pVal)
{
  float d;

  d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  if (d == 0.0) {
    v[0] = d = 1.0;
  }

  d = pVal / d;
  v[ 0 ] *= d;
  v[ 1 ] *= d;
  v[ 2 ] *= d;

}
//--------------------------------
void Utils3d::DrawTriangle( Float3 & v1, Float3 & v2,  Float3 & v3)
{
	glBegin( GL_POLYGON );

	Float3 lNorm;
	Normal( v1, v2, v3, lNorm );

		glNormal3fv( lNorm );
		glNormal3fv( v1 );
		glVertex3fv( v1 );

		glNormal3fv( lNorm );
		glNormal3fv( v2 );
		glVertex3fv( v2 );

		glNormal3fv( lNorm );
		glNormal3fv( v3 );
		glVertex3fv( v3 );

	glEnd();
}
//--------------------------------
void Utils3d::DrawSquare( Float3 & v1, Float3 & v2,  Float3 & v3, Float3 & v4)
{
	glBegin( GL_POLYGON );

		glNormal3fv( v1 );
		glVertex3fv( v1 );

		glNormal3fv( v2 );
		glVertex3fv( v2 );

		glNormal3fv( v3 );
		glVertex3fv( v3 );

		glNormal3fv( v4 );
		glVertex3fv( v4 );

	glEnd();
}
//--------------------------------
void Utils3d::Subdivide3(  Float3 &v1, Float3 &v2, Float3 &v3, long depth, float pFact )
{
	Normalize( v1, pFact );
	Normalize( v2, pFact );
	Normalize( v3, pFact );

	Float3 v12, v23, v31;

	if( depth == 0 )
	{
		DrawTriangle( v1, v2, v3 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = v1[ i ] + v2[ i ];
		v23[ i ] = v2[ i ] + v3[ i ];
		v31[ i ] = v3[ i ] + v1[ i ];
	}

//	Normalize( v12 );
//	Normalize( v23 );
//	Normalize( v31 );


	depth--;
	Subdivide3( v1, v12, v31, depth, pFact );
	Subdivide3( v2, v23, v12, depth , pFact);
	Subdivide3( v3, v31, v23, depth, pFact );
	Subdivide3( v12, v23, v31, depth, pFact );
}
//--------------------------------
void Utils3d::Subdivide4( Float3 &v1, Float3 &v2, Float3 &v3, Float3 &v4, long depth, float pFact )
{
	Normalize( v1, pFact  );
	Normalize( v2, pFact  );
	Normalize( v3, pFact );
	Normalize( v4, pFact  );

	Float3 v12, v23, v34, v41;

	if( depth == 0 )
	{
		DrawSquare( v1, v2, v3, v4 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = v1[ i ] + v2[ i ];
		v23[ i ] = v2[ i ] + v3[ i ];
		v34[ i ] = v3[ i ] + v4[ i ];
		v41[ i ] = v4[ i ] + v1[ i ];
	}


	depth--;
	Subdivide3( v1, v12, v41, depth, pFact );
	Subdivide3( v2, v23, v12, depth, pFact );
	Subdivide3( v3, v34, v23, depth, pFact );
	Subdivide3( v4, v41, v34, depth, pFact );
	Subdivide4( v12, v23, v34, v41, depth, pFact );
}
//--------------------------------
void Utils3d::DrawTriangleTex( Float3 & v1, Float3 & v2,  Float3 & v3,
 Float2 &t1, Float2 &t2, Float2 &t3)
{
	glBegin( GL_POLYGON );

	Float3 lNorm;
		Normal( v1, v2, v3, lNorm );

//		cout << "t1:" << t1[0] << "," << t1[1]
//  		<< " t2:" << t2[0] << "," << t2[1]
//  		<< " t3:" << t3[0] << "," << t3[1] <<endl;


//		glNormal3fv( lNorm );
		glNormal3fv( v1 );
		glTexCoord2fv( t1 );
		glVertex3fv( v1 );

//		glNormal3fv( lNorm );
		glNormal3fv( v2 );
		glTexCoord2fv( t2 );
		glVertex3fv( v2 );

//		glNormal3fv( lNorm );
		glNormal3fv( v3 );
		glTexCoord2fv( t3 );
		glVertex3fv( v3 );

	glEnd();
}
//--------------------------------
void Utils3d::DrawSquareTex( Float3 & v1, Float3 & v2,  Float3 & v3, Float3 & v4,
	Float2 &t1, Float2 &t2, Float2 &t3, Float2 &t4)
{
	glBegin( GL_POLYGON );

		glNormal3fv( v1 );
		glTexCoord2fv( t1 );
		glVertex3fv( v1 );

		glNormal3fv( v2 );
		glTexCoord2fv( t2 );
		glVertex3fv( v2 );

		glNormal3fv( v3 );
		glTexCoord2fv( t3 );
		glVertex3fv( v3 );

		glNormal3fv( v4 );
		glTexCoord2fv( t4 );
		glVertex3fv( v4 );

	glEnd();
}
//--------------------------------
void Utils3d::Subdivide3Tex(  Float3 &v1, Float3 &v2, Float3 &v3,
	Float2 &t1, Float2 &t2, Float2 &t3, long depth, float pFact )
{
	Normalize( v1, pFact );
	Normalize( v2, pFact );
	Normalize( v3, pFact );

	Float3 v12, v23, v31;
	Float2 t12, t23, t31;

	if( depth == 0 )
	{
		DrawTriangleTex( v1, v2, v3, t1, t2, t3 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = v1[ i ] + v2[ i ];
		v23[ i ] = v2[ i ] + v3[ i ];
		v31[ i ] = v3[ i ] + v1[ i ];
	}

	for( int t = 0; t < 2; t++ )
	{
		t12[ t ] = (t1[ t ] + t2[ t ])/2.0;
		t23[ t ] = (t2[ t ] + t3[ t ])/2.0;
		t31[ t ] = (t3[ t ] + t1[ t ])/2.0;
	}



//	Normalize( v12 );
//	Normalize( v23 );
//	Normalize( v31 );


	depth--;
	Subdivide3Tex(  v1, v12, v31,  t1, t12, t31, depth, pFact );
	Subdivide3Tex(  v2, v23, v12,  t2, t23, t12, depth, pFact );
	Subdivide3Tex(  v3, v31, v23,  t3, t31, t23, depth, pFact );
	Subdivide3Tex(  v12, v23, v31, t12, t23, t31, depth, pFact );

}
//--------------------------------
void Utils3d::Subdivide4Tex( Float3 &v1, Float3 &v2, Float3 &v3, Float3 &v4,
 Float2 &t1, Float2 &t2, Float2 &t3, Float2 &t4, long depth, float pFact )
{
	Normalize( v1, pFact  );
	Normalize( v2, pFact  );
	Normalize( v3, pFact );
	Normalize( v4, pFact  );

	Float3 v12, v23, v34, v41;
	Float2 t12, t23, t34, t41;

	if( depth == 0 )
	{
		DrawSquareTex( v1, v2, v3, v4, t1, t2, t3, t4 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = v1[ i ] + v2[ i ];
		v23[ i ] = v2[ i ] + v3[ i ];
		v34[ i ] = v3[ i ] + v4[ i ];
		v41[ i ] = v4[ i ] + v1[ i ];
	}

	for( int t = 0; t < 2; t++ )
	{
		t12[ t ] = (t1[ t ] + t2[ t ])/2.0;
		t23[ t ] = (t2[ t ] + t3[ t ])/2.0;
		t34[ t ] = (t3[ t ] + t4[ t ])/2.0;
		t41[ t ] = (t4[ t ] + t1[ t ])/2.0;
	}

	depth--;
	Subdivide3Tex(  v1, v12, v41,  t1, t12, t41,depth, pFact );
	Subdivide3Tex(  v2, v23, v12,  t2, t23, t12,depth, pFact );
	Subdivide3Tex(  v3, v34, v23,  t3, t34, t23,depth, pFact );
	Subdivide3Tex(  v4, v41, v34,  t4, t41, t34, depth, pFact );
	Subdivide4Tex(  v12, v23, v34, v41, t12, t23, t34, t41,depth, pFact );
}

//**************************************
