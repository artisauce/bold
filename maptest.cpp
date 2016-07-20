#include "map.hpp"

int main () {
	unsigned int side = 100;
    	unsigned int yList[side*side];
    	unsigned int xList[side*side];
	int ySpareList[side*side];
    	int xSpareList[side*side];
    	int map[side*side];
	unsigned int startIndex;
	unsigned int startSpareIndex;
	int spareMap[side*side];
	bool debug = true;
	unsigned int seed;
	unsigned int repeat = 0;
	//-- For testing for BAD STUFF
	while(1){ // Since it's RNG... we'll need a lot to detect even a tiny bug.
		//--
		seed = rand();
		srand(seed);
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

		circle(rand(), &startIndex, &startSpareIndex, 0.1, (side/2)-1, (side/2)-1, side/(2.5+pow(e,1.5)), 
		yList, xList, ySpareList, xSpareList, side, true, debug);

		for(int i = 0; i<startIndex;++i){
			spareMap[ (yList[i]*side) + xList[i] ] = 2;
		}
		//printMap(spareMap,side);
		//if(spareMap[((side/2)-1)*side + ((side/2)-1)] != 2){
			fillMap(1,1,2, (side/2)-1, (side/2)-1, side, map, spareMap, false, false);
		//}
		//else {
		//	e--;
		//	continue;
		//}

		//printMap(spareMap,side);
		//randLine(rand(), &startIndex, &startSpareIndex , 0.1, (side/2)-1, 0,  (side/2)-1, side-1, yList, xList, ySpareList,xSpareList, side, 0,false,debug);

		// ===
	
		//for(int i = 0; i<startIndex;++i){
		//	map[yList[i]*side + xList[i]] += 1;
		//}
		if(map[0] == 1){
			std::cout << "SEED: "<< seed << std::endl;
			printMap(map,side);
			//unsigned int crasher = 1/0;
		}
		// ===
		//if(spareMap[0] == 0){
		}
		printMap(map,side);
    		
	//--
    }
	//--
}