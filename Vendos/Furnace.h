#ifndef FURNACE_H
#define FURNACE_H

#include "StructuresOfData.h"
#include "EquipmentAreas.h"

class Furnace:
	public EquipmentStorageArea
{
public:
	Furnace(GraphicsData* graphicsData, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround);
	~Furnace();
	void updateStorageArea(const float& dt, const std::map<std::string, button*>& AllKeys);
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	ItemConstructor factoryOfItems;
	ThrownItems* itemsOnTheGround;
};

#endif // !FURNACE_H
