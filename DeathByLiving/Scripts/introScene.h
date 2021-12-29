#pragma once

#include <iostream>
#include "../lib/olcPixelGameEngine.h"

class Intro 
{
	/* DESCRIPTION OF USAGE
	* 
	* 1. Define an object pointer:
	* 
		Intro* intro = nullptr;
	* 
	* 2. Create that object in your PGE OnUserCreate
	* 
		intro = new Intro(this);
	* 
	* 3. Place this at the top of your PGE Update loop:
	* 	
		if (intro != nullptr && intro->Update(fElapsedTime) == true)
		{
			delete intro;
			intro = nullptr;
			return true;
		} else if (intro != nullptr) return true;
	* 
	*/

private:
	float logoTime = 1.0f; // Time to actually show the logo(s)

	float evalTime = 0.0f;

	olc::Renderable* introImage;
	olc::PixelGameEngine* pge;

	const olc::vf2d drawScale{ 0.25f, 0.25f };
	olc::vi2d drawPoint{0, 0};

	bool finished = false;

public:
	Intro(olc::PixelGameEngine* pge) : pge{pge}
	{
		introImage = new olc::Renderable();
		introImage->Load("Data/olc_logo.png");

		drawPoint = olc::vi2d{ static_cast<int>(introImage->Sprite()->width * (drawScale.x - 0.1f)) >> 1,
			static_cast<int>((pge->ScreenHeight() >> 1) - introImage->Sprite()->height * drawScale.y) };
	}

	~Intro() { delete introImage; }

	bool Update(float elapsedTime)
	{
		if (finished) return true;

		pge->Clear(olc::BLACK);

		float eval = sin(5.3f * evalTime);

		if (eval >= 0.9f && logoTime > 0.0f)
		{
			logoTime -= elapsedTime;
		} else evalTime += elapsedTime;

		olc::Pixel color = olc::WHITE * eval;

		pge->DrawDecal(drawPoint, introImage->Decal(), drawScale, color);

		if (eval <= 0.0f && logoTime <= 0.0f) finished = true;

		return false;
	}
};