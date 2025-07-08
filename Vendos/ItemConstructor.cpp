#include "ItemConstructor.h"

void ItemConstructor::init(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

item* ItemConstructor::creatorOfItemBasedOnExample(item* example)
{
	return creatorOfItemBasedOnID(example->itemID, example->getNumberOfItems());
}

item* ItemConstructor::creatorOfItemBasedOnID(int itemID, int ammount)
{
	switch (itemID) 
	{
	case 0:
		return new item(graphicsData);
	case 20:
		return new itemHoe(graphicsData, equipmentData, QualityOfTool::Wooden);
	case 21:
		return new itemPickaxe(graphicsData, equipmentData, QualityOfTool::Wooden);
	case 22:
		return new itemAxe(graphicsData, equipmentData, QualityOfTool::Wooden);
	case 23:
		return new itemSword(graphicsData, equipmentData, QualityOfTool::Wooden);
	case 24:
		return new itemShovel(graphicsData, equipmentData, QualityOfTool::Wooden);
	case 25:
		return new itemWateringCan(graphicsData, equipmentData, QualityOfTool::Wooden);
	case 26:
		return new itemChest(graphicsData, equipmentData);
	case 100:
		return new item(graphicsData, equipmentData, "StoneEq", ammount, TypeOfAction::Hand);
	case 101:
		return new item(graphicsData, equipmentData, "WoodEq", ammount, TypeOfAction::Hand);
	case 102:
		return new item(graphicsData, equipmentData, "Patyk", ammount, TypeOfAction::Hand);
	case 103:
		return new item(graphicsData, equipmentData, "CopperEq", ammount, TypeOfAction::Hand);
	case 104:
		return new item(graphicsData, equipmentData, "IronEq", ammount, TypeOfAction::Hand);
	case 105:
		return new item(graphicsData, equipmentData, "ChestEq", ammount, TypeOfAction::Place);
	case 106:
		return new item(graphicsData, equipmentData, "FurnaceEq", ammount, TypeOfAction::Place);
	}

	std::cout << "Brak itemu w klasie intemContructor.cpp, dodaj warunek w switchu!";
}
