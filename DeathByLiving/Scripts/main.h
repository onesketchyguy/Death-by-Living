#pragma once

extern bool AUDIO_ENABLED;

const int DRINK_POTION_COST = 2;
const int DO_ATTACK_COST = 3;
const int MOVE_COST = 1;

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
	olc::Renderable* uiSheet = nullptr;

	olc::vi2d screenMid;

public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

	~Game() 
	{
		delete characterSheet;
		delete uiSheet;
		delete player;
		delete enemy;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		srand(time(0));

		screenMid = olc::vi2d{(ScreenWidth() >> 1), (ScreenHeight() >> 1) };

		audio.LoadTestCases();

		uiSheet = new olc::Renderable();
		uiSheet->Load("Data/ui.png");

		inv.Initialize(this, uiSheet);
		inv.SetDrawing(true, this);
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
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_ADD).bPressed) player->health.ModifyValue(1);

		if (GetKey(olc::Key::LEFT).bPressed) player->MoveDir(-1, 0);

		if (GetKey(olc::Key::RIGHT).bPressed) player->MoveDir(1, 0);

		if (GetKey(olc::Key::UP).bPressed) player->MoveDir(0, -1);

		if (GetKey(olc::Key::DOWN).bPressed) player->MoveDir(0, 1);

		if (inv.GetUsedItem() != nullptr) 
		{
			if (player->actionTokens >= DRINK_POTION_COST)
			{
				player->health.ModifyValue(inv.GetUsedItem()->keyValue);
				inv.GetUsedItem()->durValue--;

				player->actionTokens -= DRINK_POTION_COST;
			}

			inv.ClearUseItem();
		}


		inv.Update(this);
		player->Draw(this, fElapsedTime);
		player->health.Draw(this, screenMid.x, 0, fElapsedTime);

		enemy->Draw(this, fElapsedTime);

		// FIXME: Implement turns
		if (player->actionTokens <= 0) player->StartTurn(); // DEBUG::REMOVE ME

		// Draw available actionTokens
		for (size_t i = 0; i < 3; i++)
		{
			bool isFilledToken = player->actionTokens > i;

			DrawPartialDecal(olc::vf2d{ 8.0f*i, 0}, olc::vi2d{ 8, 8 }, uiSheet->Decal(),
				olc::vi2d{ 16 * 4, 0}, olc::vi2d{16,16}, (isFilledToken ? olc::WHITE : olc::VERY_DARK_GREY));
		}

		return true;
	}
};