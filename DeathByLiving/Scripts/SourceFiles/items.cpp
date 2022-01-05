#include <fstream>
#include "../items.h"
#include "../../lib/json.hpp"

// for convenience
using json = nlohmann::json;

const Item Item::NULL_ITEM{ "NULLITEM", 0, 0, "NULL" };
std::vector<std::string> eqQuality{ "Horrible ", "Worn ", "", "Nice ", "Great ", "Fantastic ", "Other worldly " };

const int WEAPON_NAMES_LENGTH = 5;
std::string weaponNames[WEAPON_NAMES_LENGTH]
{
	"Wooden", "Bronze", "Iron", "Steel", "Mythril"
};

const int ARMOR_NAMES_LENGTH = 6;
std::string armorNames[ARMOR_NAMES_LENGTH]
{
	"Cloth", "Leather", "Bronze", "Iron", "Steel", "Mythril"
};

const int GetRarity(int rarityCount, const int qualityCap)
{
	std::vector<int> rarity;

	if (rarityCount == 0) { std::cout << "ERROR: Could not create rarity map." << std::endl; return 0; }

	int modAmount = 100 / rarityCount;
	int modRemainder = 100 % rarityCount;

	for (int i = 0; i < rarityCount; i++)
	{
		rarity.push_back(modAmount + modRemainder);
		modRemainder = 0;
	}

	int value = rand() % qualityCap;
	int r = 0;
	for (r = 0; r < rarityCount; r++)
	{
		value -= rarity.at(r);
		if (value <= 0) break;
	}

	return r;
}

const Item Item::GetWeapon(int quality, int level)
{
	Item i;
	i.type = WEAPON_ITEM_TYPE;

	i.spriteCellX = 0;
	i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);

	level += 1;
	i.name = eqQuality.at(quality) + weaponNames[level] + " sword";
	i.durValue = (level * 2) + rand() % (1 + quality * 3);
	i.keyValue = level + rand() % (1 + quality * 2);

	return i;
}

const Item Item::GetRandomWeapon(int qualityCap)
{
	int level = rand() % WEAPON_NAMES_LENGTH;
	return GetWeapon(GetRarity(static_cast<int>(eqQuality.size()), qualityCap), level);
}

const Item Item::GetArmor(int quality, int level)
{
	Item i;
	i.type = ARMOR_ITEM_TYPE;

	i.name = eqQuality.at(quality) + armorNames[level] + " armor";
	i.durValue = level + rand() % (1 + quality * 3);
	i.keyValue = level + rand() % (1 + quality * 2);

	i.spriteCellX = 2;
	i.spriteCellY = 1 + (rand() % ITEM::MAX_CELL_Y);

	return i;
}

const Item Item::GetRandomArmor(int qualityCap)
{
	int level = rand() % ARMOR_NAMES_LENGTH;
	return GetArmor(GetRarity(static_cast<int>(eqQuality.size()), qualityCap), level);
}

const Item Item::GetRandomHealing()
{
	Item i;
	i.type = HEALING_ITEM_TYPE;

	const int NAMES_LENGTH = 5;
	std::string names[NAMES_LENGTH]
	{
		"red", "blue", "green", "purple","grey"
	};

	const int QUALITY_LEVELS = 7;
	std::string qualityNames[QUALITY_LEVELS]
	{
		"Ugly ", "Curious ", "Smelly ", "Absurd ", "Bubbling ", "Curious ", "Enticing "
	};

	const int SIZE_NAMES = 3;
	std::string sizeNames[SIZE_NAMES]
	{
		"small ", "", "large ",
	};

	int quality = rand() % QUALITY_LEVELS;
	int level = rand() % NAMES_LENGTH;
	i.durValue = 1 + rand() % ITEM::MAX_CELL_Y; // Potion size
	i.name = qualityNames[quality] + sizeNames[i.durValue - 1] + names[level] + " potion";
	quality += 1;
	do i.keyValue = (quality - (rand() % (quality * 2))) * 2; while (i.keyValue == 0);

	int r = 220 + (rand() % 36);
	const int s = 150;
	if (i.name.find("blue") != std::string::npos) i.SetColor(s, s, r);
	else if (i.name.find("red") != std::string::npos) i.SetColor(r, s, s);
	else if (i.name.find("green") != std::string::npos) i.SetColor(s, r, s);
	else if (i.name.find("purple") != std::string::npos) i.SetColor(r, s, r);

	i.spriteCellX = 1;
	i.spriteCellY = i.durValue;

	return i;
}

///  FIXME: This funciton is for test purposes ONLY!
const Item Item::GetRandomItem(int qualityCap)
{
	Item i;

	const int NAMES_LENGTH = 3;
	std::string names[NAMES_LENGTH]{ "bag", "key", "scroll" };
	int level = rand() % NAMES_LENGTH;

	i.type = NO_USE_ITEM_TYPE;
	i.name = names[level];

	i.keyValue = 0;
	i.durValue = 1;

	i.spriteCellX = 3;
	i.spriteCellY = 1 + level;

	int t = rand() % ITEM_TYPES_LENGTH;
	switch (t)
	{
	case 0: return GetRandomArmor(qualityCap);
	case 1: return GetRandomWeapon(qualityCap);
	case 2: return GetRandomHealing();
	default: 
		return i;
	}
}

const std::string Item::GetInfo() 
{
	const char* ARMOR_TYPE = ARMOR_ITEM_TYPE;
	const char* WEAPON_TYPE = WEAPON_ITEM_TYPE;
	const char* HEALING_TYPE = HEALING_ITEM_TYPE;
	
	std::string itemInfo = "UNDEFINED";

	if (this->type == ARMOR_TYPE)
	{
		itemInfo = this->name + "\n" +
			std::to_string(this->keyValue) + "def\n" +
			std::to_string(this->durValue) + "dur\n";
	}

	if (this->type == WEAPON_TYPE)
	{
		itemInfo = this->name + "\n" +
			std::to_string(this->keyValue) + "dam\n" +
			std::to_string(this->durValue) + "dur\n";
	}

	if (this->type == HEALING_TYPE)
	{
		itemInfo = this->name + "\n" +
			std::to_string(this->durValue) + "uses\n";

		if (this->researched) itemInfo += std::to_string(this->keyValue) + "hp\n";
	}

	return itemInfo;
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
		j["r"] = item.researched;

		//std::cout << j << std::endl;
		o << j << std::endl;
	}

	o.close();
}

// Read a JSON file
const void Item::LoadJsonData(std::vector<Item>& items, std::string fileName)
{
	std::ifstream fs(fileName);

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
			item.researched = j.at("r");

			items.push_back(item);
		}

		content.clear();
	}

	fs.close();

	std::cout << "Items loaded." << std::endl;
}