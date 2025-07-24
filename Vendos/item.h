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
	:	public TilesOnMap,
		public itemTool
{
private:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	TextureNames nameOfTxtOfItem{};

	ItemNames itemName{};
	int itemID{};

	TypeOfAction typeOfAction{ TypeOfAction::Pick };

	sf::Text numberOfItems{};
	int maxStack{ 999 };
	bool OverMax{};
	int numberOfItemsInStack{ 1 };

	float timeOfItemUsage{1}; //its cooldown between now and next usage

	void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys);
	void updateAndRenderNumberOfItems();

public:
	//Constructors
	item() {};
	item(GraphicsData* graphicsData);

	//Copy constructor
	
	//Assign operators
	item& operator=(const item& model);
	
	//Destructor
	~item();

	//Functions
	void update(const float &dt, const std::map<std::string, button*>& AllKeys); //actions
	void render(); //for animations

	void initItemBasicData(EquipmentData* equipmentData, TextureNames nameOfTxt,int ammount, TypeOfAction actionType);
	void initItemGraphicsData();
	void initItemIDandName(int ID, ItemNames itemName);

	int getNumberOfItems();
	bool isNumberOfItemsEven();
	int getHalfOfItems();
	int getNumberMax();

	bool addItemsReturn1IfOverMax(item* itemPtr);
	bool addOneItemReturn1IfNmbOfItemsFromTakenIs0(item* itemPtr);
	void substrFromThisItem(int value);
	void setNumberOfItems(int value);

	bool checkIfAddable();
	bool hasTimePassed(float& timePassed);
	
	
	
	bool isNullItemsInStack();
	bool isMaxItemsInStack();

	//Variables
	
	float distance{};

	CameraSprite* cameraSpriteOfItem{};

	//GETTERS
	const int& getBreakingDamage() const;
	const ItemNames& getItemName() const;
	const TypeOfAction& getTypeOfAction() const;
	const int& getItemID() const;


	//SETTERS

};

#endif 