#include "itemAxe.h"

itemAxe::itemAxe(GraphicsData* graphicsData, EquipmentData* equipmentData,QualityOfTool qualityOfTool)
	:
	itemTool(graphicsData, equipmentData, TypeOfTool::Axe, qualityOfTool)
{
	TypeOfBlockToInterract.push_back(tileType::axableField);
}

void itemAxe::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, &this->TypeOfBlockToInterract);
}

void itemAxe::render(sf::RenderWindow* window)
{

}
