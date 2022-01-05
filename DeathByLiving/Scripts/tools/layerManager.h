#pragma once
#ifndef LAYER_MANAGER_H
#define LAYER_MANAGER_H

#include "../../lib/olcPixelGameEngine.h"

enum class LAYER_MASK : uint8_t
{
	WORLD = 2,
	CHARACTER = 1,
	UI = 0,
};

class LayerManager
{
public:
	static uint8_t GetLayer(LAYER_MASK m);
	static void GenerateLayers(olc::PixelGameEngine* pge);
};

#endif