#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(GraphicsData* graphicsData, std::stack<State*>* Stat)
	: State(graphicsData, Stat)
{
	this->equipmentData = new EquipmentData;
	this->ItemsOnTheGround = new ThrownItems(graphicsData, equipmentData, &Tile);

	initPlayer();
	initGraphics();

}

void StateSpawnPlace::initPlayer()
{
	this->entiesPointer->push_back(new EntityPlayer({ 0,0 }, "Abigail", this->graphicsData, &Tile, this->equipmentData, ItemsOnTheGround, &CollisionTilesVec));
	this->entityPlayer = this->entiesPointer->back();
}

void StateSpawnPlace::initGraphics()
{
	LoadBackground({ 0,2596 }, "Mapka");

	initTileVector();
	initTileManagement();

	makeInvisibleBarrierAroundTheMap(); //need to optimize it by creating tiles without texture 

	mapGeneration();

	updateTilesSprite();

	this->Camer = new Camera(this->graphicsData);
	this->entityPlayer->initCamera(Camer);
	collisionManagement.updateCollisionTiles(&Tile, &CollisionTilesVec);
}

void StateSpawnPlace::makeInvisibleBarrierAroundTheMap()
{
	for (int i = 0; i < Tile[0].size() - 1; i++)
	{
		for (int j = 0; j <= 2; j++)
			tileManagement->initTile({ j,i }, "EmptyTile");

		tileManagement->initTile({ 71,i }, "EmptyTile");
		tileManagement->initTile({ 72,i }, "EmptyTile");
		tileManagement->initTile({ 73,i }, "EmptyTile");
	}
	for (int i = 0; i < Tile.size() - 1; i++)
	{
		for (int j = 0; j <= 4; j++)
			tileManagement->initTile({ i,j }, "EmptyTile");

		tileManagement->initTile({ i,58 }, "EmptyTile");
	}

	tileManagement->initTile({ 3,5 }, "EmptyTile");
}



StateSpawnPlace::~StateSpawnPlace()
{
	;
}

void StateSpawnPlace::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	for (auto* elem : *this->entiesPointer)
		elem->update(dt, AllKeys);

	this->tileManagement->update(dt, AllKeys);

	if (this->equipmentData->needToUpdateTilesSpriteVec)
		updateTilesSprite();

	if (this->equipmentData->needToUpdateCameraAllSpr)
		Camer->updateAllSpritesVecMapped(equipmentData);


	this->updateKeybinds(dt, AllKeys);

	this->collisionManagement.updateCollisionTiles(&Tile, &CollisionTilesVec);

	//frameCounterF(dt);
}

void StateSpawnPlace::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->checkForQuit(AllKeys);
	this->playerMovement(dt, AllKeys);
}

void StateSpawnPlace::endState()
{
	std::cout << "Ending SpawnPlaceState\n";
}


void StateSpawnPlace::playerMovement(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	//Reseting value to "nothing"
	this->movementData.direction = "";

	if (this->equipmentData->isEqOpened == 0)
		this->entityPlayer->movement(dt, 115, this->movementData, AllKeys);

	this->entityPlayer->Animation(dt, std::move(this->movementData.direction));

	if (this->movementData.moved)
		this->Camer->sortVectorMapped();

	this->movementData.moved = 0;
}

void StateSpawnPlace::mapGeneration()
{
	tileManagement->initTile({ 17, 12 }, "Skrzynia");
	tileManagement->initTile({ 18, 12 }, "Furnace");

	std::uniform_int_distribution<int> randomValue(0, 1000);
	int randomizedValue{};

	for (int i=0;i<Tile.size();i++)
		for (int j=0;j<Tile[0].size();j++)
			if (Tile[i][j] == nullptr)
			{
				randomizedValue = randomValue(this->graphicsData->randomEngine.mt);

				if (randomizedValue<50)
					tileManagement->initTile({ i,j }, "Stone");
				else if (randomizedValue >= 50 and randomizedValue < 60)
					tileManagement->initTile({ i, j }, "Tree1");
				else if (randomizedValue >= 60 and randomizedValue < 70)
					tileManagement->initTile({ i, j }, "Tree2");
				else if (randomizedValue >= 70 and randomizedValue < 80)
					tileManagement->initTile({ i, j }, "Tree3");
				else if (randomizedValue >= 80 and randomizedValue < 90)
					tileManagement->initTile({ i, j }, "Copper");
				else if (randomizedValue >= 90 and randomizedValue < 100)
					tileManagement->initTile({ i, j }, "Iron");
				else if (randomizedValue >= 100 and randomizedValue < 150)
					tileManagement->initTile({ i, j }, "Bush_empty");

			}

	delete this->Tile[getPlayerTile().x][getPlayerTile().y];  
	this->Tile[getPlayerTile().x][getPlayerTile().y] = nullptr;
	//prevents from spawning in block

}



void StateSpawnPlace::render()
{
	
	Camer->render(this->graphicsData->window);
	
	for (auto* elem : *this->entiesPointer)
		elem->render();
	
	if (this->equipmentData->isEqOpened == 0)
		this->tileManagement->render();
}
