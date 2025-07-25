#ifndef Structuresh
#define Structuresh

#include <string_view>
#include <optional>
#include "mouseButton.h"

#include "GraphicsData.h"
#include "EquipmentData.h"
#include "itemsData.h"

	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	//5 - hoed tiles - able to make croops here (no water)
	//6 - watered - able to make croops here and it will grow on here
	//7 - pure blockade
	//8 - chests - left->destroy right->open
	//9 - player


struct MovementData
{
	bool moved{};
	std::string direction{};
};




#endif