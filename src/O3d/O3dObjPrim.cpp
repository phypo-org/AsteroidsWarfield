#include "O3dObjPrim.h"
#include <math.h>

#ifdef WIN32
#include <FL/gl.H>
#include <FL/glu.h>
#endif
#include <FL/glut.H>

/*---------------------------------------------------------------------*/
/*    doughnut ...                                                     */
/*---------------------------------------------------------------------*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void
doughnut(GLfloat r, GLfloat R, GLint nsides, GLint rings)
{
  int i, j;
  GLfloat theta, phi, theta1;
  GLfloat cosTheta, sinTheta;
  GLfloat cosTheta1, sinTheta1;
  GLfloat ringDelta, sideDelta;

  ringDelta = 2.0 * M_PI / rings;
  sideDelta = 2.0 * M_PI / nsides;

  theta = 0.0;
  cosTheta = 1.0;
  sinTheta = 0.0;
  for (i = rings - 1; i >= 0; i--) {
    theta1 = theta + ringDelta;
    cosTheta1 = cos(theta1);
    sinTheta1 = sin(theta1);
    glBegin(GL_QUAD_STRIP);
    phi = 0.0;
    for (j = nsides; j >= 0; j--) {
      GLfloat cosPhi, sinPhi, dist;

      phi += sideDelta;
      cosPhi = cos(phi);
      sinPhi = sin(phi);
      dist = R + r * cosPhi;

      glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
      glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
      glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
      glVertex3f(cosTheta * dist, -sinTheta * dist,  r * sinPhi);
    }
    glEnd();
    theta = theta1;
    cosTheta = cosTheta1;
    sinTheta = sinTheta1;
  }
}
/*---------------------------------------------------------------------*/
/*    drawBox ...                                                      */
/*---------------------------------------------------------------------*/

static void
drawBox(GLfloat size, GLenum type)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

static int patchdata[][16] =
{
    /* rim */
  {102, 103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15},
    /* body */
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27},
  {24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40},
    /* lid */
  {96, 96, 96, 96, 97, 98, 99, 100, 101, 101, 101,
    101, 0, 1, 2, 3,},
  {0, 1, 2, 3, 106, 107, 108, 109, 110, 111, 112,
    113, 114, 115, 116, 117},
    /* bottom */
  {118, 118, 118, 118, 124, 122, 119, 121, 123, 126,
    125, 120, 40, 39, 38, 37},
    /* handle */
  {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56},
  {53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
    28, 65, 66, 67},
    /* spout */
  {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83},
  {80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
    92, 93, 94, 95}
};
/* *INDENT-OFF* */

static float cpdata[][3] =
{
    {0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
    -0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
    {0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
    0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
    2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
    2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
    {1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
    1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
    {0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
    0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
    0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
    {1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
    {1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
    -1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
    -0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
    2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
    2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
    2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
    {-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
    -0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
    1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
    -0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
    1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
    0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
    0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
    {2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
    -0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
    2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
    {3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
    {3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
    {2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
    3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
    3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
    -0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
    2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
    2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
    2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
    {0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
    -0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
    0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
    {0.84, -1.5, 0.075}
};

static float tex[2][2][2] =
{
  { {0, 0},
    {1, 0}},
  { {0, 1},
    {1, 1}}
};

/* *INDENT-ON* */

static void
teapot(GLint grid, GLdouble scale, GLenum type)
{
  float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
  long i, j, k, l;

  glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_MAP2_VERTEX_3);
  glEnable(GL_MAP2_TEXTURE_COORD_2);
  glPushMatrix();
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);
  glTranslatef(0.0, 0.0, -1.5);
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 4; k++) {
        for (l = 0; l < 3; l++) {
          p[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
          q[j][k][l] = cpdata[patchdata[i][j * 4 + (3 - k)]][l];
          if (l == 1)
            q[j][k][l] *= -1.0;
          if (i < 6) {
            r[j][k][l] =
              cpdata[patchdata[i][j * 4 + (3 - k)]][l];
            if (l == 0)
              r[j][k][l] *= -1.0;
            s[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
            if (l == 0)
              s[j][k][l] *= -1.0;
            if (l == 1)
              s[j][k][l] *= -1.0;
          }
        }
      }
    }
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2,
      &tex[0][0][0]);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &p[0][0][0]);
    glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
    glEvalMesh2(type, 0, grid, 0, grid);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &q[0][0][0]);
    glEvalMesh2(type, 0, grid, 0, grid);
    if (i < 6) {
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &r[0][0][0]);
      glEvalMesh2(type, 0, grid, 0, grid);
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &s[0][0][0]);
      glEvalMesh2(type, 0, grid, 0, grid);
    }
  }
  glPopMatrix();
  glPopAttrib();
}
//**************************************

void O3dObjPrim::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
//	GLboolean lSkeleton = pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON);
//	GLboolean lSolid = pObjProps->ObjPropsBool::get( DRAW_OBJ_SKELETON );


	static GLUquadricObj *quadObj = NULL;

	if( quadObj == NULL )
		{

		 quadObj = gluNewQuadric();
		 gluQuadricTexture( quadObj,	GL_TRUE );
		}

	if( pObjProps && pObjProps->getTexture() != NULL  )
		{
			pObjProps->getTexture()->setCurrent();
			glEnable( GL_TEXTURE_2D );
		}


	switch( cObjType )
	{
		case PrimPoint:
			glPointSize( cRadius );
			glBegin( GL_POINTS );
			glVertex3f( 0.0, 0.0, 0.0 );
			glEnd();
		break;

		case PrimSphere:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				gluQuadricDrawStyle(quadObj, GLU_LINE);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluSphere(quadObj, cRadius, cSlices, cStacks);
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
				gluQuadricDrawStyle(quadObj, GLU_FILL);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluSphere(quadObj, cRadius, cSlices, cStacks);
			}
		break;

		case PrimTorus:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
				glPushAttrib(GL_POLYGON_BIT);
  				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  				doughnut(cInRadius, cRadius, cSlices, cStacks);
  				glPopAttrib();
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
  				doughnut(cInRadius, cRadius, cSlices, cStacks);
			}
		break;

		case PrimCone:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				gluQuadricDrawStyle(quadObj, GLU_LINE);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluCylinder(quadObj, cRadius, 0.0, cInRadius, cSlices, cStacks);
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
 				gluQuadricDrawStyle(quadObj, GLU_FILL);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluCylinder(quadObj, cRadius, 0.0, cInRadius, cSlices, cStacks);
			}
		break;

		case PrimCylinder:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				gluQuadricDrawStyle(quadObj, GLU_LINE);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluCylinder(quadObj, cRadius, cTop, cInRadius, cSlices, cStacks);
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
 				gluQuadricDrawStyle(quadObj, GLU_FILL);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluCylinder(quadObj, cRadius, cTop, cInRadius, cSlices, cStacks);
			}
		break;

		case PrimDisk:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				gluQuadricDrawStyle(quadObj, GLU_LINE);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluDisk(quadObj, cRadius, cInRadius, cSlices, cStacks);
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
 				gluQuadricDrawStyle(quadObj, GLU_FILL);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluDisk(quadObj, cRadius, cInRadius,  cSlices, cStacks);
			}
		break;

		case PrimPartialDisk:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				gluQuadricDrawStyle(quadObj, GLU_LINE);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluPartialDisk(quadObj, cRadius, cInRadius, cSlices, cStacks, cTop, cEnd);
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
 				gluQuadricDrawStyle(quadObj, GLU_FILL);
  				gluQuadricNormals(quadObj, GLU_SMOOTH);
  				gluPartialDisk(quadObj, cRadius, cInRadius,  cSlices, cStacks, cTop, cEnd);
			}
		break;

		case PrimCube:
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				drawBox( cRadius, GL_LINE_LOOP);
			}
			if(pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
  				drawBox( cRadius, GL_QUADS);
			}
		break;

		case PrimTeapot :
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SKELETON) )
			{
  				teapot(10, cRadius, GL_LINE);
			}
			if( pObjProps->ObjPropsBool::get(DRAW_OBJ_SOLID))
			{
			 teapot( 14, cRadius, GL_FILL );
			}

		break;
		default:;
	}


	if( pObjProps && pObjProps->getTexture() != NULL  )
		{
			glDisable( GL_TEXTURE_2D );
		}

}


//**************************************
