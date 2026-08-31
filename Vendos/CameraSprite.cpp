#include "CameraSprite.h"
#include <iostream>

void CameraSprite::setPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void CameraSprite::setOrigin(sf::Vector2f origin)
{
	this->sprite.setOrigin(origin);
}

void CameraSprite::setTexture(const sf::Texture& txt)
{
	this->sprite.setTexture(txt);
	this->active = true;
}

void CameraSprite::setTexture(const sf::Texture& txt, bool reset)
{
	this->sprite.setTexture(txt, reset);
	this->active = true;
}

sf::Sprite& CameraSprite::getSprite()
{
	return this->sprite;
}

const sf::Sprite& CameraSprite::getSprite() const
{
	return this->sprite;
}

float CameraSprite::getDistance() const
{
	return distance;
}

void CameraSprite::setDistance(float distance)
{
	this->distance = distance;
}
