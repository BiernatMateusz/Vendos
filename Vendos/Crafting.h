#ifndef CRAFTING_H
#define CRAFTING_H

#include "StructuresOfData.h"
#include "EquipmentAreas.h"

class Crafting:
	public EquipmentStorageArea
{
public:
	Crafting(GraphicsData* graphicsData, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround);
	~Crafting();
	void update(const float& dt, const std::map<std::string, button*>& AllKeys);


private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	ItemConstructor factoryOfItems;
	ThrownItems* itemsOnTheGround;

	//variables
	int itemsOnCrafting{};
	std::string stringMadeFromTable{};
	std::string patternToFind{};
	std::vector<std::string>craftingPatterns{};

	std::string tmpIDstring{};
	std::string tmpItemCountString{};
	int idOfItemToMake{};
	int itemToMakeCount{};

	sf::Vector2i craftPos{};

	int ResultItemCountFromPrevCycle{};

	//functions
	void initCraftingPatterns();
	void initPositionOfCraftedItem();

	std::string makeStringFromTable();
	void extractPatternToFindFromCrafting();
	bool checkIfAnyPatternMatches(std::string& stringToCheck);
	std::string extractPatternToFindFromPaternsVec(std::string& stringToCheck);
	void changeItemNumbersIfResultNmbChanged();

};

#endif