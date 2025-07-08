#include "TilesOnMap.h"

TilesOnMap::TilesOnMap(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->storageArea = nullptr;
	this->cameraSprite = nullptr;
	this->typeOfTile = tileType::emptyBlockade; 
	this->blokade = 1;
	this->sizeOfBlockade = { 40,40 };
	
}

TilesOnMap::TilesOnMap(sf::Vector2i position2i, std::string NameOfTxt, GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->storageArea = nullptr;
	this->cameraSprite = new CameraSprite;
	this->cameraSprite->setSpriteTexture(*this->graphicsData->TextureDataMap->at(NameOfTxt)->texture);
	this->cameraSprite->getSprite()->setOrigin(this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.x, this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.y);
	this->cameraSprite->getSprite()->setPosition((float)position2i.x * 44 + this->graphicsData->backGroundMapped->getSprite()->getPosition().x, ((float)position2i.y) * 44 - (this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height - this->graphicsData->backGroundMapped->getSprite()->getPosition().y));
	
	this->blokade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockade;

	this->cameraSprite->distance = this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForCamera;

	if (this->blokade == 1)
	{
		this->sizeOfBlockade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockadeSize;
		this->blockadeOffset= this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForBlockade;
		this->collisionBox = new sf::FloatRect;
		*this->collisionBox = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockadeRect;
		this->collisionBox->left = this->cameraSprite->getSprite()->getPosition().x + this->blockadeOffset.x;
		this->collisionBox->top = this->cameraSprite->getSprite()->getPosition().y + this->blockadeOffset.y;
	}

	this->typeOfTile = this->graphicsData->TextureDataMap->at(NameOfTxt)->typeOfTile;
	this->idOfBlocksThatDropsFromTile = this->graphicsData->TextureDataMap->at(NameOfTxt)->idOfItemsThatDropsFromTile;
	this->ammountOfItemsDroppedFromTile = this->graphicsData->TextureDataMap->at(NameOfTxt)->ammountOfDroppedItems;

}

TilesOnMap::~TilesOnMap()
{
	delete this->cameraSprite;
	delete this->collisionBox;

	if (this->storageArea != nullptr)
		delete this->storageArea;

}

void TilesOnMap::updateCollisionBoxPos()
{
	this->collisionBox->left = cameraSprite->getSprite()->getPosition().x + this->blockadeOffset.x;
	this->collisionBox->top = cameraSprite->getSprite()->getPosition().y + this->blockadeOffset.y;
}

void TilesOnMap::update(const float& dt)
{
	//if (this->remainingDurability<=0)
	;
	//animacja rozpadu tilesa

	if (this->storageArea != nullptr)
		; //std::cout << "Cos robi\n";
}

tileType TilesOnMap::getTypeOfTile()
{
	return this->typeOfTile;
}

const int& TilesOnMap::getTicksToNextAction() const
{
	return this->ticksToNextAction;
}

const int& TilesOnMap::getMaxDurability() const
{
	return this->maxDurability;
}

const int& TilesOnMap::getRemainingDurability() const
{
	return this->remainingDurability;
}

void TilesOnMap::decreaseTicksToDisappear(int valueToDecrease)
{
	this->remainingDurability -= valueToDecrease;

	if (this->remainingDurability < 0)
		this->remainingDurability = 0;
}
