#ifndef SLOT_H
#define SLOT_H

#include "item.h"

class slot
{
private:
	bool usable{};
	typeOfSlot slotType{ typeOfSlot::None };
	std::unique_ptr<item>itemPtr;

public:
	explicit operator bool() const;


	void setUsable(bool isUsable);
	bool isUsable() const;

	void setSlotType(typeOfSlot type);
	typeOfSlot getType() const;

	void setItemPtr(std::unique_ptr<item> newItem);
	item* get() const;

	void swapItems(slot& otherItem);
	void swapItems(std::unique_ptr<item> otherItem);

	void clear();

	std::unique_ptr<item> take();
	

};

#endif // !SLOT_H