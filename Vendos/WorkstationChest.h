#ifndef WORKSTATION_CHEST_H
#define WORKSTATION_CHEST_H

#include "Workstation.h"

class WorkstationChest :
    public Workstation
{
public:
    void update(const float& dt) {};
    item* getItem(sf::Vector2i xyOfItems);
    void render() {};
protected:

private:

};

#endif // !WORKSTATION_CHEST_H