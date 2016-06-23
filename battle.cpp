#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include "battle.h"
#define NOT !

using namespace std;

void battle_Player_Attacks(Group Attackers, Group Defenders) { // Case when the player attacks a group controlled by the computer

	while (NOT(Attackers.isEmpty() || Defenders.isEmpty() || Attackers.hasRetreated() || Defenders.hasRetreated())) { //conditions for the battle continuing
	
		cout << "You are attacking: " << endl;
		cout << endl;

		cout << "Attacker Healths : ";
		Attackers.printHealth();

		cout << "Attacker Attacks : ";
		Attackers.printAttack();

		cout << "Defender Healths : ";
		Defenders.printHealth();

		cout << "Defender Attacks : ";
		Defenders.printAttack();
		cout << endl;
		
		for (int i = 0; i <= Attackers.amount - 1; i++) { //Atackers designate targets by index (perhaps make the designation by name)
			int target_index;
			cout << "target for member " << i <<  ": ";
			cin >> target_index;

			((Defenders.members)[target_index]).health -= (Attackers.members[i]).stats[0]; //stats[0] corresponds to strength
			}

		Defenders.remove_goners();

		for (int i = 0; i <= Defenders.amount - 1; i++) { //Defenders designate targets by index (perhaps make the designation by name)

			int target_index = rand() % (Attackers.amount);

			((Attackers.members)[target_index]).health -= (Defenders.members[i]).stats[0]; //stats[0] corresponds to strength
				
		}

		Attackers.remove_goners();	
		cout << endl;
	}
	cout << "Battle has finished" << endl;
}

void battle_Player_Defends(Group Attackers, Group Defenders) { // Case when the player is attacked  a group controlled by the computer

	while (NOT(Attackers.isEmpty() || Defenders.isEmpty() || Attackers.hasRetreated() || Defenders.hasRetreated())) { //conditions for the battle continuing

		cout << "You are defending: " << endl;
		cout << endl;

		cout << "Attacker Healths : ";
		Attackers.printHealth();

		cout << "Attacker Attacks : ";
		Attackers.printAttack();

		cout << "Defender Healths : ";
		Defenders.printHealth();

		cout << "Defender Attacks : ";
		Defenders.printAttack();

		cout << endl;

		for (int i = 0; i <= Attackers.amount - 1; i++) { //Atackers designate targets by index (perhaps make the designation by name)

			int target_index = rand() % (Defenders.amount);

			((Defenders.members)[target_index]).health -= (Attackers.members[i]).stats[0]; //stats[0] corresponds to strength
		}
		Defenders.remove_goners();

		for (int i = 0; i <= Defenders.amount - 1; i++) { //Defenders designate targets by index (perhaps make the designation by name)

			int target_index;
			cout << "target for member " << i << ": ";
			cin >> target_index;

			((Defenders.members)[target_index]).health -= (Attackers.members[i]).stats[0]; //stats[0] corresponds to strength
		}
		Attackers.remove_goners();
	}
	cout << "Battle has finished" << endl; 
}
