#include "Workstation.h"

Workstation::Workstation(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string nameOfTxt)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->backgroundItems = new std::vector<sf::Sprite*>;

	initBackground(nameOfTxt);
}

Workstation::~Workstation()
{
	if (this->background != nullptr)
		delete this->background;
	if (this->backgroundItems != nullptr)
		delete this->backgroundItems;
}

void Workstation::initBackground(std::string name)
{
	this->background = new sf::Sprite;
	this->background->setTexture(*this->graphicsData->TextureDataMap->at(name)->texture);
	this->background->setOrigin(0, this->graphicsData->TextureDataMap->at(name)->texture->getSize().y-this->equipmentData->SizeOfItems);
	this->background->setPosition(this->equipmentData->FirstItemPositionEq);
}

void Workstation::render()
{
	this->graphicsData->window->draw(*this->background);
}
