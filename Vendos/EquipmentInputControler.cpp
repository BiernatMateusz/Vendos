#include "EquipmentInputControler.h"

EquipmentInputControler::EquipmentInputControler()
{
    ;
}

void EquipmentInputControler::update(const std::unordered_map<inputAction, std::unique_ptr<button>>& keys)
{
	toggleEq = false;
    openChest = false;
    requestedSlot = -1;
    tileClicked.reset();

    if (keys.at(inputAction::Interact)->oneSignalButtonPressed())
        toggleEq = true;

    if (keys.at(inputAction::RMouse)->oneSignalButtonPressed())
    {
        openChest = true;
        tileClicked = keys.at(inputAction::RMouse)->mouseTileGet();
    }

    if (keys.at(inputAction::Slot1)->oneSignalButtonPressed()) requestedSlot = 0;
    if (keys.at(inputAction::Slot2)->oneSignalButtonPressed()) requestedSlot = 1;
    if (keys.at(inputAction::Slot3)->oneSignalButtonPressed()) requestedSlot = 2;
    if (keys.at(inputAction::Slot4)->oneSignalButtonPressed()) requestedSlot = 3;
    if (keys.at(inputAction::Slot5)->oneSignalButtonPressed()) requestedSlot = 4;
    if (keys.at(inputAction::Slot6)->oneSignalButtonPressed()) requestedSlot = 5;
    if (keys.at(inputAction::Slot7)->oneSignalButtonPressed()) requestedSlot = 6;
    if (keys.at(inputAction::Slot8)->oneSignalButtonPressed()) requestedSlot = 7;
    if (keys.at(inputAction::Slot9)->oneSignalButtonPressed()) requestedSlot = 8;
    if (keys.at(inputAction::Slot0)->oneSignalButtonPressed()) requestedSlot = 9;

}

bool EquipmentInputControler::wantsToggleEq() const
{
    return toggleEq;
}

bool EquipmentInputControler::wantsOpenChest() const
{
    return openChest;
}

int EquipmentInputControler::selectedSlot() const
{
    return requestedSlot;
}

std::optional<sf::Vector2i> EquipmentInputControler::clickedTile() const
{
    return tileClicked;
}
