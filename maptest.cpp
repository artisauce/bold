#include "worldMap.hpp"
// Current compile: clang maptest.cpp worldMap.cpp map.cpp tile.cpp toolkit.cpp battleField.cpp -lm -lstdc++ -std=c++11



int main () {
    srand(time(NULL));
    bool debug = false;
    bool diagonal = true;
    double pushCoefficient = 0.1;
    size_t worldMapSide = 2;
    size_t mapSide = 50;
    size_t tileSide = 16;
    size_t battlefieldSide = 64;
    std::vector<std::string> tileSet;
    tileSet.push_back("@");
    tileSet.push_back("~");
    worldMap newMap(rand(), pushCoefficient, worldMapSide, mapSide, tileSide, battlefieldSide,  diagonal, debug);
    if(debug){
        std::cout << "--- EVERYTHING HAS BEEN MADE --- " << std::endl;
    }
    std::vector<int> viewer;
    unsigned int sider;
    sider = view(newMap.bigMap[0],25,25,11,11,60,true,true,false,true,true,viewer);
    std::cout << " VECTOR MAP " << std::endl;
    printMapVector(viewer,sider,tileSet);
    std::cout << " FULL MAP " << std::endl;
    printMap(newMap.bigMap[0].heightMap,mapSide,tileSet);
    battlefield newBattle(&(newMap.bigMap[0].regionMap[((tileSide/2)*tileSide)+(tileSide/2)]));
	printMap(newBattle.battleMap,battlefieldSide,tileSet);
    //printMap(newMap.bigMap[0].regionMap[((mapSide*mapSide)/2)+2].tileMap,newMap.tileSide);

}

// TODO:
// Have battlefields stored in tiles after a battle to re-use, as battles can impact terrain.
