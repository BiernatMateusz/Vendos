#include "CraftingManagement.h"

CraftingManagement::CraftingManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, 
	std::vector<std::vector<item*>>* Eq, std::vector<std::vector<item*>>* Crafting, item **CraftingSpot) 
	: EquipmentStorageArea({ 3,3 }, { 3,4 }, {}, { {7,5} })
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Eq = Eq;
	this->crafting = Crafting;
	this->craftingSpot = CraftingSpot;

	this->factoryOfItems.init(graphicsData, equipmentData);
	this->initCraftingPatterns();
	this->initPositionOfCraftedItem();

}

void CraftingManagement::update()
{
	for (auto& row : *crafting)
		for (auto& elem : row)
			if (elem != nullptr)
				; //todo

	makeStringFromTable();
	extractPatternToFindFromCrafting();
	if (checkIfAnyPatternMatches(this->stringMadeFromTable))
	{
		if (*this->craftingSpot != nullptr and (*this->craftingSpot)->itemID != idOfItemToMake)
		{
			delete *this->craftingSpot;
			*this->craftingSpot = nullptr;
		}
			
		if (*this->craftingSpot == nullptr)
		{
			*this->craftingSpot = factoryOfItems.creatorOfItemBasedOnID(idOfItemToMake, itemToMakeCount);
			(*this->craftingSpot)->cameraSprite->getSprite()->setPosition(positionOfCraftedItem);
		}
	}
	else 
	{
		delete *this->craftingSpot;
		*this->craftingSpot = nullptr;
	}

}

void CraftingManagement::render()
{
	if (*this->craftingSpot != nullptr and this->equipmentData->isEqOpened==1 and this->equipmentData->isChestOpened==0)
		(*this->craftingSpot)->render(); //its doubled - render in eq/chest render function and here
}

// deska to itemID=101
// {"NumberOfItemsToCraft_IDxIDxNxIDxID_ITEMID_COUNT"}
// string przedstawiajacy crafing z 4 desek => {"4_101x101xNx101x101_103_4"} crafting wymaga 4 itemów, które bêd¹ ustawione w kwadracie, N oznacza puste,
// 103 to ID itemka który siê zrobi a 4 to liczba itemków które powstan¹ 
// CZYTANIE ODBYWA SIE KOLUMNAMI OD LEWEJ
// decoding 

void CraftingManagement::initCraftingPatterns()
{
	this->craftingPatterns.push_back("1_101_102_4"); //jedno drewienko daje 4 patyki
	this->craftingPatterns.push_back("4_101x101xNx101x101_100_4");
}

void CraftingManagement::initPositionOfCraftedItem()
{
	this->positionOfCraftedItem.x = this->equipmentData->FirstItemPositionChest.x + (this->equipmentData->craftResultPos.x * this->equipmentData->SizeOfItems);
	this->positionOfCraftedItem.y = this->equipmentData->FirstItemPositionChest.y + this->equipmentData->craftResultPos.y * this->equipmentData->SizeOfItems;
}

std::string CraftingManagement::makeStringFromTable()
{
	this->stringMadeFromTable.clear();
	this->itemsOnCrafting = 0;

	for (auto& row : *crafting)
		for (auto& elem : row)
		{
			if (elem != nullptr)
			{
				this->stringMadeFromTable.append(std::to_string(elem->itemID));
				this->itemsOnCrafting++;
			}
			else
				this->stringMadeFromTable.append("N");
			this->stringMadeFromTable.append("x");
		}
	this->stringMadeFromTable.pop_back();
	this->stringMadeFromTable.insert(0, std::to_string(this->itemsOnCrafting));
	this->stringMadeFromTable.insert(1, "_");

	return this->stringMadeFromTable;
}

void CraftingManagement::extractPatternToFindFromCrafting()
{
	int positionOfFirstDigit{};
	int positionOfLastDigit{};
	
	for (int i = 0; i < stringMadeFromTable.size(); i++)
	{
		if (stringMadeFromTable[i] >= '0' and stringMadeFromTable[i] <= '9')
		{
			positionOfLastDigit = i;

			if (positionOfFirstDigit == 0)
				positionOfFirstDigit = i;

		}
	}

	for (int i = stringMadeFromTable.size() - 1; i >= 0; i--)
	{
		if (stringMadeFromTable[i] >= '0' and stringMadeFromTable[i] <= '9')
		{
			positionOfLastDigit = i;
			
			break;
		}
	}


	this->patternToFind.clear();
	this->patternToFind.insert(0, this->stringMadeFromTable, positionOfFirstDigit, positionOfLastDigit-positionOfFirstDigit+1);

}

std::string CraftingManagement::extractPatternToFindFromPaternsVec(std::string& stringToCheck)
{
	std::string tmpPatern{};
	int positionOfSecond_Sign{};
	int positionOfThird_Sign{};
	int Sign_Counter{};

	for (int i = 0; i < stringToCheck.size(); i++)
	{
		if (stringToCheck[i] == '_') Sign_Counter++;
			positionOfSecond_Sign++;

		if (Sign_Counter >= 2) break;
	}

	tmpPatern.insert(0, stringToCheck, 2, positionOfSecond_Sign-3); //2 is a 3rd member of string, thats why positionOfSecond_Sign-3 

	

	Sign_Counter = 0;
	tmpIDstring.clear();
	tmpItemCountString.clear();

	for (int i = positionOfSecond_Sign; i< stringToCheck.size() ; i++)
	{
		if (stringToCheck[i] == '_') Sign_Counter++;
			positionOfThird_Sign++;

		if (Sign_Counter >= 1) break;
	}

	tmpIDstring.insert(0, stringToCheck, positionOfSecond_Sign, positionOfThird_Sign-1);
	idOfItemToMake = std::stoi(tmpIDstring);

	tmpItemCountString.insert(0, stringToCheck, positionOfSecond_Sign+positionOfThird_Sign, stringToCheck.size() - positionOfSecond_Sign- positionOfThird_Sign);
	itemToMakeCount = std::stoi(tmpItemCountString);

	return tmpPatern;
}

bool CraftingManagement::checkIfAnyPatternMatches(std::string& stringToCheck)
{
	for (auto& elem : craftingPatterns)
		if (elem.at(0) == stringToCheck.at(0))
			if (extractPatternToFindFromPaternsVec(elem) == patternToFind)
				return true;
	return false;
}
