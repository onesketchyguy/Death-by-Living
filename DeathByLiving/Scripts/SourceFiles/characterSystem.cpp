#include "../characterSystem.h"
#include "../tools/audioSystem.h"
//#include "../items.h"

olc::vi2d Character::GetScreenPos() { return olc::vi2d{ pos.x * drawScaleX, pos.y * drawScaleY }; }

olc::vi2d Character::GetScreenPos(int x, int y) { return olc::vi2d{ x * drawScaleX, y * drawScaleY }; }

void Character::DealDamage(int damage)
{
	if (inv.GetArmor().name != Item::NULL_ITEM.name)
	{
		if (inv.GetArmor().durValue > 0)
		{
			damage -= inv.GetArmor().keyValue;
			inv.GetArmor().durValue -= 1;

			if (damage < 0) damage = 0;
		}

		if (inv.GetArmor().durValue <= 0)
		{
			inv.GetArmor().name = Item::NULL_ITEM.name;
			std::cout << "ARMOR BROKE!" << std::endl;
		}
	}

	if (damage > 0)
	{
		health.ModifyValue(-damage);
		//AudioSystem::GetInstance()->PlayClip("Data/Hit_Hurt.wav");
	}
}

void Character::StartTurn()
{
	actionTokens = maxTokens;
	aiThinking = AI_THINK_TIME;
}

void Character::HandleTurn(olc::PixelGameEngine* pge, float elapsedTime)
{
	if (name == "Player")
	{
		int moveX = 0;
		int moveY = 0;

		if (pge->GetKey(olc::Key::LEFT).bPressed) moveX = -1;
		if (pge->GetKey(olc::Key::RIGHT).bPressed) moveX = 1;
		if (pge->GetKey(olc::Key::UP).bPressed)	moveY = -1;
		if (pge->GetKey(olc::Key::DOWN).bPressed) moveY = 1;

		if (moveX != 0 || moveY != 0) MoveDir(moveX, moveY);

		if (inv.GetUsedItem() != nullptr)
		{
			if (actionTokens >= DRINK_POTION_COST)
			{
				health.ModifyValue(inv.GetUsedItem()->keyValue);
				inv.GetUsedItem()->durValue--;

				if (inv.GetUsedItem()->durValue > 0) inv.GetUsedItem()->researched = true;

				actionTokens -= DRINK_POTION_COST;
			}

			inv.ClearUseItem();
		}
	}
	else // Handle AI Stuff
	{
		// FIXME: Implement AI
		if (aiThinking <= 0.0f)
		{
			thinkingTime = 0;
			aiThinking = AI_THINK_TIME + ((rand() % 100) / 100.0f);
			// FIXME: use character.moveRand

			if (canMoveDiagonally)
			{
				int xDir = rand() % 100 > 50 ? 1 : -1;
				int yDir = rand() % 100 > 50 ? 1 : -1;

				MoveDir(xDir, yDir);
			}
			else
			{
				int ran = rand() % 200;

				int xDir = ran < 100 ? (ran < 50 ? 1 : -1) : 0;
				int yDir = ran > 100 ? (ran > 150 ? 1 : -1) : 0;

				MoveDir(xDir, yDir);
			}
		}
		else
		{
			aiThinking -= elapsedTime;

			std::string thinkingImage = "";
			for (int i = 0; i < aiThinkingChar; i++) thinkingImage += '.';

			if (thinkingTime >= THINK_CHAR_INTERVAL)
			{
				if (aiThinkingChar > 2) aiThinkingChar = 0;
				else aiThinkingChar++;

				thinkingTime = 0;
			}
			else thinkingTime += elapsedTime;

			pge->DrawStringDecal(GetScreenPos() + olc::vi2d{ drawScaleX / 3, -2 }, thinkingImage, olc::WHITE, olc::vf2d{ 1.0f,1.0f } *0.35f);
		}
	}
}

void Character::EndTurn() { if (name == "Player") health.ModifyValue(-1, false); }

void Character::MoveDir(int xDir, int yDir)
{
	if (actionTokens > 0)
	{
		if (pos.x + xDir >= mapSize.x || pos.x + xDir < 0 ||
			pos.y + yDir >= mapSize.y || pos.y + yDir < 0 ||
			(xDir == 0 && yDir == 0)) return;

		actionTokens -= MOVE_COST;

		pos.x += xDir;
		pos.y += yDir;

		//AudioSystem::GetInstance()->PlayClip("Data/Move.wav");
	}
}

void Character::Draw(olc::PixelGameEngine* pge, float deltaTime)
{
	if (name == "Player")
	{
		if (pge->GetKey(olc::Key::CTRL).bHeld && pge->GetKey(olc::Key::I).bPressed) inv.AddItem(Item::GetRandomItem());
		else if (pge->GetKey(olc::Key::I).bPressed) inv.SetDrawing(pge, !inv.GetDrawing());

		/*if (pge->GetKey(olc::Key::CTRL).bHeld && pge->GetKey(olc::Key::NP_SUB).bPressed) DealDamage(1);
		if (pge->GetKey(olc::Key::CTRL).bHeld && pge->GetKey(olc::Key::NP_ADD).bPressed) health.ModifyValue(1);*/
	}

	const float RIGHT = static_cast<float>(drawScaleX);
	const float BOTTOM = static_cast<float>(drawScaleY);
	const float TOP = animateAmount * sin(elapsedTime);

	elapsedTime += animationSpeed * deltaTime;
	if (elapsedTime >= TAU) elapsedTime = 0.0f;

	olc::vf2d* positions = new olc::vf2d[4]{
		GetScreenPos() + olc::vf2d{ 0, TOP },
		GetScreenPos() + olc::vf2d{ 0, BOTTOM },
		GetScreenPos() + olc::vf2d{ RIGHT, BOTTOM },
		GetScreenPos() + olc::vf2d{ RIGHT, TOP },
	};

	if (health.Empty())
	{
		if (deathAnimTime > 0.0f)
		{
			deathAnimTime -= deathAnimSpeed * deltaTime;
		}
		else
		{
			deathAnimTime = 0.0f;
			delete[] positions;
			return;
		}

		float animEval = 1 - (deathAnimTime / DEATH_ANIM_LENGTH);

		float topRight = (animateAmount * sin(elapsedTime)) + BOTTOM * animEval;
		float topLeft = (animateAmount * cos(elapsedTime)) + BOTTOM * animEval * 0.8f;
		positions[0] = GetScreenPos() + olc::vf2d{ 0, topRight };
		positions[3] = GetScreenPos() + olc::vf2d{ RIGHT, topLeft };
	}
	else
	{
		deathAnimTime = DEATH_ANIM_LENGTH;
	}

	pge->DrawPartialWarpedDecal(spriteSheet->Decal(), positions, olc::vi2d{ cellX * FRAME_SIZE, cellY * FRAME_SIZE },
		olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, (actionTokens > 0 ? olc::WHITE : olc::GREY));

	delete[] positions;
}

void Character::SetSpriteIndex(int x, int y)
{
	cellX = x;
	cellY = y;
}

void Character::GenerateFromTemplate(const CharacterTemplate& _template)
{
	this->SetSpriteIndex(_template.hSprCell, _template.vSprCell);
	this->SetMaxTokens(_template.actionPoints);
	this->health.SetValue(_template.hitPoints);
	this->name = _template.name;
	this->canMoveDiagonally = _template.diagonalMovement;
	this->canOverlap = _template.canOverlap;
	this->moveRandom = _template.moveRandom;
	this->summonsCharacter = _template.summons;
	this->summonInterval = _template.summonInterval;
	this->respawnTime = _template.respawnTime;

	if (_template.randArmor) this->inv.AddItem(Item::GetRandomArmor());
	if (_template.randWeapon) this->inv.AddItem(Item::GetRandomWeapon());
}

Character::Character(olc::Renderable* spriteSheet, const CharacterTemplate& _template, int x, int y)
{
	this->pos = olc::vi2d{ x , y };
	this->spriteSheet = spriteSheet;
	GenerateFromTemplate(_template);
}