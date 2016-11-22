#include "tile.hpp"

struct coordinate {
    int y;
    int x;
    map* pointer;
	cordinate* up;
	cordinate* down;
};

// A game area - for reference, an island
class map {
public:

	// -- ESSENTIAL
	const unsigned int worldSeed;
	const unsigned int seed;
	const map* parentM;
	map* left;
	map* right;
	map* down;
	map* up;
	bool activated;
	std::list<coordinate>::iterator xConnector; // For quick list accessing
	std::list<std::list<coordinate>>::iterator yConnector;
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

	map(unsigned int worldSeedInput, int yInput, int xInput, const double pushInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput);
	map::map(const map* parentMInput, int yDir, int xDir);
	map(map const& src);
	~map();
	map::deactivate();
	map::activate();
	

};
