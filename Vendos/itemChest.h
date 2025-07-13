#ifndef ITEMCHEST_H
#define ITEMCHEST_H

#include "item.h"
#include "EquipmentStorageArea.h"
#include "Workstation.h"
#include "TilesOnMap.h"

class itemChest :
    public item,
    public EquipmentStorageArea,
    public TilesOnMap
{
private:
public:
    itemChest(GraphicsData* graphicsData, EquipmentData* equipmentData);
    itemChest(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i position2i, std::string NameOfTxt);
    ~itemChest();

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();
};

#endif // !ITEMCHEST_H