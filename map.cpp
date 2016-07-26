#include "map.hpp"

map::map(unsigned int seedInput, const worldMap* parentWInput, size_t mapSideInput, size_t tileSideInput, size_t battlefieldSideInput):
	seed(seedInput),
	parentW(parentWInput),
    mapSide(mapSideInput),
    tileSide(tileSideInput),
    battlefieldSide(battlefieldSideInput)
{

}