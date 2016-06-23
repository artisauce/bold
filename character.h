#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>
#define Number_of_Stats 2


using namespace std;

class Weapon {
public:
	string name; //weapon name
	int strength; //weapon strength

	Weapon(); //Default constructor
	Weapon(string name_2, int strength_2); //Constructor with some attributes specified 
	//~Weapon(); // destructor
};


class Character {
public:

	string name; //character name 
	Weapon weapon; // either unarmed or one weapon per character 

	int y; int x; // (i,j) or (y,x)
	int health; // General health for general temporary solvents.
	int stats[Number_of_Stats]; // Strength, Speed

	bool retreated; // during battle

	Character(); //Default constructor
	Character(string name_2,  int* stats_2, int health,  Weapon weapon_2); // For full creation.
	//~Character(); //destructor
};

Character random_character_unarmed();


class Group { 
public:
	int amount; // the amount of members in the group
	Character* members; //dynamic array containing members of the group
	int y; int x; // (i,j) or (y,x)

	 Group(); //initialize empty group
	 Group(Character* characters , int amount_2); // makes a group of given characters
	 //~Group(); //default destructor

	void move(char c,int steps); // moves entire group
	void new_member(Character member);// new member is added 
	bool remove(string name); // remove member with given name (due to death or otherwise)

	bool hasRetreated(); //during battle
	bool isEmpty(); //indicates if the group has no members
	void remove_goners(); // remove members with health less than or equal to zero ,

	void printHealth(); // prints an array of representing the health of the members
	void printAttack(); // prints an array of representing the attack values of the members
};
