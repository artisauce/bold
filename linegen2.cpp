#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
# define M_PI           3.14159265358979323846  /* lol it's pi */
// Current compile: clang linegen2.cpp -lm -lstdc++
//           g++ linegen.cpp
// Get me meh distance.
double dist(int startY, int startX, int endY, int endX){
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

void randLine(unsigned int seed, double pushCoefficient, int startY, int startX, int endY, 
    int endX, int* placeMap, int dotPlace, std::vector<int>& ySpareList, std::vector<int>& xSpareList,
    unsigned int side, unsigned int sideLimit, bool borderLimit, bool diagonal, bool debug){
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
    unsigned int spareIndex = xSpareList.size();
    if(startY>=side || startY<0 || startX>=side || startX<0){
        if(spareIndex > 0){
            if(xSpareList[(spareIndex) - 1] != startX && ySpareList[(spareIndex) - 1] != startY){
                xSpareList.push_back(startX);
                ySpareList.push_back(startY);
                spareIndex++;
            }
        }
        else {
            xSpareList.push_back(startX);
            ySpareList.push_back(startY);
            spareIndex++;
        }
        
    }
    else {
        placeMap[(startY*side) + startX] = dotPlace;
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
        //std::cout << sideLimit << std::endl;
        //std::cout << "1 WY:" << (wy+yAdd) << " STY:" << startY << " EX:" << (ex+xAdd) << " ENDX:" << endX << std::endl;
        //std::cout << "2 EX:" << (ex+xAdd) << " STX:" << startX << " WY:" << (wy+yAdd) << " ENDY:" << endY << std::endl;
        if(sideLimit == 1 && (wy+yAdd == startY || ex+xAdd == endX)){
            // The side mod is useful for circles for avoiding center. 
            // Will be useless when better fill function is made. Remember to remove.
            // Also avoids the other spectrum, as sometimes it can create loose threads and lakes.
            bResult = origBResult;
            yAdd = yAddArray[bResult]; // We get the values where to go.
            xAdd = xAddArray[bResult];
            if(debug){
                std::cout << "SIDED" << std::endl;
            }
        }
        else if(sideLimit == 2 && (ex+xAdd == startX || wy+yAdd == endY)){
            bResult = origBResult;
            yAdd = yAddArray[bResult]; // We get the values where to go.
            xAdd = xAddArray[bResult];
            if(debug){
                std::cout << "SIDED" << std::endl;
            }
        }
    	if(wy+yAdd>=side || wy+yAdd<0 || ex+xAdd>=side || ex+xAdd<0){ // This is here so we do two things at the same time.
    		if(spareIndex > 0){
    		    if(ySpareList[(spareIndex)-1] == wy+yAdd && xSpareList[(spareIndex)-1] == ex+xAdd){
    		        bResult = origBResult;
    		        yAdd = yAddArray[bResult]; // We get the values where to go.
    		        xAdd = xAddArray[bResult];
    		    }
    		}
        }
        else{ // Saves on some comparison time. Used to be above the 'if' above after conversion, was a HNB.
            if(placeMap[((wy+yAdd)*side) + (ex+xAdd)] == dotPlace){
                bResult = origBResult;
                yAdd = yAddArray[bResult]; // We get the values where to go.
                xAdd = xAddArray[bResult];
            }
        }
        if(borderLimit){// Borderlimit has highest priority.
            if(wy+yAdd>=(side-1) || wy+yAdd<=0 || ex+xAdd>=(side-1) || ex+xAdd<=0){
                bResult = origBResult;
                yAdd = yAddArray[bResult]; // We get the values where to go.
                xAdd = xAddArray[bResult];
            }
        }
        if(diagonal && yAdd*xAdd) { // Check if diagonal.
            if(dist(wy+yAdd,ex,endY,endX) < dist(wy,ex+xAdd,endY,endX)){
                placeMap[(wy+yAdd)*side + ex] = dotPlace;
                //map[((wy+yAdd)*side) + ex] = 2;
            }
            else{
                placeMap[wy*side + ex+xAdd] = dotPlace;
                //map[(wy*side) + ex+xAdd] = 2;
            }
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
        double angle = (result*180)/M_PI;
        if (angle-(int)angle >= 0) {
            std::cout << (int)(result*180)/M_PI << "    ";
        } else {
            std::cout << (int)(result*180)/M_PI;
        }
        if(result!=0){
            std::cout << "\tDELY:";
        }
        else{
            std::cout << "\tDELY:";
        }

        double distanceC = dist(wy,ex,startY,startX) + 1;
        std::cout << (endY-wy);

                if((endY-wy) <= -10){ //Spacing conditional for DELX
                    std::cout << " DELX:" << (endX-ex);
                } else if ((endY-wy) >= 10){
                    std::cout << "  DELX:" << (endX-ex);
                }    else if ((endY-wy) > -10 && (endY-wy) < 0){
                    std::cout << "  DELX:" << (endX-ex);
                } else {
                    std::cout << "   DELX:" << (endX-ex);
                }

                if((endX-ex) >= 0 && (endX-ex) < 10){ //Spacing conditional for DIST
                    std::cout << "   DIST:";
                } else if((endX-ex) <= -10) {
                    std::cout << " DIST:";
                } else {
                    std::cout << "  DIST:";
                }                

                std::cout << (int)(distanceC + 1); //Added (int), some numbers cause indentation to fail
        if(distanceC-floor(distanceC) > 0){
            std::cout << "\tCHANCE:";
        }
        else {
            std::cout << "\tCHANCE:";
        }
        std::cout << (int)(999.5 - (pow(((orig-(dist(wy,ex,startY,startX)+1))/orig),0.5)*700));

                //Spacing conditional for RANDOM
                if ((int)(999.5 - (pow(((orig-(dist(wy,ex,startY,startX)+1))/orig),0.5)*700)) < -1000) {
                    std::cout << "      RANDOM:" << random << std::endl;
                } else {
                    std::cout << "\t\tRANDOM:" << random << std::endl;
                }
        }
        //---------------
        ex=ex+xAdd;
        wy=wy+yAdd; // Save some time.
        if(wy>=side || wy<0 || ex>=side || ex<0){
                xSpareList.push_back(startX);
                ySpareList.push_back(startY);
                spareIndex++;
        }
        else {
            placeMap[wy*side + ex] = dotPlace;
        }
            //map[(wy*side) + ex] = 1;
    }
    
}

void circle(unsigned int seed, double pushCoefficient, 
    unsigned int pointY, unsigned int pointX, int* placeMap, int dotPlace, unsigned int radiusY, unsigned int radiusX,
    std::vector<int>& ySpareList, std::vector<int>& xSpareList,
    unsigned int side, bool diagonal, bool debug){
    srand(seed);

    int yPointOne = pointY - radiusY;
    int xPointOne = pointX;
    
    int yPointTwo = pointY;
    int xPointTwo = pointX - radiusX;

    int yPointThree = pointY+radiusY;
    int xPointThree = pointX;

    int yPointFour = pointY;
    int xPointFour = pointX + radiusX;

    //(unsigned int seed, double pushCoefficient, int startY, int startX, int endY, 
    //int endX, int* placeMap, int dotPlace, std::vector<int>& ySpareList, std::vector<int>& xSpareList,
    // unsigned int side, unsigned int sideLimit, bool borderLimit, bool diagonal, bool debug)
    randLine(rand(), pushCoefficient, yPointOne, xPointOne, yPointTwo, xPointTwo, placeMap, dotPlace, ySpareList, xSpareList, side, 2, true, diagonal, debug); // Top left
    randLine(rand(), pushCoefficient, yPointTwo, xPointTwo, yPointThree, xPointThree, placeMap, dotPlace,  ySpareList, xSpareList, side, 1, true, diagonal, debug); // Bottom left
    randLine(rand(), pushCoefficient, yPointThree, xPointThree, yPointFour, xPointFour, placeMap, dotPlace,  ySpareList, xSpareList, side, 2, true, diagonal, debug); // Bottom right
    randLine(rand(), pushCoefficient, yPointFour, xPointFour, yPointOne, xPointOne, placeMap, dotPlace,  ySpareList, xSpareList, side, 1, true, diagonal, debug); // Top right
}

void fillMap( int filler, int detect, int wall, int pointY, int pointX, unsigned int side, int* map, int* spareMap, bool wallMode, bool replace){ // An earlier bug is where it was just "unsigned side". Apparently that works...
    //std::cout << "GO" << " " << pointY << " " << pointX<< " "  << detect<< " "  << filler << std::endl;
    spareMap[(pointY*side) + pointX] = 0; // Spare map is used to keep track of itself.
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
                    else if(spareMap[((pointY+y)*side) + pointX + x] == wall){
                        fillMap(filler,detect,wall,pointY+y,pointX+x,side, map, spareMap,true,replace);
                    }
                }
            }
        }
    }
    if(replace){ // Actual map is used effect the real map.
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

void genTile(unsigned int seed, double pushCoefficient, int pointY, int pointX, int* map, unsigned int side, unsigned int tileSide, bool diagonal, bool debug){
	//seed = 1457715766;
	srand(seed);
	//std::cout << "T SEED: " << seed << std::endl;
	int baseHeight = map[(pointY*side) + pointX];
	unsigned int shift = tileSide*0.2;
	int tileMap[tileSide*tileSide];
	int spareTileMap[tileSide*tileSide];
	for(int i = 0; i<tileSide*tileSide; ++i){
		tileMap[i] = baseHeight;
	}
	// Start algorithm.
	int checkDir[9] = {	1,1,1, // 0,1,2 INDEXES QUICK REFERENCE
				1,1,1, // 3,4,5
				1,1,1};// 6,7,8
	// --- Check for boundary case.
	int count = -1;
	unsigned int max = 0;
	for(int i = -1; i<2 ; ++i){
		for(int e = -1; e<2;++e){
			count++;
			if(pointY+i == side || pointY+i < 0 || pointX+e == side || pointX+e < 0){
				checkDir[count] = 0;
			}
			else {
				int dif = map[((pointY+i)*side) + pointX+e] - baseHeight;
				if(dif>0){
					checkDir[count] = 1+dif;
					if(dif > max){
						max=dif;
					}
				}
			}
			//std::cout << i << " " << e << " " << count << std::endl;
		}
	}
	// --- k done
	//(unsigned int seed, double pushCoefficient, int startY, int startX, int endY, 
    //int endX, int* placeMap, int dotPlace, std::vector<int>& ySpareList, std::vector<int>& xSpareList,
    // unsigned int side, unsigned int sideLimit, bool borderLimit, bool diagonal, bool debug)
	unsigned int orthogonal[4] = {0,0,0,0}; // N W S E
	std::vector<int> sparePointsX(25);
	std::vector<int> sparePointsY(25);
	for(int level = 0; level<max;level++){
		for(int i = 0; i < tileSide*tileSide; ++i){
			spareTileMap[i] = 1;
		}
		if(checkDir[0] > level+1 && checkDir[3] <= level+1 && checkDir[1] <= level+1){ // NW corner - single
			// ---
			randLine(rand(), pushCoefficient, 0, shift, 
			shift, 0, spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
			0, true, diagonal, debug);
			fillMap(1,1,2, 0, 0, tileSide, tileMap, spareTileMap, false, false);
			// ---
		}
		else if(checkDir[1] > level+1){ // Top shape
			orthogonal[0] = 1;
			//std::cout << "GO1" << std::endl;
			if(checkDir[3] > level+1 || checkDir[5] > level+1){ // Since there's more standard shapes,
										// this will be a bit quicker
										// to put into a general if.
				if(checkDir[3] > level+1 && checkDir[5] > level+1){ // N & W & E
					// ---
					randLine(rand(), pushCoefficient, 
					shift, shift, shift, (tileSide-1)-shift, spareTileMap, 2, 
					sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else if(checkDir[3] > level+1){ // N & W
					// ---
					randLine(rand(), pushCoefficient, 
					shift, shift, shift, (tileSide-1), spareTileMap, 2, 
					sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug); //
					// ---
				}
				else { // N & E
					// ---
					randLine(rand(), pushCoefficient, 
					shift, 0, shift, (tileSide-1)-shift, spareTileMap, 2,
					sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug); //
					// ---
				}
			}
			else { // Just N
				// ---
				randLine(rand(), pushCoefficient, 
				shift, 0, shift, (tileSide-1), spareTileMap, 2,
				sparePointsY, sparePointsX, tileSide, 
				0, true, diagonal, debug); //
				// ---
			}
		}
		// 0,1,2 INDEXES QUICK REFERENCE
		// 3,4,5
		// 6,7,8
		if(checkDir[2] > level+1 && checkDir[5] <= level+1 && checkDir[1] <= level+1){ // NE corner - single
			//std::cout << "GOLA" << std::endl;
			// ---
			randLine(rand(), pushCoefficient, 0, (tileSide-1)-shift, 
			shift, tileSide-1, spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
			0, true, diagonal, debug);
			//std::cout << "GOL" << std::endl;
			//std::cout << "GOL" << std::endl;
			fillMap(1,1,2, 0, tileSide-1, tileSide, tileMap, spareTileMap, false, false);
			// ---
		}
		else if(checkDir[5] > level+1){ // Right shape
			orthogonal[1] = 1;
			//std::cout << "GO2" << std::endl;
			if(checkDir[1] > level+1 || checkDir[7] > level+1){ // Since there's more standard shapes,
										// this will be a bit quicker
										// to put into a general if.
				if(checkDir[1] > level+1 && checkDir[7] > level+1){ // N & E & S
					// ---
					randLine(rand(), pushCoefficient, 
					shift, (tileSide-1)-shift, (tileSide-1)-shift, (tileSide-1)-shift, spareTileMap, 2,
					sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else if(checkDir[1] > level+1){ // N & E
					// ---
					randLine(rand(), pushCoefficient, 
					shift, (tileSide-1)-shift, (tileSide-1), (tileSide-1)-shift, spareTileMap, 2,
					sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else { // E and S
					// ---
					randLine(rand(), pushCoefficient, 
					0, (tileSide-1)-shift, (tileSide-1)-shift, (tileSide-1)-shift, spareTileMap, 2,
					sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
			}
			else { // Just E
				// ---
				randLine(rand(), pushCoefficient, 
				0, (tileSide-1)-shift, (tileSide-1), (tileSide-1)-shift, spareTileMap, 2,
				sparePointsY, sparePointsX, tileSide, 
				0, true, diagonal, debug); //
				// ---
			}
		}
		if(checkDir[8] > level+1 && checkDir[5] <= level+1 && checkDir[7] <= level+1){ // SE corner - single
			// ---
			randLine(rand(), pushCoefficient, 
			(tileSide-1)-shift, (tileSide-1), (tileSide-1), (tileSide-1)-shift, spareTileMap, 2,
			sparePointsY, sparePointsX, tileSide, 
			0, true, diagonal, debug);
			fillMap(1,1,2, tileSide-1, tileSide-1, tileSide, tileMap, spareTileMap, false, false);
			// ---
		}
		else if(checkDir[7] > level+1){ // Bottom shape
			orthogonal[2] = 1;
			//std::cout << "GO3" << std::endl;
			if(checkDir[5] > level+1 || checkDir[3] > level+1){ // Since there's more standard shapes,
										// this will be a bit quicker
										// to put into a general if.
				if(checkDir[3] > level+1 && checkDir[5] > level+1){ // W & E & S
					// ---
					//std::cout << "GOA" << std::endl;
					randLine(rand(), pushCoefficient, 
					(tileSide-1)-shift, shift, (tileSide-1)-shift, (tileSide-1)-shift, 
					spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else if(checkDir[5] > level+1){ // S & E
					// ---
					//std::cout << "GOB" << std::endl;
					randLine(rand(), pushCoefficient, 
					(tileSide-1)-shift, 0, (tileSide-1)-shift, (tileSide-1)-shift, 
					spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else { // W and S
					// ---
					//std::cout << "GOC" << std::endl;
					randLine(rand(), pushCoefficient, 
					(tileSide-1)-shift, shift, (tileSide-1)-shift, (tileSide-1), 
					spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
			}
			else { // Just S
				// ---
				//std::cout << "GOD" << std::endl;
				randLine(rand(), pushCoefficient, 
				(tileSide-1)-shift, 0, (tileSide-1)-shift, (tileSide-1), 
				spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
				0, true, diagonal, debug);
				// ---
			}
		}
		// 0,1,2 INDEXES QUICK REFERENCE
		// 3,4,5
		// 6,7,8
		if(checkDir[6] > level+1 && checkDir[3] <= level+1 && checkDir[7] <= level+1){ // SW corner - single
			// ---
			randLine(rand(), pushCoefficient, 
			(tileSide-1)-shift, 0, (tileSide-1), shift, 
			spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
			0, true, diagonal, debug);
			fillMap(1,1,2, tileSide-1, 0, tileSide, tileMap, spareTileMap, false, false);
			// ---
		}
		else if(checkDir[3] > level+1){ // Left Shape
			orthogonal[3] = 1;
			//std::cout << "GO4" << std::endl;
			if(checkDir[1] > level+1 || checkDir[7] > level+1){ // Since there's more standard shapes,
										// this will be a bit quicker
										// to put into a general if.
				if(checkDir[1] > level+1 && checkDir[7] > level+1){ // W & N & S
					// ---
					randLine(rand(), pushCoefficient, 
					shift, shift, (tileSide-1)-shift, shift, 
					spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else if(checkDir[1] > level+1){ // N & W
					// ---
					randLine(rand(), pushCoefficient, 
					shift, shift, (tileSide-1), shift, 
					spareTileMap, 2,sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
				else { // W and S
					// ---
					randLine(rand(), pushCoefficient, 
					0, shift, (tileSide-1)-shift, shift, 
					spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
					0, true, diagonal, debug);
					// ---
				}
			}
			else { // Just W
				// ---
				randLine(rand(), pushCoefficient, 
				0, shift, (tileSide-1), shift, 
				spareTileMap, 2, sparePointsY, sparePointsX, tileSide, 
				0, true, diagonal, debug);
				// ---
			}
		}
		//printMap(spareTileMap,tileSide);
		//std::cout << orthogonal[0] << " " << orthogonal[1] << " " << orthogonal[2] << " " << orthogonal[3] << " " << level << std::endl;
		if(orthogonal[0] && spareTileMap[(tileSide/2)-1]){ // N
			fillMap(1,1,2, 0, (tileSide/2)-1, tileSide, tileMap, spareTileMap, false, false);
		}
		// Why else? Think about it. Half the comparisons made for obvious stuff.
		else if(orthogonal[1] && spareTileMap[(((tileSide/2)-1)*tileSide) + (tileSide-1)]){ // W
			fillMap(1,1,2, (tileSide/2)-1, tileSide-1, tileSide, tileMap, spareTileMap, false, false);
		}
		if(orthogonal[2] && spareTileMap[((tileSide-1)*tileSide)+((tileSide/2)-1)]){ // S
			fillMap(1,1,2, tileSide-1, (tileSide/2)-1, tileSide, tileMap, spareTileMap, false, false);
		}
		else if(orthogonal[3] && spareTileMap[(((tileSide/2)-1)*tileSide)]){ // E
			fillMap(1,1,2, (tileSide/2)-1, 0, tileSide, tileMap, spareTileMap, false, false);
		}
		orthogonal[0] = 0; // Putting them in the if's above is buggy. Fixing requires more comparisons.
		orthogonal[1] = 0;
		orthogonal[2] = 0;
		orthogonal[3] = 0;
		//printMap(tileMap,tileSide);
	}
	std::cout << "T SEED: " << seed << std::endl;
	printMap(tileMap,tileSide);
	//int counter = 0;
	//for(int i = 0; i<tileSide*tileSide; ++i){
	//	if(tileMap[i] == 0){
	//		counter++;
	//	}
	//}
	//if(counter==0){
	//	std::cout << "T SEED: " << seed << std::endl;
	//	int gray = 1/0;
	//}
}

void genIsland(unsigned int seed, double pushCoefficient, int startY, int startX, int endY, int endX,
    int height, int* map, unsigned int side, std::vector<int>& ySpareList, std::vector<int>& xSpareList, 
    bool diagonal, bool debug){
    srand(seed);
    // Start X and Y are top left corner, end X and Y are bottom right corner.
    if(debug){
        std::cout << "MAP SEED: "<< seed << std::endl;
    }
    int width = (endX-startX+1);
    int length = (endY-startY+1);
    int spareMap[side*side];
    //printMap(map,side);
    for (int i = 0; i < width*length; i++)
    {
        map[( ( ((int)(i/width)) +startY) *side) + ((i%width)+startX)] = 0; // Clear the area, tectonic shift coming through!
    }
    //printMap(map,side);
    if(height < 0){ // If none set, etc. you set to -1 because you're a lazy ass.
        if(width < 5 || length < 5){ // Simply too small for maps to handle. Get special func instead.
            height = 0;
        }
        else if(width < 11 || length < 11){ // IT'S PRETTY BAD. D;
            height = 1;
        }
        else{ // This seems good tho.
            height = (int)((pow(side,0.5))+1);
        }
    }
    for(int e = 0; e < height; ++e){
        for (int i = 0; i < side*side; ++i)
        {
            spareMap[i] = 1;
        }
        circle(rand(),  pushCoefficient, startY+((length/2)), startX+((width/2)), spareMap, 2, 
        length/(2.5+pow(e,1.5)), width/(2.5+pow(e,1.5)), 
        ySpareList, xSpareList, side, diagonal, debug);
        fillMap(1,1,2, startY+((length/2) ), startX+((width/2)), side, map, spareMap, false, false);
        if(map[0] >= 1){
            std::cout << e << " SEED: "<< seed << std::endl;
                        
        }
        //printMap(map,side);
    }
    //std::cout << map[2] << " GO " << height << std::endl;
    //std::cout << "END" << std::endl;


}

int main () {
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
	int miniMap[9] = {	1,1,1,
				        1,0,1,
				        1,1,1};
    
    genIsland(rand(), 0.1, 0, 0, side-1, side-1,
    -1, map,  side, ySpareList, xSpareList, 
    true, debug);
    printMap(map,side);

    
    
            
    //--
    }
    //--
}

// TODO:
// Th
