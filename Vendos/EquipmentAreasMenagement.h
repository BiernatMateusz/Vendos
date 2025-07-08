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
	EquipmentAreasMenagement() {};
	EquipmentAreasMenagement(GraphicsData* graphicsData, EquipmentData* equipmentData);

	bool assignItemToArea(item* item, bool recursion, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* itemsArea, std::vector<int> orderOfSearch);
	void resetData();
protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	sf::Vector2i WhereToPutItem(item* Item, bool recursion, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* items, std::vector<int> orderOfSearch);

private:
	sf::Vector2i lastPlaceOfPuttingEq{};
	sf::Vector2i WhereToPut{ 99,99 };
	bool overMax{};
};

#endif // !EQUIPMENTAREASMENAGEMENT
