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

item* ItemConstructor::createItem(ItemNames nameOfItem)
{
	if (this->newItemToReturn != nullptr)
		this->newItemToReturn = nullptr;

	this->newItemToReturn = new item(this->graphicsData);

	switch (nameOfItem)
	{
	case ItemNames::HoedNoWater:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::HoedNoWater, tileType::hoedField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, -44);
		this->newItemToReturn->initItemID(3);
		break;
	case ItemNames::HoedWatered:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::HoedWatered, tileType::wateredField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, -44);
		this->newItemToReturn->initItemID(4);
		break;
	case ItemNames::Tree1:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Tree1, tileType::axableField, { 101 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 50,160 }, 33);
		this->newItemToReturn->initTileBlockadeData({ 30,30 }, { 6,8 }, sf::FloatRect(0, 0, 30, 22));
		this->newItemToReturn->initItemID(10);
		break;
	case ItemNames::Tree2:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Tree2,  tileType::axableField, { 101 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 68,162 }, 33);
		this->newItemToReturn->initTileBlockadeData({ 30,18 }, { 8,19 }, sf::FloatRect(0, 0, 30, 18));
		this->newItemToReturn->initItemID(11);
		break;
	case ItemNames::Tree3:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Tree3, tileType::axableField, { 101 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 42,135 }, 33);
		this->newItemToReturn->initTileBlockadeData({ 30,16 }, { 12,24 }, sf::FloatRect(0, 0, 30, 14));
		this->newItemToReturn->initItemID(12);
		break;
	case ItemNames::BushEmpty:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::BushEmpty, tileType::axableField, { 102 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,20 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemID(13);
		break;
	case ItemNames::EmptyTile:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::EmptyTile, tileType::emptyBlockade, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 0);
		this->newItemToReturn->initTileBlockadeData({ 29,29 }, { 0,0 }, sf::FloatRect(0, 0, 29, 29));
		this->newItemToReturn->initItemID(0);
		break;
	case ItemNames::WoodenHoe:
		break;
	case ItemNames::WoodenPickaxe:
		break;
	case ItemNames::WoodenAxe:
		break;
	case ItemNames::WoodenSword:
		break;
	case ItemNames::WoodenShovel:
		break;
	case ItemNames::WoodenWateringCan:
		break;
	case ItemNames::StoneEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Stone, tileType::pickaxableField, { 100 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemID(100);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::StoneEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::WoodEq:
		this->newItemToReturn->initItemID(101);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::Patyk:
		this->newItemToReturn->initItemID(102);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::Patyk, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::CopperEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Copper, tileType::pickaxableField, { 103 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemID(103);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::CopperEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::IronEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Iron, tileType::pickaxableField, { 104 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemID(104);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::IronEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::ChestEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Chest, tileType::chestField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 20);
		this->newItemToReturn->initTileBlockadeData({ 32,20 }, { 5,15 }, sf::FloatRect(0, 0, 32, 20));
		this->newItemToReturn->initItemID(105);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::ChestEq, 5, TypeOfAction::Place);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->storageArea = this->storageCreator.initStorageArea(graphicsData, equipmentData, { 9,3 }, { 0,4 }, {}, {}, "BackgroundChest");
		break;
	case ItemNames::FurnaceEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Furnace, tileType::chestField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 20);
		this->newItemToReturn->initTileBlockadeData({ 32,20 }, { 5,15 }, sf::FloatRect(0, 0, 32, 20));
		this->newItemToReturn->initItemID(106);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::FurnaceEq, 5, TypeOfAction::Place);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->storageArea = this->storageCreator.initStorageArea(graphicsData, equipmentData, { 1,1 }, { 3,5 }, {}, { {3,7}, {5,6} }, "BackgroundFurnace");
		break;
	}

	if (this->newItemToReturn==nullptr)
		std::cout << "Brak itemu w klasie intemContructor.cpp, dodaj warunek w switchu w funkcji createItem(TextureNames nameOfTxt)!";


	return this->newItemToReturn;
}

item* ItemConstructor::createItem(ItemNames nameOfTxt, sf::Vector2i position2i)
{
	this->newItemToReturn = createItem(nameOfTxt);
	this->newItemToReturn->initPosition(position2i);
	return newItemToReturn;
}
