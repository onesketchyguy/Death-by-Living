#pragma once
#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <vector>
#include <string>

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
	// The name of this item
	std::string name = "Generic Item";
	// The key value for this item. IE damage, healing, etc.
	int keyValue = 1;
	// The number of uses this item has left
	int durValue = 1;
	/// The type of item this is
	std::string type = NO_USE_ITEM_TYPE;

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

	const static void WriteToJson(std::vector<Item>& items, std::string fileName = "Data/items.json");
	const static void LoadJsonData(std::vector<Item>& items, std::string fileName = "Data/items.json");
	const static Item GetWeapon(int quality, int level);
	const static Item GetRandomWeapon(int qualityCap = 100);
	const static Item GetRandomArmor(int qualityCap = 100);
	const static Item GetRandomHealing();
	const static Item GetRandomItem(int qualityCap = 100);
};

//void RunItemsTestCase() 
//{
//	std::cout << "<------ Starting test case" << std::endl;
//
//	std::cout << "- Creating and loading items list" << std::endl;
//	std::vector<Item> items;
//	Item::LoadJsonData(items);
//
//	std::cout << "- Generating new item" << std::endl;
//	const char* itemType = WEAPON_ITEM_TYPE;
//	Item i = Item::GetRandomItem();
//
//	std::cout << "- Saving new item to list" << std::endl;
//	items.push_back(i);
//	Item::WriteToJson(items);
//
//	std::cout << "- Printing items" << std::endl;
//	for (auto& item : items)
//	{
//		std::cout << item.ToString() << std::endl;
//	}
//
//	std::cout << "<------ Ended test case" << std::endl;
//}

#endif
