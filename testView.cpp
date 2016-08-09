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
	if(viewMap[(yTar*length)+xTar]){
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

	double innerY = 0;
	double innerX = 0;
	double outerY = 1;
	double outerX = 1;
	double tarYInner = 1; // If target higher (less than, on the graph) than player then inner target (towards player) would need indent by 1.
	double tarXInner = 1;
	double tarYOuter = 0; 
	double tarXOuter = 0;
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
	bool goUp = false;
	//std::cout << "GORDON " << xDiff << " " << yDiff << std::endl;
	if(abs(yDiff)>abs(xDiff)){
		goUp = true;
	}
	if(xDiff!=0){
		rightMode = abs(xDiff)/xDiff;
	}
	if(yDiff!=0){
		upMode = abs(yDiff)/yDiff;
	}
	double checkOffset = 0;
	double indentY;
	double indentX;
	double indentTarX;
	double indentTarY;
	bool playerIsHigher = false;
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
		if(goUp){
			if(tarHeight>playerHeight){ // NOTE: You can swap the sign and the insides of the if/else to swap visibility behaviour of tiles that are same height.
				function = ((xTar+tarXInner)-(playerX+outerX))/((yTar+tarYInner)-(playerY+outerY)); // multiply by current Y to get X.
				indentTarX = tarXInner;
				indentTarY = tarYInner;
				indentX = outerX;
				indentY = outerY;
				// ((x - playerX)* functionX) + playerY
			}
			else {
				playerIsHigher = true;
				function = ((xTar+tarXOuter)-(playerX+innerX))/((yTar+tarYOuter)-(playerY+innerY)); // multiply by current Y to get X.
				indentTarX = tarXOuter;
				indentTarY = tarYOuter;
				indentX = innerX;
				indentY = innerY;
				// ((x - playerX)* functionX) + playerY
				//std::cout << "indent y: " << indentY << " x: " << indentX << " tar_indent_y: " << indentTarY << " tar_indent_x: " << indentTarX << " " << function << std::endl;
				//std::cout << "tarx: " << xTar+tarXInner << " tary: " << (yTar+tarYInner) << " playerx: " << (playerX+outerX) << " playery: " << (playerY+outerY) << " "<< std::endl;
				//std::cout << "x: " << ((xTar+tarXInner)-(playerX+outerX)) << " y: " << ((yTar+tarYInner)-(playerY+outerY)) << std::endl;
				//std::cout << "all: " << ((xTar+tarXInner)-(playerX+outerX))/((yTar+tarYInner)-(playerY+outerY)) << std::endl;
			}
		}
		else{
			if(tarHeight>playerHeight){
				function = ((yTar+tarYInner)-(playerY+outerY))/((xTar+tarXInner)-(playerX+outerX)); // multiply by current X to get Y.
				//std::cout << "FUN: " << function << std::endl;
				//std::cout << "FUN: " << function << std::endl;
				indentTarX = tarXInner;
				indentTarY = tarYInner;
				indentX = outerX;
				indentY = outerY;
				// ((y - playerY)* functionX) + playerX
			}
			else {
				playerIsHigher = true;
				function = ((yTar+tarYOuter)-(playerY+innerY))/((xTar+tarXOuter)-(playerX+innerX)); // multiply by current X to get Y.
				indentTarX = tarXOuter;
				indentTarY = tarYOuter;
				indentX = innerX;
				indentY = innerY;
				
				// ((y - playerY)* functionX) + playerX
			}
		}
	}
	// technical
	double xCheck = 0; // either 0.9999... or 0. For negative traversing
	double yCheck = 0;
	double xShift = 0; // either 0 or 0.0000...1. For negative traversing AND function.
	double yShift = 0;
	double inaccuracy = 0.001;
	// technical
	if(yDiff<0){
		yCheck = 1-inaccuracy;
		if(function<0){
			yShift = inaccuracy;
		}
	}
	//std::cout << "AHHHHH " << xDiff << std::endl;
	//std::cout << "AHHHHH2 " << function << std::endl;
	if(xDiff<0){
		//std::cout << "CHECK " << xDiff << std::endl;
		xCheck = 1-inaccuracy;
		if(function<0){
			//std::cout << "CHECK2 " << xDiff << std::endl;
			xShift = inaccuracy;
			
		}
	}
	

	// results
	int aSpecial;
	double tempAngle;
	double indexHolder;
	bool alternateAngle = false;
	bool ticker = true; // used for certain indents.
	//std::cout << "---xIndex: " << xIndex << " xTar: " << xTar << " yIndex: " << yIndex << " yTar: " << yTar << " playerY: " << playerY << " playerX: " << playerX << std::endl;
	while(xIndex != xTar || yIndex  != yTar){
		// determine direction
		//std::cout << "GORE" << std::endl;
		if(special==0){
			if(goUp){ // dealing with y as input
				yIndex+=upMode;
				checkOffset = func(((double)(yIndex-indentY-playerY))+yCheck,function,((double)(playerX+indentX))-xShift);
				//std::cout << "GORED " << checkOffset << " " <<yCheck <<  " " << xShift <<  " " << xCheck<< std::endl;
				//std::cout << 	"GORED2 " << yIndex << 
				//				" " << ((double)(yIndex-indentY-playerY)) <<  
				//				" " << ((double)(yIndex-indentY-playerY))+yCheck <<  
				//				" " << ((double)(playerX+indentX))-xShift<< std::endl;
				if(xIndex != (int)(checkOffset) ){
					yIndex=(int)func((double)((int)(checkOffset-xShift)-indentX-playerX+xCheck),(1.00/function),((double)(indentY+playerY))-yShift);
					//std::cout << "GORE3" << std::endl;
					xIndex += rightMode;
					currHeight = actualMap[(yIndex*length)+xIndex];
					//std::cout << "height diff: " << (currHeight - playerHeight) << std::endl;
					//std::cout << "x calc " << xIndex << std::endl;
					//std::cout << "y calc: " << func((double)(xIndex-playerX-indentX),(1.00/function),(double)(playerY+indentY)) << std::endl;
					//std::cout << "x player calc: " << playerX << std::endl;
					//std::cout << "y player calc " << playerY << std::endl;
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,func((double)(xIndex-playerX-indentX+xCheck),(1.00/function),(double)(playerY+indentY)),(double)xIndex); 
					// removed indents, xdiff and ydif is same anyhow, and that is used for calculating distance.
				}
				else{
					//std::cout << "GORE4" << std::endl;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,(double)yIndex,checkOffset); 
					//std::cout << "height diff: " << (currHeight - playerHeight) << std::endl;
					//std::cout << "x calc " << checkOffset << std::endl;
					//std::cout << "y calc: " << yIndex << std::endl;
					//std::cout << "x player calc: " << playerX << std::endl;
					//std::cout << "y player calc " << playerY << std::endl;
				}
			}
			else{ // dealing with x as input
				xIndex+=rightMode;
				//std::cout << "yShift " << yShift << std::endl;
				//std::cout << "GORE3 " << xShift << std::endl;
				//std::cout << "GORE3 " << xIndex << std::endl;
				checkOffset = func(((double)(xIndex-indentX-playerX)+xCheck),function,((double)(playerY+indentY))-yShift);
				if(yIndex != (int)(checkOffset) ){
					xIndex=(int)func((double)((int)(checkOffset-yShift)-indentY-playerY+yCheck),(1.00/function),((double)(indentX+playerX))-xShift);
					//std::cout << "GORE3 " << xIndex << std::endl;
					yIndex += upMode;
					//std::cout << "height diff: " << (currHeight - playerHeight) << std::endl;
					//std::cout << "x calc " << func((double)(yIndex-playerY-indentY+yCheck),(1.00/function),(double)(playerX+indentX)) << std::endl;
					//std::cout << "y calc: " << yIndex << std::endl;
					//std::cout << "x player calc: " << playerX << std::endl;
					//std::cout << "y player calc " << playerY << std::endl;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,(double)yIndex,func((double)(yIndex-playerY-indentY+yCheck),(1.00/function),(double)(playerX+indentX))); 
					// removed indents, xdiff and ydif is same anyhow, and that is used for calculating distance.
				}
				else{
					//std::cout << "GORE4 " << checkOffset << std::endl;
					//std::cout << "GORE4" << std::endl;
					currHeight = actualMap[(yIndex*length)+xIndex];
					tempAngle = (currHeight - playerHeight)/distD(playerY,playerX,checkOffset,(double)xIndex); 
					//std::cout << "height diff: " << (currHeight - playerHeight) << std::endl;
					//std::cout << "x calc " << xIndex << std::endl;
					//std::cout << "y calc: " << checkOffset << std::endl;
					//std::cout << "x player calc: " << playerX << std::endl;
					//std::cout << "y player calc " << playerY << std::endl;
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
				//std::cout << "xIndex: " << xIndex << " xTar: " << xTar << " yIndex: " << yIndex << " yTar: " << yTar << " playerY: " << playerY << " playerX: " << playerX << std::endl;
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
		if(tempAngle>=minAngle){
			viewMap[(yIndex*length)+xIndex] = true;
			minAngle=tempAngle;
		}
		//std::cout << "special: " << special << " tempAngle: " << tempAngle << " minAngle: " <<  minAngle << " maxAngle: " << maxAngle << " currHeight: " << currHeight << " checkOffset: " << checkOffset << " func: " << function << std::endl;
		//std::cout << "xIndex: " << xIndex << " xTar: " << xTar << " yIndex: " << yIndex << " yTar: " << yTar << " playerY: " << playerY << " playerX: " << playerX << std::endl;
		//std::cout << indentTarX << " " << indentTarY << " " << indentX << " " << indentY << std::endl;

	}
	//std::cout << "FIN" << std::endl;
}

int main(){
	int rX=2; // Player cords
	int rY=2;
	int length = 5;
	bool viewMap[(length*length)];
	//int dRealList[13] = 	{ 8, 9,   6,3,2, 1, 4, 7, 8, 9,6,     3,2, 1, 4};  // Adjusted for map display.
	double angleMap[length*length];
	int actualMap[] = {	1,1,1,1,1,
						1,1,1,0,1,
						1,1,1,1,1,
						1,1,1,1,1,
						1,1,1,1,1};
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
			if(!viewMap[(y*length)+x]){
				std::cout << y << " " << x << std::endl;
				viewLine(length,viewMap,actualMap,rY, rX, y, x);
				//std::cout << "GOREd" << std::endl;
			}
			//std::cout << y << " " << x << std::endl;
		}
	}
	for(int y = 0; y < length; y++)
	{
		for (int x = 0; x < length; x++)
		{
			if(viewMap[(y*length)+x]){
				std::cout << actualMap[(y*length)+x];
			}
			else{
				std::cout << " ";
			}
			
		}
		std::cout << std::endl;
	}
}