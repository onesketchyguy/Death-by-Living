#pragma once

extern bool AUDIO_ENABLED;

#include "../lib/olcPixelGameEngine.h"
#include "tools/audioSystem.h"
#include "inventorySystem.h"
#include "healthSystem.h"

class Game : public olc::PixelGameEngine
{
private: // Global variables
	AudioSystem audio;
	Inventory inv;
	UserHealth hp{inv.GetArmor()};

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
		inv.SetPosition(ScreenWidth(), ScreenHeight());

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLANK);

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
		else if (GetKey(olc::Key::I).bPressed) inv.SetDrawing(!inv.GetDrawing(), this);

		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::TILDE).bPressed) audio.RunTestCase();

		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_SUB).bPressed) hp.ModifyValue(-1);
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::SHIFT).bHeld && GetKey(olc::Key::NP_SUB).bPressed) hp.ModifyValue(-1, true);
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_ADD).bPressed) hp.ModifyValue(1);


		inv.Update(this);
		hp.Draw(this, 0, 0);

		return true;
	}
};