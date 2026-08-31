#ifndef ITEM_CONSTRUCTOR_H
#define ITEM_CONSTRUCTOR_H

#include "item.h"
#include "StructuresOfData.h"

class ItemConstructor
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	std::unique_ptr<item> newItemToReturn;

public:
	void init(GraphicsData* graphicsData, EquipmentData* equipmentData);
	std::unique_ptr<item> createItem(int itemID, int ammount);

	std::unique_ptr<item> createItem(ItemNames nameOfItem);
	std::unique_ptr<item> createItem(ItemNames nameOfItem, int ammount);
	std::unique_ptr<item> createItem(ItemNames nameOfItem, sf::Vector2i position2i);

};

#endif 