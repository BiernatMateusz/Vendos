#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(sf::Vector2f position, std::string NameOfTxt, GraphicsData *graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData *equipmentData, ThrownItems* ItemsOnTheGround, std::vector<sf::FloatRect*>* CollisionTilesVec)
	: Entity(position, NameOfTxt, graphicsData, Tile, CollisionTilesVec, equipmentData)
{	
	initPlayer();
	this->ItemsOnTheGround = ItemsOnTheGround;
	setStartingPositionOfPlayer();
	initEquipment(graphicsData, Tile, equipmentData, ItemsOnTheGround);

}

EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::setStartingPositionOfPlayer()
{
	getCenterOfScreen();

	this->cameraSprite->getSprite()->setPosition(this->centerOfGame);
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

	this->cameraSprite->getSprite()->setTextureRect
	(
		sf::IntRect
		(
			this->textureRect->left + this->textureRect->width * WhichAnimation,
			this->textureRect->top + 78 * (int)this->graphicsData->lastDirectionOfPlayerEnum,
			this->textureRect->width, 
			this->textureRect->height
		)
	);
}

void EntityPlayer::movement(const float& dt, float&& speed, MovementData& movData, const std::map<std::string, button*>& AllKeys)
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
	centerOfGame.x = (float)this->graphicsData->window->getSize().x / 2 - this->textureRect->width / 2;
	centerOfGame.y = (float)this->graphicsData->window->getSize().y / 2 - this->textureRect->height / 2;
}

void EntityPlayer::initPlayer()
{
	if (this->graphicsData->player != nullptr)
		delete this->graphicsData->player;

	this->graphicsData->player = this->cameraSprite->getSprite();
	this->graphicsData->AllExcludedSpritesPointer->push_back(this->cameraSprite->getSprite());
}

void EntityPlayer::initEquipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround)
{
	this->equipmentPtr = new Equipment(graphicsData, Tile, equipmentData, ItemsOnTheGround);
}




