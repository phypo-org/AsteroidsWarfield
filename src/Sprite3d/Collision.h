#ifndef h_Collision_h
#define h_Collision_h

#include <vector>
#include <set>


#include <Sprite3d/Array3d.h>

class Sprite3d;

typedef std::vector < Sprite3d *> VSprite3d; // redefinition


//**************************************
class Collision
{	
	//========================
	class CollisionSprite{
		
		Sprite3d * cSpriteA;
		Sprite3d * cSpriteB;

	public :
		CollisionSprite( Sprite3d * pSpriteA,  Sprite3d * pSpriteB );

		GLboolean exec();

		bool operator <  ( const CollisionSprite& B) const 
		{
			if( cSpriteA == B.cSpriteA )
				return  cSpriteB < B.cSpriteB;
			
			return  cSpriteA < B.cSpriteA;
		}

	};
	//========================

	VSprite3d** cTab;

	float      cMul;
	int        cDim;
	int        cNbDiv;

	int        cPosIter;
	float      cMin;

public:
	Collision( int pDim, GLdouble pMin, GLdouble pMax, int pNbDiv );
	virtual ~Collision();

protected:

public:
	static Array3d< std::vector<Sprite3d*> > *InitSpatialDetection3D( T3dBox& pBox, Double3 pDiv  );
	static void                               CleanSpatialDetection3D( Array3d< std::vector<Sprite3d*> >& pZones );
	static long                               SpatialDetection3D( VSprite3d& pSprites,  Array3d< std::vector<Sprite3d*> >& pZones  );

	static long      SimpleDetection( VSprite3d& pVSprite, std::set<CollisionSprite>& pContainer );
	static long      SimpleDetection( VSprite3d& pVSprite);

	static GLboolean DetectCollision( Sprite3d &A, Sprite3d &B );
};
//**************************************


#endif
