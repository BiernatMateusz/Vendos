#ifndef ITEMSHOVELH
#define ITEMSHOVELH


#include "itemTool.h"
class itemShovel :
    public itemTool
{
private:
protected:
public:
    itemShovel(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);
   
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};


#endif // !ITEMSHOVELH