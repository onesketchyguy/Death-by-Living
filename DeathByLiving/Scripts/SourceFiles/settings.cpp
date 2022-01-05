#include "../settings.h"
#include "../../lib/json.hpp"
#include <fstream>
#include "../utility.h"

// for convenience
using json = nlohmann::json;

// Write JSON to file
const void SettingsData::WriteToJson(SettingsData& settings, std::string fileName)
{
	std::ofstream o(util::GetCWD(fileName.c_str()));

	json j;
	j["soundEnabled"] = settings.soundEnabled;
	j["pixelSize"] = settings.pixelSize;
	j["windowWidth"] = settings.windowWidth;
	j["windowHeight"] = settings.windowHeight;
	o << j << std::endl;

	o.close();
}

// Read a JSON file
const bool SettingsData::LoadJsonData(SettingsData& settings, std::string fileName)
{
	std::ifstream fs(util::GetCWD(fileName.c_str()));

	if (fs.is_open() == false)
	{
		std::cout << "No settings file found. Returning default settings." << std::endl;
		return false;
	}

	std::cout << "Found file... ";
	std::string content;

	while (fs.eof() == false)
	{
		std::string lineContent;
		std::getline(fs, lineContent);

		content += lineContent;
	}

	fs.close();

	if (content.empty() == false)
	{
		auto j = json::parse(content);

		settings.soundEnabled = j.at("soundEnabled");
		settings.pixelSize = j.at("pixelSize");
		settings.windowWidth = j.at("windowWidth");
		settings.windowHeight = j.at("windowHeight");
	}

	std::cout << "Settings loaded." << std::endl;

	return true;
}