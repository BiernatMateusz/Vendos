#include "ThrowedItem.h"

//Constructors
ThrowedItem::ThrowedItem(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq, item* item, std::vector<ThrowedItem*>* ItemsThrownVec)
: EquipmentAreasMenagement(graphicsData, equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->eq = eq;
	this->tile = Tile;
	this->Item = item;
	this->ItemsThrownVec = ItemsThrownVec;
	this->directionEnum = this->graphicsData->lastDirectionOfPlayerEnum;

	setItemParametersFromPlayer();
	setItemDestination();

	this->graphicsData->ItemsThrownSpriteMapped->push_back(new CameraSprite);
	this->graphicsData->ItemsThrownSpriteMapped->back() = Item->cameraSprite;
}

ThrowedItem::ThrowedItem(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq, item* item, std::vector<ThrowedItem*>* ItemsThrownVec, sf::Vector2i TileCords)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->eq = eq;
	this->tile = Tile;
	this->Item = item;
	this->ItemsThrownVec = ItemsThrownVec;

	setItemParametersFromTile(TileCords);
	setItemDestinationFromTile();

	this->graphicsData->ItemsThrownSpriteMapped->push_back(new CameraSprite);
	this->graphicsData->ItemsThrownSpriteMapped->back() = Item->cameraSprite;
}

//Constructor functions
void ThrowedItem::setItemDestination()
{
	this->distanceMaxValue = this->distanceMaxValueBase;

	if (this->directionEnum == right)
		this->distanceToGo = { this->distanceMaxValue,0 };
	else if (this->directionEnum == left)
		this->distanceToGo = { -this->distanceMaxValue,0 };
	else if (this->directionEnum == top)
	{
		this->distanceMaxValue -= this->offsetYofDroppedItemFromPlayer;			//Throwed item from player starts from offset which is visibly higher -> to make item go equaly far from every direction offset is needed
		this->distanceToGo = { 0,-this->distanceMaxValue };
	}
	else if (this->directionEnum == bot)
	{
		this->distanceMaxValue += this->offsetYofDroppedItemFromPlayer;
		this->distanceToGo = { 0,this->distanceMaxValue };
	}

	this->destinationOfItem = { this->graphicsData->player->getPosition().x + this->distanceToGo.x, this->graphicsData->player->getPosition().y + this->distanceToGo.y };
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

	this->Item->cameraSprite->getSprite()->setScale(this->equipmentData->scaleOfThrownItems);
	this->Item->cameraSprite->getSprite()->setOrigin(this->equipmentData->originOfItemsDropped);

	this->Item->cameraSprite->getSprite()->setPosition({this->graphicsData->player->getPosition().x,this->graphicsData->player->getPosition().y - offsetYofDroppedItemFromPlayer});
	this->initialPosition = this->Item->cameraSprite->getSprite()->getPosition();
}

void ThrowedItem::setItemParametersFromTile(sf::Vector2i tileCord)
{
	this->Item->cameraSprite->getSprite()->setScale(this->equipmentData->scaleOfThrownItems);
	this->Item->cameraSprite->getSprite()->setOrigin(this->equipmentData->originOfItemsDropped);

	//to change below 
	this->Item->cameraSprite->getSprite()->setPosition(this->tile->at(tileCord.x).at(tileCord.y)->cameraSprite->getSprite()->getPosition().x+this->equipmentData->originOfItemsDropped.x, this->tile->at(tileCord.x).at(tileCord.y)->cameraSprite->getSprite()->getPosition().y + this->graphicsData->tileSize );
	this->initialPosition = this->Item->cameraSprite->getSprite()->getPosition();
}

//Update function
void ThrowedItem::update(const float& dt)
{
	accumulateTimeOfItemOnGround(dt);

	if (not(destinationReached))
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
	{
		if (this->equipmentData->IDofItemsWhichCantBeTaken.find(this->Item->itemID) == this->equipmentData->IDofItemsWhichCantBeTaken.end())
			if (checkDistanceItemToPlayer())
			{
				SpeedOfFlyingItem.x = -std::copysign(this->maxDistanceToCatchItem * dt * this->distanceToPlayer.x * 1.5 / distance, this->distanceToPlayer.x);
				SpeedOfFlyingItem.y = -std::copysign(this->maxDistanceToCatchItem * dt * this->distanceToPlayer.y * 1.5 / distance, this->distanceToPlayer.y);

				this->Item->itemSprite.move(SpeedOfFlyingItem);
			}
	}

	makeUnpickableItemsList({0,2,1});
}

//Function in update
void ThrowedItem::compareAddableAndUnaddableList()
{
	for (auto elem : TmpUnAddableList)
		if (std::end(this->TmpAddableList) == std::find(std::begin(this->TmpAddableList), std::end(this->TmpAddableList), elem ))
			this->equipmentData->IDofItemsWhichCantBeTaken.insert(elem);

	this->TmpUnAddableList.clear();
	this->TmpAddableList.clear();
}

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

	if (this->directionEnum == left)
	{
		calculatedDistanceToMove.x = -calculatedDistanceToMove.x;
	}
	else if (this->directionEnum == top)
	{
		calculatedDistanceToMove.y = -calculatedDistanceToMove.x;
		calculatedDistanceToMove.x = 0;

	}
	else if (this->directionEnum == bot)
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
		destinationReached = true;
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
	this->distanceToPlayer.x = this->Item->itemSprite.getPosition().x - this->graphicsData->player->getPosition().x;
	this->distanceToPlayer.y = this->Item->itemSprite.getPosition().y - this->graphicsData->player->getPosition().y;

	this->distance = sqrt(pow(distanceToPlayer.x, 2) + pow(distanceToPlayer.y, 2));

	if (this->distance <= this->minDistanceToCatchItem)
	{
		catchedItem = 1;
		return false;
	}

	if (this->distance < this->maxDistanceToCatchItem)
	{
		return true;
	}
	return false;
}

void ThrowedItem::makeUnpickableItemsList(std::vector<int>orderOfSearch)
{
	//BABOL do poprawienia liczby sk¹d siê bierze 3?   (wielkosc eq to 9na3 ale eq jest size 9x10 wiec trzeba to sprytnie wymysliæ 
	for (int i=0;i<3;i++)
		for (int j=0;j<eq->size();j++)
			if (eq->at(j).at(i).second->getItemPtr() == nullptr)
			{
				this->equipmentData->IDofItemsWhichCantBeTaken.clear();
				return;
			}
			else if (eq->at(j).at(i).second->getItemPtr()->checkIfAddable() == false)
			{
				this->TmpUnAddableList.push_back(eq->at(j).at(i).second->getItemPtr()->itemID);
			}
			else
			{
				this->TmpAddableList.push_back(eq->at(j).at(i).second->getItemPtr()->itemID);
			}

	compareAddableAndUnaddableList();
}

//Functions
item* ThrowedItem::getItem()
{
	return this->Item;
}

void ThrowedItem::setCatchedState(bool catched)
{
	this->catchedItem = catched;
}

bool ThrowedItem::checkIfCatched()
{
	if (this->catchedItem)
		if (this->equipmentData->IDofItemsWhichCantBeTaken.find(this->Item->itemID) != this->equipmentData->IDofItemsWhichCantBeTaken.end()) //zawsze puste hmm
		{
			this->catchedItem = 0;
		}
		

	return this->catchedItem;
}

void ThrowedItem::itemMovementTowardsDestination(const float& dt)
{
	if (this->droppedFromPlayer)
		itemMovementThrewnFromPlayer(dt);
	else
		itemMovementThrewnFromNonPlayer(dt);

	this->Item->itemSprite.move(dt * this->calculatedDistanceToMove.x, dt * calculatedDistanceToMove.y);
}

void ThrowedItem::accumulateTimeOfItemOnGround(const float& dt)
{
	this->timePassedWhileOnGround += dt;
}
