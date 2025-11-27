#include "T3d/T3dColor.h"

#include "ObjVect.h"

#include <stdio.h>


//**************************************
void ObjVect::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
}
//------------------------------------------
void ObjVect::draw( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	O3dObjProps* lCurProps = pObjProps;

	if( getObjProps() )
		lCurProps = getObjProps();

	for( VO3dObj::iterator iter = begin(); iter != end(); ++iter )
	{
		glPushMatrix();
		(*iter)->pushTransf();

		if( (*iter)->getObjProps() )
		{
			(*iter)->getObjProps()->open();
			(*iter)->draw( pVProps, (*iter)->getObjProps() );
			(*iter)->getObjProps()->close();
		}
		else
		{
			lCurProps->open();
			(*iter)->draw( pVProps, lCurProps );
			lCurProps->close();
		}

		glPopMatrix();
	}
}
//-----------------------------------------------
GLboolean
ObjVect::animate()
{
	for( VO3dObj::iterator iter = begin(); iter != end(); ++iter )
	{
		(*iter)->animate();
	}
	return GL_TRUE;
}
//-----------------------------------------------
void
ObjVect::deleteAll()
{
	for( VO3dObj::iterator iter = begin(); iter != end(); ++iter )
	{
		(*iter)->deleteAll();
		delete (*iter);		
	}

	VO3dObj::clear();
}

// 2025-11-19 Antigravity: Fix memory leak by deleting contained objects
ObjVect::~ObjVect()
{
	deleteAll();
}
//-----------------------------------------------
void
ObjVect::drawId( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	char tmp[33];
	sprintf( tmp, "%ld", cId );

	T3dColor::Red();
	pVProps.getDefaultFont()->displayAtPoint( cBox.getMin(), tmp ); 
}
//-----------------------------------------
void
ObjVect::makeMinMaxBox()
{

	for( VO3dObj::iterator iter = begin(); iter != end(); ++iter )
	{
		(*iter)->makeMinMaxBox();

		for( int i = 0; i < 3; i++ )
		{
			if( cBox.getMin()[ i ]>(*iter)->getMinMaxBox().getMin()[ i ])
				cBox.getMin()[ i ] = (*iter)->getMinMaxBox().getMin()[ i ];

			if( cBox.getMax()[ i ]<(*iter)->getMinMaxBox().getMax()[ i ])
				cBox.getMax()[ i ] = (*iter)->getMinMaxBox().getMax()[ i ];
		}
	}
}

//**************************************
