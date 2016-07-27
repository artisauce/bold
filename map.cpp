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
	regionMap.reserve(100);
	// For region map, I made it a vector because WAOW.
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		seedMap[i] = rand();
	}
	// For now, we'll just generate one, big island.
	genIsland(rand(), push, 0, 0, mapSide-1, mapSide-1,
    -1, heightMap, mapSide, ySpareList, xSpareList, 
    diagonal, debug);
    for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMap.push_back(tile(seedMap[i],this,((int)(i/mapSide)),i%mapSide,push,tileSide,battlefieldSide,diagonal,debug)); 
	}
}

map::~map(){
	delete[] heightMap;
	delete[] seedMap;
	regionMap = std::vector<tile>();
	/*for (int i = 0; i < mapSide*mapSide; ++i)
	{
		delete regionMap[i];
	}
	delete[] regionMap;*/
}