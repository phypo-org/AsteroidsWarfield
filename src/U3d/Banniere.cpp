#include "Banniere.h"


#include "T3d/T3dLoadImg.h"
#include "Space/WorldGame.h"


//*************************************************

Banniere::Banniere( const char* pStr, Float4& pColor )
	:Sprite3d(1.0)
{
	std::string lName;

	WorldGame::GetPathConfig( lName, WorldGame::PathType::TEXTURE, pStr );

  cProps.ObjPropsFloat4::set( MATERIAL, pColor );

	T3dLoadImage lImg( lName.c_str() );

  caTex = new T3dTexture( lImg.width, lImg.height, lImg.makeRGBA() );
	cProps.setTexture( caTex );

	setObjProps( &cProps );
}

//------------------------------------------------
Float3 sPt1( -1.0, -1.0, 0.0 );
Float3 sPt2( -1.0,  1.0, 0.0 );
Float3 sPt3(  1.0,  1.0, 0.0 );
Float3 sPt4(  1.0, -1.0, 0.0 );

Float3 sT1( 0, 1 );
Float3 sT2( 0, 0 );
Float3 sT3( 1, 0 );
Float3 sT4( 1, 1 );

Float3 sNorm( 0.0, 0.0, 1.0 );

//------------------------------------------------

void
Banniere::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	caTex->setCurrent();
	glEnable( GL_TEXTURE_2D );

	glBegin( GL_POLYGON );

	glNormal3fv( sNorm );
	glTexCoord2fv( sT1 );
	glVertex3fv( sPt1 );

	glNormal3fv( sNorm );
	glTexCoord2fv( sT2 );
	glVertex3fv( sPt2 );

	glNormal3fv( sNorm );
	glTexCoord2fv( sT3 );
	glVertex3fv( sPt3 );

	glNormal3fv( sNorm );
	glTexCoord2fv( sT4 );
	glVertex3fv( sPt4 );

	glEnd();

	glDisable( GL_TEXTURE_2D );
}

//*************************************************
