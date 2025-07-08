#include "Game.h"

//Constructors
Game::Game()
{
	this->initAllKeys();
	this->initializeWindow();
	this->initGraphicsData();
	this->initTextures();
	this->initStates();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->graphicsData;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}

}

//Update and render functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update();
		this->render();
	}
}

void Game::updateSfEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();

		/*if (this->sfEvent.type == sf::Event::MouseWheelMoved)
		{
			if (this->sfEvent.mouseWheel.delta > 0)
			{
				std::cout << "Krece w gore :)\n";
			}
			else if (this->sfEvent.mouseWheel.delta < 0)
			{
				std::cout << "Krece w dol :)\n";
			}
		}*/
	}
}

void Game::update()
{
	this->updateSfEvents();

	//Keys update
	if (this->graphicsData->window!=nullptr)
		std::for_each(AllKeys.begin(), AllKeys.end(), [this](auto& keys) {keys.second->update(this->graphicsData->window, this->graphicsData->backGroundMapped->getSprite()); });

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt, this->AllKeys);

		if (this->states.top()->getQuit())
		{
			//Save game before then do that 
			this->states.top()->endState();

			delete this->states.top();
			this->states.pop();
		}

	}
	else
	{
		this->endApp();
		this->window->close();
	}

}

void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}

void Game::endApp()
{
	std::cout << "KONIEC\n";
}

//Init functions
void Game::initializeWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WindowLenght, this->WindowHight), "Vendos");
	this->window->setFramerateLimit(240);
	this->window->setVerticalSyncEnabled(false);
	this->window->setKeyRepeatEnabled(false);
}

void Game::initAllKeys()
{
	this->AllKeys.insert({ "A", new button(sf::Keyboard::A)});
	this->AllKeys.insert({ "S", new button(sf::Keyboard::S)});
	this->AllKeys.insert({ "D", new button(sf::Keyboard::D)});
	this->AllKeys.insert({ "W", new button(sf::Keyboard::W)});
	this->AllKeys.insert({ "E", new button(sf::Keyboard::E)});
	this->AllKeys.insert({ "Esc", new button(sf::Keyboard::Escape)});
	this->AllKeys.insert({ "LShift", new button(sf::Keyboard::LShift) });
	this->AllKeys.insert({ "LeftMouse", new mouseButton(sf::Mouse::Left)});
	this->AllKeys.insert({ "RightMouse", new mouseButton(sf::Mouse::Right)});
	this->AllKeys.insert({ "Num0", new button(sf::Keyboard::Num0) });
	this->AllKeys.insert({ "Num1", new button(sf::Keyboard::Num1) });
	this->AllKeys.insert({ "Num2", new button(sf::Keyboard::Num2) });
	this->AllKeys.insert({ "Num3", new button(sf::Keyboard::Num3) });
	this->AllKeys.insert({ "Num4", new button(sf::Keyboard::Num4) });
	this->AllKeys.insert({ "Num5", new button(sf::Keyboard::Num5) });
	this->AllKeys.insert({ "Num6", new button(sf::Keyboard::Num6) });
	this->AllKeys.insert({ "Num7", new button(sf::Keyboard::Num7) });
	this->AllKeys.insert({ "Num8", new button(sf::Keyboard::Num8) });
	this->AllKeys.insert({ "Num9", new button(sf::Keyboard::Num9) });

}

void Game::initStates()
{
	this->states.push(new StateMenu(this->graphicsData, &this->states));
}

void Game::initTextures()
{
	//How to create new texture:
	// 
	//No blockade, no tiles texture:
	//LoadNewGraphic(name, id)
	//
	//Tile
	//LoadNewGraphic(name, size of blockade, origin, blockade offset, is it blockade?, type of tile, ID, offset for camera)


	//Main menu
	LoadNewGraphic("Menu",0);


	//Terrain
	LoadNewGraphic("Mapka", 1);

	//Player
	//LoadNewGraphic("Abigail", 2);
	LoadNewGraphic("Abigail", { 30,15 }, { 7,78 }, { 0,-15 }, true, tileType::player, StorageAreas::Empty, 2, 0, sf::FloatRect(22, 20, 40, 85), sf::FloatRect(0, 0, 30, 15), {0}, { 0 });

	//Field
	LoadNewGraphic("PoDziabceSuche", { 0,0 }, { 0,0 }, { 0,0 }, false, tileType::hoedField, StorageAreas::Empty, 3, -44, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 0, 0), {0}, { 0 });
	LoadNewGraphic("PoDziabceMokre", { 0,0 }, { 0,0 }, { 0,0 }, false, tileType::wateredField, StorageAreas::Empty, 4, -44, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 0, 0), {0}, { 0 });

	//Pickaxable map
	LoadNewGraphic("Stone", { 30,25 }, { 0,0 }, { 7,25 }, true, tileType::pickaxableField, StorageAreas::Empty, 5, 40, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 15), {100}, { 5 });
	LoadNewGraphic("Copper", { 30,25 }, { 0,0 }, { 7,25 }, true, tileType::pickaxableField, StorageAreas::Empty, 6, 40, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 15), { 103 }, { 5 });
	LoadNewGraphic("Iron", { 30,25 }, { 0,0 }, { 7,25 }, true, tileType::pickaxableField, StorageAreas::Empty, 7, 40, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 15), { 104 }, { 5 });

	//Trees
	LoadNewGraphic("Tree1", { 30,30 }, { 50,160 }, { 6,8 }, true, tileType::axableField, StorageAreas::Empty, 10, 33, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 22), {101}, { 5 });
	LoadNewGraphic("Tree2", { 30,18 }, { 68,162 }, { 8,19 }, true, tileType::axableField, StorageAreas::Empty, 11, 33, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 18), {101}, { 5 });
	LoadNewGraphic("Tree3", { 30,16 }, { 42,135 }, { 12,24 }, true, tileType::axableField, StorageAreas::Empty, 12, 33, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 14), {101}, { 5 });

	//Bushes
	LoadNewGraphic("Bush_empty", { 30,20 }, { 0,0 }, { 7,25 }, true, tileType::axableField, StorageAreas::Empty, 13, 40, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 30, 15), { 102 }, { 5 });

	//Empty
	LoadNewGraphic("EmptyTile", {29,29 }, { 0,0 }, { 0,0 }, true, tileType::emptyBlockade, StorageAreas::Empty, 0, 0, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 29, 29), { 0 }, { 0 });


	//Equipment
	// 
	//Nonstackable
	LoadNewGraphic("WoodenHoe",20);
	LoadNewGraphic("WoodenPickaxe",21);
	LoadNewGraphic("WoodenAxe",22);
	LoadNewGraphic("WoodenSword",23);
	LoadNewGraphic("WoodenShovel",24);
	LoadNewGraphic("WoodenWateringCan",25);

	//Chest
	LoadNewGraphic("Skrzynia", { 32,20 }, { 0,0 }, { 5,15 }, true, tileType::chestField, StorageAreas::Chest, 26, 20, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 32, 20), {0}, { 0 });
	LoadNewGraphic("Furnace", { 32,20 }, { 0,0 }, { 5,15 }, true, tileType::chestField, StorageAreas::Furnace, 27, 20, sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 32, 20), { 0 }, { 0 });
	//Stackable

	LoadNewGraphic("StoneEq",100);
	LoadNewGraphic("WoodEq", 101);
	LoadNewGraphic("Patyk", 102);
	LoadNewGraphic("CopperEq", 103);
	LoadNewGraphic("IronEq", 104);
	LoadNewGraphic("ChestEq", 105);
	LoadNewGraphic("FurnaceEq", 106);

	//Eq_layout
	LoadNewGraphic("ramka", 200);
	LoadNewGraphic("ramka1", 201);
	LoadNewGraphic("BackgroundCrafting", 202);
	LoadNewGraphic("BackgroundChest", 203);
	LoadNewGraphic("BackgroundFurnace", 204);
}

void Game::initGraphicsData()
{
	this->graphicsData = new GraphicsData;

	this->graphicsData->TextureDataMap = new std::map<std::string, TextureData*>;
	this->graphicsData->window = this->window;
	this->graphicsData->TexturesMap = new std::map<std::string, sf::Texture*>;
	this->graphicsData->GraphicsTxtVec = new std::vector<sf::Texture*>;
	this->graphicsData->AllExcludedSpritesPointer = new std::vector<sf::Sprite*>;
	this->graphicsData->backGroundMapped = new CameraSprite;
	this->graphicsData->itemDroppedVec = new std::vector<itemDroppedFromTile*>;
}

//Graphics functions 
void Game::LoadNewGraphic(const std::string& name, int itemID)
{
	this->graphicsData->GraphicsTxtVec->push_back(new sf::Texture);
	this->graphicsData->GraphicsTxtVec->back()->loadFromFile("Texture/" + name + ".png");
	this->graphicsData->TexturesMap->insert(std::pair<std::string, sf::Texture*>(name, this->graphicsData->GraphicsTxtVec->back()));

	this->graphicsData->TextureDataMap->insert(std::pair<std::string, TextureData*>(name, new TextureData));
	this->graphicsData->TextureDataMap->at(name)->texture = new sf::Texture;
	this->graphicsData->TextureDataMap->at(name)->texture->loadFromFile("Texture/" + name + ".png");

	this->graphicsData->TextureDataMap->at(name)->initBlocksOccupied(name);
	this->graphicsData->TextureDataMap->at(name)->itemID = itemID;
	
}

void Game::LoadNewGraphic(const std::string& name, sf::Vector2i blockadeSize,  sf::Vector2i origin, sf::Vector2f blockadeOffset, 
	bool blockade, tileType typeOfTile,StorageAreas storageArea, int itemID, float offsetForCamera, sf::FloatRect textRect, 
	sf::FloatRect blockadeRect, std::vector<int>idOfItemsDroppedFromTile, std::vector<int>ammountOfDroppedItems)
{
	LoadNewGraphic(name, itemID);

	this->graphicsData->TextureDataMap->at(name)->blockade = blockade;
	this->graphicsData->TextureDataMap->at(name)->blockadeSize = blockadeSize;
	this->graphicsData->TextureDataMap->at(name)->origin = origin;
	this->graphicsData->TextureDataMap->at(name)->typeOfTile = typeOfTile;
	this->graphicsData->TextureDataMap->at(name)->storageArea = storageArea;
	this->graphicsData->TextureDataMap->at(name)->offsetForCamera = offsetForCamera;
	this->graphicsData->TextureDataMap->at(name)->offsetForBlockade = blockadeOffset;
	this->graphicsData->TextureDataMap->at(name)->TextRect = textRect;
	this->graphicsData->TextureDataMap->at(name)->blockadeRect = blockadeRect;
	this->graphicsData->TextureDataMap->at(name)->idOfItemsThatDropsFromTile = idOfItemsDroppedFromTile;
	this->graphicsData->TextureDataMap->at(name)->ammountOfDroppedItems = ammountOfDroppedItems;

}

