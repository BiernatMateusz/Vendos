#include "Entity.h"

Entity::Entity(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
}

Entity::Entity(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* tile, std::vector<sf::FloatRect*>* collisionTilesVec, EquipmentData* equipmentData)
{
	initTexture(NameOfTxt,std::move(position));
	//setTextData(NameOfTxt);
}

Entity::~Entity()
{
	delete this->textureRect;
	delete this->cameraSpriteOfTile;
	delete this->collisionBox;
}

void Entity::initTexture(std::string NameOfTxt, sf::Vector2f &&position)
{
	this->textureRect = new sf::FloatRect;
	*this->textureRect = this->graphicsData->TextureDataMap->at(NameOfTxt)->TextRect;

	this->cameraSpriteOfTile = new CameraSprite;
	this->cameraSpriteOfTile->setSpriteTexture(*this->graphicsData->TextureDataMap->at(NameOfTxt)->texture);
	this->cameraSpriteOfTile->getSprite()->setOrigin(this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.x, this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.y);
	this->cameraSpriteOfTile->setDistance(this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForCamera);
	this->cameraSpriteOfTile->getSprite()->setPosition(position.x, position.y);

}

void Entity::setTextData()
{
	this->graphicsData->EntitiesSprite->push_back(this->cameraSpriteOfTile->getSprite());

	this->graphicsData->EntitiesSpriteMapped->push_back(cameraSpriteOfTile);

	this->cameraSpriteOfTile->getSprite()->setTextureRect((sf::IntRect)this->graphicsData->TextureDataMapN->at(this->nameOfTxtOfTile)->TextRect);
	this->textureRect = new sf::FloatRect;
	*this->textureRect = this->graphicsData->TextureDataMapN->at(this->nameOfTxtOfTile)->TextRect;
}

void Entity::initCamera(Camera* Camer)
{
	this->camer = Camer;
}

void Entity::initBasicData(ThrownItems* ItemsOnTheGround, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector<sf::FloatRect*>* collisionTilesVec)
{
	this->ItemsOnTheGround = ItemsOnTheGround;
	this->Tile = Tile;
	this->CollisionTilesVec = collisionTilesVec;
}

void Entity::initStartingPositionOfEntity()
{
	getCenterOfScreen();
	this->cameraSpriteOfTile->getSprite()->setPosition(this->centerOfGame);
}
