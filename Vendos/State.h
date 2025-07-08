#ifndef STATE_H
#define STATE_H

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury

#include <stack>
#include "EntityPlayer.h"
#include "Camera.h"
#include "Equipment.h"
#include "StructuresOfData.h"
#include "itemChest.h"
#include "itemFurnace.h"
#include "ThrownItems.h"
#include "Collision.h"
#include "TilesManagement.h"

class State
{

public:
	//Constructors
	State(GraphicsData* graphicsData, std::stack<State*>* Stat);

	//Destructor
	virtual ~State();

	//Update and render functions
	virtual void update(const float& dt, const std::map<std::string, button*> &AllKeys) = 0;
	virtual void render() = 0;

	void updateTilesSprite();

	virtual void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys) = 0;

	//Ending state
	const bool& getQuit() const;
	void setQuit();
	virtual void checkForQuit(const std::map<std::string, button*>& AllKeys);
	virtual void endState() = 0;

	//Init functions
	void initTileVector();
	void initTileManagement();
	virtual void initGraphics() = 0;

	//Functions
	virtual bool checkExactPosition(int x, int offsetX, int y, int offsetY, const std::map<std::string, button*>& AllKeys);
	sf::Vector2i getPlayerTile();
	void frameCounterF(const float& dt);

	//Graphics function
	void LoadBackground(sf::Vector2f&& position, std::string&& NameOfTxt);

	

private:
	bool quit;

protected:

	//Graphics data
	GraphicsData* graphicsData;

	//States
	std::stack<State*> *stat;

	Collision collisionManagement{};
	std::vector<sf::FloatRect*>CollisionTilesVec{};

	//Tiles
	std::vector<std::vector<TilesOnMap*>>Tile;

	//Items thrown
	ThrownItems* ItemsOnTheGround;

	//Equipment
	EquipmentData* equipmentData{};
	TilesManagement* tileManagement{};

	//Camera
	Camera* Camer;

	//Entities
	//Player
	Entity* entityPlayer;
	//All entities
	std::vector<Entity*>* entiesPointer;

	float frameCounter{};
	float timeCounterForFPS{};

};


#endif 