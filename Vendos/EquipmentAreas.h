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

	std::vector<ItemStorage*> visibleStorages;
	ItemStorage* hoveredStorage;

	sf::Vector2i sizeOfArea{9,10};

	ItemConstructor factoryOfItems;
	ThrownItems* itemsOnTheGround{};

	void updateKeybinds(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	sf::Vector2f realPosOfItems_0_0{};
	void initRealPosOfItems_0_0();

	void setHoveredStorage();

	sf::Vector2i SquareHovered{};
	void getHoveredSquareStatus(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	ItemStorage* getOtherStorage(ItemStorage* current);

	bool isInWorkArea{};
	void checkIfIsInWorkArea();

	bool itemTakenThisFrame{};
	slot itemGrabbed{};


	void updatePositionsOfItems(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	void deleteItemIfAmmount_0();

	void takingItemToTheHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void putOffItemFromHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void takeOneItemToHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void takeHalfOfItemsToHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void placeOneMoreItem(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void searchForPlaceForWholeStack();

	void addSlots(slot&from, slot& to);
	void throwItem(slot& item, bool isThrowdAllStack);

public:

	
	EquipmentAreas()=default;

	EquipmentAreas(
		GraphicsData* graphicsData, 
		EquipmentData* equipmentData, 
		ItemStorage* itemsFirstArea, 
		ItemStorage* itemsSecondArea,
		ThrownItems* ItemsOnTheGround);
	
	~EquipmentAreas();

	void setStorages(ItemStorage* firstStorage, ItemStorage* secondStorage);

	bool isAbleToCloseEq();
	void forceReleaseGrabbedItem();

	bool tryDeleteItems(ItemNames itemName, int count);

	void update(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void updateWhileClosed();
	void render();
	void renderItemHeld();

};

#endif // !EQUIPMENTSECONDARYAREA_H
