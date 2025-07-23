#include "TilesManagement.h"

//Constructors
TilesManagement::TilesManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Tile = Tile;

	this->hoveringWithMouse = new HoveringWithMouse(graphicsData, equipmentData, Tile);
	this->itemFactory.init(graphicsData, equipmentData);
}

//Public functions
void TilesManagement::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->hoveringWithMouse->update(dt, AllKeys);

	for (auto& row : *Tile)
		for (auto& elem : row)
			if (elem != nullptr)
			{
				elem->update(dt);
				if (checkIfDestroyable(elem)) 
				{ 
					delete elem; 
					elem = nullptr;

					this->equipmentData->needToUpdateTilesSpriteVec = 1;
				}
			}
}

void TilesManagement::render()
{
	this->hoveringWithMouse->render();
}

void TilesManagement::initTile(sf::Vector2i position2i, ItemNames itemName)
{
	this->equipmentData->needToUpdateTilesSpriteVec = 1;
	this->equipmentData->needToUpdateCameraAllSpr = 1;

	this->Tile->at(position2i.x).at(position2i.y) = itemFactory.createItem(itemName, position2i);
}

void TilesManagement::takingResistanceDown(sf::Vector2i coordsOfClickedTile, item* item)
{
	this->Tile->at(coordsOfClickedTile.x).at(coordsOfClickedTile.y)->decreaseTicksToDisappear(item->getBreakingDamage());
}

sf::Vector2i TilesManagement::getCordsOfClickedTile(const std::map<std::string, button*>& AllKeys)
{
	return { AllKeys.at("LeftMouse")->mouseTileGet().x,AllKeys.at("LeftMouse")->mouseTileGet().y };
}

///PRIVATE
bool TilesManagement::checkIfDestroyable(TilesOnMap* TileToCheck)
{
	return TileToCheck->getRemainingDurability()<=0;
}
