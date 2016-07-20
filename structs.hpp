#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

