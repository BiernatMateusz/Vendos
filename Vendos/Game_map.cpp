#include "Game_map.h"

Game_map::Game_map()
{
}

Game_map::Game_map(std::string txtName, int posX, int posY, float scale)
{
	initTxt(txtName,posX,posY,scale);
}

void Game_map::EntityMovement(float& dt, sf::Vector2f position, bool diagonalMovement)
{
	this->PlayerSpeed = 150 * dt;


	if (diagonalMovement)
	{
		this->PlayerSpeed *= 0.8;
	}

	this->mapPosition = this->Sprite_Entity.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and this->mapPosition.y < -1 and position.y < 400)
	{
		this->Sprite_Entity.move(0.0, (this->PlayerSpeed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and this->mapPosition.y >-1308 and position.y > 400)
	{
		this->Sprite_Entity.move(0.0, -(this->PlayerSpeed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and this->mapPosition.x < -1 and position.x<550)
	{
		this->Sprite_Entity.move((this->PlayerSpeed), 0.0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and this->mapPosition.x >-1616 and position.x>550) 
	{
		this->Sprite_Entity.move(-(this->PlayerSpeed), 0.0);
	}
	}

