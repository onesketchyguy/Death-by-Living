#pragma once
#ifndef CHARACTER_SYSTEM_H
#define CHARACTER_SYSTEM_H

#include "items.h"
#include "healthSystem.h"
#include "../lib/olcPixelGameEngine.h"


struct Character 
{
private:
	float elapsedTime = 0;
public:
	olc::vi2d pos{0, 0};
	int turnOrder = 0;
	Item& armor;
	Item& weapon;
	HealthContainer health{START_HEALTH, armor};

	const int FRAME_SIZE = 24;

	int drawScaleX = 16;
	int drawScaleY = 16;	

	olc::Renderable* spriteSheet;

	void EndTurn() 
	{
		health.ModifyValue(-1);
	}

	void Draw(olc::PixelGameEngine* pge, float deltaTime) 
	{
		const float RIGHT = static_cast<float>(drawScaleX);
		const float BOTTOM = static_cast<float>(drawScaleY);
		const float TOP = 2.0f * sin(elapsedTime);

		elapsedTime += 5.0f * deltaTime;
		if (elapsedTime >= 2 * 3.14159) elapsedTime = 0.0f;

		const olc::vf2d* positions = new olc::vf2d[4]{
			pos + olc::vf2d{ 0, TOP },
			pos + olc::vf2d{ 0, BOTTOM },
			pos + olc::vf2d{ RIGHT, BOTTOM }, 
			pos + olc::vf2d{ RIGHT, TOP },
		};

		pge->DrawPartialWarpedDecal(spriteSheet->Decal(), positions, olc::vi2d{ 0,0 }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::GREY);

		delete[] positions;
	}

	Character(olc::Renderable* spriteSheet, Item& armor, Item& weapon) : armor{armor}, weapon{weapon}
	{
		this->spriteSheet = spriteSheet;
	}
};


#endif