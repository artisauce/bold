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

	tile(unsigned int typeEntered, unsigned int elevationEntered) {
		if(typeEntered == 0){
			name[] = "FOREST";
			stats[3] = {0,0,0};
			level = 1 // 0 ocean, 1 basic tiles, 2/2+ other stuff;
			elevation = elevationEntered;
		}
		type = typeEntered;
		tracks = NULL;
	}
};

class worldMap {
public:

	worldMap(unsigned int sideEntered):
	side(sideEntered)
	{
		heightMap[(side*side)];
		memset(heightMap,0,sizeof(unsigned int)); // all was once ocean
		
		
	}

};
