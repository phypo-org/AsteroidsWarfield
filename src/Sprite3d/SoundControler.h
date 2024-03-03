#ifndef h_SoundControler_h
#define h_SoundControler_h

#include <T3d/T3dBox.h>
#include <stdint.h>

#include <string>
#include <vector>

typedef uint64_t PSoundId;
const   uint64_t  PBadSoundId =  0;

typedef int PSoundSourceId;
const   int  PBadSoundSourceId =  -1;




class SoundSourceOwner;
class SoundSource;
class SoundControler;

//*************************************************
class SoundSourceOwner{

  std::vector<SoundSource*> cMySources;

public:
  SoundSourceOwner();
  virtual ~SoundSourceOwner();
  void remove(SoundSource* pSrc);

  void playSoundSource( PSoundId pBuffer, int pPriority=0,float pGain=1.0f, float pPitch=1.0f, bool pLoop =false);

  void setSoundSourcesPosition( Double3 pPosition  );
  void setSoundSourcesSpeed(  Double3 pSpeed  );
  void setSoundSourcesPositionAndSpeed(  Double3 pPosition, Double3 pSpeed );
  friend class SoundControler;
};
//*************************************************
class SoundSource{

private:
  PSoundSourceId cId;
  PSoundId   cSourceId;

  SoundSourceOwner* cOwner;
  int cPriority;

  enum SourceState{
    FREE=0,
    PLAY=1,
    LOOP=2,
    SRC_ERR
  };

  SourceState cState;

  float cTime;

public:
  SoundSource( PSoundSourceId, PSoundId);
  virtual ~SoundSource();


  PSoundSourceId play( PSoundId pBuffer, float pGain=1.0f, float pPitch=1.0f, bool pLoop =false);

  void setPosition( Double3 pPosition  );
  void setSpeed(  Double3 pSpeed  );
  void setPositionAndSpeed(  Double3 pPosition, Double3 pSpeed );


  SoundSourceOwner* getOwner() { return cOwner; }
  void setOwner( SoundSourceOwner* pOwner ) { cOwner = pOwner; }


  friend class SoundSourceOwner;
  friend class SoundControler;
};

//*************************************************

class SoundControler{


public:
  SoundControler(  int pMaxSource, const char* pPath = NULL );
  virtual ~SoundControler(  );

  PSoundId loadSample ( const char* pName );
  double   getPos( PSoundId pSource );
  PSoundId getStatus( PSoundId pSource );

  SoundSource* playSample( PSoundId pBufferId, int pPriority=0, float pGain=1.0f, float pPitch=1.0f, bool pLoop =false);

  void freeSource( SoundSource* pSrc );

private:
  SoundSource* internalPlaySample( PSoundId pBufferId, int pPriority=0, float pGain=1.0f, float pPitch=1.0f, bool pLoop =false);
  SoundSource* internalPlaySampleOwner( SoundSourceOwner & pOwner, PSoundId pBufferId,  int pPriority=0, float pGain=1.0f, float pPitch=1.0f, bool pLoop =false);
  SoundSource* getFreeSource( int pPriority);


protected:
  std::string cPath;
  std::vector<PSoundId> cSamples;

  std::vector<SoundSource*> cSources;

public:

  static GLboolean sMute;
  static GLboolean sNoSound;
  static SoundControler* sTheSoundControler;

  static PSoundId LoadSampleConfig( const char* pKey );

  friend SoundSourceOwner;
};
//*************************************************

#define LOAD_SAMPLE(A) SoundControler::sTheSoundControler->loadSample(A);

#define PLAY_SAMPLE(A) SoundControler::sTheSoundControler->playSample(A);
#define PLAY_SAMPLE_PRIO(A, PRIO) SoundControler::sTheSoundControler->playSample(A, PRIO);
//#define LOOPSAMPLE(A) SoundControler::sTheSoundControler->loopSample(A);

#endif

