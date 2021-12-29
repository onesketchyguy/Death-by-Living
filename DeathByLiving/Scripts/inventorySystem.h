#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "../lib/olcPixelGameEngine.h"
#include "items.h"

class Inventory 
{
private:
	olc::Renderable* inventoryUI = nullptr;

	const int FRAME_SIZE = 16;

	const int CELL_SIZE = 16;
	const int HORIZONTAL_CELLS = 4;
	const int VERTICAL_CELLS = 2;

	const olc::vi2d DRAW_SIZE = olc::vi2d{ CELL_SIZE, CELL_SIZE };
	const int SLOT_TOP_OFFSET = 8;
	const int SLOT_SIDE_PADDING = 1;

	const char* ARMOR_TYPE = ARMOR_ITEM_TYPE;
	const char* WEAPON_TYPE = WEAPON_ITEM_TYPE;
	const char* HEALING_TYPE = HEALING_ITEM_TYPE;
	const char* USELESS_TYPE = NO_USE_ITEM_TYPE;

	olc::vi2d windowPosition = olc::vi2d{0,0};

	std::vector<Item> items;
	Item equippedArmor{ "NULLITEM", 0, 0, ARMOR_TYPE };
	Item equippedWeapon{ "NULLITEM", 0, 0, WEAPON_TYPE };

	Item holdingItem = Item::NULL_ITEM;

	bool changed = false;
	bool draw = false;
	uint32_t drawLayer = 0;
	bool droppingItem = false;	
	Item* output = nullptr;

	void DrawHoldingItem(olc::PixelGameEngine* pge);

	void DrawSlot(olc::vi2d pos, Item& item, olc::PixelGameEngine* pge, std::string& tooltip);

public:
	int GetEmptySlot();
	bool AddItem(Item newItem);
	void SetDrawing(olc::PixelGameEngine* pge, bool value);
	bool GetDrawing() { return draw; }

	Item* GetUsedItem() { return output; }
	void ClearUseItem() 
	{ 
		if (output->durValue <= 0) output->name = Item::NULL_ITEM.name;
		output = nullptr; 
	};

	Item& GetArmor() { return equippedArmor; }
	Item& GetWeapon() { return equippedWeapon; }

	void SetPosition(int x, int y)
	{
		windowPosition.x = x - ((SLOT_SIDE_PADDING * 2) + CELL_SIZE * static_cast<int>(HORIZONTAL_CELLS + 1.25f));
		windowPosition.y = y - (SLOT_SIDE_PADDING + SLOT_TOP_OFFSET + (CELL_SIZE * VERTICAL_CELLS));
	}

	void Update(olc::PixelGameEngine* pge);

	void Initialize(olc::PixelGameEngine* pge, olc::Renderable* inventoryUI);

	~Inventory() = default;
	Inventory() = default;
};

#endif
