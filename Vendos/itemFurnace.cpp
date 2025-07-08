#include "itemFurnace.h"

itemFurnace::itemFurnace(GraphicsData* graphicsData, EquipmentData* equipmentData)
	:
	item(graphicsData, TypeOfAction::Place),
	EquipmentStorageArea(graphicsData, equipmentData, { 1,1 }, { 3,5 }, {}, { {3,7}, {5,6} }, "BackgroundFurnace")
{
	;
}

itemFurnace::~itemFurnace()
{
	;
}

void itemFurnace::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;
}

void itemFurnace::render()
{
	;
}