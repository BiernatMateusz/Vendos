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
	CameraSprite()=default;
	
	//Functions
	void setTexture(const sf::Texture &txt);
	void setTexture(const sf::Texture& txt, bool reset);
	void setPosition(sf::Vector2f pos);
	void setOrigin(sf::Vector2f origin);

	//GetSet
	sf::Sprite& getSprite();
	const sf::Sprite& getSprite() const;

	float getDistance() const;
	void setDistance(float distance);


	bool isActive() const {return active;}
	void activate() { active = true; }
	void deactivate() { active = false; }

private:
	sf::Sprite sprite;
	float distance{0.f};
	bool active{ false };
};

#endif // !CAMERASPITEH