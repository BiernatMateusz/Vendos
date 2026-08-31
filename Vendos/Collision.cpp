#include "Collision.h"

void Collision::updateCollisionTiles(std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* tile, std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec)
{
    CollisionTilesVec.clear();

    for (auto& row:*tile)
        for (auto& elem : row)
            if (elem!=nullptr)
                if (elem->isBlockade() == true)
                    CollisionTilesVec.push_back(elem->getCollisionBox());
}

bool Collision::checkCollision(sf::Vector2f move, sf::FloatRect* spriteRectToMove, std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec)
{
    this->tmpObj = *spriteRectToMove;
    this->tmpObj.left += move.x;
    this->tmpObj.top += move.y;

    sf::FloatRect tmpFR;

    //I should check only close objects, not everyone

    auto result = std::find_if(std::begin(CollisionTilesVec), std::end(CollisionTilesVec), [&](auto Tile) {return tmpObj.intersects(Tile, tmpFR); });
    

    //RETURN
    if (result == std::end(CollisionTilesVec))
        return false; //no collision
    else 
        return true; //collision
}
