#ifndef h_Sprite3d_h
#define h_Sprite3d_h

#include <vector>

#include <T3d/T3dTransf.h>
#include <O3d/O3dObj.h>

#include <Sprite3d/World.h>
#include <Sprite3d/WorldControler.h>

class Action;
class Sprite3d;

enum EnumSpriteDouble3
	{
		SPRITE_SPEED,   //POS,
		SPRITE_SPIN,    //ANGLE,
		SPRITE_GROW,    //SCALE,
		SPRITE_DELTA_V, //SPEED
		MAX_SPRITE_DOUBLE3
	};

enum EnumSpriteAction
	{
		SPRITE_ACTION_ANIMATE,
		SPRITE_ACTION_LEAVE_WORLD,
		SPRITE_ACTION_COLLISION,
		SPRITE_ACTION_KILL,
		SPRITE_USER_ACTION,
		MAX_SPRITE_ACTION
	};

enum EnumSpriteFloat
	{
		SPRITE_LIFE_POINT,
		SPRITE_MAX_LIFE_POINT,
		SPRITE_DESTROY_POINT,
		SPRITE_LIFETIME,
		SPRITE_BIRTHTIME,
		SPRITE_TIMER1,
		SPRITE_TIMER2,
		SPRITE_TIMER3,
		SPRITE_USER1,
		SPRITE_USER2,
		SPRITE_USER3,
		SPRITE_USER4,
		SPRITE_USER5,
		SPRITE_USER6,
		MAX_SPRITE_FLOAT
	};
enum EnumSpriteLong
	{		SPRITE_TYPE,
		MAX_SPRITE_LONG
	};

typedef T3dTab < Double3, Double3 &, EnumSpriteDouble3, MAX_SPRITE_DOUBLE3>SpriteDouble3;
template <> inline void T3dTab < Double3, Double3 &, EnumSpriteDouble3, MAX_SPRITE_DOUBLE3>::set( EnumSpriteDouble3 pIdx, Double3 & pObj )
{
	cFlags[pIdx]=GL_TRUE;
	::memcpy( (void*)&cVect[ pIdx ], &pObj, sizeof( Double3 ) );
	cVect[ pIdx ] *= WorldControler::GetRatio();
}

typedef T3dTab<float, float, EnumSpriteFloat, MAX_SPRITE_FLOAT>SpriteFloat;
typedef T3dTab<long, long, EnumSpriteLong, MAX_SPRITE_LONG>SpriteLong;

//**************************************
class Sprite3dDeleteControler{
public:
	Sprite3dDeleteControler(){;}
	virtual bool execDelete( Sprite3d* pToDel ) { return false;}
};
//**************************************

class Sprite3d : public O3dObj, public SpriteDouble3, public SpriteFloat, public SpriteLong
{
public:

#define InfinityLife -1.0
#define InfinyLifeTime -1.0
#define InteractNull  0x0
#define InteractAll  0xFFFF

	


protected:

	Action *cVectAction[ MAX_SPRITE_ACTION ];
	void   *cVectActionParam[ MAX_SPRITE_ACTION ];
	unsigned int cInteractDef;
	unsigned int cInteractAtt;

	Sprite3dDeleteControler* cDeleteControler;

public:
	long cLastColId;

	virtual int getSpriteType() { return 0; }

public:
	Sprite3d( float cRadius, float pLifeTime=-1.0 );
  virtual ~Sprite3d();
	virtual const char*  getStrName() { return ""; }

	virtual void drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps )	{;	}
	virtual void makeDraw( O3dViewProps& pVProps, O3dObjProps* pObjProps);
	
	virtual GLboolean         animate();	
	virtual GLboolean         leaveWorld();
	virtual GLboolean collision
( Sprite3d & pSprite );

	virtual float getRadius() {return cRadius; }

	void setAction( EnumSpriteAction pAct, Action *pAction, void*pParam=NULL )	{ cVectAction[pAct] = pAction;cVectActionParam[pAct] = pParam;	}
	long fireUserAction( void*pParam1 = NULL,  void*pParam2 = NULL);

	void resetRatio(float pOldRatio);
	void setDeleteControler( Sprite3dDeleteControler* pControl ) { cDeleteControler=pControl; } 

	Sprite3dDeleteControler* getDeleteControler() { return cDeleteControler; }

	// le Def mask defini l'objet et le Att mask avec qui il interagit !

	void setMask( unsigned short def, unsigned short att )
	{
		cInteractDef  = def ;
		cInteractAtt  = att;
	}

	unsigned short getDefMask()
	{
		return cInteractDef;
	}
	unsigned short getAttMask()
	{
		return  cInteractAtt;
	}

	void resetLife();

	GLboolean intersect(  Double3 pPos, float pRadius );
	GLboolean intersectXY(  Double3 pPos, float pRadius );
	
	
	virtual const char* getStrInfo() { return ""; }


	static void   VerifSpeedDelta( double& pV, double& pDV, double pMaxV, double pMaxDV );
	static double GetAngle( double pCos, double pSin );


protected:
	bool cDestroy;

public:
	void destroy(){
		cDestroy = true;
	}

	bool isDestroy(){ return cDestroy; }

};
//**************************************

typedef std::vector < Sprite3d *> VSprite3d;


#define MkGetSPEED()   SpriteDouble3::get( SPRITE_SPEED )
#define MkGetSPIN()    SpriteDouble3::get( SPRITE_SPIN )
#define MkGetGROW()    SpriteDouble3::get( SPRITE_GROW )
#define MkGetDELTAV()  SpriteDouble3::get( SPRITE_DELTA_V )

#define MkSetSPEED(A)  SpriteDouble3::set( SPRITE_SPEED, A )
#define MkSetSPIN(A)   SpriteDouble3::set( SPRITE_SPIN, A )
#define MkSetGROW(A)   SpriteDouble3::set( SPRITE_GROW, A )
#define MkSetDELTAV(A) SpriteDouble3::set( SPRITE_DELTA_V, A )


#define MkGetTYPE()     SpriteLong::get(SPRITE_TYPE)
#define MkSetTYPE(A)    SpriteLong::set(SPRITE_TYPE, A)

#define MkGetLIFE()     SpriteFloat::get(SPRITE_LIFE_POINT)
#define MkGetMAXLIFE()  SpriteFloat::get(SPRITE_MAX_LIFE_POINT)
#define MkGetDESTROY()  SpriteFloat::get(SPRITE_DESTROY_POINT)
#define MkGetUSER1()    SpriteFloat::get(SPRITE_USER1)
#define MkGetUSER2()    SpriteFloat::get(SPRITE_USER2)
#define MkGetUSER3()    SpriteFloat::get(SPRITE_USER3)
#define MkGetUSER4()    SpriteFloat::get(SPRITE_USER4)
#define MkGetUSER5()    SpriteFloat::get(SPRITE_USER5)

#define MkSetLIFE(A)     SpriteFloat::set(SPRITE_LIFE_POINT, A)
#define MkSetMAXLIFE(A)  SpriteFloat::set(SPRITE_MAX_LIFE_POINT, A)
#define MkSetDESTROY(A)  SpriteFloat::set(SPRITE_DESTROY_POINT, A)
#define MkSetUSER1(A)    SpriteFloat::set(SPRITE_USER1, A)
#define MkSetUSER2(A)    SpriteFloat::set(SPRITE_USER2, A)
#define MkSetUSER3(A)    SpriteFloat::set(SPRITE_USER3, A)
#define MkSetUSER4(A)    SpriteFloat::set(SPRITE_USER4, A)
#define MkSetUSER5(A)    SpriteFloat::set(SPRITE_USER5, A)

#endif
