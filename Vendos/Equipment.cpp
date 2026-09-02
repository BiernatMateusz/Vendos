#include "Equipment.h"

//Constructor
Equipment::Equipment(GraphicsData* graphicsData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>&Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround)
	: Tile(Tile),
	  graphicsData(graphicsData),
	  equipmentData(equipmentData),
	  itemsOnTheGround(ItemsOnTheGround)
{

	this->inputController = std::make_unique<EquipmentInputControler>();

	calculatePositionOfFirstItem();

	initPlayerStorage();
	initPlayerCrafting();

	this->eqAreas = std::make_unique<EquipmentAreas>(this->graphicsData, this->equipmentData, this->playerStorage.get(), nullptr, ItemsOnTheGround);
	this->tilesByItemManagement = std::make_unique<TilesByItemsManagement>(this->graphicsData, this->equipmentData, &this->Tile, this->playerStorage.get());
	
	this->itemsOnTheGround->initEqPtr(this->playerStorage.get());
	
}

void Equipment::initPlayerStorage()
{
	this->playerStorage = std::make_unique<PlayerStorage>(graphicsData, equipmentData);
}

void Equipment::initPlayerCrafting()
{
	this->playerCrafting = std::make_unique<CraftingItems>(graphicsData, equipmentData, this->playerStorage.get(), eqAreas.get());
}

void Equipment::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	
	this->itemsOnTheGround->update(dt, this->playerStorage.get()); //DONE
	this->inputController->update(AllKeys);	//DONE

	if (inputController->wantsToggleEq())
		handleToggleInventory();			//DONE

	if (inputController->wantsOpenChest())
		tryOpenChest();						//DONE
	
	this->tilesByItemManagement->update(dt, AllKeys); //Functionality wasnt tested - need update
	
	updateActiveStorages(AllKeys);
	
	this->playerCrafting->update(dt, AllKeys);
	
	updateBottomBar();
	
}

void Equipment::render()
{
	switch (this->equipmentData->uiState)
	{
	case EquipmentUIState::Closed:
		playerStorage->renderBottomBar();
		return;

	case EquipmentUIState::OpenedCrafting:
		eqAreas->render();
		playerCrafting->renderStorage();
		eqAreas->renderItemHeld();
		break;

	case EquipmentUIState::OpenedWithSecond:
		eqAreas->render();
		eqAreas->renderItemHeld();
		break;
	}
}

//Functions

void Equipment::setState(EquipmentUIState newState, EquipmentStorageArea* secondItemStorage)
{
	if (equipmentData->uiState == newState)
		return;

	this->equipmentData->uiState = newState;

	switch (newState)
	{
	case EquipmentUIState::Closed:
		this->eqAreas->forceReleaseGrabbedItem();
		this->eqAreas->setStorages(playerStorage.get(), nullptr);
		this->secondEq = nullptr;
		break;

	case EquipmentUIState::OpenedCrafting:
		this->eqAreas->setStorages(playerStorage.get(), playerCrafting.get());
		secondEq = playerCrafting.get();
		break;

	case EquipmentUIState::OpenedWithSecond:
		eqAreas->setStorages(playerStorage.get(), secondItemStorage);
		secondEq = secondItemStorage;
		break;

	}
}

void Equipment::handleToggleInventory()
{
	switch (equipmentData->uiState)
	{
	case EquipmentUIState::Closed:
		setState(EquipmentUIState::OpenedCrafting);
		break;
	case EquipmentUIState::OpenedCrafting:
		setState(EquipmentUIState::Closed);
		break;
	case EquipmentUIState::OpenedWithSecond:
		setState(EquipmentUIState::Closed);
		break;
	default:
		std::cout << "Cos nie tak w handleToggleInventory:Equipment\n";
	}
}

void Equipment::tryOpenChest()
{
	if (equipmentData->uiState != EquipmentUIState::Closed)
		return;

	if (!inputController->clickedTile().has_value())
		return;

	auto c = inputController->clickedTile().value();

	auto& tile = Tile[c.x][c.y];
	if (!tile || tile->typeOfTile != tileType::chestField)
		return;

	setState(EquipmentUIState::OpenedWithSecond,tile->storageArea);
}

void Equipment::calculatePositionOfFirstItem()
{
	sf::Vector2f MapBorder{};
	
	MapBorder = { (float)this->graphicsData->window->getSize().x,(float)this->graphicsData->window->getSize().y };
	
	this->equipmentData->FirstItemPositionEq = {
		(MapBorder.x / 2) - (this->equipmentData->sizeOfEq.x / 2 * this->equipmentData->SizeOfItems),
		MapBorder.y - this->equipmentData->Y_Offset_Bar_From_Border };
	
}

void Equipment::updateBottomBar()
{
	int slot = inputController->selectedSlot();
	if (slot != -1)
	{
		int mem = equipmentData->whichItemSelected;
		equipmentData->whichItemSelected = slot;

		if (mem != slot)
			tilesByItemManagement->resetTimeoutWhileActionTrue();

		tilesByItemManagement->setNumberOfSlotOnBottomBar(slot);
	}
}

void Equipment::updateActiveStorages(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	if (this->equipmentData->uiState != EquipmentUIState::Closed)
	{
		this->playerStorage->updateActiveStorage(AllKeys);

		if (secondEq != nullptr)
			secondEq->updateActiveStorage(AllKeys);

		this->eqAreas->update(AllKeys);							//this is doing all - moving items stacking etc.

	}
	else
		this->eqAreas->updateWhileClosed();
}
