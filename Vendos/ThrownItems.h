#ifndef THROWNITEMS_H
#define THROWNITEMS_H

#include <iostream>
#include "ThrowedItem.h"
#include "itemConstructor.h"
#include "item.h"
#include "EquipmentAreasMenagement.h"

class ThrownItems:public EquipmentAreasMenagement
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	ItemConstructor itemCreator{};
	
	ItemStorage* storage;

	std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* tile;
	std::vector<std::unique_ptr<ThrowedItem>>ItemsThrownVec{};

	std::set<int>Pickable_ID_Items{};

	void createPickable_ID_ItemsList();


public:
	//Constructors
	ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile);

	const std::vector<std::unique_ptr<ThrowedItem>>& getItems() const;

	void update(const float& dt, EquipmentStorageArea* storageArea);
	void initEqPtr(ItemStorage* storage);
	void insertItemDroppedFromPlayer(std::unique_ptr<item> itemToAdd);
	void insertItemDroppedFromTile(std::unique_ptr<item> itemToAdd, sf::Vector2i tileCord);

	void setNumberOfItemsLastInVector(int value);

	void setUpdateCamera();
	void updatePositionOfEach(const float& dt, float speedX, float speedY);
	void checkIfNewItemDropped();
	bool checkIfPickPossible(ThrowedItem& throwedItem);
};

#endif 