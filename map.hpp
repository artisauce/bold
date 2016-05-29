#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class map {
public:

	const unsigned int type; // Determines type of region.

	tile* content; // Is square. Height/width determined by side.

	const unsigned int side;

	unsigned int* explored; // Determining which tiles are explored. 0 not, 1 seen, 2 visited

	unsigned int playerPosition; // Determines player party position.

	group_t* groups; // Positions of critters and what they are.

	map(unsigned int typeEntered, unsigned int sideEntered);

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

	tile(unsigned int type); // Construction.

	~tile();
	
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

