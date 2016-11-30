#include "playerSpace.hpp"
// The weird include needs the definition of the worldMap class for map constructor.

map::map(unsigned int worldSeedInput, int yInput, int xInput, const double pushInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput):
	x(xInput),
	y(yInput),
	worldSeed(worldSeedInput),
	seed(worldSeed + (xInput + (yInput<<16))),
	push(pushInput),
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
	up = NULL;
	down = NULL;
	right = NULL;
	left = NULL;
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMemoryMap[i] = 0;
	}
	if(debug){
		std::cout << "CREATED MAP " << this << " START" << std::endl; 
	}
	activate();

}
/* Maybe one day this will have use. -----
map::map(const map* parentMInput, int yDir, int xDir):
	parentM(parentMInput),
	worldSeed(parentM->worldSeed),
	y((yDir + parentM->y)),
	x((xDir + parentM->x)),
	seed(worldSeed + (x + (y<<16))), // dem bits. This is position-based seeding.
	push(parentM->push),
	mapSide(parentM->mapSide),
	tileSide(parentM->tileSide),
	battlefieldSide(parentM->battlefieldSide),
	diagonal(parentM->diagonal),
	debug(parentM->debug)
{
	if(debug){
    	std::cout << "CREATING MAP " << this << " FOR " << parentM << std::endl; 
    	}
    	activated = false;
	regionMemoryMap = new int[mapSide*mapSide];
	up = NULL;
	down = NULL;
	right = NULL;
	left = NULL;
	for (int i = 0; i < mapSide*mapSide; ++i)
	{
		regionMemoryMap[i] = 0;
	}
	if(debug){
		std::cout << "CREATED MAP " << this << " FOR " << parentM << std::endl; 
	}
	activate();
}
*/
map::map(map const& src): // For copying -- MANDATORY FOR VECTORS, SEE: Rule of Three (C++)
	seed(src.seed),
	parentM(src.parentM),
	worldSeed(src.worldSeed),
	y(src.y),
	x(src.x),
	push(src.push),
	mapSide(src.mapSide),
	tileSide(src.tileSide),
	battlefieldSide(src.battlefieldSide),
	diagonal(src.diagonal),
	debug(src.debug)
{
	activated = src.activated;
	if(debug){
		std::cout << "CREATING MAP CPY " << this <<  std::endl;
	}
	std::cout << "We copied?" << std::endl;
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
			regionMap.emplace_back((src.regionMap)[i]);
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
		std::cout << "CREATED MAP CPY " << this << std::endl;
	}
}

map::~map(){
	if(debug){
		std::cout << "DELETING MAP " << this << std::endl;
	}
	std::cout << "---DELETING Y: " << y << " X: " << x << std::endl;
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
	std::cout << "DONE DELETING MAP " << this << " Y: " << y << " X: " << x << std::endl;
	if(debug){
			std::cout << "DONE DELETING MAP " << this << std::endl;
	}
}

void map::deactivate(){
	if(debug){
		std::cout << "DEACTIVATING MAP " << this << std::endl;
	}
	if(activated == 0){
		std::cout << "ERROR ALREADY DEACTIVATED Y: " << y << " X: " << x << std::endl;
		return;
	}
	activated = 0;
	std::cout << "START DEACTIVATION Y: " << y << " X: " << x << " POINT: " << heightMap[10] << std::endl;
	delete[] heightMap;
	std::cout << "YELL" << std::endl;
	delete[] seedMap;
	regionMap = std::vector<tile>();
	std::cout << "DEACTIVATION Y: " << y << " X: " << x << std::endl;
	if(debug){
			std::cout << "DONE DEACTIVATING MAP " << this << std::endl;
	}
}

void map::activate(){
	// -- For activation
	std::cout << "ACTIVATION Y: " << y << " X: " << x << std::endl;
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
		//std::cout << "EMPLACE" << std::endl;
		// http://stackoverflow.com/questions/4303513/push-back-vs-emplace-back
		regionMap.emplace_back(seedMap[i],this,((int)(i/mapSide)),i%mapSide); // This makes things faster.
		//std::cout << "EMPLACEND" << std::endl;
		//printMap(regionMap[i].tileMap,tileSide);
		if(debug){
			std::cout << "MAP " << this << ": #" << i << " TILE CREATED: " << &(regionMap[i]) << std::endl; 
		}
	}
	if(debug){
		std::cout << "ACTIVATED MAP " << this << std::endl; 
	}
}
