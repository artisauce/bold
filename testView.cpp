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

double distD(double startY, double startX, double endY, double endX){
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
	double minAngle = -100.00; //a depth of darkness
	int yIndex = playerY;
	int xIndex = playerX;

	// -- inner / outer

	int innerY = 0;// t
	int innerX = 0;//  \
	int outerY = 1;//   \
	int outerX = 1;//    p
	int tarYInner = 1; // If target higher (less than, on the graph) than player then inner target (towards player) would need indent by 1.
	int tarXInner = 1;
	int tarYOuter = 0; 
	int tarXOuter = 0;
	if(yTar > playerY){
		innerY = 1;
		outerY = 0;
		tarYInner = 0;
		tarYOuter = 1;
	}
	if(xTar > playerX){
		innerX = 1;
		outerX = 0;
		tarXInner = 0;
		tarXOuter = 1;
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
		rightMode = abs(xDiff)/xDiff;
	}
	else{
		rightMode = abs(xDiff)/xDiff;
		upMode = abs(yDiff)/yDiff;
	}
	double checkerOffset = 0;
	int indentY;
	int indentX;
	int indentTarX;
	int indentTarY;
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
			if(tarHeight<playerHeight){
				function = ((xTar+tarXOuter)-(playerX+innerX))/((yTar+yOuter)-(playerY+innerY)); // multiply by current Y to get X.
				indentTarX = tarXOuter;
				indentTarY = tarYOuter;
				indentX = innerX;
				indentY = innerY;
				// ((x - playerX)* functionX) + playerY
			}
			else {
				function = ((xTar+tarXInner)-(playerX+outerX))/((yTar+yInner)-(playerY+outerY)); // multiply by current Y to get X.
				indentTarX = tarXInner;
				indentTarY = tarYInner;
				indentX = outerX;
				indentY = outerY;
				// ((x - playerX)* functionX) + playerY
			}
		}
		else{
			if(tarHeight<playerHeight){
				function = ((yTar+yOuter)-(playerY+innerY))/((xTar+tarXOuter)-(playerX+innerX)); // multiply by current X to get Y.
				indentTarX = tarXOuter;
				indentTarY = tarYOuter;
				indentX = innerX;
				indentY = innerY;
				// ((y - playerY)* functionX) + playerX
			}
			else {
				function = ((yTar+yInner)-(playerY+outerY))/((xTar+tarXInner)-(playerX+outerX)); // multiply by current X to get Y.
				indentTarX = tarXInner;
				indentTarY = tarYInner;
				indentX = outerX;
				indentY = outerY;
				// ((y - playerY)* functionX) + playerX
			}
		}
		
	}
	

	// results

	int aSpecial;
	double result;
	int bResult;
	double tempAngle;
	double inaccuray = 0.000001;
	while(xIndex + indentX != xTar && yIndex + indentY != yTar){
		// determine direction
		if(special!=0){
			if(upMode){ // dealing with y as input

			}
			else{ // dealing with x as input
				checkerOffset = func((double)((xIndex+rightMode)-playerX),function,(double)playerY); // move right, find y. remove both indents adding to  rightmode and playerX.
				if(yIndex != (int)(checkOffset - 0.00001) ){ // 0.00...1 is the inaccuracy, but needed for trunsation. remove both indentY and indentY adding to playerY above.
					currHeight = actualMap[((yIndex+upMode)*length)+xIndex];
					tempAngle = (playerHeight - currHeight)/distD((double)playerY,(double)playerX,(double)(yIndex + upMode),(double)xIndex); // removed indents, xdiff and ydif is same anyhow, and that is used for calculating distance.
					func((double)yIndex+(double)indentY,(1.00/function),(double)playerX+(double)indentX);
					(double startY, double startX, double endY, double endX)
				}
				
			}
		}
		else{
			aSpecial = abs(special)/special;
			if(special == 1){
				yIndex+=aSpecial;
			}
			else if(special == 2){
				xIndex+=aSpecial;
			}
			else if(special == 3){
				yIndex+=aSpecial;
				xIndex+=aSpecial;
			}
			else{
				yIndex+=aSpecial;
				xIndex-=aSpecial;
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