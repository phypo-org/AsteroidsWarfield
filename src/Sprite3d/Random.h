#ifndef h_Random_h
#define h_Random_h



#include <T3d/T3dType.h>
//************************************
/* TODO

class Random
{
static const int MAX_SIZE=10000;
	
protected:
	float cVect[ MAX_SIZE ];
	int cPos;
	
public:
	Random()
	{
		for( long i = 0; i < MAX_SIZE; i++ )
		{
			long i = static_cast<long>(f*10000.0);
			float j =rand()%i;
			j *= 0.0001;
			return j-f*0.5;
			cVect[ i ] = rand()
		}
	}
}
*/
//************************************
// renvoie un nombre entre -f et +f

float randf( float f);

// renvoie un nombre entre 0 et f
float randp( float f);


Float3 randFloat3( Float3 & src );
Float4 randFloat4( Float4 & src );
Double3 randDouble3( Double3 & src );
Double4 randDouble4( Double4 & src );
Float4& randf( Float4& src, Float4& dest);


//#############################

#ifndef ABS
#define ABS( A ) ( (A) > 0.0 ? (A) : (-A) )
#endif

#ifndef MAX
#define MAX(A,B) ((A)>(B)?(A):(B))
#endif

#ifndef MIN
#define MIN(A,B) ((A)<(B)?(A):(B))
#endif

#endif

