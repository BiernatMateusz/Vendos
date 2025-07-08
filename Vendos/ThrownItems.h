#ifndef THROWNITEMS_H
#define THROWNITEMS_H

#include <iostream>
#include "ThrowedItem.h"
#include "itemConstructor.h"
#include "itemAndItsPosition.h"

class ThrownItems
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	ItemConstructor itemCreator{};

	
	bool catchedItem{};

	std::vector<int> OrderOfSearch{ 0,2,1 };
	
	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq{};
	std::vector<std::vector<TilesOnMap*>>* tile;

	std::vector<ThrowedItem*>* ItemsThrownVec{};
	
	std::vector<sf::Sprite*>SprToDeleteVec{};
	sf::Sprite* SprToDelete{};
	bool itemToDeleteFound{};

public:
	//Constructors
	ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile);

	void update(const float& dt);
	void initEqPtr(std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq);
	void insertItemDroppedFromPlayer(item* itemToAdd);
	void insertItemDroppedFromTile(item* itemToAdd, sf::Vector2i tileCord);

	void setNumberOfItemsLastInVector(int value);

	void updateItemsThrownSpriteVec();
	void updatePositionOfEach(const float& dt, float speedX, float speedY);
	void checkIfItemDropped();
};

#endif 