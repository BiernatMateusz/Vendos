#ifndef HOVERINGWITHMOUSE_H
#define HOVERINGWITHMOUSE_H

#include "TilesOnMap.h"
#include "ItemConstructor.h"

class HoveringWithMouse
{
public:
	HoveringWithMouse(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile);
	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	void render();
	
	sf::Vector2i getActualTileCords(const std::map<std::string, button*>& AllKeys);

private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<TilesOnMap*>>* Tile;

	sf::Text numberOfItems{};
	std::string displayedTxt{};
	TilesOnMap* tileHovered{};

	sf::Vector2i coordsOfActualTile{};

	void updateDisplayedTxt();
	void updateAndRenderTileText(const std::map<std::string, button*>& AllKeys);
};

#endif // !HOVERINGWITHMOUSE_H