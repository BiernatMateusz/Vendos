#ifndef TILESONMAPH
#define TILESONMAPH

#include "StructuresOfData.h"
#include "SpriteAndBlockadeOnMap.h"

class EquipmentStorageArea;

class TilesOnMap : public SpriteAndBlockadeOnMap
{
private:
	
protected:
	int ticksToNextAction{};
	int maxDurability{ 100 };
	int remainingDurability{ 100 };
	StorageAreas storageAreaType{};

	

public:
	TilesOnMap() {};
	TilesOnMap(GraphicsData* graphicsData);
	virtual ~TilesOnMap() = default;
	
	EquipmentStorageArea* storageArea{};
	
	tileType typeOfTile{};
	std::vector<int>idOfBlocksThatDropsFromTile{};
	std::vector<int>ammountOfItemsDroppedFromTile{};


	//Functions
	void update(const float& dt);

	void initTileStorageArea(GraphicsData* graphicsData,
		EquipmentData* equipmentData,
		sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares,
		std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
		std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
		TextureNames nameOfBackground,
		ItemNames nameOfItem,
		std::initializer_list<int>order);

	void initTileBasicData(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames nameOfTxt, tileType TypeOfTile, std::vector<int>IDOfBlocksThatDropsFromTile, std::vector<int>AmmountOfItemsDroppedFromTile);
	
	void initPosition(sf::Vector2i position2i);

	const int& getMaxDurability() const;
	const int& getRemainingDurability() const;

	void decreaseTicksToDisappear(int valueToDecrease);
	void updateCollisionBoxPos();


};

#endif
