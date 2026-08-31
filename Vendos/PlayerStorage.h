#ifndef PLAYER_STORAGE_H
#define PLAYER_STORAGE_H

#include "StructuresOfData.h"
#include "EquipmentAreas.h"

class PlayerStorage :
	public EquipmentStorageArea
{
public:
	PlayerStorage(
		GraphicsData* graphicsData,
		EquipmentData* equipmentData);

	void renderBottomBar();
private:
	void fillStartingPlayerStorage();
};

#endif // !PLAYER_STORAGE_H