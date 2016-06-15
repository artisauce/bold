#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;
# define M_PI           3.14159265358979323846  /* lol it's pi */

// Get me meh distance.
double dist(int startY, int startX, int endY, int endX){
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

unsigned int randLine(unsigned int seed, double pushCoefficient, int startY, int startX, int endY, int endX, 
unsigned int* yList, unsigned int* xList, int* ySpareList, int* xSpareList,
unsigned int side, bool diagonal, bool debug){
    srand(1379966042);
	if(debug){
		cout << "--------- SEED: " << seed << " ---------" << endl;
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
	yList[0] = startY;
	xList[0] = startX;
    unsigned int index = 1;
	unsigned int spareIndex = 0;
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
        if(random>299 && distToA < orig){ // Checks if, by absolute means, we're going straight or not. We can still go straight...
           // Also check if distToA larger than orig. Found this by debugging, still possible. :/

            //double pushCoefficient = 0.5; 
		// Great than 0. Lower than zero means tendency means less push,
            // greater than 1 means greater push towards end point.
		// values 0.1 to 0.5 seem good. Recommend 0.1.
            int primChance = (int)(999.5 - (pow(((orig-distToA)/orig),pushCoefficient)*700)); //999 is max, 299 min. We truncate-round,
            // so add 0.5.
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
        if(yList[index-1] == wy+yAdd && xList[index-1] == ex+xAdd){
            bResult = origBResult;
            yAdd = yAddArray[bResult]; // We get the values where to go.
            xAdd = xAddArray[bResult];
        }
        if(diagonal && yAdd*xAdd) { // Check if diagonal.
            if(dist(wy+yAdd,ex,endY,endX) < dist(wy,ex+xAdd,endY,endX)){
                yList[index] = wy+yAdd;
                xList[index] = ex;
                //map[((wy+yAdd)*side) + ex] = 2;
            }
            else{
                yList[index] = wy;
                xList[index] = ex+xAdd;
                //map[(wy*side) + ex+xAdd] = 2;
            }
            index++;
        }
        //--------------- DEBUG STUFF. /t for tabbing.
        if(debug){
        cout << "WY: " << wy << "+" << yAdd << "\tEX:" << ex << "+" << xAdd << "\tDRES:" << dList[bResult] << 
        "\tRES:" << (result*180)/M_PI;
        if(result!=0){
            cout <<"\tDELY:";
        }
        else{
            cout << "\t\tDELY:";
        }
        double distanceC = dist(wy,ex,startY,startX) + 1;
        cout << (endY-wy) << "\tDELX:" << (endX-ex) << "\tDIST:" << distanceC + 1;
        if(distanceC-floor(distanceC) > 0){
            cout << "\tCHANCE:";
        }
        else{
            cout << "\t\tCHANCE:";
        }
        cout << (int)(999.5 - (pow(((orig-(dist(wy,ex,startY,startX)+1))/orig),0.5)*700)) << "\tRANDOM:" << random << endl;
        }
        //---------------
	ex=ex+xAdd;
	wy=wy+yAdd;
	if(wy>=side || wy<0 || ex>=side || ex<0){
		cout << "OUTSIDE" << endl;
		xSpareList[spareIndex] = (ex);
        	ySpareList[spareIndex] = (wy);
        	spareIndex++;
	}
	else{
		xList[index] = (ex);
		yList[index] = (wy);
		index++;
	}
        //map[(wy*side) + ex] = 1;
    }
	xSpareList[spareIndex] = 1;
        ySpareList[spareIndex] = 1; // Why 1 and 1? Because all maps are 1x1 or greater, and spare is exclusively for coordinates
	// outside of map. We use that for length.
	return index; // Return length.
}

void circle(double pushCoefficient, unsigned int pointX, unsigned int pointY, unsigned int radius, 
unsigned int* map, unsigned int side, bool diagonal, bool debug){
	
}

int main () {
//unsigned int side = 20; changed to const below
const unsigned int side = 20;
    unsigned int yList[side*side];
    unsigned int xList[side*side];
	int ySpareList[side*side];
    int xSpareList[side*side];
    unsigned int map[side*side];
	bool debug = true;
	//-- For testing for BAD STUFF
	while(1){ // Since it's RNG... we'll need a lot to detect even a tiny bug.
	//--
    for (int i = 0; i < side*side; ++i)
    {
        map[i] = 0;
    }
    int length = randLine(rand(), 0.1, (side/2)-1, 0,  (side/2)-1, side-1, yList, xList, ySpareList,xSpareList, side, false,debug);
	//----------
	for(int i = 0; i<length; ++i){
		map[ (yList[i]*side) + xList[i] ] = 1;
		if(debug){
		cout << "Y: " << yList[i] << " X: " << xList[i] << endl;
		}
	}
	//----------
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
            cout << endl;
        }
        cout << map[i];

    }
	cout << endl;
	//--
    }
	//--
}
