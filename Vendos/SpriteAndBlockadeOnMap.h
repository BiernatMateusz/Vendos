#ifndef SPRITEANDBLOCKADEONMAP_H
#define SPRITEANDBLOCKADEONMAP_H

#include "StructuresOfData.h"

class SpriteAndBlockadeOnMap
{
public:
	bool isBlockade();

	//Init
	void initSpriteOnMapBasicData(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames nameOfTxt);
	void initSpriteOnMapGraphicData(sf::Vector2i origin, float offsetYcamera, sf::FloatRect TextRect);
	void initSpriteOnMapBlockadeData(sf::Vector2i SizeOfBlockade, sf::Vector2f BlockadeOffset, sf::FloatRect BlockadeRect);

	//getters
	sf::FloatRect& getCollisionBox();
	CameraSprite& getCameraSpriteOnMap();
protected:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	//Core Txt data
	TextureNames nameOfTxtOfTile{};
	CameraSprite cameraSpriteOnMap{};

	//Blockade
	bool blokade{}; //cant walk into
	sf::Vector2i sizeOfBlockade{};
	sf::Vector2f blockadeOffset{};
	sf::FloatRect collisionBox{};
	sf::FloatRect txtRect{};



private:
};

#endif // !SPRITEANDBLOCKADE_H