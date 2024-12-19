#ifndef CHARACTER_H
#define CHARACTER_H

#include "inventory.h" // Inventory için include

typedef struct {
    char name[21];
    char classType[10];
    int health;
    int mana;
    int energy;
    int physicalAttack;
    int magicAttack;
    int rangeAttack;
    int physicalDefence;
    int magicDefence;
    int speed;
    int gold;

    struct {
        int maxHealth;
        int maxMana;
        int maxEnergy;
        int maxSpeed;
    } maxStats;

    Inventory inventory; // Inventory added to Character structure
} Character;

Character createKnight(const char* playerName);
Character createMage(const char* playerName);
Character createArcher(const char* playerName);
void displayCharacterInfo(Character* character);
void displayCharacterInfoNameless(Character character);

#endif
