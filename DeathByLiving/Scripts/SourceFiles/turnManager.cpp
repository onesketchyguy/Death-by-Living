#include "../turnManager.h"
#include "../tools/layerManager.h"

TurnManager::TurnManager()
{
	uiSheet = new olc::Renderable();
	uiSheet->Load(util::GetCWD("Data/ui.png").c_str());

	characterSheet = new olc::Renderable();
	characterSheet->Load(util::GetCWD("Data/characterSheet.png").c_str());
}

TurnManager::~TurnManager()
{
	delete characterSheet;
	delete uiSheet;
}

void TurnManager::AddCharacter(olc::PixelGameEngine* pge, const CharacterTemplate& charTemplate, int x, int y)
{
	Character c(characterSheet, charTemplate, x, y);

	if (c.name == "Player") c.inv.Initialize(pge, uiSheet, true, pge->ScreenWidth(), pge->ScreenHeight());

	c.turnOrder = 0;
	characters.push_back(c);
}

void TurnManager::ClearCharacters()
{
	characters.clear();
	lastTurnIndex = 0;
	currentTurnIndex = -1;
}

void TurnManager::SetTurnOrder()
{
	if (characters.empty())
	{
		std::cout << "ERROR: Unable to set turn order! No characters exist!" << std::endl;
		return;
	}

	std::cout << "Setting turns... ";

	bool* turnOrder = new bool[characters.size()](false);
	int r;

	for (int i = 0; i < characters.size(); i++)
	{
		do
		{
			r = rand() % characters.size();

			if (turnOrder[r] == false)
			{
				turnOrder[r] = true;
				characters.at(i).turnOrder = r + 1;
			}
		} while (characters.at(i).turnOrder == 0);
	}

	std::cout << "Done." << std::endl;

	delete[] turnOrder;
}

int TurnManager::GetNextCharacterTurn()
{
	int index = -1;

	while (1)
	{
		int lowest = -1;
		for (int i = 0; i < characters.size(); i++)
		{
			auto c = characters.at(i);
			if (c.turnOrder > lastTurnIndex)
			{
				if (index == -1 || c.turnOrder < lowest)
				{
					index = i;
					lowest = c.turnOrder;
				}
			}
		}

		if (index != -1) break;
		else if (lastTurnIndex != 0) lastTurnIndex = 0;
		else
		{
			std::cout << "ERROR: Could not return next character turn." << std::endl;
			return -1;
		}
	}

	return index;
}

void TurnManager::CycleTurn()
{
	if (currentTurnIndex != -1) characters.at(currentTurnIndex).EndTurn();
	currentTurnIndex = GetNextCharacterTurn();

	lastTurnIndex = characters.at(currentTurnIndex).turnOrder;
	characters.at(currentTurnIndex).StartTurn();

	if (characters.at(currentTurnIndex).health.Empty() && characters.size() > 1) CycleTurn();
}

void TurnManager::Update(olc::PixelGameEngine* pge, float elapsedTime)
{
	// Turn implementation
	if (currentTurnIndex == -1)
	{
		CycleTurn();
		return;
	}

	if (characters.at(currentTurnIndex).actionTokens <= 0) CycleTurn();

	//// DRAW ENEMY HEALTH BAR
	//{
	//	const int DRAW_SIZE = 5;

	//	for (int i = 0; i < current.health.GetValue(); i++)
	//	{
	//		float x = static_cast<float>(DRAW_SIZE * (i % 6));
	//		float y = static_cast<float>(DRAW_SIZE * (i / 6));
	//		bool isFilledToken = current.health.GetValue() > i;

	//		pge->DrawPartialDecal(current.GetScreenPos() + olc::vf2d{ x, - 10 + y },
	//			olc::vi2d{ DRAW_SIZE, DRAW_SIZE }, uiSheet->Decal(),
	//			olc::vi2d{ 16 * 4, 0 }, olc::vi2d{ 16,16 }, (isFilledToken ? olc::WHITE : olc::VERY_DARK_GREY));
	//	}
	//}

	for (int i = 0; i < characters.size(); i++) 
	{
		auto& c = characters.at(i);
		bool isPlayer = c.name == "Player";
		bool isCurrentTurn = i == currentTurnIndex;

		if (isCurrentTurn) // Handle current character turn
		{
			c.HandleTurn(pge, elapsedTime);

			if (isPlayer && c.inv.GetHolding() == false)
			{
				// Handle end turn early
				if (pge->GetKey(olc::SPACE).bReleased) CycleTurn();

				// Draw movement // FIXME: Draw attack positions
				for (int i = 0; i < 9; i++)
				{
					if (i == 4 || (c.canMoveDiagonally == false && i % 2 == 0)) continue;

					int x = (i % 3) - 1;
					int y = (i / 3) - 1;

					olc::vi2d screenPos = c.GetScreenPos(x + c.pos.x, y + c.pos.y);
					olc::vi2d drawScale = olc::vi2d{ 16, 16 };
					bool mouseOver = (pge->GetMouseY() > screenPos.y && pge->GetMouseY() <= screenPos.y + drawScale.y) && (pge->GetMouseX() > screenPos.x && pge->GetMouseX() <= screenPos.x + drawScale.x);

					if (mouseOver && pge->GetMouse(0).bReleased)
					{
						c.MoveDir(x, y);
						break;
					}

					pge->DrawPartialDecal(screenPos, drawScale, uiSheet->Decal(), olc::vi2d{ 0,0 }, olc::vi2d{ 16,16 }, olc::Pixel{ (uint8_t)255,(uint8_t)255, (uint8_t)255, mouseOver ? (uint8_t)192 : (uint8_t)64 });
				}
			}
		}

		pge->SetDrawTarget(LayerManager::GetLayer(LAYER_MASK::CHARACTER));
		pge->Clear(olc::BLANK);
		c.Draw(pge, elapsedTime);
		pge->SetDrawTarget(nullptr);

		if (isPlayer) // Draw player specific UI stuff
		{
			pge->SetDrawTarget(LayerManager::GetLayer(LAYER_MASK::UI));
			pge->Clear(olc::BLANK);

			c.health.Draw(pge, pge->ScreenWidth() >> 1, 0, elapsedTime);

			if (isCurrentTurn)
			{
				const int DRAW_SIZE = 10;

				// Draw available actionTokens
				for (int i = 0; i < c.GetMaxTokens(); i++)
				{
					float x = static_cast<float>(DRAW_SIZE * (i % 6));
					float y = static_cast<float>(DRAW_SIZE * (i / 6));
					bool isFilledToken = c.actionTokens > i;

					pge->DrawPartialDecal(olc::vf2d{ x, y }, olc::vi2d{ DRAW_SIZE, DRAW_SIZE }, uiSheet->Decal(),
						olc::vi2d{ 16 * 4, 0 }, olc::vi2d{ 16,16 }, (isFilledToken ? olc::WHITE : olc::VERY_DARK_GREY));
				}

				c.inv.Draw(pge);
			}

			pge->SetDrawTarget(nullptr);
		}
	}
}