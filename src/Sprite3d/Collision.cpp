#include "Collision.h"
#include <algorithm>
#include "Sprite3d.h"
#include <iostream>

#include <vector>
#include <set>

#include "Array3d.h"

static const unsigned long coll_mask= 0x3F;
static const unsigned long coll_dec = 0x0A;

// Optimisation on pourrait peut etre allouer directement new VSprite3d[pNbDiv]
// cela pourrait

#define DBGOUT if( 0 ) std::cout

//**********************************************************

Collision::CollisionSprite::CollisionSprite( Sprite3d * pSpriteA,  Sprite3d * pSpriteB )
	:cSpriteA( pSpriteA ),
	 cSpriteB( pSpriteB )
{
}
//----------------------------

GLboolean 
Collision::CollisionSprite::exec()
{
	return cSpriteA->collision( *cSpriteB );
}

//**********************************************************
// 2013 pDim represente la dimension de decoupage ? x 0 y 1 z 2 ?

Collision::Collision(  int pDim, GLdouble pMin, GLdouble pMax, int pNbDiv )
	:cTab(NULL),
	 cDim(pDim),
	 cNbDiv(pNbDiv),
	 cPosIter(0),
	 cMin( pMin)
{
	cMul = pNbDiv/(pMax-pMin);

	DBGOUT << "Collision cMul:" << cMul << std::endl;

	cTab = new VSprite3d*[pNbDiv];

	for( int i=0; i<pNbDiv; i++)
		cTab[i] = NULL;
}
//--------------------------------
Collision::~Collision()
{
	for( int i=0; i< cNbDiv; i++)
		delete cTab[i];

	delete []cTab;
}
//--------------------------------
Array3d< std::vector<Sprite3d*> > *
Collision::InitSpatialDetection3D(  T3dBox& pBox, Double3 pDiv  )
{
	// Calcul de la taille de la zone surveillé

	Double3 lDimSize = pBox.size();
  Double3 lMinBox  = pBox.getMin();

 
	 int lDimZone[3];
	 for( int i=0; i< 3 ; i++ )
		 {
			 lDimZone[i] = (int)(lDimSize[i] / pDiv[i]);
		 }

	 std::cout << "****** SpatialDetection3D Box: ";
	 pBox.print( std::cout ) << " Div:";
	 pDiv.print( std::cout ) << "DimSize";
	 lDimSize.print( std::cout ) << " MinBox:";
	 lDimSize.print(std::cout) << " MinBox: " ;
	 lMinBox.print(std::cout) << " DimZone:" ;
	 std::cout << " DimZone:" << lDimZone[0] << ','  << lDimZone[1] << ',' << lDimZone[2] << std::endl;

	return new Array3d< std::vector<Sprite3d*> >( lDimZone, lDimSize,  lMinBox, pBox, pDiv );
}
//--------------------------------
void
Collision::CleanSpatialDetection3D( 	Array3d< std::vector<Sprite3d*> >& pZones )
{
for( int i=0; i< pZones.getSizeGen(); i++)
	{
		pZones.get( i ).clear();
	}
}
//--------------------------------

//long lNbCalcul=0;


inline 
GLboolean Collision::DetectCollision( Sprite3d &A, Sprite3d &B )
{
//	lNbCalcul++;

	Double3 lDist( A.getTransf().get( POS ));
	lDist -= B.getTransf().get( POS );


	double lRadius = A.getRadius() + (double)B.getRadius();
	if( (lDist[ 0 ]*lDist[ 0 ] + lDist[ 1 ]*lDist[ 1 ] + lDist[ 2 ]*lDist[ 2 ]) < (lRadius *lRadius) )
		return GL_TRUE;

	return GL_FALSE;
}
//--------------------------------

long 
Collision::SpatialDetection3D( VSprite3d& pSprites,  Array3d< std::vector<Sprite3d*> >& pZones )
{
	int lNbSprites=0;
	int lNbSpritesZones=0;

	//	std::cout << "*********************************************************" <<  std::endl;
	//lNbCalcul = 0;

  // on dispatche les sprites dans les differente zones
	for( VSprite3d::iterator iter = pSprites.begin(); iter != pSprites.end(); ++iter )
		{
			if( (*iter)== nullptr ) continue;
			if( (*iter)->getDefMask() == InteractNull || (*iter)->getAttMask() == InteractNull  ) continue;
	
			// postion du sprite
			Double3 lPos = (*iter)->getTransf().TransfDouble3::get(POS);
			

			// le sprite est il dans la boite monde
			if( pZones.cBox.isInto( lPos ) == GL_FALSE )
				continue;

			lPos -= pZones.cMinBox; // Passage en coordonnees positive


			Double3 lMin = lPos; // limite minimale du sprite			
			Double3 lMax = lPos; // limite maximale du sprite


			for( int i =0; i< 3; i++ )
				{
					//	if( pZones.cDiv[i] >1 )
						{
							lMin[i] -= (*iter)->getRadius();
							lMin[i] /= pZones.cDiv[i]; 
							lMax[i] += (*iter)->getRadius();
							lMax[i] /= pZones.cDiv[i]; 
						}
				}

			lNbSprites++;

			// Pour toutes les positions occupes par le sprite dans la zone
			for( int x=lMin[0]; x<= lMax[0]; x++ )
				{
					if( x<0 || x >= pZones.getSize(0)) 
						continue;

					for( int y=lMin[1]; y<= lMax[1]; y++ )
						{
							if( y <0 || y >= pZones.getSize(1) )
								continue;

						 for( int z=lMin[2]; z<= lMax[2]; z++ )
							 {
								 if( z <0 || z >= pZones.getSize(2))
									 continue;

								 lNbSpritesZones++;

								 //						 std::cout << "Collision push x:" << x << " y:" << y << " z:" << z  << std::endl;
								 // we add the sprite into the zone x,y,z

								 pZones.get( x, y, z).push_back( (*iter) ); 
								 
							 }
						}			
				}			
		}
	
	//	std::cout << "****** Collision::SpatialDetection3D NbSprites:" << lNbSprites << " zone:" << lNbSpritesZones << std::endl;




	/*
 for( int x=0; x< pZones.getSize(0); x++) 
	 {
		 for( int y=0; y<  pZones.getSize(1); y++ )
			 {
				 for( int z=0; z< pZones.getSize(2); z++ )
					 {
						 std::vector<Sprite3d*>& lVect = pZones.get( x, y, z );
								if( lVect.size() != 0 )
									std::cout << "x:" << x << " y:" << y << " z:"<< z << " " << lVect.size() << std::endl;
					 }
				}
		}
	*/

// Pour toutes les zones il faut calculer les collisions
// les resultat sont mis dans un set, ce qui elimine les doublons

	pZones.activate();

	std::set<CollisionSprite> ContainerCollision;

	for( int i=0; i< pZones.getSizeGen(); i++)
		{
			SimpleDetection( 	pZones.get( i ), ContainerCollision );
		}

	//	std::cout << "**** Collision::SpatialDetection3D NbCollision:" << ContainerCollision.size() <<  " Calcul:" << lNbCalcul << std::endl;

// On execute les collisions
	for( std::set<CollisionSprite>::iterator iterCol = ContainerCollision.begin(); iterCol != ContainerCollision.end(); ++iterCol )
		{
			const_cast<CollisionSprite&>(*iterCol).exec();
		}

	return ContainerCollision.size();
}


//----------------------------------------
// Detecte et appelle la proc de collision
// Algo en factorielle N (peu efficace pour de nombreux sprites)

// static 

long 
Collision::SimpleDetection(VSprite3d& pVSprite)
{
	int lCpt=0;
	int lCpt2=0;
	//lNbCalcul = 0;

	for( VSprite3d::iterator iter = pVSprite.begin(); iter != pVSprite.end(); ++iter )
		{
			if( (*iter)== nullptr ) continue;

			unsigned int maskA_Def = (*iter)->getDefMask();
			unsigned int maskA_Att = (*iter)->getAttMask();

			if( maskA_Def == 0 && maskA_Att == 0 )
				continue;

			for( VSprite3d::iterator iter2 = iter + 1; iter2 != pVSprite.end(); ++iter2 )
				{
				if( (*iter2)== nullptr ) continue;

					unsigned int maskB_Def =  (*iter2)->getDefMask();
					unsigned int maskB_Att = (*iter2)->getAttMask();
					//			if( maskB_Def == 0 && maskB_Att == 0 )
					//		continue;

					lCpt++;


					unsigned int MaskA = maskA_Def & maskB_Att;
					unsigned int MaskB = maskA_Att & maskB_Def;
						

					if(  ( MaskA || MaskB )
							 && DetectCollision( *(*iter), *(*iter2) ) )
						{
							lCpt2++;
							// ON POURRAIT METTRE L EXECUTION DES COLLISIONS DANS UN THREAD !!!  mutex a mettre ...
							if( MaskA )
								(*iter)->collision( *(*iter2) );

							if( MaskB )
								(*iter2)->collision( *(*iter) );
						}
				}
		}
	//	std::cout << " SimpleDetection: " << pVSprite.size() << " " << lCpt << " -> " << lCpt2<<  " Calcul:" << lNbCalcul << std::endl;

	DBGOUT << " SimpleDetection: " << pVSprite.size() << " " << lCpt << " -> " << lCpt2 << std::endl;
	return lCpt2;
}
//----------------------------------------
// We detect collision and store them into a set, duplicate collision are ignored (because set refuse them)

long 
Collision::SimpleDetection( VSprite3d& pVSprite, std::set<CollisionSprite>& pContainer )
{
	int lCpt=0;
	int lCpt2=0;

	for( VSprite3d::iterator iter = pVSprite.begin(); iter != pVSprite.end(); ++iter )
		{
			if( (*iter)== nullptr ) continue;

			unsigned int maskA_Def = (*iter)->getDefMask();
			unsigned int maskA_Att = (*iter)->getAttMask();

			if( maskA_Def == 0 && maskA_Att == 0 )
				continue;

			for( VSprite3d::iterator iter2 = iter + 1; iter2 != pVSprite.end(); ++iter2 )
				{
				if( (*iter2)== nullptr ) continue;

					unsigned int maskB_Def =  (*iter2)->getDefMask();
					unsigned int maskB_Att = (*iter2)->getAttMask();
					//	if( maskB_Def == 0 && maskB_Att == 0 )
					//						continue;

	
					lCpt++;

					unsigned int MaskA = maskA_Def & maskB_Att;
					unsigned int MaskB = maskA_Att & maskB_Def;
				
 
					if(  ( MaskA || MaskB )
							 && DetectCollision( *(*iter), *(*iter2) ) )
						{
							lCpt2++;
														

							if( MaskA )
								{
									CollisionSprite lCol( (*iter), (*iter2) );
									pContainer.insert( lCol );
								}

							if( MaskB  )
								{
									CollisionSprite lCol( (*iter2), (*iter) );
									pContainer.insert( lCol );
								}
						}
				}
		}

	DBGOUT << " SimpleDetection: " << pVSprite.size() << " " << lCpt << " -> " << lCpt2 << std::endl;
	return lCpt2;
}

//**********************************************************
