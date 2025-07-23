#ifndef CRAFTMANAGEMENT_H
#define CRAFTMANAGEMENT_H

#include "StructuresOfData.h"
#include "ThrownItems.h"
#include "ItemConstructor.h"
#include "EquipmentAreas.h"


class CraftingManagement :
	public EquipmentStorageArea
{
public:
	CraftingManagement(
		GraphicsData* graphicsData,
		EquipmentData* equipmentData,
		std::vector<std::vector<item*>>* Eq,
		std::vector<std::vector<item*>>* Crafting,
		item **CraftingSpot);

	

	void update();
	void render();
private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	std::vector<std::vector<item*>>* Eq{};
	std::vector<std::vector<item*>>* crafting{};

	item** craftingSpot{};
	sf::Vector2f positionOfCraftedItem{};

	ItemConstructor factoryOfItems;

	std::vector<std::string>craftingPatterns{};

	void initCraftingPatterns();
	void initPositionOfCraftedItem();

	int maxNumberOfItemsCraftPossible{}; //from items that are put in craft area

	int itemsOnCrafting{};
	std::string stringMadeFromTable{};
	std::string patternToFind{};

	std::string tmpIDstring{};
	std::string tmpItemCountString{};
	int idOfItemToMake{};
	int itemToMakeCount{};

	std::string makeStringFromTable();
	void extractPatternToFindFromCrafting();
	std::string extractPatternToFindFromPaternsVec(std::string& stringToCheck);
	bool checkIfAnyPatternMatches(std::string& stringToCheck);

protected:

};

// deska to itemID=101
// {"NumberOfItemsToCraft_IDxIDxNxIDxID_ITEMID_COUNT"}
// string przedstawiajacy crafing z 4 desek => {"4_101x101xNx101x101_103_4"} crafting wymaga 4 itemów, które bêd¹ ustawione w kwadracie, N oznacza puste,
// 103 to ID itemka który siê zrobi a 4 to liczba itemków które powstan¹ 
// CZYTANIE ODBYWA SIE KOLUMNAMI OD LEWEJ
// decoding 


#endif