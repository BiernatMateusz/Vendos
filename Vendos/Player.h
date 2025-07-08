#ifndef PLAYER
#define PLAYER

#include "Entity.h"

class Player :
    public Entity
{
private:

protected:

public:
    //Variables
    sf::Vector2f playerPosition;

    Player();
    Player(std::string txtName, int posX, int posY, float scale);

    //Functions
    void EntityMovement(float& dt, sf::Vector2f position, bool diagonalMovement);
};

#endif // !PLAYER