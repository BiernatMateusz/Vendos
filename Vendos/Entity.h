#ifndef ENTITY_H
#define ENTITY_H

#define EE_MCR_AVERAGER_BEGIN(x) sf::Clock EEAV_CLOCK_##x; static sf::Int64 EEAV_MS_##x=0; static int EEAV_FR_##x=0;
#define EE_MCR_AVERAGER_END(x) std::cout<<"Averaging clock("#x"):"<<(EEAV_MS_##x+=EEAV_CLOCK_##x.getElapsedTime().asMicroseconds())/(++EEAV_FR_##x)<<std::endl;


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include <string>
#include <vector>

#include "item.h"

#include "Camera.h"
#include "ThrownItems.h"
#include "Collision.h"

class Entity
{
private:
	
protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	sf::Vector2f centerOfGame;
	
	//Camera
	Camera* camer;
	CameraSprite* cameraSprite{};
	sf::FloatRect* textureRect{};

	//Tiles
	std::vector<std::vector<TilesOnMap*>>*Tile;

	//Collision
	Collision collisionManagement{};
	std::vector<sf::FloatRect*>*CollisionTilesVec{};

	std::vector<ThrownItems*>* ItemsThrown;
	ThrownItems* ItemsOnTheGround{};

	float speed{};
	float time{};
	int lastDir{};

	bool actionPossible{ 1 };

	//Blockade
	bool blokade{};
	sf::Vector2i sizeOfBlockade{};
	sf::Vector2f blockadeOffset{};
	sf::FloatRect* collisionBox{};

	//direction
	directionOfMovement directionEnum = nomov;

public:
	Entity(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* tile, std::vector<sf::FloatRect*>* collisionTilesVec, EquipmentData* equipmentData);
	~Entity();

	void initTexture(std::string NameOfTxt, sf::Vector2f&& position);
	void setTextData(std::string NameOfTxt);
	virtual void update(const float& dt, const std::map<std::string, button*>& AllKeys) = 0;
	virtual void render()=0;
	virtual void movement(const float& dt, float&& speed, MovementData&movData, 
		const std::map<std::string, button*>& AllKeys)=0;

	virtual void getCenterOfScreen()=0;
	virtual void Animation(const float& dt, std::string&& direction)=0;

	void moveEntity(const float& dt, float speedX, float speedY);
	void moveEntitesWithoutThis(const float& dt, float speedX, float speedY);
	bool checkIfBackGroundMoveable();
	bool CheckingPossibleMove(const float& dt, float& speed);

	void initCamera(Camera* Camer);
};

#endif 