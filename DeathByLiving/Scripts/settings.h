#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include "../lib/json.hpp"

// for convenience
using json = nlohmann::json;

struct SettingsData 
{
	bool soundEnabled = true;
	int pixelSize = 3;
	int windowWidth = 1024;
	int windowHeight = 720;

	// Write JSON to file
	const static void WriteToJson(SettingsData& settings, std::string fileName = "Data/settings.json")
	{
		std::ofstream o(fileName);	

		json j;

		j["soundEnabled"] = settings.soundEnabled;
		j["pixelSize"] = settings.pixelSize;
		j["windowWidth"] = settings.windowWidth;
		j["windowHeight"] = settings.windowHeight;

		//std::cout << j << std::endl;
		o << j << std::endl;

		o.close();
	}

	// Read a JSON file
	const static bool LoadJsonData(SettingsData& settings, std::string fileName = "Data/settings.json")
	{
		std::ifstream fs;
		fs.open(fileName);

		if (fs.is_open() == false)
		{
			std::cout << "No settings file found. Returning default settings." << std::endl;
			return false;
		}

		std::cout << "Found file. ";
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

		content.clear();		

		std::cout << "Settings loaded." << std::endl;

		return true;
	}
};

#endif