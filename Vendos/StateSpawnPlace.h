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
    StateSpawnPlace(GraphicsData* graphicsData, StateMachine* stateMachine);

    //Functions
    void updateKeybinds(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    void endState();

    void initGraphics();
    void initPlayer();

    void playerMovement(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    
    void mapGeneration();

    void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
    void render();

    //variables
    MovementData movementData;

};

#endif 