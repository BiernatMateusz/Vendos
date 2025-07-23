#include "itemChest.h"

itemChest::itemChest(GraphicsData* graphicsData, EquipmentData* equipmentData)
	:
	item(graphicsData, TypeOfAction::Place),
	EquipmentStorageArea(graphicsData, equipmentData, { 9,3 }, { 0,4 }, {}, {}, "BackgroundChest"),
	TilesOnMap(graphicsData)
{
	;
}

itemChest::itemChest(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i position2i, std::string NameOfTxt)
	:
	item(graphicsData, TypeOfAction::Place),
	EquipmentStorageArea(graphicsData, equipmentData, { 9,3 }, { 0,4 }, {}, {}, "BackgroundChest"),
	TilesOnMap(position2i, NameOfTxt, graphicsData)
{
	;
}

itemChest::~itemChest()
{

}

void itemChest::updateStorageArea(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;//std::cout<<"Skrzynka sie updatuje\n";
}

void itemChest::render()
{
	;
}
