// Include necessary libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "character.h"
#include "inventory.h"
#include "item.h"
#include "room.h"
#include "interactEffects.h"
#include "Trader.h"
#include "save_load.h"  
#include <direct.h>  // For _mkdir on Windows
#include <errno.h>   // For errno definitions
#include <winerror.h>
#include <windows.h>
#include <ShlObj_core.h>
// Constants for command sizes
#define COMMAND_SIZE 20
#define DIRECTION_SIZE 10

// Function prototypes for main game logic
void displayWelcomeMessage();
void displayCharacterSelectionScene();
void displayStartingRoom(Room* currentRoom);
void initializeRoom(Room* room);
void handleMoveCommand(Room* currentRoom, char* lastDirection, int* roomCounter);
void handleShowCommand(Character* player, Inventory* inventory);
void handleUseCommand(Character* player, Inventory* inventory);
void applyEquipmentBonuses(Character* character, Inventory* inventory);

int main() {
    // Initialize necessary variables
    MerchantInventory merchantInventory;
    initializeMerchantInventory(&merchantInventory);

    srand((unsigned int)time(NULL));

    Room currentRoom = { 0 };
    Character player = { 0 };
    Inventory inventory = { 0 };
    char lastDirection[DIRECTION_SIZE] = "";
    char command[COMMAND_SIZE] = "", subCommand[COMMAND_SIZE] = "";
    int roomCounter = 0;

    // Display welcome message
    displayWelcomeMessage();

    // Get character name from the user
    printf("Enter your character's name: ");
    scanf_s("%20s", player.name, (unsigned int)sizeof(player.name));

    // Display character selection menu
    displayCharacterSelectionScene();
    printf("\nChoose your class (1: Knight, 2: Mage, 3: Archer): ");
    int choice;
    scanf_s("%d", &choice);

    // Create the character based on the user's choice
    switch (choice) {
    case 1: player = createKnight(player.name); break;
    case 2: player = createMage(player.name); break;
    case 3: player = createArcher(player.name); break;
    default:
        printf("Invalid choice. Defaulting to Knight.\n");
        player = createKnight(player.name);
    }

    // Set maximum stats for the character
    player.maxStats.maxHealth = player.health;
    player.maxStats.maxMana = player.mana;
    player.maxStats.maxEnergy = player.energy;
    player.maxStats.maxSpeed = player.speed;

    // Initialize starting inventory based on character class
    initializeStartingInventory(&inventory, player.classType);
    applyEquipmentBonuses(&player, &inventory);

    // Display character stats and inventory
    printf("\n--- Character Stats with Equipment ---\n");
    displayCharacterInfo(&player);
    displayInventory(&inventory, 0, 1.0f);

    // Initialize the first room
    initializeRoom(&currentRoom);
    displayStartingRoom(&currentRoom);

    // Main game loop
    while (1) {
        // Clear the command buffers for a new input cycle
        memset(command, 0, sizeof(command));
        memset(subCommand, 0, sizeof(subCommand));

        // Prompt the user for input
        printf("\nEnter command (look, move <direction>, show <type>, use <type>, interact<event num>, quit , save , load , list): ");
        scanf_s("%19s", command, (unsigned int)sizeof(command));

        // Handle various commands
        if (strcmp(command, "look") == 0) {
            // Display the description and events of the current room
            printRoomDescriptionAndEvents(&currentRoom);
        }
        else if (strcmp(command, "move") == 0) {
            // Handle movement command, update room based on direction
            handleMoveCommand(&currentRoom, lastDirection, &roomCounter);
        }
        else if (strcmp(command, "show") == 0) {
            // Display player stats or inventory based on subcommand
            handleShowCommand(&player, &inventory);
        }
        else if (strcmp(command, "use") == 0) {
            // Use an item from the inventory
            handleUseCommand(&player, &inventory);
        }
        else if (strcmp(command, "save") == 0) {
            printf("Enter filename to save the game (e.g., save1.sav): ");
            char filename[100];
            scanf_s("%99s", filename, (unsigned int)sizeof(filename));

            // Belgeler klasörüne eriþim
            char saveDirectory[MAX_PATH];
            if (SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, saveDirectory) == S_OK) {
                // Belgeler klasörüne "GameSaves" dizinini ekleyin
                strcat_s(saveDirectory, sizeof(saveDirectory), "Belgeler");

                // Dizin oluþturma veya doðrulama
                if (_mkdir(saveDirectory) == 0 || errno == EEXIST) {
                    char fullPath[MAX_PATH];
                    snprintf(fullPath, sizeof(fullPath), "%s\\%s", saveDirectory, filename);

                    // Oyun durumunu kaydetme
                    GameState state = { player, inventory, currentRoom, roomCounter };
                    saveGame(&state, fullPath);
                }
                else {
                    printf("Error: Unable to create or access the save directory.\n");
                }
            }
            else {
                printf("Error: Unable to access the Documents directory.\n");
            }
        }
        else if (strcmp(command, "load") == 0) {
            // Load a previously saved game state from a file
            printf("Enter filename to load the game (e.g., save1.sav): ");
            char filename[100];
            scanf_s("%99s", filename, (unsigned int)sizeof(filename));

            // Add save directory path
            char fullPath[256];
            snprintf(fullPath, sizeof(fullPath), "saves\\%s", filename);

            GameState state;
            loadGame(&state, fullPath);

            // Update the current game state with the loaded data
            player = state.player;
            inventory = state.inventory;
            currentRoom = state.currentRoom;
            roomCounter = state.roomCounter;

            printf("Game state loaded. Resuming from saved point.\n");
        }
        else if (strcmp(command, "list") == 0) {
            char saveDirectory[MAX_PATH];
            if (SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, saveDirectory) == S_OK) {
                strcat_s(saveDirectory, sizeof(saveDirectory), "Belgeler");

                // Dizin oluþturma veya doðrulama
                if (_mkdir(saveDirectory) == 0 || errno == EEXIST) {
                    listSaves(saveDirectory);
                }
                else {
                    printf("Error: Unable to access the save directory.\n");
                }
            }
            else {
                printf("Error: Unable to access the Documents directory.\n");
            }
        }
        else if (strcmp(command, "quit") == 0) {
            // Exit the game loop
            printf("Exiting the game. Goodbye!\n");
            break;
        }
        else if (strcmp(command, "interact") == 0) {
            // Handle interactions with events in the current room
            handleInteractCommand(&currentRoom, &player, &inventory, &merchantInventory);
        }
        else {
            // Notify the user of an unknown command
            printf("Unknown command! Use 'look', 'move <direction>', 'show <type>', 'use <type>', or 'quit'.\n");
        }
    }return 0;
}



// Function to display welcome message
void displayWelcomeMessage() {
    printf("\nWelcome to the Adventure Game!\n");
    printf("Explore rooms, collect items, and survive the dungeon.\n");
    printf("Commands: look, move <direction>, show <type>, use <type>, interact<event num>, quit\n");
}

// Function to display character selection scene
void displayCharacterSelectionScene() {
    printf("\nCharacter Classes:\n");
    printf("1. Knight - High health and physical attack.\n");
    displayCharacterInfoNameless(createKnight(""));

    printf("\n2. Mage - High mana and magic attack.\n");
    displayCharacterInfoNameless(createMage(""));

    printf("\n3. Archer - Balanced stats with range attack.\n");
    displayCharacterInfoNameless(createArcher(""));
}

// Function to display starting room
void displayStartingRoom(Room* currentRoom) {
    printf("\n--- Starting Room ---\n");
    currentRoom->directionCount = 4;
    strcpy_s(currentRoom->directions[0], sizeof(currentRoom->directions[0]), "right");
    strcpy_s(currentRoom->directions[1], sizeof(currentRoom->directions[1]), "left");
    strcpy_s(currentRoom->directions[2], sizeof(currentRoom->directions[2]), "up");
    strcpy_s(currentRoom->directions[3], sizeof(currentRoom->directions[3]), "down");

    printf("You can move in all directions: right, left, up, and down.\n");
}

// Function to initialize a room
void initializeRoom(Room* room) {
    memset(room, 0, sizeof(Room));
}

// Function to handle the move command
void handleMoveCommand(Room* currentRoom, char* lastDirection, int* roomCounter) {
    char direction[DIRECTION_SIZE] = "";
    scanf_s("%9s", direction, (unsigned int)sizeof(direction));

    int validDirection = 0;
    for (int i = 0; i < currentRoom->directionCount; i++) {
        if (strcmp(direction, currentRoom->directions[i]) == 0) {
            validDirection = 1;
            break;
        }
    }

    if (validDirection) {
        printf("You move %s.\n", direction);
        strcpy_s(lastDirection, DIRECTION_SIZE, direction);

        // Create a new room and increment the room counter
        (*roomCounter)++;
        initializeRoom(currentRoom);
        createRoom(currentRoom, lastDirection, *roomCounter);

        // Display available directions in the new room
        printf("You can move: ");
        for (int i = 0; i < currentRoom->directionCount; i++) {
            printf("%s ", currentRoom->directions[i]);
        }
        printf("\n");

    }
    else {
        printf("You cannot move in that direction!\n");
    }
}

// Function to handle the show command
void handleShowCommand(Character* player, Inventory* inventory) {
    char subCommand[COMMAND_SIZE] = "";
    scanf_s("%19s", subCommand, (unsigned int)sizeof(subCommand));

    if (strcmp(subCommand, "character") == 0) {
        displayCharacterInfo(player);
    }
    else if (strcmp(subCommand, "inventory") == 0) {
        displayInventory(inventory, 0, 1.0f);
    }
    else {
        printf("Invalid 'show' command. Use 'show character' or 'show inventory'.\n");
    }
}

// Function to handle the use command
void handleUseCommand(Character* player, Inventory* inventory) {
    char itemType[COMMAND_SIZE] = "";
    printf("What would you like to use? (potion/book): ");
    scanf_s("%19s", itemType, (unsigned int)sizeof(itemType));

    if (strcmp(itemType, "potion") == 0) {
        useItem(player, inventory);
    }
    else if (strcmp(itemType, "book") == 0) {
        useBook(player, inventory);
    }
    else {
        printf("Invalid item type! Use 'potion' or 'book'.\n");
    }
}

// Function to apply equipment bonuses to a character
void applyEquipmentBonuses(Character* character, Inventory* inventory) {
    if (strlen(inventory->equippedArmor.name) > 0) {
        character->physicalDefence += inventory->equippedArmor.physicalDefence;
        character->magicDefence += inventory->equippedArmor.magicDefence;
        character->maxStats.maxHealth += inventory->equippedArmor.healthBoost;
        character->health += inventory->equippedArmor.healthBoost;

        if (character->health > character->maxStats.maxHealth) {
            character->health = character->maxStats.maxHealth;
        }
    }

    if (strlen(inventory->equippedWeapon.name) > 0) {
        character->physicalAttack += inventory->equippedWeapon.physicalAttack;
        character->magicAttack += inventory->equippedWeapon.magicAttack;
        character->rangeAttack += inventory->equippedWeapon.rangeAttack;
    }

    // Ensure no negative stats
    if (character->physicalAttack < 0) character->physicalAttack = 0;
    if (character->magicAttack < 0) character->magicAttack = 0;
    if (character->rangeAttack < 0) character->rangeAttack = 0;
    if (character->physicalDefence < 0) character->physicalDefence = 0;
    if (character->magicDefence < 0) character->magicDefence = 0;
    if (character->health < 0) character->health = 0;
}
