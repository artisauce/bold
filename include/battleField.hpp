#include "toolkit.hpp"
// Battlefields are generated temporarily for duration of battle. Represents a coordinate in the tile map.
class tile;
class battlefield {
public:
	// -- ESSENTIAL
	const unsigned int seed;
	const tile* parentT;
	// -- ESSENTIAL

	// -- Settings
	const size_t battlefieldSide;
	const int y;
	const int x;
	const int height;
	const bool debug;
	// -- Settings

	// -- Maps
	int* battleMap;
	std::string tileSet; // Different visuals for different places.
	// -- Maps
	
	battlefield(const tile* parentTInput, const int yInput, const int xInput);
	battlefield(battlefield const& src);
	~battlefield();
	


};
