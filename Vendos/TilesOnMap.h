#ifndef TILESONMAPH
#define TILESONMAPH

#include "StructuresOfData.h"

//Add functions for creating destroying etc.

class EquipmentStorageArea;

class TilesOnMap
{
private:
	GraphicsData* graphicsData{};

	int ticksToNextAction{};
	int maxDurability{ 100 };
	int remainingDurability{100};
	StorageAreas storageAreaType{};
protected:
	TextureNames nameOfTxtOfTile;

public:
	TilesOnMap() {};
	TilesOnMap(GraphicsData* graphicsData);
	/*TilesOnMap(sf::Vector2i position2i, std::string NameOfTxt, GraphicsData* graphicsData);*/
	~TilesOnMap();

	//Blockade
	bool blokade{}; //cant walk into
	sf::Vector2i sizeOfBlockade{};
	sf::Vector2f blockadeOffset{};
	sf::FloatRect* collisionBox{};

	CameraSprite* cameraSpriteOfTile{};
	
	EquipmentStorageArea* storageArea{};
	
	tileType typeOfTile{};
	std::vector<int>idOfBlocksThatDropsFromTile{};
	std::vector<int>ammountOfItemsDroppedFromTile{};

	void updateCollisionBoxPos();

	//Functions
	void update(const float& dt);
	tileType getTypeOfTile();
	const int& getTicksToNextAction() const;
	const int& getMaxDurability() const;
	const int& getRemainingDurability() const;

	void initTileBasicData(GraphicsData* graphicsData, TextureNames nameOfTxt, tileType TypeOfTile, std::vector<int>IDOfBlocksThatDropsFromTile, std::vector<int>AmmountOfItemsDroppedFromTile);
	void initTileGraphicData(sf::Vector2i origin, float offsetYcamera);
	void initTileBlockadeData(sf::Vector2i SizeOfBlockade, sf::Vector2f BlockadeOffset, sf::FloatRect BlockadeRect);
	void initPosition(sf::Vector2i position2i);

	void decreaseTicksToDisappear(int valueToDecrease);
};

#endif
