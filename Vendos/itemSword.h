#ifndef ITEMSWORDH
#define ITEMSWORDH

#include "itemTool.h"

class itemSword :
    public itemTool
{
private:
protected:
public:
    itemSword(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);
    
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif // !ITEMSWORDH