#include <stdio.h>
#include <string.h>
#include "trader.h"
#include "item.h"
#include "inventory.h"
#include <stdlib.h> 
#include <time.h>   


// Display the merchant's inventory
void displayMerchantInventory(MerchantInventory* inventory, float multiplier) {
    if (inventory == NULL) {
        printf("Merchant inventory is NULL.\n");
        return;
    }

    int id = 1;

    printf("\n--- Merchant Inventory ---\n");

    // Display weapons
    for (int i = 0; i < inventory->weaponCount; i++) {
        printf("ID: %d | Type: Weapon | Name: %s | Physical Attack: %d | Magic Attack: %d | Range Attack: %d | Buy Price: %.2f | Sell Price: %.2f\n",
            id++,
            inventory->weapons[i].name,
            inventory->weapons[i].physicalAttack,
            inventory->weapons[i].magicAttack,
            inventory->weapons[i].rangeAttack,
            inventory->weapons[i].buyPrice * multiplier,
            inventory->weapons[i].sellPrice * multiplier);
    }

    // Display armors
    for (int i = 0; i < inventory->armorCount; i++) {
        printf("ID: %d | Type: Armor | Name: %s | Physical Defence: %d | Magic Defence: %d | Health Boost: %d | Buy Price: %.2f | Sell Price: %.2f\n",
            id++,
            inventory->armors[i].name,
            inventory->armors[i].physicalDefence,
            inventory->armors[i].magicDefence,
            inventory->armors[i].healthBoost,
            inventory->armors[i].buyPrice * multiplier,
            inventory->armors[i].sellPrice * multiplier);
    }

    // Display potions
    for (int i = 0; i < inventory->potionCount; i++) {
        printf("ID: %d | Type: Potion | Name: %s | Health Restore: %d | Mana Restore: %d | Energy Restore: %d | Buy Price: %.2f | Sell Price: %.2f\n",
            id++,
            inventory->potions[i].name,
            inventory->potions[i].healthRestore,
            inventory->potions[i].manaRestore,
            inventory->potions[i].energyRestore,
            inventory->potions[i].buyPrice * multiplier,
            inventory->potions[i].sellPrice * multiplier);
    }

    // Display books
    for (int i = 0; i < inventory->bookCount; i++) {
        printf("ID: %d | Type: Book | Name: %s | Health Boost: %d | Mana Boost: %d | Energy Boost: %d | Speed Boost: %d | Buy Price: %.2f | Sell Price: %.2f\n",
            id++,
            inventory->books[i].name,
            inventory->books[i].healthBoost,
            inventory->books[i].manaBoost,
            inventory->books[i].energyBoost,
            inventory->books[i].speedBoost,
            inventory->books[i].buyPrice * multiplier,
            inventory->books[i].sellPrice * multiplier);
    }

    printf("\nEnter the ID of the item for buy/sell or 0 to cancel.\n");
}

// Buy an item
void buyItem(Character* player, MerchantInventory* merchantInventory, float multiplier) {
    int id;

    // Display merchant's inventory
    displayMerchantInventory(merchantInventory, multiplier);

    printf("\nEnter the ID of the item you want to buy (or 0 to cancel): ");
    scanf_s("%d", &id);

    if (id == 0) {
        printf("Exiting the buy menu.\n");
        return;
    }

    // Iterate through merchant's weapons
    for (int i = 0; i < merchantInventory->weaponCount; i++) {
        if (merchantInventory->weapons[i].id == id) {
            float finalPrice = merchantInventory->weapons[i].buyPrice * multiplier;
            if (player->gold >= finalPrice) {
                if (addWeapon(&player->inventory, merchantInventory->weapons[i])) {
                    player->gold -= finalPrice;
                    printf("You bought %s for %.2f gold.\n", merchantInventory->weapons[i].name, finalPrice);
                }
                else {
                    printf("Your inventory is full for weapons.\n");
                }
                return;
            }
            else {
                printf("You don't have enough gold to buy %s.\n", merchantInventory->weapons[i].name);
                return;
            }
        }
    }

    // Add similar checks for armor, potions, and books
    // ...

    printf("Invalid ID or item not found.\n");
}

// Sell an item
void sellItem(Character* player, MerchantInventory* merchantInventory, float multiplier) {
    int id;

    // Display player's inventory
    displayInventory(&player->inventory, 0, 1.0f);

    printf("\nEnter the ID of the item you want to sell (or 0 to cancel): ");
    scanf_s("%d", &id);

    if (id == 0) {
        printf("Exiting the sell menu.\n");
        return;
    }

    // Iterate through player's inventory
    if (player->inventory.equippedWeapon.id == id) {
        float finalPrice = player->inventory.equippedWeapon.sellPrice * multiplier;
        if (removeWeapon(&player->inventory, player->inventory.equippedWeapon.name)) {
            player->gold += finalPrice;
            printf("You sold %s for %.2f gold.\n", player->inventory.equippedWeapon.name, finalPrice);
        }
    }

    // Add similar checks for armor, potions, and books
    // ...

    printf("Invalid ID or item not found.\n");
}




void initializeMerchantInventory(MerchantInventory* inventory) {
    // Set all bytes of the inventory structure to 0 (initialize it with default values)
    memset(inventory, 0, sizeof(MerchantInventory));
    // Seed the random number generator with the current time to ensure randomness
    srand((unsigned)time(NULL));

    // Weapons Section
    int weaponSize = sizeof(weapons) / sizeof(weapons[0]); // Calculate the number of weapons available
    if (weaponSize > 0) { // Check if there are any weapons available
        inventory->weaponCount = 5; // Assign the merchant to carry 5 weapons
        for (int i = 0; i < inventory->weaponCount; i++) {
            int randomWeaponIndex = rand() % weaponSize; // Generate a random index within weapon size
            inventory->weapons[i] = weapons[randomWeaponIndex]; // Assign a random weapon to the merchant's inventory
        }
    }

    // Armors Section
    int armorSize = sizeof(armors) / sizeof(armors[0]); // Calculate the number of armors available
    if (armorSize > 0) { // Check if there are any armors available
        inventory->armorCount = 6; // Assign the merchant to carry 6 armors
        for (int i = 0; i < inventory->armorCount; i++) {
            int randomArmorIndex = rand() % armorSize; // Generate a random index within armor size
            inventory->armors[i] = armors[randomArmorIndex]; // Assign a random armor to the merchant's inventory
        }
    }

    // Potions Section
    int potionSize = sizeof(potions) / sizeof(potions[0]); // Calculate the number of potions available
    if (potionSize > 0) { // Check if there are any potions available
        inventory->potionCount = 0; // Initialize potion count to 0

        // Assign 5 small potions to the merchant's inventory
        for (int i = 0; i < 5; i++) {
            inventory->potions[inventory->potionCount++] = potions[0]; // Add a small potion
        }

        // Assign 3 medium potions to the merchant's inventory
        for (int i = 0; i < 3; i++) {
            inventory->potions[inventory->potionCount++] = potions[1]; // Add a medium potion
        }

        // Assign 1 large potion to the merchant's inventory
        inventory->potions[inventory->potionCount++] = potions[2]; // Add a large potion
    }

    // Books Section
    int bookSize = sizeof(books) / sizeof(books[0]); // Calculate the number of books available
    if (bookSize > 0) { // Check if there are any books available
        inventory->bookCount = 0; // Initialize book count to 0

        // Add one old book to the inventory
        inventory->books[inventory->bookCount++] = books[0];
        // Add one new book to the inventory
        inventory->books[inventory->bookCount++] = books[1];
        // Add one legendary book to the inventory
        inventory->books[inventory->bookCount++] = books[2];
    }
}
