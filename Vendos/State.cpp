#include "State.h"



//Constructors
State::State(GraphicsData* graphicsData, StateMachine* stateMachine)
{
	this->graphicsData = graphicsData;
	this->stateMachine = stateMachine;
	this->quit = false;
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::setQuit()
{
	this->quit = true;
}

sf::Vector2i State::getPlayerTile()
{
	if (this->graphicsData->backGroundMapped.isActive())
	{
		int x = ((int)this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height - (int)this->graphicsData->backGroundMapped.getSprite().getPosition().y);
		return { ((int)this->graphicsData->player->getSprite().getPosition().x - (int)this->graphicsData->backGroundMapped.getSprite().getPosition().x) / 44,
			(((int)this->graphicsData->player->getSprite().getPosition().y + (x)) / 44)};
	}
	return {1,0};
}

void State::frameCounterF(const float& dt)
{
	frameCounter++;
	timeCounterForFPS += dt;
	if (timeCounterForFPS >= 1)
	{
		std::cout << "Liczba klatek na sekunde: " << frameCounter << "\n";
		frameCounter = 0;
		timeCounterForFPS = 0;
	}
}

void State::checkForQuit(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	if (AllKeys.at(inputAction::ESC)->isButtonPressed())
		this->quit = true;
}

void State::initTileVector()
{
	int x = this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().width;
	x = 1 + (x - (x % 44)) / 44; //size().x of vector of tiles

	int y = this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height;
	y = 1 + (y - (y % 44)) / 44; //size().y of vector of tiles


	Tile.resize(x);
	for (auto& col : Tile)
	{
		col.resize(y); // unique_ptr domyœlnie = nullptr
	}
	
  
}

void State::initTileManagement()
{
	this->tileManagement = std::make_unique<TilesManagement>(this->graphicsData, this->equipmentData.get(), &this->Tile);
}

void State::LoadBackground(sf::Vector2f&& position, TextureNames NameOfTxt)
{
	this->graphicsData->backGroundMapped.setTexture(*this->graphicsData->TexturesData.at(NameOfTxt)->texture,true);
	this->graphicsData->backGroundMapped.setDistance(this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height);

	this->graphicsData->backGroundMapped.getSprite().setOrigin(0, this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height);
	
	this->graphicsData->backGroundMapped.getSprite().setPosition(position.x, position.y+ this->graphicsData->backGroundMapped.getSprite().getGlobalBounds().height);

	
}

void State::LoadBackground(TextureNames NameOfTxt)
{
	LoadBackground({ 0,0 }, NameOfTxt);
}

void State::updateTilesSprite()
{
	this->graphicsData->TilesSpriteMapped.clear();
	for (auto& row : Tile)
		for (auto& elem : row)
			if (elem != nullptr)
				if (elem->getCameraSpriteOnMap().isActive())
					this->graphicsData->TilesSpriteMapped.push_back(&elem->getCameraSpriteOnMap());
			
	this->equipmentData->needToUpdateTilesSpriteVec = 0;
}


