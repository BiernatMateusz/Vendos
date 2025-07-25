#include "itemHoe.h"

itemHoe::itemHoe(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool)
	:
	itemTool(graphicsData, equipmentData, TypeOfTool::Hoe, qualityOfTool)
{
	this->nameOfTxtWhileReplacing = "PoDziabceSuche";
	this->isCreatingOnEmptyTilePossible = 1;
	TypeOfBlockToInterract.push_back(tileType::emptyField);
	TypeOfBlockToInterract.push_back(tileType::crop);
}

void itemHoe::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, &this->TypeOfBlockToInterract);
}

void itemHoe::render(sf::RenderWindow* window)
{
	//action
}
