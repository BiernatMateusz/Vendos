#include "itemTool.h"

void itemTool::initBlocksToInteract(std::initializer_list<tileType>& tileTypeWithInteractions)
{
	for (auto& elem : tileTypeWithInteractions)
		this->TypeOfBlockToInterract.push_back(elem);
}

void itemTool::updateKeybinds()
{
	//todo -- look for block in the direction that is character looking and check possible actions
}

void itemTool::setDurability(QualityOfTool toolQuality)
{
	switch (toolQuality)
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

itemTool::itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool)
{
	setDurability(qualityOfTool);
}

itemTool::itemTool(GraphicsData* graphicsData, QualityOfTool qualityOfTool)
{
	setDurability(qualityOfTool);
}

void itemTool::updateTool(const float& dt, const std::map<std::string, button*>& AllKeys, std::vector<tileType>* TypeOfBlockToInterract)
{
	;
}

void itemTool::initToolDrop(std::initializer_list<tileType> tileTypeWithInteractions, QualityOfTool toolQuality)
{
	initBlocksToInteract(tileTypeWithInteractions);
	setDurability(toolQuality);
}

void itemTool::initToolReplace(std::initializer_list<tileType> tileTypeWithInteractions, QualityOfTool toolQuality, bool interactionWithEmptyTile, ItemNames nameOfTileToReplace)
{
	initBlocksToInteract(tileTypeWithInteractions);
	setDurability(toolQuality);
	this->isCreatingOnEmptyTilePossible = interactionWithEmptyTile;
	this->nameOfTileToReplace = nameOfTileToReplace;
}

const int& itemTool::getBreakingDamage() const
{
	return this->breakingBlockDamage;
}

std::vector<tileType>* itemTool::getTypeOfBlocksToInterract()
{
	return &(this)->TypeOfBlockToInterract;
}

bool itemTool::getIsCreatingOnEmptyTilePossible()
{
	return isCreatingOnEmptyTilePossible;
}


