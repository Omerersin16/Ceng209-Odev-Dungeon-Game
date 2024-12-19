\# Adventure Game

\## Features

1\. \*\*Dynamic Room Structure\*\*: Each room offers a unique experience with changing layouts.

2\. \*\*Inventory Management\*\*: Add or remove items from your inventory.

3\. \*\*Room Events\*\*: Events in rooms directly affect you, either by granting items or altering your stats.

4\. \*\*Detailed Character Stats\*\*: Comprehensive tracking of character attributes.

5\. \*\*Three Selectable Character Classes\*\*: Choose between Warrior, Archer, and Mage, each with unique attributes.

6\. \*\*Command-Based Gameplay\*\*: Navigate the game world using typed commands.

\---

\## Commands

1\. \*\*move\*\*: Move to accessible rooms in the specified direction.

2\. \*\*look\*\*: View the description of the room and any events it contains.

3\. \*\*show\*\*:

`   `- `show inventory`: Display your inventory.

`   `- `show character`: Display your character's current stats.

4\. \*\*use\*\*: Use potions or books to enhance your stats temporarily or permanently.

5\. \*\*interact\*\*: Interact with events in the room and see the outcomes.

6\. \*\*quit\*\*: Exit the game.

7\. \*\*save\*\*: Save your current game progress.

8\. \*\*load\*\*: Load a previously saved game.

9\. \*\*list\*\*: List all available saved game files.

\---

\## How to Play

1\. Launch the game.

2\. Enter the name of your character.

3\. Select your character class (Warrior, Archer, or Mage).

4\. Use the \*\*move\*\* command to navigate between rooms.

5\. Use the \*\*look\*\* command to examine the room and view any events.

6\. Use the \*\*interact\*\* command to engage with events in the room.

7\. Use the \*\*use\*\* command to consume items and improve your stats.

8\. Save your progress with the \*\*save\*\* command and reload it later with the \*\*load\*\* command.

\---

\## File Structure

\- \*\*`main.c`\*\*: Contains the game loop and core mechanics.

\- \*\*`character.h/c`\*\*: Defines character classes and related functions.

\- \*\*`inventory.h/c`\*\*: Manages the player's inventory system.

\- \*\*`item.h/c`\*\*: Defines various items (weapons, armor, potions, and books).

\- \*\*`room.h/c`\*\*: Handles room generation and descriptions.

\- \*\*`interactEffects.h/c`\*\*: Implements interactions with room events.

\- \*\*`save\_load.h/c`\*\*: Implements save and load functionality.

\- \*\*`trader.h/c`\*\*: Handles merchant inventory and trading system.

\- \*\*`Makefile`\*\*: Automates the compilation of the project.

\---

\## Compilation and Execution

\### \*\*Requirements\*\*

\- A C compiler (e.g., GCC or Clang).

\- Make utility (for automated builds).

\### \*\*Steps\*\*

1\. Clone the repository:

`   ````bash

`   `git clone <repository\_url>

`   `cd AdventureGame

