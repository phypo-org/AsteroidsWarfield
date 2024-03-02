#ifndef H__ANIMATOBJ__H
#define H__ANIMATOBJ__H

#include <Sprite3d/ObjVect.h>

class Sprite3d;

//*************************************************
class AnimatObj: public ObjVect{

protected:
	float       cDelay;
	Sprite3d*   cMySprite;
	float       cLastTime;
	GLboolean   cAnimateOn;

public:
	AnimatObj( Sprite3d* pSprite=NULL,	float pDelay=1000000000,  O3dObj* pObj=NULL  );
	virtual GLboolean animate( );	
	void set(  Sprite3d* pSprite, 	float pDelay,  O3dObj* pObj=NULL );
	virtual void setAnimateOn(GLboolean pAnimat=GL_TRUE) { cAnimateOn = pAnimat; }

	virtual void animateFinal() = 0;
};

//*************************************************

#endif
