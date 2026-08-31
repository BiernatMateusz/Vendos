#ifndef STATEMENU_H
#define STATEMENU_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include "State.h"


class StateSpawnPlace;

class StateMenu :
    public State
{
private:

    

public:
    StateMenu(GraphicsData* graphicsData, StateMachine* stateMachine);

    //Functions
    void updateKeybinds(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    void endState();

    void initGraphics();
    void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    void render();
};

#endif // !STATEMENU_H