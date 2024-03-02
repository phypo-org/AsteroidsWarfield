#include "AnimatObj.h"

#include "Sprite3d/Sprite3d.h"

//*************************************************
AnimatObj::AnimatObj( Sprite3d* pSprite,	float pDelay,  O3dObj* pObj )
	:	cDelay( pDelay ),
	 cMySprite( pSprite ),
	 cLastTime(0),
	 cAnimateOn(GL_TRUE)
{
		if( pObj )		add( pObj );
}
//-----------------------------------------------
GLboolean
AnimatObj::animate()
{
	// animation des sous-objets
	ObjVect::animate();

	if( cAnimateOn == GL_FALSE || ( WorldControler::GetTime()-cLastTime) < cDelay )
	  return GL_FALSE;


	animateFinal();

	cLastTime = WorldControler::GetTime();

	return GL_TRUE;
}
//-----------------------------------------------
void
AnimatObj::set(  Sprite3d* pSprite, float pDelay,  O3dObj* pObj)
{
	cMySprite = pSprite;
	cDelay    = pDelay;

	if( pObj )
		add( pObj );
}

//*************************************************
