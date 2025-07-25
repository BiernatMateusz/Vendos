#include "EntityPlayer.h"

EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->equipmentPtr->updateStorageArea(dt, AllKeys);
}

void EntityPlayer::render()
{
	this->equipmentPtr->render();
}

void EntityPlayer::Animation(const float& dt, std::string&& direction)
{
	if (this->equipmentData->isEqOpened) directionEnum = nomov;

	if (directionEnum==nomov)
	{
		time = 0;
	}
	else time += dt;

	int timeUsed = time * 100;

	float WhichAnimation = timeUsed % 30;
	WhichAnimation = (timeUsed - WhichAnimation) / 30;

	if (WhichAnimation > 3)
	{
		time = 0;
		WhichAnimation = 0;
	}

	int WhichAnimationN = WhichAnimation + 1;
	if (WhichAnimationN == 4)
		WhichAnimationN = 0;

	this->cameraSpriteOfTile->getSprite()->setTextureRect
	(
		sf::IntRect
		(
			this->txtRect.left + this->txtRect.width * WhichAnimation,
			this->txtRect.top + 78 * (int)this->graphicsData->lastDirectionOfPlayerEnum,
			this->txtRect.width, 
			this->txtRect.height
		)
	);
}

void EntityPlayer::playerMovement(const float& dt, float&& speed, MovementData& movData, const std::map<std::string, button*>& AllKeys)
{
	if (AllKeys.at("W")->isButtonPressed())
	{
		this->directionEnum = top;
		this->lastDir = 2;
		
		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getPosition().y < this->graphicsData->CenterOfMap->y)
			{
				moveEntitesWithoutThis(dt, 0, speed);
			}
			else moveEntity(dt, 0, -speed);

			movData.moved = 1;


		}
		this->graphicsData->lastDirectionOfPlayerEnum = top;
	}
	if (AllKeys.at("S")->isButtonPressed())
	{
		this->directionEnum = bot;
		this->lastDir = 0;

		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getPosition().y > this->graphicsData->CenterOfMap->y)
			{
				moveEntitesWithoutThis(dt, 0, -speed);
			}
			else moveEntity(dt, 0, speed);

			movData.moved = 1;
		}
		this->graphicsData->lastDirectionOfPlayerEnum = bot;
	}
	if (AllKeys.at("A")->isButtonPressed())
	{
		this->directionEnum = left;
		this->lastDir = 3;

		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getPosition().x < this->graphicsData->CenterOfMap->x)
			{
				moveEntitesWithoutThis(dt, speed, 0);
			}
			else moveEntity(dt, -speed, 0);

			movData.moved = 1;

		}
		this->graphicsData->lastDirectionOfPlayerEnum = left;
	}
	if (AllKeys.at("D")->isButtonPressed())
	{
		this->directionEnum = right;
		this->lastDir = 1;

		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getPosition().x > this->graphicsData->CenterOfMap->x)
			{
				moveEntitesWithoutThis(dt, -speed, 0);
			}
			else moveEntity(dt, speed, 0);

			movData.moved = 1;

		}
		this->graphicsData->lastDirectionOfPlayerEnum = right;
	}

	if (!AllKeys.at("W")->isButtonPressed() and !AllKeys.at("D")->isButtonPressed() and !AllKeys.at("S")->isButtonPressed() and !AllKeys.at("A")->isButtonPressed()) this->directionEnum = nomov;
	
}

void EntityPlayer::getCenterOfScreen()
{
	this->centerOfGame.x = (float)this->graphicsData->window->getSize().x / 2 - this->txtRect.width / 2;
	this->centerOfGame.y = (float)this->graphicsData->window->getSize().y / 2 - this->txtRect.height / 2;
	
}

void EntityPlayer::initPlayer()
{
	if (this->graphicsData->player != nullptr)
		delete this->graphicsData->player;

	this->graphicsData->player = this->cameraSpriteOfTile->getSprite();
	this->graphicsData->AllExcludedSpritesPointer->push_back(this->cameraSpriteOfTile->getSprite());
	
	initEquipment();
}

void EntityPlayer::initItemsOnTheGround(ThrownItems* ItemsOnTheGround)
{
	this->ItemsOnTheGround = ItemsOnTheGround;
}

void EntityPlayer::initEquipment()
{
	this->equipmentPtr = new Equipment(this->graphicsData, this->Tile, this->equipmentData, this->ItemsOnTheGround);
}

bool EntityPlayer::checkIfBackGroundMoveable()
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



bool EntityPlayer::CheckingPossibleMove(const float& dt, float& speed)
{
	bool possible = 1;

	sf::FloatRect tmpRect(this->cameraSpriteOfTile->getSprite()->getPosition().x + this->blockadeOffset.x, this->cameraSpriteOfTile->getSprite()->getPosition().y + this->blockadeOffset.y, this->sizeOfBlockade.x, this->sizeOfBlockade.y);

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

void EntityPlayer::moveEntity(const float& dt, float speedX, float speedY)
{
	this->cameraSpriteOfTile->getSprite()->move(dt * speedX, dt * speedY);
	this->collisionBox->left = this->cameraSpriteOfTile->getSprite()->getPosition().x + this->blockadeOffset.x;
	this->collisionBox->top = this->cameraSpriteOfTile->getSprite()->getPosition().y + this->blockadeOffset.y;

}

void EntityPlayer::moveEntitesWithoutThis(const float& dt, float speedX, float speedY)
{
	this->camer->moveObjects_PlayerExcluded(this->cameraSpriteOfTile, dt, { speedX,speedY });

	for (auto& row : *Tile)
		for (auto& elem : row)
		{
			if (elem != nullptr and elem->collisionBox != nullptr)
				elem->updateCollisionBoxPos();
		}

	if (ItemsOnTheGround != nullptr)
		ItemsOnTheGround->updatePositionOfEach(dt, speedX, speedY);

}