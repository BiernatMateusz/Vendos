#include "HoveringWithMouse.h"

HoveringWithMouse::HoveringWithMouse(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<TilesOnMap*>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Tile = Tile;

	this->numberOfItems.setFont(this->graphicsData->font);
	this->numberOfItems.setFillColor(sf::Color::Black);
	this->numberOfItems.setStyle(sf::Text::Bold);
}

void HoveringWithMouse::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	coordsOfActualTile = this->getActualTileCords(AllKeys);
	updateAndRenderTileText(AllKeys);
	
}

void HoveringWithMouse::render()
{
	if (this->tileHovered!=nullptr)
		this->graphicsData->window->draw(this->numberOfItems);
}

sf::Vector2i HoveringWithMouse::getActualTileCords(const std::map<std::string, button*>& AllKeys)
{
	return { AllKeys.at("LeftMouse")->mouseTileActualGet().x,AllKeys.at("LeftMouse")->mouseTileActualGet().y };
}

void HoveringWithMouse::updateDisplayedTxt()
{
	tileHovered = this->Tile->at(this->coordsOfActualTile.x).at(this->coordsOfActualTile.y);
	
	if (tileHovered != nullptr)
		this->displayedTxt = std::to_string(tileHovered->getRemainingDurability()) + "/" + std::to_string(tileHovered->getMaxDurability());
	else
		this->displayedTxt = "";
}

void HoveringWithMouse::updateAndRenderTileText(const std::map<std::string, button*>& AllKeys)
{
	updateDisplayedTxt();

	this->numberOfItems.setString(this->displayedTxt);
	this->numberOfItems.setCharacterSize(16);

	this->numberOfItems.setFont(this->graphicsData->font);

	this->numberOfItems.setPosition(
		AllKeys.at("LeftMouse")->mousePosGet().x+15, //- numberOfItems.getGlobalBounds().width
		AllKeys.at("LeftMouse")->mousePosGet().y+15);
	
}
