#pragma once
#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "../lib/olcPixelGameEngine.h"
#include "inventorySystem.h"
#include "items.h"

const int START_HEALTH = 20;

struct HealthContainer 
{
private:
	int health;

	Item& armor;

public:
	void ModifyValue(int mod, const bool overrideArmor = false) 
	{
		if (mod < 0 && !overrideArmor && armor.name != Item::NULL_ITEM.name)
		{
			if (armor.durValue > 0) 
			{
				mod += armor.keyValue;
				if (mod > 0) mod = 0;

				armor.durValue -= 1;
			}
			else 
			{
				armor.name = Item::NULL_ITEM.name;
				std::cout << "ARMOR BROKE!" << std::endl;
			}
		}

		health += mod;
	}

	bool Empty() { return health <= 0;  }

	void Draw(olc::PixelGameEngine* pge, int x, int y) 
	{
		pge->DrawStringDecal(olc::vi2d{x, y}, std::to_string(health));
	}

	HealthContainer(int startHealth, Item& armor) : armor{armor}
	{
		health = startHealth;
	}
};

#endif