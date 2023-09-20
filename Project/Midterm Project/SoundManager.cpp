#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::addSample(ALLEGRO_SAMPLE* sample, std::string key)
{
	if (mAudioSampleMap.count(key) == 0) //Checks to see if the key has already been added before
	{
		mAudioSampleMap[key] = sample;
	}
}

void SoundManager::playSample(std::string key, bool loop)
{

	if (loop)
	{
		al_play_sample(mAudioSampleMap[key], 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_LOOP, nullptr);
	}
	else
	{
		al_play_sample(mAudioSampleMap[key], 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
	}
}
