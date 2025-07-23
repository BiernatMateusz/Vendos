#include "TilesByItemsManagement.h"

TilesByItemsManagement::TilesByItemsManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>* eq)
	: TilesManagement(graphicsData, equipmentData, Tile)
{
	this->factoryOfItems.init(graphicsData, equipmentData);
	this->factoryOfTiles.init(graphicsData, equipmentData);
	this->eq = eq;
}

void TilesByItemsManagement::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->itemUsed=getItemUsed();

	this->coordsOfTileClicked = getCordsOfClickedTile(AllKeys);
	
	this->tileClicked = getTileUsed(AllKeys);
	
	this->actionTimeManagement(dt);
	
	this->chooseFunction();
	
	if (checkIfActionTriggered(AllKeys))
		if (checkIfActionIsPossible())
		{
			(this->*ToolAction)(AllKeys);
			setTimeoutWhileActionTrue();
		}
	
	
	//co sie dzieje jak ³apka pusta?


	//LISTA W texturedata.H -> TAM I TU UPDEJTOWAC

	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	//5 - hoed tiles - able to make croops here (no water)
	//6 - watered - able to make croops here and it will grow on here
	//7 - pure blockade
	//8 - chests - left->destroy right->open
	//9 - player

	
		; //is action is not happening its possible to do action

	//std::cout << whichTileIsClicked(AllKeys).x<<" "<< whichTileIsClicked(AllKeys).y<<"\n";

}

void TilesByItemsManagement::ToolDropItem(const std::map<std::string, button*>& AllKeys)
{
	if (checkIfTileTypeMatchingToolType())
		if (this->Tile->at(coordsOfTileClicked.x).at(coordsOfTileClicked.y)->getRemainingDurability()>0)
		{
			this->graphicsData->itemDroppedVec->push_back(new itemDroppedFromTile());
			this->graphicsData->itemDroppedVec->back()->itemID = tileClicked->idOfBlocksThatDropsFromTile.at(0); //which tile?
			this->graphicsData->itemDroppedVec->back()->tileCords = coordsOfTileClicked;
			this->graphicsData->itemDroppedVec->back()->ammountOfItem = tileClicked->ammountOfItemsDroppedFromTile.at(0);

			takingResistanceDown(this->coordsOfTileClicked, this->itemUsed);
		}

	
}

void TilesByItemsManagement::ToolReplaceBlock(const std::map<std::string, button*>& AllKeys)
{
	if (checkIfTileTypeMatchingToolType())
	{
		initTile(this->coordsOfTileClicked, this->itemUsed->getItemName());

		this->equipmentData->needToUpdateTilesSpriteVec = 1;
		this->equipmentData->needToUpdateCameraAllSpr = 1;
	}
}

void TilesByItemsManagement::ToolPickItemFromTile(const std::map<std::string, button*>& AllKeys)
{
	std::cout << "pickaction\n";
	;
}

void TilesByItemsManagement::ToolPlaceItem(const std::map<std::string, button*>& AllKeys)
{
	std::cout << "placeAction\n";
	initTile(coordsOfTileClicked, this->itemUsed->getItemName());
	this->itemUsed->substrFromThisItem(1);
}

void TilesByItemsManagement::HandAction(const std::map<std::string, button*>& AllKeys)
{
	std::cout << "handactione\n";
	;
}

bool TilesByItemsManagement::checkIfActionTriggered(const std::map<std::string, button*>& AllKeys)
{
	return AllKeys.at("LeftMouse")->isButtonPressed()? true:false;
}

bool TilesByItemsManagement::checkIfActionIsPossible()
{
	return (not(timeoutWhileActionIsHappening) and this->equipmentData->isEqOpened == 0 and this->itemUsed != nullptr) ? true:false;
}

void TilesByItemsManagement::actionTimeManagement(const float& dt)
{
	if (timeoutWhileActionIsHappening)
		timePassedWhileAction += dt;

	if (itemUsed != nullptr)
	{
		if (timePassedWhileAction >= this->itemUsed->getTimeOfActionOfItemUsage())
		{
			timeoutWhileActionIsHappening = 0;
			timePassedWhileAction = 0;
		}
	}
	else
	{
		if (timePassedWhileAction >= 0.2)
		{
			timeoutWhileActionIsHappening = 0;
			timePassedWhileAction = 0;
		}
	}
}

void TilesByItemsManagement::setTimeoutWhileActionTrue()
{
	this->timeoutWhileActionIsHappening = true;
}

void TilesByItemsManagement::resetTimeoutWhileActionTrue()
{
	timeoutWhileActionIsHappening = 0;
	timePassedWhileAction = 0;
}


void TilesByItemsManagement::setNumberOfSlotOnBottomBar(const int& number)
{
	this->numberOfSlotOnBottomBar = number;
}

int TilesByItemsManagement::getNumberOfSlotOnBottomBar()
{
	return this->numberOfSlotOnBottomBar;
}


bool TilesByItemsManagement::checkIfTileTypeMatchingToolType()
{
	if (this->tileClicked != nullptr)
	{
		if (itemUsed->getTypeOfBlocksToInterract()->end() != std::find_if(std::begin(*itemUsed->getTypeOfBlocksToInterract()), std::end(*itemUsed->getTypeOfBlocksToInterract()),
			[&](tileType type) {return type == tileClicked->typeOfTile; }))
			return true;
	}
	else if (itemUsed->getIsCreatingOnEmptyTilePossible() == true) return true;

	return false;
}

item* TilesByItemsManagement::getItemUsed()
{
	return this->eq->at(this->numberOfSlotOnBottomBar).at(0).second->getItemPtr();
}

TilesOnMap* TilesByItemsManagement::getTileUsed(const std::map<std::string, button*>& AllKeys)
{
	return this->tileClicked = this->Tile->at(AllKeys.at("LeftMouse")->mouseTileGet().x)[AllKeys.at("LeftMouse")->mouseTileGet().y];
}

void TilesByItemsManagement::chooseFunction()
{
	if (itemUsed != nullptr)
	{
		switch (itemUsed->getTypeOfAction())
		{
		case TypeOfAction::Drop:
			this->ToolAction = &TilesByItemsManagement::ToolDropItem;
			break;
		case TypeOfAction::Replace:
			this->ToolAction = &TilesByItemsManagement::ToolReplaceBlock;
			break;
		case TypeOfAction::Pick:
			this->ToolAction = &TilesByItemsManagement::ToolPickItemFromTile;
			break;
		case TypeOfAction::Place:
			this->ToolAction = &TilesByItemsManagement::ToolPlaceItem;
			break;
		case TypeOfAction::Hand:
			this->ToolAction = &TilesByItemsManagement::HandAction;
			break;
		}
	}
	else
	{
		this->ToolAction = &TilesByItemsManagement::HandAction;
	}
}



