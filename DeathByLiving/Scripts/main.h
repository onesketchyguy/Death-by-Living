#pragma once

extern bool AUDIO_ENABLED;

#include "../lib/olcPixelGameEngine.h"
//#include "tools/audioSystem.h"
#include "inventorySystem.h"
#include "healthSystem.h"
#include "characterSystem.h"
#include "turnManager.h"
#include "levelManager.h"

class Game : public olc::PixelGameEngine
{
private: // Global variables
	AudioSystem audio;
	Inventory inv;
	Character* player;
	Character* enemy;

	TurnManager turnManager;
    LevelManager levelManager = LevelManager();

	olc::Renderable* characterSheet = nullptr;
	olc::Renderable* uiSheet = nullptr;

public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

	~Game() 
	{
		delete characterSheet;
        delete tileSheet;
		delete uiSheet;
		AudioSystem::DestroyInstance();
		
		for (auto c : characters) delete c;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		srand(time(0));

		AudioSystem::CreateInstance();		

		audio.LoadTestCases();

		uiSheet = new olc::Renderable();
		uiSheet->Load("Data/ui.png");

		characterSheet = new olc::Renderable();
		characterSheet->Load("Data/characterSheet.png");
		
		std::vector<CharacterTemplate> cTemplates;
		CharacterTemplate::LoadJsonData(cTemplates);

		for (auto& temp : cTemplates)
		{
			Character* c = new Character(characterSheet);
			GetCharacterFromTemplate(c, temp);

			if (c->name == "Player") 
			{
				player = c;
				player->inv.Initialize(this, uiSheet);
				player->inv.SetDrawing(this, true);
				player->inv.SetPosition(ScreenWidth(), ScreenHeight());
			}

			turnManager.AddCharacter(c);
			characters.push_back(c);
		}

		turnManager.SetTurnOrder();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Clear(olc::BLANK);

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

		// Turn implementation
		auto currentTurn = turnManager.GetCurrentCharacterTurn();
		if (currentTurn == nullptr) turnManager.CycleTurn();
		else if (currentTurn->actionTokens <= 0) 
		{
			currentTurn->EndTurn();

			turnManager.CycleTurn();
		}

		// FIXME: Implement AI
		if (currentTurn == enemy) 
		{
			if (aiThinking >= AI_THINK_TIME)
			{
				int xDir = rand() % 100 > 50 ? 1 : -1;
				int yDir = rand() % 100 > 50 ? 1 : -1;

				int newPosX = enemy->GetScreenPos(enemy->pos.x + xDir, 0).x;
				int newPosY = enemy->GetScreenPos(0, enemy->pos.y + yDir).y;

				if (newPosX > ScreenWidth() || newPosX <= 0) xDir = 0;
				if (newPosY > ScreenHeight() || newPosY <= 0) yDir = 0;

				aiThinking = 0.0f;

				enemy->MoveDir(xDir, yDir);
			}
			else 
			{
				aiThinking += fElapsedTime;
			}
		}

		// Draw available actionTokens
		for (size_t i = 0; i < player->GetMaxTokens(); i++)
		{
			float x = 8.0f * (i % 6);
			float y = 8.0f * (i / 6);
			bool isFilledToken = player->actionTokens > i;

			DrawPartialDecal(olc::vf2d{ x, y}, olc::vi2d{ 8, 8 }, uiSheet->Decal(),
				olc::vi2d{ 16 * 4, 0}, olc::vi2d{16,16}, (isFilledToken ? olc::WHITE : olc::VERY_DARK_GREY));
		}

		return true;
	}
};
