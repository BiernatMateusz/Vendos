#include "StateMenu.h"
#include "StateSpawnPlace.h"

StateMenu::StateMenu(GraphicsData* graphicsData, StateMachine* stateMachine)
	: State(graphicsData, stateMachine)
{
	initGraphics();
}

void StateMenu::updateKeybinds(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	if (AllKeys.at(inputAction::LMouse)->isButtonPressed())
	{
		if (AllKeys.at(inputAction::LMouse)->checkIfInBoxArea({ 305, 265 }, { 440, 200 })) //button play
			stateMachine->pushState(std::make_unique<StateSpawnPlace>(this->graphicsData, stateMachine));
	
		if (AllKeys.at(inputAction::LMouse)->checkIfInBoxArea({ 350, 540 }, { 820, 730 })) //button exit game
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

	this->Camer = std::make_unique<Camera>(this->graphicsData);
}

void StateMenu::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	this->updateKeybinds(dt, AllKeys);
}

void StateMenu::render()
{
	this->Camer->render(this->graphicsData->window);
}
