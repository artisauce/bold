#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>

// Add more includes if needed.
double dist(int startY, int startX, int endY, int endX);

void randLine(unsigned int seed, double pushCoefficient, int startY, int startX, int endY, 
    int endX, int* placeMap, int dotPlace, std::vector<int>& ySpareList, std::vector<int>& xSpareList,
    unsigned int side, unsigned int sideLimit, bool borderLimit, bool diagonal, bool debug);

void circle(unsigned int seed, double pushCoefficient, 
    unsigned int pointY, unsigned int pointX, int* placeMap, int dotPlace, unsigned int radius, 
    std::vector<int>& ySpareList, std::vector<int>& xSpareList,
    unsigned int side, bool diagonal, bool debug);

void fillMap( int filler, int detect, int wall, int pointY, int pointX, unsigned int side, int* map, int* spareMap, bool wallMode, bool replace);

void printMap(int* map, unsigned int side);

void genTile(unsigned int seed, double pushCoefficient, int pointY, int pointX, int* map, unsigned int side, unsigned int tileSide, bool diagonal, bool debug);
