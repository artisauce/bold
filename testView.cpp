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

double func(double input, double multiplier, double addition){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
 	return ((input*multiplier + (addition));
}

int viewLine(int length, bool* viewMap, double* angleMap, int* actualMap, 
	int playerY, int playerX, int yTar, int xTar){
	// This algorithm is not meant for 100% certainty. 
	int origHeight = actualMap[(playerY*length)+playerX];
	int tarHeight = actualMap[(yTar*length)+xTar];
	int currHeight = origHeight;
	int xAdd;
	int yAdd;
	double maxAngle = 0.00; 
	double minAngle = 100.00; //a depth of darkness
	int yIndex = playerY;
	int xIndex = playerX;

	// -- inner / outer

	int innerPlayerY = playerY;
	int innerPlayerX = playerX;
	int outerPlayerY = playerY+1;
	int outerPlayerX = playerX+1;
	int yIndexUpper = 0;
	int xIndexUpper = 0;
	int yUpper = 0; // If target higher (less than, on the graph) than player then inner target (towards player) would need indent by 1.
	int xUpper = 0;
	int yLower = 0; 
	int xLower = 0;
	if(yTar < playerY){
		yUpper = 1;
	}
	else if(yTar > playerY){
		innerPlayerY = playerY+1;
		outerPlayerY = playerY;
		yIndexUpper = 1;
		yLower = -1;
	}
	if(xTar < playerX){
		xUpper = 1;
	}
	else if(xTar > playerX){
		innerPlayerX = playerX+1;
		outerPlayerX = playerX;
		xIndexUpper = 1;
		xLower = -1;
	}

	// functions
	double function = 0;
	int special = 0; // For special line cases.
	int yDiff = yTar-playerY;
	int xDiff = xTar-playerX;
	int upMode = 0;
	int rightMode = 0;
	if(abs(yDiff)>abs(xDiff)){
		upMode = abs(yDiff)/yDiff;
	}
	else{
		rightMode = abs(xDiff)/xDiff;
	}
	double checkerOffset = 0;
	if(xDiff == 0 || yDiff == 0 || abs(xDiff)=abs(yDiff)){
		if(xDiff == 0){
			if(yDiff > 0){
				special = 1; // 1 is up/down
			}
			else {
				special = -1;
			}
		}
		else if(yDiff == 0){
			if(xDiff > 0){
				special = 2; // 2 is left/right
			}
			else {
				special = -2;
			}
		}
		else {
			if(xDiff/yDiff > 0){
				if(yDiff > 0){
					special = 3; // 3 is upright
				}
				else{
					special = -3; // bottom left
				}
			}
			else {
				if(yDiff > 0){
					special = 4; // 4 is upleft
				}
				else{
					special = -4; // bottomright
				}
			}
		}
	}
	else {
		if(upMode){
			if(tarHeight<currHeight){
				function = ((xTar+xLower)-innerPlayerX)/((xTar+yLower)-innerPlayerY); // multiply by current Y to get X.
				// ((x - playerX)* functionX) + playerY
			}
			else {
				function = ((xTar+xUpper)-outerPlayerX)/((yTar+yUpper)-outerPlayerY); // multiply by current Y to get X.
				// ((x - playerX)* functionX) + playerY
			}
		}
		else{
			if(tarHeight<currHeight){
				function = ((yTar+yLower)-innerPlayerY)/((xTar+xLower)-innerPlayerX); // multiply by current X to get Y.
				// ((y - playerY)* functionX) + playerX
			}
			else {
				function = ((yTar+yUpper)-outerPlayerY)/((xTar+xUpper)-outerPlayerX); // multiply by current X to get Y.
				// ((y - playerY)* functionX) + playerX
			}
		}
		
	}
	

	// results

	int aSpecial;
	double result;
	int bResult;
	while(xIndex != xTar && yIndex != yTar){
		// determine direction
		if(special!=0){
			if(upMode){ // dealing with y as input

			}
			else{ // dealing with x as input
				checkerOffset = func((double)xIndex+(double)rightMode,function,(double)yIndex+(double)yIndexUpper);
				if(yIndex+yIndexUpper != (int)(checkOffset - 0.00001) ){ // 0.00...1 is the inaccuracy, but needed for trunsation.
					if()
				}
				
			}
		}
		else{
			aSpecial = abs(special);
			if(special == 1){
				yIndex+=(aSpecial/special);
			}
			else if(special == 2){
				xIndex+=(aSpecial/special);
			}
			else if(special == 3){
				yIndex+=(aSpecial/special);
				xIndex+=(aSpecial/special);
			}
			else{
				yIndex+=(aSpecial/special);
				xIndex-=(aSpecial/special);
			}
		}
		currHeight = actualMap[(yIndex*length)+xIndex];
		if(currHeight == playerHeight){
			if(maxAngle > 0){
				viewMap[(yIndex*length)+xIndex] = -currHeight-2;
			}
			else{
				viewMap[(yIndex*length)+xIndex] = currHeight;
			}
		}
		else if(currHeight > playerHeight){
			if(dist(outerPlayerY))
		}
		else {

		}

	}

}

int main(){
	int rX=1; // Player cords
	int rY=1;
	int length = 3;
	bool viewMap[length*length];
	//int dRealList[13] = 	{ 8, 9,   6,3,2, 1, 4, 7, 8, 9,6,     3,2, 1, 4};  // Adjusted for map display.
	int yAddArray[13] = 	{-1,-1,   0,1,1, 1, 0,-1,-1,-1,0,     1,1, 1, 0};
    int xAddArray[13] = 	{ 0, 1,   1,1,0,-1,-1,-1, 0, 1,1,     1,0,-1,-1};
	double angleMap[length*length];
	int actualMap[] = {	1,1,1,
						1,0,1,
						1,1,1}
	for(int i = 0; i < length*length; i++)
	{
		viewMap[i] = false;
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