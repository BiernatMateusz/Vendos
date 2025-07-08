#ifndef itemToolh
#define itemToolh
#include "item.h"

class itemTool :
    public item
{
private:
    void ToolReplaceBlock(const float& dt, const std::map<std::string, button*>& AllKeys);
    void ToolDropItem(const float& dt, const std::map<std::string, button*>& AllKeys);

protected:
    
    TypeOfTool typeOfTool{};
    QualityOfTool qualityOfTool{};

    float dropMultiplication{};
    int durability{}; //need to be set based on quality
    int breakingBlockDamage{}; //need to be set based on quality
    
    
    

    void (itemTool::*ToolAction)(const float& dt, const std::map<std::string, button*>& AllKeys);
  
    //std::vector<int>TypeOfBlockToInterract{}; //constructor needs to make vector with those numbers for every tool 

    //0 - terrain like fields - to use by hoe
    //1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
    //2 - wooden things
    //3 - rocky things
    //4 - pickupable by hand like flowers, small wooden pieces, rocks
    //5 - hoed tiles - able to make croops here (no water)
    //6 - watered - able to make croops here and it will grow on here

    void updateKeybinds();
    void updateTypeAndQuality(TypeOfTool typeOfTool, QualityOfTool qualityOfTool);

    void setDurability();

public:

    itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, TypeOfTool typeOfTool, QualityOfTool qualityOfTool);
    itemTool(GraphicsData* graphicsData, TypeOfTool typeOfTool, QualityOfTool qualityOfTool);

    virtual void update(const float& dt, const std::map<std::string, button*>& AllKeys, std::vector<tileType>*TypeOfBlockToInterract);
    virtual void render(sf::RenderWindow* window)=0; //for animations

    const int& getBreakingDamage() const;
};

#endif