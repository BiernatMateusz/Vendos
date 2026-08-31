#include "slot.h"

slot::operator bool() const
{
	return itemPtr != nullptr;
}

void slot::setUsable(bool isUsable)
{
	this->usable = isUsable;
}

bool slot::isUsable() const
{
	return this->usable;
}

void slot::setSlotType(typeOfSlot type)
{
	this->slotType = type;
}

typeOfSlot slot::getType() const
{
	return this->slotType;
}

void slot::setItemPtr(std::unique_ptr<item> newItem)
{
	this->itemPtr = std::move(newItem);
}

item* slot::get() const
{
	return this->itemPtr.get();
}

void slot::swapItems(slot& otherItem)
{
	std::swap(this->itemPtr, otherItem.itemPtr);
}

void slot::swapItems(std::unique_ptr<item> otherItem)
{
	std::swap(this->itemPtr, otherItem);
}

void slot::clear()
{
	this->itemPtr.reset();
}

std::unique_ptr<item> slot::take()
{
	return std::move(itemPtr);
}