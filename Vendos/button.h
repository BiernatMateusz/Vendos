#ifndef BUTTONH
#define BUTTONH

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include "CameraSprite.h"

class button
{

public:
	//Constructors
	button();
	button(sf::Keyboard::Key key);

	//Destructor
	~button();

	//Update button
	virtual void update(sf::RenderWindow *window, CameraSprite Background);

	//Returning states of button
	const bool& isButtonPressed() const;
	const bool& isButtonNotPressed() const;
	const bool& oneSignalButtonPressed() const;
	const bool& oneSignalButtonUnPressed() const;
	virtual const sf::Vector2i& mousePosGet() const ;
	virtual const sf::Vector2i& mousePosPrevGet() const;
	virtual const sf::Vector2i& mouseTileGet() const;
	virtual const sf::Vector2i& mouseTileActualGet() const;
	virtual bool checkIfInBoxArea(sf::Vector2f point, sf::Vector2f Area);

	virtual const bool& isWheelScrolledUp() const;
	virtual const bool& isWheelScrolledDown() const;
	virtual void setWheelScrollUp(bool state);
	virtual void setWheelScrollDown(bool state);

	

protected:
	void setStates();

	bool isPressed{};
	bool isNotPressed{};
	bool oneSignalPressed{};
	bool oneSignalUnPressed{};

	bool scrollUpTick{};
	bool scrollDownTick{};

	bool rampPress{};
	bool rampUnPress{};

private:

	sf::Keyboard::Key key;
};



#endif // !BUTTONH