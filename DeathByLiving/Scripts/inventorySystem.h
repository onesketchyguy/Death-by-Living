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

	const int CELL_SIZE = 12;
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

	void DrawHoldingItem(olc::PixelGameEngine* pge)
	{
		olc::vi2d pos = pge->GetMousePos();


		if (holdingItem.type == ARMOR_TYPE) 
		{
			pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE * 2, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE });
		}

		if (holdingItem.type == WEAPON_TYPE)
		{
			pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ 0, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE });
		}

		if (holdingItem.type == HEALING_TYPE)
		{
			pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE });
		}
	}

	void DrawSlot(olc::vi2d pos, Item& item, olc::PixelGameEngine* pge, std::string& tooltip)
	{		
		olc::vi2d mousePos = pge->GetMousePos();
		bool mouseOver = (mousePos.y > pos.y && mousePos.y < pos.y + CELL_SIZE &&
			mousePos.x > pos.x && mousePos.x < pos.x + CELL_SIZE);

		olc::Pixel drawColor = mouseOver ? olc::WHITE : olc::GREY;		

		pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE,0 }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, drawColor);		

		if (item.type == ARMOR_TYPE)
		{
			pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE * 2, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::Pixel(255,255,255,20));
		}

		if (item.type == WEAPON_TYPE)
		{
			pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ 0, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::Pixel(255, 255, 255, 20));
		}


		if (item.name != Item::NULL_ITEM.name)
		{
			std::string itemInfo;

			if (item.type == ARMOR_TYPE)
			{
				itemInfo = item.name + "\n" +
					std::to_string(item.keyValue) + "def\n" +
					std::to_string(item.durValue) + "dur\n";

				pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE * 2, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE });
			}

			if (item.type == WEAPON_TYPE)
			{
				itemInfo = item.name + "\n" +
					std::to_string(item.keyValue) + "dam\n" +
					std::to_string(item.durValue) + "dur\n";

				pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ 0, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE });
			}

			if (item.type == HEALING_TYPE)
			{
				itemInfo = item.name + "\n" +
					std::to_string(item.keyValue) + "healing\n" +
					std::to_string(item.durValue) + "uses\n";

				pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE });
			}

			if (mouseOver) 
			{
				if (pge->GetMouse(0).bHeld)
				{
					if (holdingItem.name == Item::NULL_ITEM.name)
					{
						holdingItem = item;
						item = Item::NULL_ITEM;
					}
				}
				else 
				{
					tooltip = itemInfo;
				}
			}
		}
		else if (mouseOver)
		{
			if (pge->GetMouse(0).bReleased)
			{
				if (holdingItem.name != Item::NULL_ITEM.name && holdingItem.type != ARMOR_TYPE && holdingItem.type != WEAPON_TYPE &&
					item.type != ARMOR_TYPE && item.type != WEAPON_TYPE)
				{
					item = holdingItem;
					holdingItem = Item::NULL_ITEM;
				}
			}
		}
	}

public:
	int GetEmptySlot()
	{
		int i = 0;
		for (auto& item : items)
		{
			if (item.name == Item::NULL_ITEM.name) return i;

			i++;
		}

		return -1;
	}

	bool AddItem(Item newItem)
	{
		if (newItem.type == ARMOR_TYPE)
		{
			if (equippedArmor.name == Item::NULL_ITEM.name)
			{
				equippedArmor = newItem;
			}

			return equippedArmor.name == newItem.name;
		}

		if (newItem.type == WEAPON_TYPE)
		{
			if (equippedWeapon.name == Item::NULL_ITEM.name)
			{
				equippedWeapon = newItem;
			}

			return equippedWeapon.name == newItem.name;
		}

		int slot = GetEmptySlot();

		if (slot != -1)
		{
			items[slot] = newItem;

			return true;
		}
		else
		{
			std::cout << "Failed to add item, no free slot." << std::endl;
			return false; // Unable to add item to inventory
		}
	}

	void SetDrawing(bool value, olc::PixelGameEngine* pge) { draw = value; pge->EnableLayer(drawLayer, value); }
	bool GetDrawing() { return draw; }

	Item& GetArmor() { return equippedArmor; }
	Item& GetWeapon() { return equippedWeapon; }	

	void SetPosition(int x, int y)
	{
		windowPosition.x = x - ((SLOT_SIDE_PADDING * 2) + CELL_SIZE * (HORIZONTAL_CELLS + 1.25f));
		windowPosition.y = y - (SLOT_SIDE_PADDING + SLOT_TOP_OFFSET + (CELL_SIZE * VERTICAL_CELLS));
	}

	void Update(olc::PixelGameEngine* pge)
	{
		if (draw == false) return;

		if (equippedArmor.type != ARMOR_TYPE) equippedArmor.type = ARMOR_TYPE;
		if (equippedWeapon.type != WEAPON_TYPE) equippedWeapon.type = WEAPON_TYPE;

		const float RIGHT = static_cast<float>((SLOT_SIDE_PADDING * 2) + CELL_SIZE * (HORIZONTAL_CELLS + 1.25f));
		const float BOTTOM = static_cast<float>(SLOT_SIDE_PADDING + SLOT_TOP_OFFSET + (CELL_SIZE * VERTICAL_CELLS));

		const olc::vf2d* positions = new olc::vf2d[4]{
			windowPosition, 
			windowPosition + olc::vf2d{ 0, BOTTOM },
			windowPosition + olc::vf2d{ RIGHT, BOTTOM }, 
			windowPosition + olc::vf2d{ RIGHT, 0 }, 
		};
		
		pge->SetDrawTarget(drawLayer);

		pge->DrawPartialWarpedDecal(inventoryUI->Decal(), positions, olc::vi2d{ FRAME_SIZE*2,0 }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::GREY);
		pge->DrawStringDecal(windowPosition + olc::vf2d{ 8, 4 }, "INVENTORY", olc::WHITE, olc::vf2d{0.5,0.5});

		std::string tooltip = "";
		std::string startToolTip = "";
		int toolTipX = 0, toolTipY = 0;

		for (int x = 0; x < HORIZONTAL_CELLS; x++)
		{			
			for (int y = 0; y < VERTICAL_CELLS; y++)
			{
				startToolTip = tooltip;

				olc::vi2d pos = windowPosition + olc::vi2d{ SLOT_SIDE_PADDING + (x * CELL_SIZE), SLOT_TOP_OFFSET + (y * CELL_SIZE) };
				Item* item = &items[y * HORIZONTAL_CELLS + x];

				DrawSlot(pos, *item, pge, tooltip);

				if (startToolTip != tooltip)
				{
					toolTipX = x;
					toolTipY = y;

					startToolTip = tooltip;
				}
			}			
		}

		startToolTip = tooltip;

		DrawSlot(windowPosition + olc::vf2d{ (HORIZONTAL_CELLS + 0.25f) * CELL_SIZE, 
			static_cast<float>(SLOT_TOP_OFFSET)}, equippedArmor, pge, tooltip);
		DrawSlot(windowPosition + olc::vf2d{ (HORIZONTAL_CELLS + 0.25f) * CELL_SIZE, 
			static_cast<float>(SLOT_TOP_OFFSET + CELL_SIZE)}, equippedWeapon, pge, tooltip);

		if (holdingItem.name != Item::NULL_ITEM.name) 
		{
			DrawHoldingItem(pge);

			// If we tried to release the item, but it's still in our hands
			if (pge->GetMouse(0).bReleased)
			{
				AddItem(holdingItem);
				holdingItem = Item::NULL_ITEM;
			}
		}

		if (startToolTip != tooltip)
		{
			toolTipX = -1;
			toolTipY = 0;
		}

		if (tooltip.empty() == false) 
		{
			toolTipX += 1;

			olc::vf2d drawPos = windowPosition + olc::vi2d{ 
				SLOT_SIDE_PADDING + (toolTipX * CELL_SIZE), 
				SLOT_TOP_OFFSET + (toolTipY * CELL_SIZE) };

			if (drawPos.x + (CELL_SIZE * 2) >= pge->ScreenWidth()) drawPos.x = windowPosition.x + SLOT_SIDE_PADDING;

			pge->DrawStringDecal(olc::vf2d{-0.05f, 0.05f} + drawPos, tooltip, olc::BLACK, olc::vf2d{ 0.5f, 0.5f });
			pge->DrawStringDecal(drawPos, tooltip, olc::WHITE, olc::vf2d{ 0.5f, 0.5f });
		}

		delete[] positions;
		pge->SetDrawTarget(nullptr);
	}

public: // Constructors
	~Inventory() { delete inventoryUI; }
	Inventory() = default;

	void Initialize(olc::PixelGameEngine * pge)
	{
		inventoryUI = new olc::Renderable();
		inventoryUI->Load("Data/ui.png");

		for (size_t i = 0; i < HORIZONTAL_CELLS * VERTICAL_CELLS; i++)
		{
			items.push_back(Item::NULL_ITEM);
		}

		drawLayer = pge->CreateLayer();
	}
};

#endif