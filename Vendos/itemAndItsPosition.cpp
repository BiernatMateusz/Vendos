#include "itemAndItsPosition.h"

itemAndItsPosition::itemAndItsPosition()
{
	this->itemPtr =nullptr;
	this->type = typeOfItemArea::PickAndPlace;
}

itemAndItsPosition::itemAndItsPosition(item* ItemPtr, typeOfItemArea Type)
{
	this->itemPtr = ItemPtr;
	this->type = Type;
}

itemAndItsPosition::itemAndItsPosition(const itemAndItsPosition& copyFrom)
{
	this->itemPtr = new item();
	*this->itemPtr = *copyFrom.itemPtr;
	this->type = copyFrom.type;
}

itemAndItsPosition::itemAndItsPosition(itemAndItsPosition&& copyFrom) noexcept
{
	this->itemPtr = std::move(copyFrom.itemPtr);
	copyFrom.itemPtr = nullptr;
	this->type = copyFrom.type;
}

itemAndItsPosition& itemAndItsPosition::operator=(const itemAndItsPosition& copyFrom)
{
	if (&copyFrom != this)
	{
		delete this->itemPtr;
		this->type = copyFrom.type;
		this->itemPtr = new item();
		*this->itemPtr = *copyFrom.itemPtr;
	}
	return *this;
}

itemAndItsPosition& itemAndItsPosition::operator=(itemAndItsPosition&& copyFrom) noexcept
{
	if (&copyFrom != this)
	{
		delete this->itemPtr;
		this->type = copyFrom.type;
		this->itemPtr = std::move(copyFrom.itemPtr);
		copyFrom.itemPtr = nullptr;
	}
	return *this;
}

itemAndItsPosition::~itemAndItsPosition()
{
	delete this->itemPtr;
}

void itemAndItsPosition::setItemPtr(item* ItemPtr)
{
	delete this->itemPtr;
	itemPtr = ItemPtr;
}

void itemAndItsPosition::setPosition(sf::Vector2f pos)
{
	if (this->itemPtr!=nullptr)
		this->itemPtr->cameraSpriteOfItem->getSprite()->setPosition(pos);
}

void itemAndItsPosition::setType(typeOfItemArea Type)
{
	this->type = Type;
}



item* itemAndItsPosition::getItemPtr()
{
	return this->itemPtr;
}

item*& itemAndItsPosition::getItemPtrAdress()
{
	return this->itemPtr;
}

const sf::Vector2f itemAndItsPosition::getPosition() const
{
	return this->itemPtr->cameraSpriteOfItem->sprite->getPosition();
}

const typeOfItemArea itemAndItsPosition::getType() const
{
	return this->type;
}

void itemAndItsPosition::drawItem()
{
	if (this->itemPtr != nullptr)
		this->itemPtr->render();
}
