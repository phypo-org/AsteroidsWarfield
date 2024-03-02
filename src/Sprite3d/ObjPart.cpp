#include "ObjPart.h"
#include "World.h"
#include "WorldControler.h"
#include "T3d/T3dColor.h"

#include <stdlib.h>
#include <iostream>

#include "Utils3d.h"

#include "Random.h"

#include <FL/glu.h>

//------------------------------------------------
// Optimisation posible : definir un allocateur pour
// ObjPart (redefinir new/delete)
//
// Changer le tableau pour reutiliser les emplacements libre
// (faire un chainage des emplacements libres)




//*****************************************
ObjPart::Part::Part( )
	:cInLife(GL_FALSE),
	 cFree( NULL )
{
}
//--------------------------
GLboolean
ObjPart::Part::animate( )
{
	float lTime = WorldControler::GetTime()-cTime;
//	cout << WorldControler::GetTime() << "-" << cTime <<"=" << lTime
//			<< "   " << PartFloat::get(SIZE) << endl;

	if( (  PartFloat::get(PART_LIFETIME)!= -1.0 && lTime >= PartFloat::get(PART_LIFETIME))
		|| PartFloat::get(PART_SIZE)<1.0)
	{
		// Elle est morte Adele
		//		cInLife = GL_FALSE;

		return GL_FALSE; // On le dit au moteur
	}

	if( PartDouble3::getFlag( PART_SPEED ) )
	{
		PartDouble3::get( PART_POSITION ) += PartDouble3::get( PART_SPEED );
	}

	if( PartDouble3::getFlag( PART_ACCELERATION ) )
	{
		PartDouble3::get( PART_SPEED)+= PartDouble3::get(PART_ACCELERATION);
	}

	if( PartFloat::getFlag( PART_GROW ) )
	{
		PartFloat::set( PART_SIZE, ( PartFloat::get( PART_SIZE) +PartFloat::get( PART_GROW )));
	}

	if( PartFloat4::getFlag( PART_COLOR_CHG ) )
	{
		PartFloat4::get( PART_COLOR) +=  PartFloat4::get(PART_COLOR_CHG );
	}


	// ANGLES
	if( PartDouble3::getFlag( PART_SPIN ) )
	{
		PartDouble3::get( PART_ANGLE ) += PartDouble3::get( PART_SPIN );
	}

	if( PartDouble3::getFlag( PART_SPIN_ACCELERATION ) )
	{
		PartDouble3::get( PART_SPIN ) += PartDouble3::get( PART_SPIN_ACCELERATION );
	}


	return GL_TRUE;
}
//--------------------------
void ObjPart::Part::draw( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	if( cInLife == GL_FALSE )
		return;

	// On ne tient pas compte des angles/spin ...
	// Car ce sont des points

	glPointSize( PartFloat::get( PART_SIZE ) );
	if( PartFloat4::getFlag( PART_COLOR ) )
	{
		glColor4fv( PartFloat4::get( PART_COLOR ));
	}

	glBegin( GL_POINTS );
	glVertex3dv( PartDouble3::get( PART_POSITION ));
	glEnd();
}
//*****************************************

ObjPart::ObjPart( float cRadius, ObjPart::Part* pPrototype )
	:O3dObj( cRadius ),
	 cPrototype( pPrototype ),
	 cFree(NULL),
	 cNbLifePart(0),
     cMemNumber( 0 ),
	 cForceTransparency(GL_FALSE )
{
	if( cPrototype == NULL )
		cPrototype = new ObjPart::Part;
}
//--------------------------
ObjPart::~ObjPart()
{
	for( VPart::iterator iter = cVectPart.begin(); iter != cVectPart.end(); ++iter )
		{
			delete (*iter);
		}

	cVectPart.clear();

	delete cPrototype;
}
//--------------------------
inline ObjPart::Part *
ObjPart::allocPart()
{

	Part* lPart= cFree;
	if( lPart == NULL )
		{
			lPart = cPrototype->makeOnePart();
			cVectPart.push_back(lPart);
		}
	else
		{
			cFree = lPart->cFree;
			lPart->cFree = NULL;
		}

	lPart->cInLife = GL_TRUE;
	lPart->cTime = WorldControler::GetTime(); // date de naissance de la part

	cNbLifePart++;

	// 	cout << "allocPart :" << cNbLifePart			 << " Free:" << cFree << endl;


	return lPart;
}
//----------------------------
inline	void
ObjPart::freePart( ObjPart::Part *pPart)
{
	cNbLifePart--;

	pPart->cInLife = GL_FALSE;
	pPart->cFree = cFree;

	cFree = pPart;

	// 	cout << "freePart:" << pPart << endl;
}
//----------------------------------------------
void
ObjPart::init(  float pLifeTime, float pSize, int pNb, int pStartCycle, GLboolean pForceTransparency )
{
	ObjPartFloat::set( PART_SIZE, pSize );
	ObjPartFloat::set( PART_LIFETIME, pLifeTime );

	cMemNumber = ObjPartInt::get( PART_GEN_NUMBER );


	// Demarrage a chaud du moteur
	if( pNb )
	{
		if( ObjPartInt::getFlag( PART_RAND_NUMBER ))
			pNb += static_cast<int>(randf( ObjPartInt::get( PART_RAND_NUMBER ) ));

		for( int i = 0; i < pNb; i++ )
		{
			generateOnePart();
		}

		if( pStartCycle )
			{
				for( int p = 0; p < pStartCycle; p++)
					{
						animate();
					}
			}
	}

}
//----------------------------------------------
#define SET_VAL( TYPE, TYPE_RAND, VAR )  \
 Double3 VAR;  \
 if( ObjPartDouble3::getFlag( TYPE ) ) \
	{ \
		VAR = ObjPartDouble3::get( TYPE ); \
	} \
	if( ObjPartDouble3::getFlag( TYPE_RAND ) ) \
	{ \
		VAR += randDouble3( ObjPartDouble3::get( TYPE_RAND )); \
	} \
	lPart->PartDouble3::set( TYPE, VAR );

#define SET_VALDYN( TYPE, TYPE_RAND, VAR ) \
 Double3 VAR; \
 if( ObjPartDouble3::getFlag( TYPE ) ) \
	{ \
		VAR = ObjPartDouble3::get( TYPE ); \
	} \
	if( ObjPartDouble3::getFlag( TYPE_RAND ) ) \
	{ \
		VAR += randDouble3( ObjPartDouble3::get( TYPE_RAND )); \
	} \
	if(  ObjPartDouble3::getFlag( TYPE  ) || ObjPartDouble3::getFlag( TYPE_RAND )) \
	{ \
		VAR *=  WorldControler::GetRatio(); \
  	lPart->PartDouble3::set( TYPE, VAR ); \
	}


void
ObjPart::generateOnePart()
{
	ObjPart::Part* lPart = allocPart();

	Float4 lTmpFloat4;


	SET_VAL( PART_POSITION, PART_POSITION_RAND, lPos );
	SET_VALDYN( PART_SPEED, PART_SPEED_RAND, lSpeed );
	SET_VALDYN( PART_ACCELERATION, PART_ACCELERATION_RAND, lAcceleration);

	SET_VAL( PART_ANGLE, PART_ANGLE_RAND, lAngle );
	SET_VALDYN( PART_SPIN, PART_SPIN_RAND, lSpin );
	SET_VALDYN( PART_SPIN_ACCELERATION, PART_SPIN_ACCELERATION_RAND, lSpinAcceleration);

	Float4 lColor;
	if( ObjPartFloat4::getFlag( PART_COLOR ) )
	{
		lColor = ObjPartFloat4::get( PART_COLOR );
	}
	if( ObjPartFloat4::getFlag( PART_COLOR_RAND ) )
	{
		lColor += randFloat4( ObjPartFloat4::get( PART_COLOR_RAND ));
	}
	if( ObjPartFloat4::getFlag( PART_COLOR ) ||  ObjPartFloat4::getFlag( PART_COLOR_RAND ))
	{
		lPart->PartFloat4::set( PART_COLOR, lColor );
	}

	Float4 lColorChg;
	if( ObjPartFloat4::getFlag( PART_COLOR_CHG ) )
	{
		lColorChg = ObjPartFloat4::get( PART_COLOR_CHG );

		lColorChg *= WorldControler::GetRatio();

		lPart->PartFloat4::set( PART_COLOR_CHG, lColorChg );
	}

	float lLifeTime = ObjPartFloat::get( PART_LIFETIME );
	if( ObjPartFloat::getFlag( PART_LIFETIME_RAND ) )
	{
		lLifeTime += ObjPartFloat::get( PART_LIFETIME_RAND );
	}
	lPart->PartFloat::set( PART_LIFETIME, lLifeTime );


	float lSize = ObjPartFloat::get( PART_SIZE );
	if( ObjPartFloat::getFlag( PART_SIZE_RAND ) )
	{
		lSize += ObjPartFloat::get( PART_SIZE_RAND );
	}
	lPart->PartFloat::set( PART_SIZE, lSize );


	float lGrow =0.0;
	if( ObjPartFloat::getFlag(PART_GROW))
		lGrow = ObjPartFloat::get( PART_GROW );

	if( ObjPartFloat::getFlag( PART_GROW_RAND ) )
	{
		lGrow += ObjPartFloat::get( PART_GROW_RAND );
	}
	if( ObjPartFloat::getFlag( PART_GROW ) || ObjPartFloat::getFlag( PART_GROW_RAND ) )
	{
		lGrow *=  WorldControler::GetRatio();
		lPart->PartFloat::set( PART_GROW, lGrow );
	}




	if( lPart->initPart() == GL_FALSE )
		freePart( lPart );
}
//--------------------------
GLboolean ObjPart::animate()
{
	for( VPart::iterator iter = cVectPart.begin(); iter != cVectPart.end(); ++iter )
		{
			if( (*iter)->cInLife == GL_TRUE )
				{
					if( (*iter)->animate() == GL_FALSE)
						{
							// elle est morte, on la recycle
							freePart( (*iter) );
						}
				}
		}

	if( ObjPartInt::getFlag( PART_GEN_NUMBER ) || ObjPartInt::getFlag( PART_RAND_NUMBER )  )
		{
			int total = 0;

			int gen_var =  ObjPartInt::get( PART_GEN_VAR_NUMBER );
			if( gen_var != 0 )
				{
					int gen_number = ObjPartInt::get( PART_GEN_VAR_NUMBER ) + gen_var;
					ObjPartInt::set( PART_GEN_NUMBER, gen_number );
				}

			if(  ObjPartInt::getFlag( PART_DISPERSION_NUMBER ))
				{
					int gen_number = 	ObjPartInt::get( PART_GEN_NUMBER );
					gen_number += static_cast<int>(randf( ObjPartInt::get( PART_RAND_NUMBER ) ));

					if( gen_number > cMemNumber + ObjPartInt::get( PART_DISPERSION_NUMBER ))
						gen_number = cMemNumber + ObjPartInt::get( PART_DISPERSION_NUMBER );
					else
						if(  gen_number < cMemNumber - ObjPartInt::get( PART_DISPERSION_NUMBER ))
							gen_number = cMemNumber - ObjPartInt::get( PART_DISPERSION_NUMBER );

					// peristance de la deviance
					ObjPartInt::set( PART_GEN_NUMBER, gen_number );
					total = gen_number;
				}
			else
				{
					if( ObjPartInt::getFlag( PART_GEN_NUMBER ))
						total += ObjPartInt::get( PART_GEN_NUMBER );

					if( ObjPartInt::getFlag( PART_RAND_NUMBER ))
						total += static_cast<int>(randf( ObjPartInt::get( PART_RAND_NUMBER ) ));
				}

			// ATTENTION total PEUT DEVENIR EGAL A 0 SI LE NOMBRE DE PARTICULE EST TROP GRAND
			// PREVOIR UN AUTRE SYSTEME

			//		cout << "Part:" << cNbLifePart << "/" << cVectPart.size()
			//				 << " New:" << total << "->" << total*WorldControler::GetRatio() << endl;

			total = static_cast<int> (total*WorldControler::GetRatio());

			for( int i = 0; i < total; i++ )
				{
					generateOnePart();
				}

		}


	return GL_TRUE;
}
//--------------------------
void ObjPart::drawObj( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
}
//--------------------------
void ObjPart::draw( O3dViewProps& pVProps, O3dObjProps* pObjProps)
{
	glDisable( GL_LIGHTING );



	if( cForceTransparency )
		{
			glEnable( GL_BLEND );
			glDepthMask( GL_FALSE );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE );
		}


	for( VPart::iterator iter = cVectPart.begin(); iter != cVectPart.end(); ++iter )
	{
		if( cForceTransparency == GL_FALSE &&  (*iter)->PartFloat4::get( PART_COLOR )[3] < 0.9999 )
			{
				glEnable( GL_BLEND );
				glDepthMask( GL_FALSE );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );
			}


		(*iter)->draw(pVProps, pObjProps );


		if( cForceTransparency == GL_FALSE &&  (*iter)->PartFloat4::get( PART_COLOR )[3] < 0.9999 )
			{
				glDepthMask( GL_TRUE );
				glDisable( GL_BLEND );
				glEnable( GL_LIGHTING );
			}
	}

	if( cForceTransparency )
		{
			glDepthMask( GL_TRUE );
			glDisable( GL_BLEND );
			glEnable( GL_LIGHTING );
		}
}
//*****************************************
void
BaseObjPart::draw( O3dViewProps& pVProps, O3dObjProps* pObjProps )
{
	if( cInLife == GL_FALSE )
		return;


	T3dTransf lTransf;

	lTransf.set( POS,   PartDouble3::get( PART_POSITION ) );
	lTransf.set( ANGLE, PartDouble3::get( PART_ANGLE ) );

	double lSize = PartFloat::get( PART_SIZE );
  lTransf.get( SCALE )[0] =  lSize;
  lTransf.get( SCALE )[1] =  lSize;
  lTransf.get( SCALE )[2] =  lSize;

	{
		glPushMatrix();

		lTransf.exec();

		glColor4fv( PartFloat4::get( PART_COLOR ));

		draw();

		glPopMatrix();
	}
}
//*****************************************
Float3 sPtTri1( -0.5, -0.5, -0.5 );
Float3 sPtTri2( -0.5,  0.5, -0.5 );
Float3 sPtTri3(  0.5,  0.5,  0.5);
//Float3 sNormTri(0,0,0);
Float3 sNormTri(-0.707107, -0, 0.707107);

//---------------------------
void FacetPart::draw( )
{
	glBegin( GL_POLYGON );

	//	Utils3d::Normal( sPtTri1, sPtTri2, sPtTri3, sNormTri );
	/*	cout << "lNorm:"
			 <<  sNormTri[0] << ", "
			 <<  sNormTri[1] << ", "
			 <<  sNormTri[2] << endl;
	*/

	glNormal3fv( sNormTri );
	glVertex3fv( sPtTri1 );

	//	glNormal3fv( sNormTri );
	glVertex3fv( sPtTri2 );

	//	glNormal3fv( sNormTri );
	glVertex3fv( sPtTri3 );

	glEnd();
}
//*****************************************
void
SpherePart::draw()
{
	static GLUquadricObj *quadObj = NULL;
	if( quadObj == NULL )
		quadObj = gluNewQuadric();

//	double lSize = PartFloat::get( PART_SIZE );

	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluSphere(quadObj, 1, cNb, cNb);
}

//*****************************************
