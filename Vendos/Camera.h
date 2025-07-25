#ifndef CAMERA_H
#define CAMERA_H

//DOPISAC FUNKCJE KTORA PRZY KAZDYM NOWYM ELEMENCIE NA NOWO SORTUJE, SORTUJE PRZY KAZDYM RUCHU 
//ZMIANA RENDERINGU => mapa zawsze musi sie renderowac

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class Camera
{
public:
	//Constructors:::
	Camera(GraphicsData* graphicsData);

	//Destructor
	~Camera();

	void updateAllSpritesVecMapped(EquipmentData* equipmentData);
	void sortVectorMapped();
	
	void render(sf::RenderWindow* window);

	void moveObjects_PlayerExcluded(CameraSprite* Excluded, const float& dt, sf::Vector2f speed);

	void initPlayer(CameraSprite* cameraSprite);

private:
	//Variables
	GraphicsData* graphicsData;
	std::vector< CameraSprite*> AllSpritesMapped;

	sf::Sprite* Player;
	sf::Vector2f CenterOfMap;
	sf::Sprite* BackGround;
	//CameraSprite* Player;

	//Functions
	void initGraphicsBasics(GraphicsData* graphicsData);
	void cameraSpriteJoin();

	

};


#endif