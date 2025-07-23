#ifndef itemPickaxeH
#define itemPickaxeH

#include "itemTool.h"


class itemPickaxe :
    public itemTool
{
private:
protected:
public:
    itemPickaxe(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);
    
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif // !itemPickaxeH