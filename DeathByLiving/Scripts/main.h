#pragma once

extern bool AUDIO_ENABLED;
AudioSystem audio;

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
		
		for (auto c : characters) delete c;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		srand(time(0));

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
		Clear(olc::BLANK);

		if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::TILDE).bPressed) audio.RunTestCase();
		
		//if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_SUB).bPressed) player->DealDamage(1);
		//if (GetKey(olc::Key::CTRL).bHeld && GetKey(olc::Key::NP_ADD).bPressed) player->health.ModifyValue(1);

		turnManager.Update(this, fElapsedTime);

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