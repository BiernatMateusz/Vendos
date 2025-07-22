#ifndef EQUIPMENTDATA_H
#define EQUIPMENTDATA_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <set>

enum class typeOfItemArea { PickAndPlace, Pick, Place };

class EquipmentStorageArea;

struct EquipmentData
{
	sf::Vector2f FirstItemPositionEq{};

	const int SizeOfItems = 86;
	const int Y_Offset_Bar_From_Border = 150;
	int whichItemSelected{};

	const sf::Vector2i sizeOfEq{ 9,3 };


	const int HeightOfEqPlusChest = 7; //eq->3 , chest->3 , spacing between->1
	const int OffsetHeightEqAndSpacing = HeightOfEqPlusChest - sizeOfEq.y; //7-3 = 4

	bool actionIsHappening{};
	bool needToUpdateTilesSpriteVec{};
	bool needToUpdateCameraAllSpr{ 1 };

	bool isEqOpened{};
	bool isChestOpened{};

	EquipmentStorageArea* openedWorkstation{};

	bool needToUpdateCrafting{};
	bool needToUpdateChest{};

	sf::Vector2f scaleOfThrownItems{ 0.4f,0.4f };

	std::set<int>IDofItemsWhichCantBeTaken{};

	const sf::Vector2f originOfItemsDropped{ 10,70 };
};

#endif // !EQUIPMENTDATA_H

