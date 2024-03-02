#ifndef _TVectType_h
#define _TVectType_h



#include <iostream>

/*---------------------------------------------------------------------*/
/*    class T3dTVect ...                                               */
/*---------------------------------------------------------------------*/


// Ne pas derive, ne pas mettre de fonction virtuelle
// Car utilse par T3dTab

template <typename TYPE, int  SIZE>
class TVectType
{
	TYPE cVect[ SIZE ];

public:
	TVectType()
	{
		memset( cVect, 0, sizeof( cVect ));
	}

	TVectType( TYPE A, TYPE B, TYPE C = 0, TYPE D = 0 );
	
	TVectType(TYPE pVect[ SIZE ])
	{
		memcpy( cVect, pVect, sizeof( cVect ));	
	}

	TVectType( const TVectType&  pVal )
	{
		*this = pVal;
	}

	TYPE* getVect() { return &cVect[0]; }

	const TVectType & operator = (const TVectType& pVal)
	{
		memcpy( cVect, pVal.cVect, sizeof( cVect ) );
		return *this;
	}


	const TVectType&  operator += (const  TVectType& pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[ i ] += pVal.cVect[ i ];
		return *this;
	}

	const TVectType&  operator -= (const  TVectType& pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] -= pVal.cVect[i];
		return *this;
	}

	const TVectType&  operator *= (const  TVectType& pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] *= pVal.cVect[i];
		return *this;
	}

	const TVectType&  operator /= (const  TVectType& pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] /= pVal.cVect[i];
		return *this;
	}

	const TVectType& operator += ( TYPE pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[ i ] += pVal;

		return *this;
	}

	const TVectType&  operator -= ( TYPE pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] -= pVal;
		return *this;
	}

	const TVectType&  operator *= (TYPE pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] *= pVal;
		return *this;
	}

	const TVectType&  operator /= (TYPE pVal)
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] /= pVal;
		return *this;
	}
	
	void inverse()
	{
		for( int i = 0; i < SIZE; i++ )
			cVect[i] = -cVect[i];
	}
	
	TYPE& operator [] (int pos)
	{
		return cVect[pos];
	}

	TYPE operator [] (int pos) const 
	{
		return cVect[pos];
	}


	operator TYPE *(  )
	{
		return cVect;
	}

	std::ostream& print( std::ostream& os)
	{
		for( int i = 0; i < SIZE; i++ )
			os << cVect[i] << ", ";

		return os;
	}

};


#endif
