#include "map.hpp"
//clang maptest.cpp map.cpp -lm -lstdc++ -std=c++11
// World map - total game area

class playerSpace {
public:

	// -- ESSENTIAL
	const unsigned int seed;
	// -- ESSENTIAL

	// -- Settings
	const size_t mapSide;
	const size_t tileSide;
	const size_t battlefieldSide;
	const double push;
	const bool diagonal;
	const bool debug;
	unsigned int mapCount;
	// -- Settings

	// -- cordLists for randLine
	std::vector<int> ySpareList;
    	std::vector<int> xSpareList;
	// -- cordLists for randLine

	// -- Player stats
	int tileVewRadius; // Kinda important.
	int regionVewRadius; // Kinda important.
	int mapViewRadius; // For the extremes of testing.
	int playerWorldY; // Cordinate of world.
	int playerWorldX;
	int playerRegionY; // Cordinate on actual map object.
	int playerRegionX;
	int playerTileY; // Cordinate on the tile objects in the map object.
	int playerTileX;
	// -- Player stats

	// -- Maps
	std::list<std::list<coordinate>> cordMap; // For locating maps manually--and hard.
	map* current; // Keeps track of current map the player is on.
	// -- Maps

	playerSpace(unsigned int seedInput, int playerViewRadius, const double pushInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput);
	~playerSpace();
};

unsigned int view(playerSpace& playerSpace, int viewRadius, float heightOffset,int playerHeight, bool mapView,  
				bool circle, bool borders, bool playerSee, bool wallMode ,std::vector<int>& viewMap, 
				 std::vector<int>* optimizeArray,std::vector<int>& memoryMap, int specialTiles,bool InvisibleAboveCustom, bool checkAll ,
				 bool debug);
