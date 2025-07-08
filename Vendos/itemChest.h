#ifndef ITEMCHEST_H
#define ITEMCHEST_H

#include "item.h"
#include "EquipmentStorageArea.h"
#include "Workstation.h"

class itemChest :
    public item,
    public EquipmentStorageArea,
    public Workstation
{
private:
public:
    itemChest(GraphicsData* graphicsData, EquipmentData* equipmentData);
    ~itemChest();

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();
};

#endif // !ITEMCHEST_H