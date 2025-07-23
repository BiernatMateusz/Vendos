#ifndef itemToolh
#define itemToolh

#include "StructuresOfData.h"

class itemTool
{
private:
    std::vector<tileType>TypeOfBlockToInterract{};
    ItemNames nameOfTileToReplace{};
    bool isCreatingOnEmptyTilePossible{};
    void initBlocksToInteract(std::initializer_list<tileType>& tileTypeWithInteractions);
   
protected:
    QualityOfTool qualityOfTool{};

    float dropMultiplication{};
    int durability{}; //need to be set based on quality
    int breakingBlockDamage{}; //need to be set based on quality
    
    ItemNames nameOfTileToCreateFromToolAction;
    bool isCreatingOnEmptyTileAvailable;
    

    void (itemTool::*ToolAction)(const float& dt, const std::map<std::string, button*>& AllKeys);
  
    //std::vector<int>TypeOfBlockToInterract{}; //constructor needs to make vector with those numbers for every tool 

    void updateKeybinds();

    void setDurability(QualityOfTool toolQuality);

public:
    itemTool() {};
    itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);
    itemTool(GraphicsData* graphicsData, QualityOfTool qualityOfTool);

    void updateTool(const float& dt, const std::map<std::string, button*>& AllKeys, std::vector<tileType>*TypeOfBlockToInterract);
    void render(sf::RenderWindow* window) {}; //for animations

    void initToolDrop(std::initializer_list<tileType> tileTypeWithInteractions, QualityOfTool toolQuality);
    void initToolReplace(std::initializer_list<tileType> tileTypeWithInteractions, QualityOfTool toolQuality, bool interactionWithEmptyTile, ItemNames nameOfTileToReplace);

    const int& getBreakingDamage() const;

    std::vector<tileType>* getTypeOfBlocksToInterract();
    bool getIsCreatingOnEmptyTilePossible();
};

#endif