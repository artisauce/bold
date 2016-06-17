#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include "character.h"
#define string std::string

character::character() { //default constructor
	name = "";
	gender = -1;
	race = "";
	specialty = "";
	conditions = new int[0];
}
character::character(string name_2, unsigned int gender_2, string race_2, int* stats_2, string specialty_2){ //Some characteristics identified for constructor
	name = name_2;
	gender = gender_2;
	race = race_2;
	specialty = specialty_2;
	conditions = new int[0];
}
character::~character() { // destructor
	delete [] conditions;
	delete [] items;
	delete stats;
}
void character::move(char c, int steps) { // moves some number of steps North (N) ,  South (S) , etc.
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
group::group() {
	amount = 0;
	members = new character[0];
}
group::~group() {
	delete [] members;
}
void group::move(char c, int steps) { // moves entire group
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
void group::new_member(character* member) { // new member is added
	character* members_original = members;
	amount++;
	members = new character[amount + 1];
	for (int i = 0; i <= amount - 1; i++) {
		members[i] = members_original[i];
	}
	delete members_original;
} 
bool group::remove(string name) { // remove member with given name (due to them seperating, death or otherwise)
	for (int i = 0; i <= amount - 1; i++) {
		if (members[i].name == name) {
			members[i] = members[amount - 1];
			amount--;
			return true;
		}}
	return false;
}
void group::scatter() { // characters no longer gain group benefits (temporarily), mobility is gained
	scattered = true;} 
void group::regroup() { // after scattering 
	scattered = false;}
