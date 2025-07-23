#ifndef EQUIPMENTAREASMENAGEMENT
#define EQUIPMENTAREASMENAGEMENT

#include <iostream>
#include "StructuresOfData.h"
#include "item.h"
#include "TilesOnMap.h"
#include "itemAndItsPosition.h"

class EquipmentAreasMenagement
{
public:
	EquipmentAreasMenagement();
	EquipmentAreasMenagement(GraphicsData* graphicsData, EquipmentData* equipmentData);

	bool assignItemToAreaFromTiles(item* item, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> orderOfSearch);
	bool assignItemToAreaInEquipment(std::pair<bool, itemAndItsPosition*> slotOfItemToDelete, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> orderOfSearch);

	bool checkIfPossibleItemPlacement(item* item, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> lineOfSearches);

protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

private:
	bool ifSameID(std::pair<bool, itemAndItsPosition*> slotOfItemToDelete, std::pair <bool, itemAndItsPosition*> slot);
	bool ifEmptySpot(std::pair <bool, itemAndItsPosition*> slot);
};

#endif // !EQUIPMENTAREASMENAGEMENT
