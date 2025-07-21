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

#include "CameraSprite.h"
#include "TextureData.h"

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

enum directionOfMovement { bot, right, top, left, nomov };

struct GraphicsData
{
	sf::RenderWindow* window{};
	std::vector<sf::Texture*>* GraphicsTxtVec{};
	std::map<std::string, sf::Texture*>* TexturesMap{};
	std::map<std::string, TextureData*>* TextureDataMap{};
	std::map<TextureNames, TextureData*>* TextureDataMapN{};

	sf::Sprite* backGround{};
	sf::Sprite* player{};

	std::vector<sf::Sprite*>* EntitiesSprite{};
	std::vector<sf::Sprite*>* TilesSprite{};
	std::vector<sf::Sprite*>* ItemsThrownSprite{};

	//test
	CameraSprite* backGroundMapped{};
	std::vector<CameraSprite*>* EntitiesSpriteMapped{};
	std::vector<CameraSprite*>* TilesSpriteMapped{};
	std::vector<CameraSprite*>* ItemsThrownSpriteMapped{};
	//test

	std::vector< sf::Sprite*>* AllExcludedSpritesPointer{};

	sf::Vector2f* CenterOfMap;

	directionOfMovement lastDirectionOfPlayerEnum = bot;

	std::vector<itemDroppedFromTile*>* itemDroppedVec{};

	const int tileSize{ 44 };

	RandomEngine randomEngine{};


};




#endif