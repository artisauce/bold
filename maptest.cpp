#include "worldMap.hpp"
// Current compile: clang maptest.cpp worldMap.cpp map.cpp tile.cpp toolkit.cpp -lm -lstdc++ -std=c++11



int main () {
    srand(time(NULL));
    bool debug = true;
    bool diagonal = true;
    double pushCoefficient = 0.1;
    size_t worldMapSide = 2;
    size_t mapSide = 50;
    size_t tileSide = 16;
    size_t battlefieldSide = 16;
    std::vector<std::string> tileSet;
    tileSet.push_back("@");
    worldMap newMap(rand(), pushCoefficient, worldMapSide, mapSide, tileSide, battlefieldSide,  diagonal, debug);
    if(debug){
        std::cout << "--- EVERYTHING HAS BEEN MADE --- " << std::endl;
    }
    std::vector<int> viewer;
    unsigned int sider;
    sider = view(newMap.bigMap[0],25,25,11,11,60,false,true,true,true,true,viewer);
    printMapVector(viewer,sider,tileSet);
    printMap(newMap.bigMap[0].heightMap,mapSide,tileSet);
    
    //printMap(newMap.bigMap[0].regionMap[((mapSide*mapSide)/2)+2].tileMap,newMap.tileSide);




    /*

    unsigned int side = 100; // 10 is the bad number currently;
    std::vector<int> ySpareList;
    std::vector<int> xSpareList;
    int map[side*side];
    unsigned int seedMap[side*side];
    unsigned int startIndex;
    unsigned int startSpareIndex;
    int spareMap[side*side];
    bool debug = false;
    unsigned int seed;
    srand(time(NULL));
    //-- For testing for BAD STUFF
    while(1){ // Since it's RNG... we'll need a lot to detect even a tiny bug.
    //--
        seed = rand();
        srand(seed);
    int miniMap[9] = {  1,1,1,
                        1,0,1,
                        1,1,1};
    
    genIsland(rand(), 0.1, 0, 0, side-1, side-1,
    -1, map,  side, ySpareList, xSpareList, 
    true, debug);
    printMap(map,side);
    
    
    //--
    }
    //--

    */ 
}

// TODO:
// Th
