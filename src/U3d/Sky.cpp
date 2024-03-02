#include <FL/glut.H>

#include "Sprite3d/World.h"
#include "T3d/T3dColor.h"

#include "Sky.h"
#include <iostream>
#include "Sprite3d/Random.h"
#include <math.h>

//***************************
Sky::Sky( float pRadius, int pNb )
:Sprite3d( pRadius ),
cNb(pNb)
{
	if( cNb>1000 )
		cNb = 1000;

	cRadius = pRadius;

	for( int i=0; i< cNb; i++)
	{
		float cAngle = randf(6.20 );
		cTab[i] = Double3( cos(cAngle), randf( 1), sin(cAngle));
	}
  Double3 lD3( 0, 2, 0);
  SpriteDouble3::set( SPRITE_SPIN, lD3 );

  float lSz = 1000;
  Double3 lScale3( lSz, lSz, lSz );

  MkSetSCALE( lScale3 );
}
//----------------------
void Sky::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	glDisable( GL_LIGHTING );
	
	glPointSize( 1 );
	glColor4fv( White4 );

	glBegin( GL_POINTS );
	int i=0;
	for(  i=0; i< cNb*0.8; i++)
	{
		glVertex3dv( cTab[i] ); 
	}
	glEnd();

	glPointSize( 2);
	glBegin( GL_POINTS );
	for( ; i< cNb; i++)
	{
		glVertex3dv( cTab[i] ); 
	}
	glEnd();


	glEnable(GL_LIGHTING);
}
//***************************
