#pragma once
#include<al.h>
#include <vector>

class SoundData
{
public:
	SoundData();
	~SoundData();

	typedef std::vector<ALuint> VEC_SOUNDSOURCE;
	VEC_SOUNDSOURCE m_vecSoundSource;

	ALuint		m_bufferID;
	ALuint		m_sourceID;			//base source ID
	ALdouble	m_duration;			//duration of the sound in seconds
	ALfloat		m_volume;				//volume [0 - 1]
	ALfloat		m_pitch;				//speed
	bool		m_isLoop;
	ALenum		m_error;
	ALvoid		*m_pBufferData;		//holds the actual sound data


public:
	bool isPlaying();
};

