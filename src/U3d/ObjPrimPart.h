#ifndef h_ObjPrimPart_h
#define h_ObjPrimPart_h


#include <Sprite3d/ObjPart.h>



//**********************************
class ObjExplosion:public ObjPart
{
public:
	ObjExplosion( int pNb=500, float pLife=3.0);
};
//**********************************
class ObjFire:public ObjPart
{
public:
	ObjFire( int pNb=500, float pLife=3.0);
};
//**********************************
class ObjSmoke:public ObjPart
{
public:
	ObjSmoke(int pNb=500, float pLife=6.0);
};
//**********************************
class ObjDebris:public ObjPart
{
public:
	ObjDebris(int pNb=500, float pLife=6.0);
};
//**********************************
class ObjEtincelles:public ObjPart
{
public:
	ObjEtincelles( Float4& pColor, int pNb=50, float pLife=6.0, float pSpeed=30 );
	ObjEtincelles( Float4& pColor, Double3 pSpeed, Double3 pDelta, int pNb=50, float pLife=6.0);
};
//**********************************

#endif
