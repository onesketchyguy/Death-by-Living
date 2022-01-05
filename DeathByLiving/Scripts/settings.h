#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

struct SettingsData 
{
	bool soundEnabled = true;
	int pixelSize = 3;
	int windowWidth = 1024;
	int windowHeight = 720;

	// Write JSON to file
	const static void WriteToJson(SettingsData& settings, std::string fileName = "Data/settings.json");
	// Read a JSON file
	const static bool LoadJsonData(SettingsData& settings, std::string fileName = "Data/settings.json");
};

#endif