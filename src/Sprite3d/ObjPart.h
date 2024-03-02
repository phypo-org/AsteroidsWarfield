#ifndef h_ObjPart_h
#define h_ObjPart_h

#include <vector>
//#include <Sprite3d/TVectPtr.h>

#include <T3d/T3dTab.h>
#include <O3d/O3dObj.h>



enum EnumPartDouble3
{
	PART_POSITION,
	PART_SPEED,
	PART_ACCELERATION,
	PART_ANGLE,
  PART_SPIN, 	
	PART_SPIN_ACCELERATION, 

	// ensuite pour ObjPart seulement
	PART_POSITION_RAND,
	PART_SPEED_RAND,
	PART_ACCELERATION_RAND,
  PART_ANGLE_RAND,
  PART_SPIN_RAND,
	PART_SPIN_ACCELERATION_RAND, 
	MAX_PART_FLOAT3
};

enum EnumPartFloat4
{
	PART_COLOR,
	PART_COLOR_CHG,

	PART_COLOR_END,
	PART_COLOR_RAND,
	MAX_PART_FLOAT4
};

enum EnumPartFloat
{
	PART_LIFETIME,
	PART_SIZE,
	PART_GROW,

	// ensuite pour ObjPart seulement
	PART_LIFETIME_RAND,

	PART_SIZE_RAND,
	PART_GROW_RAND,
  MAX_PART_FLOAT
};

enum EnumPartInt
{
	PART_GEN_NUMBER,
	PART_RAND_NUMBER,
	PART_GEN_VAR_NUMBER,
	PART_DISPERSION_NUMBER,
	MAX_PART_INT
};

typedef T3dTab < Double3, Double3&,  EnumPartDouble3, MAX_PART_FLOAT3> ObjPartDouble3;
typedef T3dTab < Float4, Float4& , EnumPartFloat4, MAX_PART_FLOAT4> ObjPartFloat4;
typedef T3dTab < float,  float,    EnumPartFloat,  MAX_PART_FLOAT>  ObjPartFloat;
typedef T3dTab < int,    int,      EnumPartInt,    MAX_PART_INT>    ObjPartInt;

typedef T3dTab < Double3, Double3&,  EnumPartDouble3, PART_POSITION_RAND> PartDouble3;
typedef T3dTab < Float4, Float4& , EnumPartFloat4, PART_COLOR_END>       PartFloat4;
typedef T3dTab < float,  float,    EnumPartFloat,  PART_LIFETIME_RAND>   PartFloat;
typedef T3dTab < int,    int,      EnumPartInt,    MAX_PART_INT>    PartInt;

//*****************************

class ObjPart:public O3dObj, public ObjPartDouble3, public ObjPartFloat4, public ObjPartFloat,
	public ObjPartInt
{

public:

	//--------------
	// classe a deriver si l'on veut changer 
	// les particules

	class Part : public PartDouble3, public PartFloat4, public PartFloat
	{
	public:
		GLboolean cInLife;
		float cTime;

		Part* cFree;

		Part();
		virtual~Part()		{;}
		virtual void draw(  O3dViewProps& pVProps, O3dObjProps* pObjProps );
		virtual GLboolean animate();
		virtual Part* makeOnePart()                      { return new Part; }
		virtual GLboolean initPart()                     { return GL_TRUE;}

		friend class ObjPart;
	};
	//--------------

protected:

	typedef std::vector<Part*> VPart ; // Le vecteur de particule
//	typedef TVectPtr < Part *> VPart;

	VPart  cVectPart;

	Part*  cPrototype;
	Part*  cFree;
	int    cNbLifePart;

	int    cMemNumber;
	
	GLboolean cForceTransparency;


protected:	
	virtual void generateOnePart();

	Part  *allocPart();
	void  freePart( Part *);


public:
	ObjPart(  float cRadius, Part* pPrototype = NULL );
	virtual ~ObjPart();
	virtual void draw(  O3dViewProps& pVProps, O3dObjProps* pObjProps ); 
	virtual void drawObj(  O3dViewProps& pVProps, O3dObjProps* pObjProps ); 
	virtual GLboolean animate();
	virtual void init( float pLifeTime, float pSize,  int pNb=0, int pStartCycle=0, GLboolean pForceTransparency=GL_FALSE );
	virtual void setForceTransparency( GLboolean pForceTransparency ) { cForceTransparency = pForceTransparency; }

	int   getLifePart() { return cNbLifePart; }
	int   getMaxPart() { return cMemNumber; }
	void  setMaxPart( int pMaxPart) { cMemNumber = pMaxPart ; }	
};
//*****************************
class BaseObjPart : public ObjPart::Part
{
public:
	BaseObjPart() {;}
protected:
	virtual void draw(  O3dViewProps& pVProps, O3dObjProps* pObjProps );	
	virtual void draw()=0;
};
//*****************************
class FacetPart : public BaseObjPart
{
public:
	FacetPart() {;}
protected:
	virtual ObjPart::Part* makeOnePart()        { return new FacetPart; }
	virtual void draw();	
};
//*****************************
class SpherePart : public BaseObjPart
{
	int cNb;
public:
	SpherePart(int pNb=5) :cNb(pNb){;} 
protected:
	virtual ObjPart::Part* makeOnePart()        { return new SpherePart; }
	virtual void draw( );	
};
//*****************************

#endif
