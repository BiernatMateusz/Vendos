#ifndef ENTITY_H
#define ENTITY_H

#define EE_MCR_AVERAGER_BEGIN(x) sf::Clock EEAV_CLOCK_##x; static sf::Int64 EEAV_MS_##x=0; static int EEAV_FR_##x=0;
#define EE_MCR_AVERAGER_END(x) std::cout<<"Averaging clock("#x"):"<<(EEAV_MS_##x+=EEAV_CLOCK_##x.getElapsedTime().asMicroseconds())/(++EEAV_FR_##x)<<std::endl;

#include "EntityPlayer.h"

class Entity : 
	public EntityPlayer
{
private:
	
protected:
	//Tiles
	



public:
	Entity(GraphicsData* graphicsData);
	~Entity();

	void setTextData();
	
	void initCamera(Camera* Camer);
	void initEntityBasicData(ThrownItems* ItemsOnTheGround, std::vector<std::vector<TilesOnMap*>>* Tile, std::vector<sf::FloatRect*>* collisionTilesVec);
	void initStartingPositionOfEntity();
};

#endif 