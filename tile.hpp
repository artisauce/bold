#include "toolkit.hpp"
// A tile in the game area - has its own little map
class map;
class tile {
public:
	
	// -- ESSENTIAL
	const unsigned int seed;
	const map* parentM;
	// -- ESSENTIAL

	// -- Settings
	const size_t tileSide;
	const size_t battlefieldSide;
	const int y;
	const int x;
	const double push;
	const bool diagonal;
	const bool debug;
	// -- Settings

	// -- cordLists for randLine
	std::vector<int> ySpareList;
    std::vector<int> xSpareList;
	// -- cordLists for randLine

	// -- Maps
	int* seedMap;
	int* tileMap;
	// -- Maps
	
	tile(unsigned int seedInput, const map* parentMInput, const int yInput, 
		const int xInput, const double pushInput, const size_t tileSideInput, 
		const size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput);
	~tile();

};