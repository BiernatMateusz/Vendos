#include "PlayerStorage.h"

PlayerStorage::PlayerStorage(GraphicsData* graphicsData, EquipmentData* equipmentData) : EquipmentStorageArea(
	graphicsData,
	equipmentData,
	{ 9, 3 },
	{ 0, 0 },
	{},
	{ },
	TextureNames::BackgroundCrafting,
	{ 0,2,1 }
)
{
	this->factoryOfItems.init(this->graphicsData, this->equipmentData);
	fillStartingPlayerStorage();
	updatePositionOfItems();

}

void PlayerStorage::renderBottomBar()
{
	//render background of choosen item

		for (int x = 0; x < size().x; ++x)
		{
			if (!isUsable(x, 0))
				continue;

			drawBackground(x, 0, equipmentData->whichItemSelected==x);

			if (this->getSlotRef(x, 0).get())
				this->getSlotRef(x, 0).get()->drawItem();

		}
}

void PlayerStorage::fillStartingPlayerStorage()
{
	this->setSlot(0, 0, factoryOfItems.createItem(ItemNames::StoneEq, 10));
	this->setSlot(0, 2, factoryOfItems.createItem(ItemNames::WoodEq, 10));
	this->setSlot(1, 2, factoryOfItems.createItem(ItemNames::WoodEq, 10));
	this->setSlot(0, 1, factoryOfItems.createItem(ItemNames::StoneEq, 995));
	this->setSlot(1, 1, factoryOfItems.createItem(ItemNames::StoneEq, 995));
	this->setSlot(2, 1, factoryOfItems.createItem(ItemNames::StoneEq, 995));
	this->setSlot(2, 0, factoryOfItems.createItem(ItemNames::WoodenAxe, 1));
	this->setSlot(3, 0, factoryOfItems.createItem(ItemNames::WoodenPickaxe, 1));
	this->setSlot(4, 0, factoryOfItems.createItem(ItemNames::ChestEq, 1));
	this->setSlot(6, 0, factoryOfItems.createItem(ItemNames::WoodenHoe, 1));
	this->setSlot(7, 0, factoryOfItems.createItem(ItemNames::WoodenWateringCan, 1));
}
