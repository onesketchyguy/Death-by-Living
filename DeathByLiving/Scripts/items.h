#pragma once
#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <fstream>
#include "../lib/json.hpp"

// for convenience
using json = nlohmann::json;

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

	std::string ToString() 
	{
		return name + " " + std::to_string(keyValue) + " " + std::to_string(durValue) + " " + type;
	}

	// Write JSON to file
	const static void WriteToJson(std::vector<Item>& items, std::string fileName = "Data/items.json")
	{
		std::ofstream o(fileName);

		for (auto& item : items)
		{
			json j;

			j["name"] = item.name;
			j["key"] = item.keyValue;
			j["dur"] = item.durValue;
			j["t"] = item.type;

			//std::cout << j << std::endl;
			o << j << std::endl;
		}

		o.close();
	}

	// Read a JSON file
	const static void LoadJsonData(std::vector<Item>& items, std::string fileName = "Data/items.json")
	{
		std::ifstream fs;
		fs.open(fileName);

		if (fs.is_open() == false)
		{
			std::cout << "No file found." << std::endl;
			return;
		}

		std::cout << "Found file. ";

		while (fs.eof() == false)
		{
			std::string content;
			Item item;

			std::getline(fs, content);

			if (content.empty() == false)
			{
				auto j = json::parse(content);

				item.name = j.at("name");
				item.keyValue = j.at("key");
				item.durValue = j.at("dur");
				item.type = j.at("t");

				items.push_back(item);
			}

			content.clear();
		}

		fs.close();

		std::cout << "Items loaded." << std::endl;
	}

	const static Item GetRandomWeapon();
	const static Item GetRandomArmor();
	const static Item GetRandomHealing();
	const static Item GetRandomItem();
};

const Item Item::NULL_ITEM{ "NULLITEM", 0, 0, "NULL"};

const Item Item::GetRandomWeapon()
{
	Item i;
	i.type = WEAPON_ITEM_TYPE;

	int NAMES_LENGTH = 5;
	std::string* names = new std::string[NAMES_LENGTH]
	{
		"Stick", "Bronze sword", "Iron sword", "Steel sword", "Mythril sword"
	};

	const int QUALITY_LEVELS = 7;
	std::string* qualityNames = new std::string[QUALITY_LEVELS]
	{
		"Horrible ", "Worn ", "", "Nice ", "Great ", "Fantastic ", "Other worldly "
	};

	int quality = rand() % QUALITY_LEVELS;
	int level = rand() % NAMES_LENGTH;

	i.spriteCellX = 0;
	i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);

	i.name = qualityNames[quality] + names[level];
	i.durValue = (level * 2) + rand() % (1 + quality * 3);
	i.keyValue = level + rand() % (1 + quality * 2);


	delete[] names;
	delete[] qualityNames;

	return i;
}

const Item Item::GetRandomArmor()
{
	Item i;
	i.type = ARMOR_ITEM_TYPE;

	int NAMES_LENGTH = 5;
	std::string* names = new std::string[NAMES_LENGTH]
	{
		"Cloth", "Leather", "Iron", "Steel", "Mythril"
	};

	const int QUALITY_LEVELS = 7;
	std::string* qualityNames = new std::string[QUALITY_LEVELS]
	{
		"Horrible ", "Worn ", "", "Nice ", "Great ", "Fantastic ", "Other worldly "
	};

	int quality = rand() % QUALITY_LEVELS;
	int level = rand() % NAMES_LENGTH;
	i.name = qualityNames[quality] + names[level] + " armor";
	i.durValue = level + rand() % (1 + quality * 3);
	i.keyValue = level + rand() % (1 + quality * 2);

	i.spriteCellX = 2;
	i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);

	delete[] names;
	delete[] qualityNames;

	return i;
}

const Item Item::GetRandomHealing()
{
	Item i;
	i.type = HEALING_ITEM_TYPE;

	int NAMES_LENGTH = 5;
	std::string* names = new std::string[NAMES_LENGTH]
	{
		"red", "blue", "green", "purple","grey"
	};

	const int QUALITY_LEVELS = 7;
	std::string* qualityNames = new std::string[QUALITY_LEVELS]
	{
		"Ugly ", "Curious ", "Smelly ", "Absurd ", "Fascinating ", "Curious ", "Enticing "
	};

	int quality = rand() % QUALITY_LEVELS;
	int level = rand() % NAMES_LENGTH;
	i.name = qualityNames[quality] + names[level] + " potion";
	quality += 1;
	i.durValue = 1 + rand() % 2;	
	do i.keyValue = (quality - (rand() % (quality * 2))) * 2; while (i.keyValue == 0);

	i.spriteCellX = 1;
	i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);

	delete[] names;
	delete[] qualityNames;

	return i;
}

///  FIXME: This funciton is for test purposes ONLY!
const Item Item::GetRandomItem()
{
	Item i;
	
	int NAMES_LENGTH = 5;
	std::string* names = nullptr;

	const int QUALITY_LEVELS = 7;
	std::string* qualityNames = nullptr;

	int quality = rand() % QUALITY_LEVELS;
	int level = rand() % NAMES_LENGTH;


	int t = rand() % ITEM_TYPES_LENGTH;

	switch (t)
	{
	case 0:
		return GetRandomArmor();
		break;
	case 1:
		return GetRandomWeapon();
		break;
	case 2:
		return GetRandomHealing();
		break;
	default:
		qualityNames = new std::string[QUALITY_LEVELS] { "Horrible ", "Worn ", "", "Nice ", "Great ", "Fantastic ", "Other worldly " };
		names = new std::string[NAMES_LENGTH] { "stick", "sword", "rock", "lief", "thing" };
		i.type = NO_USE_ITEM_TYPE;

		i.name = names[level];

		i.keyValue = 0;
		i.durValue = 0;

		i.spriteCellX = 3;
		i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);
		break;
	}

	delete[] names;
	delete[] qualityNames;

	return i;
}

void RunItemsTestCase() 
{
	std::cout << "<------ Starting test case" << std::endl;

	std::cout << "- Creating and loading items list" << std::endl;
	std::vector<Item> items;
	Item::LoadJsonData(items);

	std::cout << "- Generating new item" << std::endl;
	const char* itemType = WEAPON_ITEM_TYPE;
	Item i = Item::GetRandomItem();

	std::cout << "- Saving new item to list" << std::endl;
	items.push_back(i);
	Item::WriteToJson(items);

	std::cout << "- Printing items" << std::endl;
	for (auto& item : items)
	{
		std::cout << item.ToString() << std::endl;
	}

	std::cout << "<------ Ended test case" << std::endl;
}

#endif
