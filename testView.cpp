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

double distD(int startY, int startX, double endY, double endX){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    double dx = (endX-(double)startX);
    double dy = (endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}


double dist(int startY, int startX, int endY, int endX){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

double func(double input, double multiplier, double addition){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
 	return ((input*multiplier) + (addition));
}

void viewLine(int length, bool* viewMap, int* actualMap, 
	int playerY, int playerX, int yTar, int xTar){
	if(playerY == yTar && playerX == xTar){
		return;
	}
	//std::cout << "GORE2" << std::endl;
	// This algorithm is not meant for 100% certainty. 
	int playerHeight = actualMap[(playerY*length)+playerX];
	int tarHeight = actualMap[(yTar*length)+xTar];
	int currHeight = playerHeight;
	double maxAngle = 0.00; 
	double minAngle = -100.00; //a depth of darkness
	int yIndex = playerY;
	int xIndex = playerX;

	// -- inner / outer

	int innerY = 0;
	int innerX = 0;
	int outerY = 1;
	int outerX = 1;
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
	//std::cout << "GORE4" << std::endl;
	// functions
	double function = 0;
	int special = 0; // For special line cases.
	int yDiff = yTar-playerY;
	int xDiff = xTar-playerX;
	int upMode = 0;
	int rightMode = 0;
	//std::cout << "GORDON " << xDiff << " " << yDiff << std::endl;
	if(abs(yDiff)>abs(xDiff)){
		upMode = abs(yDiff)/yDiff;
		if(xDiff!=0){
			rightMode = abs(xDiff)/xDiff;
		}
	}
	else{
		rightMode = abs(xDiff)/xDiff;
		if(yDiff!=0){
			upMode = abs(yDiff)/yDiff;
		}
	}
	double checkOffset = 0;
	int indentY;
	int indentX;
	int indentTarX;
	int indentTarY;
	//std::cout << "GORE3" << std::endl;
	if(xDiff == 0 || yDiff == 0 || abs(xDiff)==abs(yDiff)){
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
				function = ((xTar+tarXOuter)-(playerX+innerX))/((yTar+tarYOuter)-(playerY+innerY)); // multiply by current Y to get X.
				indentTarX = tarXOuter;
				indentTarY = tarYOuter;
				indentX = innerX;
				indentY = innerY;
				// ((x - playerX)* functionX) + playerY
			}
			else {
				function = ((xTar+tarXInner)-(playerX+outerX))/((yTar+tarYInner)-(playerY+outerY)); // multiply by current Y to get X.
				indentTarX = tarXInner;
				indentTarY = tarYInner;
				indentX = outerX;
				indentY = outerY;
				// ((x - playerX)* functionX) + playerY
			}
		}
		else{
			if(tarHeight<playerHeight){
				function = ((yTar+tarYOuter)-(playerY+innerY))/((xTar+tarXOuter)-(playerX+innerX)); // multiply by current X to get Y.
				indentTarX = tarXOuter;
				indentTarY = tarYOuter;
				indentX = innerX;
				indentY = innerY;
				// ((y - playerY)* functionX) + playerX
			}
			else {
				function = ((yTar+tarXInner)-(playerY+outerY))/((xTar+tarXInner)-(playerX+outerX)); // multiply by current X to get Y.
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
	double tempAngle;
	double inaccuray = 0.000001;
	//std::cout << "GO" << std::endl;
	while(xIndex != xTar && yIndex  != yTar){
		// determine direction
		//std::cout << "GORE" << std::endl;
		if(special==0){
			if(upMode){ // dealing with y as input
				checkOffset = func((double)((yIndex+upMode)-playerY),function,(double)playerX); // move right, find y. remove both indents adding to  rightmode and playerX.
				if(xIndex != (int)(checkOffset - 0.00001) ){ // 0.00...1 is the inaccuracy, but needed for trunsation. remove both indentY and indentY adding to playerY above.
					xIndex += rightMode;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,func((double)(xIndex-playerX),(1.00/function),(double)playerY),(double)xIndex); 
					// removed indents, xdiff and ydif is same anyhow, and that is used for calculating distance.
				}
				else{
					yIndex += upMode;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,(double)yIndex,checkOffset); 
				}
			}
			else{ // dealing with x as input
				checkOffset = func((double)((xIndex+rightMode)-playerX),function,(double)playerY); // move right, find y. remove both indents adding to  rightmode and playerX.
				if(yIndex != (int)(checkOffset - 0.00001) ){ // 0.00...1 is the inaccuracy, but needed for trunsation. remove both indentY and indentY adding to playerY above.
					yIndex += upMode;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,(double)yIndex,func((double)(yIndex-playerY),(1.00/function),(double)playerX)); 
					// removed indents, xdiff and ydif is same anyhow, and that is used for calculating distance.
				}
				else{
					xIndex += rightMode;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,checkOffset,(double)xIndex); 
				}
				
			}
		}
		else{
			//std::cout << "GO2R" << std::endl;
			aSpecial = abs(special)/special;
			if(abs(special) == 1){
				yIndex+=aSpecial;
			}
			else if(abs(special) == 2){
				xIndex+=aSpecial;
			}
			else if(abs(special) == 3){
				yIndex+=aSpecial;
				xIndex+=aSpecial;
			}
			else{
				yIndex+=aSpecial;
				xIndex-=aSpecial;
			}
			currHeight = actualMap[(yIndex*length)+xIndex];
			tempAngle = (currHeight - playerHeight)/dist(playerY,playerX,yIndex,xIndex);

		}
		if(currHeight == playerHeight){
			if(maxAngle == 0){
				viewMap[(yIndex*length)+xIndex] = true;
			}
		}
		else if(tempAngle<0){
			if(tempAngle>minAngle){
				viewMap[(yIndex*length)+xIndex] = true;
				minAngle=tempAngle;
			}
		}
		else{
			if(tempAngle<maxAngle){
				viewMap[(yIndex*length)+xIndex] = true;
				maxAngle=tempAngle;
			}
		}
		//std::cout << "GO3 " << special << " " << tempAngle << " " <<  minAngle << " " << maxAngle << " " << currHeight << " " << checkOffset << std::endl;
		//std::cout << "GO2 " << xIndex << " " << xTar << " " << yIndex << " " << yTar << " " << playerY << " " << playerX << std::endl;
		//xIndex != xTar && yIndex  != yTar

	}
	//std::cout << "FIN" << std::endl;
}

int main(){
	int rX=1; // Player cords
	int rY=1;
	int length = 3;
	bool viewMap[(length*length)];
	//int dRealList[13] = 	{ 8, 9,   6,3,2, 1, 4, 7, 8, 9,6,     3,2, 1, 4};  // Adjusted for map display.
	double angleMap[length*length];
	int actualMap[] = {	1,1,1,
						1,0,1,
						1,1,1};
	for(int i = 0; i < length*length; i++)
	{
		viewMap[i] = false;
	}
	viewMap[(rY*length)+rX] = true;
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
			if(!viewMap[(y*length)]+x){
				//std::cout << "GOREdO" << std::endl;
				viewLine(length,viewMap,actualMap,rY, rX, y, x);
				//std::cout << "GOREd" << std::endl;
			}
		}
	}
	for(int y = 0; y < length; y++)
	{
		for (int x = 0; x < length; x++)
		{
			if(viewMap[(y*length)]+x){
				std::cout << actualMap[(y*length)+x];
			}
			else{
				std::cout << " ";
			}
			
		}
		std::cout << std::endl;
	}
}