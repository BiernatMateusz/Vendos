#ifndef ITEM_STORAGE_H
#define ITEM_STORAGE_H

#include <SFML/Window.hpp>
#include "TextureData.h"

#include "slot.h"

class item;

class ItemStorage
{
public:
    virtual ~ItemStorage() = default;

    virtual bool isUsable(int x, int y) const = 0;
    virtual slot& getSlotRef(int x, int y) = 0;

    virtual sf::Vector2i size() const = 0;
    virtual void setUsable(int x, int y)=0;
    virtual void setType(int x, int y, typeOfSlot type) = 0;
    virtual void setSlot(int x, int y, std::unique_ptr<item>) = 0;
    virtual const int& getFirstLayer_Y() const=0;
    virtual void resizeVector() = 0;

    virtual const std::vector<int>& getOrderOfSearch() const = 0;
    virtual void setOrderOfSearch(std::initializer_list<int> order) = 0;

    virtual bool transferItem(sf::Vector2i from, ItemStorage& target, sf::Vector2i to) = 0;

    virtual bool haveItems(ItemNames ItemName, int ammount) = 0;
    virtual void removeItem(ItemNames ItemName, int ammount) = 0;
    virtual void addItem(std::unique_ptr<item> Item) = 0;

    virtual void render() = 0;
    virtual void renderBackground() = 0;
    virtual void drawBackground(int x, int y, bool highlighted) = 0;

};

#endif // !ITEM_STORAGE_H