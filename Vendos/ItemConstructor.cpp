#include "ItemConstructor.h"


void ItemConstructor::init(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

std::unique_ptr<item> ItemConstructor::createItem(int itemID, int ammount)
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

std::unique_ptr<item> ItemConstructor::createItem(ItemNames nameOfItem)
{

	auto createdItem = std::make_unique<item>(this->graphicsData);

	switch (nameOfItem)
	{
	case ItemNames::HoedNoWater:
		createdItem->initTileBasicData(this->graphicsData,this->equipmentData, TextureNames::HoedNoWater, tileType::hoedField, { 0 }, { 0 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, -44, sf::FloatRect(0,0,0,0));
		createdItem->initItemIDandName(3, ItemNames::HoedNoWater);
		break;
	case ItemNames::HoedWatered:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::HoedWatered, tileType::wateredField, { 0 }, { 0 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, -44, sf::FloatRect(0, 0, 0, 0));
		createdItem->initItemIDandName(4, ItemNames::HoedWatered);
		break;
	case ItemNames::Tree1:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Tree1, tileType::axableField, { 101 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 50,160 }, 33, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,30 }, { 6,8 }, sf::FloatRect(0, 0, 30, 22));
		createdItem->initItemIDandName(10, ItemNames::Tree1);
		break;
	case ItemNames::Tree2:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Tree2,  tileType::axableField, { 101 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 68,162 }, 33, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,18 }, { 8,19 }, sf::FloatRect(0, 0, 30, 18));
		createdItem->initItemIDandName(11, ItemNames::Tree2);
		break;
	case ItemNames::Tree3:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Tree3, tileType::axableField, { 101 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 42,135 }, 33, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,16 }, { 12,24 }, sf::FloatRect(0, 0, 30, 14));
		createdItem->initItemIDandName(12, ItemNames::Tree3);
		break;
	case ItemNames::BushEmpty:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::BushEmpty, tileType::axableField, { 102 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 40, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,20 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		createdItem->initItemIDandName(13, ItemNames::BushEmpty);
		break;
	case ItemNames::EmptyTile:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::EmptyTile, tileType::emptyBlockade, { 0 }, { 0 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 0, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 29,29 }, { 0,0 }, sf::FloatRect(0, 0, 29, 29));
		createdItem->initItemIDandName(0, ItemNames::EmptyTile);
		break;
	case ItemNames::WoodenHoe:
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodenHoe, 1, TypeOfAction::Replace);
		createdItem->initItemGraphicsData();
		createdItem->initToolReplace({tileType::emptyField, tileType::crop}, QualityOfTool::Wooden, true, ItemNames::HoedNoWater);
		createdItem->initItemIDandName(20, ItemNames::WoodenHoe);
		break;
	case ItemNames::WoodenPickaxe:
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodenPickaxe, 1, TypeOfAction::Drop);
		createdItem->initItemGraphicsData();
		createdItem->initToolDrop({ tileType::pickaxableField }, QualityOfTool::Wooden);
		createdItem->initItemIDandName(21, ItemNames::WoodenPickaxe);
		break;
	case ItemNames::WoodenAxe:
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodenAxe, 1, TypeOfAction::Drop);
		createdItem->initItemGraphicsData();
		createdItem->initToolDrop({ tileType::axableField }, QualityOfTool::Wooden);
		createdItem->initItemIDandName(22, ItemNames::WoodenAxe);
		break;
	case ItemNames::WoodenSword:
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodenSword, 1, TypeOfAction::Attack);
		createdItem->initItemGraphicsData();
		createdItem->initItemIDandName(23, ItemNames::WoodenSword);
		break;
	case ItemNames::WoodenShovel:
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodenShovel, 1, TypeOfAction::Drop);
		createdItem->initItemGraphicsData();
		createdItem->initToolDrop({ tileType::pickaxableField }, QualityOfTool::Wooden);
		createdItem->initItemIDandName(24, ItemNames::WoodenShovel);
		break;
	case ItemNames::WoodenWateringCan:
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodenWateringCan, 1, TypeOfAction::Replace);
		createdItem->initItemGraphicsData();
		createdItem->initToolReplace({ tileType::hoedField}, QualityOfTool::Wooden, false, ItemNames::HoedWatered);
		createdItem->initItemIDandName(25, ItemNames::WoodenWateringCan);
		break;
	case ItemNames::StoneEq:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Stone, tileType::pickaxableField, { 100 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 40, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		createdItem->initItemIDandName(100, ItemNames::StoneEq);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::StoneEq, 5, TypeOfAction::Hand);
		createdItem->initItemGraphicsData();
		break;
	case ItemNames::WoodEq:
		createdItem->initItemIDandName(101, ItemNames::WoodEq);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::WoodEq, 5, TypeOfAction::Hand);
		createdItem->initItemGraphicsData();
		break;
	case ItemNames::Patyk:
		createdItem->initItemIDandName(102, ItemNames::Patyk);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::Patyk, 5, TypeOfAction::Hand);
		createdItem->initItemGraphicsData();
		break;
	case ItemNames::CopperEq:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Copper, tileType::pickaxableField, { 103 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 40, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		createdItem->initItemIDandName(103, ItemNames::CopperEq);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::CopperEq, 5, TypeOfAction::Hand);
		createdItem->initItemGraphicsData();
		break;
	case ItemNames::IronEq:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Iron, tileType::pickaxableField, { 104 }, { 5 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 40, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 30,25 }, { 7,25 }, sf::FloatRect(0, 0, 30, 15));
		createdItem->initItemIDandName(104, ItemNames::IronEq);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::IronEq, 5, TypeOfAction::Hand);
		createdItem->initItemGraphicsData();
		break;
	case ItemNames::ChestEq:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Chest, tileType::chestField, { 0 }, { 0 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 20, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 32,20 }, { 5,15 }, sf::FloatRect(0, 0, 32, 20));
		createdItem->initItemIDandName(105, ItemNames::ChestEq);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::ChestEq, 5, TypeOfAction::Place);
		createdItem->initItemGraphicsData();
		createdItem->initTileStorageArea(graphicsData, equipmentData, { 9,3 }, { 0,4 }, {}, {}, TextureNames::BackgroundChest, ItemNames::ChestEq, {6,5,4});
		break;
	case ItemNames::FurnaceEq:
		createdItem->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Furnace, tileType::chestField, { 0 }, { 0 });
		createdItem->initSpriteOnMapGraphicData({ 0,0 }, 20, sf::FloatRect(0, 0, 0, 0));
		createdItem->initSpriteOnMapBlockadeData({ 32,20 }, { 5,15 }, sf::FloatRect(0, 0, 32, 20));
		createdItem->initItemIDandName(106, ItemNames::FurnaceEq);
		createdItem->initItemBasicData(this->equipmentData, TextureNames::FurnaceEq, 5, TypeOfAction::Place);
		createdItem->initItemGraphicsData();
		createdItem->initTileStorageArea(graphicsData, equipmentData, { 1,1 }, { 3,5 }, { {3,7} }, { {5,6} }, TextureNames::BackgroundFurnace, ItemNames::FurnaceEq, { 7 });
		break;
	default:
		std::cout << "Brak obs³ugi ItemNames w ItemConstructor\n";
		return nullptr;
	}

	return createdItem;
}

std::unique_ptr<item> ItemConstructor::createItem(ItemNames nameOfItem, int ammount)
{
	auto createdItem = createItem(nameOfItem);
	createdItem->setNumberOfItems(ammount);
	return createdItem;
}

std::unique_ptr<item> ItemConstructor::createItem(ItemNames nameOfItem, sf::Vector2i position2i)
{
	auto createdItem = createItem(nameOfItem);
	createdItem->initPosition(position2i);
	
	return createdItem;
}
