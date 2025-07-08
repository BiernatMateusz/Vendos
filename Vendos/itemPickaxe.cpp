#include "itemPickaxe.h"


itemPickaxe::itemPickaxe(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool)
	:
	itemTool(graphicsData, equipmentData, TypeOfTool::Pickaxe, qualityOfTool)
{
	TypeOfBlockToInterract.push_back(tileType::pickaxableField);
}

void itemPickaxe::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, &this->TypeOfBlockToInterract);
}

void itemPickaxe::render(sf::RenderWindow* window)
{

}
