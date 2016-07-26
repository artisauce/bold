#include "toolkit.hpp"
// A tile in the game area - has its own little map
class tile {
public:
	
	// -- ESSENTIAL
	const unsigned int seed;
	// -- ESSENTIAL

	// -- Settings
	const size_t tileSide;
	const size_t battlefieldSide;
	// -- Settings

	// -- cordLists for randLine
	std::vector<int> ySpareList;
    std::vector<int> xSpareList;
	// -- cordLists for randLine

	// -- Maps
	unsigned int* seedMap;
	unsigned int* tileMap;
	// -- Maps

	tile(unsigned int seedInput, size_t tileSideInput, size_t battlefieldSideInput);
	
};