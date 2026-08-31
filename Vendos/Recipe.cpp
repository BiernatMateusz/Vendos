#include "Recipe.h"

Recipe::Recipe(int ID, float craftTime, std::unique_ptr<item> itemToCreate, std::vector<std::unique_ptr<item>> itemIngedients, ItemNames resultType, std::vector<ItemNames> ingredientTypes, int resultQuantity, std::vector<int>ingredientQuantity, RecipeStatus status, GraphicsData* graphicsData)
	: ID(ID),
	craftTime(craftTime),
	itemCreated(std::move(itemToCreate)),
	itemIngredients(std::move(itemIngedients)),
	resultType(resultType),
	ingredientTypes(ingredientTypes),
	resultQuantity(resultQuantity),
	ingredientQuantity(ingredientQuantity),
	status(status),
	graphicsData(graphicsData)
{
	this->backgroundResultSpr.setTexture(*this->graphicsData->TexturesData.at(TextureNames::craftingResult)->texture);
	this->backgroundResultProgressSpr.setTexture(*this->graphicsData->TexturesData.at(TextureNames::craftingResultProgress)->texture);
}

void Recipe::setPos(sf::Vector2f Position, int SizeOfItems)
{
	//SetPosOfItemCreated
	this->itemCreated->setPositionInStorage(
		{	
			Position.x + (5* SizeOfItems),
			Position.y
		}
	);

	//SetPosOfItemIngredients
	for (int i = 0; i < itemIngredients.size(); i++)
		this->itemIngredients.at(i)->setPositionInStorage(
			{
				Position.x + (i * SizeOfItems),
				Position.y
			}
		);

}

void Recipe::setPosItemCreated(sf::Vector2f Position, int SizeOfItems)
{
	//SetPosOfItemCreated
	this->itemCreated->setPositionInStorage(
		{
			Position.x + (7 * SizeOfItems),
			Position.y
		}
	);
}

void Recipe::setStatus(RecipeStatus status)
{
	this->status = status;
}

void Recipe::update(const float& dt)
{
	if (status == RecipeStatus::InProgress)
	{
		accumulateTime(dt);
		checkIfCraftTimePassed();
	}
		

}

void Recipe::Render()
{
	this->itemCreated->drawItem();

	for (auto& elem : itemIngredients)
		elem->drawItem();
}

void Recipe::RenderItemCreated(sf::RenderWindow* window)
{
	if (status != RecipeStatus::DoneMovedToStorage and status != RecipeStatus::DoneTaken and status != RecipeStatus::InProgress)
	{
		backgroundResultSpr.setPosition(this->itemCreated->getPosition());
		setSpriteResult();
		window->draw(this->backgroundResultSpr);
		this->itemCreated->drawItem();
	}
	else if (status == RecipeStatus::InProgress)
	{
		backgroundResultProgressSpr.setPosition(this->itemCreated->getPosition());
		setSpriteProgress();
		window->draw(this->backgroundResultProgressSpr);
		this->itemCreated->drawItem();
	}
}

void Recipe::resetProgress()
{
	this->craftTimeProgress = 0.f;
}

void Recipe::setSpriteResult()
{
	int state = 0;

	switch (status)
	{
	case RecipeStatus::InQueue:
		state = 3;
		break;

	case RecipeStatus::NoIngredients:
		state = 2;
		break;

	default:
		return;
	}

	backgroundResultSpr.setTextureRect(
		sf::IntRect(
			{ 88 * state, 0 },
			{ 88, 88 }
		)
	);
}

void Recipe::setSpriteProgress()
{
	int state = 0;

	int progress = (craftTimeProgress / craftTime)*10;

	backgroundResultProgressSpr.setTextureRect(
		sf::IntRect(
			{ 88 * progress, 0 },
			{ 88, 88 }
		)
	);
}

void Recipe::accumulateTime(const float& dt)
{
	craftTimeProgress = craftTimeProgress+dt;
}

void Recipe::checkIfCraftTimePassed()
{
	if (craftTimeProgress >= craftTime)
		this->status = RecipeStatus::Done;
}
