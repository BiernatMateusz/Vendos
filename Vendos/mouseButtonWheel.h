#ifndef MOUSEBUTTONWHEEL_H
#define MOUSEBUTTONWHEEL_H


#include "mouseButton.h"
class mouseButtonWheel :
    public mouseButton
{
public:
    mouseButtonWheel();
    void update(sf::RenderWindow* window, CameraSprite backGround);

    const bool& isWheelScrolledUp() const;
    const bool& isWheelScrolledDown() const;

    void setWheelScrollUp(bool state);
    void setWheelScrollDown(bool state);

private:
    bool found1NextTickNeedToDelete{};
};

#endif // !MOUSEBUTTONWHEEL_H