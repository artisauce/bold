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
double dist(unsigned int startY, unsigned int startX, unsigned int endY, unsigned int endX){
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

void randLine(unsigned int startY, unsigned int startX, unsigned int endY, unsigned int endX, unsigned int* yList, unsigned int* xList, unsigned int* map, unsigned int side, bool diagonal, bool debug){
    srand(time(NULL));
    int dList[13]  = {    2, 3,   6,9,8, 7, 4, 1, 2, 3,6,     9,8}; // Navigation array. Check numpad.
    int dRealList[13] = { 8, 9,   6,3,2, 1, 4, 7, 8, 9,6,     3,2};  // Adjusted for map display.
    // No longer in use. Use as reference instead.
    int yAddArray[13] = {-1,-1,   0,1,1, 1, 0,-1,-1,-1,0,     1,1};
    int xAddArray[13] = { 0, 1,   1,1,0,-1,-1,-1, 0, 1,1,     1,0};
    double orig = dist(startY,startX,endY,endX); // Get original distance..
    unsigned int ex = startX; // X
    unsigned int wy = startY; // Y
    map[(startY*side) + startX] = 1;
    unsigned int index = 1;
    while(ex != endX || wy != endY){
        double result = atan2((int)(endY-wy),(int)(endX-ex));
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
        if(random>299){ // Checks if, by absolute means, we're going straight or not. We can still go straight...
            double distToA = dist(wy,ex,startY,startX) + 1; // Add one so there's a 100% chance when right
            // beside the goal. Unfortunately, it means a more push to goal. Fix?
            double pushCoefficient = 0.5; // Great than 0. Lower than zero means tendency means less push,
            // greater than 1 means greater push towards end point.
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
                map[((wy+yAdd)*side) + ex] = 2;
            }
            else{
                yList[index] = wy;
                xList[index] = ex+xAdd;
                map[(wy*side) + ex+xAdd] = 2;
            }
            index++;
        }
        //---------------
        if(debug){
        cout << "EX: " << wy << "+" << yAdd << "\tWY:" << ex << "+" << xAdd << "\tDRES:" << dRealList[bResult] << 
        "\tRES:" << result;
        if(result!=0){
            cout <<"\tDELY:";
        }
        else{
            cout << "\t\tDELY:";
        }
        double distanceC = dist(wy,ex,startY,startX) + 1;
        cout << (int)(endY-wy) << "\tDELX:" << (endX-ex) << "\tDIST:" << distanceC + 1;
        if(distanceC-floor(distanceC) > 0){
            cout << "\tCHANCE:";
        }
        else{
            cout << "\t\tCHANCE:";
        }
        cout << (int)(999.5 - (pow(((orig-(dist(wy,ex,startY,startX)+1))/orig),0.5)*700)) << "\tRANDOM:" << random << endl;
        }
        //---------------

        xList[index] = (ex+xAdd);
        yList[index] = (wy+yAdd);
        index++;
        ex = ex + xAdd;
        wy = wy + yAdd;
        map[(wy*side) + ex] = 1;

    }
}

int main () {
    unsigned int side = 100;
    unsigned int yList[side*side];
    unsigned int xList[side*side];
    unsigned int map[side*side];
    for (int i = 0; i < side*side; ++i)
    {
        map[i] = 0;
    }
    randLine( 49, 0,  49, 99, yList, xList, map, side, false,true);
    for (int i = 0; i < side*side; ++i)
    {
        if(i%100 == 0){
            cout << endl;
        }
        cout << map[i];

    }
    
}
