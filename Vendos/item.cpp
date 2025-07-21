#include "item.h"

//CONSTRUCTORS
item::item(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;

	this->cameraSprite = new CameraSprite;

	this->font.loadFromFile("Font/Rinnero.ttf");
	this->numberOfItems.setFont(font);
	this->numberOfItems.setFillColor(sf::Color::Black);
	this->numberOfItems.setStyle(sf::Text::Bold);
}

item::item(GraphicsData* graphicsData, TypeOfAction actionType) : item(graphicsData)
{
	this->typeOfAction = actionType;
}

item::item(GraphicsData* graphicsData, bool empty)
	:item(graphicsData)
{
	this->cameraSprite = new CameraSprite(true);
}

item::item(GraphicsData* graphicsData, EquipmentData* equipmentData, const std::string& name, int ammount, TypeOfAction actionType)
	:
	item(graphicsData)
{
	this->equipmentData = equipmentData;
	this->numberOfItemsInStack = ammount;
	initGraphics(name);
	this->typeOfAction = actionType;
}

item::item(GraphicsData* graphicsData, EquipmentData* equipmentData, TypeOfTool typeOfTool, QualityOfTool qualityOfTool)
	:
	item(graphicsData)
{
	this->equipmentData = equipmentData;

	this->nameOfTxt = makeNameTexture(typeOfTool, qualityOfTool);

	initGraphics(this->nameOfTxt);
}

void item::updateAndRenderNumberOfItems()
{
	this->numberOfItems.setString(std::to_string(numberOfItemsInStack));
	this->numberOfItems.setCharacterSize(16);

	this->numberOfItems.setFont(font);

	this->numberOfItems.setPosition(
		this->itemSprite.getPosition().x + 80 - numberOfItems.getGlobalBounds().width,
		this->itemSprite.getPosition().y + 62);
	this->graphicsData->window->draw(this->numberOfItems);
}

const int& item::getBreakingDamage() const
{
	return {};
}

void item::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;
}

void item::initPositon(sf::Vector2i xyOfvec, sf::Vector2f FirstItemPos, const int& itemSize, int OffsetYPositioning)
{
	this->itemSprite.setPosition(FirstItemPos.x + xyOfvec.x*itemSize, FirstItemPos.y- (-xyOfvec.y+2) * itemSize - OffsetYPositioning*itemSize);
}

void item::initItemID(int ID)
{
	this->itemID = ID;
}

void item::initGraphics(const std::string &name)
{
	this->cameraSprite->sprite = &itemSprite;
	this->cameraSprite->distance = this->graphicsData->TextureDataMap->at(name)->offsetForCamera;
	this->itemSprite.setTexture(*this->graphicsData->TexturesMap->at(name));
	this->itemID = this->graphicsData->TextureDataMap->at(name)->itemID;
}



std::string item::makeNameTexture(TypeOfTool typeOfTool, QualityOfTool qualityOfTool)
{
	return StrQuality.at(static_cast<int>(qualityOfTool))+StrType.at(static_cast<int>(typeOfTool));
}



item& item::operator=(const item& model)
{
	if (&model != this)
	{
		font =model.font;
		numberOfItems = model.numberOfItems;
		maxStack = model.maxStack;
		OverMax = model.OverMax;
		graphicsData = model.graphicsData;
		equipmentData = model.equipmentData;
		numberOfItemsInStack = 1; //model.numberOfItemsInStack 
		nameOfTxt = model.nameOfTxt;
		timeOfItemUsage = model.timeOfItemUsage;
		nameOfTxt = model.nameOfTxt;
		itemID = model.itemID;
		itemSprite = model.itemSprite;
		cameraSprite = model.cameraSprite;
		cameraSprite->sprite = &itemSprite;
	}
	return *this;
}

void item::changeNumberOfItems(int newNumberOfItems)
{
	this->numberOfItemsInStack = newNumberOfItems;
}

int item::getNumberOfItems()
{
	return this->numberOfItemsInStack;
}

bool item::isNumberOfItemsEven()
{
	return not(this->numberOfItemsInStack%2);
}

int item::getHalfOfItems()
{
	if (isNumberOfItemsEven())
		return this->numberOfItemsInStack / 2;
	else
		return (this->numberOfItemsInStack + 1) / 2;
}

int item::getNumberMax()
{
	return this->maxStack;
}

bool item::addItemsReturn1IfOverMax(item* itemPtr)
{
	this->OverMax = 0;
	
	if ((this->numberOfItemsInStack + itemPtr->numberOfItemsInStack) > maxStack)
	{
		OverMax = true;

		itemPtr->numberOfItemsInStack = itemPtr->numberOfItemsInStack + this->numberOfItemsInStack - maxStack;
		this->numberOfItemsInStack = maxStack;
	}
	else
		this->numberOfItemsInStack += itemPtr->numberOfItemsInStack;

	return OverMax;
}

bool item::addItemsReturn1IfOverMax_DontAddWhenOverMax(item* itemPtr)
{
	this->OverMax = 0;

	if ((this->numberOfItemsInStack + itemPtr->numberOfItemsInStack) > maxStack)
		OverMax = true;
	else
		this->numberOfItemsInStack += itemPtr->numberOfItemsInStack;

	return OverMax;
}

bool item::addOneItemReturn1IfNmbOfItemsFromTakenIs0(item* itemPtr)
{
	this->OverMax = 0;

	if ((this->numberOfItemsInStack + 1) <= maxStack)
	{
		this->numberOfItemsInStack += 1;
		itemPtr->substrFromThisItem(1);
	}
	
	if (itemPtr->getNumberOfItems() == 0)
		OverMax = 1;

	return OverMax;
}

void item::substrFromThisItem(int value)
{
	this->numberOfItemsInStack -= value;
}

void item::addToThisItem(int value)
{
	this->numberOfItemsInStack += value;
}

void item::setNumberOfItems(int value)
{
	this->numberOfItemsInStack = value;
}

bool item::checkIfAddable()
{
	if (this->itemID >= 100)
		if (this->numberOfItemsInStack < this->maxStack)
			return true;
	return false;
}

void item::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	updateKeybinds(dt, AllKeys);
}

void item::render()
{
	this->graphicsData->window->draw(this->itemSprite);
	//this->Window->draw(this->itemSprite);
	updateAndRenderNumberOfItems();
}


std::vector<tileType>* item::getTypeOfBlocksToInterract()
{
	return &TypeOfBlockToInterract;
}

bool item::getIsCreatingOnEmptyTilePossible()
{
	return this->isCreatingOnEmptyTilePossible;
}

TypeOfAction item::getTypeOfAction()
{
	return this->typeOfAction;
}

float item::getTimeOfActionOfItemUsage()
{
	return this->timeOfItemUsage;
}

std::string item::getReplaceTxtName()
{
	return this->nameOfTxtWhileReplacing;
}
