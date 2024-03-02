#ifndef _O3dObjProps_h_
#define _O3dObjProps_h_

/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dVect3D.h>
#include <T3d/T3dTab.h>
#include <T3d/T3dTexture.h>



/*---------------------------------------------------------------------*/
/*    Enum ...                                                         */
/*---------------------------------------------------------------------*/

enum EnumObjPropsInt
	{
		POINT_SIZE,
		LINE_WIDTH,
		MAX_OBJPROPS_INT
	};


enum EnumObjPropsFloat4
	{
		MATERIAL,
		EMISSION,
		COLOR_POINT,
		COLOR_LINE,
		COLOR_SKELETON,
		MAX_OBJPROPS_FLOAT4
	};
enum EnumObjPropsBool
	{
		DRAW_OBJ_SKELETON,
		DRAW_OBJ_SOLID,
		MAX_OBJPROPS_BOOL
	};


typedef T3dTab <int, int, EnumObjPropsInt, MAX_OBJPROPS_INT> ObjPropsInt;
typedef T3dTab <Float4, Float4 & , EnumObjPropsFloat4, MAX_OBJPROPS_FLOAT4>ObjPropsFloat4;
typedef T3dTab <GLboolean, GLboolean, EnumObjPropsBool, MAX_OBJPROPS_BOOL> ObjPropsBool;

/*---------------------------------------------------------------------*/
/*    O3dObjProps ...                                                 */
/*---------------------------------------------------------------------*/
class O3dFont;

class O3dObjProps : public ObjPropsFloat4, public ObjPropsInt, public ObjPropsBool
{
protected:	
	T3dTexture *cTex;
	GLboolean  cToClose;

public:
	O3dObjProps();
	virtual ~O3dObjProps() {;}
	
	virtual void setPointsProps();
	virtual void setLinesProps();
	virtual void setSurfProps();

	void open();
	void close();

	void setTexture( T3dTexture *pTex ) {cTex = pTex; }
	T3dTexture *getTexture()	{ return cTex; 	}

};



#endif
