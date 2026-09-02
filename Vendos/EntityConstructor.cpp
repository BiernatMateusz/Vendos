#include "EntityConstructor.h"

void EntityConstructor::init(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

std::unique_ptr<Entity> EntityConstructor::createEntity(EntityNames entityType, ThrownItems* ItemsOnTheGround, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>& Tile,
	std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec)
{
	auto entity = std::make_unique<Entity>(graphicsData, CollisionTilesVec);

	switch (entityType)
	{
	case EntityNames::Player:
		entity->initSpriteOnMapBasicData(this->graphicsData, this->equipmentData, TextureNames::Abigail);
		entity->initSpriteOnMapGraphicData({ 7,78 }, 0, sf::FloatRect(22, 20, 40, 85));
		entity->initSpriteOnMapBlockadeData({ 30,15 }, { 0,-15 }, sf::FloatRect(0, 0, 30, 15));
		entity->initEntityBasicData(ItemsOnTheGround, Tile, CollisionTilesVec);
		entity->initPlayer(this->graphicsData->CenterOfMap);
		break;
	default:
		throw std::runtime_error("Unknown EntityNames");
	}
	

	return entity;
}

