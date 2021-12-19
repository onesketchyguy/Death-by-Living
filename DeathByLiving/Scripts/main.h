#pragma once

extern bool AUDIO_ENABLED;

#include "../lib/olcPixelGameEngine.h"
#include "tools/audioSystem.h"
#include "inventorySystem.h"

class Game : public olc::PixelGameEngine
{
private: // Global variables
	AudioSystem audio;
	Inventory inv;

public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}	

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		srand(time(0));

		audio.LoadTestCases();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::TILDE).bPressed) audio.RunTestCase();
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::I).bPressed) 
		{
			if (inv.AddItem(Item::GetRandomItem())) 
			{
				std::cout << "Added item." << std::endl;
			}
			else
			{
				std::cout << "Failed to add item" << std::endl;
			}
		}
		else if (GetKey(olc::Key::I).bPressed) inv.SetDrawing(!inv.GetDrawing());

		inv.Update(this);

		return true;
	}
};