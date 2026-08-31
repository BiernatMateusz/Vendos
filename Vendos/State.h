#ifndef STATE_H
#define STATE_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include <stack>
#include "EntityPlayer.h"
#include "Camera.h"
#include "Equipment.h"
#include "StructuresOfData.h"
#include "ThrownItems.h"
#include "Collision.h"
#include "TilesManagement.h"
#include "EntityConstructor.h"

#include "StateMachine.h"

class State
{

public:
	//Constructors
	State(GraphicsData* graphicsData, StateMachine* stateMachine);

	//Destructor
	virtual ~State() = default;

	//Update and render functions
	virtual void update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>&AllKeys) = 0;
	virtual void render() = 0;

	void updateTilesSprite();

	virtual void updateKeybinds(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys) = 0;

	//Ending state
	const bool& getQuit() const;
	void setQuit();
	virtual void checkForQuit(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys);
	virtual void endState() = 0;

	//Init functions
	void initTileVector();
	void initTileManagement();
	virtual void initGraphics() = 0;

	//Functions
	sf::Vector2i getPlayerTile();
	void frameCounterF(const float& dt);

	//Graphics function
	void LoadBackground(sf::Vector2f&& position, TextureNames NameOfTxt);
	void LoadBackground(TextureNames NameOfTxt);

private:
	bool quit;

protected:

	//Graphics data
	GraphicsData* graphicsData;

	//States
	StateMachine* stateMachine;


	Collision collisionManagement{};
	std::vector<std::reference_wrapper<sf::FloatRect>> CollisionTilesVec;

	//Tiles
	std::vector<std::vector<std::unique_ptr<TilesOnMap>>>Tile;

	//Items thrown
	std::unique_ptr<ThrownItems> ItemsOnTheGround;

	//Equipment
	std::unique_ptr<EquipmentData> equipmentData;
	std::unique_ptr<TilesManagement> tileManagement;

	//Camera
	std::unique_ptr<Camera>Camer;

	//Player
	Entity* entityPlayer{};

	//Entities
	EntityConstructor entityFactory{};
	
	//All entities
	std::vector<std::unique_ptr<Entity>>  entitiesPointer;


	float frameCounter{};
	float timeCounterForFPS{};

};


#endif 