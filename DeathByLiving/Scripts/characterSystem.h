#pragma once
#ifndef CHARACTER_SYSTEM_H
#define CHARACTER_SYSTEM_H

#include "items.h"
#include "healthSystem.h"
#include "../lib/olcPixelGameEngine.h"


class Character 
{
private:
	float elapsedTime = 0;
	const float TAU = 2 * 3.14159;

	int drawScaleX = 16;
	int drawScaleY = 16;

	int cellX = 0;
	int cellY = 0;

	const int FRAME_SIZE = 24;

	float animationSpeed = 4.0f;
	float animateDeathSpeed = 8.0f;
	float animateAmount = 1.5f;

	float height = 1.0f;

	olc::Renderable* spriteSheet = nullptr;

public:
	olc::vi2d pos{0, 0};
	int turnOrder = 0;
	Item& armor;
	Item& weapon;
	HealthContainer health{ START_HEALTH, armor };

	olc::vi2d GetScreenPos()
	{
		return olc::vi2d{ pos.x * drawScaleX, pos.y * drawScaleY };
	}

	void Attack(int damage)
	{
		health.ModifyValue(-damage);
	}

	void EndTurn() 
	{
		health.ModifyValue(-1);
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
			if (height > 0.0f)
			{
				height -= animateDeathSpeed * deltaTime;
			}
			else 
			{
				height = 0.0f;
				delete[] positions;
				return;
			}

			positions[0] = pos + olc::vf2d{ 0, BOTTOM * (1 - height)};
			positions[3] = pos + olc::vf2d{ RIGHT, BOTTOM * (1 - height) };
		}
		else 
		{
			height = 1.0f;
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