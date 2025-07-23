#ifndef WATERINGCANH
#define WATERINGCANH

#include "itemTool.h"


class itemWateringCan :
    public itemTool
{
private:

protected:

public:
    itemWateringCan(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool); //NEW

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif // 