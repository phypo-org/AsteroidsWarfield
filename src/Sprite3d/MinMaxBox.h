#ifndef h_MinMaxBox_h
#define h_MinMaxBox_h


#include <Type.h>

//**************************************

class MinMaxBox
{
	Float3 cMin;
	Float3 cMax;

public:
	MinMaxBox()
	{
		for( int i = 0; i < 3; i++ )
		{
			cMin[ i ] = 1e10;
			cMax[ i ] = -1e10;
		}
	}

	MinMaxBox( Float3& pMin, Float3& pMax)
	{
		CPY_FLOAT3( &cMin, &pMin);
		CPY_FLOAT3( &cMax, pMax);
	}

	Float3 &getMin()
	{
		return cMin;
	}

	Float3  &getMax()
	{
		return cMax;
	}

	Bool isInto( Float3 & pPt )
	{
		for( int i = 0; i < 3; i++ )
		{
			if( pPt[ i ] < cMin[ i ] )
				return FALSE;
			if( pPt[ i ]>cMax[ i ] )
				return FALSE;
		}
		return TRUE;
	}

	void getCenter( Float3 & pD3 )
	{
		for( int i = 0; i < 3; i++ )
			pD3[i] = (cMin[i] + cMax[i]) / 2.0;

	}
};
//**************************************


#endif

