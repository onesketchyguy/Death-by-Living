#pragma once

extern bool AUDIO_ENABLED;

#include "../lib/olcPixelGameEngine.h"
#include "tools/audioSystem.h"

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

	AudioSystem audio;

	const char* clipA = "Data/SampleA.wav";
	const char* clipB = "Data/SampleB.wav";
	const char* clipC = "Data/SampleC.wav";

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		audio.LoadClip(clipA);
		audio.LoadClip(clipB);
		audio.LoadClip(clipC);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::K1).bPressed) 
		{
			audio.PlayClip(clipA);
		}

		if (GetKey(olc::K2).bPressed)
		{
			audio.PlayClip(clipB);
		}

		if (GetKey(olc::K3).bPressed)
		{
			audio.PlayClip(clipC);
		}

		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};