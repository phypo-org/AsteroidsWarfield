
#ifndef _T3dType_h_
#define _T3dType_h_

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#if defined(_WIN32)
#include <FL/glut.H>
#else
#include <FL/gl.h>
//#include <GL/glx.h>
#include <FL/glu.h>
#endif

#include <string.h>

#include <T3d/TVectType.h>


/*---------------------------------------------------------------------*/
/*    typedef ...                                                      */
/*---------------------------------------------------------------------*/


typedef TVectType<GLdouble, 3> Double3;

template <> inline TVectType<GLdouble, 3> ::TVectType( GLdouble A, GLdouble B, GLdouble C, GLdouble D)
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	cVect[ 2 ] = C;
	(void)D;
}

typedef TVectType<GLdouble,4>  Double4;
template <> inline TVectType<GLdouble, 4> ::TVectType( GLdouble A, GLdouble B, GLdouble C, GLdouble D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	cVect[ 2 ] = C;
	cVect[ 3 ] = D;
}

typedef TVectType<GLfloat,2> Float2;
template <> inline TVectType<GLfloat, 2> ::TVectType( GLfloat A, GLfloat B, GLfloat C, GLfloat D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	(void)C;
    (void)D;
}
typedef TVectType<GLfloat,3> Float3;
template <> inline TVectType<GLfloat, 3> ::TVectType( GLfloat A, GLfloat B, GLfloat C, GLfloat D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	cVect[ 2 ] = C;
    (void)D;
    }
typedef TVectType<GLfloat,4> Float4;
template <> inline TVectType<GLfloat, 4> ::TVectType( GLfloat A, GLfloat B, GLfloat C, GLfloat D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	cVect[ 2 ] = C;
	cVect[ 3 ] = D;
}

typedef TVectType<GLint,2> Int2;
template <> inline TVectType<GLint, 2> ::TVectType( GLint A, GLint B, GLint C, GLint D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
    (void)C;
    (void)D;
}
typedef TVectType<GLint,3> Int3;
template <> inline TVectType<GLint, 3> ::TVectType( GLint A, GLint B, GLint C, GLint D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	cVect[ 2 ] = C;
   (void)D;
}
typedef TVectType<GLint,4> Int4;
template <> inline TVectType<GLint, 4> ::TVectType( GLint A, GLint B, GLint C, GLint D )
{
	cVect[ 0 ] = A;
	cVect[ 1 ] = B;
	cVect[ 2 ] = C;
	cVect[ 3 ] = D;
}


#endif
