#include "tile.hpp"
// A game area - for reference, an island
class worldMap; // We need dis
class map {
public:

	// -- ESSENTIAL
	const unsigned int seed;
	const worldMap* parentW;
	// -- ESSENTIAL

	// -- Settings
	const size_t mapSide;
	const size_t tileSide;
	const size_t battlefieldSide;
	const int y;
	const int x;
	const double push;
	const bool diagonal;
	const bool debug;
	// -- Settings
	// -- Settings

	// -- cordLists for randLine
	std::vector<int> ySpareList;
    std::vector<int> xSpareList;
	// -- cordLists for randLine

	// -- Maps
	int* seedMap;
	int* heightMap;
	int* regionMemoryMap;
	std::vector<tile> regionMap; // Darn naming -- http://stackoverflow.com/questions/15802006/how-can-i-create-objects-while-adding-them-into-a-vector
	// -- Maps

	map(unsigned int seedInput, const worldMap* parentW, const int yInput, 
	const int xInput);
	map(map const& src);
	~map();

};
