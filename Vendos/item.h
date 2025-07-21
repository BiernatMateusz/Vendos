#ifndef item_h
#define item_h

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <String>
#include "CameraSprite.h"
#include "StructuresOfData.h"
#include "TilesOnMap.h"

class item
	: public TilesOnMap
{
private:
	sf::Font font{};
	sf::Text numberOfItems{};
	int maxStack{ 999 };
	bool OverMax{};
	

	void updateAndRenderNumberOfItems();
	


protected:
	std::vector<std::string> StrType{ "Axe", "Pickaxe", "Hoe", "WateringCan", "Shovel", "Sword" };
	std::vector<std::string> StrQuality{ "Wooden", "Stone", "Iron", "Golden", "Diamond" };
	
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	TextureNames nameOfTxtOfItem;
	
	//new things
	std::vector<tileType>TypeOfBlockToInterract{}; //constructor needs to make vector with those numbers for every tool 
	bool isCreatingOnEmptyTilePossible{};
	
	
	float timeOfItemUsage{1}; //create map of times then every item needs it 

	std::string nameOfTxt;

	int numberOfItemsInStack{ 1 };

	void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys);
	
	void initGraphics(const std::string& name);

	std::string makeNameTexture(TypeOfTool typeOfTool, QualityOfTool qualityOfTool);

	TypeOfAction typeOfAction{ TypeOfAction::Pick };
public:

	//Constructos
	item() {};
	item(GraphicsData* graphicsData);
	item(GraphicsData* graphicsData, TypeOfAction actionType);
	item(GraphicsData* graphicsData, bool empty);
	item(GraphicsData* graphicsData, EquipmentData* equipmentData, const std::string& name, int ammount, TypeOfAction actionType);
	item(GraphicsData* graphicsData, EquipmentData* equipmentData, TypeOfTool typeOfTool, QualityOfTool qualityOfTool);
	item(bool tileExist, bool equipmentStorageExist);


	
	//Assign operators
	virtual item& operator=(const item& model);

	//Functions
	virtual void update(const float &dt, const std::map<std::string, button*>& AllKeys); //actions
	virtual void render(); //for animations

	void initPositon(sf::Vector2i xyOfvec, sf::Vector2f FirstItemPos, const int& itemSize, int OffsetYPositioning);
	void initItemBasicData(EquipmentData* equipmentData, TextureNames nameOfTxt,int ammount, TypeOfAction actionType);
	void initItemGraphicsData();
	void initItemID(int ID);

	void changeNumberOfItems(int newNumberOfItems);
	int getNumberOfItems();
	bool isNumberOfItemsEven();
	int getHalfOfItems();
	int getNumberMax();

	bool addItemsReturn1IfOverMax(item* itemPtr);
	bool addItemsReturn1IfOverMax_DontAddWhenOverMax(item* itemPtr);
	bool addOneItemReturn1IfNmbOfItemsFromTakenIs0(item* itemPtr);
	void substrFromThisItem(int value);
	void addToThisItem(int value);
	void setNumberOfItems(int value);

	bool checkIfAddable();

	std::vector<tileType>*getTypeOfBlocksToInterract();
	bool getIsCreatingOnEmptyTilePossible();
	
	TypeOfAction getTypeOfAction();
	float getTimeOfActionOfItemUsage();
	std::string getReplaceTxtName();
	
	virtual const int& getBreakingDamage() const;

	//Variables
	int itemID{};
	float distance{};
	sf::Sprite itemSprite{};
	sf::Vector2i TileClicked{};
	std::string nameOfTxtWhileReplacing{};

	CameraSprite* cameraSpriteOfItem{};
};

#endif 