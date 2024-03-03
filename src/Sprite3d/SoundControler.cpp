#include "SoundControler.h"


#ifdef USE_SOUND
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#endif


#include <vector>

#include "World.h"
#include "WorldControler.h"


GLboolean SoundControler::sNoSound = GL_FALSE;
GLboolean SoundControler::sMute    = GL_FALSE;

SoundControler* SoundControler::sTheSoundControler = NULL;

#ifdef USE_SOUND

ALCdevice*  sSoundDevice = NULL;
ALCcontext* sSoundContext = NULL;

#endif
  
//*************************************************

SoundControler::SoundControler(  int pMaxSource,  const char* pPath  )
{
  if( pPath != NULL )
    cPath = pPath;

  sTheSoundControler = this;
  
  std::cout << "--- SoundControler::SoundControler path: " << pPath  << std::endl;


#ifdef USE_SOUND

  sSoundDevice = alcOpenDevice(NULL);
  if (!sSoundDevice)
    {
      sNoSound = GL_TRUE;
      std::cerr<< "*** SoundControler::SoundControler alcOpenDevice failed"  << std::endl;
      return ;
    }


  // Création du contexte
  sSoundContext = alcCreateContext( sSoundDevice, NULL );
  if (!sSoundContext)
    {
      std::cerr << "*** SoundControler::SoundControler  alcCreateContext failed"  << std::endl;
      sNoSound = GL_TRUE;
      return ;
    }

  // Activation du contexte
  if (!alcMakeContextCurrent(sSoundContext))
    {
      std::cerr << "*** SoundControler::SoundControler  alcMakeContextCurrent failed"  << std::endl;
      sNoSound = GL_TRUE;
      return;
    }


  std::cout << "--- SoundControler::SoundControler OK for " << pPath  << std::endl;


  // Reservation des sources
  for( int i=0; i< pMaxSource; ++i )
    {
      ALuint lSource;

      // IL FAUDRAIT UN CONTROL D'ERREUR
      alGenSources(1, &lSource);

      cSources.push_back( new SoundSource( i, lSource ) );

    }
#else

  std::cerr << "Sound not implemented !"  << std::endl;


#endif

}
//------------------------------------------------

SoundControler::~SoundControler(  )
{

#ifdef USE_SOUND
  // ALCcontext* Context = alcGetCurrentContext();
  // ALCdevice*  Device  = alcGetContextsDevice(Context);


  // Destruction des buffers
  for( std::vector<PSoundId>::iterator p=cSamples.begin(); p!=cSamples.end(); ++p)
    {
      ALuint lBuffer =  *p;

      alDeleteBuffers(1, &lBuffer);

    }

  // Destruction des sources
  for( std::vector<SoundSource*>::iterator p=cSources.begin(); p!=cSources.end(); ++p)
    {
      delete *p;
    }


  // Destruction du contexte
  if( sSoundContext!=NULL)
    {
      // Désactivation du contexte
      alcMakeContextCurrent(NULL);
      alcDestroyContext(sSoundContext);
    }

  // Fermeture du device
  if( sSoundDevice != NULL )
    alcCloseDevice(sSoundDevice);


  sMute =  sNoSound = true;
#endif
}
//------------------------------------------------
PSoundId
SoundControler::LoadSampleConfig( const char* pKey )
{

#ifdef USE_SOUND
  std::cout << "SoundControler::LoadSampleConfig " << pKey << std::endl;


  std::map<std::string, std::string>::iterator lIterator = World::sConfig.find(pKey );



  if( lIterator == World::sConfig.end() )
    return PBadSoundId;

  std::cout << "SoundControler::LoadSampleConfig " << pKey << " LOADING  >>>" << lIterator->second << std::endl;


  std::string lName = lIterator->second;

  if( lName.size() > 0 )
    {
      return sTheSoundControler->loadSample( lName.c_str() );
    }

  std::cerr << "*** Error SoundControler::LoadSample no filename for " << pKey << std::endl;

  return PBadSoundId;
#else
  return 0;
#endif
}
//------------------------------------------------
PSoundId
SoundControler::loadSample ( const char* pName )
{
  if( sMute || sNoSound )	return PBadSoundId;



#ifdef USE_SOUND

  std::string lFilePath(  cPath );

  if( lFilePath.length() >0 )
    lFilePath += "/";

  lFilePath +=pName;

  std::cout << "SoundControler::loadSample " << lFilePath << std::endl;

  SF_INFO lFileInfos;
  SNDFILE* lFile = sf_open( lFilePath.c_str(), SFM_READ, &lFileInfos);
  if (! lFile) {

    std::cerr << "*** SoundControler::loadSample sf_open failed " << lFilePath << std::endl;

    return 0;
  }


  ALsizei lNbSamples  = static_cast<ALsizei>(lFileInfos.channels *lFileInfos.frames);
  ALsizei lSampleRate = static_cast<ALsizei>(lFileInfos.samplerate);

  // Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
  std::vector<ALshort> lSamples(lNbSamples);
  if (sf_read_short( lFile, &lSamples[0], lNbSamples) < lNbSamples) {
    std::cerr << "*** SoundControler::loadSample sf_read_short failed " << lFilePath << std::endl;
    return 0;
  }

  // Fermeture du fichier
  sf_close(lFile);


  ALenum lFormat;
  switch (lFileInfos.channels)
    {
    case 1 :  lFormat = AL_FORMAT_MONO16;   break;
    case 2 :  lFormat = AL_FORMAT_STEREO16; break;
    default : return 0;
    }


  // Création du tampon OpenAL
  ALuint lBuffer;
  alGenBuffers(1, &lBuffer);

  // Remplissage avec les échantillons lus
  alBufferData(lBuffer, lFormat, &lSamples[0], lNbSamples * sizeof(ALushort), lSampleRate);

  // Vérification des erreurs
  if (alGetError() != AL_NO_ERROR)   {
    std::cerr << "*** SoundControler::loadSample alGetError " << lFilePath << std::endl;
    return 0;
  }

  cSamples.push_back( lBuffer );

  std::cout << "--- SoundControler::loadSample " << pName << " OK" <<  std::endl;

  return lBuffer;
#else
  return 0;
#endif
}
//------------------------------------------------
// internal protected  function

SoundSource*
SoundControler::internalPlaySample( PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop){

  ///	std::cout << "SoundControler::internalPlaySample" << pBufferId << " prio:" << pPriority ;
  //					<<  (sMute == GL_FALSE ? " ok ":" Mute ")
  //					<<  ( sNoSound == GL_FALSE ? " sound ": " no_sound") << std::endl;

#ifdef USE_SOUND


  if( sMute || sNoSound || pBufferId == PBadSoundId )	return 0;

  // Création d'une source
  SoundSource *lSrc =	 getFreeSource( pPriority );

  if( lSrc == NULL
      ||  lSrc->play( pBufferId, pGain, pPitch, pLoop ) == PBadSoundSourceId )
    {
      //		 std::cout << " RETURN NULL" << std::endl ;
      return NULL;
    }

  lSrc->cPriority = pPriority;

  //	std::cout << " ID:" << lSrc->cSourceId << std::endl ;

  return lSrc;

#else
  return NULL;
#endif
}
//------------------------------------------------
// Simple function

SoundSource*
SoundControler::playSample( PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop){

  //	std::cout << "SoundControler::playSample" << pBufferId
  //					<<  (sMute == GL_FALSE ? " ok ":" Mute ")
  //					<<  ( sNoSound == GL_FALSE ? " sound ": " no_sound") << std::endl;

  return internalPlaySample( pBufferId,  pPriority, pGain,  pPitch, pLoop );
}
//------------------------------------------------
// Simple function

SoundSource*
SoundControler::internalPlaySampleOwner( SoundSourceOwner & pOwner, PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop){

  //	std::cout << "SoundControler::playSample" << pBufferId
  //					<<  (sMute == GL_FALSE ? " ok ":" Mute ")
  //					<<  ( sNoSound == GL_FALSE ? " sound ": " no_sound") << std::endl;
  return internalPlaySample(  pBufferId,  pPriority, pGain,  pPitch, pLoop );
}
//------------------------------------------------
double
SoundControler::getPos( PSoundId pSource ) {

#ifdef USE_SOUND
  if( sMute || sNoSound || pSource == PBadSoundId )	return 0;


  ALfloat lSeconds = 0.f;

  alGetSourcef( pSource, AL_SEC_OFFSET, &lSeconds);
  return lSeconds;
#else
  return 0;
#endif
}
//------------------------------------------------
PSoundId
SoundControler::getStatus( PSoundId pSource ) {

  if( sMute || sNoSound || pSource == PBadSoundId )	return 0;

#ifdef USE_SOUND

  ALint lStatus;

  // Récupération de l'état du son
  alGetSourcei( pSource, AL_SOURCE_STATE, &lStatus);

  return lStatus;
#else
  return 0;
#endif
}
//------------------------------------------------
//------------------------------------------------
//------------------------------------------------
void SoundControler::freeSource( SoundSource* pSrc ){

#ifdef USE_SOUND
  alSourceStop( pSrc->cSourceId );

  if( pSrc->getOwner() != NULL )
    {
      pSrc->getOwner()->remove( pSrc );
    }

  pSrc->cState = SoundSource::SourceState::FREE;
#endif
}
//------------------------------------------------
// On renvoie la premiere source libre ou a defaut
// la moins prioritaire
// (on pourrait ajouter un critere de temps)

SoundSource*
SoundControler::getFreeSource( int pPriority){


#ifdef USE_SOUND

  int lMemPriority = pPriority;
  SoundSource* lMemSrc = NULL;
  float lMemTime =9E30;


  for( std::vector<SoundSource*>::iterator p=cSources.begin(); p!=cSources.end(); ++p)
    {
      SoundSource* lSrc = *p;

      ALint lSourceState;



      if( lSrc->cState == SoundSource::SourceState::FREE ) {
        //				std::cout << " - FREE - " ;
        return lSrc;
      }

      alGetSourcei( lSrc->cSourceId, AL_SOURCE_STATE, &lSourceState);

      if (lSourceState != AL_PLAYING) {
        lSrc->cState =  SoundSource::SourceState::FREE ;
        //				std::cout << " - FINISH - " ;
        return lSrc;
      }

      //	NSInteger lLooping;
      //alGetSourcei( lSrc->cSourceId, AL_LOOPING, &lLooping);


      // on exclut les sources en mode LOOP
      if( (lSrc->cState == SoundSource::SourceState::PLAY
           ||  lSrc->cState == SoundSource::SourceState::SRC_ERR)
          && lSrc->cPriority <= lMemPriority )
        {
          //		std::cout << "  Src:" +lSrc->cTime +" Mem:" + lMemTime  ;

          if( lSrc->cPriority == lMemPriority )
            {
              if( lSrc->cTime < lMemTime )
                {
                  lMemSrc = lSrc;
                  lMemTime = lSrc->cTime;
                }
            }
          else
            {
              lMemPriority = lSrc->cPriority;
              lMemSrc = lSrc;
              lMemTime = lSrc->cTime;
            }
        }
    }



  if( lMemSrc != NULL ) {
    //		std::cout << " - REUSE - " ;

    alSourceStop( lMemSrc->cSourceId );
    lMemSrc->cState =  SoundSource::SourceState::FREE;
  }

  return lMemSrc;
#else

  return NULL;
#endif
}
//*************************************************
//*************************************************
//*************************************************

SoundSource::SoundSource(  int pId, PSoundId pSourceId )
  :cId( pId ),
   cSourceId( pSourceId ),
   cOwner( NULL ),
   cPriority(0),
   cState( SoundSource::SourceState::FREE ),
   cTime(0)
{
}
//------------------------------------
SoundSource::~SoundSource()
{

#ifdef USE_SOUND

  if( cSourceId != PBadSoundId)
    {
      ALuint lSource = static_cast<ALuint>(cSourceId);

      alDeleteSources( 1, &lSource );
    }
#endif
}
//------------------------------------
PSoundSourceId
SoundSource:: play( PSoundId pBufferId,  float pGain, float pPitch, bool pLoop)
{

#ifdef USE_SOUND
  ALenum err = alGetError(); // clear error code

  alSourcei( cSourceId, AL_BUFFER, 0 );
  alSourcei( cSourceId, AL_BUFFER, pBufferId );

  if( pPitch != 1.0f )
    alSourcef( cSourceId, AL_PITCH, pPitch);
  if( pGain != 1.0f )
    alSourcef( cSourceId, AL_GAIN, pGain);

  if (pLoop)
    {
      alSourcei(cSourceId, AL_LOOPING, AL_TRUE);
      cState = SourceState::LOOP;
    }

  if( (err = alGetError()) != 0 )
    {
      std::cerr << "SoundSource:: play error" << std::endl;
      cState = SourceState::SRC_ERR;
      return PBadSoundSourceId;
    }
  else
    cState = SourceState::PLAY;


  cTime = WorldControler::GetTime();
  alSourcePlay( cSourceId );

  return cId;
#else
  return PBadSoundSourceId;
#endif
}
//------------------------------------

void
SoundSource::setPosition( Double3 pPosition  )
{
}
//------------------------------------
void
SoundSource::setSpeed(  Double3 pSpeed  )
{
}
//------------------------------------
void
SoundSource::setPositionAndSpeed(  Double3 pPosition, Double3 pSpeed )
{

}
//*************************************************
//*************************************************
//*************************************************
SoundSourceOwner::SoundSourceOwner()
{
  for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
    {
      (*p)->setOwner( NULL );
    }
}
//------------------------------------
SoundSourceOwner::~SoundSourceOwner()
{
  for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
    {
      (*p)->setOwner( NULL );
    }
}
//------------------------------------
void SoundSourceOwner::remove(SoundSource* pSrc){

  for( std::vector<SoundSource*>::iterator p= cMySources.begin();
       p!=cMySources.end();
       ++p)
    {
      if( *p == pSrc )
        cMySources.erase( p );
    }

}
//------------------------------------
void
SoundSourceOwner::playSoundSource( PSoundId pBufferId, int pPriority, float pGain, float pPitch, bool pLoop ){


  SoundSource *lSrc = SoundControler::sTheSoundControler->internalPlaySample( pBufferId,  pPriority, pGain,  pPitch, pLoop );

  if( lSrc == NULL )
    return ;


  if( lSrc->getOwner() == this )
    return;


  if( lSrc->getOwner() != NULL )
    {
      lSrc->getOwner()->remove( lSrc );
    }

  lSrc->setOwner( this );

  cMySources.push_back( lSrc );

}
//------------------------------------

void
SoundSourceOwner::setSoundSourcesPosition( Double3 pPosition  )
{
  for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
    {
      (*p)->setPosition( pPosition );
    }
}
//------------------------------------
void
SoundSourceOwner::setSoundSourcesSpeed(  Double3 pSpeed  )
{
  for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
    {
      (*p)->setSpeed( pSpeed );
    }
}
//------------------------------------
void
SoundSourceOwner::setSoundSourcesPositionAndSpeed(  Double3 pPosition, Double3 pSpeed )
{
  for( std::vector<SoundSource*>::iterator p=cMySources.begin(); p!=cMySources.end(); ++p)
    {
      (*p)->setPosition( pPosition );
      (*p)->setSpeed( pSpeed );
    }
}
//*************************************************

/*
  const ALchar* Extensions = alGetString(AL_EXTENSIONS);
  bool IsMultiChannelSupported = (alIsExtensionPresent("AL_EXT_MCFORMATS") == AL_TRUE);

  // Définition de la position de l'écouteur (ici l'origine)
  alListener3f(AL_POSITION, 0.f, 0.f, 0.f));

  // Définition de la vitesse de l'écouteur (ici nulle)
  alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));

  // Définition de l'orientation de l'écouteur (ici il regarde vers l'axe des Z)
  ALfloat Orientation[] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f};
  alListenerfv(AL_ORIENTATION, Orientation));
*/
