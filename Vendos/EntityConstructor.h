#ifndef ENTITYCONSTRUCTOR_H
#define ENTITYCONSTRUCTOR_H

#include "Entity.h"
#include "StructuresOfData.h"


class EntityConstructor
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	Entity* newEntityToReturn{};
public:
	void init(GraphicsData* graphicsData, EquipmentData* equipmentData);

	Entity* createEntity(EntityNames nameOfItem, ThrownItems* ItemsOnTheGround, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector<sf::FloatRect*>* collisionTilesVec);
};

#endif // !ENTITYCONSTRUCTOR_H
