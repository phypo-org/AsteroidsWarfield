
#ifndef _O3dKamera_h
#define _O3dKamera_h

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dType.h>
#include <T3d/T3dTab.h>
#include <T3d/T3dTransf.h>
/* ?????
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
*/
/*---------------------------------------------------------------------*/
/*    enum ...                                                         */
/*---------------------------------------------------------------------*/

enum EnumKameraDouble3
{
	POS_VIEW,
	UP_VECTOR,
	STRAFE,

	MKAMERA_DOUBLE3
};
enum EnumKameraDouble
{
	PERS_FOVY,
	PERS_ASPECT,
	PERS_ZNEAR,
	PERS_ZFAR,

	MKAMERA_DOUBLE
};
typedef T3dTab <Double3 , Double3&, EnumKameraDouble3, MKAMERA_DOUBLE3>   KameraDouble3;
typedef T3dTab <GLdouble , GLdouble, EnumKameraDouble, MKAMERA_DOUBLE>   KameraDouble;

/*---------------------------------------------------------------------*/
/*    class O3dKamera ...                                              */
/*---------------------------------------------------------------------*/

class O3dKamera:public T3dTransf, public KameraDouble3, public KameraDouble
{


public:
	GLboolean cPersFlag;

public:
		O3dKamera();

		void reset();

		void exec();
//    void look();
	GLboolean getUnProject( const Double3 & pPos, Double3 &pPtResult );
	GLboolean getProject( const Double3& pPos, Double3 & pPtResult );
	void setPick( int pX, int pY, float pWidht, float pHeight );
        void setAspectRatio( int pWidth, int pHeight);
	void setFrom( const O3dKamera & pKam )
	{
		T3dTransf::setFrom( pKam );
		KameraDouble3::setFrom( pKam );
		KameraDouble::setFrom( pKam );
	}
};




#endif
