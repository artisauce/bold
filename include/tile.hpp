#include "battleField.hpp"
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
	const int height;
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
	int* tileMemoryMap;
	// -- Maps
	
	tile(unsigned int seedInput, const map* parentMInput, const int yInput, 
		const int xInput);
	tile(tile const& src);
	~tile();

};
