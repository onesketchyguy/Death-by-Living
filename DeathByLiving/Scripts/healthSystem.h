#pragma once
#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "../lib/olcPixelGameEngine.h"
#include "inventorySystem.h"
#include "items.h"
#include "utility.h"

const float SHOW_HEALTH_DIFF_TIME = 1.0f;

struct HealthContainer 
{
private:
	int health;
	int prevHealth;
	

	float showTime = 0.0f;

public:
	void ModifyValue(int mod) 
	{
		prevHealth = health;

		health += mod;
		showTime = SHOW_HEALTH_DIFF_TIME;
	}

	void SetValue(int value) { prevHealth = health = value; }

	bool Empty() { return health <= 0;  }

	void Draw(olc::PixelGameEngine* pge, int x, int y, float deltaTime) 
	{
		int pixelWidth = util::GetStringWidth(std::to_string(prevHealth)) * 4;

		x -= pixelWidth / 2;

		if (health > 0) 
		{
			pge->DrawStringDecal(olc::vi2d{ x, y }, std::to_string(prevHealth), (prevHealth == health) ? olc::WHITE : olc::GREY);

			if (prevHealth != health)
			{
				std::string display = ((health - prevHealth > 0) ?  "+" : "") + std::to_string(health - prevHealth);
				pge->DrawStringDecal(olc::vi2d{ x + pixelWidth + 8, y }, display, prevHealth > health ? olc::RED : olc::YELLOW, olc::vf2d{ 1.0f,1.0f } *0.5f);

				showTime -= deltaTime;

				if (showTime <= 0.0f)
				{
					prevHealth = health;
					showTime = 0.0f;
				}
			}
		}
		else
		{
			pge->DrawStringDecal(olc::vi2d{ x, y }, "DEAD");
		}
	}

	HealthContainer(int startHealth) { health = startHealth; prevHealth = startHealth; }
};

#endif