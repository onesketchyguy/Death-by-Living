#pragma once
#ifndef CHEST_H
#define CHEST_H

#include <vector>
#include "../lib/olcPixelGameEngine.h"
#include "inventorySystem.h"
#include "items.h"

class ChestObject
{
private:
	std::vector<Item> items{};
	olc::Renderable* inventoryUI = nullptr;

public:
	olc::vi2d pos{ 0, 0 };
	int itemRarityCap = 100;
	int itemCount = 3;

	void Update(olc::PixelGameEngine* pge)
	{
		// Draw chest
		pge->DrawPartialDecal(pos, olc::vi2d{ 16, 16 }, inventoryUI->Decal(), olc::vi2d{ 16 * 4,16 * 1 }, olc::vi2d{16, 16});

		// Draw items if we have some
	}

	void Initialize(olc::PixelGameEngine* pge, olc::Renderable* inventoryUI)
	{
		this->inventoryUI = inventoryUI;

		// Add all items
		for (int i = 0; i < itemCount; i++) items.push_back(Item::GetRandomItem(itemRarityCap));
	}
};

#endif // CHEST_H