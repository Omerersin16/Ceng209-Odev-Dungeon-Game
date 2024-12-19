#include "save_load.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>  // For _mkdir
#include <io.h>      // For _findfirst and _findnext
void saveGame(const GameState* state, const char* filename) {
    // Ensure the save directory exists
    if (CreateDirectory("C:\\GameSaves", NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        // Proceed to save the game
        FILE* file = fopen(filename, "wb");
        if (!file) {
            printf("Error: Unable to save the game to %s.\n", filename);
            return;
        }
        fwrite(state, sizeof(GameState), 1, file);
        fclose(file);
        printf("Game saved successfully to %s\n", filename);
    }
    else {
        // Directory creation failed
        printf("Error: Unable to create directory for saves.\n");
    }
}

void loadGame(GameState* state, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Unable to load the game from %s.\n", filename);
        return;
    }
    fread(state, sizeof(GameState), 1, file);
    fclose(file);
    printf("Game loaded successfully from %s.\n", filename);
}


#include <windows.h>
#include <stdio.h>

void listSaves(const char* directory) {
    char searchPath[256];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.sav", directory);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No save files found in directory: %s\n", directory);
        return;
    }

    printf("\nAvailable save files in '%s':\n", directory);
    do {
        printf(" - %s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}


