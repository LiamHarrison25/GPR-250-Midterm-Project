#pragma once
#include <Trackable.h>
#include <map>
#include <allegro5/allegro_audio.h>

class SoundManager : public Trackable
{
public:

	SoundManager();
	~SoundManager();

	void addSample(ALLEGRO_SAMPLE* sample, std::string key);


	void playSample(std::string key, bool loop);

private:

	std::map<std::string, ALLEGRO_SAMPLE*> mAudioSampleMap;
};
