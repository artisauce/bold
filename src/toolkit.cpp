#include "toolkit.hpp"
# define M_PI           3.14159265358979323846  /* lol it's pi */

// TOOL FUNCTIONS
double dist(int startY, int startX, int endY, int endX){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

double distD(double startY, double startX, double endY, double endX){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    double dx = (endX-(double)startX);
    double dy = (endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

double func(double input, double multiplier, double addition){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    return ((input*multiplier) + (addition));
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
        if(wy+yAdd>=side || wy+yAdd<0 || ex+xAdd>=side || ex+xAdd<0){ // This is here so that NULL for spareIndex is good.
            if(spareIndex > 0){
                if(ySpareList[(spareIndex)-1] == wy+yAdd && xSpareList[(spareIndex)-1] == ex+xAdd){
                    bResult = origBResult;
                    yAdd = yAddArray[bResult]; // We get the values where to go.
                    xAdd = xAddArray[bResult];
                }
            }
        }
        else{ // Saves on some comparison time.
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

void viewLine(int length, int* viewMap,std::vector<std::vector<std::vector<double>>>* funcTracker, float heightOffset, std::vector<int>& actualMap, std::vector<int>& memoryMap,
    int playerY, int playerX, int playerHeightI, int yTar, int xTar, bool playerIsHigher, bool debug){
	// Just in case in the future, and people would find this out as some sort of bug...
	// It isn't. It just isn't possible with the algorithm to detect every square's edge.
	// So: We rely on the outer squares (the ones at the border of the screen) to create
	// lines that detect alot of the squares. Most of these are pretty accurate, and reveal
	// a lot. These also cause "view scarring", which means as you increase and decrease zoom,
	// the outer squares relative positions and the lines from the player to the outer squares
	// change. Which means things that are closer gets revealed/unrevealled because the lines
	// that went through it previously didn't detect its very edges to find it.
	// We detect later all unrevealled, and try to reveal it again directly.
	// This typically won't work, but catches a few, particularly obvious ones.
	// To put it simply: to fix this 'bug', you'll need to create a double/ triple check lines.
	// This would create lines to the corners to the target square (from the same corners of
	// the player's.) This would mean doing double/triple the per square.
	// TODO Try it out. Maybe it's worth it. Or maybe with a memory mode, it won't matter.
	// You can also just check every square. This new algorithm is a hell lot more efficient,
	// it may be affordable. For now, will be a toggle for comparison. This would remove the
	// problem entirely, particularly for tiles farther away, and is probably actually way
	// worse for efficiency than the double/triple check lines.
	//=====
	// UPDATE DECEMBER 4, 2016: Since we're going to be checking a ton of stuff anyways for optimal results, it now
	// check every "viewline" through every tile in the map. We optimize this by having the funcTracker, which
	// detects if we went on that viewline in this particular circumstances before. Put a print in there to see
	// how much it catches, if you want. We divide the funcTracker via the Swastika segmentation, and access
	// via the particulations of how this line is used and handled.
	// We also now check for perfect diagonals, and disallow "viewlines" from going in between and not accounting
	// for the corners. Using the same algorithm, I happen to fix an old bug too: when player is not higher,
	// then we check if the PREVIOUS tile had a higher hight, since we're bordering on that, and apply that
	// into the minAngle if it's less. Trust me, this was necessary now that we're checking all viewlines and diagonals,
	// and ensures that there's a whole lot less chaos in determining which tiles to reveal.
    if(playerY == yTar && playerX == xTar){
        return; // Same tile. out
    }
    //if(viewMap[(yTar*length)+xTar] == 1){
    //    return; // If it's already revealled, get out.  // TURNED INTO A TOGGLE.
    //}
	//find case
		//if(yTar == 11 && xTar == 0 && playerX == 25){
		//	debug = true;
		//}
	//find case
	//if(yTar == 0 && xTar == 0){
	//	debug = true;
	//}
	std::cout << std::fixed << std::setprecision(19);
    //bool playerIsHigher = false; // If player is higher, we use lookUp Algorithm -> playerIsHigher == !lookUp
	//if(actualMap[(yTar*length)+xTar]<playerHeightI){
	//	playerIsHigher = true;
	//}
	double minAngle = -100.00; //a depth of darkness
	double playerHeight = (double)playerHeightI;
	bool yMode = false; // If function for x > 1, then we must use inverse algorithm.
	int xDiff = xTar-playerX;
	int yDiff = yTar-playerY;
	int mode = 1; // For real traversing
	if(abs(yDiff)>abs(xDiff)){
		yMode=true;
	}
	double function = 0; // For traversing -- mandatory!
	int indent = 0; // To offset by 1 so we don't count beginning twice.
	double xShift = 0; // Shifting X by some for calc
	double yShift = 0; // Shifting Y by some for calc
	double check = 0; // For checking current index -- either for y or x
	double inaccuracy = 0.00000001;
	double inaccuracyOne = 1.00 - inaccuracy;
	int x = playerX;
	int y = playerY;
	int diagChecky=1;
	int diagCheckx=1; // This is for playerIsHigher
	int trackIndex = 1000; // to ensure seg fault
	if(xDiff<=0 && yDiff<0)
	trackIndex = 0;
	else if(xDiff<0 && yDiff>=0)
	trackIndex = 1;
	else if(xDiff>=0 && yDiff>0)
	trackIndex = 2;
	else if(xDiff>0 && yDiff<=0)
	trackIndex = 3;
	if(trackIndex == 1000){
		std::cout << "ERROOOR" << std::endl;
		std::cout << "xDiff: " << xDiff << " yDiff: " << yDiff << std::endl;
		std::cout << "ERROOOR" << std::endl;
	}
	if(debug){
		std::cout << std::endl;
		std::cout << "xDiff: " << xDiff << std::endl;
		std::cout << "yDiff: " << yDiff << std::endl;
		std::cout << "function: " << function << std::endl;
		std::cout << "yTar: " << yTar << " xTar: " << xTar << std::endl;
		std::cout << "playerY: " << playerY << " playerX: " << playerX << std::endl;
		std::cout << "sFunc: " << (yTar - playerY) << std::endl;
		std::cout << "higher: " << playerIsHigher << std::endl;
	}
    int altMode=1; // I almost avoided using this completely
    // until i decided to keep in mind the height of perfect diagonals. Yeah.
	if(yMode){
		function=(double)xDiff/(double)yDiff;
		
		if(xDiff<0){ // Going up in array - visual
			diagCheckx=0;
			indent = -1;
			
			if(function>=0){ // Func is positive
				if(playerIsHigher){ // !lookup
					check = 1.00;
					if(debug)
					std::cout << "MODE 1" << std::endl;
				}
				else { // lookup
					check = inaccuracyOne;
					yShift = inaccuracyOne;
					xShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 2" << std::endl;
				}
			}
			else{ // Func is negative
				if(playerIsHigher){ // !lookup
					yShift = inaccuracyOne;
					check = 1.00;
					if(debug)
					std::cout << "MODE 3" << std::endl;
				}
				else { // lookup
					check = inaccuracyOne;
					xShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 4" << std::endl;
				}
			}
		}
		else { // Going down in array - visual
			indent = 1;
			if(function>=0){ // Func is positive
				if(playerIsHigher){ // !lookup
					check = -inaccuracy;
					xShift = inaccuracyOne;
					if(xDiff!=0) // this is a strange occurance, but necessary
					yShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 5" << std::endl;
				}
				else { // lookup
					if(xDiff==0)
					yShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 6" << std::endl;
				}
			}
			else{ // Func is negative
				if(playerIsHigher){ // !lookup
					xShift = inaccuracyOne;
					check = -inaccuracy;
					if(xDiff==0)
					yShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 7" << std::endl;
				}
				else { // lookup
					if(xDiff!=0)
					yShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 8" << std::endl;
				}
			}
		}
		if(yDiff<=0){
			diagChecky=0;
			mode=-1;
		}
		if(xDiff<=0){
		    altMode=-1;
		}
		if(xDiff && playerIsHigher){
			x+=indent;
		}
	}
	else {
		function=(double)yDiff/(double)xDiff;
		if(debug){
			std::cout << yDiff << " " << xDiff << std::endl;
		}
		if(yDiff<0){ // Going up in array - visual
			indent = -1;
			diagChecky=0;
			if(function>=0){ // Func is positive
				if(playerIsHigher){ // !lookup
					check = 1.00;
					if(debug)
					std::cout << "MODE 9" << std::endl;
				}
				else { // lookup
					check = inaccuracyOne;
					xShift = inaccuracyOne;
					yShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 10" << std::endl;
				}
			}
			else{ // Func is negative
				if(playerIsHigher){ // !lookup
					xShift = inaccuracyOne;
					check = 1.00;
					if(debug)
					std::cout << "MODE 11" << std::endl;
				}
				else { // lookup
					check = inaccuracyOne;
					yShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 12" << std::endl;
				}
			}
		}
		else { // Going down in array - visual
			indent = 1;
			if(function>=0){ // Func is positive
				if(playerIsHigher){ // !lookup
					check = -inaccuracy;
					yShift = inaccuracyOne;
					if(yDiff!=0)
					xShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 13" << std::endl;
				}
				else { // lookup
					if(yDiff==0)
					xShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 14" << std::endl;
				}
			}
			else{ // Func is negative
				if(playerIsHigher){ // !lookup
					if(yDiff==0)
					xShift = inaccuracyOne;
					yShift = inaccuracyOne;
					check = -inaccuracy;
					if(debug)
					std::cout << "MODE 15" << std::endl;
				}
				else { // lookup
					if(yDiff!=0)
					xShift = inaccuracyOne;
					if(debug)
					std::cout << "MODE 16" << std::endl;
				}
			}
		}
		if(xDiff<=0){
			diagCheckx=0;
			mode=-1;
		}
		if(yDiff<=0){
		    altMode=-1;
        	}
		if(yDiff && playerIsHigher){
			y+=indent;
		}
	}
	//std::find(vector.begin(), vector.end(), item) != vector.end()
	std::vector<double>* vectorCheck = &((*funcTracker)[playerIsHigher+yMode*2][trackIndex]);
	if(std::find(vectorCheck->begin(),vectorCheck->end(),function+1.00) != vectorCheck->end()){
		//std::cout << vectorCheck << std::endl;
		//std::cout << trackIndex << " | " << playerIsHigher+yMode*2 << std::endl;
		//std::cout << "xShift: " << xShift << " yShift: " << yShift << std::endl;
		//std::cout << "==== " << function << std::endl;
		//std::cout << "xDiff: " << xDiff << " yDiff: " << yDiff << std::endl;
		//if(yDiff == -23 && (xDiff == -1 || xDiff == 1)){
		//	std::cout << "++++UNIQUE: " << function << std::endl;
		//}
		return;
	}
	else{
		//std::cout << "---ALARM--v: " << std::endl;
		//std::cout << trackIndex << " | " << playerIsHigher+yMode*2 << std::endl;
		//std::cout << "8888 " << function << std::endl;
		//std::cout << "xDiff: " << xDiff << " yDiff: " << yDiff << std::endl;
		//std::cout << "---ALARM--^: " << std::endl;
		//std::cout << "xDiff: " << xDiff << " yDiff: " << yDiff << std::endl;
		vectorCheck->push_back(function+1.00);

	}
	double playerXD = playerX;
	double playerYD = playerY;
	double calc; // for precision
	int get; // for getting index
	int getTwo; // for getting another index
	double tempAngle; // For getting the
	double tempAngle2; // This is for the diagonal.
	bool goBack = false;
	double currHeight;
	bool foundDiagonal;
	double saveDouble; // intermediate for saving double value.
	playerXD += xShift;
	playerYD += yShift;
	playerHeight+=heightOffset; // Because we want to look over edges to an extent.
	if(debug)
	std::cout << "---" << std::endl;
    	int maxHeight = 0; // For perfect diagonals
    	int maxHeight2 = 0; // For perfect diagonals
	if(yMode){
		while(1){
		foundDiagonal = false;
		maxHeight = -1000; // Hopefully.
		maxHeight2 = -1000; // Hopefully.
			if(!goBack){
			y+=mode;}
			if(x<=0 || y <= 0 || x>=length-1 || y>=length-1){ // This is for the else-if next. We don't want to diagonally access something out of range, so we test when we're not on corners/sides.
				if(x<0 || y<0 || x == length || y == length){
					break;
				}
			}
			else if (playerIsHigher && ( (double)((y+diagChecky) - (int)(playerYD+0.5)))*function + round(playerXD) == (double)(x+diagCheckx) && function != 0.00) {
				foundDiagonal = true;
				if(debug){
				std::cout << "====" << std::endl;
				std::cout << "playerY: " << playerY << " playerX: " << playerX << std::endl;
				std::cout << "yTar: " << yTar << " xTar: " << xTar << std::endl;
				std::cout << "func: " << function << std::endl;
				std::cout << "diag5y: " << y+mode << " diag5x: "<<  x << std::endl;
				std::cout << "diag6y: " << y << " diag6x: "<<  x+altMode << std::endl;
				std::cout << "====" << std::endl;
				}
				maxHeight = actualMap[((y+mode)*length)+x];
				maxHeight2 = actualMap[(y*length)+(x+altMode)];
				if(maxHeight2>maxHeight){
			   	 	maxHeight = maxHeight2;
		   		}
			}
			goBack = false; // we do this at start so we can calculate the last
			calc = ((((double)(y) + yShift) - playerYD)*(function)) + playerXD;
			get = calc;
			if(debug){
				std::cout << "startX: " << x << " startY: " << y << std::endl;
				std::cout << "playerXD: " << playerXD << " playerYD: " << playerYD << std::endl;
				std::cout << "calc: " << calc << " get: " << get << std::endl;
				std::cout << "PLAYERISHIGHER: " << playerIsHigher << std::endl;
			}
			if(get != x){
				calc = ((((double)get + check) - playerXD)/(function)) + playerYD;
				saveDouble = ((double)get) + check;
				if((int)(calc) != (y-mode) && playerIsHigher){
					goBack = true;
				}
				else if(!playerIsHigher && (int)calc == y && x!=(int)saveDouble){ // This is case in perfect diagonal crossing !!!
					foundDiagonal = true;
					if(debug){
					std::cout << "====" << std::endl;
					std::cout << "playerY: " << playerY << " playerX: " << playerX << std::endl;
					std::cout << "yTar: " << yTar << " xTar: " << xTar << std::endl;
					std::cout << "func: " << function << std::endl;
					std::cout << "diag7y: " << y << " diag7x: "<<  x << std::endl;
					std::cout << "diag8y: " << y-mode << " diag8x: "<<  x+altMode << std::endl;
					std::cout << "====" << std::endl;
					}
					maxHeight = actualMap[(y*length)+x];
		        		maxHeight2 = actualMap[((y-mode)*length)+(x+altMode)];
				    if(maxHeight2>maxHeight){
				        maxHeight = maxHeight2;
				    }
				    //std::cout << "ALER: " << playerY << " " << playerX << std::endl;
					//std::cout << "BARON: " << yTar << " " << xTar << std::endl;
				    //std::cout << "ALRAM: " << y << " " << x << " " << function << std::endl;
				    //std::cout << "ALRAM2: " << saveDouble << " " << calc << std::endl;
				}
				if(!playerIsHigher){
					maxHeight2 = actualMap[((y-mode)*length)+x];
					if(debug)
					std::cout << "MAXER: " << maxHeight2 << std::endl;
					if(maxHeight2>maxHeight){
				        	maxHeight = maxHeight2; // 
						if(maxHeight>actualMap[(((int)calc)*length)+((int)saveDouble)]){
							foundDiagonal=true; // This is hacky, but works well!
						}
				    	}
				}
                		x = saveDouble; // Both truncates
				y = calc;
				currHeight = actualMap[(y*length)+x];
				tempAngle = (currHeight-playerHeight)/distD(playerYD,playerXD,calc,saveDouble);
				if(foundDiagonal){
					//std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
					tempAngle2 = (maxHeight-playerHeight)/distD(playerYD,playerXD,calc,saveDouble);
				}
				if(debug){
					std::cout << "intermX: " << x << " intermY: " << y << std::endl;
					std::cout << "calc: " << calc << " saveDouble: " << get << std::endl;
					std::cout << "heightDiff: " << (currHeight-playerHeight) << " distD: " << distD(playerYD,playerXD,calc,saveDouble) << std::endl;
					std::cout << "tempAngle: " << tempAngle << std::endl;
				}
			}
			else {
				currHeight = actualMap[(y*length)+x];
				if(!playerIsHigher){
					maxHeight = actualMap[((y-mode)*length)+x];
					if(maxHeight>currHeight){
						foundDiagonal=true; // This is hacky, but works well!
					}
				}
				tempAngle = (currHeight-playerHeight)/distD(playerYD,playerXD,(double)y + yShift,calc);
				if(foundDiagonal){
					tempAngle2 = (maxHeight-playerHeight)/distD(playerYD,playerXD,(double)y + yShift,calc);
				}
				if(debug){
					std::cout << "intermX: " << x << " intermY: " << y << std::endl;
					std::cout << "heightDiff: " << (currHeight-playerHeight) << " distD: " << distD(playerYD,playerXD,(double)y + yShift,calc) << std::endl;
					std::cout << "tempAngle: " << tempAngle << std::endl;
				}
			}
			if(!playerIsHigher && foundDiagonal && tempAngle2>minAngle){
				minAngle = tempAngle2;
			}
			if(tempAngle>=minAngle-inaccuracy){
				if(debug)
				std::cout << "minAngle prev: " << minAngle << std::endl;
		    		viewMap[(y*length)+x] = 1;
				if(memoryMap.size() && memoryMap[(y*length)+x] == 0)
				memoryMap[(y*length)+x] = 2; // two indicates to be added onto real memory too.
				if(tempAngle>minAngle){
		    			minAngle=tempAngle;
				}
				if(debug)
				std::cout << "minAngle now: " << minAngle << std::endl;
			}
			else if(tempAngle<0 && minAngle<=0){
				if(viewMap[(y*length)+x] != 1){
					viewMap[(y*length)+x] = -1;
				}
			}
			if(playerIsHigher && foundDiagonal && tempAngle2>minAngle){
				minAngle = tempAngle2;
			}
			if(debug)
			std::cout << "xBefore: " << x << std::endl;
			x = get;
			if(debug){
				std::cout << "yMode: " << yMode << " x: " << x << " y: " << y << " func: " << function << std::endl;
				std::cout << "yShift: " << yShift << " xShift: " << xShift << " mode: " << mode << " check: " << check << std::endl;
				std::cout << "playerX: " << playerX << " playerY: " << playerY << " playerXD: " << playerXD << " playerYD: " << playerYD << std::endl;
				std::cout << "xTar: " << xTar << " yTar: " << yTar << std::endl;
				for(int i = 0; i<(length*length);i++){
					if(i%length == 0){
						std::cout << std::endl;
					}
					if(viewMap[i] < 0){
						std::cout << 0;
					}
					else{
						std::cout << viewMap[i];
					}
				}
			}
		}
		if(debug) 
		std::cout << "END YMODE FOR" << std::endl;
		if(playerIsHigher)
		viewLine(length,viewMap,funcTracker,heightOffset,actualMap,memoryMap,playerY,playerX,playerHeightI,yTar,xTar,false, debug);
		return;
	}
	while(1){ // used to be while(y != yTar || x != xTar)
	foundDiagonal = false;
        maxHeight = -1000; // Hopefully.
	maxHeight2 = -1000; // Hopefully.
		if(debug)
		std::cout << "goBack: " << goBack << std::endl;
		if(!goBack){
		x+=mode;}
		//std::cout << "WHY: " << y << " EXE: " << x << std::endl;
		if(x<=0 || y <= 0 || x>=length-1 || y>=length-1){ // This is for the else-if next. We don't want to diagonally access something out of range, so we test when we're not on corners/sides.
			if(x<0 || y<0 || x == length || y == length){
				break;
			}
		}
		else if (playerIsHigher && ( (double)((x+diagCheckx) - (int)(playerXD+0.5)))*function + round(playerYD) == (double)(y+diagChecky) && function != 0.00) {
			foundDiagonal = true;
			if(debug){
			std::cout << "====" << std::endl;
			std::cout << "playerY: " << playerY << " playerX: " << playerX << std::endl;
			std::cout << "yTar: " << yTar << " xTar: " << xTar << std::endl;
			std::cout << "func: " << function << std::endl;
			std::cout << "diag1y: " << y+altMode << " diag1x: "<<  x << std::endl;
			std::cout << "diag2y: " << y << " diag2x: "<<  x+mode << std::endl;
			std::cout << "====" << std::endl;
			}
			maxHeight = actualMap[((y+altMode)*length)+x];
	        	maxHeight2 = actualMap[(y*length)+(x+mode)];
			if(maxHeight2>maxHeight){
	           	 	maxHeight = maxHeight2;
	   		}
		}
			
		goBack = false; // we do this at start so we can calculate the last
		calc = ((((double)(x) + xShift) - playerXD)*(function)) + playerYD;
		get = calc;
		if(debug){
			std::cout << "startX: " << x << " startY: " << y << std::endl;
			std::cout << "playerXD: " << playerXD << " playerYD: " << playerYD << std::endl;
			std::cout << "calc: " << calc << " get: " << get << std::endl;
			std::cout << "PLAYERISHIGHER: " << playerIsHigher << std::endl;
		}
		if(get != y){
			calc = ((((double)get + check) - playerYD)/(function)) + playerXD;
			saveDouble = ((double)get) + check;
			if((int)(calc) != (x-mode) && playerIsHigher){
				goBack = true;
			}
			else if(!playerIsHigher && (int)calc == x && y!=(int)saveDouble) {
				foundDiagonal = true;
				if(debug){
				std::cout << "====" << std::endl;
				std::cout << "playerY: " << playerY << " playerX: " << playerX << std::endl;
				std::cout << "yTar: " << yTar << " xTar: " << xTar << std::endl;
				std::cout << "func: " << function << std::endl;
				std::cout << "diag3y: " << y << " diag3x: "<<  x << std::endl;
				std::cout << "diag4y: " << y+altMode << " diag4x: "<<  x-mode<< std::endl;
				std::cout << "====" << std::endl;
				}
				maxHeight = actualMap[((y)*length)+x];
		        	maxHeight2 = actualMap[((y+altMode)*length)+(x-mode)];
				if(maxHeight2>maxHeight){
		           	 	maxHeight = maxHeight2;
		   		}
			}
			if(!playerIsHigher){
				maxHeight2 = actualMap[(y*length)+(x-mode)];
				if(debug)
				std::cout << "MAXER: " << maxHeight2 << std::endl;
				if(maxHeight2>maxHeight){ // Compatibility with diagonals
				       	maxHeight = maxHeight2; // 
					if(maxHeight>actualMap[(((int)saveDouble)*length)+((int)calc)]){
						foundDiagonal=true; // This is hacky, but works well!
					}
				}
			}
		        //std::cout << "ALER: " << playerY << " " << playerX << std::endl;
			//std::cout << "BARON: " << yTar << " " << xTar << std::endl;
		        //std::cout << "ALRAM: " << y << " " << x << " " << function << std::endl;
		        //std::cout << "ALRAM2: " << saveDouble << " " << calc << std::endl;
		    	y = saveDouble; // Both truncates
			x = calc;
			currHeight = actualMap[(y*length)+x];
			tempAngle = (currHeight-playerHeight)/distD(playerYD,playerXD,saveDouble,calc);
			if(foundDiagonal){
				//std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
				tempAngle2 = (maxHeight-playerHeight)/distD(playerYD,playerXD,saveDouble,calc);
			}
			if(debug){
				std::cout << "intermX: " << x << " intermY: " << y << std::endl;
				std::cout << "calc: " << calc << " saveDouble: " << get << std::endl;
				std::cout << "heightDiff: " << (currHeight-playerHeight) << " distD: " << distD(playerYD,playerXD,saveDouble,calc) << std::endl;
				std::cout << "tempAngle: " << tempAngle << std::endl;
			}
		}
		else {
			currHeight = actualMap[(y*length)+x];
			if(!playerIsHigher){
				maxHeight = actualMap[(y*length)+(x-mode)];
				if(maxHeight>currHeight){
					foundDiagonal=true; // This is hacky, but works well!
				}
			}
			tempAngle = (currHeight-playerHeight)/distD(playerYD,playerXD,calc,(double)x + xShift);
			if(foundDiagonal){
				tempAngle2 = (maxHeight-playerHeight)/distD(playerYD,playerXD,calc,(double)x + xShift);
			}
			if(debug){
				std::cout << "intermX: " << x << " intermY: " << y << std::endl;
				std::cout << "heightDiff: " << (currHeight-playerHeight) << " distD: " << distD(playerYD,playerXD,calc,(double)x + xShift) << std::endl;
				std::cout << "tempAngle: " << tempAngle << std::endl;
			}
		}
		if(!playerIsHigher && foundDiagonal && tempAngle2>minAngle){
			minAngle = tempAngle2;
		}
		if(tempAngle>=minAngle-inaccuracy){
			if(debug)
			std::cout << "minAngle prev: " << minAngle << std::endl;
            		viewMap[(y*length)+x] = 1;
		        if(memoryMap.size() && memoryMap[(y*length)+x] == 0)
		        memoryMap[(y*length)+x] = 2; // two indicates to be added onto real memory too.
            		if(tempAngle>minAngle){
		    		minAngle=tempAngle;
			}
			if(debug)
			std::cout << "minAngle now: " << minAngle << std::endl;
		}
		else if(tempAngle<0 && minAngle<=0){
			if(viewMap[(y*length)+x] != 1){
				viewMap[(y*length)+x] = -1;
			}
		}
		if(playerIsHigher && foundDiagonal && tempAngle2>minAngle){
			minAngle = tempAngle2;
		}
		if(debug)
		std::cout << "yBefore: " << y << std::endl;
		y=get; // Ain't that cool.
		if(debug){
			std::cout << "yMode: " << yMode << " x: " << x << " y: " << y << " func: " << function << std::endl;
			std::cout << "yShift: " << yShift << " xShift: " << xShift << " mode: " << mode << " check: " << check << std::endl;
			std::cout << "playerX: " << playerX << " playerY: " << playerY << " playerXD: " << playerXD << " playerYD: " << playerYD << std::endl;
			std::cout << "xTar: " << xTar << " yTar: " << yTar << std::endl;
			for(int i = 0; i<(length*length);i++){
				if(i%length == 0){
					std::cout << std::endl;
				}
				if(viewMap[i] < 0){
					std::cout << 0;
				}
				else{
					std::cout << viewMap[i];
				}
			}
		}
	}
	if(debug)
	std::cout << "END XMODE FOR" << std::endl;
	if(playerIsHigher)
	viewLine(length,viewMap,funcTracker,heightOffset,actualMap,memoryMap,playerY,playerX,playerHeightI,yTar,xTar,false, debug);
	return;
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

//void genCaves(unsigned int seed, double pushCoefficient, 
//    unsigned int startY, unsigned int startX, unsigned int endY, unsigned int endX, worldMap& theWorldMap, bool debug){
//	//Idea's: generate for all of worldmap, connecting all isles, place cave tiles on map (by number), generate that number of 
	// of caves in tile map. We also add random points around that the caves will also generate to (much lower chance for on 
	// ocean tiles) on tilemap. We have a force connect to side if making cave from map to another, 
	// and tile to another, and battlfield to another. Costumized randline required for the height of cave to not go above ground.
//    srand(seed);
//	
//}

// Precondition: It's applied on a valid index.
void fillMap( int filler, int detect, int wall, int pointY, int pointX, unsigned int side, int* map, int* spareMap, bool wallMode, bool replace){ // An earlier bug is where it was just "unsigned side". Apparently that works...
    //std::cout << "GO" << " " << pointY << " " << pointX<< " "  << detect<< " "  << filler << std::endl;
    if(spareMap[(pointY*side) + pointX] == wall){
        wallMode = true;
    }
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

void rawPrintMap(int* map, unsigned int side){
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
           std::cout << std::endl;
        }
        std::cout << map[i];
    }
    std::cout << std::endl;

}

void printMap(int* map, unsigned int side, std::vector<std::string>& tileSet, int specialTiles){
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
           std::cout << std::endl;
        }
        if(map[i] < 0){
            if(map[i] == -1){
                std::cout << " "; // -1 is always blank.
            }
		else if(map[i] == -3){
			i = (((int)(i/side))*side)+(side-1);
		}
            else{
                //std::cout << abs(map[i])-2 << std::endl;
                std::cout << tileSet[abs(map[i])-specialTiles-1]; // Tilesets
            }
        }
        else{
            std::cout << map[i];
        }
    }
    std::cout << std::endl;
}

void rawPrintMapVector(std::vector<int>& map, unsigned int side){
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
           std::cout << std::endl;
        }
        std::cout << map[i];
    }
    std::cout << std::endl;

}

void printMapVector(std::vector<int>& map, unsigned int side, std::vector<std::string>& tileSet,  int specialTiles){
    std::string output = "";
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
        output+='\n';
        }
        //usleep(100);
        if(map[i] < 0){
            if(map[i] == -1){
        output+=' '; // -1 is always blank.
            }
            else if(map[i] == -3){
            i = (((int)(i/side))*side)+(side-1);
        }
            else{
                output+=tileSet[abs(map[i])-specialTiles-1]; // Tilesets
            }; // Tilesets
        }
        else{
        //std::cout <<map[i]<<std::endl;
            output+=std::to_string(map[i]);
        }
    }
    std::cout << output.c_str() << std::endl;
}

void genTile(int seed, double pushCoefficient, int pointY, int pointX, int* map, 
    unsigned int side, int* tileMap, unsigned int tileSide, bool diagonal, bool debug){
    //seed = 1457715766;
    srand(seed);
    //std::cout << "T SEED: " << seed << std::endl;
    int baseHeight = map[(pointY*side) + pointX];
    unsigned int shift = tileSide*0.2;
    int spareTileMap[tileSide*tileSide];
    for(int i = 0; i<tileSide*tileSide; ++i){
        tileMap[i] = baseHeight;
    }
    // Start algorithm.
    int checkDir[9] = { 1,1,1, // 0,1,2 INDEXES QUICK REFERENCE
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
    if(debug){
        std::cout << "T SEED: " << seed << std::endl;
        rawPrintMap(tileMap,tileSide);
    }
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
        else { // This seems good tho.
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
        //printMap(spareMap,side);
        fillMap(1,1,2, startY+((length/2)), startX+((width/2)), side, map, spareMap, false, false);
        //printMap(spareMap,side);
        if(map[0] >= 1){
            std::cout << e << " SEED: "<< seed << std::endl;
            std::cout << "HEIGHT: " << height << " SIDE: " << side << " LENGTH: " << length << " WIDTH: " << width << std::endl;
            rawPrintMap(map,side);
                        
        }
        //printMap(map,side);
    }
    //std::cout << map[2] << " GO " << height << std::endl;
    //std::cout << "END" << std::endl;


}
