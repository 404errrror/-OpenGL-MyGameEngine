#pragma once
#include "Global.h"
#include "SoundData.h"
class SoundManager
{
public:
	static std::unordered_map<const char*, SoundData*> soundMap;
public:
	SoundManager();
	~SoundManager();

	static void Initialize();
	static bool Load(const char* path, const char* key,bool isLoop);
	static void Loading();
	static bool Play(const char* key);
	static bool Stop(const char* key);
	static void DestroyOpenAL();
	static void Release();

private:
	static bool LoadWaveToBuffer(const char *szWaveFile, ALuint uiBufferID, ALenum eXRAMBufferMode);
};

