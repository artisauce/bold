#include "worldMap.hpp"
// The weird include needs the definition of the worldMap class for map constructor.


map::map(unsigned int seedInput, const worldMap* parentWInput, const int yInput, const int xInput):
	seed(seedInput),
	parentW(parentWInput),
	y(yInput),
	x(xInput),
	push(parentW->push),
	mapSide(parentW->mapSide),
	tileSide(parentW->tileSide),
	battlefieldSide(parentW->battlefieldSide),
	diagonal(parentW->diagonal),
	debug(parentW->debug)
{
	if(debug){
    	std::cout << "CREATING MAP " << this << " FOR " << parentW << std::endl; 
    }
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
    //printMap(heightMap,mapSide);
    for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMap.push_back(tile(seedMap[i],this,((int)(i/mapSide)),i%mapSide));
		//printMap(regionMap[i].tileMap,tileSide);
		if(debug){
			std::cout << "MAP " << this << ": #" << i << " TILE CREATED: " << &(regionMap[i]) << std::endl; 
		}
	}
	if(debug){
		std::cout << "CREATED MAP " << this << " FOR " << parentW << std::endl; 
	}

}

map::map(map const& src): // For copying -- MANDATORY FOR VECTORS, SEE: Rule of Three (C++)
	seed(src.seed),
	parentW(src.parentW),
	y(src.y),
	x(src.x),
	push(src.push),
	mapSide(src.mapSide),
	tileSide(src.tileSide),
	battlefieldSide(src.battlefieldSide),
	diagonal(src.diagonal),
	debug(src.debug)
{
	if(debug){
		std::cout << "CREATING MAP CPY " << this << " FOR " << parentW << std::endl;
	}
	heightMap = new int[mapSide*mapSide];
	seedMap = new int[mapSide*mapSide];
	regionMap.reserve(mapSide*mapSide);
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		heightMap[i] = src.heightMap[i];
		seedMap[i] = src.seedMap[i];
		regionMap.push_back(tile((src.regionMap)[i]));
	}
	ySpareList = src.ySpareList;
	xSpareList = src.xSpareList;
	if(debug){
		std::cout << "CREATED MAP CPY " << this << " FOR " << parentW << std::endl;
	}
}

map::~map(){
	if(debug){
		std::cout << "DELETING MAP " << this << std::endl;
	}
	delete[] heightMap;
	delete[] seedMap;
	regionMap = std::vector<tile>();
	if(debug){
			std::cout << "DONE DELETING MAP " << this << std::endl;
	}
}
