#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

class map {
public:

	
};

class tile {
public:

	
	
};

class worldMap {
public:

	
};

class battlefield {
public:



};

double dist(int startY, int startX, int endY, int endX);

void randLine(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
	int startY, int startX, int endY, int endX, unsigned int* yList, 
	unsigned int* xList, int* ySpareList, int* xSpareList,
	unsigned int side, unsigned int sideLimit, bool diagonal, bool debug);

void circle(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
	unsigned int pointY, unsigned int pointX, unsigned int radius, 
	unsigned int* yList, unsigned int* xList, int* ySpareList, int* xSpareList,
	unsigned int side, bool diagonal, bool debug);

void fillMap( int filler, int detect, int wall, int pointY, int pointX, unsigned side, int* map, int* spareMap, bool wallMode, bool replace);

void printMap(int* map, unsigned int side);