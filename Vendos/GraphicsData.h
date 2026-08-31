#ifndef GRAPHICSDATA_H
#define GRAPHICSDATA_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>

#include <set>
#include <algorithm>
#include <ctime> 
#include <random> 
#include <unordered_map>

#include "CameraSprite.h"
#include "TextureData.h"

class ThrownItems;

struct RandomEngine
{
	std::random_device rd;
	std::mt19937 mt{ rd() };
};

struct itemDroppedFromTile
{
	sf::Vector2i tileCords{};
	int itemID{};
	int ammountOfItem{};
};

enum class directionOfMovement { bot, right, top, left, nomov };

struct GraphicsData
{
	sf::RenderWindow* window{};
	std::map<TextureNames, TextureData*> TexturesData{};

	sf::Font font{};

	CameraSprite* player = nullptr; //Not ownership

	//test
	CameraSprite backGroundMapped{};
	std::vector<CameraSprite*> EntitiesSpriteMapped{};
	std::vector<CameraSprite*> TilesSpriteMapped{};
	ThrownItems* thrownItems;
	//test

	sf::Vector2f CenterOfMap;

	directionOfMovement lastDirectionOfPlayerEnum = directionOfMovement::bot;

	std::vector<itemDroppedFromTile*> itemDroppedVec{};

	const int tileSize{ 44 };

	RandomEngine randomEngine{};


};




#endif