#include "map.hpp"
# define M_PI           3.14159265358979323846  /* lol it's pi */

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

double dist(int startY, int startX, int endY, int endX){
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

void randLine(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
	int startY, int startX, int endY, int endX, unsigned int* yList, 
	unsigned int* xList, int* ySpareList, int* xSpareList,
	unsigned int side, unsigned int sideLimit, bool diagonal, bool debug){
    srand(seed);
	if(debug){
		std::cout << "--------- SEED: " << seed << " ---------" << std::endl;
	}
    int dList[13]  = {    2, 3,   6,9,8, 7, 4, 1, 2, 3,6,     9,8}; // Navigation array. Check numpad.
    int dRealList[13] = { 8, 9,   6,3,2, 1, 4, 7, 8, 9,6,     3,2};  // Adjusted for map display.
    // No longer in use. Use as reference instead.
    int yAddArray[13] = {-1,-1,   0,1,1, 1, 0,-1,-1,-1,0,     1,1};
    int xAddArray[13] = { 0, 1,   1,1,0,-1,-1,-1, 0, 1,1,     1,0};
    double orig = dist(startY,startX,endY,endX); // Get original distance..
    int ex = startX; // X
    int wy = startY; // Y
    //map[(startY*side) + startX] = 1;
	if(startY>=side || startY<0 || startX>=side || startX<0){
		if(*spareIndex > 0){
			if(xSpareList[(*spareIndex) - 1] != startX && ySpareList[(*spareIndex) - 1] != startY){
				xSpareList[*spareIndex] = (startX);
				ySpareList[*spareIndex] = (startY);
				(*spareIndex)++;
			}
		}
		else {
			xSpareList[*spareIndex] = (startX);
			ySpareList[*spareIndex] = (startY);
			(*spareIndex)++;
		}
		
	}
	else {
		if(*index > 0){
			if(xList[(*index) - 1] != startX && yList[(*index) - 1] != startY){
				xList[*index] = (startX);
				yList[*index] = (startY);
				(*index)++;
			}
		}
		else {
			xList[*index] = (startX);
			yList[*index] = (startY);
			(*index)++;
		}
	}
    while(ex != endX || wy != endY){
        double result = atan2((endY-wy),(endX-ex)) + (M_PI * 2);
	result = fmod(result,(M_PI * 2));
        //This gets the thing in radians.
        // We multiply the result by 180/M_PI to save us some calculations.
        // We subtract by 22.5 (to shift the 4 orthogonal directions between the 4 quadrants.)
        // We then divide by 45. // To obtain the integer on the dList.
        // Then we round up. // To finalize getting integer.
        // We add 2 to adjust for dList offset.
        // ---
        // So, we simplify this to make it quicker, and to truncate instead of using ceil. Basically adding 1 and
        // rounding down. -22.5 / 45 = -0.5, plus 1 = 0.5. Add 2, etc...
        int bResult = (int)((result * (180/(M_PI*45)))+2.5);
        int origBResult = bResult;
	
        int random = rand()%1000; // Random number between 0 and 999.
	 double distToA = dist(wy,ex,startY,startX) + 1; // Add one so there's a 100% chance when right 
							// beside the goal. Unfortunately, it means a more push to goal. Fix?
	if(sideLimit && distToA == 1){
		random = 0; // Wow RNG manipulation how dare u.
	}
        if (random>299 && distToA < orig){ // Checks if, by absolute means, we're going straight or not. We can still go straight...
           // Also check if distToA larger than orig. Found this by debugging, still possible. :/

            //double pushCoefficient = 0.5; 
		// Great than 0. Lower than zero means tendency means less push,
            // greater than 1 means greater push towards end point.
		// values 0.1 to 0.5 seem good. Recommend 0.1.
            int primChance = (int)(999.5 - (pow(((orig-distToA)/orig),pushCoefficient)*700)); //999 is max, 299 min. We truncate-round, so add 0.5.
		if(primChance<0 && debug){
			std::cout << "WARNING: orig: " << orig << " distToA: " << distToA << std::endl;
		}
            if(random>primChance){ // Checks again if we're going straight.
                int thirChance = 600-primChance; // We don't need to know secondary chance. 999-399 is what
                // got 600 here. 999-primChance is secondary chance. then -399, gets thirChance.
                if(random>999-thirChance){
                    bResult=(bResult-2)+((random%2)*4); // If it's even, negative. Odd, positive.
                }
                else { // Then secondary chance occurs. We already checked primary and third, both failed.
                    bResult=(bResult-1)+((random%2)*2); // If it's even, negative. Odd, positive.
                }
            }
        }
        int yAdd = yAddArray[bResult]; // We get the values where to go.
        int xAdd = xAddArray[bResult];
	if(sideLimit == 1 && wy+yAdd== startY){ // The side mod is useful for circles for avoiding center. Will be useless when
		// better fill function is made. Remember to remove.
		bResult = origBResult;
		yAdd = yAddArray[bResult]; // We get the values where to go.
		xAdd = xAddArray[bResult];
		if(debug){
			std::cout << "SIDED" << std::endl;
		}
	}
	else if(sideLimit == 2 && ex+xAdd == startX){
		bResult = origBResult;
		yAdd = yAddArray[bResult]; // We get the values where to go.
		xAdd = xAddArray[bResult];
		if(debug){
			std::cout << "SIDED" << std::endl;
		}
	}
	else{ // Saves on some comparison time.
		if(*index > 0){
			if(yList[(*index)-1] == wy+yAdd && xList[(*index)-1] == ex+xAdd){
				bResult = origBResult;
				yAdd = yAddArray[bResult]; // We get the values where to go.
				xAdd = xAddArray[bResult];
			}
		}
		if(*spareIndex > 0){
			if(ySpareList[(*spareIndex)-1] == wy+yAdd && xSpareList[(*spareIndex)-1] == ex+xAdd){
				bResult = origBResult;
				yAdd = yAddArray[bResult]; // We get the values where to go.
				xAdd = xAddArray[bResult];
			}
		}
	}
        if(diagonal && yAdd*xAdd) { // Check if diagonal.
            if(dist(wy+yAdd,ex,endY,endX) < dist(wy,ex+xAdd,endY,endX)){
                yList[*index] = wy+yAdd;
                xList[*index] = ex;
                //map[((wy+yAdd)*side) + ex] = 2;
            }
            else{
                yList[*index] = wy;
                xList[*index] = ex+xAdd;
                //map[(wy*side) + ex+xAdd] = 2;
            }
            (*index)++;
        }
	
        //--------------- DEBUG STUFF. /t for tabbing.
			/*Changes (June 13th, 2016): "\t" seems to be buggy at times
			so some has been swapped with "    ".
			*/
        if(debug){
		std::cout << "WY: " << wy << "+" << yAdd;
		//"\t" has been replaced as it is buggy at times and fails to indent

		if (wy < 0 || yAdd < 0) { //Conditional to space accordingly if the number is positive/negative
			std::cout << "   ";
		} else {
			std::cout << "    ";
		}

		std::cout << "EX:" << ex << "+" << xAdd; 
		std::cout << "\tDRES:" << dList[bResult]; 
		std::cout << "\tRES:"; 
		//Added (int), some numbers cause indentation to fail so I set the type of values
		if (((int)(result*180)/M_PI) == 0) {
			std::cout << (int)(result*180)/M_PI << "    ";
		} else {
			std::cout << (int)(result*180)/M_PI;
		}
        if(result!=0){
            std::cout <<"\tDELY:";
        }
        else{
            std::cout << "\tDELY:";
        }
        double distanceC = dist(wy,ex,startY,startX) + 1;
        std::cout << (endY-wy) << "\tDELX:" << (endX-ex) << "\tDIST:" << (int)(distanceC + 1); //Added (int), some numbers cause indentation to fail
        if(distanceC-floor(distanceC) > 0){
            std::cout << "\tCHANCE:";
        }
        else{
            std::cout << "\tCHANCE:";
        }
        std::cout << (int)(999.5 - (pow(((orig-(dist(wy,ex,startY,startX)+1))/orig),0.5)*700)) << "\tRANDOM:" << random << std::endl;
        }
        //---------------
	ex=ex+xAdd;
	wy=wy+yAdd;
	if(wy>=side || wy<0 || ex>=side || ex<0){
		xSpareList[*spareIndex] = (ex);
        	ySpareList[*spareIndex] = (wy);
        	(*spareIndex)++;
		
	}
	else{
		xList[*index] = (ex);
		yList[*index] = (wy);
		(*index)++;
	}
        //map[(wy*side) + ex] = 1;
    }
	
}

void circle(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
	unsigned int pointY, unsigned int pointX, unsigned int radius, 
	unsigned int* yList, unsigned int* xList, int* ySpareList, int* xSpareList,
	unsigned int side, bool diagonal, bool debug){
	srand(seed);

	int yPointOne = pointY - radius;
	int xPointOne = pointX;
	
	int yPointTwo = pointY;
	int xPointTwo = pointX - radius;

	int yPointThree = pointY+radius;
	int xPointThree = pointX;

	int yPointFour = pointY;
	int xPointFour = pointX + radius;

	if(index==NULL){
		unsigned int* index;
		*index = 0;
	}
	if(spareIndex==NULL){
		unsigned int* spareIndex;
		*spareIndex = 0;
	}
	//void randLine(unsigned int seed, unsigned int* index, unsigned int* spareIndex, double pushCoefficient, 
	//int startY, int startX, int endY, int endX, unsigned int* yList, unsigned int* xList, int* ySpareList, int* xSpareList,
	//unsigned int side, bool diagonal, bool debug){
	randLine(rand(), index, spareIndex, pushCoefficient, yPointOne, xPointOne, yPointTwo, xPointTwo, yList, xList, ySpareList, xSpareList, side, 2, diagonal, debug); // Top left
	randLine(rand(), index, spareIndex, pushCoefficient, yPointTwo, xPointTwo, yPointThree, xPointThree, yList, xList, ySpareList, xSpareList, side, 1, diagonal, debug); // Bottom left
	randLine(rand(), index, spareIndex, pushCoefficient, yPointThree, xPointThree, yPointFour, xPointFour, yList, xList, ySpareList, xSpareList, side, 2, diagonal, debug); // Bottom right
	randLine(rand(), index, spareIndex, pushCoefficient, yPointFour, xPointFour, yPointOne, xPointOne, yList, xList, ySpareList, xSpareList, side, 1, diagonal, debug); // Top right
}

void fillMap( int filler, int detect, int wall, int pointY, int pointX, unsigned side, int* map, int* spareMap, bool wallMode, bool replace){
	//std::cout << "GO" << " " << pointY << " " << pointX<< " "  << detect<< " "  << filler << std::endl;
	spareMap[(pointY*side) + pointX] = 0;
	for(int y = -1; y < 2; ++y){
		for(int x = -1; x < 2; ++x){
			//std::cout << map[(pointY*side) + pointX] << std::endl;
			//std::cout << (map[((pointY+y)*side) + pointX + x]) << std::endl;
			if(pointY+y < side && pointY+y >= 0 && pointX+x < side && pointX+x >= 0){
				if(wallMode){
					if(spareMap[((pointY+y)*side) + pointX + x] == wall){
						//std::cout << map[((pointY+y)*side) + pointX + x] << " " << detect << std::endl;
						fillMap(filler,detect,wall,pointY+y,pointX+x,side, map, spareMap,wallMode,replace);
					}
				}
				else {
					if(spareMap[((pointY+y)*side) + pointX + x] == detect){
						fillMap(filler,detect,wall,pointY+y,pointX+x,side, map, spareMap,wallMode,replace);
					}
					//else if(spareMap[((pointY+y)*side) + pointX + x] == wall){
					//	fillMap(filler,detect,wall,pointY+y,pointX+x,side, map, spareMap,true,replace);
					//}
				}
			}
		}
	}
	if(replace){
		map[(pointY*side) + pointX] = filler;
	}
	else{
		map[(pointY*side) + pointX] += filler;
	}
}

void printMap(int* map, unsigned int side){
	 for (int i = 0; i < side*side; ++i)
	{
		if(i%side == 0){
		    std::cout << std::endl;
		}
		std::cout << map[i];
	}
	std::cout << std::endl;

}