#ifndef GAMEMAP
#define GAMEMAP

#include "Entity.h"

class Game_map :
    public Entity
{
private:

public:
    //Variables
    sf::Vector2f mapPosition;

    Game_map();
    Game_map(std::string txtName, int posX, int posY, float scale);

    void EntityMovement(float& dt, sf::Vector2f position, bool diagonalMovement);
};

#endif // !GAMEMAP