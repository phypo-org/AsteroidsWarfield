#ifndef h_Utils3d_h
#define h_Utils3d_h


#include <T3d/T3dType.h>

//**************************************

class Utils3d
{
public:
	static void Init(const char *pName,int argc, char **argv, int pWidth, int pHeight );
	static void Reshape(int width, int height);
	static void Loop();

	static void Crossprod(Float3 &v1, Float3& v2, Float3& prod);
	static void Normal( Float3 &p1, Float3 &p2, Float3 &p3, Float3 & pNorm );
	static void Normalize(Float3& v, float pVal);
	static void DrawTriangle( Float3 & v1, Float3 & v2,  Float3 & v3);
	static void DrawSquare( Float3 & v1, Float3 & v2,  Float3 & v3, Float3 &v4);
	static void Subdivide3( Float3 &v1, Float3 &v2, Float3 &v3, long depth, float pVal );
	static void Subdivide4( Float3 &v1, Float3 &v2, Float3 &v3, Float3 &v4, long depth, float pVal );

	static void DrawTriangleTex( Float3 & v1, Float3 & v2,  Float3 & v3, Float2 &t1, Float2 &t2, Float2 &t3);
	static void DrawSquareTex( Float3 & v1, Float3 & v2,  Float3 & v3, Float3 &v4, Float2 &t1, Float2 &t2, Float2 &t3, Float2& t4);
	static void Subdivide3Tex( Float3 &v1, Float3 &v2, Float3 &v3, Float2 &t1, Float2 &t2, Float2 &t3, long depth, float pVal );
	static void Subdivide4Tex( Float3 &v1, Float3 &v2, Float3 &v3, Float3 &v4, Float2 &t1, Float2 &t2, Float2 &t3, Float2& t4,  long depth, float pVal );
	
};

//**************************************


#endif
