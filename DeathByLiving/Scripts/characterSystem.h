#pragma once
#ifndef CHARACTER_SYSTEM_H
#define CHARACTER_SYSTEM_H

#include "healthSystem.h"
#include "../lib/olcPixelGameEngine.h"
#include "../lib/json.hpp"
#include "inventorySystem.h"

// for convenience
using json = nlohmann::json;

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

class Character 
{
private: // Action stuff
	const int DRINK_POTION_COST = 2;
	const int DO_ATTACK_COST = 3;
	const int MOVE_COST = 1;

	int maxTokens = 3;
	int bonusTokens = 0;

public: // Map stuff
	olc::vi2d mapSize{ 21, 14 };

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

	const void RewardBonusToken(const int& bonus) { bonusTokens += bonus; };
	const int& GetMaxTokens() { return maxTokens + bonusTokens; }
	const void SetMaxTokens(int m) { maxTokens = m; }
	int actionTokens = 0;

	olc::vi2d GetScreenPos();
	olc::vi2d GetScreenPos(int x, int y);

	void DealDamage(int damage);
	void StartTurn();
	void HandleTurn(olc::PixelGameEngine* pge, float elapsedTime);
	void EndTurn();
	void MoveDir(int xDir, int yDir);
	void Draw(olc::PixelGameEngine* pge, float deltaTime);
	void SetSpriteIndex(int x, int y);
	void GenerateFromTemplate(const CharacterTemplate& _template);

	Character(olc::Renderable* spriteSheet, const CharacterTemplate& _template, int x = 0, int y = 0);
};

#endif
