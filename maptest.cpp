#include "worldMap.hpp"
// Current compile: clang maptest.cpp worldMap.cpp map.cpp tile.cpp toolkit.cpp -lm -lstdc++ -std=c++11

int main () {
    unsigned int side = 100;
    unsigned int yList[side*side];
    unsigned int xList[side*side];
    std::vector<int> ySpareList;
    std::vector<int> xSpareList;
    int map[side*side];
    unsigned int seedMap[side*side];
    unsigned int startIndex;
    unsigned int startSpareIndex;
    int spareMap[side*side];
    bool debug = false;
    unsigned int seed;
    unsigned int pointX = side/2;
    unsigned int pointY = side/3;
    unsigned int tileSide = 32;
    int tileMap[tileSide*tileSide];
    srand(time(NULL));
    //-- For testing for BAD STUFF
    while(1){ // Since it's RNG... we'll need a lot to detect even a tiny bug.
    //--
        seed = rand();
        srand(seed);
        for (int i = 0; i < tileSide*tileSide; ++i)
        {
            tileMap[i] = 0;
        }
    int miniMap[9] = {  rand()%10,rand()%10,rand()%10,
                        rand()%10,0,rand()%10,
                        rand()%10,rand()%10,rand()%10};
        for(int i = 0; i < side*side; ++i){
            seedMap[i] = rand();
        }
        std::cout << "SEED: "<< seed << std::endl;
        startIndex = 0; // Since I want to output two things. We'll need to pass these things in as pointers.
        startSpareIndex = 0;
        for (int i = 0; i < side*side; ++i)
        {
            map[i] = 0;
        }
        for(int e = 0; e < 9; ++e){
    
            startIndex = 0;
            startSpareIndex = 0;
            for (int i = 0; i < side*side; ++i)
               {
                spareMap[i] = 1;
               }
               //circle(unsigned int seed, double pushCoefficient, 
                //unsigned int pointY, unsigned int pointX, int* placeMap, int dotPlace, unsigned int radius, 
                //std::vector<int>& ySpareList, std::vector<int>& xSpareList,
                // unsigned int side, bool diagonal, bool debug)
            circle(rand(),  0.1, (side/2)-1, (side/2)-1, spareMap, 2, side/(2.5+pow(e,1.5)), 
            ySpareList, xSpareList, side, true, debug);
            //printMap(spareMap,side);
            fillMap(1,1,2, (side/2)-1, (side/2)-1, side, map, spareMap, false, false);
            //printMap(spareMap,side);
    
            //for(int i = 0; i<startIndex;++i){
            //    map[yList[i]*side + xList[i]] += 1;
            //}
            if(map[0] == 1){
                std::cout << "SEED: "<< seed << std::endl;
                printMap(map,side);
                //unsigned int crasher = 1/0;
            }
        }
        //printMap(map,side);
        
        genTile(rand(), 0.1, 1, 1, miniMap, 3, tileMap, tileSide, true, debug);
        printMap(tileMap,tileSide);
            
    //--
        }
    //--
}

// TODO:
// Th
