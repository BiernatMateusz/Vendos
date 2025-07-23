#ifndef STATESPAWNPLACE_H
#define STATESPAWNPLACE_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include "State.h"

class StateSpawnPlace :
    public State
{
private:
    void makeInvisibleBarrierAroundTheMap();

public:
    StateSpawnPlace(GraphicsData* graphicsData, std::stack<State*>* Stat);
    ~StateSpawnPlace();

    //Functions
    void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys);
    void endState();

    void initGraphics();
    void initPlayer();

    void playerMovement(const float& dt, const std::map<std::string, button*>& AllKeys);
    
    void mapGeneration();

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render();

    //variables
    MovementData movementData;

};

#endif 