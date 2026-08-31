#ifndef TOOLSCLICKEDMANAGEMENT_H
#define TOOLSCLICKEDMANAGEMENT_H

#include "HoveringWithMouse.h"

class TilesManagement
{
public:
	TilesManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile);
	std::unique_ptr<HoveringWithMouse> hoveringWithMouse{};

	void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void render();

	//void initTile(sf::Vector2i position2i, ItemNames nameOfItem);
	void initTile(sf::Vector2i position2i, ItemNames itemName);
	bool checkIfEmpty(sf::Vector2i position2i);
	void removeTile(sf::Vector2i cordsXY);

protected:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile;

	void takingResistanceDown(sf::Vector2i coordsOfClickedTile, item* item);
	sf::Vector2i getCordsOfClickedTile(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
private:
	bool checkIfDestroyable(TilesOnMap* TileToCheck);
	
	ItemConstructor itemFactory;

};

#endif // !TOOLSCLICKEDMANAGEMENT_H