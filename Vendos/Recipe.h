#ifndef RECIPE_H
#define RECIPE_H

#include "ItemConstructor.h"
#include "Workstation.h"
#include <deque>
#include "EquipmentAreas.h"

enum class RecipeStatus {InQueue, InProgress, Done, NoIngredients, DoneMovedToStorage, DoneTaken};

class Recipe
{
public:
	Recipe() {};
	Recipe(int ID, float craftTime, std::unique_ptr<item>itemToCreate, std::vector<std::unique_ptr<item>>itemIngredients,
		ItemNames resultType, std::vector<ItemNames> ingredientTypes,
		int resultQuantity, std::vector<int>ingredientQuantity, RecipeStatus status, GraphicsData* graphicsData);

	void setPos(sf::Vector2f Position, int SizeOfItems);
	void setPosItemCreated(sf::Vector2f Position, int SizeOfItems);
	void setStatus(RecipeStatus status);
	void update(const float& dt);
	void Render();
	void RenderItemCreated(sf::RenderWindow* window);


	int ID;
	float craftTime;
	float craftTimeProgress{};
	int QuantityOfRecipesToMake;
	std::unique_ptr<item>itemCreated;
	std::vector<std::unique_ptr<item>>itemIngredients;

	int resultQuantity;
	ItemNames resultType;
	std::vector<int>ingredientQuantity;
	std::vector<ItemNames> ingredientTypes;

	RecipeStatus status{RecipeStatus::InQueue};

	GraphicsData* graphicsData{};

	sf::RectangleShape backgroundResult{ sf::Vector2f(88.f, 88.f) };
	sf::Sprite backgroundResultSpr;
	sf::Sprite backgroundResultProgressSpr;

	void resetProgress();

private:
	void setSpriteResult();
	void setSpriteProgress();
	void accumulateTime(const float& dt);
	void checkIfCraftTimePassed();

};

#endif // !RECIPE_H