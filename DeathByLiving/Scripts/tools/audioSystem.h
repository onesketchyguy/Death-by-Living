#pragma once
#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

extern bool AUDIO_ENABLED;

class AudioSystem
{
public:	
	AudioSystem();
	~AudioSystem();

public:
	void LoadClip(const char* clipLocation);
	void PlayClip(const char* clipLocation);

public: // TEST CASE STUFF
	void LoadTestCases() 
	{
		const char* clipA = "Data/SampleA.wav";

		LoadClip(clipA);
	}

	void RunTestCase() 
	{
		const char* clipA = "Data/SampleA.wav";

		PlayClip(clipA);
	}
};


#endif