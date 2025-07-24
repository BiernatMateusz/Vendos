#ifndef ITEM_CONSTRUCTOR_H
#define ITEM_CONSTRUCTOR_H

#include "item.h"
#include "StructuresOfData.h"

class ItemConstructor
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	item* newItemToReturn{};

public:
	void init(GraphicsData* graphicsData, EquipmentData* equipmentData);
	item* createItem(int itemID, int ammount);

	item* createItem(ItemNames nameOfItem);
	item* createItem(ItemNames nameOfItem, int ammount);
	item* createItem(ItemNames nameOfItem, sf::Vector2i position2i);

};

#endif 