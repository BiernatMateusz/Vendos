#ifndef TILESONMAPH
#define TILESONMAPH

#include "StructuresOfData.h"

//Add functions for creating destroying etc.

class itemChest;
class EquipmentStorageArea;

class TilesOnMap
{
private:
	GraphicsData* graphicsData;

	int ticksToNextAction{};
	int maxDurability{ 100 };
	int remainingDurability{100};
	StorageAreas storageAreaType{};

public:
	TilesOnMap(GraphicsData* graphicsData);
	TilesOnMap(sf::Vector2i position2i, std::string NameOfTxt, GraphicsData* graphicsData);
	~TilesOnMap();

	static const int tileSize{ 44 };

	//Blockade
	bool blokade{}; //cant walk into
	sf::Vector2i sizeOfBlockade{};
	sf::Vector2f blockadeOffset{};
	sf::FloatRect* collisionBox{};

	CameraSprite* cameraSprite{};
	
	EquipmentStorageArea* storageArea{};

	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	//5 - hoed tiles - able to make croops here (no water)
	//6 - watered - able to make croops here and it will grow on here
	//7 - pure blockade
	//8 - chests - left->destroy right->open
	//9 - player
	
	tileType typeOfTile{};
	std::vector<int>idOfBlocksThatDropsFromTile{};
	std::vector<int>ammountOfItemsDroppedFromTile{};

	void updateCollisionBoxPos();

	static const int GetSizeOfTile()
	{
		return tileSize;
	}

	//Functions
	void update(const float& dt);
	tileType getTypeOfTile();
	const int& getTicksToNextAction() const;
	const int& getMaxDurability() const;
	const int& getRemainingDurability() const;

	void decreaseTicksToDisappear(int valueToDecrease);
};

#endif
