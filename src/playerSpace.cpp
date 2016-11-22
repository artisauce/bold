#include "playerSpace.hpp"
playerSpace::playerSpace(unsigned int seedInput, int playerViewRadius, const double pushInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput):
	seed(seedInput),
	push(pushInput),
	mapSide(mapSideInput),
	tileSide(tileSideInput),
	battlefieldSide(battlefieldSideInput),
	diagonal(diagonalInput),
	debug(debugInput)
{
	if(debug){
    	std::cout << "CREATING PLAYERSPACE " << this << std::endl; 
    }
	srand(seed);
	playerWorldY=0;
	playerWorldX=0;
	playerRegionY=0;
	playerRegionX=0;
	playerTileY=0;
	playerTileX=0;
    	current = new map(seed,0,0,push,mapSide,tileSide,battlefieldSide,diagonal.debug); 
	map* tempMap;
	std::cout << "PLAYERSPACE " << this << ": #" << 0 << " MAP CREATED: " << current << std::endl; 
	mapCount = 1;
	tileViewRadius = playerViewRadius;
	regionViewRadius = playerViewRadius; // For now they are the same.
	mapViewRadius = (regionViewRadius / mapSide) + 1; // How far away we generatin'? Must be >=1
	//std::list<std::list<coordinate>> cordMap
	coordinate tempCord = {0,0,current,NULL,NULL};
	tempList = std::list<coordinates>;
	for(int i = -mapViewRadius;i<=0;i++) cordMap.push_front(tempList); // This many rows for beginning.
	std::list<std::list<coordinate>>::iterator temp = cordMap.end();
	for(i = 0;i<mapViewRadius;i++) cordMap.push_front(tempList); // This many rows for beginning.
	temp*.push_front(tempCord); // Attach the first cord to middle.
	// Finally set up to start expanding.
	std::list<coordinate>::iterator middle = temp->begin();
	//http://www.cplusplus.com/reference/list/list/insert/ Val also copied.
	//http://www.cplusplus.com/reference/list/list/push_front/ Val is copied !!!
	bool isTop = 1;
	std::list<coordinate>::iterator justHappened;
	std::list<coordinate>::iterator it;
	temp = NULL;
	for(int y = -mapViewRadius;y<=mapViewRadius;y++){
		for(int x = -mapViewRadius;x<=mapViewRadius;x++){
			if(x==y && x==0) continue; // Skip current.
			tempMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal.debug);
			if(isTop)
			tempCord = {y,x,tempMap,NULL,NULL}; // Basic, just put in deh grill
			else {
				tempCord = {y,x,tempMap,&it,NULL);
				if(!y){
					if(x<0){
						justHappened = temp.insert(middle,tempCord); // insert, justHappened has pointer.
						(*it).down = &(*justHappened); // Set the one above to point down to justHappened.
					}
					else{
						temp.push_back(tempCord);
						(*it).down = &(*temp.end());
					}
				}
				else{
					temp.push_back(tempCord);
					(*it).down = &(*temp.end());
				}
			}
			if(x==mapViewRadius) break; // End case.
			it++;
			// consider just having by itself instead of &(*...)
			// consider not checking end case.
		}
		if(y==mapViewRadius){
			break;
		}
		if(temp){
			temp++;
		}
		else{
			temp=cordMap.begin();
		}
		it = temp.begin();
		isTop = 0;
		
	}
	temp=cordMap.begin();
	for (y=-mapViewRadius;y<=mapViewRadius; y++)
	{
		it = temp.begin();
		middle = temp; // This really just a temp value. -- is one ahead
		if(y!=mapViewRadius){
			temp++;
			justHappened = temp.begin(); // Temp value of stuff below. - same index as it
			temp--;
		}

		for (x=-mapViewRadius;x<=mapViewRadius; x++)
		{
			if(x!=mapViewRadius){
				middle++;
				(*it)->pointer.right = (*middle)->pointer;
				(*middle)->pointer.left = (*it)->pointer;
			}
			if(y!=mapViewRadius){
				(*it)->pointer.down = (*justHappened)->pointer;
				(*justHappened)->pointer.up = (*it)->pointer;
			}
			it=middle; // or it++;
		}
		temp++;
	}
	if(debug){
    	std::cout << "CREATED PLAYERSPACE " << this << std::endl; 
    }
}

playerSpace::insertCoordinateRelative(std::list<std::list<coordinate>>::iterator& yy, std::list<coordinate>::iterator& xx, coordinate data){
// if not found y, use mylist.insert (iterator,thingWeWantToPutIn);
	int wy = *(xx).y;
	int tarX = data.x;
	int tarY = data.y;
	bool goDir = true; //For technical insertion.
	// WARNING: WE'RE NOT KEEPING TRACK OF EX AND WY THROUGH THIS.
	if(tarY<cordList.begin()->begin()->y){ // test if y is out of range
		std::list<coordinate> tempList;
		tempList.push_front(data);
		cordList.push_front(tempList);
		yy = (cordList.begin());
		xx= cordList.begin()->begin();
		return;
	}
	else if(tarY>cordList.end()->begin()->y){
		std::list<coordinate> tempList;
		tempList.push_back(data);
		cordList.push_back(tempList);
		yy = (cordList.end());
		xx= cordList.end()->end();
		return;
	}
	bool tester;
	while(1){ // Welp.
		if(wy==tarY){
			if(tarX < *(yy.begin()).x){ // test if x is out of range
				yy.push_front(data);
				xx= yy.begin();
				return;
			}
			else if (tarX > *(yy.end()).x){
				yy.push_back(data);
				xx= yy.end();
				return;
			}
			tester = ((*xx).x < tarX);
			goDir = true;
			while(tester || goDir){ // while current is less than target and your going left
				if(tester){
					xx++;
					goDir = false;
				}
				else{
					xx--;
					goDir = true;
				}
				tester = ((*xx).x < tarX);
			}
			xx = yy.insert(xx,data);
			return;
		}
		else{
			wy=*((*yy).begin()).y;
			tester = (wy < tarY);
			while(tester || goDir){
				if(tester){
					yy++;
					goDir = false;
				}
				else{
					yy--;
					goDir = true;
				}
				wy= *((*yy).begin()).y;
				if(wy == tarY){
					break; // Go get x now.
				}
				tester = (wy < tarY);
			}
			if(wy!=tarY){ // If it wasn't found, we make a new one.
				std::list<coordinate> tempList;
				tempList.push_back(data);
				yy = cordList.insert(yy,tempList);
				xx= (*yy).begin();
				return;
			}
			xx = (*yy).end();
			if(tarX - *((*yy).begin()).x < *((*yy).end()).x - tarX){ //quick comparison for comparison's sake
				xx = (*yy).begin();
			}
		}
	}
}

bool playerSpace::find(int y, int x, std::list<std::list<coordinate>>::iterator& yy, std::list<coordinate>::iterator& xx){
	if(y < cordMap.begin()->begin()->y){
		return false;
	}
	else if(y > cordMap.end()->begin()->y){
		return false;
	}
	bool searchX=false;
	int diff = y - yy->begin()->y;
	if(diff){
		searchX=true;
	}
	while(diff){
		if(diff>0){
			yy++;
			diff = y - yy->begin()->y;
			if(diff<0){
				return false;
			}
		}
		else{
			yy--;
			diff = y - yy->begin()->y;
			if(diff>0){
				return false;
			}
		}
	}
	if(x>yy->end()->x){
		return false;
	}
	if(x<yy->begin()->x){
		return false;
	}
	if(searchX){
		xx = yy->end();
		if(x - *((*yy).begin()).x < *(xx).x - tarX){ //quick comparison for comparison's sake
			xx = (*yy).begin();
		}
	}
	diff = x - xx->x;
	while(diff){
		if(diff>0){
			xx++;
			diff = x - xx->x;
			if(diff<0){
				return false;
			}
		}
		else{
			xx--;
			diff = x - xx->x;
			if(diff>0){
				return false;
			}
		}
	}
	return true;
}

playerSpace::teleport(){
	// I'll implement later. For now, have this friendly neighborhood seg-fault
	current = NULL;
}

playerSpace::travel(int yT, int xT, int mode){
	//0: tile mode
	//1: region mode
	//2: special, map mode
	int worldXDest=playerWorldX;
	int worldYDest=playerWorldY;
	if(mode == 0){
		playerTileY+=yT;
		playerTileX+=xT;
	}
	else if(mode==1) {
		playerRegionY+=yT;
		playerRegionX+=xT;
	}
	else{
		playerWorldY+=yT;
		playerWorldX+=xT;
	}
	playerRegionY+=playerTileY/tileSide;
	playerRegionX+=playerTileX/tileSide;
	worldYDest+=playerRegionY/mapSide;
	worldXDest+=playerRegionX/mapside;
	playerTileX=playerTileX%tileSide;
	playerTileY=playerTileY%tileSide;
	playerRegionY=playerRegionY%mapSide;
	playerRegionX=playerRegionX%mapSide;
	int calcY = worldYDest-playerWorldY;
	int calcX = worldXDest-playerWorldx;
	playerWorldY=worldYDest;
	playerWorldX=worldXDest;
	if(abs(calcY) > 1 || abs(calcX) > 1){
		teleport(); // whoosh
	}
	else if(calcY || calcX) {
		// do complicated stuff here
		std::list<std::list<coordinate>>::iterator yIt = current->yConnector;
		std::list<coordinate>::iterator xIt = current->xConnector;
		std::list<coordinate>::iterator spareX;
		coordinate currCord = *xIt;
		coordinate* foundCord;
		coordinate* cordArray[(mapViewRadius*2)+1];
		cordinate* theTestCord;
		int y;
		int x;
		int startCord;
		int cordNumber = -1;
		map* madeMap; // We also makes maps here. Insert doesn't do it for reasons.
		if(calcY>0){
			for (int i = 0; i < mapViewRadius; i++){
				currCord = *(currCord.down); // GO DOWN TO DEACTIVATE
			}
			currCord.map->deactivate();
			spareX = currCord.map->xConnector;
			xIt = spareX;
			for (i = 0; i < mapViewRadius; i++)
			{
				xIt--;
				xIt->pointer->deactivate();
				spareX++;
				spareX->pointer->deactivate();
			}
			// now we set up list
			currCord = *(current->xConnector);
			for (i = 0; i < mapViewRadius; i++){
				currCord = *(currCord.up); // GO UP TO FIND/SEARCH/ACTIVATE
			}
			cordArray[mapViewRadius] = &currentCord;
			spareX = currCord.map->xConnector;
			yIt = currCord.map->yConnector;
			xIt = spareX;
			for (i = 0; i < mapViewRadius; i++)
			{
				xIt--;
				spareX++;
				cordArray[mapViewRadius-i] = &(*xIt);
				cordArray[mapViewRadius+i] = &(*spareX);
			}
			y = current->y + mapViewRadius + 1;
			startCord = current->x - mapViewRadius;
			x = startCord - 1; // keep this in place for now

			for (i = -mapViewRadius; i <= mapViewRadius; i++)
			{
				x++;
				theTestCord = cordArray[i]->up;
				if(theTestCord){
					theTestCord->pointer->activate();
					if(cordNumber != -1){
						cordNumber = i; // so we only do this once
						yIt=theTestCord->pointer->yConnector;
						xIt=theTestCord->pointer->xConnector;
					}
				}
				else if(find(y,x,yIt,xIt)){
					foundCord = &(*xIt);
					cordArray[i]->up = foundCord; //coordinates connect
					foundCord->down = cordArray[i];
					foundCord->pointer->down = cordArray[i]->pointer; // update up/down map
					cordArray[i]->pointer->up = foundCord->pointer;
					if(x!=startCord){ // left/right. left is gauranteed to be something, so...
						cordArray[i-1]->pointer->right = cordArray[i]->pointer;
						cordArray[i]->pointer->left = cordArray[i-1]->pointer;
					}
				}
				else{
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal.debug);
					currCord = {y,x,madeMap,NULL,cordArray[i]}; // We don't use this anyways anymore.
					insertCoordinateRelative(yIt,xIt,currCord);
					foundCord = &(*xIt);
					cordArray[i]->up = foundCord; //coordinates connect
					foundCord->pointer->down = cordArray[i]->pointer; // update up/down map
					cordArray[i]->pointer->up = foundCord->pointer;
					if(x!=startCord){ // left/right. left is gauranteed to be something, so...
						cordArray[i-1]->pointer->right = cordArray[i]->pointer;
						cordArray[i]->pointer->left = cordArray[i-1]->pointer;
					}
				}
				if(x!=startCord){ // left/right. left is gauranteed to be something, so...
					cordArray[i-1]->pointer->right = cordArray[i]->pointer;
					cordArray[i]->pointer->left = cordArray[i-1]->pointer;
				}
			}
			current = current->up; // we transfer over.
		}
		else{
			for (int i = 0; i < mapViewRadius; i++){
				currCord = *(currCord.up); // GO UP TO DEACTIVATE
			}
			currCord.map->deactivate();
			spareX = currCord.map->xConnector;
			xIt = spareX;
			for (i = 0; i < mapViewRadius; i++)
			{
				xIt--;
				xIt->pointer->deactivate();
				spareX++;
				spareX->pointer->deactivate();
			}
			// now we set up list
			currCord = *(current->xConnector);
			for (i = 0; i < mapViewRadius; i++){
				currCord = *(currCord.down); // GO DOWN TO FIND/SEARCH/ACTIVATE
			}
			cordArray[mapViewRadius] = &currentCord;
			spareX = currCord.map->xConnector;
			yIt = currCord.map->yConnector;
			xIt = spareX;
			for (i = 0; i < mapViewRadius; i++)
			{
				xIt--;
				spareX++;
				cordArray[mapViewRadius-i] = &(*xIt);
				cordArray[mapViewRadius+i] = &(*spareX);
			}
			y = current->y - mapViewRadius - 1;
			startCord = current->x - mapViewRadius;
			x = startCord - 1; // keep this in place for now

			for (i = -mapViewRadius; i <= mapViewRadius; i++)
			{
				x++;
				theTestCord = cordArray[i]->down;
				if(theTestCord){
					theTestCord->pointer->activate();
					if(cordNumber != -1){
						cordNumber = i; // so we only do this once
						yIt=theTestCord->pointer->yConnector;
						xIt=theTestCord->pointer->xConnector;
					}
				}
				else if(find(y,x,yIt,xIt)){
					foundCord = &(*xIt);
					cordArray[i]->down = foundCord; //coordinates connect
					foundCord->up = cordArray[i];
					foundCord->pointer->up = cordArray[i]->pointer; // update up/down map
					cordArray[i]->pointer->down = foundCord->pointer;
				}
				else{
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal.debug);
					currCord = {y,x,madeMap,cordArray[i],NULL}; // We don't use this anyways anymore.
					insertCoordinateRelative(yIt,xIt,currCord);
					foundCord = &(*xIt);
					cordArray[i]->down = foundCord; //coordinates connect
					foundCord->pointer->up = cordArray[i]->pointer; // update up/down map
					cordArray[i]->pointer->down = foundCord->pointer;
				}
				if(x!=startCord){ // left/right. left is gauranteed to be something, so...
					cordArray[i-1]->pointer->right = cordArray[i]->pointer;
					cordArray[i]->pointer->left = cordArray[i-1]->pointer;
				}
			}
			current = current->down; // we transfer over.
		}
		// do complicated stuff here
		yIt = current->yConnector;
		xIt = current->xConnector;
		currCord = *xIt;
		coordinate spareCord = currCord;
		cordNumber = -1;
		map* mapArray[(mapViewRadius*2)+1];
		madeMap = currentMap; // We'll use this as temp this time.
		map* testMap;
		if(calcX>0){
			for (int i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->left; // GO LEFT TO DEACTIVATE
			}
			madeMap->deactivate();
			spareCord = &(*(madeMap->xConnector));
			currCord = spareCord;
			for (i = 0; i < mapViewRadius; i++)
			{
				spareCord = spareCord->up;
				spareCord->pointer->deactivate();
				currCord = currCord->down;
				currCord->pointer->deactivate();
			}
			// now we set up list
			madeMap = currentMap;
			for (i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->right;  // GO RIGHT TO FIND/SEARCH/ACTIVATE
			}
			mapArray[mapViewRadius] = madeMap;
			spareCord = &(*(madeMap->xConnector));
			currCord = spareCord;
			for (i = 0; i < mapViewRadius; i++)
			{
				spareCord = spareCord->up;
				currCord = currCord->down;
				mapArray[mapViewRadius-i] = spareCord->pointer;
				mapArray[mapViewRadius+i] = currCord->pointer;
			}
			x = current->x + mapViewRadius + 1;
			startCord = current->y - mapViewRadius;
			y = startCord - 1; // keep this in place for now
			for (i = -mapViewRadius; i <= mapViewRadius; i++)
			{
				y++;
				testMap = mapArray[i]->right;
				yIt=mapArray[i]->yConnector; // Because now we're RIGHT beside it.
				xIt=mapArray[i]->xConnector;
				if(testMap){
					testMap->activate();
				}
				else if(find(y,x,yIt,xIt)){
					testMap = xIt->pointer;
					mapArray[i]->right = testMap; //coordinates connect
					testMap->left = mapArray[i];
				}
				else{
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal.debug);
					currCord = {y,x,madeMap,NULL,NULL}; // We don't use this anyways anymore.
					insertCoordinateRelative(yIt,xIt,currCord);
					testMap = xIt->pointer;
					mapArray[i]->right = testMap; //coordinates connect
					testMap->left = mapArray[i];
				}
				if(y!=startCord){ // left/right. left is gauranteed to be something, so...
					mapArray[i-1]->down = mapArray[i];
					mapArray[i]->up = mapArray[i-1]; 
					mapArray[i-1]->xConnector->down = &(*(mapArray[i]->xConnector));
					mapArray[i]->xConnector->up = &(*(mapArray[i-1]->xConnector));
				}
			}
			current = current->right; // we transfer over.
		}
		else{
			for (int i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->right; // GO LEFT TO DEACTIVATE
			}
			madeMap->deactivate();
			spareCord = &(*(madeMap->xConnector));
			currCord = spareCord;
			for (i = 0; i < mapViewRadius; i++)
			{
				spareCord = spareCord->up;
				spareCord->pointer->deactivate();
				currCord = currCord->down;
				currCord->pointer->deactivate();
			}
			// now we set up list
			madeMap = currentMap;
			for (i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->left;  // GO RIGHT TO FIND/SEARCH/ACTIVATE
			}
			mapArray[mapViewRadius] = madeMap;
			spareCord = &(*(madeMap->xConnector));
			currCord = spareCord;
			for (i = 0; i < mapViewRadius; i++)
			{
				spareCord = spareCord->up;
				currCord = currCord->down;
				mapArray[mapViewRadius-i] = spareCord->pointer;
				mapArray[mapViewRadius+i] = currCord->pointer;
			}
			x = current->x - mapViewRadius - 1;
			startCord = current->y - mapViewRadius;
			y = startCord - 1; // keep this in place for now
			for (i = -mapViewRadius; i <= mapViewRadius; i++)
			{
				y++;
				testMap = mapArray[i]->left;
				yIt=mapArray[i]->yConnector; // Because now we're RIGHT beside it.
				xIt=mapArray[i]->xConnector;
				if(testMap){
					testMap->activate();
				}
				else if(find(y,x,yIt,xIt)){
					testMap = xIt->pointer;
					mapArray[i]->left = testMap; //coordinates connect
					testMap->right = mapArray[i];
				}
				else{
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal.debug);
					currCord = {y,x,madeMap,NULL,NULL}; // We don't use this anyways anymore.
					insertCoordinateRelative(yIt,xIt,currCord);
					testMap = xIt->pointer;
					mapArray[i]->left = testMap; //coordinates connect
					testMap->right = mapArray[i];
				}
				if(y!=startCord){ // left/right. left is gauranteed to be something, so...
					mapArray[i-1]->down = mapArray[i];
					mapArray[i]->up = mapArray[i-1]; 
					mapArray[i-1]->xConnector->down = &(*(mapArray[i]->xConnector));
					mapArray[i]->xConnector->up = &(*(mapArray[i-1]->xConnector));
				}
			}
			current = current->left; // we transfer over.
		}
	}
}

playerSpace::~playerSpace(){
	if(debug){
		std::cout << "DELETING PLAYERSPACE " << this << std::endl;
	}
	delete[] seedMap;
	bigMap = std::vector<map>();
	if(debug){
		std::cout << "DONE DELETING PLAYERSPACE " << this << std::endl;
	}
}

// Precondition: You're on a valid tile.
unsigned int view(worldMap& theMap, int worldY, int worldX,  int regionY, int regionX, 
					 int tileY, int tileX, // Why int's? Because we'll want to still display even in negatives,
								// top/left/topleft from the map. Don't worry about it too much.
					int viewRadius, float heightOffset, int playerHeight, bool mapView, bool circle,
					 bool borders, bool playerSee, bool wallMode, std::vector<int>& viewMap, 
					 std::vector<int>* optimizeArray, std::vector<int>& memoryMap,int specialTiles, bool InvisibleAboveCustom, 
					 bool checkAll, bool debug){
	// why there's problems: angles, viewing from a platau, you wouldn't be able to see below, from side, you would.
	// view up: algorithm that's efficient. returns angles, compares. see notes in THE book.
	int viewTileWidth = (viewRadius*2)+1;
	int tileSide = theMap.tileSide;
	int mapSide = theMap.mapSide;
	int worldSide = theMap.worldMapSide;
	unsigned int mapRadius;
	//std::cout << "GO" << std::endl;
	if(viewRadius == 0){
		mapRadius = 0;
	}
	else{
		mapRadius = 1 + (unsigned int)(viewRadius/theMap.tileSide);
	}
	unsigned int mapWidth = (mapRadius*2)+1;
	viewMap.reserve(viewTileWidth*viewTileWidth);
	//std::cout << "GO" << std::endl;
	float centerPixelX;
	float centerPixelY;
	if(mapView){
		tileY=regionY;
		tileX=regionX;
		tileSide=mapSide;
		//This is a useful hack. coder plz
	}
	if(circle){
		centerPixelX = (float)tileX+0.5;
		centerPixelY = (float)tileY+0.5;
	}
	int wy;
	int ex;
	int worldYOffset;
	int worldXOffset;
	int regionYOffset;
	int regionXOffset;
	float A;
	float B;
	float difference;
	int halfTileWidth = (viewTileWidth/2);
	for (int y = -halfTileWidth; y <= halfTileWidth; y++)
	{
		
		for (int x = -halfTileWidth; x <= halfTileWidth; x++)
		{
			if(circle){
				A = (float)x+(float)tileX;
				B = (float)y+(float)tileY;
				if(A < tileX){
					A++;
				}
				if(B < tileY){
					B++;
				}
				B = B - centerPixelY; // Rogue bug: Found out these were swapped.
				A = A - centerPixelX; // See? Takes hours just to finds these...
				difference = (A*A)+(B*B);
				if(difference > (viewRadius*viewRadius)){
					//std::cout << "G" << std::endl;
					memoryMap.push_back(0);
					viewMap.push_back(-3);
					continue;
					//std::cout << "GO" << std::endl;
				}
			}
			if(borders){
				if( ((y+tileY)%tileSide) == 0 || ((x+tileX)%tileSide) == 0){
					memoryMap.push_back(0);
					viewMap.push_back(-3);
					continue;
				}
			}
			wy = y+tileY; // Relative positions, we need these
			ex = x+tileX;
			regionYOffset = 0;
			regionXOffset = 0;
			worldYOffset = 0;
			worldXOffset = 0;
			if(mapView){
				if(wy<0){
					worldYOffset = (wy-mapSide)/mapSide; // We determine how many worldspaces to left
				}
				else{
					worldYOffset = wy/mapSide; // We determine how many worldspaces to right
				}
				wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
				if(wy == mapSide){
					wy = 0;
					worldYOffset++;
				}
				if(ex<0){
					worldXOffset = (ex-mapSide)/mapSide;
				}/////
				else{
					worldXOffset = ex/mapSide;
				}
				ex -=(worldXOffset*mapSide);
				if(ex == mapSide){
					ex = 0;
					worldXOffset++;
				}
				worldYOffset+=worldY;
				worldXOffset+=worldX;
				if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
					//std::cout << "WATER" << std::endl;
					memoryMap.push_back(0);
					viewMap.push_back(0);
					continue;
				}
				//std::cout << theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex] << std::endl;
				viewMap.push_back(theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex]);
				memoryMap.push_back(theMap.bigMap[worldYOffset * worldSide + worldXOffset].regionMemoryMap[(wy*tileSide)+ex]);
				continue;
			}
			else{
				if(wy<0){
					regionYOffset = (wy-tileSide)/tileSide;
				}
				else{
					regionYOffset = wy/tileSide;
				}
				wy-=(regionYOffset*tileSide);
				if(wy == tileSide){
					wy = 0;
					regionYOffset++;
				}
				if(ex<0){
					regionXOffset = (ex-tileSide)/tileSide;
				}
				else{
					regionXOffset = ex/tileSide;
				}
				ex -=(regionXOffset*tileSide);
				if(ex == tileSide){
					ex = 0;
					regionXOffset++;
				}
				regionYOffset+=regionY;
				regionXOffset+=regionX; // get the regions
				if(regionYOffset<0){
						worldYOffset = (regionYOffset-mapSide)/mapSide; // We determine how many worldspaces to left
					}
					else{
						worldYOffset = regionYOffset/mapSide; // We determine how many worldspaces to right
					}
					regionYOffset-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
					if(regionYOffset == mapSide){
						regionYOffset = 0;
						worldYOffset++;
					}
					if(regionXOffset<0){
						worldXOffset = (regionXOffset-mapSide)/mapSide;
					}/////
					else{
						worldXOffset = regionXOffset/mapSide;
					}
					regionXOffset -=(worldXOffset*mapSide);
					if(regionXOffset == mapSide){
						regionXOffset = 0;
						worldXOffset++;
					}
					worldYOffset+=worldY;
					worldXOffset+=worldX;
					if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
						memoryMap.push_back(0);
						viewMap.push_back(0);
						continue;
					}
					viewMap.push_back(theMap.bigMap[worldYOffset*worldSide + worldXOffset].regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]);
					memoryMap.push_back(theMap.bigMap[worldYOffset*worldSide + worldXOffset].regionMap[(regionYOffset*mapSide) + regionXOffset].tileMemoryMap[(wy*tileSide)+ex]);
			}
			//if(theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] > 9){
				//std::cout << theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] << std::endl;
				//std::cout << "---- SIDE: " << tileSide << " X: " << x << " Y: " << y << " EX: "<< ex << " WY: " << wy << std::endl;
			//}
		}
	}
	//for (int j = 0; j < viewTileWidth*viewTileWidth; j++)
	//{
	//	if (j%viewTileWidth == 0) std::cout<<std::endl;
	//	std::cout << memoryMap[j];
	//}
	//std::cout<<std::endl;
	int boolMap[viewTileWidth*viewTileWidth];
	if(wallMode && !borders){ // for the time being, it's incompatible with borders
		for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
		{
			boolMap[i] = 0;
		}
		boolMap[(halfTileWidth*viewTileWidth)+halfTileWidth] = 1;
		for(int a = 0; a < viewTileWidth; a++)
		{
			// Getting most of them with this is a good, efficient idea and method.
			//std::cout << "FIRST " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, a, 0,debug);
			//std::cout << "SECOND " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, a, viewTileWidth-1,debug);
			//std::cout << "THIRD " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, 0, a,debug);
			//std::cout << "FOURTH " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth, playerHeight,viewTileWidth-1, a,debug);
		}
		//std::cout << "----END AROUND----" << std::endl;
		for(int y = 1; y < viewTileWidth-1; y++)
		{
			for (int x = 1; x < viewTileWidth-1; x++)
			{
				if(boolMap[(y*viewTileWidth)+x] != 1 || checkAll){ // This will save a function call, more efficient than in viewLine function check.
					viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, y, x,debug);
				}
				//std::cout << y << " " << x << std::endl;
			}
		}
		if(InvisibleAboveCustom){ // More efficient than detecting every for loop.
			for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
			{
				//std::cout << boolMap[i] << std::endl;
				if(viewMap[i] != -3){
					if(boolMap[i] == 0){ // Time to implement
							viewMap[i] = -1;
					}
					else if(boolMap[i] == -1){ // Above ground cannot see
							viewMap[i] = -2;
					}
				}
			}
		}

		else {
			for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
			{
				if(boolMap[i] != 1 && viewMap[i] != -3){ // Time to implement
						viewMap[i] = -1;
				}
			}
		}
	}
	if(memoryMap.size()){ // We now apply all new found
		int wyB;
		int exB;// For skipping calculations.
		int indexB;
		int getView;
		bool trigger;
		for (int y = -halfTileWidth; y <= halfTileWidth; y++)
			{
				for (int x = -halfTileWidth; x <= halfTileWidth; x++)
				{
					trigger = false;
					wyB=y+halfTileWidth;
					exB=x+halfTileWidth;
					indexB = (wyB*viewTileWidth) + exB;
					getView = viewMap[indexB];
					if((getView == -1 || getView == -2) && memoryMap[indexB] == 1){
						trigger=true; // So we have shaded out tiles.
					}
					else if(memoryMap[indexB] != 2){
						memoryMap[indexB] = 0;
						continue; // Skip already found.
					}
					wy = y+tileY; // Relative positions, we need these
					ex = x+tileX;
					regionYOffset = 0;
					regionXOffset = 0;
					worldYOffset = 0;
					worldXOffset = 0;
					if(mapView){
							if(wy<0){
								worldYOffset = (wy-mapSide)/mapSide; // We determine how many worldspaces to left
							}
							else{
								worldYOffset = wy/mapSide; // We determine how many worldspaces to right
							}
							wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							if(wy == mapSide){
								wy = 0;
								worldYOffset++;
							}
							if(ex<0){
								worldXOffset = (ex-mapSide)/mapSide;
							}/////
							else{
								worldXOffset = ex/mapSide;
							}
							ex -=(worldXOffset*mapSide);
							if(ex == mapSide){
								ex = 0;
								worldXOffset++;
							}
							worldYOffset+=worldY;
							worldXOffset+=worldX;
							if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
								continue; // Skip OOB
							}
							//std::cout << theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex] << std::endl;
							theMap.bigMap[worldYOffset * worldSide + worldXOffset].regionMemoryMap[(wy*tileSide)+ex] = 1;
							//std::cout << "GI HERE " << theMap.bigMap[worldYOffset * worldSide + worldXOffset].regionMemoryMap[(wy*tileSide)+ex]<< std::endl;
							if(trigger){
								memoryMap[indexB] = theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex]+1;
								continue;
							}
							memoryMap[indexB] = 0;
							continue;
					}
					else{
							if(wy<0){
								regionYOffset = (wy-tileSide)/tileSide;
							}
							else{
								regionYOffset = wy/tileSide;
							}
							wy-=(regionYOffset*tileSide);
							if(wy == tileSide){
								wy = 0;
								regionYOffset++;
							}
							if(ex<0){
								regionXOffset = (ex-tileSide)/tileSide;
							}
							else{
								regionXOffset = ex/tileSide;
							}
							ex -=(regionXOffset*tileSide);
							if(ex == tileSide){
								ex = 0;
								regionXOffset++;
							}
							regionYOffset+=regionY;
							regionXOffset+=regionX; // get the regions
							if(regionYOffset<0){
								worldYOffset = (regionYOffset-mapSide)/mapSide; // We determine how many worldspaces to left
							}
							else{
								worldYOffset = regionYOffset/mapSide; // We determine how many worldspaces to right
							}
							regionYOffset-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							if(regionYOffset == mapSide){
								regionYOffset = 0;
								worldYOffset++;
							}
							if(regionXOffset<0){
								worldXOffset = (regionXOffset-mapSide)/mapSide;
							}/////
							else{
								worldXOffset = regionXOffset/mapSide;
							}
							regionXOffset -=(worldXOffset*mapSide);
							if(regionXOffset == mapSide){
								regionXOffset = 0;
								worldXOffset++;
							}
							worldYOffset+=worldY;
							worldXOffset+=worldX;
							if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
								continue; // Skip OOB
							}
							theMap.bigMap[worldYOffset*worldSide + worldXOffset].regionMap[(regionYOffset*mapSide) + regionXOffset].tileMemoryMap[(wy*tileSide)+ex] = 1;
							if(trigger){
								memoryMap[indexB] = theMap.bigMap[worldYOffset*worldSide + worldXOffset].regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]+1;
								continue;
							}
							memoryMap[indexB] = 0;
							continue;
					}
				}
						//if(theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] > 9){
							//std::cout << theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] << std::endl;
							//std::cout << "---- SIDE: " << tileSide << " X: " << x << " Y: " << y << " EX: "<< ex << " WY: " << wy << std::endl;
						//}
			}
	}
	if(optimizeArray != NULL){
		int lastX;
		int firstX;
		if (memoryMap.size()){
			for(int y = 0; y < viewTileWidth; y++)
			{
				lastX = 0;
				firstX = -1;
				for (int x = 0; x < viewTileWidth; x++)
				{
					if(boolMap[(y*viewTileWidth)+x] != 0 || memoryMap[(y*viewTileWidth)+x]){ // Because we also want to see, in the case, custom invisible tiles.
						lastX = x;
						if(firstX==-1){
							firstX = x;
						}
					}
				}
				if(firstX==-1){
					firstX = 0; // No found, firstX should = lastX
				}
				if(lastX!=viewTileWidth && lastX != viewTileWidth-1){
					viewMap[(y*viewTileWidth)+lastX+1] = -4; // We detect last of X from the array itself.
				}
				//std::cout << firstX << " " << lastX << std::endl;
				optimizeArray->push_back(firstX); // We get the first x at the start of each Y.
			}
		}
		else{
			for(int y = 0; y < viewTileWidth; y++)
			{
				lastX = 0;
				firstX = -1;
				for (int x = 0; x < viewTileWidth; x++)
				{
					if(boolMap[(y*viewTileWidth)+x] != 0){ // Because we also want to see, in the case, custom invisible tiles.
						lastX = x;
						if(firstX==-1){
							firstX = x;
						}
					}
				}
				if(firstX==-1){
					firstX = 0; // No found, firstX should = lastX
				}
				if(lastX!=viewTileWidth && lastX != viewTileWidth-1){
					viewMap[(y*viewTileWidth)+lastX+1] = -4; // We detect last of X from the array itself.
				}
				//std::cout << firstX << " " << lastX << std::endl;
				optimizeArray->push_back(firstX); // We get the first x at the start of each Y.
			}
		}
	}
	if(playerSee){
		viewMap[(halfTileWidth*viewTileWidth)+halfTileWidth] = (-specialTiles)-1;
	}
	return viewTileWidth;
}
