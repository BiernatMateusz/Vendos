#include "TilesManagement.h"

//Constructors
TilesManagement::TilesManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Tile = Tile;

	this->hoveringWithMouse=std::make_unique<HoveringWithMouse>(graphicsData, equipmentData, Tile);
	this->itemFactory.init(graphicsData, equipmentData);
}

//Public functions
void TilesManagement::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	this->hoveringWithMouse->update(dt, AllKeys);

	for (auto& row : *Tile)
		for (auto& elem : row)
			if (elem != nullptr)
			{
				elem->update(dt);
				if (checkIfDestroyable(elem.get())) 
				{ 
					elem.reset();

					this->equipmentData->needToUpdateTilesSpriteVec = 1;
					this->equipmentData->needToUpdateCameraAllSpr = 1;
				}
			}
}

void TilesManagement::render()
{
	this->hoveringWithMouse->render();
}

void TilesManagement::initTile(sf::Vector2i position2i, ItemNames itemName)
{
	this->equipmentData->needToUpdateTilesSpriteVec = true;
	this->equipmentData->needToUpdateCameraAllSpr = true;
	
	this->Tile->at(position2i.x).at(position2i.y) = itemFactory.createItem(itemName, position2i);
	
}

void TilesManagement::takingResistanceDown(sf::Vector2i coordsOfClickedTile, item* item)
{
	this->Tile->at(coordsOfClickedTile.x).at(coordsOfClickedTile.y)->decreaseTicksToDisappear(item->getBreakingDamage());
}

sf::Vector2i TilesManagement::getCordsOfClickedTile(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	return { AllKeys.at(inputAction::LMouse)->mouseTileGet().x,AllKeys.at(inputAction::LMouse)->mouseTileGet().y };
}

///PRIVATE
bool TilesManagement::checkIfDestroyable(TilesOnMap* TileToCheck)
{
	return TileToCheck->getRemainingDurability()<=0;
}

bool TilesManagement::checkIfEmpty(sf::Vector2i position2i)
{
	return this->Tile->at(position2i.x).at(position2i.y) == nullptr ? true : false;
}

void TilesManagement::removeTile(sf::Vector2i cordsXY)
{
	this->Tile->at(cordsXY.x).at(cordsXY.y).reset();
}
