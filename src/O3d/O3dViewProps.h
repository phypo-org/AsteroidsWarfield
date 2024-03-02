
#ifndef _O3dViewProps_h_
#define _O3dViewProps_h_


/*---------------------------------------------------------------------*/
/*    include ...                                                      */
/*---------------------------------------------------------------------*/

#include <T3d/T3dFont.h>
#include <T3d/T3dTab.h>
#include <O3d/O3dSelector.h>

class O3dKamera;

enum EnumViewPropsBool
{
	DRAW_ID,
	DRAW_POINT,
	DRAW_LINE,
	DRAW_LINE_POLE,
	DRAW_SKELETON,

	DRAW_SELECTED_COMPONENT,

	DRAW_SURF,
	DRAW_SURF_POLE,

	MODE_INTERACTIF,
	MODE_ECO,

	NORMALIZE_COLORZ,
	
	VIEW_REMAKE_LIST,
	VIEW_REDRAW,

	DRAW_CUBE,
	MAX_VIEWPROPS_BOOL
};

enum EnumViewPropsInt
{
	MAILLE,
	UMAILLE,
	VMAILLE,
	MAX_VIEWPROPS_INT
};

typedef T3dTab < GLboolean, GLboolean, EnumViewPropsBool , MAX_VIEWPROPS_BOOL> ViewPropsBool;
typedef T3dTab < int, int, EnumViewPropsInt , MAX_VIEWPROPS_INT> ViewPropsInt;

/*---------------------------------------------------------------------*/
/*    class O3dViewProps ...                                           */
/*                                                                     */
/* Il s agit de regrouper dans cette classe tout ce qui se rapporte    */
/* a l affichage et a la selection et qui n est pas liees au O3dObj    */
/* eux memes                                                           */
/*                                                                     */
/*---------------------------------------------------------------------*/


class O3dViewProps : public ViewPropsInt, public ViewPropsBool
{
public:

	T3dFont *cDefaultFont;
	O3dKamera & cKamera;

	

	O3dSelector* cSelector;
	
	public:
	O3dViewProps( O3dKamera& pKamera )
	:cDefaultFont( NULL ),
	 cKamera( pKamera ),
	 cSelector(NULL)
	{
		ViewPropsBool::set( DRAW_ID, GL_FALSE);
		ViewPropsBool::set( DRAW_SURF, GL_TRUE);
		ViewPropsBool::set( NORMALIZE_COLORZ, GL_FALSE);
		ViewPropsBool::set( DRAW_LINE_POLE, GL_TRUE);

		ViewPropsBool::set( VIEW_REDRAW, GL_TRUE );
		ViewPropsBool::set( DRAW_CUBE, GL_TRUE);
		ViewPropsBool::set( DRAW_SELECTED_COMPONENT, GL_TRUE);

		ViewPropsInt::set( MAILLE, 8 );
		ViewPropsInt::set( UMAILLE, 1 );
		ViewPropsInt::set( VMAILLE, 1 );	
	}

	T3dFont *getDefaultFont() {return cDefaultFont; }
	O3dKamera & getKamera()	{ return cKamera; 	}
	void setDefaultFont( T3dFont *pFont ) {cDefaultFont = pFont; }

	void setSelector( O3dSelector *pSel = NULL )	{	cSelector = pSel;	}
	O3dSelector *getSelector() {return cSelector; }


	void beginSelect( long pObjId, GLuint pFlag = SELECT_NONE)
	{
		if( cSelector == NULL )
			return;

		cSelector->pushSelect( pObjId, pFlag );
	}

	void endSelect( long pObjId, GLuint pFlag = SELECT_NONE)
	{
		if( cSelector == NULL )
			return;

		cSelector->popSelect( pObjId, pFlag);
	}
};


#endif
