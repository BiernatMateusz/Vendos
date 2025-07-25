#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "Equipment.h"
#include "Camera.h"
#include "ThrownItems.h"
#include "Collision.h"

class EntityPlayer : public TilesOnMap
{
private:
   
protected:
    Equipment* equipmentPtr{};
    //Camera
    Camera* camer{};

    ThrownItems* ItemsOnTheGround{};

    sf::Vector2f centerOfGame{};
    float speed{};
    float time{};
    int lastDir{};

    bool actionPossible{ 1 };

    //direction
    directionOfMovement directionEnum = nomov;

    //Collision
    Collision collisionManagement{};
    std::vector<sf::FloatRect*>* CollisionTilesVec{};
    std::vector<std::vector<TilesOnMap*>>* Tile{};

public:
    EntityPlayer() {};
    ~EntityPlayer();

   
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();
    void Animation(const float& dt, std::string&& direction);
    void playerMovement(const float& dt, float&& speed,MovementData& movData, const std::map<std::string, button*>& AllKeys);
    void getCenterOfScreen();

    void initPlayer();
    void initItemsOnTheGround(ThrownItems* ItemsOnTheGround);
    void initEquipment();

    bool checkIfBackGroundMoveable();
    bool CheckingPossibleMove(const float& dt, float& speed);

    void moveEntity(const float& dt, float speedX, float speedY);
    void moveEntitesWithoutThis(const float& dt, float speedX, float speedY);

};

#endif // !ENTITYPLAYER_H