#ifndef HOVERINGWITHMOUSE_H
#define HOVERINGWITHMOUSE_H

#include "TilesOnMap.h"
#include "ItemConstructor.h"
#include "inputAction.h"

class HoveringWithMouse
{
public:
	HoveringWithMouse(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile);
	void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	void render();
	
	sf::Vector2i getActualTileCords(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile;

	sf::Text numberOfItems{};
	std::string displayedTxt{};
	TilesOnMap* tileHovered{};

	sf::Vector2i coordsOfActualTile{};

	void updateDisplayedTxt();
	void updateAndRenderTileText(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
};

#endif // !HOVERINGWITHMOUSE_H