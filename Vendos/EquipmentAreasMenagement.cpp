#include "EquipmentAreasMenagement.h"

EquipmentAreasMenagement::EquipmentAreasMenagement()
{
	this->graphicsData = nullptr;
	this->equipmentData=nullptr;
}

EquipmentAreasMenagement::EquipmentAreasMenagement(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

bool EquipmentAreasMenagement::assignItemToAreaFromTiles(item* item, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> orderOfSearch)
{
	std::pair<bool, itemAndItsPosition*> slotOfItemToDelete;
	slotOfItemToDelete.first = true;
	slotOfItemToDelete.second = new itemAndItsPosition();
	slotOfItemToDelete.second->setItemPtr(item);

	if (assignItemToAreaInEquipment(slotOfItemToDelete, itemsArea, orderOfSearch))
	{
		slotOfItemToDelete.second = nullptr;
		return true;
	}

	slotOfItemToDelete.second = nullptr;
	this->equipmentData->IDofItemsWhichCantBeTaken.insert(item->itemID);

	return false;
}



bool EquipmentAreasMenagement::assignItemToAreaInEquipment(std::pair<bool, itemAndItsPosition*> slotOfItemToDelete, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> orderOfSearch)
{
	//look into all itemsArea for the same itemID which is not MAX
	//if found and not max -> place as much as possible and go for next slot (if item still not emptied)

	for (int i = 0; i<orderOfSearch.size();++i)
		for (int j = 0; j < itemsArea->size(); ++j)
			if (ifSameID(slotOfItemToDelete, itemsArea->at(j).at(orderOfSearch[i])))
				if (not(itemsArea->at(j).at(orderOfSearch[i]).second->getItemPtr()->addItemsReturn1IfOverMax(slotOfItemToDelete.second->getItemPtr())))
				{
					i = orderOfSearch.size();
					j = itemsArea->size();

					slotOfItemToDelete.second->getItemPtr()->setNumberOfItems(0);
					return true; //<-- przetestowaæ czy po dodaniu tego wszystko jest nadal gitem
				}


	//if there was no matching item look for first empty slots or there is still something to put
	

	if (slotOfItemToDelete.second->getItemPtr()->getNumberOfItems() != 0)
		for (int i = 0; i < orderOfSearch.size(); ++i)
			for (int j = 0; j < itemsArea->size(); ++j)
				if (ifEmptySpot(itemsArea->at(j).at(orderOfSearch[i])))
				{

					slotOfItemToDelete.second->itemPtr->cameraSpriteOfItem->getSprite()->setOrigin(0, 0);
					slotOfItemToDelete.second->itemPtr->cameraSpriteOfItem->getSprite()->setScale(1, 1);
					std::swap(slotOfItemToDelete.second->itemPtr, itemsArea->at(j).at(orderOfSearch[i]).second->itemPtr);

					int tmpi = i;
					int tmpj = j;

					i = orderOfSearch.size();
					j = itemsArea->size();




					if (itemsArea->at(tmpj).at(orderOfSearch[tmpi]).second->itemPtr->getNumberOfItems() > 0)
						return true;
				}
	
	return false;
}

bool EquipmentAreasMenagement::checkIfPossibleItemPlacement(item* item, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> lineOfSearches)
{
	std::pair<bool, itemAndItsPosition*> slotOfItemToDelete;
	slotOfItemToDelete.first = true;
	slotOfItemToDelete.second = new itemAndItsPosition();
	slotOfItemToDelete.second->setItemPtr(item);

	for (int i = 0; i < lineOfSearches.size(); ++i)
		for (int j = 0; j < itemsArea->size(); ++j)
		{
			if (ifEmptySpot(itemsArea->at(j).at(lineOfSearches[i])))
			{
				slotOfItemToDelete.second = nullptr;
				return true;
			}
			if (ifSameID(slotOfItemToDelete, itemsArea->at(j).at(lineOfSearches[i])))
				if (itemsArea->at(j).at(lineOfSearches[i]).second->getItemPtr()->getNumberOfItems() != itemsArea->at(j).at(lineOfSearches[i]).second->getItemPtr()->getNumberMax())
				{
					slotOfItemToDelete.second = nullptr;
					return true;
				}
			
		}
	slotOfItemToDelete.second = nullptr;
	return false;
}

bool EquipmentAreasMenagement::ifSameID(std::pair<bool, itemAndItsPosition*> slotOfItemToDelete, std::pair<bool, itemAndItsPosition*> slot)
{
	if (slot.first == true)
		if (slot.second->getItemPtr() != nullptr)
			if (slot.second->getItemPtr() != slotOfItemToDelete.second->getItemPtr())
				if (slot.second->getItemPtr()->itemID == slotOfItemToDelete.second->getItemPtr()->itemID)
					return true;

	return false;

}

bool EquipmentAreasMenagement::ifEmptySpot(std::pair<bool, itemAndItsPosition*> slot)
{
	if (slot.first == true)
		if (slot.second->getItemPtr() == nullptr)
			return true;
	return false;
}