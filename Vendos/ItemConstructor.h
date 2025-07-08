#ifndef ITEM_CONSTRUCTOR_H
#define ITEM_CONSTRUCTOR_H

#include "itemAxe.h"
#include "itemPickaxe.h"
#include "itemHoe.h"
#include "itemShovel.h"
#include "itemSword.h"
#include "itemChest.h"
#include "itemFurnace.h"
#include "itemWateringCan.h"
#include "StructuresOfData.h"



class ItemConstructor
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

public:
	void init(GraphicsData* graphicsData, EquipmentData* equipmentData);
	item* creatorOfItemBasedOnExample(item* example);
	item* creatorOfItemBasedOnID(int itemID, int ammount);



};

#endif 