#include "character.h"
#include <stdio.h>
#include <string.h>

// Function to create a Knight character
Character createKnight(const char* playerName) {
    Character knight = {
        "", "Knight",               // Default name and class type
        150, 30, 80,                  // Health, Mana, Energy
        40, 0, 5,                     // Physical, Magic, and Range Attacks
        40, 15, 5,                    // Physical, Magic Defense, and Speed
        100,                          // Initial Gold
        {150, 30, 80, 5},             // Maximum Stats
        {0}                           // Initialize Inventory
    };
    // Copy player-provided name into the character struct
    strcpy_s(knight.name, sizeof(knight.name), playerName);
    return knight;
}

// Function to create a Mage character
Character createMage(const char* playerName) {
    Character mage = {
        "", "Mage",                 // Default name and class type
        100, 100, 40,                 // Health, Mana, Energy
        5, 40, 10,                    // Physical, Magic, and Range Attacks
        15, 40, 6,                    // Physical, Magic Defense, and Speed
        150,                          // Initial Gold
        {100, 100, 40, 6},            // Maximum Stats
        {0}                           // Initialize Inventory
    };
    // Copy player-provided name into the character struct
    strcpy_s(mage.name, sizeof(mage.name), playerName);
    return mage;
}

// Function to create an Archer character
Character createArcher(const char* playerName) {
    Character archer = {
        "", "Archer",              // Default name and class type
        120, 50, 60,                  // Health, Mana, Energy
        15, 10, 25,                   // Physical, Magic, and Range Attacks
        25, 20, 8,                    // Physical, Magic Defense, and Speed
        120,                          // Initial Gold
        {120, 50, 60, 8},             // Maximum Stats
        {0}                           // Initialize Inventory
    };
    // Copy player-provided name into the character struct
    strcpy_s(archer.name, sizeof(archer.name), playerName);
    return archer;
}

// Function to display detailed character information
void displayCharacterInfo(Character* character) {
    printf("\n--- Character Information ---\n");
    printf("Name: %s | Class: %s\n", character->name, character->classType);
    printf("Health: %d/%d | Mana: %d/%d | Energy: %d/%d\n",
        character->health, character->maxStats.maxHealth,
        character->mana, character->maxStats.maxMana,
        character->energy, character->maxStats.maxEnergy);
    printf("Physical Attack: %d | Magic Attack: %d | Range Attack: %d\n",
        character->physicalAttack, character->magicAttack, character->rangeAttack);
    printf("Physical Defence: %d | Magic Defence: %d | Speed: %d/%d\n",
        character->physicalDefence, character->magicDefence,
        character->speed, character->maxStats.maxSpeed);
    printf("Gold: %d\n", character->gold);
}

// Function to display basic character information without a name
void displayCharacterInfoNameless(Character character) {
    printf("Health: %d | Mana: %d | Energy: %d\n",
        character.health, character.mana, character.energy);
    printf("Physical Attack: %d | Magic Attack: %d | Range Attack: %d\n",
        character.physicalAttack, character.magicAttack, character.rangeAttack);
    printf("Physical Defence: %d | Magic Defence: %d | Speed: %d\n",
        character.physicalDefence, character.magicDefence, character.speed);
}
