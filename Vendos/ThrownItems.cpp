#include "ThrownItems.h"

ThrownItems::ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->tile = Tile;
	this->ItemsThrownVec = new std::vector<ThrowedItem*>;
	this->itemCreator.init(graphicsData, equipmentData);
}

void ThrownItems::updateItemsThrownSpriteVec()
{
	this->graphicsData->ItemsThrownSpriteMapped->clear();

	for (auto *elem : *ItemsThrownVec)
		this->graphicsData->ItemsThrownSpriteMapped->push_back(elem->getItem()->cameraSprite);
	
	


	this->equipmentData->needToUpdateCameraAllSpr = 1;
}

void ThrownItems::updatePositionOfEach(const float& dt, float speedX, float speedY)
{
	for (auto* elem : *ItemsThrownVec)
	{
		elem->getAndChangeDestinationOfItem({ dt * speedX,dt * speedY });
	}
}

void ThrownItems::checkIfItemDropped()
{

	for (auto *elem: *this->graphicsData->itemDroppedVec)
		insertItemDroppedFromTile(itemCreator.creatorOfItemBasedOnID(elem->itemID, elem->ammountOfItem), elem->tileCords);

	for (auto* elem : *this->graphicsData->itemDroppedVec)
		delete elem;

	this->graphicsData->itemDroppedVec->clear();

}

void ThrownItems::initEqPtr(std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq)
{
	this->eq = eq;
}

void ThrownItems::insertItemDroppedFromPlayer(item* itemToAdd)
{
	this->ItemsThrownVec->push_back(new ThrowedItem(this->graphicsData, this->equipmentData,this->tile, this->eq, itemToAdd, this->ItemsThrownVec));

	updateItemsThrownSpriteVec();
	
}

void ThrownItems::insertItemDroppedFromTile(item* itemToAdd, sf::Vector2i tileCord)
{
	this->ItemsThrownVec->push_back(new ThrowedItem(this->graphicsData, this->equipmentData, this->tile, this->eq, itemToAdd, this->ItemsThrownVec, tileCord));
	updateItemsThrownSpriteVec();
}

void ThrownItems::setNumberOfItemsLastInVector(int value)
{
	this->ItemsThrownVec->back()->getItem()->setNumberOfItems(1);
}

void ThrownItems::update(const float& dt)
{
	checkIfItemDropped();

	if (ItemsThrownVec->size() > 0)
	{
		this->ItemsThrownVec->erase
		(
			std::remove_if(
				this->ItemsThrownVec->begin(),
				this->ItemsThrownVec->end(),
				[&](auto& ItemsThrownVec)
				{
					ItemsThrownVec->update(dt);

					if (ItemsThrownVec->checkIfCatched())
					{
						if (ItemsThrownVec->assignItemToArea(ItemsThrownVec->getItem(), 0, this->eq, OrderOfSearch))
						{
							this->SprToDeleteVec.push_back(&ItemsThrownVec->getItem()->itemSprite);
							this->itemToDeleteFound = 1;
							return true;
						}
						else return false;
					}
					
				}
			), ItemsThrownVec->end()
					);

		this->ItemsThrownVec->shrink_to_fit();
	}
	

	if (this->itemToDeleteFound)
	{
		for (auto* elem : SprToDeleteVec)
		{
			this->graphicsData->ItemsThrownSpriteMapped->erase
			(
				std::remove_if(this->graphicsData->ItemsThrownSpriteMapped->begin(),
					this->graphicsData->ItemsThrownSpriteMapped->end(),
					[&](auto* ItemsThrownSpriteMappedx)
					{
						if (ItemsThrownSpriteMappedx->sprite == elem)
								return true;
							else return false;
					}
				), this->graphicsData->ItemsThrownSpriteMapped->end()
			);
		}

		this->graphicsData->ItemsThrownSpriteMapped->shrink_to_fit();

		this->equipmentData->needToUpdateCameraAllSpr = 1;

		for (auto elem : SprToDeleteVec)
			elem=nullptr;
		SprToDeleteVec.clear();


		this->itemToDeleteFound = 0;

		for (auto* elem : *ItemsThrownVec)
			elem->resetData();
	}
}

	