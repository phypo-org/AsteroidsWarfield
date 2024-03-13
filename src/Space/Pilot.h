#ifndef h_Pilot_h
#define h_Pilot_h

#include <istream>
#include <ostream>

#include <Sprite3d/Sprite3dPilot.h>
#include <Sprite3d/ObjPart.h>
#include <Sprite3d/AutoPtr.h>

#include <Sprite3d/Action.h>
#include <Sprite3d/SoundControler.h>


class WorldGame;

//**********************
class Pilot :  public  Sprite3dPilot, public Action, public SoundSourceOwner
{
  AutoPtr<O3dObjProps> caPropsShip;
  AutoPtr<O3dObjProps> caPropsShield;
  AutoPtr<O3dObjProps> caPropsShield2;

  AutoPtr<O3dObjProps> caPropsWarp;
  //	AutoPtr<O3dObjProps> caPropsPlasma;
  //	AutoPtr<O3dObjProps> caPropsIon;
  //	AutoPtr<O3dObjProps> caPropsRocket;

  AutoPtr<ObjVect>  caObjVect;

  AutoPtr<O3dObj>   caObjShip;
  AutoPtr<Sprite3d> caSpriteShip;
  AutoPtr<Sprite3d> caSpriteShield;
  AutoPtr<Sprite3d> caSpriteFire;
  AutoPtr<ObjVect>  caObjIonVect;

  AutoPtr<O3dObj>   caObjShield;
  AutoPtr<O3dObj>   caObjShield2;

  AutoPtr<ObjPart>  caObjFire;

  AutoPtr<T3dTexture> caTexCore;
  AutoPtr<ObjPart> caObjRecharge;

  //	AutoPtr<ActionProjectileExplosion> caActionProjectileExplosion;

  long  cErg;
  long  cRocket;
  long  cNbLife;
  long  cGold;

  long  cMaxErg;
  long  cMaxRocket;

  long  cLevelPhaser;
  long  cLevelLauncher;

  long  cLevelField;
  long  cLevelMotor;
  long  cLevelWarp;

  long  cScore;
  long  cNbUpgrade=0;
  long  cInvulnerable=0;


  GLboolean cWarpBegin;

  float cXDecalKamera;
  float cYDecalKamera;

public:
  Pilot();
  void write( std::ostream & pOs);
  bool read( std::istream & pIs );

protected:
  void firePhaser();
  void fireRocket();
  void fireMine();
  void transfertErgToField();
  void warp();

  virtual void mouseButton( int pButton, int pState, int pX, int pY );
  void key( unsigned char key, int x, int y );
  virtual GLboolean collision( Sprite3d &pMySprite, Sprite3d &pSprite, void *pParam );
  virtual GLboolean kill( Sprite3d &pMySprite, void*pParam );


  virtual void drawControl();
  virtual GLboolean animate();
  void scrollKamera();
  GLboolean collisionBonus( Sprite3d &pSprite, void *pParam);

public:
  static Pilot* ThePilot;

  static	void AddScore( long pVal ){
    if( ThePilot )
      ThePilot->cScore += pVal*((WorldControler::sDifficultyLevel*WorldControler::sDifficultyLevel)+1);
  }

  static PSoundId sSoundWarp;
  static PSoundId sSoundLaser;
  static PSoundId sSoundFireMissile;
  static PSoundId sSoundMotor;

  static PSoundId sSoundWarpFailed;
  static PSoundId sSoundCollision ;
  static PSoundId sSoundFinalExplosion;
  static PSoundId sSoundNextLife      ;
  static PSoundId sSoundBonus         ;


  static bool InitSound( );
};
//**********************

#endif
