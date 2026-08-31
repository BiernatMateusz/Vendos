#include "ThrownItems.h"
#include "ItemStorage.h"
#include "EquipmentStorageArea.h"

ThrownItems::ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->tile = Tile;
	this->itemCreator.init(graphicsData, equipmentData);
	this->graphicsData->thrownItems = this;
}

void ThrownItems::update(const float& dt, EquipmentStorageArea* storageArea)
{
	checkIfNewItemDropped();

	createPickable_ID_ItemsList();

	for (auto& elem : ItemsThrownVec)
		elem->update(dt, checkIfPickPossible(*elem));
	

	std::erase_if(ItemsThrownVec, [&](auto& item)
		{
			if (!item->isCatched())
				return false;

			std::unique_ptr<::item>tmpItemToMoveBack = item->assignItemToChosenArea(item->take(), *storageArea, storageArea->getOrderOfSearch());

			if (!tmpItemToMoveBack)
			{
				this->equipmentData->needToUpdateCameraAllSpr = true;
				return true;
			}
			else
			{
				item->setItem(tmpItemToMoveBack);
			}

			return false;
		});

}

void ThrownItems::createPickable_ID_ItemsList()
{
	this->Pickable_ID_Items.clear();

	bool foundEmpty = false;

	if (this->storage)
		for (int y = 0; y < this->storage->getOrderOfSearch().size() && !foundEmpty; y++)
			for (int x = 0; x < storage->size().x; x++)
			{
				if (!storage->getSlotRef(x, y))
				{
					this->Pickable_ID_Items.clear();
					foundEmpty = true;
					break;
				}
				else if (storage->getSlotRef(x, y).get()->checkIfAddable())
				{
					this->Pickable_ID_Items.insert(storage->getSlotRef(x, y).get()->getItemID());
				}

			}
}



const std::vector<std::unique_ptr<ThrowedItem>>& ThrownItems::getItems() const
{
	return ItemsThrownVec;
}

void ThrownItems::setUpdateCamera()
{
	this->equipmentData->needToUpdateCameraAllSpr = true;
}

void ThrownItems::updatePositionOfEach(const float& dt, float speedX, float speedY)
{
	for (auto& elem :ItemsThrownVec)
	{
		elem->getAndChangeDestinationOfItem({ dt * speedX,dt * speedY });
	}
}

void ThrownItems::checkIfNewItemDropped()
{
	for (auto* elem : this->graphicsData->itemDroppedVec)
		insertItemDroppedFromTile(itemCreator.createItem(elem->itemID, elem->ammountOfItem), elem->tileCords);
	
	for (auto* elem : this->graphicsData->itemDroppedVec)
		delete elem;

	this->graphicsData->itemDroppedVec.clear();

}

bool ThrownItems::checkIfPickPossible(ThrowedItem& throwedItem)
{
	return Pickable_ID_Items.empty() or Pickable_ID_Items.find(throwedItem.getItem()->getItemID()) != Pickable_ID_Items.end();
}

void ThrownItems::initEqPtr(ItemStorage* storage)
{
	this->storage = storage;
}

void ThrownItems::insertItemDroppedFromPlayer(std::unique_ptr<item> itemToAdd)
{
	this->ItemsThrownVec.push_back(std::make_unique<ThrowedItem>(this->graphicsData, this->equipmentData,this->tile, this->storage, std::move(itemToAdd)));
	setUpdateCamera();
}

void ThrownItems::insertItemDroppedFromTile(std::unique_ptr<item> itemToAdd, sf::Vector2i tileCord)
{
	this->ItemsThrownVec.push_back(std::make_unique<ThrowedItem>(this->graphicsData, this->equipmentData, this->tile, this->storage, std::move(itemToAdd), tileCord));
	setUpdateCamera();
}

void ThrownItems::setNumberOfItemsLastInVector(int value)
{
	this->ItemsThrownVec.back()->getItem()->setNumberOfItems(1);
}


	