#include "WorkstationChest.h"

item* WorkstationChest::getItem(sf::Vector2i xyOfItems)
{
    return this->workspace[xyOfItems.x][xyOfItems.y];
}
