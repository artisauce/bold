#include "map.hpp"
// The weird include needs the definition of the map class for tile constructor.
tile::tile(unsigned int seedInput, const map* parentMInput, const int yInput, 
	const int xInput):
	seed(seedInput),
	parentM(parentMInput),
	y(yInput),
	x(xInput),
	height(parentMInput->heightMap[y*(parentM->mapSide) + x]),
	push(parentM->push),
	tileSide(parentM->tileSide),
	battlefieldSide(parentM->battlefieldSide),
	diagonal(parentM->diagonal),
	debug(parentM->debug)
{
	if(debug){
		std::cout << "CREATING TILEMAP " << this << " FOR " << parentM << std::endl;
	}
	srand(seed);
	tileMap = new int[tileSide*tileSide];
	seedMap = new int[tileSide*tileSide];
	tileMemoryMap = new int[tileSide*tileSide];
	for (int i = 0; i < tileSide*tileSide; ++i)
	{
		tileMemoryMap[i] = 0;
		seedMap[i] = rand();
	}
	genTile(rand(),push,y,x,parentM->heightMap,parentM->mapSide,tileMap,tileSide,diagonal,debug);
	//for (int i = 0; i < tileSide*tileSide; ++i)
	//{
	//	if(i%tileSide == 0){
	//		std::cout << std::endl;
	//	}
	//	std::cout << tileMap[i];
	//}
	//std::cout << std::endl;
	//tileMap[20] = 5;
	//printMap(tileMap,tileSide);
	if(debug){
		std::cout << "CREATED TILEMAP " << this << " FOR " << parentM << std::endl;
	}
}

tile::tile(tile const& src): // For copying -- MANDATORY FOR VECTORS, SEE: Rule of Three (C++)
	seed(src.seed),
	parentM(src.parentM),
	y(src.y),
	x(src.x),
	height(src.height),
	push(src.push),
	tileSide(src.tileSide),
	battlefieldSide(src.battlefieldSide),
	diagonal(src.diagonal),
	debug(src.debug)
{
	if(debug){
		std::cout << "CREATING TILEMAP CPY " << this << " FOR " << parentM  << std::endl;
	}
	tileMap = new int[tileSide*tileSide];
	seedMap = new int[tileSide*tileSide];
	tileMemoryMap = new int[tileSide*tileSide];
	for (int i = 0; i < tileSide*tileSide; ++i)
	{
		//std::cout << i << std::endl;
		tileMap[i] = src.tileMap[i];
		seedMap[i] = src.seedMap[i];
		tileMemoryMap[i] = src.tileMemoryMap[i];
	}
	ySpareList = src.ySpareList;
	xSpareList = src.xSpareList;
	if(debug){
		std::cout << "CREATED TILEMAP CPY " << this << " FOR " << parentM << std::endl;
	}
}


tile::~tile(){
	if(debug){
		std::cout << "DELETING TILEMAP " << this << " FOR " << parentM << std::endl;
	}
	//printMap(tileMap,tileSide);
	delete[] tileMap;
	delete[] seedMap;
	delete[] tileMemoryMap;
	if(debug){
		std::cout << "DONE DELETING TILEMAP " << this << " FOR " << parentM <<  std::endl;
	}
}
