#include "audioSystem.h"
#include <iostream>

AudioSystem* AudioSystem::instance = nullptr;

#ifndef NO_AUDIO
#include <unordered_map>

// MAKE SURE YOU HAVE THE LINKER SET UP!!!
#include <soloud.h>
#include <soloud_wav.h>
// ***************************************

SoLoud::Soloud soLoud; // SoLoud engine
std::unordered_map <std::string, SoLoud::Wav*> clipMap;

AudioSystem::AudioSystem()
{
	if (AUDIO_ENABLED == false) return;

	soLoud.init(); // Initialize SoLoud	
}

AudioSystem::~AudioSystem()
{
	if (AUDIO_ENABLED == false) return;

	soLoud.deinit(); // Clean up!	
	for (auto clip : clipMap) delete clip.second; // Free pointer memory
	clipMap.clear(); // Free clipMap
}


void AudioSystem::LoadClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;

	SoLoud::Wav* wavClip = new SoLoud::Wav();   // One wave file
	wavClip->load(clipLocation); // Load a wave

	if (wavClip->getLength() > 0.0) clipMap.emplace(clipLocation, wavClip); // Add new clip to clipMap
	else std::cout << "Error: Unable to load clip" << std::endl; // Did not find clip
}

void AudioSystem::PlayClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;
	std::unordered_map<std::string, SoLoud::Wav*>::const_iterator got = clipMap.find(clipLocation);

	if (got == clipMap.end())
	{
		std::cout << "Attempting to load clip... ";
		LoadClip(clipLocation);

		got = clipMap.find(clipLocation);

		if (got == clipMap.end())
		{
			std::cout << "Error: Clip\"" << clipLocation << "\" not found" << std::endl; // Did not find clip
			return;
		} else std::cout << "Success." << std::endl;
	}

	soLoud.play(*clipMap[clipLocation]); // Found clip, play the wave
}

#endif // NO_AUDIO

#ifdef NO_AUDIO
#include <vector>
std::vector<std::string> readCallouts;

AudioSystem::AudioSystem() = default;
AudioSystem::~AudioSystem() = default;

void AudioSystem::LoadClip(const char* clipLocation) { std::cout << "WARNING: Unable to load clip. NO_AUDIO defined." << std::endl; }
void AudioSystem::PlayClip(const char* clipLocation) 
{ 
	// Make sure we haven't already debugged this, as over debugging is annoying.
	if (std::find(readCallouts.begin(), readCallouts.end(), clipLocation) == readCallouts.end()) 
	{
		std::cout << "WARNING: Unable to play clip \"" << clipLocation << "\" NO_AUDIO defined." << std::endl;
		readCallouts.push_back(clipLocation);
	}
}
#endif // NO_AUDIO