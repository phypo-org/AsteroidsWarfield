#ifndef h_Type_h
#define h_Type_h

#include <GL/glut.h>
#include <memory.h>

typedef GLfloat Float3[3];
typedef GLfloat Float4[4];

typedef GLdouble Double3[3];
typedef GLdouble Double4[4];

typedef char Bool;
#define FALSE 0
#define TRUE 1


#define CPY_FLOAT3(A,B) memcpy( (A),(B),sizeof( Float3))
#define CPY_FLOAT4(A,B) memcpy( (A),(B),sizeof( Float4))
#define CPY_DOUBLE3(A,B) memcpy( (A),(B),sizeof( Double3))
#define CPY_DOUBLE4(A,B) memcpy( (A),(B),sizeof( Double4))
#endif
