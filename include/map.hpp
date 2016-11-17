#include "tile.hpp"
// A game area - for reference, an island
class map {
public:

	// -- ESSENTIAL
	const unsigned int worldSeed;
	const unsigned int seed;
	const map* parentM;
	const map* left;
	const map* right;
	const map* down;
	const map* up;
	bool activated;
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

	// -- cordLists for randLine
	std::vector<int> ySpareList;
    std::vector<int> xSpareList;
	// -- cordLists for randLine

	// -- memoryMap for tiles -- leftover from deactivation
	std::vector<std::vector<int>>;
	// -- memoryMap for tiles -- leftover from deactivation

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
