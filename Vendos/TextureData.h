#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>

//Name of every texture 
enum class TextureNames
{
	Menu,
	Mapka,
	Abigail, 
	HoedNoWater,
	HoedWatered,
	Stone,
	Copper,
	Iron,
	Tree1,
	Tree2,
	Tree3,
	BushEmpty,
	EmptyTile,
	Furnace,
	Chest, 
	WoodenHoe,
	WoodenPickaxe,
	WoodenAxe,
	WoodenSword,
	WoodenShovel,
	WoodenWateringCan,
	StoneEq,
	WoodEq,
	Patyk,
	CopperEq,
	IronEq,
	ChestEq,
	FurnaceEq,
	ramka,
	ramka1,
	BackgroundCrafting,
	BackgroundChest,
	BackgroundFurnace
};

//list of every item (tileable only are items too)
enum class ItemNames
{
	HoedNoWater,
	HoedWatered,
	Tree1,
	Tree2,
	Tree3,
	BushEmpty,
	EmptyTile,
	WoodenHoe,
	WoodenPickaxe,
	WoodenAxe,
	WoodenSword,
	WoodenShovel,
	WoodenWateringCan,
	StoneEq,
	WoodEq,
	Patyk,
	CopperEq,
	IronEq,
	ChestEq,
	FurnaceEq

};

enum class StorageAreas { Empty, Chest, Crafting, Furnace };
enum class tileType { emptyField, crop, axableField, pickaxableField, hoedField, wateredField, emptyBlockade, chestField, player };

struct TextureData
{
	sf::Vector2i origin{};
	sf::Texture* texture{};
	float offsetForPositonY{};

	float offsetForCamera{};
	sf::Vector2f offsetForBlockade{};
	bool blockade{}; //cant walk into
	sf::Vector2i blockadeSize{};
	tileType typeOfTile{};
	std::vector<int>idOfItemsThatDropsFromTile{};
	std::vector<int>ammountOfDroppedItems{};
	int itemID{};

	sf::FloatRect TextRect{};
	sf::FloatRect blockadeRect{};

	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	//5 - hoed tiles - able to make croops here (no water)
	//6 - watered - able to make croops here and it will grow on here
	//7 - pure blockade
	//8 - chests - left->destroy right->open
	//9 - player

	StorageAreas storageArea{};

	std::vector<std::vector<bool>>blocksOccupied;
	void initBlocksOccupied(std::string nameOfTxt)
	{
		if (nameOfTxt == "Mapka")
		{
			std::vector<std::vector<bool>> twoDVector(this->texture->getSize().x / 44, std::vector<bool>(this->texture->getSize().y / 44, false));
			blocksOccupied = twoDVector;
		}
	}

};





#endif // !TEXTUREDATA_H
