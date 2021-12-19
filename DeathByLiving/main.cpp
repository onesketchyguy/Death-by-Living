#include <iostream>

#define OLC_PGE_APPLICATION
#include "lib/olcPixelGameEngine.h"
#include "Scripts/main.h"
#include "Scripts/settings.h"

bool AUDIO_ENABLED = true;

int main() 
{
	SettingsData settings;
	SettingsData::LoadJsonData(settings);

	int width = settings.windowWidth / settings.pixelSize;
	int height = settings.windowHeight / settings.pixelSize;

	AUDIO_ENABLED = settings.soundEnabled;

	Game application;
	if (application.Construct(width, height, settings.pixelSize, settings.pixelSize))
		application.Start();

	return 0;
}
