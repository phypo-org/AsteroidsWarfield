
#include "T3dPrimitiv.h"

#include "T3dCalcul.h"
#include "T3dColor.h"
#include "T3dVect3D.h"

#include <string.h>

#define sTsz 3
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawChar ...                                       */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawChar( float pX, float pY, float pZ, float pSz,  char pChar )
{	

	Float3 P[ sTsz ][ sTsz ];

	float lPas = pSz / sTsz;

//	float x = -pSz;
	float x = 0;

	for( int i = 0; i < sTsz; i++  )
	{
		float y = pSz-lPas;
		for( int j = 0; j < sTsz; j++ )
		{
			Float3 &p =  P[ i ][ j ];
			p[ 0 ] = pX+x;
			p[ 1 ] = pY+y;
			p[ 2 ] = pZ;
			
			y -= lPas;
		}
		x+= lPas;
	}

#define P1 			glVertex3fv( P[0][0] );
#define P2			glVertex3fv( P[1][0] );
#define P3			glVertex3fv( P[2][0] );
#define P4		  glVertex3fv( P[0][1] );
#define P5		  glVertex3fv( P[1][1] );
#define P6			glVertex3fv( P[2][1] );
#define P7			glVertex3fv( P[0][2] );
#define P8			glVertex3fv( P[1][2] );
#define P9			glVertex3fv( P[2][2] );

	glBegin( GL_LINE_STRIP );
	switch( pChar )
	{
		case '0':
			P1; P3; P9; P7; P1;
			break;


		case '1':
			P2; P8;
			break;
		case '2':
			P1; P3; P6;
			P4; P7; P9
			break;
		case '3':
			P1; P3; P6; P4; P6; P9; P7;
			break;
		case '4':
			P1; P4; P6; P9;
			break;
		case '5':
			P3; P1; P4; P6; P9; P7;
			break;
		case '6':
			P3; P1; P7; P9; P6; P4;
			break;
		case '7':
			P1; P3; P8;
			break;
		case '8':
			P1; P3; P9; P7; P1;
			P4; P6;
			break;
		case '9':
			P6; P4; P1; P3; P9; P7;
			break;
		case '-':
			P5; P6;
			break;
		case '/':
			P3; P7;
			break;
		case '+':
			P4; P6; P5;P2; P8;
			break;

		case '.':
			glEnd();
			glBegin( GL_POINT );				
			P8;
			break;
		case '_':
			P7; P9;
			break;

		case '=':
			P4; P6;
			glEnd();			
			glBegin( GL_LINE_STRIP );
			P8;P9;
			break;

		case '|':
			P2; P8;
			break;

		case ',':
			P5; P8;
			break;
		case '*':
			P1; P9; P5; P3; P7; P5; P4; P6; P5; P2; P8;
			break;
		case '?':
			P4; P1; P3; P6; P5; P8;
			break;
		case '[':
			P2; P1; P7; P8;
			break;
		case ']':
			P2; P3; P9; P8;
			break;
		case 'E':
			P3; P1; P4; P5; P4; P7; P9;
			break;
		case 'e':
			P4; P6; P3; P1; P7; P9;
			break;
		case 'A':
			P7; P1; P3; P6; P4; P6; P9;
			break;
		case 'X':
			P1; P9; P5; P3; P7;
			break;
		case 'Y':
			P1; P5; P3; P5; P8;
			break;
		case 'Z':
			P1; P3; P7; P9;
			break;

		default:;
	}
					
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawText ...                                       */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawText(  T3dOrientation pOrient, float pX, float pY, float pZ, float pSz, const char* pStr,  int pReverse)
{
	float x =pX;
 	float y =pY;
 	float z =pZ;

	int lNb =strlen( pStr);

//	DrawX( pX, pY, pZ, 10 );
	if( pReverse == 0 )
		for( int i = 0; i < lNb;  i++ )
		{
			DrawChar( x, y, z, pSz, pStr[ i ] );

			if( pOrient == T3d_HORIZONTAL )
			{
				x += pSz;
			}
			else
			{
				y -= pSz;
			}
		
		}
	else
		for( int i = lNb-1; i >= 0;  i--)
		{
			if( pOrient == T3d_HORIZONTAL )
			{
				x -= pSz;
			}
			else
			{
				y += pSz;
			}

			DrawChar( x, y, z, pSz, pStr[ i ] );		
		}

}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawText ...                                       */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawText(  T3dOrientation pOrient, Double3& pPt, float pSz, const char* pStr, int  pReverse)
{
	DrawText( pOrient, pPt[0], pPt[1], pPt[2], pSz, pStr, pReverse );
}

/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawMinus ...                                      */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawMinus( float pX, float pY, float pZ, float pSz )
{
	glBegin( GL_LINES );
	glVertex3f( pX-2*pSz, pY, pZ );
	glVertex3f( pX-pSz, pY, pZ );
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawX ...                                           */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawX( float pX, float pY, float pZ, float pSz )
{	
	glBegin( GL_LINES );
//	glColor3f( 1.0, 0.0, 0.0 );
	glVertex3f( pX-pSz, pY-pSz, pZ );
	glVertex3f( pX + pSz, pY + pSz, pZ );

	glVertex3f( pX+pSz, pY-pSz, pZ  );
	glVertex3f( pX - pSz, pY + pSz, pZ );
	glEnd();

}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawY ...                                           */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawY( float pX, float pY, float pZ, float pSz )
{
	glBegin( GL_LINE_STRIP );
	glVertex3f( pX-pSz, pY+pSz, pZ );
	glVertex3f( pX, pY, pZ );
	glVertex3f( pX, pY - pSz, pZ );
	glVertex3f( pX, pY, pZ );
	glVertex3f( pX+pSz, pY+pSz, pZ );
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawZ ...                                           */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawZ( float pX, float pY, float pZ, float pSz )
{
	glBegin( GL_LINE_STRIP );
	glVertex3f( pX-pSz, pY+pSz, pZ );
	glVertex3f( pX + pSz, pY + pSz, pZ );
	glVertex3f( pX-pSz, pY-pSz, pZ );
	glVertex3f( pX+pSz, pY- pSz, pZ );
	glEnd();

}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Repere ...                                         */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawRepere( float pSz, int  pNeg )
{
	glDisable(GL_LIGHTING);
	
	T3dColor::Red();
	glBegin( GL_LINES );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( pSz, 0.0, 0.0 );
	glEnd();
	DrawX( pSz *1.1, 0.0, 0.0, pSz / 20.0 );


	T3dColor::Green();
	glColor3f( 0.0, 1.0, 0.0 );
	glBegin( GL_LINES );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, pSz, 0.0 );
	glEnd();
	DrawY( 0.0, pSz*1.1, 0.0, pSz/20.0 );


	T3dColor::Blue();	
	glBegin( GL_LINES );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, 0.0, pSz );
	glEnd();
	DrawZ( 0.0, 0.0, pSz*1.1, pSz/20.0 );



	if( pNeg == 1 )
	{
		glLineStipple( 1, 0x00FF );
		glEnable( GL_LINE_STIPPLE );

     	T3dColor::Red();
		glBegin( GL_LINES );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( -pSz, 0.0, 0.0 );
		glEnd();

	    T3dColor::Green();
		glBegin( GL_LINES );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( 0.0, -pSz, 0.0 );
		glEnd();
		
	    T3dColor::Blue();	
		glBegin( GL_LINES );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( 0.0, 0.0, -pSz );
		glEnd();
			
		glDisable( GL_LINE_STIPPLE );
				
     	T3dColor::Red();
		DrawMinus( pSz*-1.1, 0.0, 0.0, pSz/20.0 );
		DrawX( pSz*-1.1, 0.0, 0.0, pSz/20.0 );
					
	    T3dColor::Green();
		DrawMinus( 0.0, -pSz*1.1, 0.0, pSz/20.0 );
		DrawY( 0.0, -pSz*1.1, 0.0, pSz/20.0 );

		T3dColor::Blue();	
		DrawMinus( 0.0, 0.0, -pSz*1.1, pSz/20.0 );
		DrawZ( 0.0, 0.0, -pSz *1.1, pSz / 20.0 );
	}
    glEnable(GL_LIGHTING);

}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawGrid ...                                       */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawGrid( float pSz, int pNb )
{
	   // Turn the lines GREEN
    T3dColor::Green();
	float lPas = pSz / pNb;
	//	float lOrg = pSz / 2;

    // Draw a 1x1 grid along the X and Z axis'
    for(float i = -pSz; i <= pSz; i += lPas )
    {
        // Start drawing some lines
        glBegin(GL_LINES);

            // Do the horizontal lines (along the X)
            glVertex3f(-pSz, 0, i);
            glVertex3f(pSz, 0, i);

            // Do the vertical lines (along the Z)
            glVertex3f(i, 0, -pSz);
            glVertex3f(i, 0, pSz);

        // Stop drawing lines
        glEnd();
    }
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawNappe2D ...                                    */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawNappe2D( float pSz, int pNb )
{
	float lPas = pSz / pNb;
	float lOrg = pSz / 2;

	glDisable( GL_LIGHTING );

	T3dColor::LightGrey();
	glBegin( GL_POINTS );
	for( int x = 0; x < pNb; x++ )
	{
		float xval = x * lPas - lOrg;

		for( int z = 0; z < pNb; z++ )
		{
			float zval = z *lPas - lOrg;

			glVertex3f( xval, 0.0, zval );
		} 
	}
	glEnd();

    glEnable(GL_LIGHTING);
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawNappeT3d ...                                    */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawNappeT3d( float pSz, int pNb )
{
	float lPas = pSz / pNb;
	float lOrg = pSz / 2;


	glBegin( GL_POINTS );
	for( int x = 0; x < pNb; x++ )
	{
		float xval = x * lPas - lOrg;

		for( int y = 0; y < pNb; y++ )
		{
			float yval = y *lPas - lOrg;
			for( int z = 0; z < pNb; z++ )
			{
				float zval = z *lPas - lOrg;
				glVertex3f( xval, yval, zval );
			}
		} 
	}
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::DrawPyramid ...                                    */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::DrawPyramid( float pX, float pY, float pZ, int pWidth, int pHeight)
{
    // Start rendering the 4 triangles for the sides
    glBegin(GL_TRIANGLES);      
        
        // These vertices create the Back Side
        glColor3ub(255, 255, 0);   glVertex3f(pX, pY + pHeight, pZ);                    // Top point
        glColor3ub(255, 255, 255); glVertex3f(pX - pWidth, pY - pHeight, pZ - pWidth);    // Bottom left point
        glColor3ub(255, 0, 0); glVertex3f(pX + pWidth, pY - pHeight, pZ - pWidth);  // Bottom right point

        // These vertices create the Front Side
        glColor3ub(255, 255, 0);   glVertex3f(pX, pY + pHeight, pZ);                    // Top point
        glColor3ub(255, 255, 255); glVertex3f(pX + pWidth, pY - pHeight, pZ + pWidth);  // Bottom right point
        glColor3ub(255, 0, 0); glVertex3f(pX - pWidth, pY - pHeight, pZ + pWidth);    // Bottom left point

        // These vertices create the Front Left Side
        glColor3ub(255, 255, 0);   glVertex3f(pX, pY + pHeight, pZ);                    // Top point
        glColor3ub(255, 0, 0); glVertex3f(pX - pWidth, pY - pHeight, pZ + pWidth);    // Front bottom point
        glColor3ub(255, 255, 255); glVertex3f(pX - pWidth, pY - pHeight, pZ - pWidth);    // Bottom back point

        // These vertices create the Front right Side
        glColor3ub(255, 255, 0);   glVertex3f(pX, pY + pHeight, pZ);                    // Top point
        glColor3ub(255, 0, 0); glVertex3f(pX + pWidth, pY - pHeight, pZ - pWidth);    // Bottom back point
        glColor3ub(255, 255, 255); glVertex3f(pX + pWidth, pY - pHeight, pZ + pWidth);    // Front bottom point
            
    glEnd();

    // Now render the bottom of our pyramid

    glBegin(GL_QUADS);

        // These vertices create the bottom of the pyramid
        glColor3ub(0, 0, 255); glVertex3f(pX - pWidth, pY - pHeight, pZ + pWidth);    // Front left point
        glColor3ub(0, 0, 255); glVertex3f(pX + pWidth, pY - pHeight, pZ + pWidth);    // Front right point
        glColor3ub(0, 0, 255); glVertex3f(pX + pWidth, pY - pHeight, pZ - pWidth);    // Back right point
        glColor3ub(0, 0, 255); glVertex3f(pX - pWidth, pY - pHeight, pZ - pWidth);    // Back left point
    glEnd();
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Subdivide3 ...                                      */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Subdivide3( DoFacette& pToDo, Double3 &v1, Double3 &v2, Double3 &v3, long depth )
{
	Double3 v12, v23, v31;

	if( depth == 0 )
	{
		pToDo.doTriangle(  v1, v2, v3 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = (v1[ i ] + v2[ i ])/2.0;
		v23[ i ] = (v2[ i ] + v3[ i ])/2.0;
		v31[ i ] = (v3[ i ] + v1[ i ])/2.0;
	}

	depth--;
	Subdivide3( pToDo, v1, v12, v31, depth );
	Subdivide3( pToDo, v2, v23, v12, depth );
	Subdivide3( pToDo, v3, v31, v23, depth );
	Subdivide3( pToDo, v12, v23, v31, depth );
}
/*---------------------------------------------------------------------*/
/*     T3dPrimitiv::Subdivide4 ...                                     */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Subdivide4( DoFacette& pToDo, Double3 &v1, Double3 &v2, Double3 &v3, Double3 &v4, long depth )
{
	Double3 v12, v23, v34, v41;

	if( depth == 0 )
	{ 
		pToDo.doSquare( v1, v2, v3, v4 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = (v1[ i ] + v2[ i ])/2.0;
		v23[ i ] = (v2[ i ] + v3[ i ])/2.0;
		v34[ i ] = (v3[ i ] + v4[ i ])/2.0;
		v41[ i ] = (v4[ i ] + v1[ i ])/2.0;
	}

	depth--;
	Subdivide3( pToDo, v1, v12, v41, depth );
	Subdivide3( pToDo, v2, v23, v12, depth );
	Subdivide3( pToDo, v3, v34, v23, depth );
	Subdivide3( pToDo, v4, v41, v34, depth );
	Subdivide4( pToDo, v12, v23, v34, v41, depth );
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Subdivide3Tex ...                                   */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Subdivide3Tex( DoFacette& pToDo, Double3 &v1, Double3 &v2, Double3 &v3,
	Float2& t1, Float2& t2,  Float2& t3, long depth )
{
	Double3 v12, v23, v31;
	Float2  t12, t23, t31;

	if( depth == 0 )
	{
		pToDo.doTriangleTex(  v1, v2, v3, t1, t2, t3 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = (v1[ i ] + v2[ i ])/2.0;
		v23[ i ] = (v2[ i ] + v3[ i ])/2.0;
		v31[ i ] = (v3[ i ] + v1[ i ]) / 2.0;
	}

	for( int t = 0; t < 2; t++ )
	{
		t12[ t ] = (t1[ t ] + t2[ t ])/2.0;
		t23[ t ] = (t2[ t ] + t3[ t ])/2.0;
		t31[ t ] = (t3[ t ] + t1[ t ])/2.0;
	}

	depth--;
	Subdivide3Tex( pToDo, v1, v12, v31,  t1, t12, t31, depth );
	Subdivide3Tex( pToDo, v2, v23, v12,  t2, t23, t12, depth );
	Subdivide3Tex( pToDo, v3, v31, v23,  t3, t31, t23, depth );
	Subdivide3Tex( pToDo, v12, v23, v31, t12, t23, t31, depth );
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Subdivide4Tex ...                                   */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Subdivide4Tex( DoFacette& pToDo, Double3 &v1, Double3 &v2, Double3 &v3, Double3 &v4,
	Float2& t1, Float2& t2,  Float2& t3, Float2& t4, long depth )
{
	Double3 v12, v23, v34, v41;
	Float2 t12, t23, t34, t41;

	if( depth == 0 )
	{ 
		pToDo.doSquareTex( v1, v2, v3, v4, t1, t2, t3, t4 );
		return;
	}

	for( int i = 0; i < 3; i++ )
	{
		v12[ i ] = (v1[ i ] + v2[ i ])/2.0;
		v23[ i ] = (v2[ i ] + v3[ i ])/2.0;
		v34[ i ] = (v3[ i ] + v4[ i ])/2.0;
		v41[ i ] = (v4[ i ] + v1[ i ])/2.0;
	}

	for( int t = 0; t < 2; t++ )
	{
		t12[ t ] = (t1[ t ] + t2[ t ])/2.0;
		t23[ t ] = (t2[ t ] + t3[ t ])/2.0;
		t34[ t ] = (t3[ t ] + t4[ t ])/2.0;
		t41[ t ] = (t4[ t ] + t1[ t ])/2.0;
	}

	depth--;
	Subdivide3Tex( pToDo, v1, v12, v41,  t1, t12, t41,depth );
	Subdivide3Tex( pToDo, v2, v23, v12,  t2, t23, t12,depth );
	Subdivide3Tex( pToDo, v3, v34, v23,  t3, t34, t23,depth );
	Subdivide3Tex( pToDo, v4, v41, v34,  t4, t41, t34, depth );
	Subdivide4Tex( pToDo, v12, v23, v34, v41, t12, t23, t34, t41,depth );
}
/*---------------------------------------------------------------------*/
/*    DoFacette::doTriangle ...                                        */
/*---------------------------------------------------------------------*/

void 
DoFacette::doTriangle( Double3 & v1, Double3 & v2,  Double3 & v3 )
{
	Double3 lNorm;
    T3dCalcul::Normal( v1, v2, v3, lNorm );

	glBegin( GL_POLYGON );
		glNormal3dv( lNorm );
		glVertex3dv( v1 );
		glNormal3dv( lNorm);
		glVertex3dv( v2 );
		glNormal3dv( lNorm);
		glVertex3dv( v3 );
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    DoFacette::doSquare ...                                          */
/*---------------------------------------------------------------------*/

void 
DoFacette::doSquare( Double3 & v1, Double3 & v2,  Double3 & v3, Double3 & v4)
{
	Double3 lNorm;

	glBegin( GL_POLYGON );
	    T3dCalcul::Normal( v4, v1, v2, lNorm );
		glNormal3dv( lNorm);
		glVertex3dv( v1 );

	    T3dCalcul::Normal( v1, v2, v3, lNorm );
		glNormal3dv( lNorm);
		glVertex3dv( v2 );

	    T3dCalcul::Normal( v2, v3, v4, lNorm );
		glNormal3dv( lNorm);
		glVertex3dv( v3 );

	    T3dCalcul::Normal( v3, v4, v1, lNorm );
		glNormal3dv( lNorm);
		glVertex3dv( v4 );
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    DoFacette::doTriangleTex ...                                     */
/*---------------------------------------------------------------------*/

void 
DoFacette::doTriangleTex( Double3 & v1, Double3 & v2,  Double3 & v3,
	Float2& t1, Float2& t2,  Float2& t3 )
{
	Double3 lNorm;
    T3dCalcul::Normal( v1, v2, v3, lNorm );

	glBegin( GL_POLYGON );
		glNormal3dv( lNorm );
		glTexCoord2fv( t1 );
		glVertex3dv( v1 );

		glNormal3dv( lNorm);
		glTexCoord2fv( t2 );
		glVertex3dv( v2 );

		glNormal3dv( lNorm);
		glTexCoord2fv( t3 );
		glVertex3dv( v3 );
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    DoFacette::doSquareTex ...                                       */
/*---------------------------------------------------------------------*/

void 
DoFacette::doSquareTex( Double3 & v1, Double3 & v2,  Double3 & v3, Double3 & v4,
	Float2& t1, Float2& t2,  Float2& t3,  Float2& t4 )
{
	Double3 lNorm;

	glBegin( GL_POLYGON );
	    T3dCalcul::Normal( v4, v1, v2, lNorm );
		glNormal3dv( lNorm );
		glTexCoord2fv( t1 );
		glVertex3dv( v1 );

	    T3dCalcul::Normal( v1, v2, v3, lNorm );
		glNormal3dv( lNorm);
		glTexCoord2fv( t2 );
		glVertex3dv( v2 );

	    T3dCalcul::Normal( v2, v3, v4, lNorm );
		glNormal3dv( lNorm);
		glTexCoord2fv( t3 );
		glVertex3dv( v3 );

	    T3dCalcul::Normal( v3, v4, v1, lNorm );
		glNormal3dv( lNorm);
		glTexCoord2fv( t4 );
		glVertex3dv( v4 );
	glEnd();
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Degrade ...                                         */
/*                                                                     */ 
/*    pPos de 0 a 1                                                    */
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Degrade ...                                         */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Degrade( float  &deb, float  & fin, float pPos, float  & res )
{
	res = deb + (fin - deb)*pPos;
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Degrade ...                                         */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Degrade( Float3 &deb, Float3 & fin, float pPos, Float3 & res )
{
	for( int i = 0; i < 3; i++ )
		Degrade( deb[i], fin[i], pPos, res[i] );
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::Degrade ...                                         */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::Degrade( Float4 &deb, Float4 & fin, float pPos, Float4 & res )
{
	for( int i = 0; i < 4; i++ )
		Degrade( deb[i], fin[i], pPos, res[i] );
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::MakePoles ...                                       */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::MakePoles( Double3* pSrc, int pNb, T3dVect3D& pDest )
{	
	GLdouble *tmp = new GLdouble[ pNb ];
	GLdouble *res = new GLdouble[ pNb ];
	Double3 *dest = new Double3[ pNb ];

	for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < pNb; j++ )
		{
			tmp[ j ] = pSrc[j][i];
		}

		T3dCalcul::Thomas( tmp, res, pNb );

		for( int k = 0; k < pNb; k++ )
			dest[k][i] = res[k];
	}

	// On double le premier point
	pDest.add( dest[0] );
				
	for( int j = 0; j < pNb; j++ )
		pDest.add( dest[ j ] );

	// On double le dernier point
	pDest.add( dest[ pNb - 1 ] );

	delete tmp;
	delete res;
	delete [] dest;
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::InitYama ...                                          */
/*---------------------------------------------------------------------*/

void T3dPrimitiv::InitYama (int pMaille, long pYa1[], long pYa2[])
{
	int i;
	long int mai,maille3;

	mai = pMaille;
	maille3 = mai * mai * mai;
	for ( i=0; i<pMaille+1; i++ )
		{
			pYa1[i] = i*i*i;
			pYa2[i] =(3 * ( ( i*i * (-2L) * mai ) + pYa1[i] ) + 4l*maille3);
		}
}
/*---------------------------------------------------------------------*/
/*    AX3dObjBezier::draw ...                                          */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::MakeBSplinePoint( DoPoint& pDoPoint, int pMaille, Double3* pSrc, int pNb )
{
	long Yam1[ 33 ];
	long Yam2[ 33 ];

	double x, y, z  ;
	double x0,x1,x2,x3,y0,y1,y2,y3,z0,z1,z2,z3;
	int jm;


	InitYama( pMaille,Yam1, Yam2);

#define CX( i )	(pSrc[i][0])
#define CY( i )	(pSrc[i][1])
#define CZ( i )	(pSrc[i][2])


	double multi = 1.0/( 6.0 *Yam1[ pMaille ]);

	/* calcul du premier point de la courbe    */
	x = (CX( 0 ) + 4 *CX( 1 ) + CX( 2 )) / 6.0;
	y = (CY( 0 ) + 4 *CY( 1 ) + CY( 2 )) / 6.0;
	z = (CZ( 0 ) + 4 *CZ( 1 ) + CZ( 2 )) / 6.0;


	pDoPoint.doIt( x, y, z );
	
	/* calcul des autres points */
	for ( int k=0; k< pNb-3; k++ )
	{
		x0 = CX(k);
		x1 = CX(k+1);
		x2 = CX(k+2);
		x3 = CX(k+3);
		y0 = CY(k);
		y1 = CY(k+1);
		y2 = CY(k+2);
		y3 = CY(k+3);
		z0 = CZ(k);
		z1 = CZ(k+1);
		z2 = CZ(k+2);
		z3 = CZ(k+3);

		for ( int j=1; j<pMaille+1; j++ )
		{
			jm = pMaille-j;
			x = ((Yam1[jm] * x0 +
			   	   Yam2[j] * x1 +
			   	   Yam2[jm] * x2 +
		      	   Yam1[j] * x3     	 )  * multi );
			y =  ((Yam1[jm] * y0 +
		      		Yam2[j] * y1  +
		      		Yam2[jm] * y2 +
		      		Yam1[j] * y3     	 )  * multi );
			z =  ((Yam1[jm] * z0 +
		      		Yam2[j] * z1  +
		      		Yam2[jm] * z2 +
		      		Yam1[j] * z3     	 )  * multi );
			pDoPoint.doIt( x, y, z );
		}
	}
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::BSplinePoles2Surf ...                               */
/*    Creer une surface a partir des poles de 2eme niveau              */
/*---------------------------------------------------------------------*/

void
T3dPrimitiv::BSplinePoles2Surf( int pUMaille, int pVMaille, T3dVect3D& pSrc, long pCU, long pCV, T3dVect3D& pDest, long &pU, long &pV )
{
	T3dVect3D cSurf;

	T3dVect3D lPoles1( pCU*pUMaille*pCV);
	StorePoint lStorePole1( lPoles1 );

	for( int v = 0; v < pCV; v++ )
	{
		T3dPrimitiv::MakeBSplinePoint( lStorePole1, pUMaille, &pSrc.get(v*pCU), pCU );
	}


	int lU = (pCU-3)*pUMaille +1 ;

	StorePoint lStorePole2( pDest );

	Double3* lTmp = new Double3[ pCV ];
	for( int u = 0; u < lU; u++ )
	{
		for( int v = 0; v < pCV; v++ )
			lTmp[ v ] = lPoles1.get( v * lU  + u );
		
		T3dPrimitiv::MakeBSplinePoint( lStorePole2, pVMaille, lTmp, pCV );	
	}
	delete lTmp;

	pU = (pCV-3)*pVMaille +1 ;
	pV = (pCU-3)*pUMaille +1 ;
}
/*---------------------------------------------------------------------*/
/*    T3dPrimitiv::BSplineSurf2Poles ...                               */
/*---------------------------------------------------------------------*/

void 
T3dPrimitiv::BSplineSurf2Poles(  T3dVect3D& pSrc, long pCU, long pCV, T3dVect3D& pDest, long &pU, long &pV )
{
	T3dVect3D lPoles1( pCV*(pCU+2) );

	for( int v = 0; v < pCV; v++ )
	{
		T3dPrimitiv::MakePoles( &pSrc.get(v*pCU), pCU,  lPoles1);	
	}

	Double3* lTmp = new Double3[ pCV ];
	for( int u = 0; u < pCU + 2; u++ )
	{
		for( int v = 0; v < pCV; v++ )
			lTmp[ v ] = lPoles1.get( v *( pCU + 2 )+u );

		T3dPrimitiv::MakePoles( lTmp, pCV, pDest);	
	}
	delete lTmp;
	
	pU = pCV+2;
	pV = pCU+2;
}


