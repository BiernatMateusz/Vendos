#ifndef ITEMANDITSPOS_H
#define ITEMANDITSPOS_H

#include "StructuresOfData.h"
#include "item.h"



class itemAndItsPosition
{
private:
	typeOfItemArea type{ typeOfItemArea::PickAndPlace };
	item* itemPtr{};
public:
	//constructors //destructors
	itemAndItsPosition();
	itemAndItsPosition(item* ItemPtr, typeOfItemArea Type);
	itemAndItsPosition(const itemAndItsPosition&copyFrom);
	itemAndItsPosition(itemAndItsPosition&& copyFrom) noexcept;
	itemAndItsPosition& operator=(const itemAndItsPosition& copyFrom);
	itemAndItsPosition& operator=(itemAndItsPosition&& copyFrom) noexcept;

	~itemAndItsPosition();

	//Setters//geters
	void setItemPtr(item* ItemPtr);
	void setPosition(sf::Vector2f pos);
	void setType(typeOfItemArea Type);
	
	item* getItemPtr();
	item*& getItemPtrAdress();
	const sf::Vector2f getPosition() const;
	const typeOfItemArea getType() const;

	void drawItem();

};

#endif // !ITEMANDITSPOS_H