#pragma once

#include "../lib/olcPixelGameEngine.h"
#include "tools/audioSystem.h"
#include "inventorySystem.h"
#include "healthSystem.h"
#include "characterSystem.h"
#include "turnManager.h"

class Game : public olc::PixelGameEngine
{
private: // Global variables
	std::vector<Character*> characters;
	Character* player;	

	TurnManager turnManager;

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

			c->pos = {rand() % c->mapSize.x, rand() % c->mapSize.y };

			turnManager.AddCharacter(c);
			characters.push_back(c);
		}

		turnManager.SetTurnOrder();
		turnManager.SetUISheet(uiSheet);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLANK);

		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::I).bPressed) player->inv.AddItem(Item::GetRandomItem());
		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_SUB).bPressed) player->DealDamage(1);
		//if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_ADD).bPressed) player->health.ModifyValue(1);

		turnManager.Update(this, fElapsedTime);

		return true;
	}
};