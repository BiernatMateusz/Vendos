#ifndef EQUIPMENT_INPUT_CONTROLER
#define EQUIPMENT_INPUT_CONTROLER

#include "inputAction.h"
#include <unordered_map>
#include "EquipmentData.h"
#include "StructuresOfData.h"
#include <memory>

class EquipmentInputControler
{
public:
    EquipmentInputControler();

    void update(const std::unordered_map<inputAction, std::unique_ptr<button>>& keys);

    bool wantsToggleEq() const;
    bool wantsOpenChest() const;
    int  selectedSlot() const;

    std::optional<sf::Vector2i> clickedTile() const;

private:
    int requestedSlot = -1;
    bool toggleEq = false;
    bool openChest = false;

    std::optional<sf::Vector2i> tileClicked;

};

#endif