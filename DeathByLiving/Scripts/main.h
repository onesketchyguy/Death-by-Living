#pragma once

#include "../lib/olcPixelGameEngine.h"
#include "tools/audioSystem.h"
#include "inventorySystem.h"
#include "healthSystem.h"
#include "characterSystem.h"
#include "turnManager.h"
#include "utility.h"
#include "tools/layerManager.h"

uint8_t LayerManager::GetLayer(LAYER_MASK m) { return static_cast<uint8_t>(m); }

void LayerManager::GenerateLayers(olc::PixelGameEngine* pge)
{
	for (uint8_t i = 0; i < 3; i++) pge->EnableLayer(pge->CreateLayer(), true);
}

class Game : public olc::PixelGameEngine
{
private: // Global variables
	TurnManager* turnManager;

public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

	~Game() 
	{
		delete turnManager;
		AudioSystem::DestroyInstance();
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		srand(static_cast<unsigned int>(time(0)));

		LayerManager::GenerateLayers(this);

		AudioSystem::CreateInstance();
		AudioSystem::GetInstance()->SetSoundTrack(util::GetCWD("/Data/SFX/OST.wav").c_str());

		olc::vi2d mapSize{ 21, 14 };
		std::vector<CharacterTemplate> cTemplates;
		CharacterTemplate::LoadJsonData(cTemplates, util::GetCWD("/Data/characterTemplates.json").c_str());

		turnManager = new TurnManager();
		for (int i = 0; i < cTemplates.size(); i++) turnManager->AddCharacter(this, cTemplates.at(i), rand() % mapSize.x, rand() % mapSize.y);
		turnManager->SetTurnOrder();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		AudioSystem::GetInstance()->PlaySoundTrack(fElapsedTime);

		SetDrawTarget(LayerManager::GetLayer(LAYER_MASK::WORLD));
		Clear(olc::BLANK);

		// FIXME: Draw world

		SetDrawTarget(nullptr);

		// Draw characters/UI
		turnManager->Update(this, fElapsedTime);

		return !(GetKey(olc::ESCAPE).bReleased);
	}
};
