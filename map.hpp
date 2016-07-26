#include "tile.hpp"
// A game area - for reference, an island
class map {
public:

	// -- ESSENTIAL
	const unsigned int seed;
	// -- ESSENTIAL

	// -- Settings
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
	tile* regionMap; // Darn naming
	// -- Maps

	map(unsigned int seedInput, size_t mapSideInput, size_t tileSideInput, size_t battlefieldSideInput);

};