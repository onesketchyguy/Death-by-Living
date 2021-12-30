#pragma once
#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

extern bool AUDIO_ENABLED;

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	static void DestroyInstance() { if (instance != nullptr) delete instance; }
	static void CreateInstance() { instance = new AudioSystem(); }
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