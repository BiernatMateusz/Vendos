#ifndef ENTITYCONSTRUCTOR_H
#define ENTITYCONSTRUCTOR_H

#include "Entity.h"
#include "StructuresOfData.h"


class EntityConstructor
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

public:
	void init(GraphicsData* graphicsData, EquipmentData* equipmentData);

	std::unique_ptr<Entity> createEntity
	(	
		EntityNames entityType, 
		ThrownItems* ItemsOnTheGround, 
		std::vector<std::vector<std::unique_ptr<TilesOnMap>>>& Tile, 
		std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec
	);
};

#endif // !ENTITYCONSTRUCTOR_H
