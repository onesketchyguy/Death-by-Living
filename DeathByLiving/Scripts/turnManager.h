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
	olc::Renderable* uiSheet = nullptr;

public:
	void SetUISheet(olc::Renderable* uiSheet) { this->uiSheet = uiSheet; }

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
		else 
		{
			currentTurn->HandleTurn(pge, elapsedTime);

			if (currentTurn->name == "Player")
			{
				const int DRAW_SIZE = 10;

				// Draw available actionTokens
				for (size_t i = 0; i < currentTurn->GetMaxTokens(); i++)
				{
					float x = static_cast<float>(DRAW_SIZE * (i % 6));
					float y = static_cast<float>(DRAW_SIZE * (i / 6));
					bool isFilledToken = currentTurn->actionTokens > i;

					pge->DrawPartialDecal(olc::vf2d{ x, y }, olc::vi2d{ DRAW_SIZE, DRAW_SIZE }, uiSheet->Decal(),
						olc::vi2d{ 16 * 4, 0 }, olc::vi2d{ 16,16 }, (isFilledToken ? olc::WHITE : olc::VERY_DARK_GREY));
				}

				// FIXME: draw movement/attack positions
				for (size_t i = 0; i < 9; i++)
				{
					if (i == 4) continue;

					int x = i % 3;
					int y = i / 3;

					x += currentTurn->pos.x - 1;
					y += currentTurn->pos.y - 1;

					pge->DrawPartialDecal(currentTurn->GetScreenPos(x, y), olc::vi2d{ 16,16 }, uiSheet->Decal(), olc::vi2d{ 0,0 }, olc::vi2d{ 16,16 });
				}
			}
		}
	}

	Character* GetCurrentCharacterTurn()
	{		
		return currentTurn;
	}
};

#endif