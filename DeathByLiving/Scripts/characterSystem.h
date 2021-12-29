#pragma once
#ifndef CHARACTER_SYSTEM_H
#define CHARACTER_SYSTEM_H

#include "items.h"
#include "healthSystem.h"
#include "../lib/olcPixelGameEngine.h"
#include "../lib/json.hpp"

// for convenience
using json = nlohmann::json;

class Character 
{
private: // Action stuff
	const int DRINK_POTION_COST = 2;
	const int DO_ATTACK_COST = 3;
	const int MOVE_COST = 1;

	int maxTokens = 3;

public: // Map stuff
	olc::vi2d mapSize{ 22, 15 };

private: // Animation stuff
	float elapsedTime = 0;
	const float TAU = 2.0f * 3.14159f;

	int drawScaleX = 16;
	int drawScaleY = 16;

	int cellX = 0;
	int cellY = 0;

	const int FRAME_SIZE = 24;

	float animationSpeed = 4.0f;
	float animateAmount = 1.5f;

	const float DEATH_ANIM_LENGTH = 1.0f;
	float deathAnimSpeed = 4.0f;
	float deathAnimTime = DEATH_ANIM_LENGTH;

	olc::Renderable* spriteSheet = nullptr;

public: // AI stuff
	const float AI_THINK_TIME = 0.5f;
	float aiThinking = 0.0f;

	const float THINK_CHAR_INTERVAL = 0.2f;
	float thinkingTime = 0.0f;
	int aiThinkingChar = 0;

	std::string summonsCharacter = "";
	int summonInterval = 0;
	int lastSummon = 0;

	bool moveRandom = false;

public: // Character stuff
	std::string name = "Genericcha Racter";
	bool canMoveDiagonally = false;
	bool canOverlap = false;
	int respawnTime = 0;	

	olc::vi2d pos{0, 0};
	int turnOrder = 0;
	Inventory inv;
	HealthContainer health{ 10 };

	const int& GetMaxTokens() { return maxTokens; }
	const void SetMaxTokens(int m) { maxTokens = m; }
	int actionTokens = 0;

	olc::vi2d GetScreenPos() { return olc::vi2d{ pos.x * drawScaleX, pos.y * drawScaleY }; }

	olc::vi2d GetScreenPos(int x, int y) { return olc::vi2d{ x * drawScaleX, y * drawScaleY }; }

	void DealDamage(int damage)
	{
		if (inv.GetArmor().name != Item::NULL_ITEM.name)
		{
			if (inv.GetArmor().durValue > 0)
			{
				damage -= inv.GetArmor().keyValue;
				inv.GetArmor().durValue -= 1;

				if (damage < 0) damage = 0;
			}

			if (inv.GetArmor().durValue <= 0)
			{
				inv.GetArmor().name = Item::NULL_ITEM.name;
				std::cout << "ARMOR BROKE!" << std::endl;
			}
		}

		if (damage > 0) 
		{
			health.ModifyValue(-damage);
			//AudioSystem::GetInstance()->PlayClip("Data/Hit_Hurt.wav");
		}
	}

	void StartTurn() 
	{
		actionTokens = maxTokens;
		aiThinking = AI_THINK_TIME;
	}

	void HandleTurn(olc::PixelGameEngine* pge, float elapsedTime)
	{
		if (name == "Player") 
		{
			int moveX = 0;
			int moveY = 0;

			if (pge->GetKey(olc::Key::LEFT).bPressed) moveX = -1;
			if (pge->GetKey(olc::Key::RIGHT).bPressed) moveX = 1;
			if (pge->GetKey(olc::Key::UP).bPressed)	moveY = -1;
			if (pge->GetKey(olc::Key::DOWN).bPressed) moveY = 1;

			if (moveX != 0 || moveY != 0) MoveDir(moveX, moveY);

			if (inv.GetUsedItem() != nullptr)
			{
				if (actionTokens >= DRINK_POTION_COST)
				{
					health.ModifyValue(inv.GetUsedItem()->keyValue);
					inv.GetUsedItem()->durValue--;

					actionTokens -= DRINK_POTION_COST;
				}

				inv.ClearUseItem();
			}
		}
		else // Handle AI Stuff
		{
			// FIXME: Implement AI
			if (aiThinking <= 0.0f)
			{
				thinkingTime = 0;
				aiThinking = AI_THINK_TIME + ((rand() % 100)/100.0f);
				// FIXME: use character.moveRand

				if (canMoveDiagonally) 
				{
					int xDir = rand() % 100 > 50 ? 1 : -1;
					int yDir = rand() % 100 > 50 ? 1 : -1;
					
					MoveDir(xDir, yDir);
				}
				else 
				{
					int ran = rand() % 200;

					int xDir = ran < 100 ? (ran < 50 ? 1 : -1) : 0;
					int yDir = ran > 100 ? (ran > 150 ? 1 : -1) : 0;

					MoveDir(xDir, yDir);
				}				
			}
			else
			{
				aiThinking -= elapsedTime;

				std::string thinkingImage = "";
				for (int i = 0; i < aiThinkingChar; i++) thinkingImage += '.';

				if (thinkingTime >= THINK_CHAR_INTERVAL)
				{
					if (aiThinkingChar > 2) aiThinkingChar = 0;
					else aiThinkingChar++;

					thinkingTime = 0;
				}
				else thinkingTime += elapsedTime;

				pge->DrawStringDecal(GetScreenPos() + olc::vi2d{ drawScaleX / 3, -2 }, thinkingImage, olc::WHITE, olc::vf2d{1.0f,1.0f} * 0.35f);
			}
		}
	}

	void EndTurn() 
	{
		if (name == "Player") health.ModifyValue(-1);
	}

	void MoveDir(int xDir, int yDir)
	{
		if (actionTokens > 0) 
		{
			if (pos.x + xDir >= mapSize.x || pos.x + xDir < 0 || 
				pos.y + yDir >= mapSize.y || pos.y + yDir < 0 ||
				(xDir == 0 && yDir == 0)) return;

			actionTokens -= MOVE_COST;

			pos.x += xDir;
			pos.y += yDir;

			//AudioSystem::GetInstance()->PlayClip("Data/Move.wav");
		}
	}

	void Draw(olc::PixelGameEngine* pge, float deltaTime) 
	{
		if (name == "Player") 
		{			
			health.Draw(pge, pge->ScreenWidth() >> 1, 0, deltaTime);

			if (pge->GetKey(olc::Key::I).bPressed) inv.SetDrawing(pge, !inv.GetDrawing());
		}

		const float RIGHT = static_cast<float>(drawScaleX);
		const float BOTTOM = static_cast<float>(drawScaleY);
		const float TOP = animateAmount * sin(elapsedTime);

		elapsedTime += animationSpeed * deltaTime;
		if (elapsedTime >= TAU) elapsedTime = 0.0f;

		olc::vf2d* positions = new olc::vf2d[4]{
			GetScreenPos() + olc::vf2d{ 0, TOP },
			GetScreenPos() + olc::vf2d{ 0, BOTTOM },
			GetScreenPos() + olc::vf2d{ RIGHT, BOTTOM },
			GetScreenPos() + olc::vf2d{ RIGHT, TOP },
		};

		if (health.Empty())
		{			
			if (deathAnimTime > 0.0f)
			{
				deathAnimTime -= deathAnimSpeed * deltaTime;
			}
			else 
			{
				deathAnimTime = 0.0f;
				delete[] positions;
				return;
			}

			float animEval = 1 - (deathAnimTime / DEATH_ANIM_LENGTH);

			float topRight = (animateAmount * sin(elapsedTime)) + BOTTOM * animEval;
			float topLeft = (animateAmount * cos(elapsedTime)) + BOTTOM * animEval * 0.8f;
			positions[0] = GetScreenPos() + olc::vf2d{ 0, topRight };
			positions[3] = GetScreenPos() + olc::vf2d{ RIGHT, topLeft };
		}
		else 
		{
			deathAnimTime = DEATH_ANIM_LENGTH;
		}

		pge->DrawPartialWarpedDecal(spriteSheet->Decal(), positions, olc::vi2d{ cellX * FRAME_SIZE, cellY * FRAME_SIZE }, 
			olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, (actionTokens > 0 ? olc::WHITE : olc::GREY));

		delete[] positions;
	}

	void SetSpriteIndex(int x, int y)
	{
		cellX = x; 
		cellY = y;
	}

	Character(olc::Renderable* spriteSheet) { this->spriteSheet = spriteSheet; }
};


struct CharacterTemplate 
{
	std::string name = "";
	int actionPoints = 0;
	
	int respawnTime = 0;
	int hitPoints = 0;
	int attackRange = 0;

	bool randWeapon = false, randArmor = false;
	
	std::string summons = "";
	int summonInterval = 0;

	// Sprite stuff
	int hSprCell = 0, vSprCell = 0;

	// Movement stuff	
	bool diagonalMovement = false;
	bool moveRandom = false;
	bool canOverlap = false;
	int fleeRange = 0;

	// Write JSON to file
	const static void WriteToJson(std::vector<CharacterTemplate>& items, std::string fileName = "Data/characterTemplates.json")
	{
		std::ofstream o(fileName);

		for (auto& item : items)
		{
			json j;

			j["name"] = item.name;
			j["ap"] = item.actionPoints;
			j["rt"] = item.respawnTime;
			j["hp"] = item.hitPoints;
			j["attRange"] = item.attackRange;
			j["randW"] = item.randWeapon;
			j["randA"] = item.randArmor;
			j["summons"] = item.summons;
			j["summonInt"] = item.summonInterval;
			j["hCell"] = item.hSprCell;
			j["vCell"] = item.vSprCell;
			j["overlap"] = item.canOverlap;
			j["movDiag"] = item.diagonalMovement;
			j["movRand"] = item.moveRandom;
			j["fleeRange"] = item.fleeRange;

			//std::cout << j << std::endl;
			o << j << std::endl;
		}

		o.close();
	}

	// Read a JSON file
	const static void LoadJsonData(std::vector<CharacterTemplate>& items, std::string fileName = "Data/characterTemplates.json")
	{
		std::ifstream fs;
		fs.open(fileName);

		if (fs.is_open() == false)
		{
			std::cout << "No file found." << std::endl;
			return;
		}

		std::cout << "Found file. ";

		while (fs.eof() == false)
		{
			std::string content;
			CharacterTemplate item;

			std::getline(fs, content);

			if (content.empty() == false)
			{
				auto j = json::parse(content);

				item.name = j.at("name");
				item.actionPoints = j.at("ap");
				item.respawnTime = j.at("rt");
				item.hitPoints = j.at("hp");
				item.attackRange = j.at("attRange");
				item.randWeapon = j.at("randW");
				item.randArmor = j.at("randA");
				item.summons = j.at("summons");
				item.summonInterval = j.at("summonInt");
				item.hSprCell = j.at("hCell");
				item.vSprCell = j.at("vCell");
				item.canOverlap = j.at("overlap");
				item.diagonalMovement = j.at("movDiag");
				item.moveRandom = j.at("movRand");
				item.fleeRange = j.at("fleeRange");

				items.push_back(item);
			}

			content.clear();
		}

		fs.close();

		std::cout << "Characters loaded." << std::endl;
	}
};

const static void GetCharacterFromTemplate(Character* c, const CharacterTemplate& _template)
{
	c->SetSpriteIndex(_template.hSprCell, _template.vSprCell);
	c->SetMaxTokens(_template.actionPoints);
	c->health.SetValue(_template.hitPoints);
	c->name = _template.name;
	c->canMoveDiagonally = _template.diagonalMovement;
	c->canOverlap = _template.canOverlap;
	c->moveRandom = _template.moveRandom;
	c->summonsCharacter = _template.summons;
	c->summonInterval = _template.summonInterval;
	c->respawnTime = _template.respawnTime;

	if (_template.randArmor) c->inv.AddItem(Item::GetRandomArmor());
	if (_template.randWeapon) c->inv.AddItem(Item::GetRandomWeapon());
}

#endif
