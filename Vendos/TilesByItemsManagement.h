#ifndef TILESBYITEMSMANAGEMENT_H
#define TILESBYITEMSMANAGEMENT_H

#include "TilesManagement.h"
#include "ItemConstructor.h"
#include "TileConstructor.h"
#include "itemAndItsPosition.h"

class TilesByItemsManagement : public TilesManagement
{
public:
	TilesByItemsManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq);
	
	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	
	void setNumberOfSlotOnBottomBar(const int &number);
	int getNumberOfSlotOnBottomBar();
	void resetTimeoutWhileActionTrue();

private:
	std::vector<std::vector<item*>>* Eq{};
	std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq{};
	ItemConstructor factoryOfItems;
	TileConstructor factoryOfTiles;
	int numberOfSlotOnBottomBar{};
	item* itemUsed{};

	sf::Vector2i coordsOfTileClicked{};
	TilesOnMap* tileClicked{};

	float timePassedWhileAction{};

	void (TilesByItemsManagement::* ToolAction)(const std::map<std::string, button*>& AllKeys);
	
	bool timeoutWhileActionIsHappening{};

	bool checkIfTileTypeMatchingToolType();

	item* getItemUsed();
	TilesOnMap* getTileUsed(const std::map<std::string, button*>& AllKeys);

	void chooseFunction();

	void ToolReplaceBlock(const std::map<std::string, button*>& AllKeys);
	void ToolDropItem(const std::map<std::string, button*>& AllKeys);
	void ToolPickItemFromTile(const std::map<std::string, button*>& AllKeys);
	void ToolPlaceItem(const std::map<std::string, button*>& AllKeys);
	void HandAction(const std::map<std::string, button*>& AllKeys);

	bool checkIfActionTriggered(const std::map<std::string, button*>& AllKeys);
	bool checkIfActionIsPossible();
	
	void actionTimeManagement(const float& dt);
	void setTimeoutWhileActionTrue();
	
};

#endif // !TILESBYITEMSMANAGEMENT_H