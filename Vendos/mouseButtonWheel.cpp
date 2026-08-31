#include "mouseButtonWheel.h"

mouseButtonWheel::mouseButtonWheel()
{
	;
}

void mouseButtonWheel::update(sf::RenderWindow* window, CameraSprite backGround)
{
	if (this->found1NextTickNeedToDelete == true)
	{
		this->scrollDownTick = false;
		this->scrollUpTick = false;
		this->found1NextTickNeedToDelete = false;
	}

	if (this->scrollDownTick == true or this->scrollUpTick == true)
		this->found1NextTickNeedToDelete = true;
}

const bool& mouseButtonWheel::isWheelScrolledUp() const
{
	return this->scrollUpTick;
}

const bool& mouseButtonWheel::isWheelScrolledDown() const
{
	return this->scrollDownTick;
}

void mouseButtonWheel::setWheelScrollUp(bool state)
{
	this->scrollUpTick = state;
}

void mouseButtonWheel::setWheelScrollDown(bool state)
{
	this->scrollDownTick = state;
}