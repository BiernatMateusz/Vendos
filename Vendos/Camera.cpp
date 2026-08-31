#include "Camera.h"
#include "ThrownItems.h"

//Operators
bool operator>(const sf::Sprite &x,const sf::Sprite &y)
{
	return (y.getPosition().y ) > (x.getPosition().y);
}

//Constructors
Camera::Camera(GraphicsData *graphicsData)
{
	initGraphicsBasics(graphicsData);

	cameraSpriteJoin();
	sortVectorMapped();
}
//Destructors
Camera::~Camera()
{

}

void Camera::initPlayer(CameraSprite cameraSprite)
{
	;// this->Player = cameraSprite;
}

void Camera::initGraphicsBasics(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
}

void Camera::cameraSpriteJoin()
{
	AllSpritesMapped.clear();

	auto appendPtrs = [this](const std::vector<CameraSprite*>& vec)
		{
			for (CameraSprite* sprite : vec)
			{
				if (sprite && sprite->isActive())
					AllSpritesMapped.push_back(sprite);
			}
		};

	appendPtrs(graphicsData->EntitiesSpriteMapped);
	appendPtrs(graphicsData->TilesSpriteMapped);
	appendThrownItems();
			
}

void Camera::appendThrownItems()
{
	if (graphicsData->thrownItems)
		for (auto& item : graphicsData->thrownItems->getItems())
		{
			if (item && item->getItem())
			{
				CameraSprite& spr = item->getItem()->cameraSpriteOfItem;

				if (spr.isActive())
					AllSpritesMapped.push_back(&spr);
			}
		}
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
		[](CameraSprite*& y, CameraSprite*& x) -> bool
		{
			if (y->getSprite().getPosition().y + y->getDistance() != x->getSprite().getPosition().y + x->getDistance())
				return y->getSprite().getPosition().y + y->getDistance() < x->getSprite().getPosition().y + x->getDistance();
			else 
				return y->getSprite().getPosition().x < x->getSprite().getPosition().x;
		}
	);
	
	
}

void Camera::render(sf::RenderWindow* window)
{
	window->draw(this->graphicsData->backGroundMapped.getSprite());

	for (auto &elem : AllSpritesMapped)
		window->draw(elem->getSprite());

	//window->draw(this->graphicsData->backGroundMapped.getSprite());

	//std::unordered_map<const sf::Texture*, sf::VertexArray> batches;

	//for (auto& elem : AllSpritesMapped)
	//{
	//	sf::Sprite& sprite = elem->getSprite();
	//	const sf::Texture* texture = sprite.getTexture();
	//	if (!texture) continue;

	//	// pobierz batch dla tej tekstury
	//	auto& batch = batches[texture];
	//	batch.setPrimitiveType(sf::Quads);

	//	std::size_t start = batch.getVertexCount();
	//	batch.resize(start + 4);

	//	sf::Vertex* quad = &batch[start];

	//	sf::Vector2f pos = sprite.getPosition();
	//	sf::FloatRect bounds = sprite.getGlobalBounds();
	//	sf::IntRect uv = sprite.getTextureRect();

	//	quad[0].position = { pos.x, pos.y };
	//	quad[1].position = { pos.x + bounds.width, pos.y };
	//	quad[2].position = { pos.x + bounds.width, pos.y + bounds.height };
	//	quad[3].position = { pos.x, pos.y + bounds.height };

	//	quad[0].texCoords = { (float)uv.left, (float)uv.top };
	//	quad[1].texCoords = { (float)(uv.left + uv.width), (float)uv.top };
	//	quad[2].texCoords = { (float)(uv.left + uv.width), (float)(uv.top + uv.height) };
	//	quad[3].texCoords = { (float)uv.left, (float)(uv.top + uv.height) };
	//}

	//// render wszystkich batchy
	//for (auto& [texture, batch] : batches)
	//{
	//	sf::RenderStates states;
	//	states.texture = texture;

	//	window->draw(batch, states);
	//}

}

void Camera::moveObjects_PlayerExcluded(CameraSprite& Excluded, const float& dt, sf::Vector2f speed)
{
	this->graphicsData->backGroundMapped.getSprite().move(dt * speed.x, dt * speed.y);
	for (auto *elem : this->AllSpritesMapped)
		if (elem != &Excluded)
			elem->getSprite().move(dt * speed.x, dt * speed.y);
}
