#include "Entity.h"

Entity::Entity(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* tile, std::vector<sf::FloatRect*>* collisionTilesVec, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Tile = tile;
	this->CollisionTilesVec = collisionTilesVec;

	//Blockade things
	this->blokade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockade;
	if (this->blokade) 
	{
		this->sizeOfBlockade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockadeSize;
		this->blockadeOffset = this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForBlockade;
		this->collisionBox = new sf::FloatRect;
		*this->collisionBox = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockadeRect;
	}

	initTexture(NameOfTxt,std::move(position));
	setTextData(NameOfTxt);
}

Entity::~Entity()
{
	delete this->textureRect;
	delete this->cameraSprite;
	delete this->collisionBox;
}

void Entity::initTexture(std::string NameOfTxt, sf::Vector2f &&position)
{
	this->textureRect = new sf::FloatRect;
	*this->textureRect = this->graphicsData->TextureDataMap->at(NameOfTxt)->TextRect;

	this->cameraSprite = new CameraSprite;
	this->cameraSprite->setSpriteTexture(*this->graphicsData->TextureDataMap->at(NameOfTxt)->texture);
	this->cameraSprite->getSprite()->setOrigin(this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.x, this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.y);
	this->cameraSprite->setDistance(this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForCamera);
	this->cameraSprite->getSprite()->setPosition(position.x, position.y);


	this->graphicsData->EntitiesSprite->push_back(this->cameraSprite->getSprite());

	this->graphicsData->EntitiesSpriteMapped->push_back(cameraSprite);

}

void Entity::setTextData(std::string NameOfTxt)
{
	this->cameraSprite->getSprite()->setTextureRect((sf::IntRect)this->graphicsData->TextureDataMap->at(NameOfTxt)->TextRect);
}

void Entity::moveEntity(const float& dt, float speedX, float speedY)
{
	this->cameraSprite->getSprite()->move(dt * speedX, dt * speedY);
	this->collisionBox->left = this->cameraSprite->getSprite()->getPosition().x + this->blockadeOffset.x;
	this->collisionBox->top = this->cameraSprite->getSprite()->getPosition().y + this->blockadeOffset.y;

}

void Entity::moveEntitesWithoutThis(const float& dt, float speedX, float speedY)
{
	this->camer->moveObjects_1stExcluded(this->cameraSprite->getSprite(), dt, {speedX,speedY});

	for (auto& row : *Tile)
		for (auto& elem : row)
		{
			if (elem != nullptr and elem->collisionBox != nullptr)
				elem->updateCollisionBoxPos();
		}
	
	if (ItemsOnTheGround != nullptr)
		ItemsOnTheGround->updatePositionOfEach(dt, speedX, speedY);

}

bool Entity::checkIfBackGroundMoveable()
{
	if (directionEnum == left)
	{
		if (this->graphicsData->backGroundMapped->getSprite()->getPosition().x >= 0)
			return false;
		else { return true; }
	}
	else if (directionEnum == right)
	{
		if (this->graphicsData->backGroundMapped->getSprite()->getPosition().x <= this->graphicsData->window->getSize().x - this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().width)
			return false;
		else { return true; }
	}
	else if (directionEnum == top)
	{
		if (this->graphicsData->backGroundMapped->getSprite()->getPosition().y >= this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height)
			return false;
		else { return true; }
	}
	else if (directionEnum == bot)
	{
		if (this->graphicsData->backGroundMapped->getSprite()->getPosition().y <= this->graphicsData->window->getSize().y)
			return false;
		else { return true; }
	} 
}

bool Entity::CheckingPossibleMove(const float& dt, float& speed)
{
	bool possible = 1;

	sf::FloatRect tmpRect(this->cameraSprite->getSprite()->getPosition().x + this->blockadeOffset.x, this->cameraSprite->getSprite()->getPosition().y + this->blockadeOffset.y, this->sizeOfBlockade.x, this->sizeOfBlockade.y);

	if (directionEnum == left)
		possible = not(collisionManagement.checkCollision({ -dt * speed,0 }, &tmpRect, this->CollisionTilesVec));

	if (directionEnum == right) 
		possible = not(collisionManagement.checkCollision({ dt * speed,0 }, &tmpRect, this->CollisionTilesVec));

	if (directionEnum == top)
		possible = not(collisionManagement.checkCollision({ 0,-dt * speed }, &tmpRect, this->CollisionTilesVec));

	if (directionEnum == bot)
		possible = not(collisionManagement.checkCollision({ 0,dt * speed }, &tmpRect, this->CollisionTilesVec));

	return possible;
}

void Entity::initCamera(Camera* Camer)
{
	this->camer = Camer;
}
