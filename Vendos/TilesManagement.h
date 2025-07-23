#ifndef TOOLSCLICKEDMANAGEMENT_H
#define TOOLSCLICKEDMANAGEMENT_H

#include "HoveringWithMouse.h"

class TilesManagement
{
public:
	TilesManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile);
	HoveringWithMouse* hoveringWithMouse{};

	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	void render();

	//void initTile(sf::Vector2i position2i, ItemNames nameOfItem);
	void initTile(sf::Vector2i position2i, ItemNames itemName);

protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<TilesOnMap*>>* Tile;

	void takingResistanceDown(sf::Vector2i coordsOfClickedTile, item* item);
	sf::Vector2i getCordsOfClickedTile(const std::map<std::string, button*>& AllKeys);
private:
	bool checkIfDestroyable(TilesOnMap* TileToCheck);
	ItemConstructor itemFactory;

};

#endif // !TOOLSCLICKEDMANAGEMENT_H