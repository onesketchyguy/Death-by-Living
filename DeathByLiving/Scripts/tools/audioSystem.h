#pragma once
#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <iostream>

extern bool AUDIO_ENABLED;

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	static void DestroyInstance() { if (instance != nullptr) { delete instance;  std::cout << "Deleted audio system instance." << std::endl; } }
	static void CreateInstance() { instance = new AudioSystem(); std::cout << "Created audio system instance." << std::endl; }
	static AudioSystem* GetInstance() { return instance; }

private:
	static AudioSystem* instance;

public:
	void LoadClip(const char* clipLocation);
	// Returns clip length
	double PlayClip(const char* clipLocation);

	void SetSoundTrack(const char* clipLocation);
	void PlaySoundTrack(float elapsedTime);
};

#endif