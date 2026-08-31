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
	void updateCollisionTiles(std::vector<std::vector<std::unique_ptr<TilesOnMap>>>*tile, std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec);
	bool checkCollision(sf::Vector2f move, sf::FloatRect* spriteRectToMove, std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec);
};

#endif

//Do tiles do³o¿yæ zmienn¹ *Sprite, bêd¹ca wyznacznikiem granic kolizji
//Stworzyæ set zawieraj¹cy tylko *Sprite tilesów które maj¹ blokade
//Funkcja odbieraj¹ca wartoœæ sf::move oraz *Sprite który jest przesuwany a zwraca bool - informacje o tym czy nast¹pi kolizja czy nie
