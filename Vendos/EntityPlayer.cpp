#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec) : CollisionTilesVec(CollisionTilesVec)
{
	;
}

EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	this->equipmentPtr->update(dt, AllKeys);
}

void EntityPlayer::render()
{
	this->equipmentPtr->render();
}

void EntityPlayer::Animation(const float& dt, std::string&& direction)
{
	if (this->equipmentData->isEqOpened) directionEnum = directionOfMovement::nomov;

	if (directionEnum==directionOfMovement::nomov)
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

	this->cameraSpriteOnMap.getSprite().setTextureRect
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

void EntityPlayer::playerMovement(const float& dt, float&& speed, MovementData& movData, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	if (AllKeys.at(inputAction::MoveUp)->isButtonPressed())
	{
		this->directionEnum = directionOfMovement::top;
		this->lastDir = 2;
		
		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getSprite().getPosition().y - this->centerOfSprite.y < this->graphicsData->CenterOfMap.y)
			{
				moveEntitesWithoutThis(dt, 0, speed);
			}
			else moveEntity(dt, 0, -speed);

			movData.moved = 1;


		}
		this->graphicsData->lastDirectionOfPlayerEnum = directionOfMovement::top;
	}
	if (AllKeys.at(inputAction::MoveDown)->isButtonPressed())
	{
		this->directionEnum = directionOfMovement::bot;
		this->lastDir = 0;

		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getSprite().getPosition().y - this->centerOfSprite.y > this->graphicsData->CenterOfMap.y)
			{
				moveEntitesWithoutThis(dt, 0, -speed);
			}
			else moveEntity(dt, 0, speed);

			movData.moved = 1;
		}
		this->graphicsData->lastDirectionOfPlayerEnum = directionOfMovement::bot;
	}
	if (AllKeys.at(inputAction::MoveLeft)->isButtonPressed())
	{
		this->directionEnum = directionOfMovement::left;
		this->lastDir = 3;

		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getSprite().getPosition().x + this->centerOfSprite.x < this->graphicsData->CenterOfMap.x)
			{
				moveEntitesWithoutThis(dt, speed, 0);
			}
			else moveEntity(dt, -speed, 0);

			movData.moved = 1;

		}
		this->graphicsData->lastDirectionOfPlayerEnum = directionOfMovement::left;
	}
	if (AllKeys.at(inputAction::MoveRight)->isButtonPressed())
	{
		this->directionEnum = directionOfMovement::right;
		this->lastDir = 1;

		if (CheckingPossibleMove(dt, speed))
		{
			if (checkIfBackGroundMoveable() and this->graphicsData->player->getSprite().getPosition().x + this->centerOfSprite.x > this->graphicsData->CenterOfMap.x)
			{
				moveEntitesWithoutThis(dt, -speed, 0);
			}
			else moveEntity(dt, speed, 0);

			movData.moved = 1;

		}
		this->graphicsData->lastDirectionOfPlayerEnum = directionOfMovement::right;
	}

	if (!AllKeys.at(inputAction::MoveUp)->isButtonPressed() and !AllKeys.at(inputAction::MoveRight)->isButtonPressed() and !AllKeys.at(inputAction::MoveDown)->isButtonPressed() and !AllKeys.at(inputAction::MoveLeft)->isButtonPressed()) this->directionEnum = directionOfMovement::nomov;
	
}

void EntityPlayer::getCenterOfTxt()
{
	this->centerOfSprite.x = this->txtRect.width / 2;
	this->centerOfSprite.y = this->txtRect.height / 2;
	
}

void EntityPlayer::initStartingPositionOfEntity(sf::Vector2f position)
{
	getCenterOfTxt();
	this->cameraSpriteOnMap.getSprite().setPosition({ position.x - this->centerOfSprite.x,position.y + this->centerOfSprite.y });
}

void EntityPlayer::initPlayer(sf::Vector2f position)
{
	this->graphicsData->player = &this->cameraSpriteOnMap;
	
	initStartingPositionOfEntity(position);
	initEquipment();
}

void EntityPlayer::initItemsOnTheGround(ThrownItems* ItemsOnTheGround)
{
	this->ItemsOnTheGround = ItemsOnTheGround;
}

void EntityPlayer::initEquipment()
{
	this->equipmentPtr = new Equipment(this->graphicsData, *this->Tile, this->equipmentData, this->ItemsOnTheGround);
}

bool EntityPlayer::checkIfBackGroundMoveable()
{
	if (directionEnum == directionOfMovement::left)
	{
		if (this->graphicsData->backGroundMapped.getSprite().getPosition().x >= 0)
			return false;
		else { return true; }
	}
	else if (directionEnum == directionOfMovement::right)
	{
		if (this->graphicsData->backGroundMapped.getSprite().getPosition().x <= this->graphicsData->window->getSize().x - this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().width)
			return false;
		else { return true; }
	}
	else if (directionEnum == directionOfMovement::top)
	{
		if (this->graphicsData->backGroundMapped.getSprite().getPosition().y >= this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height)
			return false;
		else { return true; }
	}
	else if (directionEnum == directionOfMovement::bot)
	{
		if (this->graphicsData->backGroundMapped.getSprite().getPosition().y <= this->graphicsData->window->getSize().y)
			return false;
		else { return true; }
	}
}



bool EntityPlayer::CheckingPossibleMove(const float& dt, float& speed)
{
	bool possible = 1;

	sf::FloatRect tmpRect(this->cameraSpriteOnMap.getSprite().getPosition().x + this->blockadeOffset.x, this->cameraSpriteOnMap.getSprite().getPosition().y + this->blockadeOffset.y, this->sizeOfBlockade.x, this->sizeOfBlockade.y);

	if (directionEnum == directionOfMovement::left)
		possible = not(collisionManagement.checkCollision({ -dt * speed,0 }, &tmpRect, this->CollisionTilesVec));

	if (directionEnum == directionOfMovement::right)
		possible = not(collisionManagement.checkCollision({ dt * speed,0 }, &tmpRect, this->CollisionTilesVec));

	if (directionEnum == directionOfMovement::top)
		possible = not(collisionManagement.checkCollision({ 0,-dt * speed }, &tmpRect, this->CollisionTilesVec));

	if (directionEnum == directionOfMovement::bot)
		possible = not(collisionManagement.checkCollision({ 0,dt * speed }, &tmpRect, this->CollisionTilesVec));

	return possible;
}

void EntityPlayer::moveEntity(const float& dt, float speedX, float speedY)
{
	this->cameraSpriteOnMap.getSprite().move(dt * speedX, dt * speedY);
	this->collisionBox.left = this->cameraSpriteOnMap.getSprite().getPosition().x + this->blockadeOffset.x;
	this->collisionBox.top = this->cameraSpriteOnMap.getSprite().getPosition().y + this->blockadeOffset.y;

}

void EntityPlayer::moveEntitesWithoutThis(const float& dt, float speedX, float speedY)
{
	this->camer->moveObjects_PlayerExcluded(this->cameraSpriteOnMap, dt, { speedX,speedY });

	for (auto& row : *Tile)
		for (auto& elem : row)
		{
			if (elem != nullptr)// and elem->getCollisionBox() != nullptr)
				elem->updateCollisionBoxPos();
		}

	if (ItemsOnTheGround)
		ItemsOnTheGround->updatePositionOfEach(dt, speedX, speedY);

}