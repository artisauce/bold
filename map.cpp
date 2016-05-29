#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class map {
public:

	map(unsigned int typeEntered, unsigned int sideEntered):
	type(typeEntered), // Initialize const values.
	side(sideEntered)
	{

		

	}

};

class tile {
public:

	char* name; // Tile name.

	unsigned int type; // What type of place this is.

	int* stats; // Stats determining how this place can be used. --> ATTACK, HIDE, FLEE. -10 means you can't/risks, 10 is gauranteed/bonuses.

	tract_t* tracks; // Tracks. Optdate when ready m8.
	
};
