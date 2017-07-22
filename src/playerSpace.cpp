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
	flyMode = 0;
	cordMap = {};
    	current = new map(seed,0,0,push,mapSide,tileSide,battlefieldSide,diagonal,debug); 
	map* tempMap;
	if(debug)
	std::cout << "PLAYERSPACE " << this << ": #" << 0 << " MAP CREATED: " << current << std::endl; 
	mapCount = 0;
	tileViewRadius = playerViewRadius;
	regionViewRadius = playerViewRadius; // For now they are the same.
	mapViewRadius = (regionViewRadius / mapSide) + 1; // How far away we generatin'? Must be >=1
	std::list<map*> tempList = {}; // DEALLOC PER EACH WITHIN CORDMAP
	for(int i = -mapViewRadius;i<=0;i++) {
		cordMap.push_back(tempList); // This many rows for beginning.
	}
	std::prev(cordMap.end())->push_back(current);
	std::list<map*>::iterator middle = std::prev(cordMap.end())->begin();
	for(int i = 0;i<mapViewRadius;i++) {
		cordMap.push_back(tempList); // This many rows for beginning.
	}
	//LEARN FROM MY MISTAKES LESSION 20: .end() is an iterator to an element past the LAST IN THE LIST!!!
	// Finally set up to start expanding.
	//http://www.cplusplus.com/reference/list/list/insert/ Val also copied.
	//http://www.cplusplus.com/reference/list/list/push_front/ Val is copied !!!
	bool isTop = 1;
	std::list<map*>::iterator justHappened;
	std::list<map*>::iterator it;
	std::list<std::list<map*> >::iterator temp = cordMap.begin();
	std::list<std::list<map*> >::iterator before;
	bool isSide;
	for(int y = -mapViewRadius;y<=mapViewRadius;y++){
		before = std::prev(temp); // even if temp is first, will not bring error--it's all gud
		it = before->begin();
		isSide = false;
		for(int x = -mapViewRadius;x<=mapViewRadius;x++){
			if(x==y && x==0) {
				current->xConnector = std::prev(temp->end());
				current->yConnector = temp;
				current->up = *(it);
				(*it)->down = current;
				current->left = (*std::prev(it))->down; // work with the tools you have!
				(*std::prev(it))->down->right = current;
				it++;
				continue; // Skip current.
			}
			tempMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
			if(debug) 
				std::cout << "PLAYERSPACE " << this << ": #" << (++mapCount) << " MAP CREATED: " << tempMap << std::endl; 
			if(isTop){
				temp->push_back(tempMap);
				(*std::prev(temp->end()))->xConnector = std::prev(temp->end());
				(*std::prev(temp->end()))->yConnector = temp;
				if(isSide){
					(*std::prev(temp->end()))->left = *(std::prev(std::prev(temp->end())));
					( *std::prev( std::prev( temp->end() ) ) )->right = *(std::prev(temp->end()));
				}
			}
			else {
				if(!y){ // if middle row
					if(x<0){
						justHappened = temp->insert(middle,tempMap); // insert, justHappened has pointer.
						(*justHappened)->xConnector = justHappened;
						(*justHappened)->yConnector = temp;
						(*it)->down = (*justHappened); // Set the one above to point down to justHappened.
						(*justHappened)->up = (*it);
						if(isSide){
							(*justHappened)->left = (*std::prev(it))->down;
							(*std::prev(it))->down->right = (*justHappened);
						}
					}
					else{
						temp->push_back(tempMap);
						(*std::prev(temp->end()))->xConnector = std::prev(temp->end());
						(*std::prev(temp->end()))->yConnector = temp;
						(*it)->down = *(std::prev(temp->end()));
						(*(std::prev(temp->end())))->up = (*it);
						(*std::prev(temp->end()))->left = (*std::prev(it))->down;
						(*std::prev(it))->down->right = *(std::prev(temp->end()));
					}
				}
				else{
					temp->push_back(tempMap);
					(*std::prev(temp->end()))->xConnector = std::prev(temp->end());
					(*std::prev(temp->end()))->yConnector = temp;
					(*it)->down = *(std::prev(temp->end()));
					(*(std::prev(temp->end())))->up = (*it);
					if(isSide){
						(*std::prev(temp->end()))->left = (*std::prev(it))->down;
						(*std::prev(it))->down->right = *(std::prev(temp->end()));
					}
				}
				it++;
			}
			isSide = true;
			if(x==mapViewRadius) break; // End case.
		}
		if(y==mapViewRadius){
			break;
		}
		temp++;
		isTop = 0;		
	}
	/*
	temp=cordMap.begin();
	it=temp->begin();
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector)) << " " << (*it)->up << " " << (*it)->down << " " << (*it)->left << " " << (*it)->right <<  std::endl;
	it++;
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  <<" " << (*it)->up << " " << (*it)->down << " " << (*it)->left << " " << (*it)->right <<std::endl;
	it++;
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  << " " << (*it)->up << " " << (*it)->down << " " << (*it)->left << " " << (*it)->right <<std::endl;
	temp++;
	it=temp->begin();
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  <<" " << (*it)->up << " " << (*it)->down <<" " << (*it)->left << " " << (*it)->right << std::endl;
	it++;
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  <<" " << (*it)->up << " " << (*it)->down << " " << (*it)->left << " " << (*it)->right <<std::endl;
	it++;
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector)) <<" " << (*it)->up << " " << (*it)->down << " " << (*it)->left << " " << (*it)->right <<std::endl;
	temp++;
	it=temp->begin();
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  << " " << (*it)->up << " " << (*it)->down <<" " << (*it)->left << " " << (*it)->right << std::endl;
	it++;
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  <<" " << (*it)->up << " " << (*it)->down <<" " << (*it)->left << " " << (*it)->right << std::endl;
	it++;
	std::cout << "CHECKZa " << (*it)->y << " " << (*it)->x << " " << (*it) << " " << (*((*it)->xConnector))  << " " << (*it)->up << " " << (*it)->down << " " << (*it)->left << " " << (*it)->right <<std::endl;
	temp++;
	*/

	if(debug)
    	std::cout << "CREATED PLAYERSPACE " << this << std::endl; 
	if(current->activated == 2){
		playerZ = 0;
	}
	else{
		playerZ = current->regionMap[playerRegionY*mapSide + playerRegionX].tileMap[playerTileY*tileSide + playerTileX];
	}
    
}
// Another function will connect the directions later for this insertion.
void playerSpace::insertCoordinateRelative(std::list<std::list<map*>>::iterator& yy, std::list<map*>::iterator& xx, map* data){
// if not found y, use mylist.insert (iterator,thingWeWantToPutIn);
	int wy = (*xx)->y;
	int tarX = data->x;
	int tarY = data->y;
	bool goDir = true; //For technical insertion.
	// WARNING: WE'RE NOT KEEPING TRACK OF EX THROUGH THIS.
	if(tarY< (*cordMap.begin()->begin())->y){ // test if y is out of range
		std::list<map*> tempList;
		tempList.push_front(data);
		cordMap.push_front(tempList);
		yy = (cordMap.begin());
		xx= cordMap.begin()->begin();
		return;
	}
	else if(tarY>(*std::prev(cordMap.end())->begin())->y){
		std::list<map*> tempList;
		tempList.push_back(data);
		cordMap.push_back(tempList);
		yy = std::prev(cordMap.end());
		xx= std::prev(cordMap.end())->begin();
		return;
	}
	bool tester;
	while(1){ // Welp.
		if(wy==tarY){
			if(tarX < (*yy->begin())->x){ // test if x is out of range
				yy->push_front(data);
				xx= yy->begin();
				return;
			}
			else if (tarX > (*std::prev(yy->end()))->x){
				yy->push_back(data);
				xx= std::prev(yy->end());
				return;
			}
			tester = ((*xx)->x < tarX);
			goDir = true;
			while(tester || goDir){ // while current is less than target or your going left
				if(tester){
					xx++;
					goDir = false;
				}
				else{
					xx--;
					goDir = true;
				}
				tester = ((*xx)->x < tarX);
			}
			xx = yy->insert(xx,data);
			return;
		}
		else{
			wy=(*yy->begin())->y;
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
				wy= (*yy->begin())->y;
				if(wy == tarY){
					break; // Go get x now.
				}
				tester = (wy < tarY);
			}
			if(wy!=tarY){ // If it wasn't found, we make a new one.
				std::list<map*> tempList;
				tempList.push_back(data);
				yy = cordMap.insert(yy,tempList);
				xx= yy->begin();
				return;
			}
			xx = std::prev((*yy).end());
			if(tarX - (*yy->begin())->x < (*prev(yy->end()))->x - tarX){ //quick comparison for comparison's sake
				xx = yy->begin();
			}
		}
	}
}

bool playerSpace::find(int y, int x, std::list<std::list<map*>>::iterator& yy, std::list<map*>::iterator& xx){
	if(y < (*cordMap.begin()->begin())->y){
		return false;
	}
	else if(y > (*std::prev(cordMap.end())->begin())->y){
		return false;
	}
	bool searchX=false;
	int diff = y - (*yy->begin())->y;
	if(diff){
		searchX=true;
	}
	//How about we try using the up/down of maps to our advantage?
	//A: Well, REMEMBER: We use this func if there's no passage up in the first place.
	//std::cout << "AH no" << std::endl;
	while(diff){
		if(diff>0){
			yy++;
			diff = y - (*yy->begin())->y;
			if(diff<0){
				return false;
			}
		}
		else{
			yy--;
			diff = y - (*yy->begin())->y;
			if(diff>0){
				return false;
			}
		}
	}
	//std::cout << "AH no3" << std::endl;
	if(x>(*std::prev((yy->end())))->x){
		return false;
	}
	if(x<(*(yy->begin()))->x){
		return false;
	}
	if(searchX){
		xx = std::prev(yy->end());
		if(x - (*yy->begin())->x < (*xx)->x - x){ //quick comparison for comparison's sake
			xx = yy->begin();
		}
	}
	diff = x - (*xx)->x;
	//std::cout << "AH no2" << std::endl;
	while(diff){
		if(diff>0){
			xx++;
			diff = x - (*xx)->x;
			if(diff<0){
				return false;
			}
		}
		else{
			xx--;
			diff = x - (*xx)->x;
			if(diff>0){
				return false;
			}
		}
	}
	return true;
}
// Lots of short-circuiting here.
map* playerSpace::gotoMapX(map* currMap, bool goRight){
	std::list<std::list<map*>>::iterator yIt = currMap->yConnector;
	std::list<map*>::iterator xIt = currMap->xConnector;
	if(goRight){
		if(!(currMap->right) || (currMap->right)->activate()){
			int ex = currMap->x+1;
			int wy = currMap->y;
			if(!find(wy,ex,yIt,xIt) || (*xIt)->activate()){
				map* tempMap = new map(seed,wy,ex,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
				insertCoordinateRelative(yIt,xIt,tempMap);
				(*xIt)->xConnector = xIt;
				(*xIt)->yConnector = yIt;
			}
			currMap->right = *xIt;
			(*xIt)->left = currMap;
		}
		return currMap->right;
	}
	else {
		if(!(currMap->left) || (currMap->left)->activate()){
			int ex = currMap->x-1;
			int wy = currMap->y;
			if(!find(wy,ex,yIt,xIt) || (*xIt)->activate()){ // short circuit ftw
				map* tempMap = new map(seed,wy,ex,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
				insertCoordinateRelative(yIt,xIt,tempMap);
				(*xIt)->xConnector = xIt;
				(*xIt)->yConnector = yIt;
			}
			currMap->left = *xIt;
			(*xIt)->right = currMap;
		}
		return currMap->left;
	}
}

map* playerSpace::gotoMapY(map* currMap, bool goDown, std::list<std::list<map*>>::iterator yIt, std::list<map*>::iterator xIt){
	// iterator in arguments are there to help
	if(goDown){
		if(!(currMap->down) || (currMap->down)->activate()){
			int ex = currMap->x;
			int wy = currMap->y+1;
			if(!find(wy,ex,yIt,xIt) || (*xIt)->activate()){
				map* tempMap = new map(seed,wy,ex,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
				insertCoordinateRelative(yIt,xIt,tempMap);
				(*xIt)->xConnector = xIt;
				(*xIt)->yConnector = yIt;
			}
			currMap->down = *xIt;
			(*xIt)->up = currMap;
		}
		return currMap->down;
	}
	else{
		if(!(currMap->up) || (currMap->up)->activate()){
			int ex = currMap->x;
			int wy = currMap->y-1;
			if(!find(wy,ex,yIt,xIt) || (*xIt)->activate()){
				map* tempMap = new map(seed,wy,ex,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
				insertCoordinateRelative(yIt,xIt,tempMap);
				(*xIt)->xConnector = xIt;
				(*xIt)->yConnector = yIt;
			}
			currMap->up = *xIt;
			(*xIt)->down = currMap;
		}
		return currMap->up;
	}
}


void playerSpace::adjustView(){
	int holder = (regionViewRadius / mapSide) + 1;
	//std::cout << "HOLDER: " << holder << std::endl;
	if(holder > mapViewRadius){
		map* currMap=current;
		map* currMapB=currMap;
		for (int i = 0; i < mapViewRadius; i++)
		{
			currMap=currMap->up->left;
			currMapB=currMapB->down->right;
		}
		currMap = gotoMapX(gotoMapY(currMap,false,currMap->yConnector,currMap->xConnector),false); // lol
		currMapB = gotoMapX(gotoMapY(currMapB,true,currMapB->yConnector,currMapB->xConnector),true);
		//std::cout << "Gottem 1" << std::endl;
		map* holdMap = currMap;
		map* holdMapB = currMapB;
		currMap = currMap->right;
		currMapB = currMapB->left;
		map* spareMap = currMap->down;
		map* spareMapB = currMapB->up;
		int tempHolder = (mapViewRadius+1)*2 -1; // to include middle
		//std::cout << "Gottem 2" << std::endl;
		for (int i = 0; i < tempHolder; i++)
		{
			currMap = gotoMapX(currMap,true);
			currMapB = gotoMapX(currMapB,false);
			//std::cout << "Gottemb " << i <<  std::endl;
			if(i!=tempHolder-1){
				//std::cout << "Gotteme " << i << " " << spareMap->right << " " << spareMapB->left << std::endl;
				spareMap=spareMap->right;
				spareMapB=spareMapB->left;
				//std::cout << "Gottemc " << i <<  std::endl;
				currMap->down = spareMap;
				spareMap->up = currMap;
				//std::cout << "Gottemd " << i <<  std::endl;
				currMapB->up = spareMapB;
				spareMapB->down = currMapB;
			}
		}
		//std::cout << "Gottem 3" << std::endl;
		for (int i = 0; i < tempHolder; i++)
		{
			if(i!=0){
				spareMap=spareMap->down;
				spareMapB=spareMapB->up;
			}
			currMap = gotoMapY(currMap,true,spareMap->yConnector,spareMap->xConnector);
			currMapB = gotoMapY(currMapB,false,spareMapB->yConnector,spareMapB->xConnector);
			currMap->left = spareMap;
			spareMap->right = currMap;
			currMapB->right = spareMapB;
			spareMapB->left = currMapB;
		}
		holdMap->down = currMapB; // complete circuit
		currMapB->up = holdMap;
		holdMapB->up = currMap;
		currMap->down = holdMapB;
		mapViewRadius++;
		if(holder>mapViewRadius){
			adjustView();
			return;
		}
	}
	else if(holder != mapViewRadius){
		//deactivate in swastika
		map* currMapA=current;
		map* currMapB=current;
		map* currMapC=current;
		map* currMapD=current;
		for (int i = 0; i < mapViewRadius; i++){
			currMapA = currMapA->down; // GO DOWN TO DEACTIVATE
			currMapB = currMapB->left; // GO LEFT TO DEACTIVATE
			currMapC = currMapC->up; // GO UP TO DEACTIVATE
			currMapD = currMapD->right; // GO RIGHT TO DEACTIVATE
		}
		currMapA->deactivate();
		currMapB->deactivate();
		currMapC->deactivate();
		currMapD->deactivate();
		for (int i = 0; i < mapViewRadius; i++)
		{
			currMapA = currMapA->right;
			currMapB = currMapB->down; 
			currMapC = currMapC->left; 
			currMapD = currMapD->up; 
			currMapA->deactivate();
			currMapB->deactivate();
			currMapC->deactivate();
			currMapD->deactivate();
		}
		for (int i = 0; i < mapViewRadius-1; i++)
		{
			currMapA = currMapA->up;
			currMapB = currMapB->right; 
			currMapC = currMapC->down; 
			currMapD = currMapD->left; 
			currMapA->deactivate();
			currMapB->deactivate();
			currMapC->deactivate();
			currMapD->deactivate();
		}
		mapViewRadius--;
		if(holder<mapViewRadius){
			adjustView();
			return;
		}
	}
}

void playerSpace::teleport(){
	current->deactivate();
	map* deLeft = current;
	map* deRight = current;
	map* deUp = current;
	map* deDown = current;
	for (int i = 0; i < mapViewRadius; i++)
	{
		deUp=deUp->up;
		deDown=deDown->down;
		deUp->deactivate();
		deDown->deactivate();
	}
	for (int i = 0; i < mapViewRadius; i++)
	{
		deLeft=deLeft->left;
		deLeft->deactivate();
		deUp = deLeft;
		deDown = deLeft;
		for(int e = 0; e < mapViewRadius; e++){
			deUp=deUp->up;
			deDown=deDown->down;
			deUp->deactivate();
			deDown->deactivate();
		}
		deRight=deRight->right;
		deRight->deactivate();
		deUp = deRight;
		deDown = deRight;
		for(int e = 0; e < mapViewRadius; e++){
			deUp=deUp->up;
			deDown=deDown->down;
			deUp->deactivate();
			deDown->deactivate();
		}
	}
	//deactivated all -- likely
	//now to make where we will be.
	std::list<std::list<map*>>::iterator yIt = current->yConnector;
	std::list<map*>::iterator xIt = current->xConnector;
	int y = playerWorldY;
	int x = playerWorldX;
	map* tempMap;
	if(!find(y,x,yIt,xIt) || (*xIt)->activate()){ // Short circuit
		tempMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
		insertCoordinateRelative(yIt,xIt,tempMap);
	}
	current = (*xIt);
	current->xConnector = xIt;
	current->yConnector = yIt;
	deLeft = current;
	deRight = current;
	mapViewRadius = (regionViewRadius / mapSide) + 1;
	for(int i = 0;i<mapViewRadius;i++){
		deRight = gotoMapX(deRight,true);
		deLeft = gotoMapX(deLeft,false);
	}
	map* connectMap;
	deUp=deLeft; // re-use these variables. they still kinda make sense here
	deDown=deLeft;
	int holder = mapViewRadius*2;
	for(int i = 0;i<mapViewRadius;i++){ // Consider: Maybe use this as initial construction for maps?
		connectMap = deUp;
		deUp = gotoMapY(deUp,false,deUp->yConnector,deUp->xConnector);
		deRight = deUp;
		for(int e = 0; e < holder; e++){
			deRight=gotoMapX(deRight,true);
			connectMap=connectMap->right;
			connectMap->up=deRight;
			deRight->down = connectMap;
		}
		connectMap = deDown;
		deDown = gotoMapY(deDown,true,deDown->yConnector,deDown->xConnector);
		deRight = deDown;
		for(int e = 0; e < holder; e++){
			deRight=gotoMapX(deRight,true);
			connectMap=connectMap->right;
			connectMap->down=deRight;
			deRight->up = connectMap;
		}
	}
	
	
}

void playerSpace::travel(int yT, int xT, int mode){
	if(yT != xT || xT != 0){ // Else, we just update height.
		//0: tile mode
		//1: region mode
		//2: special, map mode
		int worldXDest=playerWorldX;
		int worldYDest=playerWorldY;
		int regionYOffset;
		int regionXOffset;
		int worldYOffset;
		int worldXOffset;
		if(mode == 0){
			playerTileY+=yT;
			playerTileX+=xT;
		}
		else if(mode==1) {
			playerRegionY+=yT;
			playerRegionX+=xT;
		}
		else if(mode==2){
			worldYDest+=yT;
			worldXDest+=xT;
		}
		if(playerTileY<0){
			regionYOffset=((playerTileY+1)/tileSide) - 1;
			playerTileY-=(regionYOffset*tileSide);
			playerRegionY+=regionYOffset;
		}
		else if(playerTileY>=tileSide){
			playerRegionY+=playerTileY/tileSide;
			playerTileY=playerTileY%tileSide;
		}
		if(playerTileX<0){
			regionXOffset=((playerTileX+1)/tileSide) - 1;
			playerTileX-=(regionXOffset*tileSide);
			playerRegionX+=regionXOffset;
		}
		else if(playerTileX>=tileSide){
			playerRegionX+=playerTileX/tileSide;
			playerTileX=playerTileX%tileSide;
		}
		//std::cout << "ALER1: " << playerRegionY << std::endl;
		if(playerRegionY<0){
			worldYDest+=((playerRegionY+1)/mapSide) - 1;
			playerRegionY-=((worldYDest-playerWorldY)*mapSide);
		}
		else if(playerRegionY>=mapSide){
			worldYDest+=playerRegionY/mapSide;
			playerRegionY=playerRegionY%mapSide;
		}
		//worldYDest+=playerRegionY/mapSide;
		if(playerRegionX<0){
			worldXDest+=((playerRegionX+1)/mapSide) - 1;
			playerRegionX-=((worldXDest-playerWorldX)*mapSide);
		}
		else if(playerRegionX>=mapSide){
			worldXDest+=playerRegionX/mapSide;
			playerRegionX=playerRegionX%mapSide;
		}
		//worldXDest+=playerRegionX/mapSide;
		//std::cout << "ALER2: " << worldYDest << std::endl;
		//playerTileX=playerTileX%tileSide;
		//playerTileY=playerTileY%tileSide;
		//std::cout << "ALER3: " << playerTileY << std::endl;
	
		//playerRegionX=playerRegionX%mapSide;
		int calcY = worldYDest-current->y;
		int calcX = worldXDest-current->x;
		playerWorldY=worldYDest;
		playerWorldX=worldXDest;
		int length = (mapViewRadius*2);
		//std::cout << "START" << std::endl;
		//std::cout << "go" << std::endl;
		if(abs(calcY) > 1 || abs(calcX) > 1){
			teleport(); // whoosh
		}
		else if(calcY || calcX) {
			//std::cout << "go1" << std::endl;
			// do complicated stuff here
			std::list<std::list<map*>>::iterator yIt = current->yConnector;
			std::list<map*>::iterator xIt = current->xConnector;
			//std::cout << "went" << std::endl;
			map* spareMap;
			map* currMap = current;
			//std::cout << "half" << std::endl;
			map* theTestMap;
			//coordinate* cordArray[(mapViewRadius*2)+1];
			// we'll need to convert the thing below into a vector to work !!!
			std::vector<map*> iterArray; // needed?
			iterArray.resize((mapViewRadius*2)+1);
			//std::list<coordinate>::iterator testIterate;
			//std::cout << "tie" << std::endl;
			int y;
			int x;
			int startCord;
			int cordNumber = -1;
			//bool boolTest;
			std::vector<map*> checkArray;
			checkArray.resize((mapViewRadius*2)+1);
			//map* madeMap; // We also makes maps here. Insert doesn't do it for reasons.
			//std::cout << "go2" << std::endl;
			if(calcY<0){
				//std::cout << "GO!" << std::endl;
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->down; // GO DOWN TO DEACTIVATE
				}
				//std::cout << "GO!" << std::endl;
				currMap->deactivate();
				spareMap = currMap;
				for (int i = 0; i < mapViewRadius; i++)
				{
					currMap=currMap->left;
					currMap->deactivate();
					spareMap=spareMap->right;
					spareMap->deactivate();
				}
				currMap = current;
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->up; // GO UP TO FIND/SEARCH/ACTIVATE
				}
				iterArray[mapViewRadius] = currMap;
				spareMap = currMap;	
				yIt = currMap->yConnector;
				xIt = currMap->xConnector;
				for (int i = 1; i <= mapViewRadius; i++)
				{
					currMap=currMap->left;
					spareMap=spareMap->right;
					iterArray[mapViewRadius-i] = (currMap);
					iterArray[mapViewRadius+i] = (spareMap);
				}
				y = current->y - mapViewRadius - 1;
				startCord = current->x - mapViewRadius;
				x = startCord - 1; // keep this in place for now
				for (int i = 0; i <= length; i++){
					theTestMap = (iterArray[i])->up;
					checkArray[i] = theTestMap;
					if(checkArray[i]){
						theTestMap->activate();
						if(cordNumber==-1){
							yIt=theTestMap->yConnector;
							xIt=theTestMap->xConnector;
							cordNumber = i; // so we only do this once
						}
					}
				}
				for (int i = 0; i <= length; i++)
				{
					x++;
					if(!checkArray[i]){
						if(find(y,x,yIt,xIt)){
							(iterArray[i])->up = *xIt; //coordinates connect
							(*xIt)->down = iterArray[i]; //coordinates connect
							(*xIt)->activate();
						}
						else{
							currMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
							insertCoordinateRelative(yIt,xIt,currMap);
							(*xIt)->xConnector = xIt; // Connect to self, enforce loop
							(*xIt)->yConnector = yIt; // We don't do this in the function!
							(iterArray[i])->up = *xIt; //coordinates connect
							(*xIt)->down = (iterArray[i]); // update up/down map
							// starts activated
						}
					}
					if(x!=startCord){ // left/right. left is gauranteed to be something, so...
						(iterArray[i-1])->up->right = (iterArray[i])->up;
						(iterArray[i])->up->left = (iterArray[i-1])->up;
					}
				}
				current = current->up; // we transfer over.
			}
			else if (calcY){
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->up; // GO UP TO DEACTIVATE
				}
				currMap->deactivate();
				spareMap = currMap;
				for (int i = 0; i < mapViewRadius; i++)
				{
					currMap=currMap->left;
					currMap->deactivate();
					spareMap=spareMap->right;
					spareMap->deactivate();
				}
				currMap = current;
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->down; // GO DOWN TO FIND/SEARCH/ACTIVATE
				}
				iterArray[mapViewRadius] = currMap;
				spareMap = currMap;	
				yIt = currMap->yConnector;
				xIt = currMap->xConnector;
				for (int i = 1; i <= mapViewRadius; i++)
				{
					currMap=currMap->left;
					spareMap=spareMap->right;
					iterArray[mapViewRadius-i] = (currMap);
					iterArray[mapViewRadius+i] = (spareMap);
				}
				y = current->y + mapViewRadius + 1;
				startCord = current->x - mapViewRadius;
				x = startCord - 1; // keep this in place for now
				for (int i = 0; i <= length; i++){
					theTestMap = (iterArray[i])->down;
					checkArray[i] = theTestMap;
					if(checkArray[i]){
						theTestMap->activate();
						if(cordNumber==-1){
							yIt=theTestMap->yConnector;
							xIt=theTestMap->xConnector;
							cordNumber = i; // so we only do this once
						}
					}
				}
				for (int i = 0; i <= length; i++)
				{
					x++;
					if(!checkArray[i]){
						if(find(y,x,yIt,xIt)){
							(iterArray[i])->down = *xIt; //coordinates connect
							(*xIt)->up = iterArray[i]; //coordinates connect
							(*xIt)->activate();
						}
						else{
							currMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
							insertCoordinateRelative(yIt,xIt,currMap);
							(*xIt)->xConnector = xIt; // Connect to self, enforce loop
							(*xIt)->yConnector = yIt; // We don't do this in the function!
							(iterArray[i])->down = *xIt; //coordinates connect
							(*xIt)->up = (iterArray[i]); // update up/down map
							// starts activated
						}
					}
					if(x!=startCord){ // left/right. left is gauranteed to be something, so...
						(iterArray[i-1])->down->right = (iterArray[i])->down;
						(iterArray[i])->down->left = (iterArray[i-1])->down;
					}
				}
				current = current->down; // we transfer over.
			}
			// do complicated stuff here
			yIt = current->yConnector;
			xIt = current->xConnector;
			spareMap = current;
			cordNumber = -1;
			iterArray.clear();
			currMap = spareMap; // We'll use this as temp this time.
			if(calcX>0){
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->left; // GO LEFT TO DEACTIVATE
				}
				currMap->deactivate();
				spareMap = currMap;
				for (int i = 0; i < mapViewRadius; i++)
				{
					currMap = currMap->up;
					currMap->deactivate();
					spareMap = spareMap->down;
					spareMap->deactivate();
				}
				// now we set up list
				currMap = current;
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->right;  // GO RIGHT TO FIND/SEARCH/ACTIVATE
				}
				iterArray[mapViewRadius] = currMap;
				spareMap = currMap;
				for (int i = 1; i <= mapViewRadius; i++)
				{
					currMap = currMap->up;
					spareMap = spareMap->down;
					iterArray[mapViewRadius-i] = currMap;
					iterArray[mapViewRadius+i] = spareMap;
				}
				x = current->x + mapViewRadius + 1;
				startCord = current->y - mapViewRadius;
				y = startCord - 1; // keep this in place for now
				for (int i = 0; i <= length; i++)
				{
					y++;
					theTestMap = iterArray[i]->right;
					yIt=iterArray[i]->yConnector; // Because now we're RIGHT beside it.
					xIt=iterArray[i]->xConnector;
					if(theTestMap){
						theTestMap->activate();
					}
					else if(find(y,x,yIt,xIt)){
						iterArray[i]->right = *xIt; //coordinates connect
						(*xIt)->left = iterArray[i];
						(*xIt)->activate();
					}
					else{
						currMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
						insertCoordinateRelative(yIt,xIt,currMap);
						(*xIt)->xConnector = xIt;
						(*xIt)->yConnector = yIt;
						iterArray[i]->right = *xIt; //coordinates connect
						(*xIt)->left = iterArray[i];
					}
					if(y!=startCord){ // left/right. left is gauranteed to be something, so...
						iterArray[i-1]->right->down = iterArray[i]->right;
						iterArray[i]->right->up = iterArray[i-1]->right; 
					}
				}
				current = current->right; // we transfer over.
			}
			else if (calcX){
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->right; // GO RIGHT TO DEACTIVATE
				}
				currMap->deactivate();
				spareMap = currMap;
				//std::cout << "Lo2" << std::endl;
				for (int i = 0; i < mapViewRadius; i++)
				{
					currMap = currMap->up;
					currMap->deactivate();
					spareMap = spareMap->down;
					spareMap->deactivate();
				}
				// now we set up list
				//std::cout << "Lo4" << std::endl;
				currMap = current;
				for (int i = 0; i < mapViewRadius; i++){
					currMap = currMap->left;  // GO LEFT TO FIND/SEARCH/ACTIVATE
				}
				iterArray[mapViewRadius] = currMap;
				spareMap = currMap;
				//std::cout << "Lo3" << std::endl;
				for (int i = 1; i <= mapViewRadius; i++)
				{
					currMap = currMap->up;
					spareMap = spareMap->down;
					iterArray[mapViewRadius-i] = currMap;
					iterArray[mapViewRadius+i] = spareMap;
				}
				//std::cout << "Lo1" << std::endl;
				x = current->x - mapViewRadius - 1;
				startCord = current->y - mapViewRadius;
				y = startCord - 1; // keep this in place for now
				for (int i = 0; i <= length; i++)
				{
					//std::cout << "Lo " << i << std::endl;
					y++;
					theTestMap = iterArray[i]->left;
					yIt=iterArray[i]->yConnector; // Because now we're RIGHT beside it.
					xIt=iterArray[i]->xConnector;
					//std::cout << "Loa" << std::endl;
					if(theTestMap){
						//std::cout << "Lob" << std::endl;
						theTestMap->activate();
					}
					else if(find(y,x,yIt,xIt)){
						//std::cout << "Loc" << std::endl;
						iterArray[i]->left = *xIt; //coordinates connect
						(*xIt)->right = iterArray[i];
						(*xIt)->activate();
					}
					else{
						//std::cout << "Lod" << std::endl;
						currMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
						insertCoordinateRelative(yIt,xIt,currMap);
						(*xIt)->xConnector = xIt;
						(*xIt)->yConnector = yIt;
						iterArray[i]->left = *xIt; //coordinates connect
						(*xIt)->right = iterArray[i];
					}
					if(y!=startCord){ // left/right. left is gauranteed to be something, so...
						//std::cout << "Loe" << std::endl;
						iterArray[i-1]->left->down = iterArray[i]->left;
						iterArray[i]->left->up = iterArray[i-1]->left; 
					}
				}
				current = current->left; // we transfer over.
			}
		}
	}
	// IF WONDERING IF PLAYERZ IS OFF BY 1 OR SOME MORE: KNOW THAT WE USE HEIGHT FROM TILE.
	// THE TILES
	// NOT THE MAPHEIGHT
	// ELSE, GO FOR IT
	if(flyMode == 0){
		if(current->activated == 2){
			playerZ = 0;
		}
		else{
			playerZ = current->regionMap[playerRegionY*mapSide + playerRegionX].tileMap[playerTileY*tileSide + playerTileX];
		}
		return;
	}
	else if(flyMode == 1){
		int calcHeight;
		if(current->activated == 2){
			calcHeight = 0;
		}
		else{
			calcHeight = current->regionMap[playerRegionY*mapSide + playerRegionX].tileMap[playerTileY*tileSide + playerTileX];
		}
		if(calcHeight > playerZ){
			playerZ = calcHeight;
		}
	}
	// Else noclip.
}

playerSpace::~playerSpace(){
	if(debug){
		std::cout << "DELETING PLAYERSPACE " << this << std::endl;
	}
	std::list<std::list<map*>>::iterator yy = cordMap.begin();
	std::list<map*>::iterator xx;
	std::list<std::list<map*>>::iterator yyEnd = prev(cordMap.end());
	std::list<map*>::iterator xxEnd;
	bool startY = true;
	bool startX;
	while(yy!=yyEnd){
		if(!startY){
			yy++;
		}
		startY = false;
		xx=yy->begin();
		xxEnd=prev(yy->end());
		startX = true;
		while(xx!=xxEnd){
			if(!startX){
				xx++;
			}
			startX = false;
			delete (*xx);
		}
		yy->clear();
	}
	cordMap.clear();
	if(debug){
		std::cout << "DONE DELETING PLAYERSPACE " << this << std::endl;
	}
}

// Precondition: You're on a valid tile.
unsigned int playerSpace::view(float heightOffset,  int mapView, bool circle, bool borders, bool playerSee, bool wallMode, std::vector<int>& viewMap, std::vector<int>* optimizeArray, std::vector<int>& memoryMap,int specialTiles, bool InvisibleAboveCustom, bool checkAll, bool debug){
	// why there's problems: angles, viewing from a platau, you wouldn't be able to see below, from side, you would.
	// view up: algorithm that's efficient. returns angles, compares. see notes in THE book.
	int viewRadius;
	if(mapView){
		viewRadius= regionViewRadius;
	}
	else{
		viewRadius= tileViewRadius;
	}
	int viewTileWidth = (viewRadius*2)+1;
	unsigned int mapRadius;
	////std::cout << "GO" << std::endl;
	if(viewRadius == 0){
		mapRadius = 0;
	}
	else{
		mapRadius = 1 + (unsigned int)(viewRadius/tileSide);
	}
	unsigned int mapWidth = (mapRadius*2)+1;
	viewMap.reserve(viewTileWidth*viewTileWidth);
	////std::cout << "GO" << std::endl;
	float centerPixelX;
	float centerPixelY;
	int tileY;
	int tileX;
	int tileSideB;
	if(mapView){
		tileY=playerRegionY;
		tileX=playerRegionX;
		tileSideB=mapSide;
		//This is a useful hack. coder plz
	}
	else{
		tileY=playerTileY;
		tileX=playerTileX;
		tileSideB=tileSide;
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
	int regionX;
	int regionY;
	float A;
	float B;
	float difference;
	map* usedMap;
	int halfTileWidth = (viewTileWidth/2);
	////std::cout << "Wwoa" << std::endl;
	for (int y = -halfTileWidth; y <= halfTileWidth; y++)
	{
		
		for (int x = -halfTileWidth; x <= halfTileWidth; x++)
		{
			map* usedMap = current;
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
					////std::cout << "G" << std::endl;
					memoryMap.push_back(0);
					viewMap.push_back(-3);
					continue;
					////std::cout << "GO" << std::endl;
				}
			}
			wy = y+tileY; // Relative positions, we need these
			ex = x+tileX;
			regionYOffset = 0;
			regionXOffset = 0;
			worldYOffset = 0;
			worldXOffset = 0;
			if(mapView){
				//std::cout << "ester: " << wy << " " << mapSide <<std::endl;
				if(wy<0){
					worldYOffset = ((wy+1)/mapSide)-1;
				}
				else{
					worldYOffset = wy/mapSide;
				}
				//worldYOffset = wy/mapSide; // We determine how many worldspaces to left
				wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
				//std::cout << "res: " << wy <<std::endl;
				//std::cout << "worldY " << worldYOffset <<std::endl;
				
				////std::cout << "ALERT= " << ex << " " << mapSide << std::endl;
				if(ex<0){
					worldXOffset = ((ex+1)/mapSide)-1;
				}
				else{
					worldXOffset = ex/mapSide;
				}
				////std::cout << "ALERTD= " << worldXOffset << std::endl;
				ex -=(worldXOffset*mapSide);
				//std::cout << "EZ: " << y << " " << x << std::endl;
				while(worldYOffset){
					if(worldYOffset>0){
						//std::cout << "==DOWN" << std::endl;
						usedMap = usedMap->down;
						worldYOffset--;
					}
					else if(worldYOffset<0){
						//std::cout << "==UP" << std::endl;
						usedMap = usedMap->up;
						worldYOffset++;
					}
				}
				while(worldXOffset){
					if(worldXOffset>0){
						//std::cout << "==RIGHT" << std::endl;
						usedMap = usedMap->right;
						worldXOffset--;
					}
					else if(worldXOffset<0){
						//std::cout << usedMap->down << std::endl;
						//std::cout << usedMap->up << std::endl;
						//std::cout << usedMap->left << std::endl;
						//std::cout << usedMap->right << std::endl;
						//std::cout << "==LEFT" << std::endl;
						usedMap = usedMap->left;
						worldXOffset++;
					}
				}
				//worldYOffset+=worldY;
				//worldXOffset+=worldX;
				//if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
				//	////std::cout << "WATER" << std::endl;
				//	memoryMap.push_back(0);
				//	viewMap.push_back(0);
				//	continue;
				//}
				////std::cout << theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex] << std::endl;
				////std::cout<<wy<<" "<<ex<<" "<<tileSideB<<std::endl;
				if(usedMap->activated == 2){ // Ocean tiles yoo.
					viewMap.push_back(0);
				}
				else{
					viewMap.push_back(usedMap->heightMap[(wy*tileSideB)+ex]);
					
				}
				memoryMap.push_back(usedMap->regionMemoryMap[(wy*tileSideB)+ex]);
				continue;
			}
			else{
				if(wy<0){
					regionYOffset = ((wy+1)/tileSide)-1;
				}
				else{
					regionYOffset = wy/tileSide;
				}
				//regionYOffset = wy/tileSide;
				////std::cout << "AGO1 " << wy << std::endl;
				wy-=(regionYOffset*tileSide);
				////std::cout << "AGO1 " << wy << std::endl;
				if(ex<0){
					regionXOffset = ((ex+1)/tileSide)-1;
				}
				else{
					regionXOffset = ex/tileSide;
				}
				//regionXOffset = ex/tileSide;
				ex -=(regionXOffset*tileSide);
				////std::cout<<regionXOffset<<" "<<regionYOffset<<" "<<tileSide<<std::endl;
				regionYOffset+=playerRegionY;
				regionXOffset+=playerRegionX; // get the regions
				if(regionYOffset<0){
					worldYOffset = ((regionYOffset+1)/mapSide)-1;
				}
				else{
					worldYOffset = regionYOffset/mapSide;
				}
				//worldYOffset = regionYOffset/mapSide; // We determine how many worldspaces to right
				regionYOffset-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
				if(regionXOffset<0){
					worldXOffset  = ((regionXOffset+1)/mapSide)-1;
				}
				else{
					worldXOffset  = regionXOffset/mapSide;
				}
				//worldXOffset = (regionXOffset)/mapSide;
				regionXOffset -=(worldXOffset*mapSide);
				while(worldYOffset){
				////std::cout << "======WARN=====" << std::endl;
					if(worldYOffset>0){
						usedMap = usedMap->down;
						worldYOffset--;
					}
					else if(worldYOffset<0){
						usedMap = usedMap->up;
						worldYOffset++;
					}
				}
				while(worldXOffset){
					////std::cout << "======WARN=====" << std::endl;
					if(worldXOffset>0){
						usedMap = usedMap->right;
						worldXOffset--;
					}
					else if(worldXOffset<0){
						usedMap = usedMap->left;
						worldXOffset++;
					}
				}
				//if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
				//	memoryMap.push_back(0);
				//	viewMap.push_back(0);
				//	continue;
				//}
				////std::cout << "REGION: " << regionYOffset << " " << regionXOffset << std::endl;
				////std::cout << "TILE: " << wy << " " << ex << std::endl;
				if(usedMap->activated == 2){ // Ocean tiles yoo.
					viewMap.push_back(0);
					memoryMap.push_back(1); // Really shouldn't matter, but... you know.
				}
				else{
					viewMap.push_back(usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]);
					memoryMap.push_back(usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMemoryMap[(wy*tileSide)+ex]);
				}
				
				
			}
			//if(theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] > 9){
				////std::cout << theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] << std::endl;
				////std::cout << "---- SIDE: " << tileSide << " X: " << x << " Y: " << y << " EX: "<< ex << " WY: " << wy << std::endl;
			//}
		}
	}
	//std::cout << "Wwo" << std::endl;
	//for (int j = 0; j < viewTileWidth*viewTileWidth; j++)
	//{
	//	if (j%viewTileWidth == 0) std::cout<<std::endl;
	//	std::cout << viewMap[j];
	//}
	//std::cout<<std::endl;
	int boolMap[viewTileWidth*viewTileWidth];
	std::vector<std::vector<std::vector<double>>> funcTracking;
	funcTracking.resize(4); // First is playerIsHigher + yMode*2
	funcTracking[0].resize(4); // Then is xShift + yShift*2
	//funcTracking[0][0].resize(2);
	//funcTracking[0][1].resize(2);
	//funcTracking[0][2].resize(2);
	//funcTracking[0][3].resize(2);
	funcTracking[1].resize(4);
	//funcTracking[1][0].resize(2);
	//funcTracking[1][1].resize(2);
	//funcTracking[1][2].resize(2);
	//funcTracking[1][3].resize(2);
	funcTracking[2].resize(4);
	funcTracking[3].resize(4);
	if(wallMode && !borders){ // for the time being, it's incompatible with borders
		for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
		{
			boolMap[i] = 0;
		}
		boolMap[(halfTileWidth*viewTileWidth)+halfTileWidth] = 1;
		for(int a = 0; a < viewTileWidth; a++)
		{
			// Getting most of them with this is a good, efficient idea and method.
			////std::cout << "FIRST " << std::endl;
			viewLine(viewTileWidth,boolMap,&funcTracking,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerZ, a, 0,true,debug);
			////std::cout << "SECOND " << std::endl;
			viewLine(viewTileWidth,boolMap,&funcTracking,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerZ, a, viewTileWidth-1,true,debug);
			////std::cout << "THIRD " << std::endl;
			viewLine(viewTileWidth,boolMap,&funcTracking,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerZ, 0, a,true,debug);
			////std::cout << "FOURTH " << std::endl;
			viewLine(viewTileWidth,boolMap,&funcTracking,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth, playerZ,viewTileWidth-1, a,true,debug);
		}
		////std::cout << "----END AROUND----" << std::endl;
		for(int y = 1; y < viewTileWidth-1; y++)
		{
			for (int x = 1; x < viewTileWidth-1; x++)
			{
				if(boolMap[(y*viewTileWidth)+x] != 1 || checkAll){ // This will save a function call, more efficient than in viewLine function check.
					viewLine(viewTileWidth,boolMap,&funcTracking,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerZ, y, x,true,debug);
				}
				////std::cout << y << " " << x << std::endl;
			}
		}
		if(InvisibleAboveCustom){ // More efficient than detecting every for loop.
			for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
			{
				////std::cout << boolMap[i] << std::endl;
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
					usedMap = current;
					if(mapView){
							//std::cout << "ester2: " << wy << " " << mapSide << " " << wy/mapSide << std::endl;
							if(wy<0){
								worldYOffset = ((wy+1)/mapSide)-1;
							}
							else{
								worldYOffset = wy/mapSide;
							}
							wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							//std::cout << "res2: " << wy <<std::endl;
							//std::cout << "worldY2: " << worldYOffset <<std::endl;
							//worldYOffset = wy/mapSide; // We determine how many worldspaces to right
							//wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							if(ex<0){
								worldXOffset = ((ex+1)/mapSide)-1;
							}
							else{
								worldXOffset = ex/mapSide;
							}
							//worldXOffset = ex/mapSide;
							ex -=(worldXOffset*mapSide);
							while(worldYOffset){
								if(worldYOffset>0){
									usedMap = usedMap->down;
									worldYOffset--;
								}
								else if(worldYOffset<0){
									usedMap = usedMap->up;
									worldYOffset++;
								}
							}
							while(worldXOffset){
								if(worldXOffset>0){
									usedMap = usedMap->right;
									worldXOffset--;
								}
								else if(worldXOffset<0){
									usedMap = usedMap->left;
									worldXOffset++;
								}
							}
							//if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
							//	continue; // Skip OOB
							//}
							////std::cout << theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex] << std::endl;
							//std::cout << "FIND BUGGER: Y: " << wy << " X: " << ex << std::endl;
							usedMap->regionMemoryMap[(wy*mapSide)+ex] = 1;
							////std::cout << "GI HERE " << theMap.bigMap[worldYOffset * worldSide + worldXOffset].regionMemoryMap[(wy*tileSide)+ex]<< std::endl;
							if(trigger){
								if(usedMap->activated == 2){
									memoryMap[indexB] = 1;
								}
								else{
									memoryMap[indexB] = usedMap->heightMap[(wy*mapSide)+ex]+1;
								}
								continue;
							}
							memoryMap[indexB] = 0;
							continue;
					}
					else{
							if(wy<0){
								regionYOffset = ((wy+1)/tileSide)-1;
							}
							else{
								regionYOffset = wy/tileSide;
							}
							wy-=(regionYOffset*tileSide);
							if(ex<0){
								regionXOffset = ((ex+1)/tileSide)-1;
							}
							else{
								regionXOffset = ex/tileSide;
							}
							ex -=(regionXOffset*tileSide);
							regionYOffset+=playerRegionY;
							regionXOffset+=playerRegionX; // get the regions
							if(regionYOffset<0){
								worldYOffset = ((regionYOffset+1)/mapSide)-1;
							}
							else{
								worldYOffset = regionYOffset/mapSide;
							}
							regionYOffset-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							if(regionXOffset<0){
								worldXOffset  = ((regionXOffset+1)/mapSide)-1;
							}
							else{
								worldXOffset  = regionXOffset/mapSide;
							}
							regionXOffset -=(worldXOffset*mapSide);
							while(worldYOffset){
								if(worldYOffset>0){
									usedMap = usedMap->down;
									worldYOffset--;
								}
								else if(worldYOffset<0){
									usedMap = usedMap->up;
									worldYOffset++;
								}
							}
							while(worldXOffset){
								if(worldXOffset>0){
									usedMap = usedMap->right;
									worldXOffset--;
								}
								else if(worldXOffset<0){
									usedMap = usedMap->left;
									worldXOffset++;
								}
							}
							//if(worldXOffset<0 || worldYOffset<0 || worldXOffset >= worldSide || worldYOffset >=worldSide){
							//	continue; // Skip OOB
							//}
							//std::cout << "FIND BUGGER: RY: " << regionYOffset << "RX: " << regionXOffset <<" Y: "<< wy << " X: " << ex << std::endl;
							if(usedMap->activated != 2){
								usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMemoryMap[(wy*tileSide)+ex] = 1;
							}
							if(trigger){
								if(usedMap->activated == 2){
									memoryMap[indexB] = 1;
								}
								else{
									memoryMap[indexB] = usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]+1;
								}
								continue;
							}
							memoryMap[indexB] = 0;
							continue;
					}
				}
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
				////std::cout << firstX << " " << lastX << std::endl;
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
				////std::cout << firstX << " " << lastX << std::endl;
				optimizeArray->push_back(firstX); // We get the first x at the start of each Y.
			}
		}
	}
	if(playerSee){
		viewMap[(halfTileWidth*viewTileWidth)+halfTileWidth] = (-specialTiles)-1;
	}
	return viewTileWidth;
}
