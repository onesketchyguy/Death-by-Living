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

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		audio.LoadTestCases();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::TILDE).bPressed) 
		{
			audio.RunTestCase();
		}

		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};