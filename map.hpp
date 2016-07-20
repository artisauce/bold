#include <assert.h>
#include <stdint.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class map {
public:

	const unsigned int type; // Determines type of region.

	tile* content; // Is square. Height/width determined by side.

	const unsigned int side; // Length/side

	worldMap* world; // Pointer to its parant.

	unsigned int* explored; // Determining which tiles are explored. 0 not, 1 seen, 2 visited

	unsigned int playerPosition; // Determines player party position.

	group_t* groups; // Positions of critters and what they are.

	map(unsigned int typeEntered, unsigned int sideEntered);

	~map();

	// seeds

	unsigned int seed; // seed for this area.

	unsigned int offset; // In the matter that this seed could not ever work, an offset is needed to get a "better" seed.

	// elevation --

	unsigned int elevationDirection; // Check numpad. 0 means none. 5 means self (a small hill :P)

	// ---


	//--generation from other map tiles--//

	tile* fromTiles; // Tiles generated from other maps, by index.

	unsigned int* fromPosY; // Y positions of the tiles, by index.

	unsigned int* fromPosX; // X positions of the tiles, by index.

	// generation to other map tiles

	updateExplore(); // To be called when you move a tile or gain a scout -- explores map. DO NOT combine with map update.

	encounter(unsigned int position); // Checks if battle is held at current player pos.

	mapUpdate(); // All AI on the map will move around where they want to go.

	exportMap(); // Export map contents -- efficiently -- for a graphic program to read and interpret.

	spawning(); // Handles spawning of critters at the border of region. Remember the trials from the previous map player visited also continue.

};

class tile {
public:

	char* name; // Tile name.

	unsigned int level; // Determines hierachy of what gets placed over what.

	unsigned int type; // What type of place this is.

	int* stats; // Stats determining how this place can be used. --> ATTACK, HIDE, FLEE. -10 means you can't/large risks, 10 is gauranteed/large bonuses.

	tract_t* tracks; // Tracks. Optdate when ready m8.

	tile(unsigned int typeEntered, unsigned int elevationEntered); // Construction.

	unsigned int elevation; // 0 ocean, 1 river, 2 flat land, 3/3+ hills.

	~tile();
	
};

class worldMap {
public:

	char* name; // World name. Again, 17 characters. Not const because const arrays can't be initialized...?

	map* content; // Is square. Height/width determined by side.

	unsigned int* heightMap; // Each map such have a primary elevation.

	const unsigned int side;

	unsigned int* lock; // Determines lock on region position. 0 means nothing, 1 means current, 2 means OOR (out-of-region), 3 means resetted.
	// This is so that groups can still get generated and chase you.

	unsigned int playerPosition; // Determines player party position.

	worldMap(unsigned int sideEntered);

	unsigned int* capitalHeightPos; // The tallest part of island. [0] is y, [1] is x.

	unsigned int* subCapitalHeightPos; // There are 4. [0] is y of first, [1] is x of first, [2] is y of second... up to [7].

	~worldMap();

	worldMapUpdate(); // All AI on the world map will move around where they want to go.

	exportWorldMap(); // Export map contents -- efficiently -- for a graphic program to read and interpret.

};

