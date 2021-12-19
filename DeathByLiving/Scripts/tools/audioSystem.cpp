#include <iostream>
#include <unordered_map>

// MAKE SURE YOU HAVE THE LINKER SET UP!!!
#include <soloud.h>
#include <soloud_wav.h>
// ***************************************

#include "audioSystem.h"

SoLoud::Soloud soLoud; // SoLoud engine
std::unordered_map <std::string, SoLoud::Wav*> clipMap;

AudioSystem::AudioSystem()
{
	if (AUDIO_ENABLED == false) return;

	soLoud.init(); // Initialize SoLoud	

	clipMap = std::unordered_map <std::string, SoLoud::Wav*>();
	clipMap.clear();
}

AudioSystem::~AudioSystem()
{
	if (AUDIO_ENABLED == false) return;

	soLoud.deinit(); // Clean up!
	clipMap.clear();
}


void AudioSystem::LoadClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;

	SoLoud::Wav* wavClip = new SoLoud::Wav();   // One wave file
	wavClip->load(clipLocation); // Load a wave

	clipMap.emplace(clipLocation, wavClip);
}

void AudioSystem::PlayClip(const char* clipLocation)
{
	if (AUDIO_ENABLED == false) return;

	// Verify the clip exists before tryint to play it
	std::unordered_map<std::string, SoLoud::Wav*>::const_iterator got = clipMap.find(clipLocation);

	if (got == clipMap.end()) std::cout << "Error: Clip not found" << std::endl;
	else soLoud.play(*clipMap[clipLocation]); // Play the wave

	//int x = soLoud.play(gWave); // Grab the handle
	//soLoud.setPan(x, -0.2f);    // Use handle to adjust panning
}