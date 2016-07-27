#include "worldMap.hpp"
worldMap::worldMap(unsigned int seedInput, const double pushInput, size_t worldMapSideInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput):
	seed(seedInput),
	push(pushInput),
	worldMapSide(worldMapSideInput),
	mapSide(mapSideInput),
	tileSide(tileSideInput),
	battlefieldSide(battlefieldSideInput),
	diagonal(diagonalInput),
	debug(debugInput)
{
	if(debug){
    	std::cout << "CREATING WORLDMAP " << this << std::endl; 
    }
	srand(seed);
	seedMap = new int[worldMapSide*worldMapSide];
	bigMap.reserve(worldMapSide*worldMapSide);
	for (int i = 0; i < worldMapSide*worldMapSide; ++i)
	{
		seedMap[i] = rand();
	}
    for (int i = 0; i < worldMapSide*worldMapSide; ++i)
	{
		bigMap.push_back(map(seedMap[i],this,((int)(i/worldMapSide)),i%worldMapSide,push,mapSide,tileSide,battlefieldSide,diagonal,debug)); 
		if(debug){
			std::cout << "WORLDMAP " << this << ": #" << i << " MAP CREATED: " << &(bigMap[i]) << std::endl; 
		}
	}
	if(debug){
    	std::cout << "CREATED WORLDMAP " << this << std::endl; 
    }
}

worldMap::~worldMap(){
	if(debug){
		std::cout << "DELETING WORLDMAP " << this << std::endl;
	}
	delete[] seedMap;
	bigMap = std::vector<map>();
	if(debug){
		std::cout << "DONE DELETING WORLDMAP " << this << std::endl;
	}
}