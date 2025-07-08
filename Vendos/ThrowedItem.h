#ifndef THROWEDITEM_H
#define THROWEDITEM_H

#include "EquipmentAreasMenagement.h"

#define M_PI 3.14159265358979323846

class ThrowedItem :
	public EquipmentAreasMenagement
{
public:
	ThrowedItem(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq, item* item, std::vector<ThrowedItem*>* ItemsThrownVec);
	ThrowedItem(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq, item* item, std::vector<ThrowedItem*>* ItemsThrownVec, sf::Vector2i TileCords);

	void update(const float& dt);

	bool checkIfCatched();

	void getAndChangeDestinationOfItem(sf::Vector2f MoveValues);
	item* getItem();

	
	
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<item*>>* Eq{};
	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq{};
	std::vector<ThrowedItem*>* ItemsThrownVec{};
	std::vector<std::vector<TilesOnMap*>>* tile;

	std::string direction{};
	directionOfMovement directionEnum;

	item* Item;
	const int range{ 100 };
	const double gravity{ 200 };
	const float v0 = 200;
	const float cos30_times_v0 = cos(M_PI * 30)*v0;
	const float sin30_times_v0 = sin(M_PI * 30)*v0;
	float offsetYofDroppedItemFromPlayer{ 30 };
	float additionalOffset{};
	sf::Vector2f distanceFlied{};
	bool firstCycle{ 1 };
	bool destinationReached{};
	bool destinationReachedONS{};
	bool droppedFromPlayer{};

	sf::Vector2f initialPosition{};
	sf::Vector2f destinationOfItem{};
	sf::Vector2f distanceToTravel{};
	float distance{};
	const float distanceMaxValueBase{ 80 };
	float distanceMaxValue{ distanceMaxValueBase };
	const float minDistanceToCatchItem{ 10 };
	const float maxDistanceToCatchItem{ 100 };
	sf::Vector2f SpeedOfFlyingItem{};
	sf::Vector2f distanceToGo{ 0,0 };

	std::vector<int>TmpAddableList{};
	std::vector<int>TmpUnAddableList{};

	sf::Vector2f calculatedDistanceToMove{};
	float timePassedWhileOnGround{};
	const float timeWhileUnableToCatch{ 3 };

	bool catchedItem{};
	sf::Vector2f distanceToPlayer{};

	float tmpX, tmpY;

	void calculateMoveDistanceItemFromPlayer();
	void setDistanceToMoveBasedOnDirection();
	bool checkDistanceItemToPlayer();
	
	void makeUnpickableItemsList();
	void itemMovementTowardsDestination(const float& dt);
	void accumulateTimeOfItemOnGround(const float& dt);

	void setItemDestination();
	void setItemDestinationFromTile();
	void setItemParametersFromPlayer();
	void setItemParametersFromTile(sf::Vector2i tileCord);

	void compareAddableAndUnaddableList();

	void itemMovementThrewnFromPlayer(const float& dt);
	void itemMovementThrewnFromNonPlayer(const float& dt);
};

#endif // !THROWEDITEM_H