#ifndef ITEMAXEH
#define ITEMAXEH

#include "itemTool.h"
class itemAxe :
    public itemTool
{
private:
protected:
public:
    itemAxe(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif 