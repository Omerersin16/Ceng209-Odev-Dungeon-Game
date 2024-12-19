#ifndef ITEM_H
#define ITEM_H

// Structure defining a Weapon
typedef struct {
    int id;                 // Unique identifier for the weapon
    char name[30];          // Name of the weapon
    int physicalAttack;     // Physical attack stat of the weapon
    int magicAttack;        // Magic attack stat of the weapon
    int rangeAttack;        // Range attack stat of the weapon
    float buyPrice;         // Purchase price of the weapon
    float sellPrice;        // Selling price of the weapon
} Weapon;

// Structure defining an Armor
typedef struct {
    int id;                 // Unique identifier for the armor
    char name[30];          // Name of the armor
    int physicalDefence;    // Physical defense stat of the armor
    int magicDefence;       // Magic defense stat of the armor
    int healthBoost;        // Additional health boost provided by the armor
    float buyPrice;         // Purchase price of the armor
    float sellPrice;        // Selling price of the armor
} Armor;

// Structure defining a Potion
typedef struct {
    int id;                 // Unique identifier for the potion
    char name[30];          // Name of the potion
    int healthRestore;      // Health restoration value of the potion
    int manaRestore;        // Mana restoration value of the potion
    int energyRestore;      // Energy restoration value of the potion
    float buyPrice;         // Purchase price of the potion
    float sellPrice;        // Selling price of the potion
} Potion;

// Structure defining a Book
typedef struct {
    int id;                 // Unique identifier for the book
    char name[30];          // Name of the book
    int healthBoost;        // Permanent health boost provided by the book
    int manaBoost;          // Permanent mana boost provided by the book
    int energyBoost;        // Permanent energy boost provided by the book
    int speedBoost;         // Permanent speed boost provided by the book
    float buyPrice;         // Purchase price of the book
    float sellPrice;        // Selling price of the book
} Book;

// Global arrays for predefined items
extern const Weapon weapons[];  // Array of predefined weapons
extern const Armor armors[];    // Array of predefined armors
extern const Potion potions[];  // Array of predefined potions
extern const Book books[];      // Array of predefined books

#endif // ITEM_H
