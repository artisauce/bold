#include "map.hpp"
// The weird include needs the definition of the map class for tile constructor.
tile::tile(unsigned int seedInput, const map* parentMInput, const int yInput, 
	const int xInput, const double pushInput, size_t tileSideInput, size_t battlefieldSideInput,
	const bool diagonalInput, const bool debugInput):
	seed(seedInput),
	parentM(parentMInput),
	y(yInput),
	x(xInput),
	height(parentMInput->heightMap[y*(parentMInput->mapSide) + x]),
	push(pushInput),
	tileSide(tileSideInput),
	battlefieldSide(battlefieldSideInput),
	diagonal(diagonalInput),
	debug(debugInput)
{
	srand(seed);
	tileMap = new int[tileSide*tileSide];
	seedMap = new int[tileSide*tileSide];
	for (int i = 0; i < tileSide*tileSide; ++i)
	{
		seedMap[i] = rand();
	}
	genTile(rand(),push,y,x,parentM->heightMap,parentM->mapSide,tileMap,tileSide,diagonal,debug);
	tileMap[20] = 5;
	printMap(tileMap,tileSide);

	std::cout << "CREATING TILEMAP " << this << " FOR " << parentM << " FOR " << parentM->parentW << std::endl;
}

tile::~tile(){
	std::cout << "DELETING TILEMAP " << this << " FOR " << parentM << " FOR " << parentM->parentW << std::endl;
	printMap(tileMap,tileSide);
	delete[] tileMap;
	delete[] seedMap;
	std::cout << "DONE DELETING TILEMAP " << this << " FOR " << parentM << " FOR " << parentM->parentW << std::endl;
}