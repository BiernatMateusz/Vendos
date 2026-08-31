#include "EquipmentAreas.h"
#include "EquipmentInputControler.h"

//Constuctors

EquipmentAreas::EquipmentAreas(GraphicsData* graphicsData, EquipmentData* equipmentData, ItemStorage* itemsFirstArea, ItemStorage* itemsSecondArea, ThrownItems* ItemsOnTheGround)
	: EquipmentAreasMenagement(graphicsData, equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;

	factoryOfItems.init(graphicsData, equipmentData);
	this->itemsOnTheGround = ItemsOnTheGround;

	initRealPosOfItems_0_0();

	if (itemsSecondArea!=nullptr)
		this->visibleStorages = { itemsFirstArea, itemsSecondArea };
	else 
		this->visibleStorages = { itemsFirstArea };

	this->itemTakenThisFrame = true;
}

EquipmentAreas::~EquipmentAreas()
{
	;
}

void EquipmentAreas::update(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	updateKeybinds(AllKeys);
	deleteItemIfAmmount_0();
	updatePositionsOfItems(AllKeys);

	this->itemTakenThisFrame = 0;
}

void EquipmentAreas::updateWhileClosed()
{
	deleteItemIfAmmount_0();
}

void EquipmentAreas::updateKeybinds(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	getHoveredSquareStatus(AllKeys);
	
	if (this->isInWorkArea == true)
	{
		if (not(AllKeys.at(inputAction::LShift)->isButtonPressed()) and AllKeys.at(inputAction::LMouse)->oneSignalButtonPressed() and !itemGrabbed and this->itemTakenThisFrame == 0)
			takingItemToTheHand(AllKeys); //DONE

		if (AllKeys.at(inputAction::LShift)->isButtonPressed() and AllKeys.at(inputAction::LMouse)->oneSignalButtonPressed() and !itemGrabbed and this->itemTakenThisFrame == 0)
			searchForPlaceForWholeStack(); //DONE

		if (AllKeys.at(inputAction::LMouse)->oneSignalButtonPressed() and itemGrabbed and this->itemTakenThisFrame == 0)
			putOffItemFromHand(AllKeys); //DONE

		if (AllKeys.at(inputAction::RMouse)->oneSignalButtonPressed() and !itemGrabbed and this->itemTakenThisFrame == 0)
			takeHalfOfItemsToHand(AllKeys); //DONE

		if (AllKeys.at(inputAction::RMouse)->oneSignalButtonPressed() and itemGrabbed and this->itemTakenThisFrame == 0)
			placeOneMoreItem(AllKeys); //DONE
	}
	else if (this->itemGrabbed)
	{
		if (AllKeys.at(inputAction::LMouse)->oneSignalButtonPressed() and this->itemTakenThisFrame == 0)
			throwItem(this->itemGrabbed, true); //DONE

		if (AllKeys.at(inputAction::RMouse)->oneSignalButtonPressed() and this->itemTakenThisFrame == 0)
			throwItem(this->itemGrabbed, false); //DONE
	}
}

void EquipmentAreas::initRealPosOfItems_0_0()
{
	this->realPosOfItems_0_0 = this->equipmentData->FirstItemPositionEq;
}

void EquipmentAreas::setHoveredStorage()
{
	if (visibleStorages.size() == 1)
		this->hoveredStorage = visibleStorages.at(0);
	else if (visibleStorages.size() > 1)
	{
		if (this->SquareHovered.y >= visibleStorages.at(1)->getFirstLayer_Y())
			this->hoveredStorage = visibleStorages.at(1);
		else this->hoveredStorage = visibleStorages.at(0);
	}
	else this->hoveredStorage = nullptr;
}

void EquipmentAreas::getHoveredSquareStatus(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	this->SquareHovered = 
	{	(int)((std::floor((float)(AllKeys.at(inputAction::LMouse)->mousePosGet().x - (int)this->realPosOfItems_0_0.x) / (float)this->equipmentData->SizeOfItems))), //x
		(int)(std::floor((this->realPosOfItems_0_0.y - AllKeys.at(inputAction::LMouse)->mousePosGet().y) / (float)this->equipmentData->SizeOfItems)) + 1			//y
	};

	setHoveredStorage();

	checkIfIsInWorkArea();
}

ItemStorage* EquipmentAreas::getOtherStorage(ItemStorage* current)
{
	if (visibleStorages.size() < 2)
		return visibleStorages[0];

	if (visibleStorages[0] == current)
	{
		return visibleStorages[1];
	}

	return visibleStorages[0];
}

void EquipmentAreas::checkIfIsInWorkArea()
{
	if (((this->SquareHovered.x >= 0 and this->SquareHovered.x < this->sizeOfArea.x) and (this->SquareHovered.y >= 0 and this->SquareHovered.y < this->sizeOfArea.y)) and this->hoveredStorage->isUsable(this->SquareHovered.x, this->SquareHovered.y))
		this->isInWorkArea = true;
	else this->isInWorkArea = false;
}

void EquipmentAreas::updatePositionsOfItems(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	for (int y = 0; y < this->sizeOfArea.y; y++)
		for (int x = 0; x < this->sizeOfArea.x; x++)
			if (this->hoveredStorage->isUsable(x,y))
				if (this->hoveredStorage->getSlotRef(x,y))
					this->hoveredStorage->getSlotRef(x, y).get()->setPositionInStorage({ (x * this->equipmentData->SizeOfItems) + this->realPosOfItems_0_0.x,this->realPosOfItems_0_0.y - (y * this->equipmentData->SizeOfItems) });
	
	if (this->itemGrabbed)
		this->itemGrabbed.get()->cameraSpriteOfItem.getSprite().setPosition({AllKeys.at(inputAction::LMouse)->mousePosGet().x - (float)(this->equipmentData->SizeOfItems / 2), AllKeys.at(inputAction::LMouse)->mousePosGet().y - (float)(this->equipmentData->SizeOfItems / 2)});

}

void EquipmentAreas::deleteItemIfAmmount_0()
{
	for (int i=0;i<visibleStorages.size();++i)
		for (int y = 0; y < this->sizeOfArea.y; y++)
			for (int x = 0; x < this->sizeOfArea.x; x++)
				if (this->visibleStorages.at(i)->isUsable(x, y))
					if (this->visibleStorages.at(i)->getSlotRef(x, y))
						if (this->visibleStorages.at(i)->getSlotRef(x, y).get()->getNumberOfItems() == 0)
							this->visibleStorages.at(i)->getSlotRef(x, y).clear();

}

void EquipmentAreas::takingItemToTheHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	this->itemGrabbed.swapItems(this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y));
	this->itemTakenThisFrame = true;
}

void EquipmentAreas::putOffItemFromHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	auto& hoveredSquare = this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y);
	auto* hoveredSquarePtr = hoveredSquare.get();
	auto* itemGrabbedPtr = itemGrabbed.get();

	if (hoveredSquare.getType() != typeOfSlot::Pick)
	{
		if (!hoveredSquarePtr or
			(hoveredSquarePtr and hoveredSquarePtr->getItemID() != itemGrabbedPtr->getItemID())
	)
		{
			this->itemGrabbed.swapItems(hoveredSquare);
			this->itemTakenThisFrame = true;
		}
		else if (hoveredSquarePtr->getItemID() == itemGrabbedPtr->getItemID())
			addSlots(this->itemGrabbed, hoveredSquare);
	}
}

void EquipmentAreas::takeOneItemToHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	auto &hoveredSquare = this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y);
	auto* hoveredSquarePtr = hoveredSquare.get();
	auto* itemGrabbedPtr = itemGrabbed.get();

	if (hoveredSquarePtr)
	{
		if (hoveredSquarePtr->getNumberOfItems() == 1)
			this->itemGrabbed.swapItems(hoveredSquare);
		else
		{
			this->itemGrabbed.setItemPtr(factoryOfItems.createItem(hoveredSquarePtr->getItemName()));
			itemGrabbedPtr->setNumberOfItems(1);
			hoveredSquarePtr->substrFromThisItem(1);
		}
		this->itemTakenThisFrame = true;
	}
}

void EquipmentAreas::takeHalfOfItemsToHand(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	auto &hoveredSquare = this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y);
	auto* hoveredSquarePtr = hoveredSquare.get();
	auto* itemGrabbedPtr = itemGrabbed.get();

	if (hoveredSquarePtr)
	{
		if (hoveredSquarePtr->getNumberOfItems() == 1)
			this->itemGrabbed.swapItems(hoveredSquare);
		else
		{
			int tmpGrabbedNumberValue = hoveredSquarePtr->getHalfOfItems();

			this->itemGrabbed.setItemPtr(this->factoryOfItems.createItem(hoveredSquarePtr->getItemName()));
			this->itemGrabbed.get()->setNumberOfItems(tmpGrabbedNumberValue);
			hoveredSquarePtr->substrFromThisItem(tmpGrabbedNumberValue);
			
		}
		this->itemTakenThisFrame = true;
	}
}

void EquipmentAreas::placeOneMoreItem(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	auto& hoveredSquare = this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y);
	auto* hoveredSquarePtr = hoveredSquare.get();
	auto* itemGrabbedPtr = itemGrabbed.get();

	if (hoveredSquarePtr)
	{
		if (hoveredSquarePtr->getItemID() == itemGrabbed.get()->getItemID())
			if (hoveredSquarePtr->addOneItemReturn1IfNmbOfItemsFromTakenIs0(itemGrabbedPtr))
				this->itemGrabbed.clear();
	}
	else
	{
		hoveredSquare.setItemPtr(this->factoryOfItems.createItem(itemGrabbedPtr->getItemName()));
		hoveredSquare.get()->setNumberOfItems(1);
		itemGrabbedPtr->substrFromThisItem(1);
		if (itemGrabbedPtr->isNullItemsInStack())
			this->itemGrabbed.clear();
	}
}

void EquipmentAreas::searchForPlaceForWholeStack()
{
	std::unique_ptr<item>tmpItem;
	if (this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y))
	{
		tmpItem = assignItemToChosenArea(this->hoveredStorage->getSlotRef(this->SquareHovered.x, this->SquareHovered.y).take(), *getOtherStorage(this->hoveredStorage), getOtherStorage(this->hoveredStorage)->getOrderOfSearch());
		if (tmpItem != nullptr)
			this->hoveredStorage->setSlot(this->SquareHovered.x, this->SquareHovered.y, std::move(tmpItem));
	}


}

void EquipmentAreas::setStorages(ItemStorage* firstStorage, ItemStorage* secondStorage)
{
	this->visibleStorages.clear();
	if (firstStorage !=nullptr)		this->visibleStorages.push_back(firstStorage);
	if (secondStorage != nullptr)	this->visibleStorages.push_back(secondStorage);
}

void EquipmentAreas::addSlots(slot& from, slot& to)
{
	if (to.get()->addItemsReturn1IfOverMax(from.get()) == false)
		from.clear();
}

void EquipmentAreas::throwItem(slot& item, bool isThrowdAllStack)
{
	if (!item.get()) return;

	if (isThrowdAllStack)
	{
		this->itemsOnTheGround->insertItemDroppedFromPlayer(item.take());
		this->itemGrabbed.clear();
	}
	else
	{
		this->itemsOnTheGround->insertItemDroppedFromPlayer(factoryOfItems.createItem(this->itemGrabbed.get()->getItemName()));
		this->itemsOnTheGround->setNumberOfItemsLastInVector(1);
		this->itemGrabbed.get()->substrFromThisItem(1);

		if (this->itemGrabbed.get()->getNumberOfItems() == 0)
			this->itemGrabbed.clear();
	}
}

void EquipmentAreas::forceReleaseGrabbedItem()
{
	if (!itemGrabbed) return;
	
	std::unique_ptr<item> tmp = assignItemToChosenArea(this->itemGrabbed.take(), *visibleStorages[0], visibleStorages[0]->getOrderOfSearch());

	if (tmp)
		this->itemsOnTheGround->insertItemDroppedFromPlayer(std::move(tmp));

}

bool EquipmentAreas::tryDeleteItems(ItemNames itemName, int count)
{
	if (isThereItem(*visibleStorages[0], itemName, count)) std::cout << "Są itemy\n";
	return false;
}

bool EquipmentAreas::isAbleToCloseEq()
{
	return !itemGrabbed;
}

void EquipmentAreas::render()
{
	visibleStorages.back()->renderBackground();

	for (auto* storage : visibleStorages)
		storage->render();
	
	
}

void EquipmentAreas::renderItemHeld()
{
	if (this->itemGrabbed)
		this->itemGrabbed.get()->render();
}
