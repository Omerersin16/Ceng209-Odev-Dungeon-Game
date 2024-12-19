#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External declaration of random events array
extern const char* randomEvents[];

// Room descriptions for different room types
const char* roomDescriptions[30] = {
    "This is a very old room. Broken furniture, small and large bones lie scattered around.",
    "The room is damp and cold, with water dripping from the ceiling.",
    "Broken furniture and debris litter the ground.",
    "The air is thick with an eerie silence.",
    "A massive hole dominates the center of the room.",
    "You find yourself surrounded by tall, looming bookshelves.",
    "The smell of burning incense lingers here.",
    "You see cracks in the walls, large enough for creatures to hide.",
    "The ceiling is covered with spider webs.",
    "A faint blue glow emanates from the stone walls.",
    "The floor is covered in a soft, mossy carpet.",
    "A pool of stagnant water fills the far corner of the room.",
    "The room vibrates with a strange hum, as if alive.",
    "Rusty chains hang from the ceiling, swaying gently.",
    "The walls are adorned with faded murals of unknown deities.",
    "There’s an unsettling quietness, broken only by the sound of your breathing.",
    "A stone staircase spirals down into darkness.",
    "The air smells like sulfur, and faint scorch marks cover the floor.",
    "The room feels colder than ice; frost covers everything.",
    "The walls are smooth and unnaturally white.",
    "Golden chandeliers hang from the ceiling, illuminating the space.",
    "You step into a room filled with statues frozen in combat.",
    "A massive, cracked mirror reflects a distorted version of yourself.",
    "Broken columns and shattered vases hint at a once-great hall.",
    "The ground trembles slightly, as if something moves beneath.",
    "A circle of ancient runes glows softly on the floor.",
    "A strange mechanical ticking echoes through the room.",
    "The sound of rushing water comes from behind one of the walls.",
    "The room is lined with thousands of lit candles.",
    "The walls shimmer with faint golden light, almost as if alive."
};

// Random events that may occur in a room
const char* randomEvents[22] = {
    "There is nothing in this room right now. This could be either a blessing or a curse.",
    "In the farthest corner of the room, you see a hooded man staring at you. He starts waving and slightly steps aside to show you the goods he is selling.",
    "You see a merchant with a stall set up along the room's edge. He has all kinds of items: armors, potions, and weapons. He calls out to you, urging you to come closer.",
    "What you see right now is truly incredible: a bustling marketplace filled with colorful stalls and merchants. Here, you can find almost anything you are looking for.",
    "There is a suspicious-looking golden chest in the middle of the room. Danger might lurk inside, or it could hold great rewards. Many adventurers have gotten rich—or perished—because of such chests.",
    "Damn it! It's a trap. But if you want to move forward, you must get through it.",
    "What is this wet feeling? Oh, it’s a river flowing gently beneath your feet. Perhaps you should rest and drink some water, but what if the water is poisoned?",
    "As you enter the room, something shiny catches your eye. A dead knight lies here with two goblin corpses nearby. Perhaps you can take some useful items from him.",
    "What is that beautiful sound? A singing woman. But upon closer look, she seems to be a doctor, judging by her clothes.",
    "You see a well in the room. Just as you approach to drink water, the well suddenly speaks! It promises you something better in return if you throw an item inside.",
    "As you enter the room, something flies past your head—a rock! You turn and see a goblin standing there, ready to fight. If you want to move forward, you must defeat it.",
    "A voice calls to you from across the room. It looks like a beautiful woman from afar, but as you approach, you see a pool of blood and realize it's a siren feeding. Kill her before she kills you.",
    "You see a hooded figure holding a black wooden staff. The moment he notices you, he waves the staff toward you. This could be dangerous.",
    "What is this? A massive nose, a crooked hat, and a twisted body! A classic witch with her wand is ready to trouble you.",
    "A bandit stands before you, his dirty clothes and crossbow aimed directly at you. Kill him before he kills you.",
    "A knight stands in front of you, wearing a shining suit of armor and wielding a massive two-handed sword as he charges at you.",
    "This is not something you see every day. An old man with a huge book approaches you, asking if you want to learn magic.",
    "As you enter, the sound of clashing swords greets you. Two knights appear to be sparring. They ask if you want to join them.",
    "An arrow narrowly misses your face as you step into the room. Looking in its direction, you see an elf holding a bow and asking if you want to team up.",
    "You never expected to see a woman punching a boxing bag in a dungeon. She offers to teach you a few moves if you join her.",
    "What is this? A floating monk meditating on a carpet. He offers to increase your mana if you meditate with him."
};

// Function to create a room with description, events, and directions
void createRoom(Room* room, const char* lastDirection, int roomNumber) {
    memset(room, 0, sizeof(Room)); // Initialize room structure

    if (roomNumber == 0) {
        // Starting room configuration
        strcpy_s(room->description, sizeof(room->description), "This is the starting room. No events happen here.");
        room->eventCount = 0;
        room->directionCount = 4;

        // Fixed directions for starting room
        strcpy_s(room->directions[0], sizeof(room->directions[0]), "right");
        strcpy_s(room->directions[1], sizeof(room->directions[1]), "left");
        strcpy_s(room->directions[2], sizeof(room->directions[2]), "up");
        strcpy_s(room->directions[3], sizeof(room->directions[3]), "down");
    }
    else {
        // Generate random room description
        int randomDescription = rand() % 30;
        strcpy_s(room->description, sizeof(room->description), roomDescriptions[randomDescription]);

        // Randomize number of events (0-2)
        room->eventCount = rand() % 3;
        if (room->eventCount > 0) {
            for (int i = 0; i < room->eventCount; i++) {
                room->eventIndices[i] = rand() % 22; // Random event index
            }
        }

        // Randomize directions (1-3 directions, avoiding lastDirection)
        const char* allDirections[] = { "right", "left", "up", "down" };
        int addedDirections = 0;
        for (int i = 0; i < 4; i++) {
            if (lastDirection != NULL && strcmp(allDirections[i], lastDirection) == 0) {
                continue; // Skip the direction we came from
            }
            strcpy_s(room->directions[addedDirections++], sizeof(room->directions[0]), allDirections[i]);
        }
        room->directionCount = addedDirections;
    }
}

// Function to print room details
void printRoomDetails(Room* room) {
    printf("\n%s\n", room->description);

    for (int i = 0; i < room->eventCount; i++) {
        int eventIndex = room->eventIndices[i];
        if (eventIndex >= 0 && eventIndex < 22 && randomEvents[eventIndex] != NULL) {
            printf("Event %d: %s\n", i + 1, randomEvents[eventIndex]);
        }
        else {
            printf("Event %d: No description available.\n", i + 1);
        }
    }
}

// Function to print room description and events
void printRoomDescriptionAndEvents(Room* room) {
    printRoomDetails(room);

    // If no events, print the default "nothing happens" event
    if (room->eventCount == 0) {
        printf("%s\n", randomEvents[0]);
    }
}
