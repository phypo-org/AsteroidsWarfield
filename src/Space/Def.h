#ifndef h_Def_h
#define h_Def_h

// il faudrait etre plus descriminant dans les masques
/*
static const unsigned int InteractAllied       =0x03+0x4; // + bonus

static const unsigned int InteractAlliedWeapon  =0x403; // enemy + obstacle

static const unsigned int InteractAlliedWeaponMask =0x330; // enemy + obstacle


static const unsigned int InteractEnemy        =0x30;
static const unsigned int InteractEnemyWeapon  =0x303;     // Allied + obstacle


static const unsigned int InteractObstacle     =0x300;
static const unsigned int InteractObstacleWeapon     =0x33; // interagit contre tout sauf bonus

static const unsigned int InteractBonus    =0x4;
*/

static const unsigned int InteractShipAllied  =  0x001;  //allied
static const unsigned int InteractShipEnemy   =  0x010;
static const unsigned int InteractObstacle    =  0x100;


static const unsigned int InteractBonus = 0x004;


static const unsigned int InteractShipAlliedIn  = InteractShipAllied + InteractBonus ;
static const unsigned int InteractShipAlliedOut = InteractShipEnemy  ;

static const unsigned int InteractShipEnemyIn   = InteractShipEnemy ;
static const unsigned int InteractShipEnemyOut  = InteractShipAllied ;


static const unsigned int InteractObstacleIn    = InteractObstacle;
static const unsigned int InteractObstacleOut   = InteractShipAllied+InteractShipEnemy;


static const unsigned int InteractWeaponAlliedIn   = InteractShipAllied ;
static const unsigned int InteractWeaponAlliedOut  = InteractShipEnemyIn + InteractObstacle;

static const unsigned int InteractWeaponEnemyIn    = InteractShipEnemy   ;
static const unsigned int InteractWeaponEnemyOut   = InteractShipAllied  + InteractObstacle;



enum {
	NO_TYPE=0,
	CONTAINER,
	FRIEND_SHIP,
	ALIEN_SHIP,
	ASTEROIDE
};

enum{ FRIEND, ALIEN };



#endif
