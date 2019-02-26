#include "SoundData.h"



SoundData::SoundData()
{
	m_isLoop = false;

	m_sourceID = 0;
	m_volume = 0.1;
	m_pitch = 1.0;
	m_pBufferData = NULL;
}


SoundData::~SoundData()
{
}


bool SoundData::isPlaying()
{
	ALenum state;
	alGetSourcei(m_sourceID, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}