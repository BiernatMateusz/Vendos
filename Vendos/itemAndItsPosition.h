#ifndef ITEMANDITSPOS_H
#define ITEMANDITSPOS_H

#include "StructuresOfData.h"
#include "item.h"



class itemAndItsPosition
{
private:
	typeOfItemArea type{ typeOfItemArea::PickAndPlace };
public:
	item* itemPtr{};
	//constructors //destructors
	itemAndItsPosition();
	itemAndItsPosition(item* ItemPtr, typeOfItemArea Type);
	itemAndItsPosition(const itemAndItsPosition&copyFrom);
	itemAndItsPosition(itemAndItsPosition&& copyFrom);
	itemAndItsPosition& operator=(const itemAndItsPosition& copyFrom);
	itemAndItsPosition& operator=(itemAndItsPosition&& copyFrom);

	~itemAndItsPosition();

	//Setters//geters
	void setItemPtr(item* ItemPtr);
	void setPosition(sf::Vector2f pos);
	void setType(typeOfItemArea Type);
	
	item* getItemPtr();
	const sf::Vector2f getPosition() const;
	const typeOfItemArea getType() const;

	void drawItem();

};

#endif // !ITEMANDITSPOS_H