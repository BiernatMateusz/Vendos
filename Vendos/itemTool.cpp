#include "itemTool.h"

void itemTool::updateKeybinds()
{
	//todo -- look for block in the direction that is character looking and check possible actions
}

void itemTool::updateTypeAndQuality(TypeOfTool typeOfTool, QualityOfTool qualityOfTool)
{
	switch (typeOfTool)
	{
	case TypeOfTool::Axe:
		this->typeOfAction = TypeOfAction::Drop;
		break;
	case TypeOfTool::Pickaxe:
		this->typeOfAction = TypeOfAction::Drop;
		break;
	case TypeOfTool::Shovel:
		this->typeOfAction = TypeOfAction::Drop;
		break;
	case TypeOfTool::Sword:
		this->ToolAction = nullptr;
		break;
	case TypeOfTool::WateringCan:
		this->typeOfAction = TypeOfAction::Replace;
		break;
	case TypeOfTool::Hoe:
		this->typeOfAction = TypeOfAction::Replace;
		break;

	}

}

void itemTool::setDurability()
{
	switch (qualityOfTool)
	{
	case QualityOfTool::Wooden:
		this->durability = 100;
		this->breakingBlockDamage = 5;
		this->dropMultiplication = 1;
		break;
	case QualityOfTool::Stone:
		this->durability = 200;
		this->breakingBlockDamage = 6;
		this->dropMultiplication = 1.3;
		break;
	case QualityOfTool::Iron:
		this->durability = 400;
		this->breakingBlockDamage = 8;
		this->dropMultiplication = 1.9;
		break;
	case QualityOfTool::Golden:
		this->durability = 500;
		this->breakingBlockDamage = 10;
		this->dropMultiplication = 2.5;
		break;
	case QualityOfTool::Diamond:
		this->durability = 2000;
		this->breakingBlockDamage = 13;
		this->dropMultiplication = 3.5;
		break;
	}
}

itemTool::itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, TypeOfTool typeOfTool, QualityOfTool qualityOfTool)
	:
	item(graphicsData, equipmentData, typeOfTool, qualityOfTool)
{
	updateTypeAndQuality(typeOfTool, qualityOfTool);
	setDurability();
}

itemTool::itemTool(GraphicsData* graphicsData, TypeOfTool typeOfTool, QualityOfTool qualityOfTool)
{
	updateTypeAndQuality(typeOfTool, qualityOfTool);
	setDurability();
}

void itemTool::update(const float& dt, const std::map<std::string, button*>& AllKeys, std::vector<tileType>* TypeOfBlockToInterract)
{
	;
}

const int& itemTool::getBreakingDamage() const
{
	return this->breakingBlockDamage;
}


