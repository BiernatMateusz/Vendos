#ifndef TILESONMAPH
#define TILESONMAPH

#include "StructuresOfData.h"

class EquipmentStorageArea;

class TilesOnMap
{
private:
	
protected:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	int ticksToNextAction{};
	int maxDurability{ 100 };
	int remainingDurability{ 100 };
	StorageAreas storageAreaType{};

	TextureNames nameOfTxtOfTile{};

public:
	TilesOnMap() {};
	TilesOnMap(GraphicsData* graphicsData);
	~TilesOnMap();

	//Blockade
	bool blokade{}; //cant walk into
	sf::Vector2i sizeOfBlockade{};
	sf::Vector2f blockadeOffset{};
	sf::FloatRect* collisionBox{};
	
	sf::FloatRect txtRect{};

	CameraSprite* cameraSpriteOfTile{};
	
	EquipmentStorageArea* storageArea{};
	
	tileType typeOfTile{};
	std::vector<int>idOfBlocksThatDropsFromTile{};
	std::vector<int>ammountOfItemsDroppedFromTile{};


	//Functions
	void update(const float& dt);

	void initStorageArea(GraphicsData* graphicsData,
		EquipmentData* equipmentData,
		sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares,
		std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
		std::initializer_list<sf::Vector2i>PlacesOfOnlyPickableSpots,
		TextureNames nameOfBackground);

	void initTileBasicData(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames nameOfTxt, tileType TypeOfTile, std::vector<int>IDOfBlocksThatDropsFromTile, std::vector<int>AmmountOfItemsDroppedFromTile);
	void initTileGraphicData(sf::Vector2i origin, float offsetYcamera, sf::FloatRect TextRect);
	void initTileBlockadeData(sf::Vector2i SizeOfBlockade, sf::Vector2f BlockadeOffset, sf::FloatRect BlockadeRect);
	void initPosition(sf::Vector2i position2i);

	const int& getMaxDurability() const;
	const int& getRemainingDurability() const;

	void decreaseTicksToDisappear(int valueToDecrease);
	void updateCollisionBoxPos();


};

#endif
