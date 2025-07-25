#include "tileConstructor.h"

void TileConstructor::init(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

std::string TileConstructor::creatorOfTileBasedOnHeldItemID(int itemID)
{
	switch (itemID)
	{
	case 105:
		return  "Skrzynia";
	case 106:
		return  "Furnace";
	}

	std::cout << "Brak itemu w klasie TileContructor.cpp, dodaj warunek w switchu!";
}
