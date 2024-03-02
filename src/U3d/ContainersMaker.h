#ifndef H__CONTAINERS_MAKER__H
#define H__CONTAINERS_MAKER__H

#include <O3d/O3dObjProps.h>
#include <O3d/O3dObj.h>
#include <O3d/O3dObjPrim.h>
#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>


enum EnumContainers{ CONTAINER_ERG, CONTAINER_ROCKET, CONTAINER_LIFE, CONTAINER_MAX};

//************************************************************
class ContainersMaker : public Action
{
	Float4    cColorErg;
	Float4		cColorRocket;
	Float4		cColorLife;

	O3dObjProps cPropsErg;
	O3dObjProps cPropsRocket;
	O3dObjProps cPropsLife;
	O3dObjProps cPropsSkeleton;


public:		
	AutoPtr<O3dObj> cObjContainer;

public:
	ContainersMaker();	

	ObjVect*  makeContainer( float pSz );
	Sprite3d* makeSpriteContainer( int cObjType, EnumContainers pType, unsigned int pMaskObj, unsigned int pMakInteract);
};

extern ContainersMaker* TheContainersMaker;

#define	CONTAINER_TYPE    SPRITE_USER1
#define	CONTAINER_VALUE   SPRITE_USER2

//************************************************************

#endif
