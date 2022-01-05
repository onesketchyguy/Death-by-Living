#include "../inventorySystem.h"
#include "../utility.h"
#include "../button.h"
#include "../tools/layerManager.h"

// Private functions
void Inventory::DrawHoldingItem(olc::PixelGameEngine* pge)
{
	olc::vi2d pos = pge->GetMousePos();

	pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(),
		olc::vi2d{ FRAME_SIZE * holdingItem.spriteCellX, FRAME_SIZE * holdingItem.spriteCellY },
		olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, holdingItem.GetColor());
}

void Inventory::DrawSlot(olc::vi2d pos, Item& item, olc::PixelGameEngine* pge, std::string& tooltip)
{
	olc::vi2d mousePos = pge->GetMousePos();
	bool mouseOver = (mousePos.y > pos.y && mousePos.y < pos.y + CELL_SIZE &&
		mousePos.x > pos.x && mousePos.x < pos.x + CELL_SIZE);

	olc::Pixel drawColor = mouseOver ? olc::WHITE : olc::GREY;

	pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE,0 }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, drawColor);

	if (item.type == ARMOR_TYPE)
	{
		pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ FRAME_SIZE * 2, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::Pixel(255, 255, 255, 20));
	}

	if (item.type == WEAPON_TYPE)
	{
		pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(), olc::vi2d{ 0, FRAME_SIZE }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::Pixel(255, 255, 255, 20));
	}


	if (item.name != Item::NULL_ITEM.name)
	{
		std::string itemInfo = item.GetInfo();
		olc::Pixel col = item.GetColor();

		if (pge->GetMouse(1).bReleased && mouseOver && item.type == HEALING_TYPE) output = &item;

		pge->DrawPartialDecal(pos, DRAW_SIZE, inventoryUI->Decal(),
			olc::vi2d{ FRAME_SIZE * item.spriteCellX, FRAME_SIZE * item.spriteCellY },
			olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, col);

		if (mouseOver)
		{
			if (pge->GetMouse(0).bHeld)
			{
				if (holdingItem.name == Item::NULL_ITEM.name)
				{
					holdingItem = item;
					item = Item::NULL_ITEM;

					//AudioSystem::GetInstance()->PlayClip("Data/Blip_Select2.wav");
				}
			}
			else
			{
				tooltip = itemInfo;
			}
		}
	}
	else if (mouseOver)
	{
		if (pge->GetMouse(0).bReleased && holdingItem.name != Item::NULL_ITEM.name)
		{
			bool isWeapon = holdingItem.type == WEAPON_TYPE;
			bool isArmor = holdingItem.type == ARMOR_TYPE;

			bool isArmorSlot = item.type == ARMOR_TYPE;
			bool isWeaponSlot = item.type == WEAPON_TYPE;

			if (((isArmor && isArmorSlot) || (isWeapon && isWeaponSlot)) ||
				(!isArmor && !isArmorSlot && !isWeapon && !isWeaponSlot))
			{
				item = holdingItem;
				holdingItem = Item::NULL_ITEM;

				//AudioSystem::GetInstance()->PlayClip("Data/Blip_Select.wav");
			}
			else
			{
				AddItem(holdingItem);
				holdingItem = Item::NULL_ITEM;
			}
		}
	}
}

void Inventory::HandleDropItem(olc::PixelGameEngine* pge)
{
	olc::vf2d screenMid = olc::vf2d{ static_cast<float>(pge->ScreenWidth() >> 1), static_cast<float>(pge->ScreenHeight() >> 1) };

	// Draw item
	std::string itemInfo = holdingItem.GetInfo();

	olc::vf2d drawPos = screenMid + olc::vf2d{ 10.0f, -10.0f };
	olc::vf2d itemDrawPos = screenMid + olc::vf2d{ -10.0f, -10.0f };

	// Adjust the position to keep the text on screen
	int delta = static_cast<int>((drawPos.x + (util::GetStringWidth(itemInfo) * 4)) - pge->ScreenWidth());
	if (delta > 0) drawPos.x -= delta;

	delta = static_cast<int>((drawPos.y + (util::GetStringHeight(itemInfo) * 4)) - pge->ScreenHeight());
	if (delta > 0) drawPos.y -= delta;

	pge->DrawStringDecal(olc::vf2d{ -0.05f, 0.05f } + drawPos, itemInfo, olc::BLACK, olc::vf2d{ 0.5f, 0.5f });
	pge->DrawStringDecal(drawPos, itemInfo, olc::WHITE, olc::vf2d{ 0.5f, 0.5f });

	pge->DrawPartialDecal(itemDrawPos, DRAW_SIZE, inventoryUI->Decal(),
		olc::vi2d{ FRAME_SIZE * holdingItem.spriteCellX, FRAME_SIZE * holdingItem.spriteCellY },
		olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, holdingItem.GetColor());

	// Draw buttons
	Button dropButton{ screenMid.x, screenMid.y + 10.0f, 50, 15, 1.0f, "Drop" };
	Button cancelButton{ screenMid.x, screenMid.y + 30.0f, 50, 15, 1.0f, "Cancel" };
	dropButton.Draw(pge, olc::VERY_DARK_GREY, olc::DARK_GREY, olc::WHITE, olc::WHITE);
	cancelButton.Draw(pge, olc::VERY_DARK_GREY, olc::DARK_GREY, olc::WHITE, olc::WHITE);

	if (pge->GetMouse(0).bReleased)
	{
		if (cancelButton.IsColliding(pge->GetMouseX(), pge->GetMouseY()))
		{
			AddItem(holdingItem);
			holdingItem = Item::NULL_ITEM;

			droppingItem = false;
		}
		else if (dropButton.IsColliding(pge->GetMouseX(), pge->GetMouseY()))
		{
			holdingItem = Item::NULL_ITEM;

			//AudioSystem::GetInstance()->PlayClip("Data/Drop_Item.wav");

			droppingItem = false;
		}
	}
}


// Public functions
int Inventory::GetEmptySlot()
{
	int i = 0;
	for (auto& item : items)
	{
		if (item.name == Item::NULL_ITEM.name) return i;

		i++;
	}

	return -1;
}

bool Inventory::AddItem(Item newItem)
{
	if (newItem.type == ARMOR_TYPE)
	{
		if (equippedArmor.name == Item::NULL_ITEM.name)
		{
			equippedArmor = newItem;
		}

		//AudioSystem::GetInstance()->PlayClip("Data/Blip_Select.wav");

		return equippedArmor.name == newItem.name;
	}

	if (newItem.type == WEAPON_TYPE)
	{
		if (equippedWeapon.name == Item::NULL_ITEM.name)
		{
			equippedWeapon = newItem;
		}

		//AudioSystem::GetInstance()->PlayClip("Data/Blip_Select.wav");

		return equippedWeapon.name == newItem.name;
	}

	int slot = GetEmptySlot();

	if (slot != -1)
	{
		items[slot] = newItem;

		//AudioSystem::GetInstance()->PlayClip("Data/Blip_Select.wav");

		return true;
	}
	else
	{
		std::cout << "Failed to add item, no free slot." << std::endl;
		return false; // Unable to add item to inventory
	}
}

void Inventory::SetDrawing(olc::PixelGameEngine* pge, bool value) { draw = value; }

void Inventory::Draw(olc::PixelGameEngine* pge)
{
	if (draw == false) return;
	if (GetUsedItem() != nullptr && GetUsedItem()->name == Item::NULL_ITEM.name) ClearUseItem();

	if (droppingItem)
	{
		HandleDropItem(pge);
		pge->SetDrawTarget(nullptr);
		return;
	}

	if (equippedArmor.type != ARMOR_TYPE) equippedArmor.type = ARMOR_TYPE;
	if (equippedWeapon.type != WEAPON_TYPE) equippedWeapon.type = WEAPON_TYPE;

	const float RIGHT = static_cast<float>((SLOT_SIDE_PADDING * 2) + CELL_SIZE * (HORIZONTAL_CELLS + 1.25f));
	const float BOTTOM = static_cast<float>(SLOT_SIDE_PADDING + SLOT_TOP_OFFSET + (CELL_SIZE * VERTICAL_CELLS));

	const olc::vf2d* positions = new olc::vf2d[4]{
		windowPosition,
		windowPosition + olc::vf2d{ 0, BOTTOM },
		windowPosition + olc::vf2d{ RIGHT, BOTTOM },
		windowPosition + olc::vf2d{ RIGHT, 0 },
	};

	pge->DrawPartialWarpedDecal(inventoryUI->Decal(), positions, olc::vi2d{ FRAME_SIZE * 2,0 }, olc::vi2d{ FRAME_SIZE, FRAME_SIZE }, olc::GREY);
	pge->DrawStringDecal(windowPosition + olc::vf2d{ 8, 4 }, "INVENTORY", olc::WHITE, olc::vf2d{ 0.5,0.5 });

	std::string tooltip = "";

	for (int x = 0; x < HORIZONTAL_CELLS; x++)
	{
		for (int y = 0; y < VERTICAL_CELLS; y++)
		{
			olc::vi2d pos = windowPosition + olc::vi2d{ SLOT_SIDE_PADDING + (x * CELL_SIZE), SLOT_TOP_OFFSET + (y * CELL_SIZE) };
			Item* item = &items[y * HORIZONTAL_CELLS + x];

			DrawSlot(pos, *item, pge, tooltip);
		}
	}

	DrawSlot(windowPosition + olc::vf2d{ (HORIZONTAL_CELLS + 0.25f) * CELL_SIZE,
		static_cast<float>(SLOT_TOP_OFFSET) }, equippedArmor, pge, tooltip);
	DrawSlot(windowPosition + olc::vf2d{ (HORIZONTAL_CELLS + 0.25f) * CELL_SIZE,
		static_cast<float>(SLOT_TOP_OFFSET + CELL_SIZE) }, equippedWeapon, pge, tooltip);

	if (holdingItem.name != Item::NULL_ITEM.name)
	{
		DrawHoldingItem(pge);

		// If we tried to release the item, but it's still in our hands
		if (pge->GetMouse(0).bReleased)
		{
			droppingItem = true;

			//AudioSystem::GetInstance()->PlayClip("Data/Blip_Select3.wav");
		}
	}

	if (tooltip.empty() == false)
	{
		olc::vf2d drawPos = pge->GetMousePos();

		// Adjust the position to keep the text on screen
		int delta = static_cast<int>((drawPos.x + (util::GetStringWidth(tooltip) * 4)) - pge->ScreenWidth());
		if (delta > 0) drawPos.x -= delta;

		delta = static_cast<int>((drawPos.y + (util::GetStringHeight(tooltip) * 4)) - pge->ScreenHeight());
		if (delta > 0) drawPos.y -= delta;

		pge->DrawStringDecal(olc::vf2d{ -0.05f, 0.05f } + drawPos, tooltip, olc::BLACK, olc::vf2d{ 0.5f, 0.5f });
		pge->DrawStringDecal(drawPos, tooltip, olc::WHITE, olc::vf2d{ 0.5f, 0.5f });
	}

	delete[] positions;
}

void Inventory::Initialize(olc::PixelGameEngine* pge, olc::Renderable* inventoryUI, bool drawing, int x, int y)
{
	this->inventoryUI = inventoryUI;
	for (size_t i = 0; i < HORIZONTAL_CELLS * VERTICAL_CELLS; i++) items.push_back(Item::NULL_ITEM);

	SetPosition(x, y);
	SetDrawing(pge, drawing);
}