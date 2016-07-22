#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>

//TODO: Maybe it's time for vectors.

// World map - total game area
class worldMap {
public:

	const unsigned int seed;

	// -- Settings
	const size_t worldMapSide;
	const size_t mapSide;
	const size_t tileSide;
	const size_t battlefieldSide;
	// -- Settings

	// -- cordLists for randLine
	unsigned int startIndex;
	std::vector<unsigned int> yList = std::vector<unsigned int>(worldMapSide);
        std::vector<unsigned int> xList = std::vector<unsigned int>(worldMapSide);
    	unsigned int startSpareIndex;
	int ySpareList[(worldMapSide*worldMapSide)*2]; // Turn's out even side*side isn't enough... atleast, for the circle function.
        int xSpareList[(worldMapSide*worldMapSide)*2];
	// -- cordLists for randLine

	// -- Maps
	unsigned int seedMap[worldMapSide*worldMapSide];
	map spareMap[worldMapSide*worldMapSide];
	map worldMap[worldMapSide*worldMapSide];
	// -- Maps

	worldMap(unsigned int seedInput,unsigned int worldMapSideInput, unsigned int mapSideInput, unsigned int tileSideInput, 
	unsigned int battlefieldSideInput);
};

// A game area - for reference, an island
class map {
public:

	const unsigned int seed;
	const worldMap* parentW;

	// -- Settings
	const unsigned int mapSide;
	// -- Settings

	// -- cordLists for randLine
	unsigned int startIndex;
	unsigned int yList[mapSide*mapSide];
        unsigned int xList[mapSide*mapSide];
    	unsigned int startSpareIndex;
	int ySpareList[(mapSide*mapSide)*2]; // Turn's out even side*side isn't enough... atleast, for the circle function.
        int xSpareList[(mapSide*mapSide)*2];
	// -- cordLists for randLine

	// -- Maps
	unsigned int seedMap[mapSide*mapSide];
	tile spareMap[mapSide*mapSide];
	tile regionMap[mapSide*mapSide]; // Darn naming
	// -- Maps

	map(unsigned int seedInput, worldMap* parentWInput);

};

// A tile in the game area - has its own little map
class tile {
public:
	
	const unsigned int seed;
	const map* parentM;

	// -- Settings
	const unsigned int tileSide;
	// -- Settings

	// -- cordLists for randLine
	unsigned int startIndex;
	unsigned int yList[tileSide*tileSide];
        unsigned int xList[tileSide*tileSide];
    	unsigned int startSpareIndex;
	int ySpareList[(tileSide*tileSide)*2]; // Turn's out even side*side isn't enough... atleast, for the circle function.
        int xSpareList[(tileSide*tileSide)*2];
	// -- cordLists for randLine

	// -- Maps
	unsigned int seedMap[tileSide*tileSide];
	unsigned int spareMap[tileSide*tileSide];
	unsigned int tileMap[tileSide*tileSide];
	// -- Maps

	tile(unsigned int seedInput, map* parentMInput);
	
};

// Battlefields are generated temporarily for duration of battle. Represents a coordinate in the tile map.
class battlefield {
public:

	


};

double dist(int startY, int startX, int endY, int endX);

void randLine(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
    int startY, int startX, int endY, int endX, unsigned int* yList, 
    unsigned int* xList, int* ySpareList, int* xSpareList,
    unsigned int side, unsigned int sideLimit, bool borderLimit, bool diagonal, bool debug);

void circle(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
    unsigned int pointY, unsigned int pointX, unsigned int radius, 
    unsigned int* yList, unsigned int* xList, int* ySpareList, int* xSpareList,
    unsigned int side, bool diagonal, bool debug);

void fillMap( int filler, int detect, int wall, int pointY, int pointX, unsigned int side, int* map, int* spareMap, bool wallMode, bool replace);

void printMap(int* map, unsigned int side);

void genTile(unsigned int seed, double pushCoefficient, int pointY, int pointX, int* map, unsigned int side, unsigned int tileSide, bool diagonal, bool debug);


