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
};


#endif