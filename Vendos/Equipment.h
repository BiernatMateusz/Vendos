#ifndef EQUIPMENTh
#define EQUIPMENTh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"

#include "ItemConstructor.h"

#include "Camera.h"
#include "ThrownItems.h"

#include "TilesByItemsManagement.h"
#include "EquipmentAreas.h"

#include "Crafting.h"



class Equipment :
	public EquipmentStorageArea
{
private:
	//Variables
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<TilesOnMap*>>* Tile;

	TilesByItemsManagement* tilesByItemManagement;
	Crafting* crafting;

	//Second eq area holder
	EquipmentStorageArea* secondEq{};

	//ThrownItemsClass
	ThrownItems* itemsOnTheGround{};

	//Eq menagement
	EquipmentAreas *eqAreas{};

	bool ableToClose{};
	bool ableToOpen{};
	sf::Vector2i OpenedWorkstationAreaCords{};


	ItemConstructor factoryOfItems;

	//Additional functions
	void updateKeybinds(const std::map<std::string, button*>& AllKeys);
	void initEquipment();
	void calculatePositionOfFirstItemEqAndChest();

	void openingEquipment(const std::map<std::string, button*>& AllKeys);
	void openingChest(const std::map<std::string, button*>& AllKeys);
	void changingSelectedItem(const std::map<std::string, button*>& AllKeys);


protected:

public:
	//Constructors/Destructors
	Equipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround);

	//Functions
	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	void render();

};

#endif // !EQUIPMENTh
