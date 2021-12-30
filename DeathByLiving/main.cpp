#include <iostream>

#define OLC_PGE_APPLICATION
#include "lib/olcPixelGameEngine.h"
#include "Scripts/main.h"
//#include "../tools/MapEditor/project.h"
#include "Scripts/settings.h"

bool AUDIO_ENABLED = true;

int main() 
{
/*
#ifdef NDEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // NDEBUG
#ifndef NDEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif // !NDEBUG
*/

	try
	{
		SettingsData settings;
		SettingsData::LoadJsonData(settings);

		int width = settings.windowWidth / settings.pixelSize;
		int height = settings.windowHeight / settings.pixelSize;

		AUDIO_ENABLED = settings.soundEnabled;

		std::cout << "AUDIO ENABLED: " << std::to_string(AUDIO_ENABLED) << std::endl;

		Game application;
		if (application.Construct(width, height, settings.pixelSize, settings.pixelSize))
			application.Start();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl; // information from error printed
		
		system("pause");
		return 3;
	}

	return 0;
}
