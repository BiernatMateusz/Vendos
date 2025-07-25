#include "Entity.h"

Entity::Entity(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
}

Entity::~Entity()
{
	delete this->cameraSpriteOfTile;
	delete this->collisionBox;
}

void Entity::setTextData()
{
	this->graphicsData->EntitiesSprite->push_back(this->cameraSpriteOfTile->getSprite());

	this->graphicsData->EntitiesSpriteMapped->push_back(cameraSpriteOfTile);

	//this->txtRect = new sf::FloatRect;
	//*this->textureRect = this->graphicsData->TextureDataMapN->at(this->nameOfTxtOfTile)->TextRect;

}

void Entity::initCamera(Camera* Camer)
{
	this->camer = Camer;
}

void Entity::initEntityBasicData(ThrownItems* ItemsOnTheGround, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector<sf::FloatRect*>* collisionTilesVec)
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
