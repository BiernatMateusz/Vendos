#ifndef CRAFTING_ITEMS_H
#define CRAFTING_ITEMS_H

#include "StructuresOfData.h"
#include "EquipmentAreas.h"
#include "Recipe.h"


class CraftingItems :
	public EquipmentStorageArea
{
private:
	EquipmentAreas* eqAreas;

	std::vector<Recipe>RecipesVecNew;
	std::vector<Recipe>RecipesQueue;
	void initRecipesVecNew();
	void updateRecipesPos();
	void updateRecipesQueuePos();

	EquipmentStorageArea* playerStorage;

	ItemConstructor factoryOfItems;

	RecipeStatus getStatus(Recipe rec);

	sf::Vector2i RecipeHovered{};
	void getHoveredSquareStatus(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	float scrolledOffset{};
	void updateScroll(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	int minPossibleScrollOffset{};
	int maxPossibleScrollOffset{};
	int showedItemStart{};
	void calculateMaxOffsetBothDirections();

	void updateKeybinds(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);

	Recipe copyRecipe(const Recipe& OriginalRecipe);
	void addRecipeToQueue();
	void deleteRecipeFromQueue(int numberOfRecipeHovered);
	bool isCursorInCraftingArea();
	bool isCrusorInResultArea();

	void checkIfCraftingPossible(int numberOfRecipeInQue);
	bool checkIngredients(int numberOfRecipeInQue);
	void setDoneTakenStatus();
	void clearQueueFromTaken();

	void moveRecipeResultToStorage(int recipeSlot);
	void takeItemsFromStorage(int recipeSlot);

	const std::vector<sf::Vector2i>recipePositions{ {7,8}, {7,7}, {7,6}, {7,5}, {7,4} };

public:
	CraftingItems(
		GraphicsData* graphicsData,
		EquipmentData* equipmentData,
		EquipmentStorageArea* playerStorage,
		EquipmentAreas* eqAreas);

	void updateCrafting(const float& dt);
	void updateActiveStorage(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys) override;
	void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys) override;
	void renderStorage();
};

#endif 