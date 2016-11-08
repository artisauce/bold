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
	std::vector<map>  bigMap; // Damn naming
	// -- Maps

	worldMap(unsigned int seedInput, const double pushInput, size_t worldMapSideInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput);
	~worldMap();
};

unsigned int view(worldMap& theMap, int worldY, int worldX, int regionY, int regionX, 
				int tileY,  int tileX, int viewRadius, float heightOffset,int playerHeight, bool mapView,  
				bool circle, bool borders, bool playerSee, bool wallMode ,std::vector<int>& viewMap, 
				 std::vector<int>* optimizeArray,std::vector<int>& memoryMap, int specialTiles,bool InvisibleAboveCustom, bool checkAll ,
				 bool debug);
