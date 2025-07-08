#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H


#include "Entity.h"
#include "Equipment.h"

class EntityPlayer :
    public Entity
{
private:

protected:
    Equipment* equipmentPtr;
public:
    EntityPlayer(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround, std::vector<sf::FloatRect*>* CollisionTilesVec);
    ~EntityPlayer();

    void setStartingPositionOfPlayer();
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();
    void Animation(const float& dt, std::string&& direction);
    void movement(const float& dt, float&& speed,MovementData& movData, 
        const std::map<std::string, button*>& AllKeys);
    void getCenterOfScreen();

    void initPlayer();
    void initEquipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>*Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround);

};

#endif // !ENTITYPLAYER_H