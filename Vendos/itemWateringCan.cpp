#include "itemWateringCan.h"

itemWateringCan::itemWateringCan(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool)
	:
	itemTool(graphicsData, equipmentData, TypeOfTool::WateringCan,  qualityOfTool)
{
	this->nameOfTxtWhileReplacing = "PoDziabceMokre";
	this->isCreatingOnEmptyTilePossible = 0;
	TypeOfBlockToInterract.push_back(tileType::hoedField);
}

void itemWateringCan::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, &this->TypeOfBlockToInterract);
}

void itemWateringCan::render(sf::RenderWindow* window)
{

}
