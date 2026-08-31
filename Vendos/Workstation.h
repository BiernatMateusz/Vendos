#ifndef WORK_STATION_H
#define WORK_STATION_H

#include "StructuresOfData.h"
#include "ItemStorage.h"



class Workstation : public ItemStorage
{
private:
	const sf::Vector2i sizeOfArea{ 9, 10 };
	int firstLayerFromDown{0};
	sf::Sprite BackGroundSquare{};
	sf::Sprite BackGroundSquareHighlighted{};
	std::vector<int>orderOfSearchForEmptySpace;

	std::vector < std::vector<slot>> slots{};
public:
	Workstation()=default;
	Workstation(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames name, std::initializer_list<int>order);
	virtual ~Workstation()=default;

	void initBackground(TextureNames name);
	void initWorkstation(GraphicsData* graphicsData, EquipmentData* equipmentData, TextureNames name);
	void resizeVector() override;

	virtual void update(const float& dt, const std::map<std::string, button*>& AllKeys) {};
	void render();
	void renderBackground();

	bool isUsable(int x, int y) const override;

	sf::Vector2i size() const override;
	void setUsable(int x, int y);
	void setType(int x, int y, typeOfSlot type);
	void setSlot(int x, int y, std::unique_ptr<item>);
	void setFirstLayer_Y(int Layer);
	const int& getFirstLayer_Y() const;
	ItemStorage* getItemArea();

	const std::vector<int>& getOrderOfSearch() const override;
	void setOrderOfSearch(std::initializer_list<int> order) override;

	bool haveItems(ItemNames ItemName, int ammount);
	void removeItem(ItemNames ItemName, int ammount);
	void addItem(std::unique_ptr<item> Item);

	slot& getSlotRef(int x, int y);

	bool transferItem(sf::Vector2i from, ItemStorage& target, sf::Vector2i to);
	
	void drawBackground(int x, int y, bool highlighted);

protected:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	std::unique_ptr<sf::Sprite>background{};
	
};

#endif // !WORK_STATION_H