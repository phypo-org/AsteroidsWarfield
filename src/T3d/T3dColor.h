

#ifndef _T3dColor_h
#define _T3dColor_h


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/


#include <T3d/T3dType.h>

/*---------------------------------------------------------------------*/
/*    Class T3dColor ...                                               */
/*---------------------------------------------------------------------*/
class T3dColor
{

public:
	static void Red()	      { glColor3f(1.0,0.0,0.0); 	}
	static void Green()    	{ glColor3f(0.0,1.0,0.0); 	}
	static void Blue()      {glColor3f( 0.0, 0.0, 1.0 ); }
	static void LightBlue() {glColor3f( 0.5, 0.5, 1.0 ); }

	static void Yellow()	  { glColor3f(1.0,1.0,0.0); 	}
	static void Pink()	    { glColor3f(1.0,0.0,1.0); 	}

	static void White()	    { glColor3f(1.0,1.0,1.0); 	}
	static void Black()     {glColor3f( 0.0, 0.0, 0.0 ); }
   
	static void Grey()	    { glColor3f(0.5,0.5,0.5); 	}
	static void LightGrey()	{ glColor3f(0.7f,0.7f,0.7f); 	}
	static void DarkGrey()  {glColor3f( 0.3f, 0.3f, 0.3f ); }

};

extern Float3 Red3;
extern Float3 Yellow3;
extern Float3 Green3;
extern Float3 Blue3;
extern Float3 Grey3;
extern Float3 White3;

extern Float4 Red4;
extern Float4 Yellow4;
extern Float4 Green4;
extern Float4 Blue4;
extern Float4 Pink4;
extern Float4 Cyan4;
extern Float4 Grey4;
extern Float4 White4;
extern Float4 Black4;

#endif
 
