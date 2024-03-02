#ifndef h_TVectPtr_h
#define h_TVectPtr_h


#include <stdlib.h>
#include <T3d/T3dType.h>

//****************************
template <typename OBJ>
class TVectPtr
{
public:
	typedef OBJ *iterator;

protected:
	OBJ *cVect;
	long cCount;
	long cSize;

public:
	TVectPtr( long pSz = 0 )
	:cVect( NULL ), cCount(0), cSize(pSz)
	{
		if( pSz )
			resize();
	}
	virtual~TVectPtr()
	{
		::free( cVect);
		cVect =  NULL;
		cCount = cSize=0;
	}

	void push_back( OBJ pObj)
	{
		if( cCount == cSize )
		{
			resize();
		}
		cVect[ cCount++ ] = pObj;
	}

	GLboolean erase( iterator i )
	{
		if( i < end() && i != NULL )
		{
			cCount--;
			*i = cVect[ cCount ];
			return GL_TRUE;
		}
		return GL_FALSE;
	}
	GLboolean erase( long cPos )
	{
		iterator i = cVect + cPos;
		return remove( i );
	}

	long size()  { return cCount; 	}

	OBJ operator[](long pPos)
	{
		return cVect[pPos];
	}
	
	iterator begin()	{ return cVect;   }
	iterator end() { return cVect+cCount; }

	void clear()
	{
		cCount = 0;
	}

	void destroy()
	{
		for( iterator i = begin(); i < end(); i++ )
			delete (*iter);
		clear();		
	}

	
protected:
	void resize()
	{
		if( cSize == 0 )
				cSize = 0x0f;

		if( cVect == NULL )
		{
			cVect = (OBJ*)::malloc( cSize*sizeof(OBJ) );
		}
		else
		{
			cSize <<= 1;
			cVect = (OBJ*)::realloc( cVect, cSize * sizeof(OBJ) );
		}
	}
	
};
//****************************

#endif
