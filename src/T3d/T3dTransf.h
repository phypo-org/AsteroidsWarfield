
#ifndef _T3dTransf_h
#define _T3dTransf_h

#include <T3d/T3dType.h>
#include <T3d/T3dTab.h>

#include <string.h>


class T3dBox;


/*---------------------------------------------------------------------*/
/*    Enum ...                                                         */
/*---------------------------------------------------------------------*/

enum EnumTransfDouble3
{
	POS,
	ANGLE,
	SCALE,
	MAX_TRANSF_DOUBLE3
};
typedef T3dTab <Double3 , Double3&, EnumTransfDouble3, MAX_TRANSF_DOUBLE3>  TransfDouble3;

/*---------------------------------------------------------------------*/
/*    T3dTransf ...                                                   */
/*---------------------------------------------------------------------*/

class T3dTransf : public TransfDouble3
{
	
protected:


public:
	T3dTransf();

	virtual void exec();
	virtual void execBox( T3dBox & pBox );

	void raz();
	void centerTo( T3dBox& pBox);
	void scaleTo( T3dBox & pBox, Double3 & pSz );
	void scaleTo( T3dBox& pBox, double pSz );
};

#endif
