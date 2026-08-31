#include "HoveringWithMouse.h"

HoveringWithMouse::HoveringWithMouse(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<std::unique_ptr<TilesOnMap>>>* Tile)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Tile = Tile;

	this->numberOfItems.setFont(this->graphicsData->font);
	this->numberOfItems.setFillColor(sf::Color::Black);
	this->numberOfItems.setStyle(sf::Text::Bold);
}

void HoveringWithMouse::update(const float& dt, const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	coordsOfActualTile = this->getActualTileCords(AllKeys);
	updateAndRenderTileText(AllKeys);
	
}

void HoveringWithMouse::render()
{
	if (this->tileHovered!=nullptr)
		this->graphicsData->window->draw(this->numberOfItems);
}

sf::Vector2i HoveringWithMouse::getActualTileCords(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	return { AllKeys.at(inputAction::LMouse)->mouseTileActualGet().x,AllKeys.at(inputAction::LMouse)->mouseTileActualGet().y };
}

void HoveringWithMouse::updateDisplayedTxt()
{
	tileHovered = this->Tile->at(this->coordsOfActualTile.x).at(this->coordsOfActualTile.y).get();
	
	if (tileHovered != nullptr)
		this->displayedTxt = std::to_string(tileHovered->getRemainingDurability()) + "/" + std::to_string(tileHovered->getMaxDurability());
	else
		this->displayedTxt = "";
}

void HoveringWithMouse::updateAndRenderTileText(const std::unordered_map<inputAction, std::unique_ptr<button>>& AllKeys)
{
	updateDisplayedTxt();

	this->numberOfItems.setString(this->displayedTxt);
	this->numberOfItems.setCharacterSize(16);

	this->numberOfItems.setFont(this->graphicsData->font);

	this->numberOfItems.setPosition(
		AllKeys.at(inputAction::LMouse)->mousePosGet().x+15, //- numberOfItems.getGlobalBounds().width
		AllKeys.at(inputAction::LMouse)->mousePosGet().y+15);
	
}
