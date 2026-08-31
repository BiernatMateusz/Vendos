#include "Workstation.h"

Workstation::Workstation(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames name, std::initializer_list<int>order)
{

	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	
	initBackground(name);
	this->setOrderOfSearch(order);
}

void Workstation::initBackground(TextureNames name)
{
	this->background = std::make_unique<sf::Sprite>();
	this->background->setTexture(*this->graphicsData->TexturesData.at(name)->texture);
	this->background->setOrigin(0, this->graphicsData->TexturesData.at(name)->texture->getSize().y-this->equipmentData->SizeOfItems);
	this->background->setPosition({ this->equipmentData->FirstItemPositionEq.x- 30, this->equipmentData->FirstItemPositionEq.y+30 });

	this->BackGroundSquare.setTexture(*this->graphicsData->TexturesData.at(TextureNames::ramka)->texture);
	this->BackGroundSquareHighlighted.setTexture(*this->graphicsData->TexturesData.at(TextureNames::ramka1)->texture);
}

void Workstation::initWorkstation(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames name)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	
	initBackground(name);
}

void Workstation::resizeVector()
{
	this->slots.resize(this->size().x);
	for (auto& elem : slots)
	{
		elem.resize(this->size().y);

		/*for (auto& row : elem)
			row = std::make_pair(false, std::make_unique<item>());*/

	}
}

void Workstation::render()
{
	this->graphicsData->window->draw(*this->background);
}

void Workstation::renderBackground()
{
	this->graphicsData->window->draw(*this->background);
}

bool Workstation::isUsable(int x, int y) const
{
	return slots[x][y].isUsable();
}

//item* Workstation::getSlot(int x, int y)
//{
//	return items[x][y].second.get();
//}
//
//std::unique_ptr<item>& Workstation::slotPtr(int x, int y)
//{
//	return items[x][y].second;
//}

sf::Vector2i Workstation::size() const
{
	return sizeOfArea;
}

void Workstation::setUsable(int x, int y)
{
	this->slots[x][y].setUsable(true);
}

void Workstation::setType(int x, int y, typeOfSlot type)
{
	this->slots[x][y].setSlotType(type);
}

void Workstation::setSlot(int x, int y, std::unique_ptr<item>newItem)
{
	this->slots[x][y].setItemPtr(std::move(newItem));
}

//void Workstation::setSlot(int x, int y, std::unique_ptr<item>newItem)
//{
//	auto slot = std::make_unique<item>();
//	slot=(std::move(newItem));
//	this->items[x][y].second = std::move(slot);
//}

void Workstation::setFirstLayer_Y(int Layer)
{
	this->firstLayerFromDown = Layer;
}

const int& Workstation::getFirstLayer_Y() const
{
	return this->firstLayerFromDown;
}


ItemStorage* Workstation::getItemArea()
{
	return this;
}

const std::vector<int>& Workstation::getOrderOfSearch() const 
{
	return orderOfSearchForEmptySpace;
}

void Workstation::setOrderOfSearch(std::initializer_list<int> order) {
	orderOfSearchForEmptySpace = order;
}



bool Workstation::haveItems(ItemNames ItemName, int ammount)
{
	return false;
}

void Workstation::removeItem(ItemNames ItemName, int ammount)
{
	;
}

void Workstation::addItem(std::unique_ptr<item> Item)
{
	;
}

slot& Workstation::getSlotRef(int x, int y)
{
	return slots[x][y];
}

bool Workstation::transferItem(sf::Vector2i from, ItemStorage& target, sf::Vector2i to)
{
	/*auto* sourceItem = getSlot(from.x, from.y);
	auto* dstnItem = target.getSlot(to.x, to.y);*/

	//if (!sourceItem or !dstnItem) return false; 
	//uzupelnic
	
	
	return true;
}

void Workstation::drawBackground(int x, int y, bool highlighted)
{
	if (!highlighted)
	{
		this->BackGroundSquare.setPosition((x * this->equipmentData->SizeOfItems) + this->equipmentData->FirstItemPositionEq.x, this->equipmentData->FirstItemPositionEq.y - (y * this->equipmentData->SizeOfItems));
		this->graphicsData->window->draw(BackGroundSquare);
	}
	else
	{
		this->BackGroundSquareHighlighted.setPosition((x * this->equipmentData->SizeOfItems) + this->equipmentData->FirstItemPositionEq.x, this->equipmentData->FirstItemPositionEq.y - (y * this->equipmentData->SizeOfItems));
		this->graphicsData->window->draw(BackGroundSquareHighlighted);
	}
}

