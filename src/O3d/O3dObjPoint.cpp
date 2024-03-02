
#include "O3dObjPoint.h"
#include "O3dObjProps.h"
#include "T3d/T3dPrimitiv.h"

#include "T3d/T3dColor.h"

#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------------------*/
/*    O3dObjPoint::O3dObjPoint ...                                     */
/*---------------------------------------------------------------------*/

O3dObjPoint::O3dObjPoint( long pSz )
:cData( pSz ),
cSelectetPoint(-1)
{
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::drawObj ...                                            */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	glDisable( GL_LIGHTING );
	pObjProps->setPointsProps();

	glBegin( GL_POINTS );
	cData.doGlVertex3d();
	glEnd();

	glEnable(GL_LIGHTING);
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::drawSelectedComponents ...                          */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::drawSelectedComponents( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	if( cSelectetPoint == -1 )
		return;

	glDisable( GL_LIGHTING );

	glPointSize( 12 );
	glColor4fv( Pink4 );

	glBegin( GL_POINTS );
	cData.doGlVertex3dPoint( cSelectetPoint );
	glEnd();

	glEnable( GL_LIGHTING );

	pObjProps->setPointsProps();
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::drawForSelectComponents ...                         */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::drawForSelectComponents(  O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	printf("O3dObjPoint::drawForSelectComponents\n" );

	pObjProps->setPointsProps();
	pVProps.beginSelect( cId, SELECT_POINT );
	for( long i = 0; i < cData.getNbPoint(); i++ )
		{
			pVProps.beginSelect( cId, i );

			glBegin( GL_POINTS );
			cData.doGlVertex3dPoint( i );
			glEnd();

			pVProps.endSelect( cId,  i );
		}
	pVProps.endSelect( cId, SELECT_POINT );	
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::drawId ...                                         */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::drawId( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	if( pVProps.ViewPropsBool::get( DRAW_ID ) == GL_FALSE )
		return;

	char tmp[33];
	sprintf( tmp,   "%ld", cId );

	Double3 & lData = cData.get( 0 );
	if( lData == NULL )
		return;

	glDisable(GL_LIGHTING);
	
	if( isSelect() )
	{
	   	T3dColor::Red();
		T3dPrimitiv::DrawX( lData[0], lData[1], lData[2], 10 );
	}
	else
       T3dColor::Yellow();

	glEnable(GL_LIGHTING);

	 pVProps.getDefaultFont()->displayAtPoint( lData, tmp );
}

/*---------------------------------------------------------------------*/
/*	   O3dObjPoint::setSelectComponent ...                              */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::setSelectComponent( O3dSelector* pSelect )
{
	if( pSelect && pSelect->getSelectObject() == cId
		&& pSelect->getNbComponent() )
		{
			if( pSelect->getComponent()[0] < cData.getNbPoint() )
				cSelectetPoint = pSelect->getComponent()[0];
		}
	else 
		cSelectetPoint = -1;
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::makeMinMaxBox ...                                  */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::makeMinMaxBox()
{
	cData.makeMinMaxBox( cBox );

	GLdouble lVal=0;
	for( int i = 0; i < 3; i++ )
	{
		GLdouble tmp  = cBox.getMax()[i] - cBox.getMin()[i];
		lVal += tmp *tmp;
	}
	cRadius = sqrt( lVal )* 0.5;
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::add ...                                                 */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::add( double pX, double pY, double pZ )
{
	cData.add( pX, pY, pZ );
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::add ...                                                 */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::add( Double3 &pPt )
{
	cData.add( pPt );
}
/*---------------------------------------------------------------------*/
/*    O3dObjPoint::add ...                                            */
/*---------------------------------------------------------------------*/

void
O3dObjPoint::add( T3dVect3D & pVect )
{
	cData.add( pVect );
}

