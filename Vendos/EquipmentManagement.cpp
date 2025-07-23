#include "EquipmentManagement.h"

EquipmentManagement::EquipmentManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, 
	std::vector<std::vector<item*>>* Eq, std::vector<std::vector<item*>>* Crafting, ThrownItems* ItemsOnTheGround)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Eq = Eq;
	this->crafting = Crafting;
	this->factoryOfItems.init(graphicsData, equipmentData);
	this->ItemsOnTheGround = ItemsOnTheGround;

	this->OffsetHeightEqAndSpacing = HeightOfEqPlusChest - equipmentData->sizeOfEq.y; //7-3 = 4

	this->craftingManagement = new CraftingManagement(graphicsData, equipmentData, Eq, Crafting, &craftingSpot);
	this->allItemsArea = new std::vector<itemAndItsPosition*>;
}

void EquipmentManagement::update(const std::map<std::string, button*>& AllKeys)
{
	if (this->equipmentData->isEqOpened == 1)
	{
		//firstEqArea->connectAreas(secondEqArea, allItemsArea);
		//do dupy to jest do przerobienia ,wszystko musi byc w tej klasie, a tutaj jedynie bedzie sie udpejtowa³o jej zawartoœæ


		checkIfCraftingSpotIsBeingHovered(AllKeys);

		//+++check if chest is not open + eqPos = {7, 1} -> if both ok then zmieniaja sie troche warunki 
		//left/right without shift do the same ->take item / add to stack in hand 
		//left/right with shift -> make max stack possible (based on item in source or max stack of created item)


		if (not(AllKeys.at("LShift")->isButtonPressed()) and AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and itemTakenThisFrame == 0) //DONE
			takingItemToTheHand(AllKeys);

		if (AllKeys.at("LShift")->isButtonPressed() and AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and itemTakenThisFrame == 0 and this->equipmentData->isChestOpened)
			sendItemToOtherInventorySpace(AllKeys);

		if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr)
			takeOneItemToHand(AllKeys);

		if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and itemGrabbed != nullptr and itemTakenThisFrame == 0)
			takeOneMoreItemToHand(AllKeys);

		if (itemGrabbed != nullptr) //DONE
			moveItemWhereCursorGoes(AllKeys);

		if (AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed != nullptr and itemTakenThisFrame == 0) //DONE 
			putOffItemFromHand(AllKeys);


		this->itemTakenThisFrame = 0;

		this->craftingManagement->update();
	}
}

void EquipmentManagement::render()
{
	this->craftingManagement->render();

	if (this->itemGrabbed != nullptr)
		this->itemGrabbed->render(); //its doubled - render in eq/chest render function and here???
}

bool EquipmentManagement::isAbleToCloseEq()
{
	if (itemGrabbed==nullptr) return true;
	return false;
}

bool EquipmentManagement::isMouseInEqLayout()
{
	if (this->equipmentData->eqPos.x >= 0
		and this->equipmentData->eqPos.x < this->equipmentData->sizeOfEq.x
		and ((this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened)
			or (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and (this->equipmentData->eqPos.x > 2 and this->equipmentData->eqPos.x < 6) and not(this->equipmentData->isChestOpened))
			or (this->equipmentData->eqPos.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPos.y < this->HeightOfEqPlusChest)))
		return true;
	else return false;
}

void EquipmentManagement::stackingItems()
{
	this->overMaxInStack = holder->addItemsReturn1IfOverMax(itemGrabbed);

	if (this->overMaxInStack == false)
	{
		delete this->itemGrabbed;
		this->itemGrabbed = nullptr;
	}
}

void EquipmentManagement::stackingItemsInCrafting()
{
	this->overMaxInStack = itemGrabbed->addItemsReturn1IfOverMax_DontAddWhenOverMax(holder);

	if (this->overMaxInStack == false)
	{
		decreaseItemsInCrafting();
		delete this->craftingSpot;
		this->craftingSpot = nullptr;
	}
}

void EquipmentManagement::searchForNextFreeSpot(std::vector<std::vector<item*>>* ArrayToSearch, item* ItemToPut)
{
	int tempTest = 0;

	for (auto& row : *ArrayToSearch)
		for (auto& elem : row)
			if (elem == nullptr)
				tempTest++;

	std::cout <<"Wolnych spotow: " << tempTest << "\n";
}

void EquipmentManagement::substractItemInCrafting(item* itemToSubstr, int numberOfItems)
{
	itemToSubstr->substrFromThisItem(numberOfItems);
	
	if (itemToSubstr->getNumberOfItems() < 1)
		itemToSubstr = nullptr;

}

void EquipmentManagement::decreaseItemsInCrafting()
{
	for (auto& row : *crafting)
		for (auto& elem : row)
			if (elem != nullptr)
			{
				substractItemInCrafting(elem, 1);

				if (elem->getNumberOfItems() < 1)
				{
					delete elem;
					elem = nullptr;
				}
			}
}

void EquipmentManagement::takingItemToTheHand(const std::map<std::string, button*>& AllKeys)
{
	this->equipmentData->eqPos=getWhichTileIsClicked(AllKeys);

	if (this->equipmentData->eqPos.x >= 0 and this->equipmentData->eqPos.x < this->equipmentData->sizeOfEq.x)
		if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened)							//Chest area
		{
				std::swap(this->itemGrabbed, this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]);
				this->itemTakenThisFrame = 1;
		}
		else if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and (this->equipmentData->eqPos.x>2 and this->equipmentData->eqPos.x <6) and not(this->equipmentData->isChestOpened))					//Crafting
		{
				std::swap(this->itemGrabbed, crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y));
				this->itemTakenThisFrame = 1;
		}
		else if (this->equipmentData->eqPos.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPos.y < this->HeightOfEqPlusChest)		//Eq area
		{
				std::swap(this->itemGrabbed, Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing));
				this->itemTakenThisFrame = 1;
		}

	if (craftingSpotHovered)
	{
		std::swap(this->itemGrabbed, craftingSpot);
		decreaseItemsInCrafting();
		this->itemTakenThisFrame = 1;
	}

}

void EquipmentManagement::moveItemWhereCursorGoes(const std::map<std::string, button*>& AllKeys)
{
	this->itemGrabbed->itemSprite.setPosition(AllKeys.at("LeftMouse")->mousePosGet().x - TilesOnMap::GetSizeOfTile(), AllKeys.at("LeftMouse")->mousePosGet().y - TilesOnMap::GetSizeOfTile());
}

void EquipmentManagement::putOffItemFromHand(const std::map<std::string, button*>& AllKeys)
{
	this->equipmentData->eqPosNew = getWhichTileIsClicked(AllKeys);
	
	this->holder = nullptr;

	//Checking if mouse pos in on eq / chest
	if (isMouseInEqLayout())
	{
		if (this->equipmentData->eqPosNew.y >= 0 and this->equipmentData->eqPosNew.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened) //Mouse in chest area
		{
			if (this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] != nullptr
				and this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y]->itemID == this->itemGrabbed->itemID)
			{
				this->holder = this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y];
				stackingItems();
			}
			else
			std::swap(this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y], this->itemGrabbed);

		}
		else if (this->equipmentData->eqPosNew.y >= 0 and this->equipmentData->eqPosNew.y < this->equipmentData->sizeOfEq.y and (this->equipmentData->eqPosNew.x > 2 and this->equipmentData->eqPosNew.x < 6) and not(this->equipmentData->isChestOpened)) //Crafting area
		{
			if (this->crafting->at(this->equipmentData->eqPosNew.x-3).at(this->equipmentData->eqPosNew.y) != nullptr
				and this->crafting->at(this->equipmentData->eqPosNew.x-3).at(this->equipmentData->eqPosNew.y)->itemID == this->itemGrabbed->itemID)
			{
				this->holder = this->crafting->at(this->equipmentData->eqPosNew.x-3).at(this->equipmentData->eqPosNew.y);
				stackingItems();
			}
			else
				std::swap(this->crafting->at(this->equipmentData->eqPosNew.x-3).at(this->equipmentData->eqPosNew.y), this->itemGrabbed);
		}
		else if (this->equipmentData->eqPosNew.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPosNew.y < this->HeightOfEqPlusChest) //Mouse in eq area
		{
			if (this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) != nullptr
				and this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing)->itemID == this->itemGrabbed->itemID)
			{
				this->holder = this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing);
				stackingItems();
			}
			else 
			std::swap(this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing), this->itemGrabbed);
		}
	}
	else if (this->craftingSpotHovered)
	{
		this->holder = this->craftingSpot;
		stackingItemsInCrafting();
	}
	else
	{
		throwItem(itemGrabbed);
	}

	this->holder = nullptr;

	this->equipmentData->needToUpdateEq = true;

	if (not(this->equipmentData->isChestOpened))
		this->equipmentData->needToUpdateCrafting = true;

	if (this->equipmentData->isChestOpened)
		this->equipmentData->needToUpdateChest = true;
}

void EquipmentManagement::sendItemToOtherInventorySpace(const std::map<std::string, button*>& AllKeys)
{
	std::cout << "XD\n";
	searchForNextFreeSpot(Eq, itemGrabbed);
}

void EquipmentManagement::takeOneItemToHand(const std::map<std::string, button*>& AllKeys)
{
	 this->equipmentData->eqPos=getWhichTileIsClicked(AllKeys);
	
	//After catching 
		if (this->equipmentData->eqPos.x >= 0 and this->equipmentData->eqPos.x < this->equipmentData->sizeOfEq.x)
			if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened)							//Chest area
			{
				if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] != nullptr)
				{
					if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->getNumberOfItems() == 1)
						takingItemToTheHand(AllKeys);
					else
					{
						this->itemGrabbed = factoryOfItems.creatorOfItemBasedOnExample(this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]);
						*this->itemGrabbed = *this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y];
						this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->substrFromThisItem(1);
						this->itemGrabbed->changeNumberOfItems(1);
						this->itemTakenThisFrame = 1;
					}
				}
			}
			else if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfCrafting.y and (this->equipmentData->eqPos.x > 2 and this->equipmentData->eqPos.x < 6) and not(this->equipmentData->isChestOpened)) //crafting area
			{
				if (this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y) != nullptr)
				{
					if (this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y)->getNumberOfItems() == 1)
						takingItemToTheHand(AllKeys);
					else
					{
						this->itemGrabbed = factoryOfItems.creatorOfItemBasedOnExample(crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y));
						*this->itemGrabbed = *crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y );
						crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y)->substrFromThisItem(1);
						this->itemGrabbed->changeNumberOfItems(1);
						this->itemTakenThisFrame = 1;
					}
				}
			}
			else if (this->equipmentData->eqPos.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPos.y < this->HeightOfEqPlusChest)		//Eq area
			{
				if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) != nullptr)
				{
					if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->getNumberOfItems() == 1)
						takingItemToTheHand(AllKeys);
					else
					{
						this->itemGrabbed = factoryOfItems.creatorOfItemBasedOnExample(Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing));
						*this->itemGrabbed = *Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing);
						Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->substrFromThisItem(1);
						this->itemGrabbed->changeNumberOfItems(1);
						this->itemTakenThisFrame = 1;
					}
				}
			}

		if (this->craftingSpotHovered)
		{
			std::swap(this->itemGrabbed, craftingSpot);
			decreaseItemsInCrafting();
			this->itemTakenThisFrame = 1;
		}

}

void EquipmentManagement::takeOneMoreItemToHand(const std::map<std::string, button*>& AllKeys)
{
	this->equipmentData->eqPos = getWhichTileIsClicked(AllKeys);

	if (isMouseInEqLayout())
	{
		if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened) //Chest area
		{
			if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] != nullptr)
			{
				if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->itemID == itemGrabbed->itemID)
				{
					this->itemGrabbed->addToThisItem(1);
					this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->substrFromThisItem(1);
					if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->getNumberOfItems() == 0)
					{
						delete this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y];
						this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = nullptr;
					}
				}
			}
			else
			{
				if (itemGrabbed->getNumberOfItems() > 1)
				{
					this->itemGrabbed->substrFromThisItem(1);
					this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = factoryOfItems.creatorOfItemBasedOnExample(itemGrabbed);
					*this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = *itemGrabbed;
				}
				else
				{
					std::swap(this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y], itemGrabbed);
				}
				this->equipmentData->needToUpdateChest = true;
			}
		}
		else if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfCrafting.y and this->equipmentData->eqPos.x > 2 and this->equipmentData->eqPos.x < 6 and not(this->equipmentData->isChestOpened)) //crafting area
		{
			if (this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y) != nullptr)
			{
				if (this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y )->itemID == itemGrabbed->itemID)
				{
					itemGrabbed->addToThisItem(1);
					this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y)->substrFromThisItem(1);
					if (this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y)->getNumberOfItems() == 0)
						this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y) = nullptr;
				}
			}
			else
			{
				if (itemGrabbed->getNumberOfItems() > 1)
				{
					this->itemGrabbed->substrFromThisItem(1);
					this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y) = factoryOfItems.creatorOfItemBasedOnExample(itemGrabbed);
					*this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y) = *itemGrabbed;
				}
				else
				{
					std::swap(this->crafting->at(this->equipmentData->eqPos.x-3).at(this->equipmentData->eqPos.y), this->itemGrabbed);
				}
				this->equipmentData->needToUpdateCrafting = true;
			}
		}
		else if (this->equipmentData->eqPos.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPos.y < this->HeightOfEqPlusChest) //Eq area
		{
			if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) != nullptr)
			{
				if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->itemID == itemGrabbed->itemID)
				{
					itemGrabbed->addToThisItem(1);
					this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->substrFromThisItem(1);
					if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->getNumberOfItems() == 0)
						this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) = nullptr;
				}
			}
			else
			{
				if (itemGrabbed->getNumberOfItems() > 1)
				{
					this->itemGrabbed->substrFromThisItem(1);
					this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) = factoryOfItems.creatorOfItemBasedOnExample(itemGrabbed);
					*this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) = *itemGrabbed;
				}
				else
				{
					std::swap(this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing), this->itemGrabbed);
				}
				this->equipmentData->needToUpdateEq = true;
			}
		}
	}
}

void EquipmentManagement::throwItem(item* item)
{
	this->ItemsOnTheGround->insertItemDroppedFromPlayer(item);
	this->itemGrabbed = nullptr;
}

bool EquipmentManagement::checkIsFirstAreaClicked(const std::map<std::string, button*>& AllKeys)
{
	return false;
}

bool EquipmentManagement::checkIsSecondAreaClicked(const std::map<std::string, button*>& AllKeys)
{
	return false;
}

sf::Vector2i EquipmentManagement::getWhichTileIsClicked(const std::map<std::string, button*>& AllKeys)
{
	return
	{
		(int)(std::floor((float)(AllKeys.at("LeftMouse")->mousePosGet().x - (int)this->equipmentData->FirstItemPositionEq.x) / (float)this->equipmentData->SizeOfItems)),
		(int)(((AllKeys.at("LeftMouse")->mousePosGet().y - (int)this->equipmentData->FirstItemPositionEq.y + (this->HeightOfEqPlusChest * this->equipmentData->SizeOfItems)) / this->equipmentData->SizeOfItems) - 1)
	};
}

void EquipmentManagement::checkIfCraftingSpotIsBeingHovered(const std::map<std::string, button*>& AllKeys)
{
	this->craftingSpotHovered = 0;

	if (this->equipmentData->isChestOpened == 0)
	{	
		this->equipmentData->eqPos = getWhichTileIsClicked(AllKeys);
		if (this->equipmentData->eqPos == sf::Vector2i(7, 1))
			this->craftingSpotHovered = 1;
	}
}

