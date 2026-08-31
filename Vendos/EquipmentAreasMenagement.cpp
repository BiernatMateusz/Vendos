#include "EquipmentAreasMenagement.h"
#include "Workstation.h"

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



std::unique_ptr<item> EquipmentAreasMenagement::assignItemToChosenArea(std::unique_ptr<item> slotOfItemToDelete, ItemStorage& storage, std::vector<int> orderOfSearch)
{
	//look into all itemsArea for the same itemID which is not MAX
	//if found and not max -> place as much as possible and go for next slot (if item still not emptied)

	//Check if slot is usable

	auto size = storage.size();

	for (int i = 0; i < orderOfSearch.size(); ++i)
		for (int j = 0; j < size.x; ++j)
			if (ifSameID(slotOfItemToDelete.get(), storage.getSlotRef(j, orderOfSearch[i]).get()))
				if (storage.getSlotRef(j, orderOfSearch[i]).getType() == typeOfSlot::PickAndPlace and storage.isUsable(j, orderOfSearch[i]))
					if (not(storage.getSlotRef(j, orderOfSearch[i]).get()->addItemsReturn1IfOverMax(slotOfItemToDelete.get())))
					{
						i = orderOfSearch.size();
						j = size.x;

						slotOfItemToDelete.get()->setNumberOfItems(0);
						return nullptr; //<-- przetestowaæ czy po dodaniu tego wszystko jest nadal gitem
					}


	//if there was no matching item look for first empty slots or there is still something to put

	if (slotOfItemToDelete->getNumberOfItems() != 0)
		for (int i = 0; i < orderOfSearch.size(); ++i)
			for (int j = 0; j < size.x; ++j)
				if (ifEmptySpot(storage.getSlotRef(j, orderOfSearch[i])))
				{
					if (storage.getSlotRef(j, orderOfSearch[i]).getType() == typeOfSlot::PickAndPlace and storage.isUsable(j, orderOfSearch[i]))
					{
						slotOfItemToDelete->cameraSpriteOfItem.getSprite().setOrigin(0, 0);
						slotOfItemToDelete->cameraSpriteOfItem.getSprite().setScale(1, 1);

						storage.getSlotRef(j, orderOfSearch[i]).swapItems(std::move(slotOfItemToDelete));

						int tmpi = orderOfSearch[i];
						int tmpj = j;

						i = orderOfSearch.size();
						j = size.x;

						if (!(storage.getSlotRef(tmpj, tmpi).get()->isNullItemsInStack()))
							return nullptr;
					}
				}
						
	
	return slotOfItemToDelete;
}

bool EquipmentAreasMenagement::isThereItem(ItemStorage& storage, ItemNames itemName, int count)
{
	auto size = storage.size();
	int countedItems{};

	

	for (int i = 0; i < size.y; ++i)
		for (int j = 0; j < size.x; ++j)
			if (storage.getSlotRef(j, i).get()!=nullptr)
				if (storage.getSlotRef(j,i).get()->getItemName() == itemName)
				{
					countedItems+= storage.getSlotRef(j, i).get()->getNumberOfItems();
					if (countedItems >= count) return true;
				}

	return false;
}

void EquipmentAreasMenagement::takeItems(ItemStorage& storage, ItemNames itemName, int count)
{
	auto size = storage.size();
	
	for (int i = size.y-1; i >= 0; --i)
		for (int j = size.x-1; j >=0 ; --j)
		{

			auto slotRef = storage.getSlotRef(j, i).get();

			if (storage.getSlotRef(j, i).get() != nullptr)
			{
				if (slotRef->getItemName() == itemName)
				{
					int itemCount;
					itemCount=slotRef->getNumberOfItems();
					if (itemCount > count)
					{
						slotRef->substrFromThisItem(count);
						return;
					}
					else if (itemCount == count)
					{
						slotRef->substrFromThisItem(count);
						storage.setSlot(j, i, nullptr);
						return;
					}
					else
					{
						slotRef->substrFromThisItem(itemCount);
						storage.setSlot(j, i, nullptr);
						count -= itemCount;
					}
				}
			}
		}
}

bool EquipmentAreasMenagement::ifSameID(item* slotOfItemToDelete, item* Slot)
{
	if (Slot != nullptr and
		Slot != slotOfItemToDelete and
		Slot->getItemID() == slotOfItemToDelete->getItemID())
		return true;

	return false;

}

bool EquipmentAreasMenagement::ifEmptySpot(slot& Slot)
{
	if (Slot.get() == nullptr)
		return true;

	return false;
}