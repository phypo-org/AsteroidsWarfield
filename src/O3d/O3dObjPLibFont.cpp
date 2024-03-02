#include "O3dObjPLibFont.h"
#include "O3dObjProps.h"

#include <iostream>
#include "T3d/T3dColor.h"
#include <stdlib.h>


//****************************************
void 
O3dObjPLibFont::drawObj( O3dViewProps & pVProps, O3dObjProps *pObjProps )
{
	glDisable(GL_LIGHTING);
	//	gl_font( cFont, cSize );
	//	gl_draw( cStr.data(),   0.0f,  0.0f,  0.0f); 
	T3dFont::DefaultFont->displayAt( 0, 0, 0, cStr.data());
	glEnable(GL_LIGHTING);
}



//****************************************
