#include "Random.h"
#include <stdlib.h>


//************************************
// renvoie un nombre entre -f et +f

//------------------------
static const float rifrand =1.0/RAND_MAX;

float randf( float f)
{
	 return static_cast<float>( (rand()*(f*2*rifrand))-f );
}
float randp( float f)
{
	 return static_cast<float>(rand()*(f*rifrand));
}


/*
float randf( float f)
{
	long i = static_cast<long>(f*2000.0);
	if( i==0 )
			return 0.0;
	float j = (rand()%i)*0.001;	
	return static_cast<float>(j-f);
}

// renvoie un nombre entre 0 et f
float randp( float f)
{
	long i = static_cast<long>(f*1000.0);
	if( i==0 )
			return 0.0;
	float j = (rand()%i)*0.001;	
	return static_cast<float>(j);
}
*/

Float3 randFloat3( Float3 & src )
{
	Float3 tmp( randf( src[ 0 ] ), randf( src[ 1 ] ), randf( src[ 2 ] ) );
	return tmp;
}
Float4 randFloat4( Float4 & src )
{
	Float4 tmp( randf( src[ 0 ] ), randf( src[ 1 ] ), randf( src[ 2 ]), randf( src[ 3 ] ) );
	return tmp;
}
Double3 randDouble3( Double3 & src )
{
	Double3 tmp( randf( src[ 0 ] ), randf( src[ 1 ] ), randf( src[ 2 ] ) );
	return tmp;
}
Double4 randDouble4( Double4 & src )
{
	Double4 tmp( randf( src[ 0 ] ), randf( src[ 1 ] ), randf( src[ 2 ]), randf( src[ 3 ] ) );
	return tmp;
}

inline Float4& randf( Float4& src, Float4& dest)
{
	for( int i = 0; i < 4; i++ )
		dest[ i ] = randf( src[ i ] );

	return dest;
}

