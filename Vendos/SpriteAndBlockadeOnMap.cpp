#include "SpriteAndBlockadeOnMap.h"

void SpriteAndBlockadeOnMap::initSpriteOnMapBasicData(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames nameOfTxt)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->nameOfTxtOfTile = nameOfTxt;
}

void SpriteAndBlockadeOnMap::initSpriteOnMapGraphicData(sf::Vector2i origin, float offsetYcamera, sf::FloatRect TextRect)
{
	this->cameraSpriteOnMap.setTexture(*this->graphicsData->TexturesData.at(this->nameOfTxtOfTile)->texture);
	this->cameraSpriteOnMap.setOrigin((sf::Vector2f)origin);
	this->cameraSpriteOnMap.setDistance(offsetYcamera);

	if (TextRect != sf::FloatRect(0, 0, 0, 0))
	{
		this->cameraSpriteOnMap.getSprite().setTextureRect((sf::IntRect)TextRect);
		this->txtRect = TextRect;
	}
}

void SpriteAndBlockadeOnMap::initSpriteOnMapBlockadeData(sf::Vector2i SizeOfBlockade, sf::Vector2f BlockadeOffset, sf::FloatRect BlockadeRect)
{
	this->blokade = true;
	this->sizeOfBlockade = SizeOfBlockade;
	this->blockadeOffset = BlockadeOffset;
	this->collisionBox = BlockadeRect;
}

bool SpriteAndBlockadeOnMap::isBlockade()
{
    return this->blokade;
}

sf::FloatRect& SpriteAndBlockadeOnMap::getCollisionBox()
{
    return this->collisionBox;
}

CameraSprite& SpriteAndBlockadeOnMap::getCameraSpriteOnMap()
{
    return this->cameraSpriteOnMap;
}
