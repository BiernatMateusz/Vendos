#include "CameraSprite.h"

CameraSprite::CameraSprite()
{
	this->sprite = new sf::Sprite;
	this->distance=0;
}

CameraSprite::CameraSprite(bool empty)
{
	this->sprite = nullptr;
	this->distance = 0;
}

CameraSprite::CameraSprite(sf::Sprite* sprite, float distance)
{
	this->sprite = sprite;
	this->distance = distance;
}

CameraSprite::CameraSprite(const CameraSprite* model)
{
	this->sprite = new sf::Sprite;
	*this->sprite = *(model->sprite);
	this->distance = model->distance;
	
}

CameraSprite::CameraSprite(CameraSprite&& model)
{
	this->sprite = model.sprite;
	this->distance = model.distance;
	model.sprite = nullptr;
}

CameraSprite::~CameraSprite()
{
	delete this->sprite;
}

CameraSprite& CameraSprite::operator=(const CameraSprite& model)
{
	if (this != &model)
	{
		this->sprite = new sf::Sprite;
		*this->sprite = *(model.sprite);
		this->distance = model.distance;
		return *this;
	}
}

CameraSprite& CameraSprite::operator=(CameraSprite&& model)
{
	if (this != &model)
	{
		delete this->sprite;
		this->sprite = model.sprite;
		this->distance = model.distance;
		
		model.sprite = nullptr;
		return *this;
	}
}

void CameraSprite::setSpriteTexture(const sf::Texture& txt)
{
	this->sprite->setTexture(txt);
}

sf::Sprite* CameraSprite::getSprite()
{
	return this->sprite;
}

void CameraSprite::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

float CameraSprite::getDistance()
{
	return distance;
}

void CameraSprite::setDistance(float distance)
{
	this->distance = distance;
}
