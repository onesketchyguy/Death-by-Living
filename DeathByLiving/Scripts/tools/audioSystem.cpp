#include "audioSystem.h"
#include <iostream>

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

	clipMap.emplace(clipLocation, wavClip); // Add new clip to clipMap
}

void AudioSystem::PlayClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;

	// Verify the clip exists before trying to play it
	std::unordered_map<std::string, SoLoud::Wav*>::const_iterator got = clipMap.find(clipLocation);

	if (got == clipMap.end()) std::cout << "Error: Clip not found" << std::endl; // Did not find clip
	else soLoud.play(*clipMap[clipLocation]); // Found clip, play the wave

	//int x = soLoud.play(gWave); // Grab the handle
	//soLoud.setPan(x, -0.2f);    // Use handle to adjust panning
}

#endif // NO_AUDIO

#ifdef NO_AUDIO
AudioSystem::AudioSystem() = default;
AudioSystem::~AudioSystem() = default;

void AudioSystem::LoadClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;
	std::cout << "Unable to load clip! NO_AUDIO defined in comiler" << std::endl;
}

void AudioSystem::PlayClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;
	std::cout << "Unable to play clip! NO_AUDIO defined in comiler" << std::endl;
}

#endif // NO_AUDIO