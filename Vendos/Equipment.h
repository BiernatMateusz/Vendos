#ifndef EQUIPMENTh
#define EQUIPMENTh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"

#include "Camera.h"
#include "ThrownItems.h"

#include "TilesByItemsManagement.h"
#include "EquipmentAreas.h"

#include "CraftingItems.h"
#include "PlayerStorage.h"
#include "inputAction.h"
#include "EquipmentInputControler.h"

class Equipment
{
private:
	std::unique_ptr<PlayerStorage> playerStorage;
	std::unique_ptr<CraftingItems> playerCrafting;

	///////////////////////////////////////////Pointers not owned ///////////////////////////////////////////////////
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<std::unique_ptr<TilesOnMap>>>& Tile;
	EquipmentStorageArea* secondEq{};
	ThrownItems* itemsOnTheGround{};


	///////////////////////////////////////////Pointers owned ///////////////////////////////////////////////////
	std::unique_ptr<EquipmentAreas>eqAreas;
	std::unique_ptr<TilesByItemsManagement>tilesByItemManagement;
	std::unique_ptr<EquipmentInputControler>inputController;

	//Private functions
	void initPlayerStorage();
	void initPlayerCrafting();
	void calculatePositionOfFirstItem();
	
	void updateBottomBar();
	void updateActiveStorages(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	void setState(EquipmentUIState newState, EquipmentStorageArea* itemStorage = nullptr);
	void handleToggleInventory();
	void tryOpenChest();



protected:

public:
	//Constructors//Destructors
	Equipment(GraphicsData* graphicsData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>& Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround);

	//Public Functions
	void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void render();

};

#endif // !EQUIPMENTh
