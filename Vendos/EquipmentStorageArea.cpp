#include "EquipmentStorageArea.h"
#include "itemAndItsPosition.h"

EquipmentStorageArea::EquipmentStorageArea()
{
	this->items = new std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>;
}

EquipmentStorageArea::EquipmentStorageArea(
	GraphicsData* graphicsData, 
	EquipmentData* equipmentData,
	sf::Vector2i SizeOfMainVec,
	sf::Vector2i FirstItemSquares,
	std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
	std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots,
	TextureNames name)
	: 
	Workstation(graphicsData, equipmentData, name)
{
	this->items = new std::vector < std::vector<std::pair <bool, itemAndItsPosition*>>>;
	resizeVector();
	makeUsableSpots(SizeOfMainVec, FirstItemSquares, PlacesOfPickAndPlaceInRandomSpots, PlacesOfOnlyPickableSpots);
	setItemTypes(PlacesOfOnlyPickableSpots, typeOfItemArea::Pick);
}

EquipmentStorageArea::~EquipmentStorageArea()
{
	for (auto& row : *items)
		for (auto& elem : row)
			delete elem.second;
	items->clear();
}

void EquipmentStorageArea::resizeVector()
{
	this->items->resize(this->sizeOfArea.x);
	for (auto &elem : *items)
	{
		elem.resize(this->sizeOfArea.y);
		
		for (auto& row : elem)
			row = std::make_pair(false, new itemAndItsPosition());

	}
}

void EquipmentStorageArea::makeUsableSpots(sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots)
{
	for (int i=FirstItemSquares.x; i<SizeOfMainVec.x+ FirstItemSquares.x; i++)
		for (int j = FirstItemSquares.y; j < SizeOfMainVec.y+ FirstItemSquares.y; j++)
			items->at(i).at(j).first = true;


	for (auto& elem : PlacesOfPickAndPlaceInRandomSpots)
		items->at(elem.x).at(elem.y).first = true;

	for (auto& elem : PlacesOfOnlyPickableSpots)
		items->at(elem.x).at(elem.y).first = true;

}

void EquipmentStorageArea::setItemTypes(std::initializer_list<sf::Vector2i> Places, typeOfItemArea itemType)
{
	for (auto& elem : Places)
		items->at(elem.x).at(elem.y).second->setType(itemType);
}

std::vector<std::vector<std::pair<bool, itemAndItsPosition*>>>* EquipmentStorageArea::getItemsArea()
{
	return this->items;
}
