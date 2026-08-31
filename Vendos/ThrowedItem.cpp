#include "ThrowedItem.h"
#include "ItemStorage.h"

//Constructors
ThrowedItem::ThrowedItem(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile, ItemStorage* storage, std::unique_ptr<item> item)
: EquipmentAreasMenagement(graphicsData, equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->storage = storage;
	this->tile = Tile;
	this->Item = std::move(item);
	this->directionEnum = this->graphicsData->lastDirectionOfPlayerEnum;

	setItemParametersFromPlayer();
	setItemDestination();

}

ThrowedItem::ThrowedItem(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile, ItemStorage* storage, std::unique_ptr<item> item, sf::Vector2i TileCords)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->storage = storage;
	this->tile = Tile;
	this->Item = std::move(item);

	setItemParametersFromTile(TileCords);
	setItemDestinationFromTile();

}

//Constructor functions
void ThrowedItem::setItemDestination()
{
	this->distanceMaxValue = this->distanceMaxValueBase;

	if (this->directionEnum == directionOfMovement::right)
		this->distanceToGo = { this->distanceMaxValue,0 };
	else if (this->directionEnum == directionOfMovement::left)
		this->distanceToGo = { -this->distanceMaxValue,0 };
	else if (this->directionEnum == directionOfMovement::top)
	{
		this->distanceMaxValue -= this->offsetYofDroppedItemFromPlayer;			//Throwed item from player starts from offset which is visibly higher -> to make item go equaly far from every direction offset is needed
		this->distanceToGo = { 0,-this->distanceMaxValue };
	}
	else if (this->directionEnum == directionOfMovement::bot)
	{
		this->distanceMaxValue += this->offsetYofDroppedItemFromPlayer;
		this->distanceToGo = { 0,this->distanceMaxValue };
	}

	this->destinationOfItem = { this->graphicsData->player->getSprite().getPosition().x + this->distanceToGo.x, this->graphicsData->player->getSprite().getPosition().y + this->distanceToGo.y};
}

void ThrowedItem::setItemDestinationFromTile()
{
	std::uniform_int_distribution<int> horiz(-this->distanceMaxValue/2, this->distanceMaxValue/2);
	std::uniform_int_distribution<int> vert(0,1);

	tmpX = horiz(this->graphicsData->randomEngine.mt);
	tmpY = vert(this->graphicsData->randomEngine.mt);

	if (tmpY == 0) tmpY = -1;
	
	tmpY = sqrt((this->distanceMaxValue / 2) * (this->distanceMaxValue / 2) - tmpX * tmpX)*tmpY;

	this->distanceToTravel = {tmpX, tmpY};
	this->destinationOfItem = { this->initialPosition.x+tmpX, this->initialPosition.y + tmpY };

}

void ThrowedItem::setItemParametersFromPlayer()
{
	this->droppedFromPlayer = true;

	this->Item->cameraSpriteOfItem.getSprite().setScale(this->equipmentData->scaleOfThrownItems);
	this->Item->cameraSpriteOfItem.getSprite().setOrigin(this->equipmentData->originOfItemsDropped);

	this->Item->cameraSpriteOfItem.getSprite().setPosition({this->graphicsData->player->getSprite().getPosition().x,this->graphicsData->player->getSprite().getPosition().y - offsetYofDroppedItemFromPlayer});
	this->initialPosition = this->Item->cameraSpriteOfItem.getSprite().getPosition();
}

void ThrowedItem::setItemParametersFromTile(sf::Vector2i tileCord)
{
	this->Item->cameraSpriteOfItem.getSprite().setScale(this->equipmentData->scaleOfThrownItems);
	this->Item->cameraSpriteOfItem.getSprite().setOrigin(this->equipmentData->originOfItemsDropped);

	//to change below 
	this->Item->cameraSpriteOfItem.getSprite().setPosition(this->tile->at(tileCord.x).at(tileCord.y)->getCameraSpriteOnMap().getSprite().getPosition().x + this->equipmentData->originOfItemsDropped.x, this->tile->at(tileCord.x).at(tileCord.y)->getCameraSpriteOnMap().getSprite().getPosition().y + this->graphicsData->tileSize);
	this->initialPosition = this->Item->cameraSpriteOfItem.getSprite().getPosition();
}

//Update function
void ThrowedItem::update(const float& dt, bool canBePicked)
{
	accumulateTimeOfItemOnGround(dt);

	if (!destinationReached)
		itemMovementTowardsDestination(dt);
	else
	{
		if (destinationReachedONS == 0)
		{
			this->equipmentData->needToUpdateCameraAllSpr = 1;
			destinationReachedONS = 1;
		}
	}
	
	if (this->timePassedWhileOnGround > this->timeWhileUnableToCatch)
		if (canBePicked && checkDistanceItemToPlayer())
		{
			SpeedOfFlyingItem.x = -std::copysign(this->maxDistanceToCatchItem * dt * this->distanceToPlayer.x * 1.5 / distance, this->distanceToPlayer.x);
			SpeedOfFlyingItem.y = -std::copysign(this->maxDistanceToCatchItem * dt * this->distanceToPlayer.y * 1.5 / distance, this->distanceToPlayer.y);

			this->Item->cameraSpriteOfItem.getSprite().move(SpeedOfFlyingItem);
		}
}

//Function in update


void ThrowedItem::calculateMoveDistanceItemFromPlayer()
{
	calculatedDistanceToMove.x = this->timePassedWhileOnGround * cos30_times_v0;
	calculatedDistanceToMove.y = this->timePassedWhileOnGround * sin30_times_v0 - (this->gravity * pow(this->timePassedWhileOnGround, 2)) / 2;  //it creates parabolic throw

	//Next 3 lines transform values from positive {0, max} to {max, 0} --> in range 0 to 100 it tranform 80 into 20, 40 into 60 etc. 
	//but maximum is unknown so using max - 1stValue= newValue doesnt work
	calculatedDistanceToMove.y -= calculatedDistanceToMove.y / 2;
	calculatedDistanceToMove.y *= -1;
	calculatedDistanceToMove.y += calculatedDistanceToMove.y * 2;
}

void ThrowedItem::setDistanceToMoveBasedOnDirection()
{
	if (distanceFlied.y >= offsetYofDroppedItemFromPlayer)
		calculatedDistanceToMove.y = 0;

	if (this->directionEnum == directionOfMovement::left)
	{
		calculatedDistanceToMove.x = -calculatedDistanceToMove.x;
	}
	else if (this->directionEnum == directionOfMovement::top)
	{
		calculatedDistanceToMove.y = -calculatedDistanceToMove.x;
		calculatedDistanceToMove.x = 0;

	}
	else if (this->directionEnum == directionOfMovement::bot)
	{
		calculatedDistanceToMove.y = calculatedDistanceToMove.x;
		calculatedDistanceToMove.x = 0;
	}
}

void ThrowedItem::itemMovementThrewnFromPlayer(const float& dt)
{
	calculateMoveDistanceItemFromPlayer();

	distanceFlied += dt * calculatedDistanceToMove;

	setDistanceToMoveBasedOnDirection();

	if (distanceFlied.x >= distanceMaxValue)
	{
		destinationReached = true;
	}
}

void ThrowedItem::itemMovementThrewnFromNonPlayer(const float& dt)
{
	calculatedDistanceToMove.x = distanceToTravel.x * dt* 200;
	calculatedDistanceToMove.y = distanceToTravel.y * dt* 200;

	distanceFlied += dt * calculatedDistanceToMove;

	if (sqrt(pow(distanceFlied.x,2) + pow(distanceFlied.y,2)) > distanceMaxValue / 2)
		destinationReached = true;
}

void ThrowedItem::getAndChangeDestinationOfItem(sf::Vector2f MoveValues)
{
	this->destinationOfItem.x += MoveValues.x;
	this->destinationOfItem.y += MoveValues.y;
}

bool ThrowedItem::checkDistanceItemToPlayer()
{
	this->distanceToPlayer.x = this->Item->cameraSpriteOfItem.getSprite().getPosition().x - this->graphicsData->player->getSprite().getPosition().x;
	this->distanceToPlayer.y = this->Item->cameraSpriteOfItem.getSprite().getPosition().y - this->graphicsData->player->getSprite().getPosition().y;

	this->distance = sqrt(pow(distanceToPlayer.x, 2) + pow(distanceToPlayer.y, 2));

	if (this->distance <= this->minDistanceToCatchItem)
	{
		catchedItem = true;
		return false;
	}

	if (this->distance < this->maxDistanceToCatchItem)
	{
		return true;
	}
	return false;
}

//Functions
std::unique_ptr<item>& ThrowedItem::getItem()
{
	return Item;
}

void ThrowedItem::setItem(std::unique_ptr<item>& item)
{
	this->Item = std::move(item);
}

std::unique_ptr<item> ThrowedItem::take()
{
	return std::move(this->Item);
}

bool ThrowedItem::isCatched()
{
	return this->catchedItem;
}

void ThrowedItem::itemMovementTowardsDestination(const float& dt)
{
	if (this->droppedFromPlayer)
	{
		itemMovementThrewnFromPlayer(dt);
	}
	else
		itemMovementThrewnFromNonPlayer(dt);

	this->Item->cameraSpriteOfItem.getSprite().move(dt * this->calculatedDistanceToMove.x, dt * calculatedDistanceToMove.y);
}

void ThrowedItem::accumulateTimeOfItemOnGround(const float& dt)
{
	this->timePassedWhileOnGround += dt;
}
