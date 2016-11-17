#include "worldMap.hpp"
// The weird include needs the definition of the worldMap class for map constructor.


map::map(unsigned int worldSeedInput, const double pushInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput):
	worldSeed(worldSeedInput),
	seed(worldSeed),
	push(pushInput),
	x(0),
	y(0),
	parentM(NULL),
	mapSide(mapSideInput),
	tileSide(tileSideInput),
	battlefieldSide(battlefieldSideInput),
	diagonal(diagonalInput),
	debug(debugInput)
{
	if(debug){
    	std::cout << "CREATING MAP " << this << " START" << std::endl; 
    }
    activated = false;
	regionMemoryMap = new int[mapSide*mapSide];
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMemoryMap[i] = 0;
	}
	if(debug){
		std::cout << "CREATED MAP " << this << " START" << std::endl; 
	}
	activate();

}

map::map(const map* parentMInput, int yDir, int xDir):
	parentM(parentMInput),
	worldSeed(parentM->worldSeed),
	y((yDir + parentM->y)),
	x((xDir + parentM->x)),
	seed(worldSeed + (x + (y<<16))), // dem bits. This is position-based seeding.
	push(parentW->push),
	mapSide(parentW->mapSide),
	tileSide(parentW->tileSide),
	battlefieldSide(parentW->battlefieldSide),
	diagonal(parentW->diagonal),
	debug(parentW->debug)
{
	if(debug){
    	std::cout << "CREATING MAP " << this << " FOR " << parentM << std::endl; 
    }
    activated = false;
	regionMemoryMap = new int[mapSide*mapSide];
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMemoryMap[i] = 0;
	}
	if(debug){
		std::cout << "CREATED MAP " << this << " FOR " << parentM << std::endl; 
	}
	if(yDir > 0 && xDir > 0){
		
	}
}

map::map(map const& src): // For copying -- MANDATORY FOR VECTORS, SEE: Rule of Three (C++)
	seed(src.seed),
	parentM(src.parentM),
	y(src.y),
	x(src.x),
	push(src.push),
	mapSide(src.mapSide),
	tileSide(src.tileSide),
	battlefieldSide(src.battlefieldSide),
	diagonal(src.diagonal),
	debug(src.debug)
{
	acivated = src.activated;
	if(debug){
		std::cout << "CREATING MAP CPY " << this << " FOR " << parentW << std::endl;
	}
	if(activated){
		heightMap = new int[mapSide*mapSide];
		seedMap = new int[mapSide*mapSide];
		regionMemoryMap = new int[mapSide*mapSide];
		regionMap.reserve(mapSide*mapSide);
		for (int i = 0; i < mapSide*mapSide; ++i)
		{
			heightMap[i] = src.heightMap[i];
			seedMap[i] = src.seedMap[i];
			regionMemoryMap[i] = src.regionMemoryMap[i];
			regionMap.push_back(tile((src.regionMap)[i]));
		}
		ySpareList = src.ySpareList;
		xSpareList = src.xSpareList;
	}
	else{
		for (int i = 0; i < mapSide*mapSide; ++i)
		{
			regionMemoryMap[i] = src.regionMemoryMap[i];
		}
	}
	if(debug){
		std::cout << "CREATED MAP CPY " << this << " FOR " << parentW << std::endl;
	}
}

map::~map(){
	if(debug){
		std::cout << "DELETING MAP " << this << std::endl;
	}
	if(activated){
		delete[] heightMap;
		delete[] seedMap;
		delete[] regionMemoryMap;
		regionMap = std::vector<tile>();
	}
	else{
		regionMap = std::vector<tile>(); // just in case
		delete[] regionMemoryMap;
	}
	if(debug){
			std::cout << "DONE DELETING MAP " << this << std::endl;
	}
}

map::deactivate(){
	if(debug){
		std::cout << "DEACTIVATING MAP " << this << std::endl;
	}
	if(activated == 0){
		std::cout << "ERROR ALREADY DEACTIVATED Y: " << y << " X: " << x << std::endl;
		return;
	}
	activated = 0;
	delete[] heightMap;
	delete[] seedMap;
	regionMap = std::vector<tile>();
	if(debug){
			std::cout << "DONE DEACTIVATING MAP " << this << std::endl;
	}
}

map::activate(){
	// -- For activation
	if(activated == 1){
		std::cout << "ERROR ALREADY ACTIVATED Y: " << y << " X: " << x << std::endl;
		return;
	}
	activated = 1;
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
		std::cout << "ACTIVATED MAP " << this << " FOR " << parentW << std::endl; 
	}
}

map* map::update(int yDir, int xDir){
	srand(this.seed); // so it's consistent as it gens
	map* current = this;
	int yCounter = yDir;
	int xCounter = xDir;
	while(yDir != 0)
	{
		if(yDir < 0){
			if(this.down != NULL){

			}
		}
	}
}