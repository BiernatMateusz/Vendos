#include "itemChest.h"

itemChest::itemChest(GraphicsData* graphicsData, EquipmentData* equipmentData)
	:
	item(graphicsData, TypeOfAction::Place),
	EquipmentStorageArea(graphicsData, equipmentData, { 9,3 }, { 0,4 }, {}, {}, "BackgroundChest")
{
	;
}

itemChest::~itemChest()
{

}

void itemChest::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;//std::cout<<"Skrzynka sie updatuje\n";
}

void itemChest::render()
{
	;
}
