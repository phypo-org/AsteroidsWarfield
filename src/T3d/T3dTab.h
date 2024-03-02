
#ifndef _T3dTab_h
#define _T3dTab_h

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/


#include <T3d/T3dType.h>

/*---------------------------------------------------------------------*/
/*    class T3dTab ...                                                 */
/*  pour faire des tableaux de Float3 float int ...                    */
/*---------------------------------------------------------------------*/

template <typename OBJ, typename PARAM, typename INDEX, int SIZE>
class T3dTab
{
	GLboolean cFlags[SIZE];
	OBJ cVect[ SIZE ];

public:
	T3dTab()
	{
		raz();
	}

	T3dTab( const T3dTab & pSrc )
	{
		*this = pSrc;
	}

	T3dTab & operator = (const T3dTab & pSrc)
	{
          ::memcpy( (void*)cFlags, pSrc.cFlags, sizeof( cFlags ));
          ::memcpy( (void*)cVect, pSrc.cVect, sizeof( cVect ));
		
		return *this;
	}

	void setFrom( const T3dTab &pSrc )
	{
		*this = pSrc;
	}

	void raz()
	{
          ::memset( (void*)cFlags, 0, sizeof(cFlags));
          ::memset( (void*)cVect, 0, sizeof( cVect ) );
	}

	void set(  INDEX pIdx,   PARAM  pObj)
	{
		cFlags[pIdx]=GL_TRUE;
		memcpy( (void*)&cVect[pIdx], &pObj, sizeof(OBJ));
	}

	PARAM get( INDEX pIdx )
	{
		return cVect[pIdx];
	}

	OBJ* getPtr( INDEX pIdx )
	{
		return &cVect[pIdx];
	}

	GLboolean getFlag( INDEX pIdx )
	{
		return cFlags[pIdx];
	}

	void add( INDEX pIdx, OBJ &pObj )
	{
		cVect[pIdx] += pObj;
	}
	
};



#endif
