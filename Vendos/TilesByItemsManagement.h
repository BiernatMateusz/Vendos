#ifndef TILESBYITEMSMANAGEMENT_H
#define TILESBYITEMSMANAGEMENT_H

#include "TilesManagement.h"
#include "ItemConstructor.h"

class ItemStorage;

class TilesByItemsManagement : public TilesManagement
{
public:
	TilesByItemsManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile, ItemStorage* storage);
	
	void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	
	void setNumberOfSlotOnBottomBar(const int &number);
	int getNumberOfSlotOnBottomBar();
	void resetTimeoutWhileActionTrue();

private:
	ItemStorage* storage;
	ItemConstructor factoryOfItems;
	int numberOfSlotOnBottomBar{};
	item* itemUsed{};

	sf::Vector2i coordsOfTileClicked{};
	TilesOnMap* tileClicked{};

	float timePassedWhileAction{};

	void (TilesByItemsManagement::* ToolAction)(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	
	bool timeoutWhileActionIsHappening{};

	bool checkIfTileTypeMatchingToolType();

	item* getItemUsed();
	TilesOnMap* getTileUsed(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	void chooseFunction();

	void ToolReplaceBlock(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void ToolDropItem(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void ToolPickItemFromTile(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void ToolPlaceItem(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void HandAction(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	bool checkIfActionTriggered(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	bool checkIfActionIsPossible();
	
	void actionTimeManagement(const float& dt);
	void setTimeoutWhileActionTrue();
	
};

#endif // !TILESBYITEMSMANAGEMENT_H