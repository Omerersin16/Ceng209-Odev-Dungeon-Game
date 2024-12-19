#include "inventory.h"
#include <stdio.h>
#include <string.h>
#include "Trader.h"

// Initializes the starting inventory for the player based on the chosen class
void initializeStartingInventory(Inventory* inventory, const char* classType) {
    memset(inventory, 0, sizeof(Inventory)); // Reset inventory to zero

    // Assign initial weapon and armor based on class type
    if (strcmp(classType, "Knight") == 0) {
        inventory->equippedWeapon = weapons[0]; // Knight starts with the first weapon
        inventory->equippedArmor = armors[0];  // Knight starts with the first armor
    }
    else if (strcmp(classType, "Mage") == 0) {
        inventory->equippedWeapon = weapons[5]; // Mage starts with the sixth weapon
        inventory->equippedArmor = armors[1];  // Mage starts with the second armor
    }
    else if (strcmp(classType, "Archer") == 0) {
        inventory->equippedWeapon = weapons[10]; // Archer starts with the eleventh weapon
        inventory->equippedArmor = armors[2];   // Archer starts with the third armor
    }

    // Add starting potions
    inventory->smallPotions[0] = potions[0];
    inventory->smallPotionCount = 1;

    inventory->mediumPotions[0] = potions[3];
    inventory->mediumPotionCount = 1;

    inventory->largePotions[0] = potions[6];
    inventory->largePotionCount = 1;

    // Add the first health book
    inventory->healthBook = books[0];
}

// Adds a weapon to the player's inventory
int addWeapon(Inventory* inventory, Weapon weapon) {
    // Check if there is space for a weapon
    if (strlen(inventory->equippedWeapon.name) == 0) {
        inventory->equippedWeapon = weapon;
        printf("Weapon equipped: %s\n", weapon.name);
        return 1;
    }
    if (strlen(inventory->extraWeapon.name) == 0) {
        inventory->extraWeapon = weapon;
        printf("Extra weapon added: %s\n", weapon.name);
        return 1;
    }
    printf("Cannot add more weapons. Inventory full.\n");
    return 0;
}

// Removes a weapon from the inventory by name
int removeWeapon(Inventory* inventory, const char* weaponName) {
    if (strcmp(inventory->equippedWeapon.name, weaponName) == 0) {
        memset(&inventory->equippedWeapon, 0, sizeof(Weapon)); // Clear the equipped weapon
        printf("Equipped weapon removed: %s\n", weaponName);
        return 1;
    }
    if (strcmp(inventory->extraWeapon.name, weaponName) == 0) {
        memset(&inventory->extraWeapon, 0, sizeof(Weapon)); // Clear the extra weapon
        printf("Extra weapon removed: %s\n", weaponName);
        return 1;
    }
    printf("Weapon not found in inventory: %s\n", weaponName);
    return 0;
}

// Adds an armor to the player's inventory
int addArmor(Inventory* inventory, Armor armor) {
    // Check if there is space for armor
    if (strlen(inventory->equippedArmor.name) == 0) {
        inventory->equippedArmor = armor;
        printf("Armor equipped: %s\n", armor.name);
        return 1;
    }
    if (strlen(inventory->extraArmor.name) == 0) {
        inventory->extraArmor = armor;
        printf("Extra armor added: %s\n", armor.name);
        return 1;
    }
    printf("Cannot add more armors. Inventory full.\n");
    return 0;
}

// Removes an armor from the inventory by name
int removeArmor(Inventory* inventory, const char* armorName) {
    if (strcmp(inventory->equippedArmor.name, armorName) == 0) {
        memset(&inventory->equippedArmor, 0, sizeof(Armor)); // Clear the equipped armor
        printf("Equipped armor removed: %s\n", armorName);
        return 1;
    }
    if (strcmp(inventory->extraArmor.name, armorName) == 0) {
        memset(&inventory->extraArmor, 0, sizeof(Armor)); // Clear the extra armor
        printf("Extra armor removed: %s\n", armorName);
        return 1;
    }
    printf("Armor not found in inventory: %s\n", armorName);
    return 0;
}

// Adds a potion to the player's inventory
int addPotion(Inventory* inventory, Potion potion) {
    if (strcmp(potion.name, "Small Health Potion") == 0) {
        if (inventory->smallPotionCount < 10) {
            inventory->smallPotions[inventory->smallPotionCount++] = potion;
            return 1;
        }
    }
    else if (strcmp(potion.name, "Medium Health Potion") == 0) {
        if (inventory->mediumPotionCount < 5) {
            inventory->mediumPotions[inventory->mediumPotionCount++] = potion;
            return 1;
        }
    }
    else if (strcmp(potion.name, "Large Health Potion") == 0) {
        if (inventory->largePotionCount < 3) {
            inventory->largePotions[inventory->largePotionCount++] = potion;
            return 1;
        }
    }
    printf("Cannot carry more potions of this type: %s\n", potion.name);
    return 0;
}

// Removes a potion from the inventory by name
int removePotion(Inventory* inventory, const char* potionName) {
    if (strcmp(potionName, "Small Health Potion") == 0 && inventory->smallPotionCount > 0) {
        inventory->smallPotionCount--;
        return 1;
    }
    if (strcmp(potionName, "Medium Health Potion") == 0 && inventory->mediumPotionCount > 0) {
        inventory->mediumPotionCount--;
        return 1;
    }
    if (strcmp(potionName, "Large Health Potion") == 0 && inventory->largePotionCount > 0) {
        inventory->largePotionCount--;
        return 1;
    }
    printf("You don't have any %s to remove!\n", potionName);
    return 0;
}

// Adds a book to the player's inventory
int addBook(Inventory* inventory, Book book) {
    if (strstr(book.name, "Health") && strlen(inventory->healthBook.name) == 0) {
        inventory->healthBook = book;
        printf("Health book added: %s\n", book.name);
        return 1;
    }
    if (strstr(book.name, "Mana") && strlen(inventory->manaBook.name) == 0) {
        inventory->manaBook = book;
        printf("Mana book added: %s\n", book.name);
        return 1;
    }
    if (strstr(book.name, "Energy") && strlen(inventory->energyBook.name) == 0) {
        inventory->energyBook = book;
        printf("Energy book added: %s\n", book.name);
        return 1;
    }
    if (strstr(book.name, "Speed") && strlen(inventory->speedBook.name) == 0) {
        inventory->speedBook = book;
        printf("Speed book added: %s\n", book.name);
        return 1;
    }
    printf("Cannot add more books. Inventory full or book type exists.\n");
    return 0;
}

// Removes a book from the inventory by name
int removeBook(Inventory* inventory, const char* bookName) {
    if (strcmp(inventory->healthBook.name, bookName) == 0) {
        memset(&inventory->healthBook, 0, sizeof(Book));
        printf("Health book removed: %s\n", bookName);
        return 1;
    }
    if (strcmp(inventory->manaBook.name, bookName) == 0) {
        memset(&inventory->manaBook, 0, sizeof(Book));
        printf("Mana book removed: %s\n", bookName);
        return 1;
    }
    if (strcmp(inventory->energyBook.name, bookName) == 0) {
        memset(&inventory->energyBook, 0, sizeof(Book));
        printf("Energy book removed: %s\n", bookName);
        return 1;
    }
    if (strcmp(inventory->speedBook.name, bookName) == 0) {
        memset(&inventory->speedBook, 0, sizeof(Book));
        printf("Speed book removed: %s\n", bookName);
        return 1;
    }
    printf("Book not found in inventory: %s\n", bookName);
    return 0;
}

// Displays the current inventory
#include <stdio.h>
#include <string.h>
#include "inventory.h"

void displayInventory(Inventory* inventory, int isMerchant, float multiplier) {
    printf("\n--- Inventory ---\n");

    // Display equipped weapon
    if (strlen(inventory->equippedWeapon.name) > 0) {
        printf("Equipped Weapon: %s (Physical: %d, Magic: %d, Range: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->equippedWeapon.name,
            inventory->equippedWeapon.physicalAttack,
            inventory->equippedWeapon.magicAttack,
            inventory->equippedWeapon.rangeAttack,
            inventory->equippedWeapon.buyPrice * multiplier,
            inventory->equippedWeapon.sellPrice * multiplier);
    }
    else {
        printf("No equipped weapon.\n");
    }

    // Display extra weapon
    if (strlen(inventory->extraWeapon.name) > 0) {
        printf("Extra Weapon: %s (Physical: %d, Magic: %d, Range: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->extraWeapon.name,
            inventory->extraWeapon.physicalAttack,
            inventory->extraWeapon.magicAttack,
            inventory->extraWeapon.rangeAttack,
            inventory->extraWeapon.buyPrice * multiplier,
            inventory->extraWeapon.sellPrice * multiplier);
    }
    else {
        printf("No extra weapon.\n");
    }

    // Display equipped armor
    if (strlen(inventory->equippedArmor.name) > 0) {
        printf("Equipped Armor: %s (Physical Def: %d, Magic Def: %d, Health Boost: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->equippedArmor.name,
            inventory->equippedArmor.physicalDefence,
            inventory->equippedArmor.magicDefence,
            inventory->equippedArmor.healthBoost,
            inventory->equippedArmor.buyPrice * multiplier,
            inventory->equippedArmor.sellPrice * multiplier);
    }
    else {
        printf("No equipped armor.\n");
    }

    // Display extra armor
    if (strlen(inventory->extraArmor.name) > 0) {
        printf("Extra Armor: %s (Physical Def: %d, Magic Def: %d, Health Boost: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->extraArmor.name,
            inventory->extraArmor.physicalDefence,
            inventory->extraArmor.magicDefence,
            inventory->extraArmor.healthBoost,
            inventory->extraArmor.buyPrice * multiplier,
            inventory->extraArmor.sellPrice * multiplier);
    }
    else {
        printf("No extra armor.\n");
    }

    // Display potions
    printf("\nPotions:\n");
    for (int i = 0; i < inventory->smallPotionCount; i++) {
        printf(" - Small Potion: %s (Health Restore: %d, Mana Restore: %d, Energy Restore: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->smallPotions[i].name,
            inventory->smallPotions[i].healthRestore,
            inventory->smallPotions[i].manaRestore,
            inventory->smallPotions[i].energyRestore,
            inventory->smallPotions[i].buyPrice * multiplier,
            inventory->smallPotions[i].sellPrice * multiplier);
    }
    for (int i = 0; i < inventory->mediumPotionCount; i++) {
        printf(" - Medium Potion: %s (Health Restore: %d, Mana Restore: %d, Energy Restore: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->mediumPotions[i].name,
            inventory->mediumPotions[i].healthRestore,
            inventory->mediumPotions[i].manaRestore,
            inventory->mediumPotions[i].energyRestore,
            inventory->mediumPotions[i].buyPrice * multiplier,
            inventory->mediumPotions[i].sellPrice * multiplier);
    }
    for (int i = 0; i < inventory->largePotionCount; i++) {
        printf(" - Large Potion: %s (Health Restore: %d, Mana Restore: %d, Energy Restore: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->largePotions[i].name,
            inventory->largePotions[i].healthRestore,
            inventory->largePotions[i].manaRestore,
            inventory->largePotions[i].energyRestore,
            inventory->largePotions[i].buyPrice * multiplier,
            inventory->largePotions[i].sellPrice * multiplier);
    }

    // Display books
    printf("\nBooks:\n");
    if (strlen(inventory->healthBook.name) > 0) {
        printf(" - Health Book: %s (Health Boost: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->healthBook.name,
            inventory->healthBook.healthBoost,
            inventory->healthBook.buyPrice * multiplier,
            inventory->healthBook.sellPrice * multiplier);
    }
    if (strlen(inventory->manaBook.name) > 0) {
        printf(" - Mana Book: %s (Mana Boost: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->manaBook.name,
            inventory->manaBook.manaBoost,
            inventory->manaBook.buyPrice * multiplier,
            inventory->manaBook.sellPrice * multiplier);
    }
    if (strlen(inventory->energyBook.name) > 0) {
        printf(" - Energy Book: %s (Energy Boost: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->energyBook.name,
            inventory->energyBook.energyBoost,
            inventory->energyBook.buyPrice * multiplier,
            inventory->energyBook.sellPrice * multiplier);
    }
    if (strlen(inventory->speedBook.name) > 0) {
        printf(" - Speed Book: %s (Speed Boost: %d, Buy Price: %.2f, Sell Price: %.2f)\n",
            inventory->speedBook.name,
            inventory->speedBook.speedBoost,
            inventory->speedBook.buyPrice * multiplier,
            inventory->speedBook.sellPrice * multiplier);
    }
}
