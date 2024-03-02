#ifndef h_Sprite3dPilot_h
#define h_Sprite3dPilot_h


#include <Sprite3d/Sprite3dObj.h>



//**************************************

class Sprite3dPilot : public Sprite3dObj
{
	int cMemX, cMemY;

protected:
	float cManX;
	float cManY;

public:

	Sprite3dPilot( O3dObj *pObj );
	virtual ~Sprite3dPilot(){;}

//	virtual void drawObj(O3dObjProps* pProps);
	virtual GLboolean animate();
	virtual GLboolean leaveWorld();
	virtual GLboolean collision( Sprite3d& pSprite );

	virtual void mouseMove( int pX, int pY );
	virtual void mouseButton( int pButton, int pState, int pX, int pY );
	virtual void key( unsigned char key, int x, int y );
	virtual void specialKey( int key, int x, int y );
	virtual void keyUp( unsigned char key, int x, int y );

	virtual void drawControl() {;}
};

//**************************************

#endif

