#include "item.h"
#include <stdio.h>
#include <string.h>
#include "Inventory.h"
#include "Character.h"

// Weapons list
const Weapon weapons[] = {
    {1, "Starting Sword", 10, 0, 0, 20.0f, 10.0f},
    {2, "Iron Sword", 20, 0, 0, 40.0f, 20.0f},
    {3, "Steel Sword", 30, 0, 0, 60.0f, 30.0f},
    {4, "Black Sword", 50, 0, 0, 100.0f, 50.0f},
    {5, "Excalibur", 100, 0, 0, 200.0f, 100.0f},
    {6, "Starting Staff", 0, 10, 0, 20.0f, 10.0f},
    {7, "Willow Staff", 0, 20, 0, 40.0f, 20.0f},
    {8, "White Staff", 0, 30, 0, 60.0f, 30.0f},
    {9, "Black Staff", 0, 50, 0, 100.0f, 50.0f},
    {10, "Merlin's Staff", 0, 100, 0, 200.0f, 100.0f},
    {11, "Starting Bow", 0, 0, 10, 20.0f, 10.0f},
    {12, "Oak Bow", 0, 0, 20, 40.0f, 20.0f},
    {13, "Metal Bow", 0, 0, 30, 60.0f, 30.0f},
    {14, "Black Bow", 0, 0, 50, 100.0f, 50.0f},
    {15, "Apollo's Bow", 0, 0, 100, 200.0f, 100.0f}
};

// Armors list
const Armor armors[] = {
    {16, "Starting Armor (Knight)", 20, 10, 50, 30.0f, 15.0f},
    {17, "Starting Robe (Mage)", 10, 20, 30, 25.0f, 12.0f},
    {18, "Starting Vest (Archer)", 15, 10, 40, 28.0f, 14.0f},
    {19, "Iron Armor", 30, 15, 60, 60.0f, 30.0f},
    {20, "Steel Armor", 50, 20, 80, 80.0f, 40.0f},
    {21, "Magic Cloak", 20, 40, 50, 70.0f, 35.0f},
    {22, "Leather Armor", 25, 10, 55, 60.0f, 30.0f},
    {23, "Shadow Armor", 40, 30, 70, 100.0f, 50.0f},
    {24, "Golden Plate", 60, 25, 90, 120.0f, 60.0f},
    {25, "Dragon Scale", 70, 40, 120, 150.0f, 75.0f},
    {26, "Phantom Armor", 45, 50, 100, 130.0f, 65.0f},
    {27, "Mystic Robe", 30, 60, 80, 110.0f, 55.0f}
};

// Potions list
const Potion potions[] = {
    {28, "Small Health Potion", 25, 0, 0, 10.0f, 5.0f},
    {29, "Medium Health Potion", 50, 0, 0, 20.0f, 10.0f},
    {30, "Large Health Potion", 100, 0, 0, 40.0f, 20.0f},
    {31, "Small Mana Potion", 0, 25, 0, 10.0f, 5.0f},
    {32, "Medium Mana Potion", 0, 50, 0, 20.0f, 10.0f},
    {33, "Large Mana Potion", 0, 100, 0, 40.0f, 20.0f},
    {34, "Small Energy Potion", 0, 0, 25, 10.0f, 5.0f},
    {35, "Medium Energy Potion", 0, 0, 50, 20.0f, 10.0f},
    {36, "Large Energy Potion", 0, 0, 100, 40.0f, 20.0f}
};

// Books list
const Book books[] = {
    {37, "Old Health Book", 10, 0, 0, 0, 50.0f, 25.0f},
    {38, "New Health Book", 20, 0, 0, 0, 100.0f, 50.0f},
    {39, "Legendary Health Book", 50, 0, 0, 0, 200.0f, 100.0f},
    {40, "Old Mana Book", 0, 10, 0, 0, 50.0f, 25.0f},
    {41, "New Mana Book", 0, 20, 0, 0, 100.0f, 50.0f},
    {42, "Legendary Mana Book", 0, 50, 0, 0, 200.0f, 100.0f},
    {43, "Old Energy Book", 0, 0, 10, 0, 50.0f, 25.0f},
    {44, "New Energy Book", 0, 0, 20, 0, 100.0f, 50.0f},
    {45, "Legendary Energy Book", 0, 0, 50, 0, 200.0f, 100.0f},
    {46, "Old Speed Book", 0, 0, 0, 5, 50.0f, 25.0f},
    {47, "New Speed Book", 0, 0, 0, 10, 100.0f, 50.0f},
    {48, "Legendary Speed Book", 0, 0, 0, 20, 200.0f, 100.0f}
};

// Function to use a potion
void useItem(Character* player, Inventory* inventory) {
    printf("Available potions:\n");
    printf("1. Small Health Potions: %d\n", inventory->smallPotionCount);
    printf("2. Medium Health Potions: %d\n", inventory->mediumPotionCount);
    printf("3. Large Health Potions: %d\n", inventory->largePotionCount);
    printf("Which potion would you like to use? (1-3): ");

    int choice;
    scanf_s("%d", &choice);

    if (choice == 1 && inventory->smallPotionCount > 0) {
        player->health += 25;
        inventory->smallPotionCount--;
        printf("You used a Small Health Potion. Health restored: 25.\n");
    }
    else if (choice == 2 && inventory->mediumPotionCount > 0) {
        player->health += 50;
        inventory->mediumPotionCount--;
        printf("You used a Medium Health Potion. Health restored: 50.\n");
    }
    else if (choice == 3 && inventory->largePotionCount > 0) {
        player->health += 100;
        inventory->largePotionCount--;
        printf("You used a Large Health Potion. Health restored: 100.\n");
    }
    else {
        printf("You don't have any potions of this type!\n");
    }

    if (player->health > player->maxStats.maxHealth) {
        player->health = player->maxStats.maxHealth;
    }
}

// Function to use a book
void useBook(Character* player, Inventory* inventory) {
    printf("Available books:\n");
    if (strlen(inventory->healthBook.name) > 0) printf("1. %s\n", inventory->healthBook.name);
    if (strlen(inventory->manaBook.name) > 0) printf("2. %s\n", inventory->manaBook.name);
    if (strlen(inventory->energyBook.name) > 0) printf("3. %s\n", inventory->energyBook.name);
    if (strlen(inventory->speedBook.name) > 0) printf("4. %s\n", inventory->speedBook.name);

    printf("Which book would you like to use? (1-4): ");
    int choice;
    scanf_s("%d", &choice);

    if (choice == 1 && strlen(inventory->healthBook.name) > 0) {
        player->maxStats.maxHealth += inventory->healthBook.healthBoost;
        player->health += inventory->healthBook.healthBoost;
        printf("You used %s. Health increased by %d.\n", inventory->healthBook.name, inventory->healthBook.healthBoost);
        memset(&inventory->healthBook, 0, sizeof(Book));
    }
    else if (choice == 2 && strlen(inventory->manaBook.name) > 0) {
        player->maxStats.maxMana += inventory->manaBook.manaBoost;
        player->mana += inventory->manaBook.manaBoost;
        printf("You used %s. Mana increased by %d.\n", inventory->manaBook.name, inventory->manaBook.manaBoost);
        memset(&inventory->manaBook, 0, sizeof(Book));
    }
    else if (choice == 3 && strlen(inventory->energyBook.name) > 0) {
        player->maxStats.maxEnergy += inventory->energyBook.energyBoost;
        player->energy += inventory->energyBook.energyBoost;
        printf("You used %s. Energy increased by %d.\n", inventory->energyBook.name, inventory->energyBook.energyBoost);
        memset(&inventory->energyBook, 0, sizeof(Book));
    }
    else if (choice == 4 && strlen(inventory->speedBook.name) > 0) {
        player->maxStats.maxSpeed += inventory->speedBook.speedBoost;
        player->speed += inventory->speedBook.speedBoost;
        printf("You used %s. Speed increased by %d.\n", inventory->speedBook.name, inventory->speedBook.speedBoost);
        memset(&inventory->speedBook, 0, sizeof(Book));
    }
    else {
        printf("You don't have this book type!\n");
    }
}
