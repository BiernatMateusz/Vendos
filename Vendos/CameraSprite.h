#ifndef CAMERASPRITEH
#define CAMERASPRITEH

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <algorithm>

class CameraSprite
{
public:
	CameraSprite();
	CameraSprite(bool empty);
	CameraSprite(sf::Sprite* sprite, float distance);

	//Copy
	CameraSprite(const CameraSprite* model);
	//Move
	CameraSprite(CameraSprite&& model);

	~CameraSprite();

	//Assign operators
	CameraSprite& operator=(const CameraSprite& model);
	CameraSprite& operator=(CameraSprite&& model);
	//Functions
	void setSpriteTexture(const sf::Texture &txt);

	//GetSet
	sf::Sprite* getSprite();
	void setSprite(sf::Sprite* sprite);

	float getDistance();
	void setDistance(float distance);
	
	
	sf::Sprite* sprite; 
	float distance;

private:

};

#endif // !CAMERASPITEH