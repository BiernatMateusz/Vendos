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

	void initTile(sf::Vector2i position2i, std::string NameOfTxt);
	

protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<TilesOnMap*>>* Tile;

	void initStorageArea(sf::Vector2i position2i, StorageAreas storageArea);
	void takingResistanceDown(sf::Vector2i coordsOfClickedTile, item* item);
	sf::Vector2i getCordsOfClickedTile(const std::map<std::string, button*>& AllKeys);
private:
	bool checkIfDestroyable(TilesOnMap* TileToCheck);

};

#endif // !TOOLSCLICKEDMANAGEMENT_H