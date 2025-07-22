#ifndef EQUIPMENTSTORAGEAREA_H
#define EQUIPMENTSTORAGEAREA_H

#include "Workstation.h"
#include "itemAndItsPosition.h"

class EquipmentStorageArea:
	public Workstation
{
private:
	const sf::Vector2i sizeOfArea{ 9, 10 };
	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* items{}; //bool - true if spot is usable

public:
	EquipmentStorageArea();
	EquipmentStorageArea(
		GraphicsData* graphicsData, 
		EquipmentData* equipmentData, 
		sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, 
		std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, 
		std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
		std::string nameOfBackground);

	~EquipmentStorageArea();

	void resizeVector();
	void makeUsableSpots(sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots);
	void setItemTypes(std::initializer_list<sf::Vector2i>Places, typeOfItemArea itemType);

	virtual void update(const float& dt, const std::map<std::string, button*>& AllKeys) {};

	

	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* getItemsArea();
};

#endif // !EQUIPMENTSTORAGEAREA_H