#include "map.hpp"
// The weird include needs the definition of the tile class for tile constructor.
battlefield::battlefield(const tile* parentTInput, const int yInput, const int xInput, int specialTiles):
	seed(parentTInput->seed), // It's now the same when done in same tile. Woo.
	parentT(parentTInput),
	y(yInput),
	x(xInput),
	height(parentT->tileMap[y*(parentT->tileSide)  + x]),
	battlefieldSide(parentT->battlefieldSide),
	debug(parentT->debug)
{
	if(debug){
		std::cout << "CREATING BATTLEFIELD " << this << " FOR " << parentT << " FOR " << parentT->parentM << std::endl;
	}
	unsigned int originalSeed = rand(); // From in-game. Should be unique each time.
	srand(seed);
	//int treeStandard = 7;
	//int treeDeviation = 2;
	double maxDensity = 0.15; // To be generalized from biome/map.
	if(height-3 > 0){
		maxDensity = maxDensity - ((double)(height-3))*(maxDensity/5); // to be generalized from biome/map instead later.
	}
	std::cout << std::endl;
	std::cout << "HEIGHT: " << height << std::endl;
	// TODO: Cliff battles. This will be tricky.
	battleMap = new int[battlefieldSide*battlefieldSide];
	for(int i = 0; i<(battlefieldSide*battlefieldSide); i++){
		battleMap[i] = (-specialTiles)-2;
	}
	unsigned int amount = (unsigned int)(((double)(battlefieldSide*battlefieldSide))*maxDensity);
	if(height){
		while(amount>0){
			//battleMap[((rand()%battlefieldSide)*battlefieldSide)+(rand()%battlefieldSide)] = 
			//				treeStandard + (
			//				(rand()%((treeDeviation*2)+1))-treeDeviation
			//				);
			battleMap[((rand()%battlefieldSide)*battlefieldSide)+(rand()%battlefieldSide)] = (-specialTiles)-3;
			amount--;
		}
	}
	if(debug){
		std::cout << "CREATED BATTLEFIELD "<< this << " FOR " << parentT << " FOR " << parentT->parentM <<  std::endl;
	srand(originalSeed);
	}
}

battlefield::battlefield(battlefield const& src): // For copying -- MANDATORY FOR VECTORS, SEE: Rule of Three (C++). We MAY need this in the future!
	seed(src.seed),
	parentT(src.parentT),
	y(src.y),
	x(src.x),
	height(src.height),
	battlefieldSide(src.battlefieldSide),
	debug(src.debug)
{
	if(debug){
		std::cout << "CREATING BATTLEFIELD CPY " << this << " FOR " << parentT << " FOR " << parentT->parentM << std::endl;
	}
	battleMap = new int[battlefieldSide*battlefieldSide];
	for (int i = 0; i < battlefieldSide*battlefieldSide; ++i)
	{
		//std::cout << i << std::endl;
		battleMap[i] = src.battleMap[i];
	}
	if(debug){
		std::cout << "CREATED BATTLEFIELD CPY " << this << " FOR " << parentT << " FOR " << parentT->parentM << std::endl;
	}
}


battlefield::~battlefield(){
	if(debug){
		std::cout << "DELETING BATTLEFIELD " << this << " FOR " << parentT << " FOR " << parentT->parentM << " FOR " << std::endl;
	}
	delete[] battleMap;
	if(debug){
		std::cout << "DONE DELETING BATTLEFIELD " << this << " FOR " << parentT << " FOR " << parentT->parentM <<  std::endl;
	}
}
