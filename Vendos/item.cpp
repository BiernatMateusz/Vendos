#include "item.h"

//CONSTRUCTORS
item::item(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;

	this->numberOfItems.setFont(this->graphicsData->font);
	this->numberOfItems.setFillColor(sf::Color::Black);
	this->numberOfItems.setStyle(sf::Text::Bold);
}

void item::updateAndRenderNumberOfItems()
{
	this->numberOfItems.setString(std::to_string(numberOfItemsInStack));
	this->numberOfItems.setCharacterSize(16);

	this->numberOfItems.setFont(this->graphicsData->font);

	this->numberOfItems.setPosition(
		this->cameraSpriteOfItem->getSprite()->getPosition().x + 80 - numberOfItems.getGlobalBounds().width,
		this->cameraSpriteOfItem->getSprite()->getPosition().y + 62);
	this->graphicsData->window->draw(this->numberOfItems);
}

const int& item::getBreakingDamage() const
{
	return {};
}

const ItemNames& item::getItemName() const
{
	return this->itemName;
}

const TypeOfAction& item::getTypeOfAction() const
{
	return this->typeOfAction;
}

const int& item::getItemID() const
{
	return this->itemID;
}

void item::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	;
}

void item::initItemBasicData(EquipmentData* equipmentData, TextureNames nameOfTxt, int ammount, TypeOfAction actionType)
{
	this->equipmentData = equipmentData;
	this->numberOfItemsInStack = ammount;
	this->typeOfAction = actionType;
	this->nameOfTxtOfItem = nameOfTxt;
}

void item::initItemGraphicsData()
{
	this->cameraSpriteOfItem = new CameraSprite;
	this->cameraSpriteOfItem->distance = this->graphicsData->TextureDataMapN->at(this->nameOfTxtOfItem)->offsetForCamera;
	this->cameraSpriteOfItem->setSpriteTexture(*this->graphicsData->TextureDataMapN->at(this->nameOfTxtOfItem)->texture);
}

void item::initItemIDandName(int ID, ItemNames itemName)
{
	this->itemID = ID;
	this->itemName = itemName;
}

item& item::operator=(const item& model)
{
	if (&model != this)
	{
		numberOfItems = model.numberOfItems;
		maxStack = model.maxStack;
		OverMax = model.OverMax;
		graphicsData = model.graphicsData;
		equipmentData = model.equipmentData;
		numberOfItemsInStack = 1; //model.numberOfItemsInStack 
		timeOfItemUsage = model.timeOfItemUsage;
		itemID = model.itemID;
		cameraSpriteOfItem = model.cameraSpriteOfItem;
	}
	return *this;
}

item::~item()
{
	delete this->cameraSpriteOfItem;
	this->cameraSpriteOfItem = nullptr;
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

bool item::hasTimePassed(float& timePassed)
{
	return (timePassed >=  this->timeOfItemUsage) ? true : false;
}

void item::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	updateKeybinds(dt, AllKeys);
}

void item::render()
{
	this->graphicsData->window->draw(*this->cameraSpriteOfItem->getSprite());

	updateAndRenderNumberOfItems();
}

bool item::isNullItemsInStack()
{
	return (this->numberOfItemsInStack==0)? true:false;
}

bool item::isMaxItemsInStack()
{
	return (this->numberOfItemsInStack == maxStack) ? true : false;
}
