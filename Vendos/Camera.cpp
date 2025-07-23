#include "Camera.h"
//Operators
bool operator>(const sf::Sprite &x,const sf::Sprite &y)
{
	return (y.getPosition().y ) > (x.getPosition().y);
}

//Constructors
Camera::Camera(GraphicsData *graphicsData)
{
	
	initGraphicsBasics(graphicsData);
	
	if (graphicsData->EntitiesSprite->size() > 0)
	{
		this->Player = *graphicsData->EntitiesSprite->begin();
		this->CenterOfMap = Player->getPosition();
		graphicsData->CenterOfMap = &this->CenterOfMap;
	}

	cameraSpriteJoin();
	sortVectorMapped();
}
//Destructors
Camera::~Camera()
{

}


void Camera::initGraphicsBasics(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->BackGround = graphicsData->backGroundMapped->getSprite();
	this->Window = graphicsData->window;
}

void Camera::cameraSpriteJoin()
{
	if (graphicsData->EntitiesSpriteMapped->size() > 0)
		AllSpritesMapped.insert(std::end(AllSpritesMapped), std::begin(*graphicsData->EntitiesSpriteMapped), std::end(*graphicsData->EntitiesSpriteMapped));

	if (graphicsData->TilesSpriteMapped->size() > 0)
		AllSpritesMapped.insert(std::end(AllSpritesMapped), std::begin(*graphicsData->TilesSpriteMapped), std::end(*graphicsData->TilesSpriteMapped));

	if (graphicsData->ItemsThrownSpriteMapped->size() > 0)
		AllSpritesMapped.insert(std::end(AllSpritesMapped), std::begin(*graphicsData->ItemsThrownSpriteMapped), std::end(*graphicsData->ItemsThrownSpriteMapped));


	this->AllSpritesMapped.erase
	(
		std::remove_if(
			this->AllSpritesMapped.begin(),
			this->AllSpritesMapped.end(),
			[&](auto& AllSpritesMapped)
			{
				if (AllSpritesMapped == nullptr) return true;
				else return false;
			}
		), AllSpritesMapped.end()
	);

	this->AllSpritesMapped.shrink_to_fit();
			
}

//Functions

void Camera::updateAllSpritesVecMapped(EquipmentData* equipmentData)
{
	this->AllSpritesMapped.clear();
	
	cameraSpriteJoin();

	sortVectorMapped();

	equipmentData->needToUpdateCameraAllSpr = 0;


}

void Camera::sortVectorMapped()
{
	std::sort(std::begin(AllSpritesMapped), std::end(AllSpritesMapped),
		[*this](CameraSprite*& y, CameraSprite*& x) -> bool
		{
			if (y->sprite->getPosition().y + y->distance != x->sprite->getPosition().y + x->distance)
				return y->sprite->getPosition().y + y->distance < x->sprite->getPosition().y + x->distance;
			else 
				return y->sprite->getPosition().x < x->sprite->getPosition().x;
		}
	);
	
	
}

void Camera::render(sf::RenderWindow* window)
{
	//Function enables us to draw background at the beggining then all sprites
	window->draw(*this->BackGround);

	for (auto &elem : AllSpritesMapped)
	{
		window->draw(*elem->sprite);
	}
	
}

void Camera::moveObjects_1stExcluded(sf::Sprite* Excluded, const float& dt, sf::Vector2f speed)
{
	this->graphicsData->backGroundMapped->sprite->move(dt * speed.x, dt * speed.y);
	for (auto *elem : this->AllSpritesMapped)
		if (elem->sprite != Excluded)
			elem->sprite->move(dt * speed.x, dt * speed.y);
}
