#include "itemShovel.h"

itemShovel::itemShovel(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool)
	:
	itemTool(graphicsData, equipmentData, TypeOfTool::Shovel, qualityOfTool)
{
}


void itemShovel::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, &this->TypeOfBlockToInterract);
}

void itemShovel::render(sf::RenderWindow* window)
{

}
