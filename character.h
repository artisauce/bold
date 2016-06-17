
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>

#define string std::string

class character {
public:

	string name;
	// Character name
	// 17 characters should be good -- the extra for a space.


	unsigned int gender; // 0 male, 1 female, 2 it's complicated

	string race; // We'll eventually make a dictionary that associates an unsigned int with a race. For now, it's flexible.
	string specialty; // Healer, Scout, Alchemist, etc.

	string* items;  // the items which the character is currently carrying 

	int y; int x; // (i,j) or (y,x)
	int health; // General health for general temporary solvents.
	int maxHealth;

	int* conditions; // Poisoned, Burned, Wounded, etc. 

	int stats[7]; // Strength, Dexterity, Speed, Defense, Confidence , Stamina, Intelligence

	character();
	character(string name_2, unsigned int gender_2, string race_2, int* stats_2, string specialty_2); // For full creation.

	//void character(char* race, char* type, int size); // For group creation. You know, AI.

	 ~character();
	void battle(character* enemy);
	void move(char c, int steps); // moves some number of steps North (N) ,  South (S) , etc.
};

class group { //when characters are in a group, they gain various bonuses

	int amount;
	character* members; //dynamic array containing members of the group
	int y; int x; // (i,j) or (y,x)
	 group(); //initialize empty group
	 group(character* characters); // makes a group of given characters
	 ~group();
	void move(char c,int steps); // moves entire group
	void new_member(character* member);// new member is added 
	bool remove(string name); // remove member with given name (due to death or otherwise)
	void scatter(); // characters no longer gain group benefits (temporarily), mobility is gained
	bool scattered;
	void regroup(); // after scattering 
};


