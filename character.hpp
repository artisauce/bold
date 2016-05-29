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

