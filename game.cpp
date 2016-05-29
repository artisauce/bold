#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct part {
	// FOR ANY PART:
		// 0: Name
		// 1: Parent part
		// 2: Child parts
		// 3: Health - Positive means usable, 0 is useless, negative adds chance to go MISSING.
		// 3: Bleeding - Number is severity, 0 is none, -1 is cannot bleed
		// 4: Stunned - Number is severity, 0 is none, -1 is cannot be stunned
		// 5: Pain - Number is severity, 0 is none, negative is [drugged] threshold (so if you have -5, it'll take 6 pain for you to feel anything.)
		// 6: Comfort - Positive is comfort severity, 0 is meh, negative is discomfort severity
		// 7: Infection - Number is advancement of infection
		// 8: Temperature - 0 is comfortable, negative is cold severity, positive is hot severity.
		// 9: State - "MISSING","OK","NONE","BURNED","ITCHY","FROSTBITE" - None if never had, missing if it was lost (phantom pain). Burned is alt for okay, sensitive. Itchy distracts. Frostbite is bad and you should feel bad.
		// 10: Scarring: Number is severity, negative is (?) smoothness severity, 0 is default
		// 11: Visibility: Number is severity. Zero is none/hidden. -1 is cloaked.

	char* name;
	part* parent;
	double health;
	double bleeding;
	double stunned;
	double pain;
	double comfort;
	double infection;
	double temperature;
	char* state;
	double scarring;
	double visibility;
	
	// 0: Head
		// 0: Skin
		// 1: Internals
		// 2: Skull
		// 3: Brain
		// 4: Right Ear
		// 5: Left Ear
		// 6: Right Eye
		// 7: Left Eye
		// 8: Mouth
		// 9: Teeth
		// 10: Nose
		// 11: Neck
	// 1: Upper Torso
		// 0: Skin
		// 1: Internals
		// 2: Ribcage
		// 3: Heart
		// 4: Right Lung
		// 5: Left Lung
	// 2: Lower Torso
		// 0: Skin
		// 1: Internals
		// 2: Intestines
		// 3: Groin
	// 3: Right Arm
		// 0: Skin
		// 1: Internals
		// 2: Elbow
		// 3: Hand
	// 4: Left Arm
		// 0: Skin
		// 1: Internals
		// 2: Elbow
		// 3: Hand
	// 7: Right Leg
		// 0: Skin
		// 1: Internals
		// 2: Knee
		// 3: Foot
	// 9: Left Leg
		// 0: Skin
		// 1: Internals
		// 2: Knee
		// 3: Foot
	
} part_t;

struct effect {
	char* name; // If NULL, will not display no matter what in visibility. This should be what it says, unless trolling.

	char* description; // Describe effect here
.
	double visible; // If negative one, visible only at death screen, 0 visible anytime, positive is severity (determined with medical care/awareness.)
	// Negative anything but one means never visible, even in death. Ultitroll. Doesn't mean that another effect can reveal it... :D (It's douable.)

	int typeOf; // If 0, have effect until time runs out. If 1, apply effect on top of each turn per subtime, then revert back to original at end. If 2,
	// then it will apply effect until half time, then start applying reverse effect -- in case of math rounding badness, apply original at end anyways.

	bool perma; // If 1, will not revert back to original values when done.

	bool set; // If 1, and type is 0, then stat will be set to, not applied.

	double subTimeOrig; // Reverts back to this when sub time is zero.

	double subTimeEffect; // When zero, will apply effect, and go back to original sub time.

	double timeEffect; // Will go down until zero, then apply original if not perma.

	double timeEffectOriginal; // Keep track if using half-time (tyepOf type 2.)

	int numOfEffects; // Number of effects.

	// Indexes are in line here.

	double* originals; // Original stats to revert to if not perma.
	double* effects; // Application.
	double** location; // Where effects are applied.

	//
} effect_t;

struct item {
	char* name; // Please don't be NULL;
	char* description; // Describe object here
	bool wearable; // Can you wear it?
		bool* covers; // List of what it covers.
		// 0: Head
		// 1: Upper Torso
		// 2: Lower Torso
		// 3: Right Arm
		// 4: Left Arm
		// 7: Right Leg
		// 9: Left Leg
		double warmth; // 0 for none, positive for warth, negative (icecube vest?) cools.
	double* types; // Protection against types of damages, or amount of damage dealt
	double weight; // How heavy;
	double volume; // How much space it takes.
	double cargo; // How much cargo space it has.
	// 0: Blunt Damage
	// 1: Cutting Damage
	// 2: Piercing Damage
	// 3: Bullet Damage
	double health; // 0 is destroyed. Positive is health remaining. Negative one is indestructable.
	double timeToUse; // To hit (determing DPS) or to wear.
	effect_t** effects; // Effects when worn.
		
} item_t;

class character {
public:
	char* name; // Character name
	char* description; // Character description.
	unsigned int gender; // 0 male, 1 female, 2 it's complicated
	unsigned int state; // 0 human, 1 vampire, 2 werewolf, 3 werewolf transformed, 4 zombie, 5 robot
	double* age;
	// 0: Mental Age
	// 1: Mental Age Rate - 1 norm
	// 2: Physical Age
	// 3: Physical Age Rate - 1 norm
	// 4: Percieved Age
	// 5: Actual Age
	double** stats;
	// For every stat:
		//0: Current Value
		//1: Set Value
		//2: Start Value

	// 0: Strength (ST) - Zero Incapitates. Negative kills.
	// 1: Dexterity (DX) - Zero Incapitates. Negative kills.
	// 2: Hardiness (HD) - Negative causes heart failure.
	// 3: Quality (QU)
	// 4: Intellect (IN)  - Zero Incapitates and damages memory/skills. Negative kills.
	// 5: Wit (WT)  - Zero Incapitates.
	// 6: Willpower (WP)  - Zero Incapitates. Negative ? causes suicide.
	// 7: Leadership (LD) (aka Persuasion/Charisma) - Zero mutes a person.
	part_t* main; // Contains main parts.
	// 0: Head - NEED OR DIE
	// 1: Upper Torso - NEED OR DIE
	// 2: Lower Torso
	// 3: Right Arm
	// 4: Left Arm
	// 5: Right Leg
	// 6: Left Leg

	effect_t* effectQueue;
	// Effects apply from first in to last in.

	item_t* inventory;
	// Whoo.

	item_t* wornItems;
	// Maybe a limit?

	// TODO
	// 1: git gud
	// 2: attributes: tallness, weight, attractiveness, hair, eye color...
	// 3: skills
	// 4: MAYBE: memory queue? contains info on other characters. slow forgetting.
	// 5: update character creation to reflect this
	// 6: start making other functions
	// good luck

	character(double* ageList,double* statsStart,bool* parts);
	//All indexes are relative to ones above, and the one below. Parts list determine whether you have it or not.
	//Spawning people without brains will make zombies.
	//Spawning people without skin is bad and you should feel bad.

	// 0: Head
		// 1: Skin
		// 2: Internals
		// 3: Skull
		// 4: Brain
		// 5: Right Ear
		// 6: Left Ear
		// 7: Right Eye
		// 8: Left Eye
		// 9: Mouth
		// 10: Teeth
		// 11: Nose
		// 12: Neck
	// 13: Upper Torso
		// 14: Skin
		// 15: Internals
		// 16: Ribcage
		// 17: Heart
		// 18: Right Lung
		// 19: Left Lung
	// 20: Lower Torso
		// 21: Skin
		// 22: Internals
		// 23: Intestines
		// 24: Groin
	// 25: Right Arm
		// 26: Skin
		// 27: Internals
		// 28: Elbow
		// 29: Hand
	// 30: Left Arm
		// 31: Skin
		// 32: Internals
		// 33: Elbow
		// 34: Hand
	// 35: Right Leg
		// 36: Skin
		// 37: Internals
		// 38: Knee
		// 39: Foot
	// 40: Left Leg
		// 41: Skin
		// 42: Internals
		// 43: Knee
		// 44: Foot


	~character()
	updateAge();
	updateStats();
	updateEffects();
	
};

