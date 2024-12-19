#ifndef TRADER_H
#define TRADER_H

#include "item.h"
#include "character.h"
#include "inventory.h"

// Structure representing the merchant's inventory
typedef struct {
    Weapon weapons[15];   // Array to store the weapons the merchant owns
    int weaponCount;      // Number of weapons the merchant has

    Armor armors[15];     // Array to store the armors the merchant owns
    int armorCount;       // Number of armors the merchant has

    Potion potions[20];   // Array to store the potions the merchant owns
    int potionCount;      // Number of potions the merchant has

    Book books[10];       // Array to store the books the merchant owns
    int bookCount;        // Number of books the merchant has
} MerchantInventory;

// Function prototypes for merchant-related operations

/**
 *  Initializes the merchant's inventory with default items.
 *  inventory Pointer to the MerchantInventory to initialize.
 */
void initializeMerchantInventory(MerchantInventory* inventory);

/**
 *  Allows the player to buy an item from the merchant.
 *  player Pointer to the player's Character structure.
 *  merchantInventory Pointer to the MerchantInventory containing items for sale.
 *  multiplier Float multiplier for adjusting item prices (e.g., discounts or surcharges).
 */
void buyItem(Character* player, MerchantInventory* merchantInventory, float multiplier);

/**
 *  Allows the player to sell an item to the merchant.
 *  player Pointer to the player's Character structure.
 *  merchantInventory Pointer to the MerchantInventory where the items will be sold.
 *  multiplier Float multiplier for adjusting item prices (e.g., discounts or surcharges).
 */
void sellItem(Character* player, MerchantInventory* merchantInventory, float multiplier);

#endif 
