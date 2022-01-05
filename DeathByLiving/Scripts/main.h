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
		//AudioSystem::DestroyInstance();
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		srand(time(0));

		//AudioSystem::CreateInstance();

		uiSheet = new olc::Renderable();
		uiSheet->Load(util::GetCWD("Data/ui.png"));

		characterSheet = new olc::Renderable();
		characterSheet->Load(util::GetCWD("Data/characterSheet.png"));
		
		std::vector<CharacterTemplate> cTemplates;
		CharacterTemplate::LoadJsonData(cTemplates);

		for (auto& temp : cTemplates)
		{
			Character* c = new Character(characterSheet, temp);

			if (c->name == "Player")
			{
				c->inv.Initialize(this, uiSheet);
				c->inv.SetDrawing(this, true);
				c->inv.SetPosition(ScreenWidth(), ScreenHeight());
			}

			c->pos = { rand() % c->mapSize.x, rand() % c->mapSize.y };

			turnManager.AddCharacter(c);
		}

		turnManager.SetTurnOrder();
		turnManager.SetUISheet(uiSheet);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLANK);

		// FIXME: Draw world

		// Draw characters/UI
		turnManager.Update(this, fElapsedTime);

		return true;
	}
};
