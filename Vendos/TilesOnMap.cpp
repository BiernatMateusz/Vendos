#include "TilesOnMap.h"
#include "EquipmentStorageArea.h"

TilesOnMap::TilesOnMap(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->storageArea = nullptr;
	this->cameraSpriteOfTile = nullptr;
	this->typeOfTile = tileType::emptyBlockade; 
	this->blokade = true;
	this->sizeOfBlockade = { 40,40 };
	
}


TilesOnMap::~TilesOnMap()
{
	delete this->cameraSpriteOfTile;
	delete this->collisionBox;

	if (this->storageArea != nullptr)
		delete this->storageArea;

}

void TilesOnMap::updateCollisionBoxPos()
{
	this->collisionBox->left = cameraSpriteOfTile->getSprite()->getPosition().x + this->blockadeOffset.x;
	this->collisionBox->top = cameraSpriteOfTile->getSprite()->getPosition().y + this->blockadeOffset.y;
}

void TilesOnMap::update(const float& dt)
{
	//if (this->remainingDurability<=0)
	;
	//animacja rozpadu tilesa

	if (this->storageArea != nullptr)
		; // std::cout << "Cos robi\n";
}

void TilesOnMap::initStorageArea(GraphicsData* graphicsData,
	EquipmentData* equipmentData,
	sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares,
	std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
	std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
	TextureNames nameOfBackground)
{
	this->storageArea= new EquipmentStorageArea(graphicsData, equipmentData, SizeOfMainVec, FirstItemSquares, PlacesOfPickAndPlaceInRandomSpots, PlacesOfOnlyPickableSpots, nameOfBackground);
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
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->storageArea = nullptr;
	this->nameOfTxtOfTile = nameOfTxt;
	

	this->typeOfTile = TypeOfTile;
	this->idOfBlocksThatDropsFromTile = IDOfBlocksThatDropsFromTile;
	this->ammountOfItemsDroppedFromTile = AmmountOfItemsDroppedFromTile;

}

void TilesOnMap::initTileGraphicData(sf::Vector2i origin, float offsetYcamera, sf::FloatRect BlockadeRect)
{
	this->cameraSpriteOfTile = new CameraSprite;
	this->cameraSpriteOfTile->setSpriteTexture(*this->graphicsData->TextureDataMapN->at(this->nameOfTxtOfTile)->texture);
	this->cameraSpriteOfTile->getSprite()->setOrigin(origin.x, origin.y);
	this->cameraSpriteOfTile->distance = offsetYcamera;
	this->cameraSpriteOfTile->getSprite()->setTextureRect((sf::IntRect)BlockadeRect);
}

void TilesOnMap::initTileBlockadeData(sf::Vector2i SizeOfBlockade, sf::Vector2f BlockadeOffset, sf::FloatRect BlockadeRect)
{
	this->blokade = true;
	this->sizeOfBlockade = SizeOfBlockade;
	this->blockadeOffset = BlockadeOffset;
	this->collisionBox = new sf::FloatRect;
	*this->collisionBox = BlockadeRect;
	
}

void TilesOnMap::initPosition(sf::Vector2i position2i)
{
	this->cameraSpriteOfTile->getSprite()->setPosition((float)position2i.x * 44 + this->graphicsData->backGroundMapped->getSprite()->getPosition().x, ((float)position2i.y) * 44 - (this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height - this->graphicsData->backGroundMapped->getSprite()->getPosition().y));

	if (this->blokade == true)
	{
		this->collisionBox->left = this->cameraSpriteOfTile->getSprite()->getPosition().x + this->blockadeOffset.x;
		this->collisionBox->top = this->cameraSpriteOfTile->getSprite()->getPosition().y + this->blockadeOffset.y;
	}
}

void TilesOnMap::decreaseTicksToDisappear(int valueToDecrease)
{
	this->remainingDurability -= valueToDecrease;

	if (this->remainingDurability < 0)
		this->remainingDurability = 0;
}
