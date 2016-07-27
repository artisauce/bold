#include "map.hpp"
//clang maptest.cpp map.cpp -lm -lstdc++ -std=c++11
// World map - total game area

class worldMap {
public:

	// -- ESSENTIAL
	const unsigned int seed;
	// -- ESSENTIAL

	// -- Settings
	const size_t worldMapSide;
	const size_t mapSide;
	const size_t tileSide;
	const size_t battlefieldSide;
	// -- Settings

	// -- cordLists for randLine
	std::vector<int> ySpareList;
    std::vector<int> xSpareList;
	// -- cordLists for randLine

	// -- Maps
	unsigned int* seedMap;
	map* bigMap; // Damn naming
	// -- Maps

	worldMap(unsigned int seedInput,size_t worldMapSideInput, size_t mapSideInput, size_t tileSideInput, 
	size_t battlefieldSideInput);
};