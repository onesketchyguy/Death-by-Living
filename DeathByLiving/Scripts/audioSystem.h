#pragma once

#ifdef UNSAFE_CODE

#define OLC_PGEX_SOUND
#include "../lib/olcPGEX_Sound.h"

void StartAudioTestCase() 
{
	olc::SOUND::InitialiseAudio();

	auto track = olc::SOUND::LoadAudioSample("/Data/SampleA.wav");

	olc::SOUND::PlaySample(track);

	while (olc::SOUND::listActiveSamples.size() > 0)
	{
		// Wait while we play out these sounds
	}

	olc::SOUND::DestroyAudio();
}

#endif