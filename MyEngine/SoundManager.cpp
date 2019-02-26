#include "SoundManager.h"
#include <al.h>
#include <alc.h>
#include "CWaves.h"

std::unordered_map<const char*, SoundData*> SoundManager::soundMap;
static CWaves  *g_pWaveLoader;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}


void SoundManager::Initialize()
{
	ALCcontext	*context = NULL;
	ALCdevice	*device = NULL;

	// Initialization
	device = alcOpenDevice(NULL); // select the "preferred device"
	if (!device)
		return;

	// use the device to make a context
	context = alcCreateContext(device, NULL);
	if (!context)
		return;

	// set my context to the currently active one
	alcMakeContextCurrent(context);

	g_pWaveLoader = new CWaves();
}


bool SoundManager::Load(const char* path, const char* key, bool isLoop)
{
	SoundData* soundData = new SoundData();

	alGetError(); //clear any previous error...

				  // grab a buffer ID from openAL
	alGenBuffers(1, &soundData->m_bufferID);


	if (LoadWaveToBuffer(path, soundData->m_bufferID, 0))
	{

	}

	// grab a source ID from openAL, this will be the base source ID
	alGenSources(1, &soundData->m_sourceID);

	// attach the buffer to the source
	alSourcei(soundData->m_sourceID, AL_BUFFER, soundData->m_bufferID);

	soundData->m_isLoop = isLoop;
	if (soundData->m_isLoop)
		alSourcei(soundData->m_sourceID, AL_LOOPING, AL_TRUE);


	if ((soundData->m_error = alGetError()) != AL_NO_ERROR)
		return false;

	soundMap.insert(std::pair<const char*, SoundData*>(key, soundData));
	return true;
}


void SoundManager::Loading()
{
	Initialize();
	Load("00.wav", "Test", true);
	Load("./Sound/005 Shot.wav", "Shot", false);
	Load("./Sound/002 Game Start Music.wav", "StartMusic", false);
	Load("./Sound/006 Hit on Zako.wav", "ZakoHitted", false);
	Load("./Sound/341626__projectsu012__small-boom.wav", "PlayerDie", false);
	Load("./Sound/007 Hit on Goei.wav", "GoeiHitted", false);
	Load("./Sound/008 Hit on Boss (1).wav", "Boss1Hitted", false);
	Load("./Sound/009 Hit on Boss (2).wav", "Boss2Hitted", false);
	Load("./Sound/004 Alien Flying.wav", "EnemyFly", false);
	Load("./Sound/233985__foolboymedia__running-out.wav", "BreakAdventureBgm", true);
	//Load("./Sound/275151__bird-man__gun-shot.wav", "DefaultGunShoot", false);
	Load("./Sound/138583__goodsoundforyou__single-surpressed-shot.wav", "DefaultGunShoot", false);
	//Load("./Sound/163456__lemudcrab__pistol-shot.wav", "DefaultGunShoot", false);
	Load("./Sound/275151__bird-man__gun-shot.wav", "SniperShoot", false);
	Load("./Sound/345297__scrampunk__itemize.wav", "GetItem", false);
	Load("./Sound/195396__goup-1__boom-kick.wav", "Explosion", false);
	Load("./Sound/396331__nioczkus__1911-reload.wav", "GunLoad2", false);
}


bool SoundManager::Play(const char* key)
{
#ifdef NO_SOUND
	return false;
#endif // !NO_SOUND

	SoundData* soundData = soundMap[key];
	if (soundData->isPlaying()) //see if the base source is busy...
	{
		//if so, create a new source
		ALuint tmpSourceID;
		alGenSources(1, &tmpSourceID);

		//attach the buffer to the source
		alSourcei(tmpSourceID, AL_BUFFER, soundData->m_bufferID);
		if (soundData->m_isLoop)
			alSourcei(soundData->m_sourceID, AL_LOOPING, AL_TRUE);

		alSourcePlay(tmpSourceID);

		soundData->m_vecSoundSource.push_back(tmpSourceID);

		return ((soundData->m_error = alGetError()) != AL_NO_ERROR);
	}

	//if the base source isn't busy, just use that one...
	alSourcePlay(soundData->m_sourceID);

	return ((soundData->m_error = alGetError()) != AL_NO_ERROR);
}


bool SoundManager::Stop(const char* key)
{
	alSourceStop(soundMap[key]->m_sourceID);

	return ((soundMap[key]->m_error = alGetError()) != AL_NO_ERROR);
}

bool SoundManager::LoadWaveToBuffer(const char *szWaveFile, ALuint uiBufferID, ALenum eXRAMBufferMode)
{
	WAVEID			WaveID;
	ALint			iDataSize, iFrequency;
	ALenum			eBufferFormat;
	ALchar			*pData;
	bool			bReturn;

	bReturn = AL_FALSE;
	if (g_pWaveLoader)
	{
		if (SUCCEEDED(g_pWaveLoader->LoadWaveFile(szWaveFile, &WaveID)))
		{
			if ((SUCCEEDED(g_pWaveLoader->GetWaveSize(WaveID, (unsigned long*)&iDataSize))) &&
				(SUCCEEDED(g_pWaveLoader->GetWaveData(WaveID, (void**)&pData))) &&
				(SUCCEEDED(g_pWaveLoader->GetWaveFrequency(WaveID, (unsigned long*)&iFrequency))) &&
				(SUCCEEDED(g_pWaveLoader->GetWaveALBufferFormat(WaveID, &alGetEnumValue, (unsigned long*)&eBufferFormat))))
			{
				// Set XRAM Mode (if application)
				//if (eaxSetBufferMode && eXRAMBufferMode)
				//	eaxSetBufferMode(1, &uiBufferID, eXRAMBufferMode);

				alGetError();
				alBufferData(uiBufferID, eBufferFormat, pData, iDataSize, iFrequency);
				if (alGetError() == AL_NO_ERROR)
					bReturn = AL_TRUE;

				g_pWaveLoader->DeleteWaveFile(WaveID);
			}
		}
	}

	return bReturn;
}


void SoundManager::DestroyOpenAL()
{
	ALCcontext	*context = NULL;
	ALCdevice	*device = NULL;

	//Get active context (there can only be one)
	context = alcGetCurrentContext();

	//Get device for active context
	device = alcGetContextsDevice(context);

	alcMakeContextCurrent(NULL);

	//Release context
	alcDestroyContext(context);

	//Close device
	alcCloseDevice(device);

	if (g_pWaveLoader) delete g_pWaveLoader;
	g_pWaveLoader = NULL;
}


void SoundManager::Release()
{
	for (std::unordered_map<const char*, SoundData*>::iterator it = soundMap.begin(); it != soundMap.end();)
	{
		delete (*it).second;
		it = soundMap.erase(it);
	}
}