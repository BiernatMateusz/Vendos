#include "State.h"


//Constructors
State::State(GraphicsData* graphicsData, std::stack<State*>* Stat)
{
	this->graphicsData = graphicsData;
	this->stat = Stat;
	this->quit = false;

	this->entiesPointer = new std::vector<Entity*>;
	
	this->graphicsData->EntitiesSprite = new std::vector<sf::Sprite*>;
	this->graphicsData->EntitiesSpriteMapped = new std::vector<CameraSprite*>;

	for (auto* elem : *this->graphicsData->EntitiesSprite)
		delete elem;

	for (auto* elem : *this->graphicsData->EntitiesSpriteMapped)
		delete elem;

	this->graphicsData->EntitiesSprite->clear();
	this->graphicsData->EntitiesSpriteMapped->clear();

	this->graphicsData->TilesSprite = new std::vector<sf::Sprite*>;
	this->graphicsData->TilesSpriteMapped = new std::vector<CameraSprite*>;

	for (auto* elem : *this->graphicsData->TilesSprite)
		delete elem;

	for (auto* elem : *this->graphicsData->TilesSpriteMapped)
		delete elem;

	this->graphicsData->TilesSprite->clear();
	this->graphicsData->TilesSpriteMapped->clear();

	this->graphicsData->ItemsThrownSprite = new std::vector<sf::Sprite*>;
	this->graphicsData->ItemsThrownSpriteMapped = new std::vector<CameraSprite*>;

	for (auto* elem : *this->graphicsData->ItemsThrownSprite)
		delete elem;

	for (auto* elem : *this->graphicsData->ItemsThrownSpriteMapped)
		delete elem;

	this->graphicsData->ItemsThrownSprite->clear();
	this->graphicsData->ItemsThrownSpriteMapped->clear();
}

//Destructor
State::~State()
{
	delete this->graphicsData->window;
	std::cout << "Usunalem stat\n";
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::setQuit()
{
	this->quit = true;
}

bool State::checkExactPosition(int x,int offsetX,int y,int offsetY, const std::map<std::string, button*>& AllKeys)
{
		return (AllKeys.at("LeftMouse")->mousePosGet().x > x && AllKeys.at("LeftMouse")->mousePosGet().x < offsetX && AllKeys.at("LeftMouse")->mousePosGet().y>y && AllKeys.at("LeftMouse")->mousePosGet().y < offsetY);
}

sf::Vector2i State::getPlayerTile()
{
	if (this->graphicsData->backGroundMapped->getSprite() != nullptr)
	{
		int x = ((int)this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height - (int)this->graphicsData->backGroundMapped->getSprite()->getPosition().y);
		return { ((int)this->graphicsData->player->getPosition().x - (int)this->graphicsData->backGroundMapped->getSprite()->getPosition().x) / 44,
			(((int)this->graphicsData->player->getPosition().y + (x)) / 44)};
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

void State::checkForQuit(const std::map<std::string, button*>& AllKeys)
{
	if (AllKeys.at("Esc")->isButtonPressed())
		this->quit = true;
}

void State::initTileVector()
{
	int x = this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().width;
	x = 1 + (x - (x % 44)) / 44; //size().x of vector of tiles

	int y = this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height;
	y = 1 + (y - (y % 44)) / 44; //size().y of vector of tiles

	this->Tile.resize(x, std::vector<TilesOnMap*>(y));
	
	for (auto& row : Tile)
		for (auto& elem : row)
			elem = nullptr;
  
}

void State::initTileManagement()
{
	this->tileManagement = new TilesManagement(this->graphicsData, this->equipmentData, &this->Tile);
}

void State::LoadBackground(sf::Vector2f&& position, TextureNames NameOfTxt)
{
	if (this->graphicsData->backGroundMapped != nullptr) delete this->graphicsData->backGroundMapped;
	
	this->graphicsData->backGroundMapped = new CameraSprite();
	this->graphicsData->backGroundMapped->setSpriteTexture(*this->graphicsData->TextureDataMapN->at(NameOfTxt)->texture);
	this->graphicsData->backGroundMapped->setDistance(this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height);

	this->graphicsData->backGroundMapped->getSprite()->setOrigin(0, this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height);
	
	this->graphicsData->backGroundMapped->getSprite()->setPosition(position.x, position.y+ this->graphicsData->backGroundMapped->getSprite()->getGlobalBounds().height);


}

void State::LoadBackground(TextureNames NameOfTxt)
{
	LoadBackground({ 0,0 }, NameOfTxt);
}

void State::updateTilesSprite()
{
	this->graphicsData->TilesSpriteMapped->clear();
	for (auto& row : Tile)
		for (auto& elem : row)
			if (elem != nullptr)
				if (elem->cameraSpriteOfTile != nullptr)
					this->graphicsData->TilesSpriteMapped->push_back(elem->cameraSpriteOfTile);
			
	this->equipmentData->needToUpdateTilesSpriteVec = 0;
}


