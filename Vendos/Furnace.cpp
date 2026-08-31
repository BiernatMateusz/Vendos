#include "Furnace.h"

Furnace::Furnace(GraphicsData* graphicsData, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->itemsOnTheGround = ItemsOnTheGround;

	this->factoryOfItems.init(graphicsData, equipmentData);
}

Furnace::~Furnace()
{
	;
}

void Furnace::updateStorageArea(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;
}