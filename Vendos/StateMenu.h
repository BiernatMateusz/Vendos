#ifndef STATEMENU_H
#define STATEMENU_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include "State.h"
#include "StateSpawnPlace.h"

class StateMenu :
    public State
{
private:

    

public:
    StateMenu(GraphicsData* graphicsData, std::stack<State*>* Stat);
    ~StateMenu();

    //Functions
    void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys);
    void endState();

    void initGraphics();
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();
};

#endif // !STATEMENU_H