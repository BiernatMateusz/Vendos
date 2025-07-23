#include "Player.h"

Player::Player()
{

}

Player::Player(std::string txtName, int posX, int posY, float scale)
{
	initTxt(txtName,posX,posY,scale);
}

void Player::EntityMovement(float& dt, sf::Vector2f position, bool diagonalMovement)
{
	this->PlayerSpeed = 150 * dt;

	if (diagonalMovement)
	{
		this->PlayerSpeed *= 0.8;
	}

	this->playerPosition = this->Sprite_Entity.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //UP DIR=1
	{
		this->direction = 1;

		if (position.y >= -1 or this->playerPosition.y >= 400)
		{
			this->Sprite_Entity.move(0.0, -(this->PlayerSpeed));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //DOWN DIR=2
	{
		this->direction = 2;
		if (position.y <= -1308 or this->playerPosition.y <= 400)
		{
			this->Sprite_Entity.move(0.0, (this->PlayerSpeed));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //LEFT DIR=3
	{
		
		this->direction = 3;
		if (position.x >= -1 or this->playerPosition.x >= 550)
		{
			this->Sprite_Entity.move(-(this->PlayerSpeed), 0.0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //RIGHT DIR=4
	{
		this->direction = 4;
		if (position.x <= -1616 or this->playerPosition.x<=550)
		{
			this->Sprite_Entity.move((this->PlayerSpeed), 0.0);
		}
	}

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		this->direction = 0;
	}
}
