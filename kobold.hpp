#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class character {
public:

	char* name; 
	// Character name
	// 17 characters should be good -- the extra for a space.

	unsigned int gender; // 0 male, 1 female, 2 it's complicated

	char* race; // We'll eventually make a dictionary that associates an unsigned int with a race. For now, it's flexible.

	int health; // General health for general temporary solvents.
	int maxHealth;

	int* stats; // Strength, Dexterity, Intelligence

	character(char* name,unsigned int gender, char* race, int* stats); // For full creation.
	character(char* race, char* type); // For group creation. You know, AI.
	~character();
	battle(character* enemy);
};

typedef struct group { // Might be turned into a class one day.

	
	unsigned int position; // Position on map.
	character* characters; // Critters in the group.
	unsigned int amount; // Convenient for quick amount.

} group_t;

typedef struct track {

	
	unsigned int pointing; // Pointing where? use numpad for quick reference. 5 means ambush ;). Is 5 if enemy is present on tile, or died there.
	char** characters; // Just their names. Maybe some more details added later, like feet equipment.
	unsigned int life; // How long the tracks where there. Gets removed at 30, starts at 0, beneath them.

} track_t;

class map {
public:

	const unsigned int type; // Determines type of region.

	tile* content; // Is square. Height/width determined by side.

	const unsigned int side;

	unsigned int* explored; // Determining which tiles are explored. 0 not, 1 seen, 2 visited

	unsigned int playerPosition; // Determines player party position.

	group_t* groups; // Positions of critters and what they are.

	map(unsigned int type, unsigned int side);

	~map();

	updateExplore(); // To be called when you move a tile or gain a scout -- explores map. DO NOT combine with map update.

	encounter(unsigned int position); // Checks if battle is held at current player pos.

	mapUpdate(); // All AI on the map will move around where they want to go.

	exportMap(); // Export map contents -- efficiently -- for a graphic program to read and interpret.

	spawning(); // Handles spawning of critters at the border of region. Remember the trials from the previous map player visited also continue.

};

class tile {
public:

	char* name; // Tile name.

	unsigned int type; // What type of place this is.

	int* stats; // Stats determining how this place can be used. --> ATTACK, HIDE, FLEE. -10 means you can't/risks, 10 is gauranteed/bonuses.

	tract_t* tracks; // Tracks. Optdate when ready m8.
	
};

class worldMap {
public:

	const char* name; // World name. Again, 17 characters.

	map* content; // Is square. Height/width determined by side.

	const unsigned int side;

	unsigned int* lock; // Determines lock on region position. 0 means nothing, 1 means current, 2 means OOR (out-of-region), 3 means resetted.
	// This is so that groups can still get generated and chase you.

	unsigned int playerPosition; // Determines player party position.

	worldMap(unsigned int side);

	~worldMap();

	worldMapUpdate(); // All AI on the world map will move around where they want to go.

	exportWorldMap(); // Export map contents -- efficiently -- for a graphic program to read and interpret.

};