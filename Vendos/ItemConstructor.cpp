#include "ItemConstructor.h"

void ItemConstructor::init(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

item* ItemConstructor::createItem(int itemID, int ammount)
{
	ItemNames tempName{};

	switch (itemID)
	{
	case 0:
		tempName = ItemNames::EmptyTile;
		break;
	case 20:
		tempName = ItemNames::WoodenHoe;
		break;
	case 21:
		tempName = ItemNames::WoodenPickaxe;
		break;
	case 22:
		tempName = ItemNames::WoodenAxe;
		break;
	case 23:
		tempName = ItemNames::WoodenSword;
		break;
	case 24:
		tempName = ItemNames::WoodenShovel;
		break;
	case 25:
		tempName = ItemNames::WoodenWateringCan;
		break;
	case 100:
		tempName = ItemNames::StoneEq;
		break;
	case 101:
		tempName = ItemNames::WoodEq;
		break;
	case 102:
		tempName = ItemNames::Patyk;
		break;
	case 103:
		tempName = ItemNames::CopperEq;
		break;
	case 104:
		tempName = ItemNames::IronEq;
		break;
	case 105:
		tempName = ItemNames::ChestEq;
		break;
	case 106:
		tempName = ItemNames::FurnaceEq;
		break;
	}

	return createItem(tempName, ammount);

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
		this->newItemToReturn->initItemIDandName(3, ItemNames::HoedNoWater);
		break;
	case ItemNames::HoedWatered:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::HoedWatered, tileType::wateredField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, -44);
		this->newItemToReturn->initItemIDandName(4, ItemNames::HoedWatered);
		break;
	case ItemNames::Tree1:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Tree1, tileType::axableField, { 101 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 50,160 }, 33);
		this->newItemToReturn->initTileBlockadeData({ 30,30 }, { 6,8 }, sf::FloatRect(0, 0, 30, 22));
		this->newItemToReturn->initItemIDandName(10, ItemNames::Tree1);
		break;
	case ItemNames::Tree2:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Tree2,  tileType::axableField, { 101 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 68,162 }, 33);
		this->newItemToReturn->initTileBlockadeData({ 30,18 }, { 8,19 }, sf::FloatRect(0, 0, 30, 18));
		this->newItemToReturn->initItemIDandName(11, ItemNames::Tree2);
		break;
	case ItemNames::Tree3:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Tree3, tileType::axableField, { 101 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 42,135 }, 33);
		this->newItemToReturn->initTileBlockadeData({ 30,16 }, { 12,24 }, sf::FloatRect(0, 0, 30, 14));
		this->newItemToReturn->initItemIDandName(12, ItemNames::Tree3);
		break;
	case ItemNames::BushEmpty:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::BushEmpty, tileType::axableField, { 102 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,20 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemIDandName(13, ItemNames::BushEmpty);
		break;
	case ItemNames::EmptyTile:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::EmptyTile, tileType::emptyBlockade, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 0);
		this->newItemToReturn->initTileBlockadeData({ 29,29 }, { 0,0 }, sf::FloatRect(0, 0, 29, 29));
		this->newItemToReturn->initItemIDandName(0, ItemNames::EmptyTile);
		break;
	case ItemNames::WoodenHoe:
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodenHoe, 1, TypeOfAction::Replace);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->initToolReplace({tileType::emptyField, tileType::crop}, QualityOfTool::Wooden, true, ItemNames::HoedNoWater);
		this->newItemToReturn->initItemIDandName(20, ItemNames::WoodenHoe);
		break;
	case ItemNames::WoodenPickaxe:
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodenPickaxe, 1, TypeOfAction::Drop);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->initToolDrop({ tileType::pickaxableField }, QualityOfTool::Wooden);
		this->newItemToReturn->initItemIDandName(21, ItemNames::WoodenPickaxe);
		break;
	case ItemNames::WoodenAxe:
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodenAxe, 1, TypeOfAction::Drop);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->initToolDrop({ tileType::axableField }, QualityOfTool::Wooden);
		this->newItemToReturn->initItemIDandName(22, ItemNames::WoodenAxe);
		break;
	case ItemNames::WoodenSword:
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodenSword, 1, TypeOfAction::Attack);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->initItemIDandName(23, ItemNames::WoodenSword);
		break;
	case ItemNames::WoodenShovel:
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodenShovel, 1, TypeOfAction::Drop);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->initToolDrop({ tileType::pickaxableField }, QualityOfTool::Wooden);
		this->newItemToReturn->initItemIDandName(24, ItemNames::WoodenShovel);
		break;
	case ItemNames::WoodenWateringCan:
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodenWateringCan, 1, TypeOfAction::Replace);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->initToolReplace({ tileType::hoedField}, QualityOfTool::Wooden, false, ItemNames::HoedWatered);
		this->newItemToReturn->initItemIDandName(25, ItemNames::WoodenWateringCan);
		break;
	case ItemNames::StoneEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Stone, tileType::pickaxableField, { 100 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemIDandName(100, ItemNames::StoneEq);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::StoneEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::WoodEq:
		this->newItemToReturn->initItemIDandName(101, ItemNames::WoodEq);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::WoodEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::Patyk:
		this->newItemToReturn->initItemIDandName(102, ItemNames::Patyk);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::Patyk, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::CopperEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Copper, tileType::pickaxableField, { 103 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemIDandName(103, ItemNames::CopperEq);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::CopperEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::IronEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Iron, tileType::pickaxableField, { 104 }, { 5 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 40);
		this->newItemToReturn->initTileBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		this->newItemToReturn->initItemIDandName(104, ItemNames::IronEq);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::IronEq, 5, TypeOfAction::Hand);
		this->newItemToReturn->initItemGraphicsData();
		break;
	case ItemNames::ChestEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Chest, tileType::chestField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 20);
		this->newItemToReturn->initTileBlockadeData({ 32,20 }, { 5,15 }, sf::FloatRect(0, 0, 32, 20));
		this->newItemToReturn->initItemIDandName(105, ItemNames::ChestEq);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::ChestEq, 5, TypeOfAction::Place);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->storageArea = this->storageCreator.initStorageArea(graphicsData, equipmentData, { 9,3 }, { 0,4 }, {}, {}, "BackgroundChest");
		break;
	case ItemNames::FurnaceEq:
		this->newItemToReturn->initTileBasicData(this->graphicsData, TextureNames::Furnace, tileType::chestField, { 0 }, { 0 });
		this->newItemToReturn->initTileGraphicData({ 0,0 }, 20);
		this->newItemToReturn->initTileBlockadeData({ 32,20 }, { 5,15 }, sf::FloatRect(0, 0, 32, 20));
		this->newItemToReturn->initItemIDandName(106, ItemNames::FurnaceEq);
		this->newItemToReturn->initItemBasicData(this->equipmentData, TextureNames::FurnaceEq, 5, TypeOfAction::Place);
		this->newItemToReturn->initItemGraphicsData();
		this->newItemToReturn->storageArea = this->storageCreator.initStorageArea(graphicsData, equipmentData, { 1,1 }, { 3,5 }, {}, { {3,7}, {5,6} }, "BackgroundFurnace");
		break;
	}

	if (this->newItemToReturn==nullptr)
		std::cout << "Brak itemu w klasie intemContructor.cpp, dodaj warunek w switchu w funkcji createItem(TextureNames nameOfTxt)!";


	return this->newItemToReturn;
}

item* ItemConstructor::createItem(ItemNames nameOfItem, int ammount)
{
	this->newItemToReturn = createItem(nameOfItem);
	this->newItemToReturn->setNumberOfItems(ammount);
	return newItemToReturn;
}

item* ItemConstructor::createItem(ItemNames nameOfItem, sf::Vector2i position2i)
{
	this->newItemToReturn = createItem(nameOfItem);
	this->newItemToReturn->initPosition(position2i);
	return newItemToReturn;
}
