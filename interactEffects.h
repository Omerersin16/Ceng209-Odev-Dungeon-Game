#ifndef INTERACT_EFFECTS_H
#define INTERACT_EFFECTS_H

#include "character.h"
#include "inventory.h"
#include "Room.h"
#include "Trader.h"

// Increases the player's magic attack damage by a fixed amount
void handleMagicDamageIncrease(Character* player);

// Increases the player's physical attack damage by a fixed amount
void handlePhysicalDamageIncrease(Character* player);

// Increases the player's range attack damage by a fixed amount
void handleRangeDamageIncrease(Character* player);

// Increases the player's energy and adjusts the maximum energy limit if needed
void handleEnergyIncrease(Character* player);

// Increases the player's mana and adjusts the maximum mana limit if needed
void handleManaIncrease(Character* player);

// Increases the player's speed and adjusts the maximum speed limit if needed
void handleSpeedIncrease(Character* player);

// Processes an interaction command in the current room
// Takes the room details, player character, and optionally inventory and merchant details
void handleInteractCommand(Room* currentRoom, Character* player, Inventory* inventory, MerchantInventory* merchantInventory);


// Handles a specific event effect based on the event index
// Updates the player's stats or inventory as needed
void handleEventEffect(int eventIndex, Character* player, Inventory* inventory);

#endif
