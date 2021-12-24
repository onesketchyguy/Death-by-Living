#pragma once
#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include <iostream>
#include "characterSystem.h"

struct TurnManager 
{
private:
	std::vector<Character*> characters;
	Character* currentTurn = nullptr;
	int lastTurnIndex = 0;

public:
	void AddCharacter(Character* character) { character->turnOrder = 0; characters.push_back(character); }

	void ClearCharacters() 
	{
		characters.clear(); 
		lastTurnIndex = 0; 
		currentTurn = nullptr;
	}

	void SetTurnOrder() 
	{
		std::vector<bool> turnAvailable;
		for (Character* c : characters) { c->turnOrder = 0; turnAvailable.push_back(true); }

		for (Character* c : characters)
		{
			do
			{
				int t = rand() % characters.size();

				if (turnAvailable.at(t)) 
				{
					c->turnOrder = t + 1;
					turnAvailable.at(t) = false;
				}

			} while (c->turnOrder == 0);
		}

		turnAvailable.clear();
	}

	Character* GetNextCharacterTurn() 
	{
		Character* lowest = nullptr;
		for (Character* c : characters)
		{
			if (c->turnOrder > lastTurnIndex)
			{
				if (lowest == nullptr || lowest != nullptr && c->turnOrder < lowest->turnOrder) lowest = c;
			}
		}

		return lowest;
	}

	void CycleTurn() 
	{
		if (currentTurn != nullptr) currentTurn->EndTurn();
		currentTurn = GetNextCharacterTurn();

		if (currentTurn == nullptr)
		{
			lastTurnIndex = 0;
			currentTurn = GetNextCharacterTurn();
		}

		lastTurnIndex = currentTurn->turnOrder;
		currentTurn->StartTurn();

		if (currentTurn->health.Empty() && characters.size() > 1) CycleTurn();
	}

	void Update(olc::PixelGameEngine* pge, float elapsedTime)
	{
		for (auto& c : characters) c->Draw(pge, elapsedTime);

		// Turn implementation
		auto currentTurn = GetCurrentCharacterTurn();
		if (currentTurn == nullptr) CycleTurn();
		else if (currentTurn->actionTokens <= 0) CycleTurn();
		else currentTurn->HandleTurn(pge, elapsedTime);
	}

	Character* GetCurrentCharacterTurn()
	{		
		return currentTurn;
	}
};

#endif