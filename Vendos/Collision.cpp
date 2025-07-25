#include "Collision.h"

void Collision::updateCollisionTiles(std::vector<std::vector<TilesOnMap*>>* tile, std::vector<sf::FloatRect*>* collisionTiles)
{
    collisionTiles->clear();

    for (auto& row:*tile)
        for (auto& elem : row)
            if (elem!=nullptr)
                if (elem->blokade == true)
                    collisionTiles->push_back(elem->collisionBox);
}

bool Collision::checkCollision(sf::Vector2f move, sf::FloatRect* spriteRectToMove, std::vector<sf::FloatRect*>* CollisionTiles)
{
    this->tmpObj = *spriteRectToMove;
    this->tmpObj.left += move.x;
    this->tmpObj.top += move.y;

    sf::FloatRect tmpFR;

    //I should check only close objects, not everyone

    auto result = std::find_if(std::begin(*CollisionTiles), std::end(*CollisionTiles), [&](auto Tile) {return tmpObj.intersects(*Tile, tmpFR); });
    

    //RETURN
    if (result == std::end(*CollisionTiles))
        return false; //no collision
    else 
        return true; //collision
}
