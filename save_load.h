#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "character.h"
#include "inventory.h"
#include "room.h"

// GameState yap�s�, oyunun durumunu tutar
typedef struct {
    Character player;      // Karakter bilgileri
    Inventory inventory;   // Envanter bilgileri
    Room currentRoom;      // Mevcut oda bilgileri
    int roomCounter;       // Ge�ilen oda say�s�
} GameState;

// Fonksiyon prototipleri
void saveGame(const GameState* state, const char* filename);
void loadGame(GameState* state, const char* filename);
void listSaves(const char* directory);

#endif // SAVE_LOAD_H
