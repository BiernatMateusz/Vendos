#include "itemFurnace.h"

itemFurnace::itemFurnace(GraphicsData* graphicsData, EquipmentData* equipmentData)
	:
	item(graphicsData, TypeOfAction::Place),
	EquipmentStorageArea(graphicsData, equipmentData, { 1,1 }, { 3,5 }, {}, { {3,7}, {5,6} }, "BackgroundFurnace"),
	TilesOnMap(graphicsData)
{
	;
}

itemFurnace::itemFurnace(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i position2i, std::string NameOfTxt)
	:
	item(graphicsData, TypeOfAction::Place),
	EquipmentStorageArea(graphicsData, equipmentData, { 1,1 }, { 3,5 }, {}, { {3,7}, {5,6} }, "BackgroundFurnace"),
	TilesOnMap(position2i, NameOfTxt, graphicsData)
{
	;
}

itemFurnace::~itemFurnace()
{
	;
}

void itemFurnace::updateStorageArea(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;
}

void itemFurnace::render()
{
	;
}