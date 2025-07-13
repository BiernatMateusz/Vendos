#ifndef ITEMFURNACE_H
#define ITEMFURNACE_H

#include "item.h"
#include "EquipmentStorageArea.h"
#include "Workstation.h"
#include "TilesOnMap.h"

class itemFurnace:
	public item,
	public EquipmentStorageArea,
	public TilesOnMap
{
private:
public:
	itemFurnace(GraphicsData* graphicsData, EquipmentData* equipmentData);
	itemFurnace(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i position2i, std::string NameOfTxt);
	~itemFurnace();

	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	void render();

};

#endif // !ITEMFURNACE_H