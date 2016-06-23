#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include "battle.h"
#define NOT !




void main() {

	/*
	//Testing various Group class methods
	Group Grp;
	for (int i = 0; i <= 6 - 1; i++) {
		Grp.new_member(random_character_unarmed());
	}
	Grp.printHealth();

	Grp.remove((Grp.members[3]).name);
	Grp.printHealth();

	Grp.remove_goners();
	Grp.printHealth();


	int input;
	cin >> input;  */


	Group Grp_1;
	for (int i = 0; i <= 3 - 1; i++) {
		Grp_1.new_member(random_character_unarmed());
	}

	Group Grp_2;
	for (int i = 0; i <= 3 - 1; i++) {
		Grp_2.new_member(random_character_unarmed());
	}

	battle_Player_Attacks(Grp_1, Grp_2);


	int input;
	cin >> input;


}
