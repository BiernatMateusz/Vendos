#include "CraftingItems.h"


CraftingItems::CraftingItems(GraphicsData* graphicsData, EquipmentData* equipmentData, EquipmentStorageArea* playerStorage,
	EquipmentAreas* eqAreas) : EquipmentStorageArea(
	graphicsData,
	equipmentData,
	{ 1, 5 },
	{ 7, 4 },
	{},
	{ {7,4}, {7,5}, {7,6}, {7,7}, {7,8} },
	TextureNames::BackgroundCrafting,
	{ 8,7,6,5,4 }
), playerStorage(playerStorage), eqAreas(eqAreas)
{
	factoryOfItems.init(graphicsData, equipmentData);
	initRecipesVecNew();
	calculateMaxOffsetBothDirections();
}

void CraftingItems::updateActiveStorage(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
		updateKeybinds(AllKeys);
		updateRecipesPos();
		updateRecipesQueuePos();
}

void CraftingItems::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	if (!this->RecipesQueue.empty())
		updateCrafting(dt);
}

void CraftingItems::renderStorage()
{
	for (int i = this->showedItemStart, j = i + 5; (i - this->showedItemStart) < RecipesVecNew.size() && (i - this->showedItemStart) < 5; i++)
		RecipesVecNew.at(i).Render();

	for (auto& elem : RecipesQueue)
		elem.RenderItemCreated(this->graphicsData->window);
}

void CraftingItems::calculateMaxOffsetBothDirections()
{
	if (this->RecipesVecNew.size() <= 5)
		this->maxPossibleScrollOffset = (5 - this->RecipesVecNew.size()) * this->equipmentData->SizeOfItems;
	else
		this->maxPossibleScrollOffset = 0;

	if (this->RecipesVecNew.size() <= 5)
		this->minPossibleScrollOffset = 0;
	else
		this->minPossibleScrollOffset = ((this->RecipesVecNew.size() - 5) * this->equipmentData->SizeOfItems) * (-1);
}

void CraftingItems::updateCrafting(const float& dt)
{
	for (int i = 0; i < RecipesQueue.size(); i++)
	{
		auto RecStatus = RecipesQueue.at(i).status;
		if (RecStatus != RecipeStatus::Done and RecStatus != RecipeStatus::DoneMovedToStorage and RecStatus != RecipeStatus::DoneTaken)
		{
			checkIfCraftingPossible(i);
			RecipesQueue.at(i).update(dt);
			break;
		}
		else if (RecStatus == RecipeStatus::Done)
		{
			moveRecipeResultToStorage(i);
			takeItemsFromStorage(i);
			RecipesQueue.at(i).setStatus(RecipeStatus::DoneMovedToStorage);
		}
	}

	setDoneTakenStatus();
	clearQueueFromTaken();
}



void CraftingItems::updateRecipesPos()
{
	for (int i = 0; i < RecipesVecNew.size(); i++)
		RecipesVecNew.at(i).setPos(
			{ this->equipmentData->FirstItemPositionEq.x,
			this->equipmentData->FirstItemPositionEq.y - (8 * this->equipmentData->SizeOfItems) + (i * this->equipmentData->SizeOfItems) + this->scrolledOffset },
			this->equipmentData->SizeOfItems
		);
}

void CraftingItems::updateRecipesQueuePos()
{
	for (int i = 0; i < RecipesQueue.size(); i++)
		if (RecipesQueue.at(i).status != RecipeStatus::DoneMovedToStorage and RecipesQueue.at(i).status != RecipeStatus::DoneTaken)
		{
			RecipesQueue.at(i).setPosItemCreated(
				{ this->equipmentData->FirstItemPositionEq.x,
				this->equipmentData->FirstItemPositionEq.y - (8 * this->equipmentData->SizeOfItems) + (i * this->equipmentData->SizeOfItems) },
				this->equipmentData->SizeOfItems
			);
		}
}

RecipeStatus CraftingItems::getStatus(Recipe rec)
{
	return rec.status;
}

void CraftingItems::getHoveredSquareStatus(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	this->RecipeHovered =
	{ (int)((std::floor((float)(AllKeys.at(inputAction::LMouse)->mousePosGet().x - (int)this->equipmentData->FirstItemPositionEq.x) / (float)this->equipmentData->SizeOfItems))), //x
		(int)(std::floor((AllKeys.at(inputAction::LMouse)->mousePosGet().y - this->equipmentData->FirstItemPositionEq.y + (8 * this->equipmentData->SizeOfItems)) / (float)this->equipmentData->SizeOfItems))		//y
	};

	this->RecipeHovered.y += this->showedItemStart;
}

void CraftingItems::updateScroll(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	if (this->RecipesVecNew.size() >= 5)
	{
		if (this->scrolledOffset < this->maxPossibleScrollOffset)
			if (AllKeys.at(inputAction::Scroll)->isWheelScrolledUp())
				this->scrolledOffset += this->equipmentData->SizeOfItems;
		if (this->scrolledOffset > this->minPossibleScrollOffset)
			if (AllKeys.at(inputAction::Scroll)->isWheelScrolledDown())
				this->scrolledOffset -= this->equipmentData->SizeOfItems;
	}
	else this->scrolledOffset = 0;

	if (this->RecipesVecNew.size() >= 5)
		this->showedItemStart = (this->scrolledOffset / this->equipmentData->SizeOfItems) * -1;
	else this->showedItemStart = 0;
}

void CraftingItems::updateKeybinds(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	getHoveredSquareStatus(AllKeys);

	updateScroll(AllKeys);

	if (AllKeys.at(inputAction::LMouse)->oneSignalButtonPressed() and RecipesQueue.size() < 5 and isCursorInCraftingArea())
		addRecipeToQueue();

	if (AllKeys.at(inputAction::RMouse)->oneSignalButtonPressed() and RecipesQueue.size() <= 5 and isCrusorInResultArea())
		deleteRecipeFromQueue(RecipeHovered.y);
	

}

Recipe CraftingItems::copyRecipe(const Recipe& OriginalRecipe)
{
	std::vector<std::unique_ptr<item>> newIngredients;

	for (int i = 0; i < OriginalRecipe.ingredientTypes.size(); i++)
		newIngredients.push_back(factoryOfItems.createItem(OriginalRecipe.ingredientTypes.at(i), OriginalRecipe.ingredientQuantity.at(i)));

	auto newResult = factoryOfItems.createItem(OriginalRecipe.resultType, OriginalRecipe.resultQuantity);

	return Recipe(
		OriginalRecipe.ID,
		OriginalRecipe.craftTime,
		std::move(newResult),
		std::move(newIngredients),
		OriginalRecipe.resultType,
		OriginalRecipe.ingredientTypes,
		OriginalRecipe.resultQuantity,
		OriginalRecipe.ingredientQuantity,
		OriginalRecipe.status,
		OriginalRecipe.graphicsData
	);
}

void CraftingItems::addRecipeToQueue()
{
	//CHECK IF THERE IS ENOUGH ITEMS TO TAKE FOR CRAFTING
	this->RecipesQueue.push_back(copyRecipe(this->RecipesVecNew.at(RecipeHovered.y)));
}

void CraftingItems::deleteRecipeFromQueue(int numberOfRecipeHovered)
{
	if (RecipesQueue.at(numberOfRecipeHovered).status==RecipeStatus::InQueue or 
		RecipesQueue.at(numberOfRecipeHovered).status == RecipeStatus::InProgress or 
		RecipesQueue.at(numberOfRecipeHovered).status == RecipeStatus::NoIngredients)
			RecipesQueue.erase(RecipesQueue.begin()+ numberOfRecipeHovered);
}

bool CraftingItems::isCursorInCraftingArea()
{
	if (this->RecipeHovered.x == 5 and
		this->RecipeHovered.y - this->showedItemStart >= 0 and
		this->RecipeHovered.y - this->showedItemStart < 5)
		return true;

	return false;
}

bool CraftingItems::isCrusorInResultArea()
{
	if (this->RecipeHovered.x == 7 and
		this->RecipeHovered.y - this->showedItemStart >= 0 and
		this->RecipeHovered.y - this->showedItemStart < RecipesQueue.size())
		return true;

	return false;
}

void CraftingItems::checkIfCraftingPossible(int numberOfRecipeInQue)
{
	auto& recipe = RecipesQueue.at(numberOfRecipeInQue);
	if (checkIngredients(numberOfRecipeInQue)) 
	{ 
		if (recipe.status!=RecipeStatus::Done)
			recipe.setStatus(RecipeStatus::InProgress);
	}
	else 
	{ 
		recipe.setStatus(RecipeStatus::NoIngredients);
		recipe.resetProgress();
	}
}

bool CraftingItems::checkIngredients(int numberOfRecipeInQue)
{
	bool possible = true;

	auto& recipe = RecipesQueue.at(numberOfRecipeInQue);


	for (int i = 0; i < recipe.ingredientTypes.size(); i++)
	{
		if (!eqAreas->isThereItem(
			*playerStorage,
			recipe.ingredientTypes.at(i),
			recipe.ingredientQuantity.at(i)))
		{
			possible = false;
			break;
		}
	}

	return possible;
}

void CraftingItems::setDoneTakenStatus()
{
	for (int i = 0; i < RecipesQueue.size(); i++)
		if (RecipesQueue.at(i).status == RecipeStatus::DoneMovedToStorage)
			if (this->getSlotRef(recipePositions.at(i).x, recipePositions.at(i).y).get() == nullptr)
				RecipesQueue.at(i).status = RecipeStatus::DoneTaken;
}

void CraftingItems::clearQueueFromTaken()
{
	for (auto it = RecipesQueue.begin(); it != RecipesQueue.end(); )
	{
		if (it->status == RecipeStatus::DoneTaken)
			it = RecipesQueue.erase(it);
		else
			++it;
	}
}

void CraftingItems::moveRecipeResultToStorage(int recipeSlot)
{
	this->setSlot(recipePositions.at(recipeSlot).x, recipePositions.at(recipeSlot).y, std::move(RecipesQueue.at(recipeSlot).itemCreated));
}

void CraftingItems::takeItemsFromStorage(int recipeSlot)
{
	auto& recipe = RecipesQueue.at(recipeSlot);

	for (int i = 0; i < recipe.ingredientTypes.size(); i++)
	{
		eqAreas->takeItems(
			*playerStorage,
			recipe.ingredientTypes.at(i),
			recipe.ingredientQuantity.at(i));
	}
}


void CraftingItems::initRecipesVecNew()
{
	//1 ITEM
	{
		std::vector<std::unique_ptr<item>> ingredients;
		std::vector<ItemNames> ingredientTypes;
		std::vector<int> ingredientQuantity;

		ingredients.push_back(factoryOfItems.createItem(ItemNames::WoodEq, 15));

		ingredientTypes.push_back(ItemNames::WoodEq);

		ingredientQuantity.push_back(15);

		auto resultItem = factoryOfItems.createItem(ItemNames::WoodEq, 1);

		this->RecipesVecNew.emplace_back(
			1,
			3.f,
			std::move(resultItem),
			std::move(ingredients),
			ItemNames::WoodEq,
			ingredientTypes,
			1,
			ingredientQuantity,
			RecipeStatus::InQueue,
			graphicsData
		);
	}

	//2 ITEM
	{
		std::vector<std::unique_ptr<item>> ingredients;
		std::vector<ItemNames> ingredientTypes;
		std::vector<int> ingredientQuantity;

		ingredients.push_back(factoryOfItems.createItem(ItemNames::WoodEq, 5));
		ingredients.push_back(factoryOfItems.createItem(ItemNames::Patyk, 5));

		ingredientTypes.push_back(ItemNames::WoodEq);
		ingredientTypes.push_back(ItemNames::Patyk);

		ingredientQuantity.push_back(5);
		ingredientQuantity.push_back(5);

		auto resultItem = factoryOfItems.createItem(ItemNames::StoneEq, 2);

		this->RecipesVecNew.emplace_back(
			2,
			3.f,
			std::move(resultItem),
			std::move(ingredients),
			ItemNames::StoneEq,
			ingredientTypes,
			2,
			ingredientQuantity,
			RecipeStatus::InQueue,
			graphicsData
		);
	}

	//3 ITEM
	{
		std::vector<std::unique_ptr<item>> ingredients;
		std::vector<ItemNames> ingredientTypes;
		std::vector<int> ingredientQuantity;

		ingredients.push_back(factoryOfItems.createItem(ItemNames::WoodEq, 5));
		ingredients.push_back(factoryOfItems.createItem(ItemNames::Patyk, 5));

		ingredientTypes.push_back(ItemNames::WoodEq);
		ingredientTypes.push_back(ItemNames::Patyk);

		ingredientQuantity.push_back(5);
		ingredientQuantity.push_back(5);


		auto resultItem = factoryOfItems.createItem(ItemNames::StoneEq, 2);

		this->RecipesVecNew.emplace_back(
			3,
			3,
			std::move(resultItem),
			std::move(ingredients),
			ItemNames::StoneEq,
			ingredientTypes,
			2.f,
			ingredientQuantity,
			RecipeStatus::InQueue,
			graphicsData
		);
	}

	//4 ITEM
	{
		std::vector<std::unique_ptr<item>> ingredients;
		std::vector<ItemNames> ingredientTypes;
		std::vector<int> ingredientQuantity;

		ingredients.push_back(factoryOfItems.createItem(ItemNames::WoodEq, 15));
		ingredients.push_back(factoryOfItems.createItem(ItemNames::Patyk, 15));

		ingredientTypes.push_back(ItemNames::WoodEq);
		ingredientTypes.push_back(ItemNames::Patyk);

		ingredientQuantity.push_back(15);
		ingredientQuantity.push_back(15);

		auto resultItem = factoryOfItems.createItem(ItemNames::StoneEq, 12);

		this->RecipesVecNew.emplace_back(
			4,
			3.f,
			std::move(resultItem),
			std::move(ingredients),
			ItemNames::StoneEq,
			ingredientTypes,
			12,
			ingredientQuantity,
			RecipeStatus::InQueue,
			graphicsData
		);
	}

	//5 ITEM
	{
		std::vector<std::unique_ptr<item>> ingredients;
		std::vector<ItemNames> ingredientTypes;
		std::vector<int> ingredientQuantity;

		ingredients.push_back(factoryOfItems.createItem(ItemNames::WoodEq, 55));
		ingredients.push_back(factoryOfItems.createItem(ItemNames::Patyk, 55));

		ingredientTypes.push_back(ItemNames::WoodEq);
		ingredientTypes.push_back(ItemNames::Patyk);

		ingredientQuantity.push_back(55);
		ingredientQuantity.push_back(55);

		auto resultItem = factoryOfItems.createItem(ItemNames::StoneEq, 52);

		this->RecipesVecNew.emplace_back(
			5,
			3.f,
			std::move(resultItem),
			std::move(ingredients),
			ItemNames::StoneEq,
			ingredientTypes,
			52,
			ingredientQuantity,
			RecipeStatus::InQueue,
			graphicsData
		);
	}

	//6 ITEM
	{
		std::vector<std::unique_ptr<item>> ingredients;
		std::vector<ItemNames> ingredientTypes;
		std::vector<int> ingredientQuantity;

		ingredients.push_back(factoryOfItems.createItem(ItemNames::WoodEq, 65));
		ingredients.push_back(factoryOfItems.createItem(ItemNames::Patyk, 65));

		ingredientTypes.push_back(ItemNames::WoodEq);
		ingredientTypes.push_back(ItemNames::Patyk);

		ingredientQuantity.push_back(65);
		ingredientQuantity.push_back(65);

		auto resultItem = factoryOfItems.createItem(ItemNames::StoneEq, 62);

		this->RecipesVecNew.emplace_back(
			6,
			3.f,
			std::move(resultItem),
			std::move(ingredients),
			ItemNames::StoneEq,
			ingredientTypes,
			62,
			ingredientQuantity,
			RecipeStatus::InQueue,
			graphicsData
		);
	}

	updateRecipesPos();
	updateRecipesQueuePos();

}
