#ifndef TILECONSTRUCTOR_H
#define TILECONSTRUCTOR_H

#include "StructuresOfData.h"
#include "TilesOnMap.h"

class TileConstructor
{
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
public:
	void init(GraphicsData* graphicsData, EquipmentData* equipmentData);
	std::string creatorOfTileBasedOnHeldItemID(int itemID);
};

#endif 