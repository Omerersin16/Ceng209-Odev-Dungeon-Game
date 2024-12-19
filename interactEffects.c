#include "interactEffects.h"
#include <stdio.h>
#include <stdlib.h>
#include "item.h"  
#include "inventory.h" 
#include "Trader.h"



// Handle event effects based on the eventIndex
void handleEventEffect(int eventIndex, Character* player, Inventory* inventory, MerchantInventory* merchantInventory) {
    char command[10];
    float multiplier;

    switch (eventIndex) {
    case 1: // Discounted merchant
        printf("You found a discounted merchant! Prices are 30%% off.\n");
        multiplier = 0.7f; // Discount multiplier
        break;

    case 2: // Regular merchant
        printf("You found a regular merchant.\n");
        multiplier = 1.0f; // Regular price multiplier
        break;

    case 3: // Expensive merchant
        printf("You found an expensive merchant! Prices are 50%% higher.\n");
        multiplier = 1.5f; // Expensive multiplier
        break;

    case 4: { // Random chest with potential trap or reward
        int randomValue = (rand() % 10) + 1;

        if (randomValue <= 4) {
            printf("Damn, this chest was a trap! You take some wounds.\n");
            player->health -= 50;
            if (player->health < 0) player->health = 0;
            printf("You lost 50 health. Current Health: %d/%d\n", player->health, player->maxStats.maxHealth);
        }
        else {
            printf("This is what I call luck, the chest is full of gold!\n");
            player->gold += 100;
            printf("You gained 100 gold. Current Gold: %d\n", player->gold);
        }
        break;
    }

    case 5: // Random trap
        printf("Damn, you got caught in a trap!\n");
        player->health -= 30;
        if (player->health < 0) player->health = 0;
        printf("You lost 30 health. Current Health: %d/%d\n", player->health, player->maxStats.maxHealth);
        break;

    case 6: // Healing water or poison
        if ((rand() % 10) < 3) {
            printf("The water is poisoned! You lose 20 health.\n");
            player->health -= 20;
            if (player->health < 0) player->health = 0;
        }
        else {
            printf("The water is refreshing! You regain 40 health.\n");
            player->health += 40;
            if (player->health > player->maxStats.maxHealth) player->health = player->maxStats.maxHealth;
        }
        printf("Current Health: %d/%d\n", player->health, player->maxStats.maxHealth);
        break;

    case 7: // Dead knight
        printf("You encounter a dead knight. Searching him, you find 3 small health potions.\n");
        for (int i = 0; i < 3; i++) {
            addPotion(inventory, potions[0]);
        }
        break;

    case 8: // Healing woman
        printf("A kind woman heals you for free.\n");
        player->health += 50;
        if (player->health > player->maxStats.maxHealth) player->health = player->maxStats.maxHealth;
        printf("You gain 50 health! Current Health: %d/%d\n", player->health, player->maxStats.maxHealth);
        break;

    case 9: // Mysterious figure offering upgrades
        printf("A mysterious figure offers you an upgrade in exchange for a potion or book.\n");
        printf("1. Throw a Potion\n2. Throw a Book\nChoose an option: ");
        int choice;
        scanf_s("%d", &choice);

        if (choice == 1) {
            printf("Throwing a potion for an upgrade.\n");
            if (removePotion(inventory, "Small Health Potion")) {
                addPotion(inventory, potions[1]);
                printf("You received a Medium Health Potion!\n");
            }
            else {
                printf("You have no Small Health Potion to throw.\n");
            }
        }
        else if (choice == 2) {
            printf("Throwing a book for an upgrade.\n");
            if (removeBook(inventory, "Old Health Book")) {
                addBook(inventory, books[1]);
                printf("You received a New Health Book!\n");
            }
            else {
                printf("You have no Old Health Book to throw.\n");
            }
        }
        else {
            printf("Invalid choice.\n");
        }
        break;
    case 16: // Magic damage increase event
        printf("You meet a wise sorcerer who enchants your weapon.\n");
        player->magicAttack += 20;
        printf("Your magic attack has increased by 20! Current Magic Attack: %d\n", player->magicAttack);
        break;

    case 17: // Physical damage increase event
        printf("A seasoned warrior offers to train you in close combat.\n");
        player->physicalAttack += 20;
        printf("Your physical attack has increased by 20! Current Physical Attack: %d\n", player->physicalAttack);
        break;
    case 18:
        printf("You encounter a ranger practicing their skills. They offer to train you in ranged combat.\n");
        player->rangeAttack += 20; // Increase range attack
        printf("Your range attack has increased by 20! Current Range Attack: %d\n", player->rangeAttack);
        break;
    case 19: // Energy boost
        player->energy += 20;
        player->maxStats.maxEnergy += 20;
        printf("Your energy increased by 20!\n");
        break;

    case 20: // Mana boost
        player->mana += 20;
        player->maxStats.maxMana += 20;
        printf("Your mana increased by 20!\n");
        break;

    case 21: // Speed boost
        player->speed += 4;
        player->maxStats.maxSpeed += 4;
        printf("Your speed increased by 4!\n");
        break;

    default:
        printf("Nothing special happens.\n");
        break;
    }

    // Trader interactions (if applicable)
    while (eventIndex >= 1 && eventIndex <= 3) {
        float multiplier = 1.0f;
        printf("\nEnter command (buy, sell, exit): ");
        scanf_s("%9s", command, (unsigned)_countof(command));

        if (strcmp(command, "buy") == 0) {
            buyItem(player, merchantInventory, multiplier);
        }
        else if (strcmp(command, "sell") == 0) {
            sellItem(player, merchantInventory, multiplier);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("Exiting the trade menu.\n");
            break;
        }
        else {
            printf("Invalid command. Please enter 'buy', 'sell', or 'exit'.\n");
        }
    }
}


// Function to handle the command to interact with events in a room
void handleInteractCommand(Room* currentRoom, Character* player, Inventory* inventory, MerchantInventory* merchantInventory) {
    int eventNumber = 0;

    // Ask the user which event they want to interact with
    printf("Which event would you like to interact with? (1 or 2): ");
    scanf_s("%d", &eventNumber);

    // Validate the entered event number
    if (eventNumber < 1 || eventNumber > currentRoom->eventCount) {
        printf("Invalid event number! There are only %d events in this room.\n", currentRoom->eventCount);
        return;
    }

    // Process the selected event
    int eventIndex = currentRoom->eventIndices[eventNumber - 1]; // Get the correct eventIndex from the array
    printf("You are interacting with event %d (Event ID: %d).\n", eventNumber, eventIndex);

    // Handle the effects of the selected event
    handleEventEffect(eventIndex, player, inventory, merchantInventory);
}

// Function to increase the player's magic attack
void handleMagicDamageIncrease(Character* player) {
    player->magicAttack += 20; // Increase magic attack by 20
    printf("Your magic damage increased by 20!\n");
}

// Function to increase the player's physical attack
void handlePhysicalDamageIncrease(Character* player) {
    player->physicalAttack += 20; // Increase physical attack by 20
    printf("Your physical damage increased by 20!\n");
}

// Function to increase the player's ranged attack
void handleRangeDamageIncrease(Character* player) {
    player->rangeAttack += 20; // Increase ranged attack by 20
    printf("Your range damage increased by 20!\n");
}

// Function to increase the player's energy
void handleEnergyIncrease(Character* player) {
    player->energy += 20; // Increase energy by 20
    if (player->energy > player->maxStats.maxEnergy) {
        player->energy = player->maxStats.maxEnergy; // Cap at max energy
    }
    printf("Your energy increased by 20! Current Energy: %d/%d\n", player->energy, player->maxStats.maxEnergy);
}

// Function to increase the player's mana
void handleManaIncrease(Character* player) {
    player->mana += 20; // Increase mana by 20
    if (player->mana > player->maxStats.maxMana) {
        player->mana = player->maxStats.maxMana; // Cap at max mana
    }
    printf("Your mana increased by 20! Current Mana: %d/%d\n", player->mana, player->maxStats.maxMana);
}

// Function to increase the player's speed
void handleSpeedIncrease(Character* player) {
    player->speed += 4; // Increase speed by 4
    if (player->speed > player->maxStats.maxSpeed) {
        player->speed = player->maxStats.maxSpeed; // Cap at max speed
    }
    printf("Your speed increased by 4! Current Speed: %d/%d\n", player->speed, player->maxStats.maxSpeed);
}
