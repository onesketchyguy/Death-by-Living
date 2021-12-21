#pragma once

extern bool AUDIO_ENABLED;

#include "../lib/olcPixelGameEngine.h"
#include "tools/audioSystem.h"
#include "inventorySystem.h"
#include "healthSystem.h"
#include "characterSystem.h"

class Game : public olc::PixelGameEngine
{
private: // Global variables
	AudioSystem audio;
	Inventory inv;
	Character* player;
	Character* enemy;
	olc::Renderable* characterSheet = nullptr;

public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

	~Game() 
	{
		delete characterSheet;
		delete player;
		delete enemy;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		srand(time(0));

		audio.LoadTestCases();

		inv.Initialize(this);
		inv.SetPosition(ScreenWidth(), ScreenHeight());

		characterSheet = new olc::Renderable();
		characterSheet->Load("Data/characterSheet.png");

		player = new Character(characterSheet, inv.GetArmor(), inv.GetWeapon());
		player->pos = olc::vi2d{ 0, 0 };

		enemy = new Character(characterSheet, inv.GetArmor(), inv.GetWeapon(), 1, 0);
		enemy->pos = olc::vi2d{2, 1 };

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

		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_SUB).bPressed)  player->health.ModifyValue(-1);
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::SHIFT).bHeld && GetKey(olc::Key::NP_SUB).bPressed)  player->health.ModifyValue(-1, true);
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_ADD).bPressed) player->health.ModifyValue(1);

		if (GetKey(olc::Key::LEFT).bPressed) 
		{
			player->pos.x--;
		}

		if (GetKey(olc::Key::RIGHT).bPressed)
		{
			player->pos.x++;
		}

		if (GetKey(olc::Key::UP).bPressed)
		{
			player->pos.y--;
		}

		if (GetKey(olc::Key::DOWN).bPressed)
		{
			player->pos.y++;
		}

		inv.Update(this);
		player->Draw(this, fElapsedTime);
		player->health.Draw(this, 0, 0);

		enemy->Draw(this, fElapsedTime);

		return true;
	}
};