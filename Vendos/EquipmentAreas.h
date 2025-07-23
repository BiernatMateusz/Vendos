#ifndef EQUIPMENTAREAS_H
#define EQUIPMENTAREAS_H

#include "ItemConstructor.h"
#include "StructuresOfData.h"
#include "EquipmentStorageArea.h"
#include "ThrownItems.h"

class EquipmentAreas :
	public EquipmentAreasMenagement
{
private:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	sf::Sprite* BackGroundSquare{};
	sf::Sprite* BackGroundSquareUsed{};

	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* itemsFirstArea{};
	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* itemsSecondArea{};
	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* AllitemsArea{};

	sf::Vector2i sizeOfArea{};

	ItemConstructor factoryOfItems;
	ThrownItems* itemsOnTheGround{};

	int linesToDraw{};

	void updateKeybinds(const std::map<std::string, button*>& AllKeys);
	void whichLinesOfEqOpen();

	sf::Vector2f realPosOfItems_0_0{};
	void initRealPosOfItems_0_0();

	sf::Vector2i SquareHovered{};
	void getHoveredSquareStatus(const std::map<std::string, button*>& AllKeys);

	bool isInWorkArea{};
	void checkIfIsInWorkArea();

	bool itemTakenThisFrame{};
	item* itemGrabbed{};

	void updatePositionsOfItems(const std::map<std::string, button*>& AllKeys);

	void deleteItemIfAmmount_0();

	void takingItemToTheHand(const std::map<std::string, button*>& AllKeys);
	void putOffItemFromHand(const std::map<std::string, button*>& AllKeys);
	void takeOneItemToHand(const std::map<std::string, button*>& AllKeys);
	void takeHalfOfItemsToHand(const std::map<std::string, button*>& AllKeys);
	void placeOneMoreItem(const std::map<std::string, button*>& AllKeys);
	void searchForPlaceForWholeStack(const std::map<std::string, button*>& AllKeys);

	std::vector<int> decideWhichOrder(int);

	void stackItems_TrueIfRestEqual0(item** ItemFrom, item** ItemTo);
	void throwItem(item* item, bool isThrowdAllStack);

	std::vector<int> makeVectorOfUsedRows();
	std::vector<int> shrinkVectorToOnlyPlacableRows(std::vector<int>vec, int hoveredRow);
	std::vector<int> makeSortedFromHighestVecBiggerThatHoveredRow(std::vector<int>vec, int hoveredRow);

public:

	
	EquipmentAreas() {};

	EquipmentAreas(
		GraphicsData* graphicsData,
		EquipmentData* equipmentData);

	EquipmentAreas(
		GraphicsData* graphicsData, 
		EquipmentData* equipmentData, 
		std::vector < std::vector<std::pair <bool,itemAndItsPosition*>>>* itemsFirstArea, 
		std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* itemsSecondArea,
		ThrownItems* ItemsOnTheGround);
	
	~EquipmentAreas();

	void getAllItemsVecSize();
	void resizeAllItemsAreaVec();
	void connectBothAreas();

	bool isAbleToCloseEq();

	void update(const std::map<std::string, button*>& AllKeys);
	void render();

	void disconectBothArea();
protected:
	std::vector<itemAndItsPosition*>allItemsArea{}; 
	


};

#endif // !EQUIPMENTSECONDARYAREA_H
