#include "EquipmentStorageArea.h"


EquipmentStorageArea::EquipmentStorageArea()
{
	;
}

EquipmentStorageArea::EquipmentStorageArea(
	GraphicsData* graphicsData, 
	EquipmentData* equipmentData,
	sf::Vector2i SizeOfMainVec,
	sf::Vector2i FirstItemSquares,
	std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots,
	std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots,
	TextureNames name,
	std::initializer_list<int>order)
	: 
	Workstation(graphicsData, equipmentData, name, order)
{

	resizeVector();
	makeUsableSpots(SizeOfMainVec, FirstItemSquares, PlacesOfPickAndPlaceInRandomSpots, PlacesOfOnlyPickableSpots);
}


void EquipmentStorageArea::makeUsableSpots(sf::Vector2i SizeOfMainVec, sf::Vector2i FirstItemSquares, std::initializer_list<sf::Vector2i> PlacesOfPickAndPlaceInRandomSpots, std::initializer_list<sf::Vector2i> PlacesOfOnlyPickableSpots)
{
	setFirstLayer_Y(FirstItemSquares.y);

	for (int i = FirstItemSquares.x; i < SizeOfMainVec.x + FirstItemSquares.x; i++)
		for (int j = FirstItemSquares.y; j < SizeOfMainVec.y + FirstItemSquares.y; j++)
		{
			setUsable(i, j);
			setType(i, j, typeOfSlot::PickAndPlace);
		}

	for (auto& elem : PlacesOfPickAndPlaceInRandomSpots)
	{
		setUsable(elem.x, elem.y);
		setType(elem.x, elem.y, typeOfSlot::PickAndPlace);
	}

	for (auto& elem : PlacesOfOnlyPickableSpots)
	{
		setUsable(elem.x, elem.y);
		setType(elem.x, elem.y, typeOfSlot::Pick);
	}

}

void EquipmentStorageArea::updateActiveStorage(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	updatePositionOfItems();
}

void EquipmentStorageArea::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	;
}

void EquipmentStorageArea::updatePositionOfItems()
{
	for (int y = 0; y < size().y; y++)
		for (int x = 0; x < size().x; x++)
			if (this->isUsable(x, y))
				if (this->getSlotRef(x,y).get() != nullptr)
					this->getSlotRef(x, y).get()->setPositionInStorage({ (x * this->equipmentData->SizeOfItems) + this->equipmentData->FirstItemPositionEq.x,this->equipmentData->FirstItemPositionEq.y - (y * this->equipmentData->SizeOfItems) });
			 
}

void EquipmentStorageArea::render()
{
	for (int y = 0; y < size().y; ++y)
	{
		for (int x = 0; x < size().x; ++x)
		{
			if (!isUsable(x, y))
				continue;

			drawBackground(x, y, false);

			if (this->getSlotRef(x, y).get())
				this->getSlotRef(x, y).get()->drawItem();
		
		}
	}
}