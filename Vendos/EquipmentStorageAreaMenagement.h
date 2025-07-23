#ifndef EQUIPMENTSTORAGEAREAMENAGEMENT_H
#define EQUIPMENTSTORAGEAREAMENAGEMENT_H

#include "item.h"
#include "EquipmentStorageArea.h"

class EquipmentStorageAreaMenagement
{
public:
	EquipmentStorageArea* initStorageArea(GraphicsData* graphicsData,
		EquipmentData* equipmentData,
		sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares,
		std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
		std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
		std::string nameOfBackground);
};

#endif