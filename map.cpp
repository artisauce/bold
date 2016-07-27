#include "worldMap.hpp"
// The weird include needs the definition of the worldMap class for map constructor.


map::map(unsigned int seedInput, const worldMap* parentWInput, const int yInput, 
	const int xInput, const double pushInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput):
	seed(seedInput),
	parentW(parentWInput),
	y(yInput),
	x(xInput),
	push(pushInput),
	mapSide(mapSideInput),
	tileSide(tileSideInput),
	battlefieldSide(battlefieldSideInput),
	diagonal(diagonalInput),
	debug(debugInput)
{
	srand(seed);
	heightMap = new int[mapSide*mapSide];
	seedMap = new int[mapSide*mapSide];
	regionMap.reserve(mapSide*mapSide);
	// For region map, I made it a vector because WAOW.
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		seedMap[i] = rand();
	}
	// For now, we'll just generate one, big island.
	genIsland(rand(), push, 0, 0, mapSide-1, mapSide-1,
    -1, heightMap, mapSide, ySpareList, xSpareList, 
    diagonal, debug);
    printMap(heightMap,mapSide);
    std::cout << "CREATING MAP " << this << " FOR " << parentW << std::endl; 
    for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMap.push_back(tile(seedMap[i],this,((int)(i/mapSide)),i%mapSide,push,tileSide,battlefieldSide,diagonal,debug));
		std::cout << "MAP " << this << " #" << i << " TILE CREATED: " << &(regionMap[i]) << std::endl; 
	}
	std::cout << "CREATED MAP " << this << " FOR " << parentW << std::endl; 

}

map::~map(){
	std::cout << "DELETING MAP " << this << std::endl;
	delete[] heightMap;
	delete[] seedMap;
	std::cout << "DELETING MAP " << this << std::endl;
	printMap(regionMap[0].tileMap,tileSide);
	regionMap = std::vector<tile>();
	/*for (int i = 0; i < mapSide*mapSide; ++i)
	{
		delete regionMap[i];
	}
	delete[] regionMap;*/
}