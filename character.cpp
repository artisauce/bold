#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include "character.h"

#define Number_of_Stats 2

using namespace std; 

Character::Character() { // default constructor
	name = "";
	Weapon w;
	weapon = w; 
	retreated = false;
}

Character::Character(string name_2, int* stats_2, int health_2, Weapon weapon_2) { //Some characteristics identified for constructor

	name = name_2;
	for (int i = 0; i <= Number_of_Stats - 1; i++) {
		stats[i] = stats_2[i];
		weapon = weapon_2; 
		health = health_2; 
		retreated = false; 
	}
}

/*
Character::~Character() { // destructor

	delete [] stats;
} */ 




Character random_character_unarmed() {

	srand(time(NULL));
	string name_2 = to_string(rand());
	int stats_2[Number_of_Stats];
	for (int i = 0; i <= Number_of_Stats - 1; i++) {
		stats_2[i] = rand() % 10;
	}
	int health_2 = rand() % 50 + 1; 
	Weapon w;

	Character character_to_return(name_2, stats_2, health_2, w);
	return character_to_return;
	
}






Group::Group() { //default constructor
	amount = 0;
	members = new Character[0];
}



Group::Group(Character* characters, int amount_2) { //makes a group of given characters 
	members = new Character[amount_2];
	for (int i = 0; i <= amount_2 - 1; i++) {
		members[i] = characters[i]; 
	}
	amount = amount_2; 
}



/*
Group::~Group() {
	delete [] members;} */





void Group::move(char c, int steps) { // moves entire group
	if (c == 'N') {
		y += steps;
	}
	if (c == 'S') {
		y -= steps;
	}
	if (c == 'W') {
		x -= steps;
	}
	if (c == 'E') {
		x += steps;
	}
}   





void Group::new_member(Character member) { // new member is added

	if (amount == 0) {
		members = new Character[1];
		members[0] = member; 
		amount++;
		return;
	}

	Character* members_original = members;
	members = new Character[amount+1];
	for (int i = 0; i <= amount - 1; i++) {
		members[i] = members_original[i];
	}
	amount++;
	members[amount - 1] = member;
	//delete [] members_original;
} 



bool Group::remove(string name) { //remove member with given name (due to them seperating, death or otherwise)
	for (int i = 0; i <= amount - 1; i++) {
		if (members[i].name == name) {
			members[i] = members[amount - 1];
			amount--;
			return true;
		}}
	return false;
}

bool Group::hasRetreated() { // during battle 
	for (int i = 0; i <= amount - 1; i++) {

		if (members[i].retreated == false ) {
			return false;
		}
 
	}
	return true;
}




bool Group::isEmpty() {  //indicates if the group has no members 

	if (amount == 0) {
		return true;
}
	return false;
}


void Group::remove_goners() { // remove members with health less than or equal to zero ,

	for (int i = 0; i <= amount - 1; i++) {
		if (members[i].health <= 0) {
			members[i] = members[amount - 1];
			amount--;
		}
	}

}



void Group::printHealth() { // prints an array of representing the health of the members

	if (this->isEmpty() == true) {
		cout << "Empty" << endl;
	}
	cout << '[';
	for (int i = 0; i <= amount-1; i++) {
		cout << members[i].health << " ";
	}
	cout << ']';
	cout << endl;
}



void Group::printAttack() { // prints an array of representing the health of the members

	if (this->isEmpty() == true) {
		cout << "Empty" << endl;
	}
	cout << '[';
	for (int i = 0; i <= amount - 1; i++) {
		cout << (members[i].stats)[0] << " ";
	}
	cout << ']';
	cout << endl;
}



Weapon::Weapon() { //Default constructor
	name = "";
	strength = 0; 
}


Weapon::Weapon(string name_2, int strength_2) { //Constructor with certain attributes specified 
	name = name_2;
	strength = strength_2; 
}
