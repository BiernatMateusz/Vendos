#ifndef COLLISIONH
#define COLLISIONH

#include "StructuresOfData.h"
#include "TilesOnMap.h"

class Collision
{
private:
	sf::FloatRect tmpObj{};
	int licznik{};
public:
	void updateCollisionTiles(std::vector<std::vector<TilesOnMap*>>*tile, std::vector<sf::FloatRect*>* collisionTiles);
	bool checkCollision(sf::Vector2f move, sf::FloatRect* spriteRectToMove, std::vector<sf::FloatRect*>* CollisionTiles);
};

#endif

//Do tiles do�o�y� zmienn� *Sprite, b�d�ca wyznacznikiem granic kolizji
//Stworzy� set zawieraj�cy tylko *Sprite tiles�w kt�re maj� blokade
//Funkcja odbieraj�ca warto�� sf::move oraz *Sprite kt�ry jest przesuwany a zwraca bool - informacje o tym czy nast�pi kolizja czy nie
