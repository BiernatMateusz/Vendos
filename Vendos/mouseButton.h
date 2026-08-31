#ifndef MOUSEBUTTONH
#define MOUSEBUTTONH

#include "button.h"

class mouseButton :
    public button
{
public:
    mouseButton();
    mouseButton(sf::Mouse::Button MouseButton);
    void update(sf::RenderWindow *window, CameraSprite backGround);
   

    //getters
    const sf::Vector2i& mousePosGet() const;
    const sf::Vector2i& mousePosPrevGet() const;
    const sf::Vector2i& mouseTileGet() const;
    const sf::Vector2i& mouseTileActualGet() const;
    
    bool checkIfInBoxArea(sf::Vector2f point, sf::Vector2f Area);
protected:
    sf::Mouse::Button MouseButton;
private:
    void setMouseStates(sf::RenderWindow* window);
    void setMouseTile(sf::RenderWindow* window, CameraSprite BackGround);
    void setMouseTileActual(sf::RenderWindow* window, CameraSprite BackGround);

    void setTileCoveredByMouse(sf::RenderWindow* window, CameraSprite BackGround, sf::Vector2i& MouseTileVariable);

    bool checkIfInScreen(sf::RenderWindow* window);

    sf::Vector2i mousePos{};
    sf::Vector2i mousePosPrev{};
    sf::Vector2i mouseTile{};
    sf::Vector2i mouseTileActual{};
    sf::RenderWindow* window{};
};

#endif // !MOUSEBUTTONH