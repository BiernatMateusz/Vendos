#ifndef WORK_STATION_H
#define WORK_STATION_H

#include "StructuresOfData.h"

class Workstation
{
private:
public:
	Workstation() {};
	Workstation(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string nameOfTxt);
	~Workstation();

	void initBackground(std::string name);

	virtual void updateStorageArea(const float& dt, const std::map<std::string, button*>& AllKeys) {};
	void render();
protected:
	GraphicsData* graphicsData{};
	EquipmentData* equipmentData{};

	std::vector<sf::Sprite*>* backgroundItems{};
	sf::Sprite* background{};

};

#endif // !WORK_STATION_H