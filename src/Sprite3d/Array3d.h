#ifndef H__ARRAY3D__H
#define H__ARRAY3D__H

#include <T3d/T3dTransf.h>
#include <O3d/O3dObj.h>

//**************************************
template <typename TYPE>
class Array3d{
	
	TYPE *cTab;
	
	int cSz[3];
	int cSzYZ;
	int cSzGen;


public:
	Double3 cDimSize;
  Double3 cMinBox ;
	Double3 cDiv ;
	T3dBox  cBox;

protected:
	bool cActive;
public:
	void activate()    { cActive=true;}
	void desactivate() { cActive=false;}
  bool isActive()    { return cActive; }

	//----------------------------
	void init()
	{
		std::cout << "*** Array3d init("<< cSz[0] << " " << cSz[1] << " " << cSz[2 ] << std::endl;
		
		cSzYZ  = cSz[1]*cSz[2];
		cSzGen = cSz[0]*cSzYZ;
		
		cTab = new TYPE[ cSzGen ];
		
	}
	//----------------------------
public:
	Array3d( int x, int y, int z, 	Double3 pDimSize, Double3 pMinBox,  T3dBox pBox, Double3 pDiv )
		: cTab(nullptr),
			cSz{x,y,z},
			cDimSize(pDimSize),
			cMinBox(pMinBox), 
			cDiv(pDiv),
		 	cBox(pBox), 
		  cActive(false)
	{
		init();
	}
	//----------------------------
	Array3d( int pSz[3], 	Double3 pDimSize, Double3 pMinBox,  T3dBox pBox, Double3 pDiv)
		: cTab(nullptr),
			cSz{pSz[0],pSz[1],pSz[2] },
			cDimSize(pDimSize),
			cMinBox(pMinBox),
			cDiv(pDiv),
			cBox(pBox), 
		 	cActive(false)
	{																																				
		init();
	}
	//----------------------------
	virtual ~Array3d(){
		delete [] cTab;
	}
	//----------------------------
	TYPE& get( int x, int y, int z )
	{

		int pos =  x*cSzYZ + y*cSz[2] + z;
		//		x*cSzY*cSzZ + y*SzZ + z;
		if( x >= cSz[0]  || y >= cSz[1] || z >= cSz[2] || pos <0 || pos >= cSzGen )
			{
				std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>Array3d Out of bound for " << x << " " << y << " " << z << std::endl;
				return cTab[0];
			}
		return cTab[pos];
	}
	//----------------------------
	TYPE& get( Double3 pPos )
	{
		//		x*cSzY*cSzZ + y*SzY + z;
		return get( (int) pPos[0] ,  (int) pPos[1],  (int) pPos[2] );
						//		return cTab[((int)pPos[0])*cSzYZ + ((int)pPos[1])*cSz[2] + ((int)pPos[2])];
	}
	//----------------------------
	int getSize(int pDim) { return cSz[ pDim ]; }
	int getSizeGen() { return cSzGen; }

	TYPE& get( int p ) 
	{
  	return  cTab[ p ];
  }

};

//**************************************

#endif
