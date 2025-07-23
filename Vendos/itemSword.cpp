#include "itemSword.h"


itemSword::itemSword(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool)
	:
	itemTool(graphicsData, equipmentData, TypeOfTool::Sword, qualityOfTool)
{
}


void itemSword::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, &this->TypeOfBlockToInterract);
}

void itemSword::render(sf::RenderWindow* window)
{

}
