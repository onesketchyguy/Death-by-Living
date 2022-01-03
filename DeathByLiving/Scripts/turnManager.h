#pragma once
#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <iostream>
#include "characterSystem.h"

struct TurnManager 
{
private:
	std::vector<Character> characters;
	int currentTurnIndex = -1;
	int lastTurnIndex = 0;
	olc::Renderable* uiSheet = nullptr;
	olc::Renderable* characterSheet = nullptr;

public:
	TurnManager();
	~TurnManager();

public:

	void AddCharacter(olc::PixelGameEngine* pge, const CharacterTemplate& charTemplate, int x = 0, int y = 0);
	void ClearCharacters();
	void SetTurnOrder();
	int GetNextCharacterTurn();
	void CycleTurn();
	void Update(olc::PixelGameEngine* pge, float elapsedTime);
};

#endif