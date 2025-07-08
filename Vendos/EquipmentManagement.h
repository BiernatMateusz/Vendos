#ifndef EQUIPMENTMANAGEMENT_H
#define EQUIPMENTMANAGEMENT_H

#include "StructuresOfData.h"
#include "ThrownItems.h"
#include "ItemConstructor.h"
#include "CraftingManagement.h"
#include "EquipmentAreas.h"

class EquipmentManagement
{
public:
	//Constructor
	EquipmentManagement(
		GraphicsData* graphicsData, 
		EquipmentData* equipmentData, 
		std::vector<std::vector<item*>>*Eq, 
		std::vector<std::vector<item*>>* Crafting, 
		ThrownItems* ItemsOnTheGround);

	//Core functions
	void update(const std::map<std::string, button*>& AllKeys);
	void render();

	//Functions
	bool isAbleToCloseEq();

	bool isMouseInEqLayout();
	void stackingItems();
	void stackingItemsInCrafting();
	void searchForNextFreeSpot(std::vector<std::vector<item*>>* ArrayToSearch, item* ItemToPut);

	void substractItemInCrafting(item* itemToSubstr, int numberOfItems);
	void decreaseItemsInCrafting();

	void takingItemToTheHand(const std::map<std::string, button*>& AllKeys);
	void moveItemWhereCursorGoes(const std::map<std::string, button*>& AllKeys);
	void putOffItemFromHand(const std::map<std::string, button*>& AllKeys);
	void sendItemToOtherInventorySpace(const std::map<std::string, button*>& AllKeys);
	void takeOneItemToHand(const std::map<std::string, button*>& AllKeys);
	void takeOneMoreItemToHand(const std::map<std::string, button*>& AllKeys);
	void throwItem(item* item);

private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	std::vector<std::vector<item*>>*Eq{};
	std::vector<std::vector<item*>>* crafting{};

	std::vector<std::vector<item*>>* FirstArea{};
	std::vector<std::vector<item*>>* SecondArea{};
	
	sf::Vector2i positionOfFirstItem2ndArea{};

	bool checkIsFirstAreaClicked(const std::map<std::string, button*>& AllKeys);
	bool checkIsSecondAreaClicked(const std::map<std::string, button*>& AllKeys);

	EquipmentAreas* firstEqArea{};
	EquipmentAreas* secondEqArea{};
	std::vector<itemAndItsPosition*>*allItemsArea{};

	ThrownItems* ItemsOnTheGround{};

	item* itemGrabbed = nullptr;
	item* holder = nullptr;
	item* craftingSpot = nullptr;

	//Factory Items
	ItemConstructor factoryOfItems;

	CraftingManagement* craftingManagement{};

	bool overMaxInStack{};
	bool itemTakenThisFrame{};
	const int HeightOfEqPlusChest = 7; //eq->3 , chest->3 , spacing between->1
	sf::Vector2i OpenedChestCoords{};
	int OffsetHeightEqAndSpacing;
	bool craftingSpotHovered{};
	
	sf::Vector2i getWhichTileIsClicked(const std::map<std::string, button*>& AllKeys);
	void checkIfCraftingSpotIsBeingHovered(const std::map<std::string, button*>& AllKeys);

	

};

#endif // !EQUIPMENTMANAGEMENT_H
