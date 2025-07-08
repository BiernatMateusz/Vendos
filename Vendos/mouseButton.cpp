#include "mouseButton.h"


mouseButton::mouseButton(sf::Mouse::Button MouseButton)
{
	this->MouseButton = MouseButton;
}

void mouseButton::update(sf::RenderWindow* window, sf::Sprite* backGround)
{
	if (sf::Mouse::isButtonPressed(this->MouseButton))
		this->isPressed = 1;
	else this->isPressed = 0;

	this->isNotPressed = not(this->isPressed);

	this->mousePos = sf::Mouse::getPosition(*window);


	setStates();
	setMouseStates(window);
	
	//Setting coordinates of tile clicked - [x][y] 
	if (this->oneSignalPressed)
		setMouseTile(window, backGround);

	setMouseTileActual(window, backGround);
}

void mouseButton::setMouseTile(sf::RenderWindow* window, sf::Sprite* BackGround)
{
	setTileCoveredByMouse(window, BackGround, this->mouseTile);
}

void mouseButton::setMouseTileActual(sf::RenderWindow* window, sf::Sprite* BackGround)
{
	setTileCoveredByMouse(window, BackGround, this->mouseTileActual);
}

void mouseButton::setTileCoveredByMouse(sf::RenderWindow* window, sf::Sprite* BackGround, sf::Vector2i& MouseTileVariable)
{
	if (checkIfInScreen(window))
		if (BackGround != nullptr)
		{
			int x = ((int)BackGround->getGlobalBounds().height - (int)BackGround->getPosition().y);
			MouseTileVariable = { (this->mousePos.x - (int)BackGround->getPosition().x) / 44,((mousePos.y + (x)) / 44) };
		}
} 

bool mouseButton::checkIfInScreen(sf::RenderWindow* window)
{
	return checkIfInBoxArea({0,0}, {(float)window->getSize().x,(float)window->getSize().y});
}

const sf::Vector2i& mouseButton::mousePosGet() const
{
	return this->mousePos;
}

const sf::Vector2i& mouseButton::mousePosPrevGet() const
{
	return this->mousePosPrev;
}

const sf::Vector2i& mouseButton::mouseTileGet() const
{
	return this->mouseTile;
}

const sf::Vector2i& mouseButton::mouseTileActualGet() const
{
	return this->mouseTileActual;
}

bool mouseButton::checkIfInBoxArea(sf::Vector2f point, sf::Vector2f Area)
{
	return (
		this->mousePosGet().x > point.x && 
		this->mousePosGet().x < point.x + Area.x && 
		this->mousePosGet().y > point.y && 
		this->mousePosGet().y < point.y+Area.y);
}

void mouseButton::setMouseStates(sf::RenderWindow *window)
{
	if (oneSignalButtonPressed())
		this->mousePosPrev = sf::Mouse::getPosition(*window);
}
