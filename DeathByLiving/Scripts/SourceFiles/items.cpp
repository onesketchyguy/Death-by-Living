#include <fstream>
#include "../items.h"
#include "../../lib/json.hpp"

// for convenience
using json = nlohmann::json;

const Item Item::NULL_ITEM{ "NULLITEM", 0, 0, "NULL" };

const Item Item::GetWeapon(int quality, int level)
{
	Item i;
	i.type = WEAPON_ITEM_TYPE;

	int NAMES_LENGTH = 5;
	std::string* names = new std::string[NAMES_LENGTH]
	{
		"Wooden sword", "Bronze sword", "Iron sword", "Steel sword", "Mythril sword"
	};

	const int QUALITY_LEVELS = 7;
	std::string* qualityNames = new std::string[QUALITY_LEVELS]
	{
		"Horrible ", "Worn ", "", "Nice ", "Great ", "Fantastic ", "Other worldly "
	};

	i.spriteCellX = 0;
	i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);

	level + 1;
	i.name = qualityNames[quality] + names[level];
	i.durValue = (level * 2) + rand() % (1 + quality * 3);
	i.keyValue = level + rand() % (1 + quality * 2);

	delete[] names;
	delete[] qualityNames;

	return i;
}

const Item Item::GetRandomWeapon(int qualityCap)
{
	int NAMES_LENGTH = 5;

	std::map<int, std::string> rarity
	{
		{10, "Horrible "},
		{21, "Worn "},
		{25, ""},
		{21, "Nice "},
		{14, "Great "},
		{ 7, "Fantastic "},
		{ 5, "Other worldly "}
	};

	int value = rand() % qualityCap;

	int quality = 0;
	for (auto key : rarity)
	{
		value -= key.first;
		if (value <= 0) break;

		quality++;
	}

	int level = rand() % NAMES_LENGTH;

	return GetWeapon(quality, level);
}

const Item Item::GetRandomArmor(int qualityCap)
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
const Item Item::GetRandomItem(int qualityCap)
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
		return GetRandomArmor(qualityCap);
		break;
	case 1:
		return GetRandomWeapon(qualityCap);
		break;
	case 2:
		return GetRandomHealing();
		break;
	default:
		qualityNames = new std::string[QUALITY_LEVELS]{ "Horrible ", "Worn ", "", "Nice ", "Great ", "Fantastic ", "Other worldly " };
		names = new std::string[NAMES_LENGTH]{ "stick", "sword", "rock", "lief", "thing" };
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

// Write JSON to file
const void Item::WriteToJson(std::vector<Item>& items, std::string fileName)
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
const void Item::LoadJsonData(std::vector<Item>& items, std::string fileName)
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