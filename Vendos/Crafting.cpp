#include "Crafting.h"

Crafting::Crafting(GraphicsData* graphicsData, EquipmentData* equipmentData, ThrownItems* ItemsOnTheGround)
	: EquipmentStorageArea(graphicsData, equipmentData, { 3,3 }, { 3,4 }, {}, { {7,5} }, "BackgroundCrafting")
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->itemsOnTheGround = ItemsOnTheGround;

	this->factoryOfItems.init(graphicsData, equipmentData);
	this->initCraftingPatterns();
	this->initPositionOfCraftedItem();
}

Crafting::~Crafting()
{
	
	for (int i=0;i< this->getItemsArea()->size();i++)
		for (int j=0;j< this->getItemsArea()->at(0).size();j++)
			if (this->getItemsArea()->at(i).at(j).second->getItemPtr() != nullptr)
			{
				this->itemsOnTheGround->insertItemDroppedFromPlayer(this->getItemsArea()->at(i).at(j).second->getItemPtr());
				this->getItemsArea()->at(i).at(j).second->setItemPtr(nullptr);
			}
}

void Crafting::updateStorageArea(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	changeItemNumbersIfResultNmbChanged();

	makeStringFromTable();
	extractPatternToFindFromCrafting();

	if (checkIfAnyPatternMatches(this->stringMadeFromTable))
	{
		if (this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr() != nullptr and this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr()->getItemID() != idOfItemToMake)
			this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->setItemPtr(nullptr);

		if (this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr() == nullptr)
			this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->setItemPtr(factoryOfItems.createItem(idOfItemToMake, itemToMakeCount));
	}
	else
		this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->setItemPtr(nullptr);


	if (this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr() != nullptr)
		this->ResultItemCountFromPrevCycle = this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr()->getNumberOfItems();
	else
		this->ResultItemCountFromPrevCycle = 0;

	
}

void Crafting::initCraftingPatterns()
{
	//"8_101x101x101x101xNx101x101x101x101_105_1"//
	// 8 - liczba itemów bioracych udzial w craftingu 
	// 101x101... id itemów 
	// xNx... pusty slot pomiedzy itemami
	// Kolejnosc wypelniania ID -> Od góry od lewej najpierw wiersz do pe³na potem nastepna kolumna... 

	this->craftingPatterns.push_back("1_101_102_4"); //PATYK
	this->craftingPatterns.push_back("4_101x101xNx101x101_100_4"); 
	this->craftingPatterns.push_back("8_101x101x101x101xNx101x101x101x101_105_1"); // CHEST
	this->craftingPatterns.push_back("8_100x100x100x100xNx100x100x100x100_106_1"); // FURNACE

}

void Crafting::initPositionOfCraftedItem()
{
	this->craftPos = { 7,5 };
}

std::string Crafting::makeStringFromTable()
{
	//	{ 3, 3 }, { 3,4 }

	this->stringMadeFromTable.clear();
	this->itemsOnCrafting = 0;

	for (int i=3;i<3+3;i++)
		for (int j = 4; j < 4 + 3; j++)
		{
			if (this->getItemsArea()->at(i).at(j).second->getItemPtr() != nullptr)
			{
				this->stringMadeFromTable.append(std::to_string(this->getItemsArea()->at(i).at(j).second->getItemPtr()->getItemID()));
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

void Crafting::extractPatternToFindFromCrafting()
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
	this->patternToFind.insert(0, this->stringMadeFromTable, positionOfFirstDigit, positionOfLastDigit - positionOfFirstDigit + 1);
}

bool Crafting::checkIfAnyPatternMatches(std::string& stringToCheck)
{
	for (auto& elem : this->craftingPatterns)
	{
		if (elem.at(0) == stringToCheck.at(0))
			if (extractPatternToFindFromPaternsVec(elem) == patternToFind)
			{
				
				return true;
			}
	}
	return false;
}

std::string Crafting::extractPatternToFindFromPaternsVec(std::string& stringToCheck)
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

	tmpPatern.insert(0, stringToCheck, 2, positionOfSecond_Sign - 3); //2 is a 3rd member of string, thats why positionOfSecond_Sign-3 



	Sign_Counter = 0;
	tmpIDstring.clear();
	tmpItemCountString.clear();

	for (int i = positionOfSecond_Sign; i < stringToCheck.size(); i++)
	{
		if (stringToCheck[i] == '_') Sign_Counter++;
		positionOfThird_Sign++;

		if (Sign_Counter >= 1) break;
	}

	tmpIDstring.insert(0, stringToCheck, positionOfSecond_Sign, positionOfThird_Sign - 1);
	idOfItemToMake = std::stoi(tmpIDstring);

	tmpItemCountString.insert(0, stringToCheck, positionOfSecond_Sign + positionOfThird_Sign, stringToCheck.size() - positionOfSecond_Sign - positionOfThird_Sign);
	itemToMakeCount = std::stoi(tmpItemCountString);

	return tmpPatern;
}

void Crafting::changeItemNumbersIfResultNmbChanged()
{
	int tmpItemCount{};

	if (this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr() == nullptr)
		tmpItemCount = 0;
	else
		tmpItemCount = this->getItemsArea()->at(craftPos.x).at(craftPos.y).second->getItemPtr()->getNumberOfItems();


	if (tmpItemCount != this->ResultItemCountFromPrevCycle)
		for (auto& elem : *this->getItemsArea())
			for (auto& row : elem)
				if (row.second->getItemPtr() != nullptr)
				{
					row.second->getItemPtr()->substrFromThisItem(1);
					if (row.second->getItemPtr()->getNumberOfItems() == 0)
						row.second->setItemPtr(nullptr);
				}
}
