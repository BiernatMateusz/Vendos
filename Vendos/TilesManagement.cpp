#include "TilesManagement.h"

//Constructors
TilesManagement::TilesManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Tile = Tile;

	this->hoveringWithMouse = new HoveringWithMouse(graphicsData, equipmentData, Tile);
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

void TilesManagement::initTile(sf::Vector2i position2i, std::string NameOfTxt)
{
	this->Tile->at(position2i.x).at(position2i.y) = new TilesOnMap(position2i, NameOfTxt, graphicsData);

	if (this->graphicsData->TextureDataMap->at(NameOfTxt)->typeOfTile == tileType::chestField) //8 -> workstation
		initStorageArea({ position2i.x,position2i.y }, this->graphicsData->TextureDataMap->at(NameOfTxt)->storageArea);

	this->equipmentData->needToUpdateTilesSpriteVec = 1;
	this->equipmentData->needToUpdateCameraAllSpr = 1;
}

///PROTECTED
void TilesManagement::initStorageArea(sf::Vector2i position2i, StorageAreas storageArea)
{
	switch (storageArea)
	{
	case StorageAreas::Empty:
		break;
	case StorageAreas::Chest:
		this->Tile->at(position2i.x).at(position2i.y)->storageArea = new itemChest(this->graphicsData, this->equipmentData);
		break;
	case StorageAreas::Crafting:
		break;
	case StorageAreas::Furnace:
		this->Tile->at(position2i.x).at(position2i.y)->storageArea = new itemFurnace(this->graphicsData, this->equipmentData);
		break;
	}
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
