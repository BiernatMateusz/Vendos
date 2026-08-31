#ifndef EQUIPMENTAREASMENAGEMENT
#define EQUIPMENTAREASMENAGEMENT

#include <iostream>
#include "StructuresOfData.h"
#include "item.h"
#include "TilesOnMap.h"
#include "slot.h"


class ItemStorage;

class EquipmentAreasMenagement
{
public:
	EquipmentAreasMenagement();
	EquipmentAreasMenagement(GraphicsData* graphicsData, EquipmentData* equipmentData);

	//bool assignItemToAreaFromTiles(item* item, ItemStorage& storage, std::vector<int> orderOfSearch);
	std::unique_ptr<item> assignItemToChosenArea(std::unique_ptr<item> slotOfItemToDelete, ItemStorage &storage, std::vector<int> orderOfSearch);

	//bool checkIfPossibleItemPlacement(item* item, ItemStorage& storage, std::vector<int> lineOfSearches);

	bool isThereItem(ItemStorage& storage, ItemNames itemName, int count);
	void takeItems(ItemStorage& storage, ItemNames itemName, int count);

protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

private:
	bool ifSameID(item* slotOfItemToDelete, item* Slot);
	bool ifEmptySpot(slot& slot);
};

#endif // !EQUIPMENTAREASMENAGEMENT
