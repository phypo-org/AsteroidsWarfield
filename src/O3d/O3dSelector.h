
#ifndef _O3dSelector_h_
#define _O3dSelector_h_


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*-------------------i--------------------------------------------------*/
#include <T3d/T3dType.h>

class O3dViewProps;
class O3dKamera;


	static const GLuint SELECT_NONE=(GLuint)-1;
	static const GLuint SELECT_OBJECT=(GLuint)-2;
	static const GLuint SELECT_POINT   = (GLuint)-3;
	static const GLuint SELECT_SEGMENT = (GLuint)-4;
	static const GLuint SELECT_PATCH   = (GLuint)-5;
	

/*---------------------------------------------------------------------*/
/*    O3dSelector  ...                                                 */
/*---------------------------------------------------------------------*/

class O3dSelector
{
protected:
	enum{ cSzBuf = 256};
	GLuint cSelectBuf[cSzBuf];
	GLint  cNbSelect;
	GLuint cFind;

	O3dViewProps * cViewProps;
	O3dKamera    * cKamera;

	GLuint cObjId[ 32 ];
	int    cNbObj;

	GLuint cTypeComponent;
	GLuint cComponent[ 32 ];
	int    cNbComponent;

	int  cDepth;
	// For restrict the selection into the components of one object
	long cRestrictedObjectId;

public:
	O3dSelector( );

	void raz();
	void begin( O3dViewProps* pViewProps, O3dKamera* pKamera, int pX, int pY, float pWidht, float pHeight );
	void finish();
	long getSelectObject();
	int  getNbComponent()	{ return cNbComponent; 	}
	GLuint *getComponent() {return cComponent; }

	void pushSelect(  long pObjId, GLuint pFlag =SELECT_NONE);
	void popSelect(long pObjId, GLuint pFlag =SELECT_NONE);

	void setRestrictedObject( long pId=-1  ){ cRestrictedObjectId = pId; }

	void print();
	void print2();
};

#endif
