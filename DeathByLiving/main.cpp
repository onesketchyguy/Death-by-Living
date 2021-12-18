#include <iostream>

#define OLC_PGE_APPLICATION
#include "lib/olcPixelGameEngine.h"
#include "Scripts/main.h"
#include "Scripts/settings.h"

int main() 
{
	SettingsData settings;
	SettingsData::LoadJsonData(settings);

	int width = settings.windowWidth / settings.pixelSize;
	int height = settings.windowHeight / settings.pixelSize;

	// FIXME: Prevent sound from being used when settings disables it

	Game application;
	if (application.Construct(width, height, settings.pixelSize, settings.pixelSize))
		application.Start();

	return 0;
}
