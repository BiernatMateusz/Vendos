#ifndef ITEMFURNACE_H
#define ITEMFURNACE_H

#include "item.h"
#include "EquipmentStorageArea.h"
#include "Workstation.h"

class itemFurnace:
	public item,
	public EquipmentStorageArea
{
private:
public:
	itemFurnace(GraphicsData* graphicsData, EquipmentData* equipmentData);
	~itemFurnace();

	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	void render();

};

#endif // !ITEMFURNACE_H