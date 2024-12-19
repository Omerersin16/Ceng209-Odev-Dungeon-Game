#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h" // Includes the definitions for Weapon, Armor, Potion, and Book structures

/**
 * Inventory structure holds equipped items, extra items, potions, and books.
 */
typedef struct {
    // Weapons
    Weapon equippedWeapon;        // The currently equipped weapon
    Weapon extraWeapon;           // A spare weapon (maximum 1)

    // Armors
    Armor equippedArmor;          // The currently equipped armor
    Armor extraArmor;             // A spare armor (maximum 1)

    // Potions
    Potion smallPotions[10];      // Array to hold small potions (up to 10)
    int smallPotionCount;         // Number of small potions in inventory

    Potion mediumPotions[5];      // Array to hold medium potions (up to 5)
    int mediumPotionCount;        // Number of medium potions in inventory

    Potion largePotions[3];       // Array to hold large potions (up to 3)
    int largePotionCount;         // Number of large potions in inventory

    // Books
    Book healthBook;              // Health book (only one allowed)
    Book manaBook;                // Mana book (only one allowed)
    Book energyBook;              // Energy book (only one allowed)
    Book speedBook;               // Speed book (only one allowed)

} Inventory;

/**
 * Adds a weapon to the inventory.
 * inventory The inventory to modify.
 * weapon The weapon to add.
 * return 1 if successful, 0 if the inventory is full.
 */
int addWeapon(Inventory* inventory, Weapon weapon);

/**
 * Adds armor to the inventory.
 * inventory The inventory to modify.
 * armor The armor to add.
 * return 1 if successful, 0 if the inventory is full.
 */
int addArmor(Inventory* inventory, Armor armor);

/**
 * Adds a potion to the inventory.
 * inventory The inventory to modify.
 * potion The potion to add.
 * return 1 if successful, 0 if the inventory is full.
 */
int addPotion(Inventory* inventory, Potion potion);

/**
 * Adds a book to the inventory.
 * inventory The inventory to modify.
 * book The book to add.
 * return 1 if successful, 0 if the book slot is already occupied.
 */
int addBook(Inventory* inventory, Book book);

/**
 * Removes a weapon from the inventory by name.
 * inventory The inventory to modify.
 * name The name of the weapon to remove.
 * return 1 if successful, 0 if the weapon was not found.
 */
int removeWeapon(Inventory* inventory, const char* name);

/**
 * Removes armor from the inventory by name.
 * inventory The inventory to modify.
 * name The name of the armor to remove.
 * return 1 if successful, 0 if the armor was not found.
 */
int removeArmor(Inventory* inventory, const char* name);

/**
 * Removes a potion from the inventory by name.
 * inventory The inventory to modify.
 * name The name of the potion to remove.
 * return 1 if successful, 0 if the potion was not found.
 */
int removePotion(Inventory* inventory, const char* name);

/**
 * Removes a book from the inventory by name.
 * inventory The inventory to modify.
 * name The name of the book to remove.
 * return 1 if successful, 0 if the book was not found.
 */
int removeBook(Inventory* inventory, const char* name);

/**
 * Displays the inventory.
 * inventory The inventory to display.
 * isMerchant A flag indicating if the display is for a merchant interaction.
 * multiplier The price multiplier for merchant transactions.
 */
void displayInventory(Inventory* inventory, int isMerchant, float multiplier);

#endif
