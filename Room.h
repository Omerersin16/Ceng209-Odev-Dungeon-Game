#ifndef ROOM_H
#define ROOM_H

// Structure defining a Room
typedef struct {
    char description[256];    // Description of the room
    char directions[4][10];   // Possible directions in the room (e.g., "up", "down")
    int directionCount;       // Number of valid directions in the room
    int descriptionIndex;     // Index for the room description (used for randomization)
    int eventCount;           // Number of events in the room (0, 1, or 2)
    int eventIndices[2];      // Indices of events present in the room
} Room;

/**
 *  Creates a new room, initializing its properties.
 *  room Pointer to the room to be initialized.
 *  lastDirection The direction the player came from (to avoid looping back).
 *  isStartingRoom Flag indicating if the room is the starting room.
 */
void createRoom(Room* room, const char* lastDirection, int isStartingRoom);

/**
 * Prints the details of the room, including its description and directions.
 * room Pointer to the room whose details will be printed.
 */
void printRoomDetails(Room* room);

/**
 *  Prints the room description along with any events in the room.
 * room Pointer to the room whose description and events will be printed.
 */
void printRoomDescriptionAndEvents(Room* room);

#endif // ROOM_H
