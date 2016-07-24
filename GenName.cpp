#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <ctime>
#include "GenName.h"

std::string kolboldName()
{
	//temp is the name being generated

	//If calling this function a lot at once, same name will be generated, so 
	// add srand(x) where x is the time called in main function,
	// let x=x+1 to make sure each time called will get a new random name
	//srand(x);
	std::string kolbold_first[] = {"Ab","Ad","Ag","Agh","Ak","Al","Am","An","Ar","Az","Bab","Bag","Bar","Baz","Blab","Blar","Blug","Blu","Brag","Daz","Dob","Dok","Dor","Drub","Dur","Dush","Duz","Gab","Gar","Gra","Gash","Graz","Ghab","Ghur","Gli","Glo","Griz","Gro","Gru","Guz","Hag","Hal","Hug","Huk","Hul","Huz","Ib","Id","Ig","Ik","Ir","Kab","Kag","Kir","Kob","Kog","Kra","Kro","Krug","Kug","Mag","Mash","Ma","Mig","Mob","Mu","Naz","Nog","Nok","Nol","Nuk","Nuz","Ob","Og","Or","Oz","Rob","Raz","Rub","Run","Sag","Saz","Ska","Sko","Sku","Sm","Sna","Snu","Sug","Tab","Tag","Th","Thi","To","Toz","Tro","Tug","Tuz","Ug","Ur","Uz"};
	std::string kolbold_rest[] = {"dak","dig","gunk","kog","k","g","og","dush","gorg","zog","duh","bug","bub","tug","ru","ha","nab","buzg","unk","rut","bog","duk","bu","ush","guul","gug","gagh","pug","ga","hu","uk","gob","zud","muk","guh","gha","kub","ok","ld","keetix","ruz","rux","mus","kaa","zalk","zoo","ril","dot","ro","derk","zas","mix"};
	std::string temp; //The name being generated
	int rest=0; //the rest of the syllables
	int start=rand() % 101; //the first random syllable
	temp= kolbold_first[start]; //add the first syllable
	int len=rand() % 2 + 1; //how many syllables to add to the name
	for (int i = 0; i < len; ++i) //loop of adding syllables
	{
		rest=rand() % 52; //add one of the random syllable
		temp=temp+kolbold_rest[rest];
	}
	return temp;
}

std::string IslandName()
{
	std::string Island_prefix[]={"The ","Isla ", "Isla de ", "The island of the "};
	std::string Island_middle[]={"Winter","Summer","Angel","Devil","Black","Overgrown","Shopwreck","Arctic","Collapsing","Stingray","Northern","Eastern","Skeleton","Rugged","Hopless","Homeless","Endless","Bottomless","Dread","Aging","Ancient","Botton","Ivory","Ebony","Rain","Trusk","Relentless","Still","Unmoving","Unknown","Grave","Silent","Voiceless","Unending","Moonless","Calming","Lifeless","Shimmering","Emerald","Untouched","Lost","Asylum","Old","New","Open","Ember","Boiling"};
	std::string Island_end[]={" Enclave"," Key"," Reef"," Ilse"," Chain"," Peninsula"," Archipelago"," Cay"," Atoll"," Haven"};
	std::string temp;

	int rest=0; //the rest of the syllables
	int start=rand() % 2; //the add prefex or not
	if(start==1)
	{
		rest=rand() % 4;
		if(rest==0)
		{
			temp=temp+Island_prefix[0];
		}
		else
		{
			temp=temp+Island_prefix[rest];
			rest=rand() % 47; //add one of the random middle town name
			temp=temp+Island_middle[rest];
			return temp;
		}
	}
	rest=rand() % 47; //add one of the random middle town name
	temp=temp+Island_middle[rest];
	rest=rand() % 10; //add one of the random postfix town name
	temp=temp+Island_end[rest];
	return temp;
}

std::string TownName()
{
	std::string prefix_town_name[]={"Town of ","The settlement of ", "The city of "};
	std::string middle_town_name[]={"Green","Blue","White","Night","Under","Over","Wolf","Oak","Down","Summer","River","Snow","Barrow","Cold","Coast","Haven","High","Water","Wood","Mage","Gold","North","East","South","West","Spring"};
	std::string postfix_town_name[]={"Pit","fox","cliff"," Vally"," Park","den","gale"," Ridge","ford","hill","sing","hold","dale"," Heights","ville","ton","pond","hollow","well","holt","bridge"};
	std::string temp;

	int rest=0; //the rest of the syllables
	int start=rand() % 2; //the add prefex or not
	if(start==1)
	{
		rest=rand() % 3; //add one of the random prefex
		temp=temp+prefix_town_name[rest];
	}
		rest=rand() % 26; //add one of the random middle town name
		temp=temp+middle_town_name[rest];
		rest=rand() % 21; //add one of the random postfix town name
		temp=temp+postfix_town_name[rest];

	return temp;
}