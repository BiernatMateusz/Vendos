#include "Entity.h"

Entity::Entity(GraphicsData* graphicsData, std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec) : EntityPlayer(CollisionTilesVec)
{
	this->graphicsData = graphicsData;
}

Entity::~Entity()
{
	//delete this->collisionBox;
}

void Entity::pushSpriteToMainEntitiesVector()
{
	this->graphicsData->EntitiesSpriteMapped.push_back(&cameraSpriteOnMap);
}

void Entity::initCamera(Camera* Camer)
{
	this->camer = Camer;
}

void Entity::initEntityBasicData(ThrownItems* ItemsOnTheGround, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile, std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec)
{
	this->ItemsOnTheGround = ItemsOnTheGround;
	this->Tile = Tile;
	this->CollisionTilesVec = CollisionTilesVec;

	pushSpriteToMainEntitiesVector();
}


