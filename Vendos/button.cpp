#include "button.h"


button::button()
{
}

button::button(sf::Keyboard::Key key)
{
	this->key = key;
}

button::~button()
{

}

void button::update(sf::RenderWindow* window, sf::Sprite* Background)
{
	//Press state
	//Keyboard
	if (sf::Keyboard::isKeyPressed(this->key))
		this->isPressed = 1;
	else this->isPressed = 0;

	this->isNotPressed = not(this->isPressed);

	setStates();

}

const bool& button::isButtonPressed() const
{
	return this->isPressed;
}

const bool& button::isButtonNotPressed() const
{
	return this->isNotPressed;
}

const bool& button::oneSignalButtonPressed() const
{
	return this->oneSignalPressed;
}

const bool& button::oneSignalButtonUnPressed() const
{
	return this->oneSignalUnPressed;
}

const sf::Vector2i& button::mousePosGet() const
{
	return { 0,0 };
}

const sf::Vector2i& button::mousePosPrevGet() const
{
	return { 0,0 };
}

const sf::Vector2i& button::mouseTileGet() const
{
	return { 0,0 };
}

const sf::Vector2i& button::mouseTileActualGet() const
{
	return { 0,0 };
}

bool button::checkIfInBoxArea(sf::Vector2f point, sf::Vector2f Area)
{
	return false;
}

void button::setStates()
{
	//Ramp Press and unPress
	if (this->isPressed and this->rampPress == 0)
	{
		this->oneSignalPressed = 1;
		this->rampPress = 1;
	}
	else { this->oneSignalPressed = 0; }

	if (this->isNotPressed and this->rampPress == 1)
	{
		this->oneSignalUnPressed = 1;
		this->rampPress = 0;
	}
	else { this->oneSignalUnPressed = 0; }



}
