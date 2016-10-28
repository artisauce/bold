#include "toolkit.hpp"
# define M_PI           3.14159265358979323846  /* lol it's pi */

// TOOL FUNCTIONS
double dist(int startY, int startX, int endY, int endX){
    // Remember to rate the code, comment the code, and subscribe if you want to see code similar to this one.
    double dx = ((double)endX-(double)startX);
    double dy = ((double)endY-(double)startY);
    return(sqrt(dx*dx + dy*dy));
}

double distD(int startY, int startX, double endY, double endX){
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

void viewLine(int length, bool* viewMap, bool VIEWMODE, std::vector<int>& actualMap, 
    int playerY, int playerX, int yTar, int xTar){
    if(playerY == yTar && playerX == xTar){
        return;
    }
    if(viewMap[(yTar*length)+xTar]){
        return;
    }
    //for(int y = 0; y < length; y++)
    //{
    //    for (int x = 0; x < length; x++)
    //    {
    //        std::cout << actualMap[(y*length)+x];
    //        
    //    }
    //    std::cout << std::endl;
    //}
    //std::cout << "GORE2" << std::endl;
    // This algorithm is not meant for 100% certainty. 
    double playerHeight = actualMap[(playerY*length)+playerX];
    //std::cout << playerHeight << std::endl;
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
    if(VIEWMODE){
    playerHeight+=0.5;
    }
    while(xIndex != xTar || yIndex  != yTar){
        // determine direction
        //std::cout << "GORE" << std::endl;
        if(special==0){
            if(goUp){ // dealing with y as input
                yIndex+=upMode;
                checkOffset = func(((double)(yIndex-indentY-playerY))+yCheck,function,((double)(playerX+indentX))-xShift);
                //std::cout << "GORED " << checkOffset << " " <<yCheck <<  " " << xShift <<  " " << xCheck<< std::endl;
                //std::cout <<  "GORED2 " << yIndex << 
                //              " " << ((double)(yIndex-indentY-playerY)) <<  
                //              " " << ((double)(yIndex-indentY-playerY))+yCheck <<  
                //              " " << ((double)(playerX+indentX))-xShift<< std::endl;
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
        if(currHeight==-1){
            break; // This is to save time for the real thing.
        }
        //std::cout << indentTarX << " " << indentTarY << " " << indentX << " " << indentY << std::endl;

    }
    //std::cout << "FIN" << std::endl;
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

void printMap(int* map, unsigned int side, std::vector<std::string>& tileSet){
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
           std::cout << std::endl;
        }
        if(map[i] < 0){
            if(map[i] == -1){
                std::cout << " "; // -1 is always blank.
            }
		else if(map[i] == -2){
			i = (((int)(i/side))*side)+(side-1);
		}
            else{
                //std::cout << abs(map[i])-2 << std::endl;
                std::cout << tileSet[abs(map[i])-3]; // Tilesets
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

void printMapVector(std::vector<int>& map, unsigned int side, std::vector<std::string>& tileSet){
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
            else if(map[i] == -2){
            i = (((int)(i/side))*side)+(side-1);
        }
            else{
                output+=tileSet[abs(map[i])-3]; // Tilesets
            }
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
