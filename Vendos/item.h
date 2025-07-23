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
#include "itemTool.h"

class item
	: public TilesOnMap,
	public itemTool
{
private:
	sf::Text numberOfItems{};
	int maxStack{ 999 };
	bool OverMax{};
	

	void updateAndRenderNumberOfItems();

protected:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	TextureNames nameOfTxtOfItem{};
	ItemNames itemName{};
	
	//new things
	 //constructor needs to make vector with those numbers for every tool 
	
	
	
	float timeOfItemUsage{1}; //create map of times then every item needs it 

	int numberOfItemsInStack{ 1 };

	void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys);

	TypeOfAction typeOfAction{ TypeOfAction::Pick };
public:

	//Constructos
	item() {};
	item(GraphicsData* graphicsData);
	/*item(GraphicsData* graphicsData, TypeOfAction actionType);
	item(GraphicsData* graphicsData, bool empty);
	item(GraphicsData* graphicsData, EquipmentData* equipmentData, const std::string& name, int ammount, TypeOfAction actionType);
	item(GraphicsData* graphicsData, EquipmentData* equipmentData, QualityOfTool qualityOfTool);
	item(bool tileExist, bool equipmentStorageExist);*/


	
	//Assign operators
	item& operator=(const item& model);

	//Functions
	void update(const float &dt, const std::map<std::string, button*>& AllKeys); //actions
	void render(); //for animations

	void initItemBasicData(EquipmentData* equipmentData, TextureNames nameOfTxt,int ammount, TypeOfAction actionType);
	void initItemGraphicsData();
	void initItemIDandName(int ID, ItemNames itemName);

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
	
	TypeOfAction getTypeOfAction();
	float getTimeOfActionOfItemUsage();
	std::string getReplaceTxtName();
	
	virtual const int& getBreakingDamage() const;

	//Variables
	int itemID{};
	float distance{};
	sf::Vector2i TileClicked{};
	std::string nameOfTxtWhileReplacing{};

	CameraSprite* cameraSpriteOfItem{};

	ItemNames getItemName();
};

#endif 