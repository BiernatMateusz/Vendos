#include "Game.h"

//Constructors
Game::Game()
{
	this->initAllKeys();
	this->initializeWindow();
	this->initGraphicsData();
	this->initTextures();
	//this->initStates();
	this->stateMachine = std::make_unique<StateStack>();
	this->stateMachine->pushState(std::make_unique<StateMenu>(getGraphicsData(), this->stateMachine.get()));

}

//Destructor
Game::~Game()
{
	;
}

//Update and render functions
void Game::run()
{
	


	while (this->window->isOpen())
	{

		//this->frameCounting();

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

		

		if (this->sfEvent.type == sf::Event::MouseWheelMoved)
		{
			if (this->sfEvent.mouseWheel.delta > 0)
			{
				AllKeys.at(inputAction::Scroll)->setWheelScrollUp(true);
			}
			else if (this->sfEvent.mouseWheel.delta < 0)
			{
				AllKeys.at(inputAction::Scroll)->setWheelScrollDown(true);
			}	
		}		
	}
}

void Game::update()
{
	
	this->updateSfEvents();
	
	//Keys update
	if (this->graphicsData->window!=nullptr)
		std::for_each(AllKeys.begin(), AllKeys.end(), [this](auto& keys) {keys.second->update(this->graphicsData->window, this->graphicsData->backGroundMapped); });

	
	if (auto* state = stateMachine->top())
	{
		state->update(this->dt, this->AllKeys);

		if (state->getQuit())
		{
			state->endState();
			stateMachine->popState();
		}
	}
	else
	{
		endApp();
		window->close();
	}

}

void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::render()
{
	this->window->clear();

	if (auto* state = stateMachine->top())
	{
		state->render();
	}

	this->window->display();
}

void Game::endApp()
{
	std::cout << "KONIEC\n";
}

void Game::frameCounting()
{
	frames++;

	timer += clock.restart().asSeconds();

	if (timer >= 1.f)
	{
		std::cout << "FPS: " << frames << "\n";
		frames = 0;
		timer = 0;
	}
}

//Init functions
void Game::initializeWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(this->WindowLenght, this->WindowHight), "Vendos");
	this->window->setFramerateLimit(240);
	this->window->setVerticalSyncEnabled(false);
	this->window->setKeyRepeatEnabled(false);
	
}

 sf::RenderWindow* Game::getWindow() const
{
	return this->window.get();
}

 GraphicsData* Game::getGraphicsData() const
 {
	 return this->graphicsData.get();
 }


void Game::initAllKeys()
{
	this->AllKeys.emplace(inputAction::MoveLeft, std::make_unique<button>(sf::Keyboard::A));
	this->AllKeys.emplace(inputAction::MoveDown, std::make_unique<button>(sf::Keyboard::S));
	this->AllKeys.emplace(inputAction::MoveRight, std::make_unique<button>(sf::Keyboard::D));
	this->AllKeys.emplace(inputAction::MoveUp, std::make_unique<button>(sf::Keyboard::W));

	this->AllKeys.emplace(inputAction::Interact, std::make_unique<button>(sf::Keyboard::E));

	this->AllKeys.emplace(inputAction::ESC, std::make_unique<button>(sf::Keyboard::Escape));
	this->AllKeys.emplace(inputAction::LShift, std::make_unique<button>(sf::Keyboard::LShift));

	this->AllKeys.emplace(inputAction::LMouse, std::make_unique<mouseButton>(sf::Mouse::Left) );
	this->AllKeys.emplace(inputAction::RMouse, std::make_unique<mouseButton>(sf::Mouse::Right) );
	this->AllKeys.emplace(inputAction::Scroll, std::make_unique<mouseButtonWheel>());

	this->AllKeys.emplace(inputAction::Slot0, std::make_unique<button>(sf::Keyboard::Num0));
	this->AllKeys.emplace(inputAction::Slot1, std::make_unique<button>(sf::Keyboard::Num1));
	this->AllKeys.emplace(inputAction::Slot2, std::make_unique<button>(sf::Keyboard::Num2));
	this->AllKeys.emplace(inputAction::Slot3, std::make_unique<button>(sf::Keyboard::Num3));
	this->AllKeys.emplace(inputAction::Slot4, std::make_unique<button>(sf::Keyboard::Num4));
	this->AllKeys.emplace(inputAction::Slot5, std::make_unique<button>(sf::Keyboard::Num5));
	this->AllKeys.emplace(inputAction::Slot6, std::make_unique<button>(sf::Keyboard::Num6));
	this->AllKeys.emplace(inputAction::Slot7, std::make_unique<button>(sf::Keyboard::Num7));
	this->AllKeys.emplace(inputAction::Slot8, std::make_unique<button>(sf::Keyboard::Num8));
	this->AllKeys.emplace(inputAction::Slot9, std::make_unique<button>(sf::Keyboard::Num9));

}

void Game::initTextures()
{
	//Main menu
	LoadNewGraphic("Menu",TextureNames::Menu);

	//Terrain
	LoadNewGraphic("Mapka", TextureNames::Mapka);

	//Player
	LoadNewGraphic("Abigail", TextureNames::Abigail);

	//Field
	LoadNewGraphic("PoDziabceSuche", TextureNames::HoedNoWater);
	LoadNewGraphic("PoDziabceMokre", TextureNames::HoedWatered);

	//Pickaxable map
	LoadNewGraphic("Stone", TextureNames::Stone);
	LoadNewGraphic("Copper", TextureNames::Copper);
	LoadNewGraphic("Iron", TextureNames::Iron);

	//Trees
	LoadNewGraphic("Tree1", TextureNames::Tree1);
	LoadNewGraphic("Tree2", TextureNames::Tree2);
	LoadNewGraphic("Tree3", TextureNames::Tree3);

	//Machines
	LoadNewGraphic("Skrzynia", TextureNames::Chest);
	LoadNewGraphic("Furnace", TextureNames::Furnace);

	//Bushes
	LoadNewGraphic("Bush_empty", TextureNames::BushEmpty);

	//Empty
	LoadNewGraphic("EmptyTile", TextureNames::EmptyTile);

	//Equipment
	LoadNewGraphic("WoodenHoe", TextureNames::WoodenHoe);
	LoadNewGraphic("WoodenPickaxe", TextureNames::WoodenPickaxe);
	LoadNewGraphic("WoodenAxe", TextureNames::WoodenAxe);
	LoadNewGraphic("WoodenSword", TextureNames::WoodenSword);
	LoadNewGraphic("WoodenShovel", TextureNames::WoodenShovel);
	LoadNewGraphic("WoodenWateringCan", TextureNames::WoodenWateringCan);

	
	//Stackable
	LoadNewGraphic("StoneEq", TextureNames::StoneEq);
	LoadNewGraphic("WoodEq", TextureNames::WoodEq);
	LoadNewGraphic("Patyk", TextureNames::Patyk);
	LoadNewGraphic("CopperEq", TextureNames::CopperEq);
	LoadNewGraphic("IronEq", TextureNames::IronEq);
	LoadNewGraphic("ChestEq", TextureNames::ChestEq);
	LoadNewGraphic("FurnaceEq", TextureNames::FurnaceEq);

	//Eq_layout
	LoadNewGraphic("ramka", TextureNames::ramka);
	LoadNewGraphic("ramka1", TextureNames::ramka1);
	LoadNewGraphic("BackgroundCrafting", TextureNames::BackgroundCrafting);
	LoadNewGraphic("BackgroundChest", TextureNames::BackgroundChest);
	LoadNewGraphic("BackgroundFurnace", TextureNames::BackgroundFurnace);
	LoadNewGraphic("craftingResult", TextureNames::craftingResult);
	LoadNewGraphic("craftingResultProgress", TextureNames::craftingResultProgress);
}

void Game::initGraphicsData()
{
	this->graphicsData = std::make_unique<GraphicsData>();

	this->graphicsData->window = getWindow();
	this->graphicsData->CenterOfMap = {(float)this->graphicsData->window->getSize().x/2, (float)this->graphicsData->window->getSize().y/2 };

	this->graphicsData->font.loadFromFile("Font/Rinnero.ttf");
}

//Graphics functions 
void Game::LoadNewGraphic(const std::string& name, TextureNames nameOfTxt)
{
	this->graphicsData->TexturesData.insert(std::pair<TextureNames, TextureData*>(nameOfTxt, new TextureData));
	this->graphicsData->TexturesData.at(nameOfTxt)->texture = new sf::Texture;
	
	if (!this->graphicsData->TexturesData.at(nameOfTxt)->texture->loadFromFile("Texture/" + name + ".png"))
	{
		std::cout << "ERROR: nie zaladowano tekstury: Texture/"
			<< name << ".png\n";
	}
	
}

