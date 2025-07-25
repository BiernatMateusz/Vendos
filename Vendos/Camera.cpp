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
	
	if (!graphicsData->EntitiesSprite->empty())
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

void Camera::initPlayer(CameraSprite* cameraSprite)
{
	;// this->Player = cameraSprite;
}

void Camera::initGraphicsBasics(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->BackGround = graphicsData->backGroundMapped->getSprite();
}

void Camera::cameraSpriteJoin()
{
	if (!graphicsData->EntitiesSpriteMapped->empty())
		AllSpritesMapped.insert(std::end(AllSpritesMapped), std::begin(*graphicsData->EntitiesSpriteMapped), std::end(*graphicsData->EntitiesSpriteMapped));

	if (!graphicsData->TilesSpriteMapped->empty())
		AllSpritesMapped.insert(std::end(AllSpritesMapped), std::begin(*graphicsData->TilesSpriteMapped), std::end(*graphicsData->TilesSpriteMapped));

	if (!graphicsData->ItemsThrownSpriteMapped->empty())
		AllSpritesMapped.insert(std::end(AllSpritesMapped), std::begin(*graphicsData->ItemsThrownSpriteMapped), std::end(*graphicsData->ItemsThrownSpriteMapped));

	this->AllSpritesMapped.erase
	(
		std::remove_if(
			this->AllSpritesMapped.begin(),
			this->AllSpritesMapped.end(),
			[&](auto& AllSpritesMapped)
			{
				return (AllSpritesMapped == nullptr) ? true : false;
			}
		), this->AllSpritesMapped.end()
	);

	this->AllSpritesMapped.shrink_to_fit();
			
}

//Functions

void Camera::updateAllSpritesVecMapped(EquipmentData* equipmentData)
{
	this->AllSpritesMapped.clear();
	
	cameraSpriteJoin();

	sortVectorMapped();

	equipmentData->needToUpdateCameraAllSpr = false;

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

void Camera::moveObjects_PlayerExcluded(CameraSprite* Excluded, const float& dt, sf::Vector2f speed)
{
	this->graphicsData->backGroundMapped->sprite->move(dt * speed.x, dt * speed.y);
	for (auto *elem : this->AllSpritesMapped)
		if (elem != Excluded)
			elem->sprite->move(dt * speed.x, dt * speed.y);
}
