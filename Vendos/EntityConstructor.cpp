#include "EntityConstructor.h"

void EntityConstructor::init(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

Entity* EntityConstructor::createEntity(EntityNames nameOfItem, ThrownItems* ItemsOnTheGround, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector<sf::FloatRect*>* collisionTilesVec)
{
	if (this->newEntityToReturn != nullptr)
		this->newEntityToReturn = nullptr;

	this->newEntityToReturn = new Entity(graphicsData);
	
	switch (nameOfItem)
	{
	case EntityNames::Player:
		this->newEntityToReturn->initTileBasicData(this->graphicsData, this->equipmentData, TextureNames::Abigail, tileType::player, { 0 }, { 0 });
		this->newEntityToReturn->initTileGraphicData({ 7,78 }, 0, sf::FloatRect(22, 20, 40, 85));
		this->newEntityToReturn->initTileBlockadeData({ 30,15 }, { 0,-15 }, sf::FloatRect(0, 0, 30, 15));
		this->newEntityToReturn->initEntityBasicData(ItemsOnTheGround, Tile, collisionTilesVec);
		this->newEntityToReturn->setTextData();
		this->newEntityToReturn->initPlayer();
		this->newEntityToReturn->initStartingPositionOfEntity();

		break;
	}

	return this->newEntityToReturn;
}

