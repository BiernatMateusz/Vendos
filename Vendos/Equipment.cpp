#include "Equipment.h"


//Constructor
Equipment::Equipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>*Tile, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround)
	: EquipmentStorageArea(graphicsData, equipmentData,{ 9,3 }, { 0,0 }, {}, {}, "BackgroundCrafting")
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;

	this->itemsOnTheGround = ItemsOnTheGround;

	initEquipment();
	
	this->eqAreas = new EquipmentAreas(this->graphicsData, this->equipmentData, this->getItemsArea(), nullptr, ItemsOnTheGround);

	this->Tile = Tile;

	this->tilesByItemManagement = new TilesByItemsManagement(this->graphicsData, this->equipmentData, this->Tile, this->getItemsArea());

	this->itemsOnTheGround->initEqPtr(this->getItemsArea());
}


void Equipment::updateKeybinds(const std::map<std::string, button*>& AllKeys)
{
	//E key
	openingEquipment(AllKeys);
	
	//Dealing with chests
	openingChest(AllKeys);

	//1-9(0) keys
	changingSelectedItem(AllKeys);
}

void Equipment::initEquipment()
{
	factoryOfItems.init(this->graphicsData, this->equipmentData);
	getItemsArea()->at(0).at(0).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(100, 10));
	getItemsArea()->at(0).at(2).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(101, 10));
	getItemsArea()->at(0).at(1).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(100, 995));
	getItemsArea()->at(1).at(1).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(100, 995));
	getItemsArea()->at(2).at(1).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(100, 995));
	getItemsArea()->at(2).at(0).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(22, 1));
	getItemsArea()->at(3).at(0).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(21, 1));
	getItemsArea()->at(4).at(0).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(105, 1));
	getItemsArea()->at(6).at(0).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(20, 1));
	getItemsArea()->at(7).at(0).second->setItemPtr(factoryOfItems.creatorOfItemBasedOnID(25, 1));

	calculatePositionOfFirstItemEqAndChest();
}

void Equipment::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->tilesByItemManagement->update(dt, AllKeys);
	
	if (secondEq != nullptr)
		secondEq->update(dt, AllKeys);

	this->eqAreas->update(AllKeys);

	this->itemsOnTheGround->update(dt);

	this->updateKeybinds(AllKeys); 

}

void Equipment::render()
{
	if (this->equipmentData->openedWorkstation != nullptr)
		this->equipmentData->openedWorkstation->render();
	
		this->eqAreas->render();
		
}

//Functions
void Equipment::openingEquipment(const std::map<std::string, button*>& AllKeys)
{
	this->ableToClose = 0;
	this->ableToOpen = 0;

	if (AllKeys.at("E")->oneSignalButtonPressed())
	{
		if (this->equipmentData->isEqOpened)
			this->ableToClose = true;
		else this->ableToOpen = true;
	}

	if (this->ableToOpen)
	{
		this->equipmentData->isEqOpened = true;
		delete this->eqAreas;
		this->crafting = new Crafting(this->graphicsData, this->equipmentData, this->itemsOnTheGround);
		this->equipmentData->openedWorkstation = this->crafting;
		this->eqAreas= new EquipmentAreas(this->graphicsData, this->equipmentData, this->getItemsArea(), this->crafting->getItemsArea(), this->itemsOnTheGround);
		this->secondEq = this->crafting;
	}

	if (this->ableToClose and this->eqAreas->isAbleToCloseEq()) //prevents from holding an item and closing chest at the same time 
	{
		this->equipmentData->isEqOpened = false;
		this->equipmentData->isChestOpened = false;
		this->equipmentData->openedWorkstation = nullptr;
		delete this->eqAreas;

		if (this->crafting != nullptr)
		{
			delete this->crafting;
			this->crafting = nullptr;
		}

		this->eqAreas = new EquipmentAreas(this->graphicsData, this->equipmentData, this->getItemsArea(), nullptr, this->itemsOnTheGround);
		this->secondEq = nullptr;
	}

}

void Equipment::openingChest(const std::map<std::string, button*>& AllKeys)
{
	if (!this->equipmentData->isEqOpened)
		if (AllKeys.at("RightMouse")->oneSignalButtonPressed()) //NEED TO CHECK IF ITS ON THE TILE MAP -> >=0 <=50/70
		{
			this->OpenedWorkstationAreaCords = AllKeys.at("RightMouse")->mouseTileGet();

			if ((*Tile)[OpenedWorkstationAreaCords.x][OpenedWorkstationAreaCords.y] != nullptr)
			{
				if ((*Tile)[OpenedWorkstationAreaCords.x][OpenedWorkstationAreaCords.y]->typeOfTile == tileType::chestField)
				{
					ableToOpen = true;
					this->equipmentData->openedWorkstation = this->Tile->at(OpenedWorkstationAreaCords.x).at(OpenedWorkstationAreaCords.y)->storageArea;
				}

				if (this->ableToOpen)
				{
					this->equipmentData->isEqOpened = true;
					this->equipmentData->isChestOpened = true;
					this->eqAreas = new EquipmentAreas(this->graphicsData, this->equipmentData, this->getItemsArea(), this->equipmentData->openedWorkstation->getItemsArea(), this->itemsOnTheGround);
					this->secondEq = this->equipmentData->openedWorkstation;
				}

			}
		}
}

void Equipment::calculatePositionOfFirstItemEqAndChest()
{
	sf::Vector2f MapBorder{};

	MapBorder = { (float)this->graphicsData->window->getSize().x,(float)this->graphicsData->window->getSize().y };
	
	this->equipmentData->FirstItemPositionEq = {
		(MapBorder.x / 2) - (this->equipmentData->sizeOfEq.x / 2 * this->equipmentData->SizeOfItems),
		MapBorder.y - this->equipmentData->Y_Offset_Bar_From_Border };

}

void Equipment::changingSelectedItem(const std::map<std::string, button*>& AllKeys)
{
	int mem = this->equipmentData->whichItemSelected;

	if (AllKeys.at("Num1")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 0;

	if (AllKeys.at("Num2")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 1;

	if (AllKeys.at("Num3")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 2;

	if (AllKeys.at("Num4")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 3;

	if (AllKeys.at("Num5")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 4;

	if (AllKeys.at("Num6")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 5;

	if (AllKeys.at("Num7")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 6;

	if (AllKeys.at("Num8")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 7;

	if (AllKeys.at("Num9")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 8;

	if (AllKeys.at("Num0")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 9;

	if (mem != this->equipmentData->whichItemSelected)
		this->tilesByItemManagement->resetTimeoutWhileActionTrue();

	this->tilesByItemManagement->setNumberOfSlotOnBottomBar(this->equipmentData->whichItemSelected); //to rework
	
}