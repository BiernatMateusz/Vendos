#ifndef EQUIPMENTSTORAGEAREA_H
#define EQUIPMENTSTORAGEAREA_H

#include "Workstation.h"
#include "item.h"
#include "ItemConstructor.h"

class slotInStorages;

class EquipmentStorageArea:
	public Workstation
{
protected:
	ItemConstructor factoryOfItems;


public:
	EquipmentStorageArea();

	EquipmentStorageArea(
		GraphicsData* graphicsData, 
		EquipmentData* equipmentData, 
		sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, 
		std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, 
		std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
		TextureNames name,
		std::initializer_list<int>order);

	~EquipmentStorageArea() = default;

	void makeUsableSpots(sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots);

	virtual void updateActiveStorage(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void (EquipmentStorageArea::*updateStorageAreaForTile)(const float& dt) {};

	virtual void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	void updatePositionOfItems();

	void render();

	//need update which is always happening 
	//second update happening only when opened
};

#endif // !EQUIPMENTSTORAGEAREA_H