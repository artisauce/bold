#include "worldMap.hpp"
// The weird include needs the definition of the worldMap class for map constructor.
map::map(unsigned int seedInput, const worldMap* parentWInput, size_t mapSideInput, size_t tileSideInput, size_t battlefieldSideInput):
	seed(seedInput),
	parentW(parentWInput),
    mapSide(mapSideInput),
    tileSide(tileSideInput),
    battlefieldSide(battlefieldSideInput)
{

}