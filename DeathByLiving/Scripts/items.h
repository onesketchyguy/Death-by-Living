#pragma once
#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <vector>
#include <string>
#include "../lib/olcPixelGameEngine.h"

#define ARMOR_ITEM_TYPE "Armor";
#define WEAPON_ITEM_TYPE "Weapon";
#define HEALING_ITEM_TYPE "Healing";
#define NO_USE_ITEM_TYPE "Useless";
#define ITEM_TYPES_LENGTH 3;

namespace ITEM 
{
	const int MAX_CELL_X = 4;
	const int MAX_CELL_Y = 3;
}

struct Item
{
private:
	// WARNING! THESE ARE NOT SAVED!
	uint8_t colR = 255;
	uint8_t colG = 255;
	uint8_t colB = 255;
	// *****************************
public:
	// The name of this item
	std::string name = "Generic Item";
	// The key value for this item. IE damage, healing, etc.
	int keyValue = 1;
	// The number of uses this item has left
	int durValue = 1;
	/// The type of item this is
	std::string type = NO_USE_ITEM_TYPE;
	// We may decide to hide some information from the user
	bool researched = false;

	int spriteCellY = 0;
	int spriteCellX = 0;

	Item() = default;
	Item(const char* name, short keyValue, int durValue, const char* type)
	{
		this->name = name;
		this->keyValue = keyValue;
		this->durValue = durValue;
		this->type = type;
	}

	const static Item NULL_ITEM;

	std::string ToString() { return name + " " + std::to_string(keyValue) + " " + std::to_string(durValue) + " " + type; }

	const void SetColor(uint8_t r, uint8_t g, uint8_t b) { colR = r; colG = g; colB = b; }
	const olc::Pixel GetColor() { return olc::Pixel{ colR, colG, colB, 255 }; }
	const std::string GetInfo();

	const static void WriteToJson(std::vector<Item>& items, std::string fileName = "Data/items.json");
	const static void LoadJsonData(std::vector<Item>& items, std::string fileName = "Data/items.json");
	const static Item GetWeapon(int quality, int level);
	const static Item GetRandomWeapon(int qualityCap = 100);
	const static Item GetArmor(int quality, int level);
	const static Item GetRandomArmor(int qualityCap = 100);
	const static Item GetRandomHealing();
	const static Item GetRandomItem(int qualityCap = 100);
};

#endif
