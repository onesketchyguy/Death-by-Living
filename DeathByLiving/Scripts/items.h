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

struct Item
{
	// The name of this item
	std::string name = "Generic Item";
	// The key value for this item. IE damage, healing, etc.
	short keyValue = 1;
	// The number of uses this item has left
	int durValue = 1;
	/// The type of item this is
	std::string type = NO_USE_ITEM_TYPE;

	Item() = default;
	Item(const char* name, short keyValue, int durValue, const char* type)
	{
		this->name = name;
		this->keyValue = keyValue;
		this->durValue = durValue;
		this->type = type;
	}

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
	const static void LoadJsonData(std::vector<Item>& grades, std::string fileName = "Data/items.json")
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

				grades.push_back(item);
			}

			content.clear();
		}

		fs.close();

		std::cout << "Items loaded." << std::endl;
	}

	const static Item GetRandomItem();
};

///  FIXME: This funciton is for test purposes ONLY!
const Item Item::GetRandomItem()
{
	Item i;
	
	const int NAMES_LENGTH = 5;
	std::string* names = new std::string[NAMES_LENGTH]
	{
		"stick", "sword", "rock", "lief", "leather"
	};

	i.name = names[rand() % NAMES_LENGTH];

	int t = rand() % ITEM_TYPES_LENGTH;

	switch (t)
	{
	case 0:
		i.type = ARMOR_ITEM_TYPE;
		break;
	case 1:
		i.type = WEAPON_ITEM_TYPE;
		break;
	case 2:
		i.type = HEALING_ITEM_TYPE;
		break;
	default:
		i.type = NO_USE_ITEM_TYPE;
		break;
	}

	i.keyValue = rand() % 10;
	i.durValue = rand() % 10;

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
