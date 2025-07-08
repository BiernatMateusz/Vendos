#include "EquipmentAreasMenagement.h"

EquipmentAreasMenagement::EquipmentAreasMenagement(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

sf::Vector2i EquipmentAreasMenagement::WhereToPutItem(item* Item, bool recursion, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* items, std::vector<int> orderOfSearch)
{
	int x{};
	int y{};

	bool PossibleSearch{ 1 };

	if (recursion)
	{
		x = lastPlaceOfPuttingEq.x + 1;
		y = lastPlaceOfPuttingEq.y;

		if (y >= orderOfSearch.size())
		{
			x++;
			y = 0;
		}

		if (x >= items->at(0).size())
		{
			PossibleSearch = 0;
		}
	}

	bool foundPerf{};

	if (PossibleSearch)
	{
		for (int i = y; i < orderOfSearch.size(); ++i)
			for (int j = x; j < items->size(); ++j)
			{
				if (items->at(j).at(orderOfSearch[i]).second->getItemPtr() != nullptr)
				{
					if (items->at(j).at(orderOfSearch[i]).second->getItemPtr()->itemID == Item->itemID)
					{
						if (items->at(j).at(orderOfSearch[i]).second->getItemPtr()->getNumberOfItems() < items->at(j).at(orderOfSearch[i]).second->getItemPtr()->getNumberMax())
						{
							WhereToPut = { j,orderOfSearch[i] };

							i = orderOfSearch.size();	//end of for
							j = items->size();			//end of for
							foundPerf = true;
						}
					}
				}
			}

		if (not foundPerf)
			for (int i = 0; i < orderOfSearch.size(); ++i)
				for (int j = 0; j < items->size(); ++j)
					if (items->at(j).at(orderOfSearch[i]).second->getItemPtr() == nullptr)
					{
						WhereToPut = { j,orderOfSearch[i] };
						i = orderOfSearch.size();		//end of for
						j = items->size();				//end of for
					}

	}
	else WhereToPut = { 99,99 }; //It means there if no enough space for everything
	return WhereToPut;
}

bool EquipmentAreasMenagement::assignItemToArea(item* item, bool recursion, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> orderOfSearch)
{
	if (recursion == 0)
		lastPlaceOfPuttingEq = {};

	lastPlaceOfPuttingEq = WhereToPutItem(item, recursion, itemsArea, orderOfSearch); //it returns positions on Eq[][] where to put item, need to check if it is nullptr - then move item there, if there is something already need to stack it 

	if (not(lastPlaceOfPuttingEq.x == 99 and lastPlaceOfPuttingEq.y == 99))
	{
		if (itemsArea->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y).second->getItemPtr() == nullptr)
		{
			itemsArea->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y).second->setItemPtr(item);

		}
		else if (itemsArea->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y).second->getItemPtr() != nullptr)
		{
			this->overMax = itemsArea->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y).second->getItemPtr()->addItemsReturn1IfOverMax(item);

			if (this->overMax)
			{
				this->overMax = 0;
				assignItemToArea(item, 1, itemsArea, orderOfSearch);
			}
		}

		if (lastPlaceOfPuttingEq.x == 99 and lastPlaceOfPuttingEq.y == 99)
		{
			this->equipmentData->IDofItemsWhichCantBeTaken.insert(item->itemID);
			return false;
		}

		item->itemSprite.setOrigin(0, 0);
		item->itemSprite.setScale(1, 1);

		return true;
	}
	else
	{
		this->equipmentData->IDofItemsWhichCantBeTaken.insert(item->itemID);
	}
	return false;
}

void EquipmentAreasMenagement::resetData()
{
	this->WhereToPut = { 99,99 };	//looks ugly but it needs to be this way
}