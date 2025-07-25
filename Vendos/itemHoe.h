#ifndef itemHoeH
#define itemHoeH


#include "itemTool.h"


class itemHoe :
    public itemTool
{
private:
protected:
public:
    itemHoe(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations


};

#endif