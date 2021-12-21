#pragma once
#ifndef CHARACTER_SYSTEM_H
#define CHARACTER_SYSTEM_H

#include "items.h"
#include "healthSystem.h"
#include "../lib/olcPixelGameEngine.h"


class Character 
{
private:
	const int START_TURN_TOKENS = 3;

private: // Animation stuff
	float elapsedTime = 0;
	const float TAU = 2 * 3.14159;

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

public:
	olc::vi2d pos{0, 0};
	int turnOrder = 0;
	Item& armor;
	Item& weapon;
	HealthContainer health{ START_HEALTH };

	int actionTokens = 0;

	olc::vi2d GetScreenPos()
	{
		return olc::vi2d{ pos.x * drawScaleX, pos.y * drawScaleY };
	}

	void DealDamage(int damage)
	{
		if (armor.name != Item::NULL_ITEM.name)
		{
			if (armor.durValue > 0)
			{
				damage += armor.keyValue;
				armor.durValue -= 1;
			}

			if (armor.durValue <= 0)
			{
				armor.name = Item::NULL_ITEM.name;
				std::cout << "ARMOR BROKE!" << std::endl;
			}
		}

		health.ModifyValue(-damage);
	}

	void StartTurn() 
	{
		actionTokens = START_TURN_TOKENS;
	}

	void EndTurn() 
	{
		health.ModifyValue(-1);
	}

	void MoveDir(int xDir, int yDir)
	{
		if (actionTokens > 0) 
		{
			actionTokens -= MOVE_COST;

			pos.x += xDir;
			pos.y += yDir;

			if (actionTokens <= 0) 
			{
				EndTurn();
			}
		}

	}

	void Draw(olc::PixelGameEngine* pge, float deltaTime) 
	{
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

			positions[0] = GetScreenPos() + olc::vf2d{ 0, (animateAmount * sin(elapsedTime)) + BOTTOM * animEval };
			positions[3] = GetScreenPos() + olc::vf2d{ RIGHT, (animateAmount * cos(elapsedTime)) + BOTTOM * animEval*0.8f };
		}
		else 
		{
			deathAnimTime = DEATH_ANIM_LENGTH;
		}

		pge->DrawPartialWarpedDecal(spriteSheet->Decal(), positions, olc::vi2d{ cellX * FRAME_SIZE, cellY * FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::GREY);

		delete[] positions;
	}

	void SetSpriteIndex(int x, int y)
	{
		cellX = x; 
		cellY = y;
	}

	Character(olc::Renderable* spriteSheet, Item& armor, Item& weapon, int cellX = 0, int cellY = 0) : armor{armor}, weapon{weapon}
	{		
		this->spriteSheet = spriteSheet;
		SetSpriteIndex(cellX, cellY);
	}
};


#endif