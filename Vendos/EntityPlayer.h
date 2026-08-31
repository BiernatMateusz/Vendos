#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "Equipment.h"
#include "Camera.h"
#include "ThrownItems.h"
#include "Collision.h"

class EntityPlayer : public SpriteAndBlockadeOnMap
{
private:
   
protected:
    Equipment* equipmentPtr{};
    //Camera
    Camera* camer{};

    ThrownItems* ItemsOnTheGround{};

    sf::Vector2f centerOfSprite{};
    float speed{};
    float time{};
    int lastDir{};

    bool actionPossible{ true };

    //direction
    directionOfMovement directionEnum = directionOfMovement::nomov;

    //Collision
    Collision collisionManagement{};
    std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec;
    std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile{};

public:
    EntityPlayer(std::vector<std::reference_wrapper<sf::FloatRect>>& CollisionTilesVec);
    ~EntityPlayer();

   
    void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    void render();
    void Animation(const float& dt, std::string&& direction);
    void playerMovement(const float& dt, float&& speed,MovementData& movData, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    void getCenterOfTxt();

    void initStartingPositionOfEntity(sf::Vector2f position);
    void initPlayer(sf::Vector2f position);
    void initItemsOnTheGround(ThrownItems* ItemsOnTheGround);
    void initEquipment();

    bool checkIfBackGroundMoveable();
    bool CheckingPossibleMove(const float& dt, float& speed);

    void moveEntity(const float& dt, float speedX, float speedY);
    void moveEntitesWithoutThis(const float& dt, float speedX, float speedY);

};

#endif // !ENTITYPLAYER_H