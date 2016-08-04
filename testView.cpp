#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdexcept>      // std::out_of_range
# define M_PI           3.14159265358979323846  /* lol it's pi */

double dist(int startY, int startX, int endY, int endX){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

int viewLine(int length, int* viewMap, double* angleMap, int* actualMap, 
	int playerY, int playerX,
	int playerHeight, int yTar, int xTar){
	int origHeight = currHeight = actualMap[(yIndex*length)+xIndex];
	int currHeight = origHeight;
	int xAdd;
	int yAdd;
	double maxAngle = 0.00; 
	double minAngle = 100.00; //a depth of darkness
	int yIndex = playerY;
	int xIndex = playerX;
	//double functionY = (playerY-yTar)/(playerX-xTar); // multiply by current X to get Y.
	//double functionX = (playerX-xTar)/(playerY-yTar); // multiply by current X to get Y.
	// ((x - playerX)* functionY) + playerY
	// ((y - playerY)* functionX) + playerX
	double result;
	int innerPlayerY;
	int innerPlayerX;
	int outerPlayerY;
	int outerPlayerX;
	int bResult;
	while(xIndex != xTar && yIndex != yTar){
		result = atan2((playerY-yIndex),(playerX-xIndex)) + (M_PI * 2);
		result = fmod(result,(M_PI * 2));
		bResult = (int)((result * (180/(M_PI*45)))+2.5);
		yAdd = yAddArray[bResult];
		xAdd = xAddArray[bResult]; // what comes next
		// See randline function in toolkit.cpp for more documentation on this.
		yIndex+=yAdd;
		xIndex+=xAdd;
		currHeight = actualMap[(yIndex*length)+xIndex];
		if(currHeight == playerHeight){
			if(maxAngle > 0){
				viewMap[(yIndex*length)+xIndex] = -currHeight-2;
			}
			else{
				viewMap[(yIndex*length)+xIndex] = currHeight;
				if()
			}
		}
		else if(currHeight > playerHeight){

		}
		else {

		}

	}

}

int main(){
	int rX=1; // Player cords
	int rY=1;
	int length = 3;
	int viewMap[length*length];
	//int dRealList[13] = 	{ 8, 9,   6,3,2, 1, 4, 7, 8, 9,6,     3,2, 1, 4};  // Adjusted for map display.
	int yAddArray[13] = 	{-1,-1,   0,1,1, 1, 0,-1,-1,-1,0,     1,1, 1, 0};
    int xAddArray[13] = 	{ 0, 1,   1,1,0,-1,-1,-1, 0, 1,1,     1,0,-1,-1};
	double angleMap[length*length];
	int actualMap[] = {	1,1,1,
						1,0,1,
						1,1,1}
	for(int i = 0; i < length*length; i++)
	{
		viewMap[i] = -1;
	}
	viewMap[(rY*length)+rX] = actualMap[(rY*length)+rX];
	int xAdd;
	int yAdd;
	int bResult;
	double result;
	int wy;
	int ex;
	for(int y = 0; y < length; y++)
	{
		for (int x = 0; x < length; x++)
		{
			wy = y;
			ex = x;
			double functionY = (playerY-wy)/(playerX-ex); // multiply by current X to get Y.
			double functionX = (playerX-ex)/(playerY-wy); // multiply by current X to get Y.
			while(1) { // Bad programming? LOL.
				double result = atan2((playerY-wy),(playerX-ex)) + (M_PI * 2);
	        	result = fmod(result,(M_PI * 2));
	        	int bResult = (int)((result * (180/(M_PI*45)))+2.5);
	        	int yAdd = yAddArray[bResult];
	        	int xAdd = xAddArray[bResult]; // what comes next
	        	// See randline function in toolkit.cpp for more documentation on this.


	        }
			
		}
	}
}