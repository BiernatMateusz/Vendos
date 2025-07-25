#include "StateMenu.h"

StateMenu::StateMenu(GraphicsData* graphicsData, std::stack<State*>* Stat)
	: State(graphicsData, Stat)
{
	initGraphics();
}

StateMenu::~StateMenu()
{

}

void StateMenu::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	if (AllKeys.at("LeftMouse")->isButtonPressed())
	{
		if (AllKeys.at("LeftMouse")->checkIfInBoxArea({ 305, 265 }, { 440, 200 })) //button play
			stat->push(new StateSpawnPlace(this->graphicsData, this->stat));
	
		if (AllKeys.at("LeftMouse")->checkIfInBoxArea({ 350, 540 }, { 820, 730 })) //button exit game
			this->setQuit();
	}

	this->checkForQuit(AllKeys);
}


void StateMenu::endState()
{
	std::cout << "Ending Menustate\n";
}


void StateMenu::initGraphics()
{
	LoadBackground(TextureNames::Menu);

	this->Camer = new Camera(this->graphicsData);
}

void StateMenu::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->updateKeybinds(dt, AllKeys);
}

void StateMenu::render()
{
	this->Camer->render(this->graphicsData->window);
}
