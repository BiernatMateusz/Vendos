#include "EquipmentAreas.h"

//Constuctors
EquipmentAreas::EquipmentAreas(GraphicsData* graphicsData, EquipmentData* equipmentData)
	:EquipmentAreasMenagement(graphicsData, equipmentData)
{
	this->AllitemsArea = new std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>;
}

EquipmentAreas::EquipmentAreas(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsFirstArea, std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* itemsSecondArea, ThrownItems* ItemsOnTheGround)
	: EquipmentAreas(graphicsData, equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;

	factoryOfItems.init(graphicsData, equipmentData);
	this->itemsOnTheGround = ItemsOnTheGround;

	initRealPosOfItems_0_0();

	this->BackGroundSquare = new sf::Sprite;
	this->BackGroundSquareUsed = new sf::Sprite;

	this->BackGroundSquare->setTexture(*this->graphicsData->TextureDataMap->at("ramka")->texture);
	this->BackGroundSquareUsed->setTexture(*this->graphicsData->TextureDataMap->at("ramka1")->texture);

	this->itemsFirstArea = itemsFirstArea;
	this->itemsSecondArea = itemsSecondArea;

	getAllItemsVecSize();
	resizeAllItemsAreaVec();
	connectBothAreas();
	whichLinesOfEqOpen();

}

EquipmentAreas::~EquipmentAreas()
{
	disconectBothArea();

	for (auto elem : allItemsArea)
	{
		delete elem;
		elem = nullptr;
	}

	allItemsArea.clear();

	delete this->AllitemsArea;
}

void EquipmentAreas::update(const std::map<std::string, button*>& AllKeys)
{
	//Equipment management // moving items etc
	updateKeybinds(AllKeys);

	deleteItemIfAmmount_0();

	updatePositionsOfItems(AllKeys);

	this->itemTakenThisFrame = 0;
}

void EquipmentAreas::updateKeybinds(const std::map<std::string, button*>& AllKeys)
{
	getHoveredSquareStatus(AllKeys);
	
	if (this->isInWorkArea == true)
	{
		if (not(AllKeys.at("LShift")->isButtonPressed()) and AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and this->itemTakenThisFrame == 0)
			takingItemToTheHand(AllKeys);

		if (AllKeys.at("LShift")->isButtonPressed() and AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and this->itemTakenThisFrame == 0)
			searchForPlaceForWholeStack(AllKeys);

		if (AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed != nullptr and this->itemTakenThisFrame == 0)
			putOffItemFromHand(AllKeys);

		if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and this->itemTakenThisFrame == 0)
			takeHalfOfItemsToHand(AllKeys);

		if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and itemGrabbed != nullptr and this->itemTakenThisFrame == 0)
			placeOneMoreItem(AllKeys);
	}
	else if (this->itemGrabbed != nullptr)
	{
		if (AllKeys.at("LeftMouse")->oneSignalButtonPressed() and this->itemTakenThisFrame == 0)
			throwItem(this->itemGrabbed, true);

		if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and this->itemTakenThisFrame == 0)
			throwItem(this->itemGrabbed, false);
	}
}

void EquipmentAreas::whichLinesOfEqOpen()
{
	if (this->equipmentData->isEqOpened == false)
		this->linesToDraw = 1;
	else
		this->linesToDraw = AllitemsArea->at(0).size();
}

void EquipmentAreas::initRealPosOfItems_0_0()
{
	this->realPosOfItems_0_0 = this->equipmentData->FirstItemPositionEq;
}

void EquipmentAreas::getHoveredSquareStatus(const std::map<std::string, button*>& AllKeys)
{
	this->SquareHovered = 
	{	(int)((std::floor((float)(AllKeys.at("LeftMouse")->mousePosGet().x - (int)this->realPosOfItems_0_0.x) / (float)this->equipmentData->SizeOfItems))), //x
		(int)(std::floor((this->realPosOfItems_0_0.y - AllKeys.at("LeftMouse")->mousePosGet().y) / (float)this->equipmentData->SizeOfItems)) + 1			//y
	};

	checkIfIsInWorkArea();
}

void EquipmentAreas::checkIfIsInWorkArea()
{
	if (((this->SquareHovered.x >= 0 and this->SquareHovered.x < this->sizeOfArea.x) and (this->SquareHovered.y >= 0 and this->SquareHovered.y < this->sizeOfArea.y)) and AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).first==true)
		this->isInWorkArea = true;
	else this->isInWorkArea = false;
}

void EquipmentAreas::updatePositionsOfItems(const std::map<std::string, button*>& AllKeys)
{
	for (int y = 0; y < this->sizeOfArea.y; y++)
		for (int x = 0; x < this->sizeOfArea.x; x++)
			if (this->AllitemsArea->at(x).at(y).first == true)
				if (this->AllitemsArea->at(x).at(y).second->getItemPtr()!=nullptr)
				this->AllitemsArea->at(x).at(y).second->setPosition({ (x * this->equipmentData->SizeOfItems) + this->realPosOfItems_0_0.x,this->realPosOfItems_0_0.y - (y * this->equipmentData->SizeOfItems) });
	
	if (this->itemGrabbed!= nullptr)
		this->itemGrabbed->cameraSpriteOfItem->getSprite()->setPosition({AllKeys.at("LeftMouse")->mousePosGet().x - (float)(this->equipmentData->SizeOfItems / 2), AllKeys.at("LeftMouse")->mousePosGet().y - (float)(this->equipmentData->SizeOfItems / 2)});

}

void EquipmentAreas::deleteItemIfAmmount_0()
{
	for (int y = 0; y < this->sizeOfArea.y; y++)
		for (int x = 0; x < this->sizeOfArea.x; x++)
			if (this->AllitemsArea->at(x).at(y).first == true)
				if (this->AllitemsArea->at(x).at(y).second != nullptr)
					if (this->AllitemsArea->at(x).at(y).second->getItemPtr()!=nullptr)
						if (this->AllitemsArea->at(x).at(y).second->getItemPtr()->getNumberOfItems() == 0)
							this->AllitemsArea->at(x).at(y).second->setItemPtr(nullptr);

}

void EquipmentAreas::takingItemToTheHand(const std::map<std::string, button*>& AllKeys)
{
	std::swap(this->itemGrabbed, this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).second->getItemPtrAdress());
	this->itemTakenThisFrame = true;
}

void EquipmentAreas::putOffItemFromHand(const std::map<std::string, button*>& AllKeys)
{
	auto hoveredSquare = this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).second;

	if (hoveredSquare->getType() != typeOfItemArea::Pick)
	{
		if (hoveredSquare->getItemPtr() == nullptr or
			(hoveredSquare->getItemPtr() != nullptr and hoveredSquare->getItemPtr()->getItemID() != this->itemGrabbed->getItemID()))
		{
			std::swap(this->itemGrabbed, hoveredSquare->getItemPtrAdress());
			this->itemTakenThisFrame = true;
		}
		else if (hoveredSquare->getItemPtr()->getItemID() == this->itemGrabbed->getItemID())
			stackItems_TrueIfRestEqual0(&this->itemGrabbed, &hoveredSquare->getItemPtrAdress());
	}
}

void EquipmentAreas::takeOneItemToHand(const std::map<std::string, button*>& AllKeys)
{
	auto hoveredSquare = this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).second;

	if (hoveredSquare->getItemPtr() != nullptr)
	{
		if (hoveredSquare->getItemPtr()->getNumberOfItems() == 1)
			std::swap(this->itemGrabbed, hoveredSquare->getItemPtrAdress());
		else
		{
			this->itemGrabbed = factoryOfItems.createItem(hoveredSquare->getItemPtr()->getItemName());
			this->itemGrabbed->setNumberOfItems(1);
			hoveredSquare->getItemPtr()->substrFromThisItem(1);
		}
		this->itemTakenThisFrame = true;
	}
}

void EquipmentAreas::takeHalfOfItemsToHand(const std::map<std::string, button*>& AllKeys)
{
	auto hoveredSquare = this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).second;

	if (hoveredSquare->getItemPtr() != nullptr)
	{
		if (hoveredSquare->getItemPtr()->getNumberOfItems() == 1)
			std::swap(this->itemGrabbed, hoveredSquare->getItemPtrAdress());
		else
		{
			int tmpGrabbedNumberValue = hoveredSquare->getItemPtr()->getHalfOfItems();

			this->itemGrabbed = this->factoryOfItems.createItem(hoveredSquare->getItemPtr()->getItemName());
			
			this->itemGrabbed->setNumberOfItems(tmpGrabbedNumberValue);
			hoveredSquare->getItemPtr()->substrFromThisItem(tmpGrabbedNumberValue);
		}
		this->itemTakenThisFrame = true;
	}
}

void EquipmentAreas::placeOneMoreItem(const std::map<std::string, button*>& AllKeys)
{
	auto hoveredSquare = this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).second;

	if (hoveredSquare->getItemPtr() != nullptr)
	{
		if (hoveredSquare->getItemPtr()->getItemID() == itemGrabbed->getItemID())
			if (hoveredSquare->getItemPtr()->addOneItemReturn1IfNmbOfItemsFromTakenIs0(this->itemGrabbed))
				this->itemGrabbed=nullptr;
	}
	else
	{
		hoveredSquare->setItemPtr(this->factoryOfItems.createItem(this->itemGrabbed->getItemName()));
		hoveredSquare->getItemPtr()->setNumberOfItems(1);
		this->itemGrabbed->substrFromThisItem(1);
		if (this->itemGrabbed->isNullItemsInStack())
			this->itemGrabbed = nullptr;
	}
}

void EquipmentAreas::searchForPlaceForWholeStack(const std::map<std::string, button*>& AllKeys)
{
	if (this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y).second->getItemPtr() != nullptr)
		assignItemToAreaInEquipment(this->AllitemsArea->at(this->SquareHovered.x).at(this->SquareHovered.y), AllitemsArea, decideWhichOrder(this->SquareHovered.y));
}

std::vector<int> EquipmentAreas::makeVectorOfUsedRows()
{
	std::vector<int> tmpVec{};

	for (int i = 0; i < AllitemsArea->at(0).size(); i++)
		for (int j = 0; j < AllitemsArea->size(); j++)
			if (AllitemsArea->at(j).at(i).first == true)
				if (AllitemsArea->at(j).at(i).second->getType()==typeOfItemArea::PickAndPlace or AllitemsArea->at(j).at(i).second->getType() == typeOfItemArea::Place)
				{
					tmpVec.push_back(i);
					break;
				}
	return tmpVec;
}

std::vector<int> EquipmentAreas::shrinkVectorToOnlyPlacableRows(std::vector<int> vec, int hoveredRow)
{
	int howMuch{};

	for (auto& elem : vec)
		if (elem >= this->equipmentData->sizeOfEq.y)
			howMuch++;

	if (howMuch == 0)
	{
		switch (hoveredRow)
		{
		case 0:
			return { 2,1,0 };
		case 1:
			return { 0,2,1 };
		case 2:
			return { 0,2,1 };
		}
	}
	else if (hoveredRow < this->equipmentData->sizeOfEq.y)
	{
		return makeSortedFromHighestVecBiggerThatHoveredRow(vec, hoveredRow);  //make decisions based on which hovered clicked
	}
	else
		return { 0,2,1 };
		
	

	return std::vector<int>();
}

std::vector<int> EquipmentAreas::makeSortedFromHighestVecBiggerThatHoveredRow(std::vector<int> vec, int hoveredRow)
{
	std::vector<int> tmpVec{};

	for (auto elem : vec)
		if (elem >= this->equipmentData->sizeOfEq.y)
			tmpVec.push_back(elem);

	std::reverse(tmpVec.begin(),tmpVec.end());

	return tmpVec;
}

std::vector<int> EquipmentAreas::decideWhichOrder(int hoveredRow)
{
	return shrinkVectorToOnlyPlacableRows(makeVectorOfUsedRows(), hoveredRow);
}

void EquipmentAreas::stackItems_TrueIfRestEqual0(item** ItemFrom, item** ItemTo)
{
	if ((*ItemTo)->addItemsReturn1IfOverMax(*ItemFrom) == false)
	{
		delete *ItemFrom;
		*ItemFrom = nullptr;
	}
}

void EquipmentAreas::throwItem(item* item, bool isThrowdAllStack)
{
	if (isThrowdAllStack)
	{
		this->itemsOnTheGround->insertItemDroppedFromPlayer(item);
		this->itemGrabbed = nullptr;
	}
	else
	{
		this->itemsOnTheGround->insertItemDroppedFromPlayer(factoryOfItems.createItem(this->itemGrabbed->getItemName()));
		this->itemsOnTheGround->setNumberOfItemsLastInVector(1);
		this->itemGrabbed->substrFromThisItem(1);

		if (this->itemGrabbed->getNumberOfItems() == 0)
			this->itemGrabbed = nullptr;
	}
}



void EquipmentAreas::getAllItemsVecSize()
{
	this->sizeOfArea.x = itemsFirstArea->size();
	this->sizeOfArea.y = itemsFirstArea->at(0).size();
}

void EquipmentAreas::resizeAllItemsAreaVec()
{
	this->AllitemsArea->resize(sizeOfArea.x);
	for (auto& elem : *AllitemsArea)
		elem.resize(sizeOfArea.y);
}



bool EquipmentAreas::isAbleToCloseEq()
{
	if (itemGrabbed == nullptr) return true;
	return false;
}



void EquipmentAreas::render()
{
	//Render all items area and their background
	for (int y=0;y< this->linesToDraw;y++)
		for (int x=0;x< this->sizeOfArea.x;x++)
			if (this->AllitemsArea->at(x).at(y).first == true)
			{
				this->BackGroundSquare->setPosition((x * this->equipmentData->SizeOfItems)+this->realPosOfItems_0_0.x, this->realPosOfItems_0_0.y-(y * this->equipmentData->SizeOfItems));
				this->graphicsData->window->draw(*BackGroundSquare);

				if (y==0 and x == this->equipmentData->whichItemSelected)
				{
					this->BackGroundSquareUsed->setPosition((x * this->equipmentData->SizeOfItems) + this->realPosOfItems_0_0.x, this->realPosOfItems_0_0.y - (y * this->equipmentData->SizeOfItems));
					this->graphicsData->window->draw(*BackGroundSquareUsed);
				}

				if (this->AllitemsArea->at(x).at(y).second != nullptr)
					this->AllitemsArea->at(x).at(y).second->drawItem();
			}

	if (this->itemGrabbed != nullptr)
		this->itemGrabbed->render();
}

void EquipmentAreas::connectBothAreas()
{
	//First area
	for (int y = 0; y < this->equipmentData->sizeOfEq.y; y++)
		for (int x = 0; x < this->itemsFirstArea->size(); x++)
			this->AllitemsArea->at(x).at(y) = itemsFirstArea->at(x).at(y);

	//Second area
	if (this->itemsSecondArea != nullptr)
		for (int y = this->equipmentData->sizeOfEq.y; y < this->itemsSecondArea->at(0).size(); y++)
			for (int x = 0; x < this->itemsSecondArea->size(); x++)
				this->AllitemsArea->at(x).at(y) = itemsSecondArea->at(x).at(y);
}

void EquipmentAreas::disconectBothArea()
{
	//First area
	for (int y = 0; y < this->equipmentData->sizeOfEq.y; y++)
		for (int x = 0; x < this->sizeOfArea.x; x++)
			itemsFirstArea->at(x).at(y) = this->AllitemsArea->at(x).at(y);

	//Second area
	if (this->itemsSecondArea != nullptr)
		for (int y = this->equipmentData->sizeOfEq.y; y < itemsFirstArea->at(0).size(); y++)
			for (int x = 0; x < this->sizeOfArea.x; x++)
				itemsSecondArea->at(x).at(y) = AllitemsArea->at(x).at(y);
}

