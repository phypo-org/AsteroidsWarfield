#include "ObjPrimPart.h"


//**********************************
ObjFire::ObjFire( int pNb, float pLife)
	:ObjPart(10)
{
	setForceTransparency( GL_TRUE );

	Double3 lPartPos(0.0, 0.0, 0.0);
	
	Double3 pos(13, 3, 13);
	ObjPartDouble3::set( PART_POSITION_RAND, pos );
	
	Double3 speed1(0, 10, 0);
	ObjPartDouble3::set( PART_SPEED, speed1 );
	
	Double3 speed2(6, 6, 6);
	ObjPartDouble3::set( PART_SPEED_RAND, speed2 );
	
	Double3 acc1( 0, 0, 0);
	ObjPartDouble3::set( PART_ACCELERATION, acc1 );
	
	Double3 acc2( 0.1, -0.3, -0.1);
	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );
	
	ObjPartFloat::set( PART_SIZE_RAND, 2);
	ObjPartFloat::set( PART_GROW, -4);
	ObjPartFloat::set( PART_GROW_RAND, -3 );
	
	ObjPartInt::set( PART_GEN_NUMBER, pNb );
	ObjPartInt::set( PART_RAND_NUMBER, pNb/4 );
	ObjPartInt::set( PART_DISPERSION_NUMBER, pNb/2 );


	Float4 color1( 0.9, 0.7, 0.0, 0.5 );
	Float4 color2( -0.05, -0.3, 0.0, -0.2);
	Float4 color3( 0.15, 0.2, 0.3, 0.2 );
	ObjPartFloat4::set( PART_COLOR, color1 );
	ObjPartFloat4::set( PART_COLOR_RAND, color3 );
	ObjPartFloat4::set( PART_COLOR_CHG, color2 );
	
	init( pLife, 15.0, ObjPartInt::get( PART_GEN_NUMBER) );
}
//**********************************
ObjSmoke::ObjSmoke(int pNb, float pLife)
	:ObjPart(10)
{
	setForceTransparency( GL_TRUE );

	Double3 lPartPos(0.0, 0.0, 0.0);
	
	//	  Float3 pos(15, 5, 15);
	Double3 pos(15, 15, 15);
	ObjPartDouble3::set( PART_POSITION_RAND, pos );
	
	Double3 speed1( 0, 15, 0);
	ObjPartDouble3::set( PART_SPEED, speed1 );
	
	Double3 speed2(3, 3, 3);
	ObjPartDouble3::set( PART_SPEED_RAND, speed2 );
	
	Double3 acc1( 0, 0.2, 0.1);
	ObjPartDouble3::set( PART_ACCELERATION, acc1 );
	
	Double3 acc2( 0, 0.2, 0.1);
	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );
	
	ObjPartFloat::set( PART_SIZE_RAND, 3);
	ObjPartFloat::set( PART_GROW, 0.1);
	ObjPartFloat::set( PART_GROW_RAND, 0.2 );
	
	ObjPartInt::set( PART_GEN_NUMBER, pNb );
	
	Float4 color1( 0.2, 0.2, 0.1, 0.4 );
	Float4 color2( 0.03, 0.03, 0.03, -0.06 );
	
	Float4 color3( 0.05, 0.05, 0.05, 0.1 );
	
	ObjPartFloat4::set( PART_COLOR, color1 );
	ObjPartFloat4::set( PART_COLOR_CHG, color2 );
	ObjPartFloat4::set( PART_COLOR_RAND, color3 );
	
	init( pLife, 15.0);
}

//**********************************
ObjExplosion::ObjExplosion( int pNb, float pLife)
	:ObjPart(10)
{
	setForceTransparency( GL_TRUE );

	Double3 pos( 3, 3, 3);
	ObjPartDouble3::set( PART_POSITION_RAND, pos );
	
	//	Double3 speed1(30, 30, 30);
	//	ObjPartDouble3::set( PART_SPEED, speed1 );
	
	Double3 speed2( 50, 50, 50);
	ObjPartDouble3::set( PART_SPEED_RAND, speed2 );
	 
	//	Double3 acc1( 10, 10, 10);
	//	ObjPartDouble3::set( PART_ACCELERATION, acc1 );
	
	Double3 acc2( 10, 10, 10);
	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );
	
	ObjPartFloat::set( PART_SIZE_RAND, 4);
	ObjPartFloat::set( PART_GROW, -10);

	
	ObjPartInt::set( PART_GEN_NUMBER, 0 );
	
	Float4 color1( 0.9, 0.7, 0.0, 0.4 );
	Float4 color2( 0.15, 0.2, 0.3, 0.2 );
	Float4 color3( -0.05, -0.3, 0.0, -0.6);
	
	
	ObjPartFloat4::set( PART_COLOR, color1 );
	ObjPartFloat4::set( PART_COLOR_RAND, color2 );

	ObjPartFloat4::set( PART_COLOR_CHG, color3 );
	
	init( pLife, 15.0, pNb, 0, GL_TRUE ); 
}

//**********************************
ObjDebris::ObjDebris( int pNb, float pLife)
	:ObjPart(10, new FacetPart() )	
{
	setForceTransparency( GL_TRUE );

	Double3 pos( 10, 10, 10 );
	ObjPartDouble3::set( PART_POSITION_RAND, pos );
	
	//	Double3 speed1(10, 10, 10);
	//	ObjPartDouble3::set( PART_SPEED, speed1 );
	
	Double3 speed2( 40, 40, 40);
	ObjPartDouble3::set( PART_SPEED_RAND, speed2 );
	
	//	Double3 acc1( 10, 10, 10);
	//	ObjPartDouble3::set( PART_ACCELERATION, acc1 );
	
	Double3 acc2( 5, 5, 5);
	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );

  
	Double3 lAngle( 360, 360, 360);
	ObjPartDouble3::set( PART_ANGLE_RAND, lAngle );

	Double3 lSpinRand( 300, 300, 300);
	ObjPartDouble3::set( PART_SPIN_RAND, lSpinRand );
	
	
	ObjPartFloat::set( PART_SIZE_RAND, 1); 

	//	ObjPartFloat::set( PART_GROW, -2);
	//	ObjPartFloat::set( PART_GROW_RAND, -3 );
	
	ObjPartInt::set( PART_GEN_NUMBER, pNb);
	
	Float4 color1( 0.5, 0.5, 0.5, 1.0 );
	Float4 color2( 0.4, 0.4, 0.4, 1.0 );
	
	 
	ObjPartFloat4::set( PART_COLOR, color1 );
	ObjPartFloat4::set( PART_COLOR_RAND, color2);
	
	init( pLife, 10.0, pNb, 0 );
}
//**********************************
ObjEtincelles::ObjEtincelles( Float4& pColor, int pNb, float pLife, float pSpeed )
	:ObjPart(pNb)
{
	setForceTransparency( GL_TRUE );

	Double3 pos( 1, 1, 1);
	ObjPartDouble3::set( PART_POSITION_RAND, pos );
		
	Double3 speed2( pSpeed, pSpeed, pSpeed);
	ObjPartDouble3::set( PART_SPEED_RAND, speed2 );
	 
	float lDiv = pLife*0.5;
	Double3 acc1( -pSpeed/lDiv,  -pSpeed/lDiv, -pSpeed/lDiv );
	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc1 );
	
//	Double3 acc2( 1, 1, 1);
//	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );
	
	ObjPartFloat::set( PART_SIZE_RAND, 1.5);
	ObjPartFloat::set( PART_GROW, -1);

	
	ObjPartInt::set( PART_GEN_NUMBER, pNb );
	
	Float4 color2( 0.1, 0.1, 0.1, 0.1 );
	Float4 color3( -0.1, -0.1, -0.1, -0.1);
	
	
	ObjPartFloat4::set( PART_COLOR, pColor );
	ObjPartFloat4::set( PART_COLOR_RAND, color2 );
	ObjPartFloat4::set( PART_COLOR_CHG, color3 );
	
	init( pLife, 3.0, pNb, 0 ); 
}
//**********************************
ObjEtincelles::ObjEtincelles( Float4& pColor, Double3 pSpeed, Double3 pDelta, int pNb, float pLife)
	:ObjPart(pNb)
{ 
	setForceTransparency( GL_TRUE );

	Double3 pos( 1, 1, 1);

	ObjPartDouble3::set( PART_POSITION_RAND, pos );
	
	ObjPartDouble3::set( PART_SPEED_RAND, pSpeed);	 
	ObjPartDouble3::set( PART_ACCELERATION, pDelta );
//	ObjPartDouble3::set( PART_ACCELERATION, acc1 );
	
//	Double3 acc2( 1, 1, 1);
//	ObjPartDouble3::set( PART_ACCELERATION_RAND, acc2 );
	
	ObjPartFloat::set( PART_SIZE_RAND, 1.5);
	ObjPartFloat::set( PART_GROW, -1); 


	ObjPartInt::set( PART_GEN_NUMBER, pNb );
	
	Float4 color2( 0.1, 0.2, 0.2, 0.2 );
	Float4 color3( -0.2, -0.2, -0.2, -0.1);
	
	
	ObjPartFloat4::set( PART_COLOR, pColor );
	ObjPartFloat4::set( PART_COLOR_RAND, color2 );

	ObjPartFloat4::set( PART_COLOR_CHG, color3 );
	
	init( pLife, 3.0, pNb, 0 ); 
}
//**********************************
