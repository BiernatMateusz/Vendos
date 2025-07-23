#include "EquipmentStorageAreaMenagement.h"

EquipmentStorageArea* EquipmentStorageAreaMenagement::initStorageArea(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots, std::string nameOfBackground)
{
	return new EquipmentStorageArea(graphicsData, equipmentData, SizeOfMainVec, FirstItemSquares, PlacesOfPickAndPlaceInRandomSpots,  PlacesOfOnlyPickableSpots, nameOfBackground);
}
