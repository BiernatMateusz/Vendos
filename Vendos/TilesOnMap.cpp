#include "TilesOnMap.h"
#include "EquipmentStorageArea.h"

TilesOnMap::TilesOnMap(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->storageArea = nullptr;
	this->typeOfTile = tileType::emptyBlockade; 
	this->blokade = true;
	this->sizeOfBlockade = { 40,40 };
	
}


//TilesOnMap::~TilesOnMap()
//{
//
//	if (this->storageArea != nullptr)
//		delete this->storageArea;
//
//}

void TilesOnMap::updateCollisionBoxPos()
{
	this->collisionBox.left = cameraSpriteOnMap.getSprite().getPosition().x + this->blockadeOffset.x;
	this->collisionBox.top = cameraSpriteOnMap.getSprite().getPosition().y + this->blockadeOffset.y;
}

void TilesOnMap::update(const float& dt)
{
	//if (this->remainingDurability<=0)
	;
	//animacja rozpadu tilesa

	if (this->storageArea)
		if (this->storageArea->updateStorageAreaForTile)
			(storageArea->*storageArea->updateStorageAreaForTile)(dt);
}

void TilesOnMap::initTileStorageArea(GraphicsData* graphicsData,
	EquipmentData* equipmentData,
	sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares,
	std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
	std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
	TextureNames nameOfBackground,
	ItemNames nameOfItem,
	std::initializer_list<int>order)
{
	this->storageArea= new EquipmentStorageArea(graphicsData, equipmentData, SizeOfMainVec, FirstItemSquares, PlacesOfPickAndPlaceInRandomSpots, PlacesOfOnlyPickableSpots, nameOfBackground, order);
}

const int& TilesOnMap::getMaxDurability() const
{
	return this->maxDurability;
}

const int& TilesOnMap::getRemainingDurability() const
{
	return this->remainingDurability;
}

void TilesOnMap::initTileBasicData(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames nameOfTxt, tileType TypeOfTile, std::vector<int>IDOfBlocksThatDropsFromTile, std::vector<int>AmmountOfItemsDroppedFromTile)
{
	initSpriteOnMapBasicData(graphicsData, equipmentData, nameOfTxt);
	
	this->storageArea = nullptr;
	this->typeOfTile = TypeOfTile;
	this->idOfBlocksThatDropsFromTile = IDOfBlocksThatDropsFromTile;
	this->ammountOfItemsDroppedFromTile = AmmountOfItemsDroppedFromTile;

}

void TilesOnMap::initPosition(sf::Vector2i position2i)
{
	this->cameraSpriteOnMap.getSprite().setPosition((float)position2i.x * 44 + this->graphicsData->backGroundMapped.getSprite().getPosition().x, ((float)position2i.y) * 44 - (this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height - this->graphicsData->backGroundMapped.getSprite().getPosition().y));

	if (this->blokade == true)
	{
		this->collisionBox.left = this->cameraSpriteOnMap.getSprite().getPosition().x + this->blockadeOffset.x;
		this->collisionBox.top = this->cameraSpriteOnMap.getSprite().getPosition().y + this->blockadeOffset.y;
	}
}

void TilesOnMap::decreaseTicksToDisappear(int valueToDecrease)
{
	this->remainingDurability -= valueToDecrease;

	if (this->remainingDurability < 0)
		this->remainingDurability = 0;
}
