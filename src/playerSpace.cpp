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
		cordMap = {};
    	current = new map(seed,0,0,push,mapSide,tileSide,battlefieldSide,diagonal,debug); 
	map* tempMap;
	if(debug)
	std::cout << "PLAYERSPACE " << this << ": #" << 0 << " MAP CREATED: " << current << std::endl; 
	mapCount = 1;
	tileViewRadius = playerViewRadius;
	regionViewRadius = playerViewRadius; // For now they are the same.
	mapViewRadius = (regionViewRadius / mapSide) + 1; // How far away we generatin'? Must be >=1
	//std::list<std::list<coordinate>> cordMap
	////std::cout << "CHECK0 " << current << std::endl;
	coordinate tempCord = {0,0,current,NULL,NULL};
	std::list<coordinate> tempList = {}; // DEALLOC PER EACH WITHIN CORDMAP
	////std::cout << "CHECK1" << std::endl;
	for(int i = -mapViewRadius;i<=0;i++) {
		////std::cout << "CHECKA" << std::endl;
		cordMap.push_back(tempList); // This many rows for beginning.
	}
	////std::cout << "CHECKAA" << std::endl;
	std::list<std::list<coordinate>>::iterator temp = --cordMap.end();
	////std::cout << "CHECKB " << &temp << std::endl;
	for(int i = 0;i<mapViewRadius;i++) {
		////std::cout << "CHECKC " << &temp << std::endl;
		cordMap.push_back(tempList); // This many rows for beginning.
	}
	//LEARN FROM MY MISTAKES LESSION 20: .end() is an iterator to an element past the LAST IN THE LIST!!!
	////std::cout << "CHECKD " << &temp << " " << &tempCord << " " << &(*temp) << std::endl;
	(*temp).push_front(tempCord); // Attach the first cord to middle.
	////std::cout << "CHECKE" << std::endl;
	// Finally set up to start expanding.
	////std::cout << "CHECK2 " << temp->size() << std::endl;
	std::list<coordinate>::iterator middle = temp->begin();
	//http://www.cplusplus.com/reference/list/list/insert/ Val also copied.
	//http://www.cplusplus.com/reference/list/list/push_front/ Val is copied !!!
	bool isTop = 1;
	std::list<coordinate>::iterator justHappened;
	std::list<coordinate>::iterator it;
	temp = cordMap.begin();
	////std::cout << "CHECK3" << std::endl;
	for(int y = -mapViewRadius;y<=mapViewRadius;y++){
		////std::cout << "CHECK4 " << y << std::endl;
		for(int x = -mapViewRadius;x<=mapViewRadius;x++){
			//std::cout << "TRAVEL1 " << y << " " << x <<std::endl;
			if(x==y && x==0) {
				current->xConnector = std::prev(std::next(temp)->end());
				current->yConnector = temp;
				std::prev(std::next(temp)->end())->up = &(*(it));
				it->down = &(*(std::prev(std::next(temp)->end())));
				it++;
				continue; // Skip current.
			}
			tempMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
			if(debug) 
				std::cout << "PLAYERSPACE " << this << ": #" << mapCount << " MAP CREATED: " << tempMap << std::endl; 
			if(isTop){
				//std::cout << "TRAVEL2a" << std::endl;
				tempCord = {y,x,tempMap,NULL,NULL}; // Basic, just put in deh grill
				temp->push_back(tempCord);
				//std::cout << "TRAVEL2b" << std::endl;
				std::prev(temp->end())->pointer->xConnector = std::prev(temp->end());
				//std::cout << "TRAVEL2c" << std::endl;
				std::prev(temp->end())->pointer->yConnector = temp;
				//std::cout << "TRAVEL2d" << std::endl;
			}
			else {
				//std::cout << "TRAVEL3 " << &(*it) << std::endl;
				tempCord = {y,x,tempMap,&(*it),NULL};
				if(!y){
					////std::cout << "TRAVEL4" << std::endl;
					if(x<0){
						////std::cout << "TRAVEL5 " << &middle << " " << temp->size() << std::endl;
						justHappened = std::next(temp)->insert(middle,tempCord); // insert, justHappened has pointer.
						justHappened->pointer->xConnector = justHappened;
						justHappened->pointer->yConnector = temp;
						//std::cout << "TRAVEL5B " << justHappened->pointer << " === " << it->y << std::endl;
						it->down = &(*justHappened); // Set the one above to point down to justHappened.
						//justHappened is already pointing up -- look at tempCord
						////std::cout << "TRAVEL5C" << std::endl;
					}
					else{
						//std::cout << "TRAVEL6 " << std::prev(std::next(temp)->end())->pointer << " === " << it->y << std::endl;
						std::next(temp)->push_back(tempCord);
						std::prev(std::next(temp)->end())->pointer->xConnector = std::prev(std::next(temp)->end());
						std::prev(std::next(temp)->end())->pointer->yConnector = std::next(temp);
						it->down = &(*(std::prev(std::next(temp)->end())));
					}
				}
				else{
					//std::cout << "TRAVEL57 " << std::prev(std::next(temp)->end())->pointer << " === " << it->y << std::endl;
					std::next(temp)->push_back(tempCord);
					std::prev(std::next(temp)->end())->pointer->xConnector = std::prev(std::next(temp)->end());
					std::prev(std::next(temp)->end())->pointer->yConnector = std::next(temp);
					it->down = &(*(std::prev(std::next(temp)->end())));;
				}
				it++;
			}
			////std::cout << "TRAVELt" << std::endl;
			if(x==mapViewRadius) break; // End case.
			////std::cout << "TRAVELG" << std::endl;
			////std::cout << "TRAVEL8" << std::endl;
			// consider just having by itself instead of &(*...) -- CONFIRMED BAD.
			// consider not checking end case.
		}
		////std::cout << "TRAVEL9" << std::endl;
		if(y==mapViewRadius){
			break;
		}
		////std::cout << "TRAVEL10" << std::endl;
		if(!isTop){
			temp++;
		}

		////std::cout << "TRAVEL11" << std::endl;
		it = temp->begin();
		isTop = 0;
		
		
	}
	
	temp=cordMap.begin();
	it=temp->begin();
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector)) << " " << it->up << " " << it->down <<  std::endl;
	it++;
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  <<" " << it->up << " " << it->down << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  << " " << it->up << " " << it->down << std::endl;
	temp++;
	it=temp->begin();
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  <<" " << it->up << " " << it->down << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  <<" " << it->up << " " << it->down << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector)) <<" " << it->up << " " << it->down << std::endl;
	temp++;
	it=temp->begin();
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  << " " << it->up << " " << it->down << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  <<" " << it->up << " " << it->down << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->y << " " << it->x << " " << &(*it) << " " << &(*(it->pointer->xConnector))  << " " << it->up << " " << it->down << std::endl;
	temp++;
	

	temp=cordMap.begin();
	std::list<std::list<coordinate>>::iterator  spareTemp = temp;
	for (int y=-mapViewRadius;y<=mapViewRadius; y++)
	{
		//std::cout << "ST " << temp->begin()->y << " " << cordMap.size()<< std::endl;
		it = temp->begin();
		//std::cout << "STA " << temp->size() << std::endl;
		middle = it; // This really just a temp value. -- is one ahead
		if(y!=mapViewRadius){
			spareTemp++;
			justHappened = spareTemp->begin(); // Temp value of stuff below. - same index as it
			////std::cout << "ALRAM== " << justHappened->y << std::endl;;
		}

		for (int x=-mapViewRadius;x<=mapViewRadius; x++)
		{
			//std::cout << "TRAVEL13 " << x << " " << y <<std::endl;
			if(x!=mapViewRadius){
				//std::cout << "TRAVEL14" << std::endl;
				middle++;
				//std::cout << "TRAVEL14a " << std::endl;
				it->pointer->right = middle->pointer;
				//std::cout << "TRAVEL14b " <<  std::endl;
				middle->pointer->left = it->pointer;
				//std::cout << "TRAVEL14c" << std::endl;
			}
			if(y!=mapViewRadius){
				//std::cout << "TRAVEL15 " << justHappened->pointer <<std::endl;
				it->pointer->down = justHappened->pointer;
				//std::cout << "TRAVEL15B " << it->pointer->down << std::endl;
				justHappened->pointer->up = it->pointer;
			}
			//std::cout << "TRAVEL16" << std::endl;
			it=middle; // or it++;
			justHappened++;
			//std::cout << "TRAVEL17" << std::endl;
		}
		//std::cout << "TRAVEL18 " << temp->begin()->y << std::endl;
		temp++;
		//std::cout << "TRAVEL19" << std::endl;
	}
	if(debug)
    	std::cout << "CREATED PLAYERSPACE " << this << std::endl; 
    temp=cordMap.begin();
	it=temp->begin();
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up << " " << it->pointer->down << " " << it->pointer->left << " " << it->pointer->right << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up << " " << it->pointer->down  << " " << it->pointer->left<< " " << it->pointer->right   << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up<< " " << it->pointer->down << " " <<it->pointer->left<< " " <<it->pointer->right   <<  std::endl;
	temp++;
	it=temp->begin();
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up<< " " << it->pointer->down  << " " <<it->pointer->left<< " " << it->pointer->right   <<std::endl;
	it++;
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up<< " " << it->pointer->down << " " << it->pointer->left << " " << it->pointer->right   <<std::endl;
	it++;
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up<< " " << it->pointer->down  << " " << it->pointer->left << " " << it->pointer->right  <<std::endl;
	temp++;
	it=temp->begin();
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up << " " << it->pointer->down  << " " << it->pointer->left << " " << it->pointer->right  <<  std::endl;
	it++;
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up<< " " << it->pointer->down  << " " << it->pointer->left << " " << it->pointer->right  << std::endl;
	it++;
	//std::cout << "CHECKZa " << it->pointer << " " << it->pointer->up<< " " << it->pointer->down << " " << it->pointer->left << " " << it->pointer->right  <<std::endl;
	temp++;
    
}

void playerSpace::insertCoordinateRelative(std::list<std::list<coordinate>>::iterator& yy, std::list<coordinate>::iterator& xx, coordinate data){
// if not found y, use mylist.insert (iterator,thingWeWantToPutIn);
	int wy = xx->y;
	int tarX = data.x;
	int tarY = data.y;
	bool goDir = true; //For technical insertion.
	// WARNING: WE'RE NOT KEEPING TRACK OF EX AND WY THROUGH THIS.
	if(tarY< cordMap.begin()->begin()->y){ // test if y is out of range
		std::list<coordinate> tempList;
		tempList.push_front(data);
		cordMap.push_front(tempList);
		yy = (cordMap.begin());
		xx= cordMap.begin()->begin();
		//xx->xConnector = &(*xx);
		//xx->yConnector = &(*yy);
		return;
	}
	else if(tarY>std::prev(cordMap.end())->begin()->y){
		std::list<coordinate> tempList;
		tempList.push_back(data);
		cordMap.push_back(tempList);
		yy = std::prev(cordMap.end());
		xx= std::prev(std::prev(cordMap.end())->end());
		return;
	}
	bool tester;
	while(1){ // Welp.
		if(wy==tarY){
			if(tarX < yy->begin()->x){ // test if x is out of range
				yy->push_front(data);
				xx= yy->begin();
				return;
			}
			else if (tarX > std::prev(yy->end())->x){
				yy->push_back(data);
				xx= std::prev(yy->end());
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
			xx = yy->insert(xx,data);
			return;
		}
		else{
			wy=yy->begin()->y;
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
				wy= yy->begin()->y;
				if(wy == tarY){
					break; // Go get x now.
				}
				tester = (wy < tarY);
			}
			if(wy!=tarY){ // If it wasn't found, we make a new one.
				std::list<coordinate> tempList;
				tempList.push_back(data);
				yy = cordMap.insert(yy,tempList);
				xx= yy->begin();
				return;
			}
			xx = std::prev((*yy).end());
			if(tarX - yy->begin()->x < prev(yy->end())->x - tarX){ //quick comparison for comparison's sake
				xx = yy->begin();
			}
		}
	}
}

bool playerSpace::find(int y, int x, std::list<std::list<coordinate>>::iterator& yy, std::list<coordinate>::iterator& xx){
	if(y < cordMap.begin()->begin()->y){
		return false;
	}
	else if(y > std::prev(cordMap.end())->begin()->y){
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
	if(x>std::prev(yy->end())->x){
		return false;
	}
	if(x<yy->begin()->x){
		return false;
	}
	if(searchX){
		xx = std::prev(yy->end());
		if(x - yy->begin()->x < xx->x - x){ //quick comparison for comparison's sake
			xx = yy->begin();
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

void playerSpace::teleport(){
	// I'll implement later. For now, have this friendly neighborhood seg-fault
	current = NULL;
}

void playerSpace::travel(int yT, int xT, int mode){
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
	worldXDest+=playerRegionX/mapSide;
	playerTileX=playerTileX%tileSide;
	playerTileY=playerTileY%tileSide;
	playerRegionY=playerRegionY%mapSide;
	playerRegionX=playerRegionX%mapSide;
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
		std::list<std::list<coordinate>>::iterator yIt = current->yConnector;
		std::list<coordinate>::iterator xIt = current->xConnector;
		//std::cout << "went" << std::endl;
		std::list<coordinate>::iterator spareX;
		coordinate currCord = *xIt;
		//std::cout << "half" << std::endl;
		coordinate* theTestCord;
		//coordinate* cordArray[(mapViewRadius*2)+1];
		// we'll need to convert the thing below into a vector to work !!!
		std::vector<std::list<coordinate>::iterator> iterArray; // needed?
		iterArray.resize((mapViewRadius*2)+1);
		//std::list<coordinate>::iterator testIterate;
		//std::cout << "tie" << std::endl;
		int y;
		int x;
		int startCord;
		int cordNumber = -1;
		map* madeMap; // We also makes maps here. Insert doesn't do it for reasons.
		//std::cout << "go2" << std::endl;
		if(calcY<0){
			std::cout << "go1" << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				//std::cout << "YBC: " << (currCord).y << std::endl;
				currCord = *(currCord.down); // GO DOWN TO DEACTIVATE
				//std::cout << "YAC: " << (currCord).y << std::endl;
			}
			currCord.pointer->deactivate();
			spareX = currCord.pointer->xConnector;
			xIt = spareX;
			for (int i = 0; i < mapViewRadius; i++)
			{
				xIt--;
				xIt->pointer->deactivate();
				spareX++;
				spareX->pointer->deactivate();
			}
			// now we set up list
			//std::cout << "go4" << std::endl;
			//std::cout << "YcC: " << (currCord).y << std::endl;
			currCord = *(current->xConnector);
			//std::cout << "YcB: " << (currCord).y << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				//std::cout << "YBCa: " << (currCord).y << std::endl;
				currCord = *(currCord.up); // GO UP TO FIND/SEARCH/ACTIVATE
				//std::cout << "YBb: " << (currCord).y << std::endl;
			}
			iterArray[mapViewRadius] = (currCord.pointer->xConnector);
			//std::cout << "go45" << std::endl;
			spareX = iterArray[mapViewRadius];	
			yIt = currCord.pointer->yConnector;
			xIt = spareX;
			for (int i = 1; i <= mapViewRadius; i++)
			{
				//std::cout << "TESTER1: " << xIt->pointer << " " << spareX->pointer << std::endl;
				xIt--;
				//std::cout << "TESTER2: " << xIt->pointer << " " << spareX->pointer << std::endl;
				spareX++;
				//std::cout << "TESTER3: " << xIt->pointer << " " << spareX->pointer << std::endl;
				iterArray[mapViewRadius-i] = ((xIt));
				iterArray[mapViewRadius+i] = ((spareX));
			}
			y = current->y - mapViewRadius - 1;
			startCord = current->x - mapViewRadius;
			x = startCord - 1; // keep this in place for now
			//std::cout << "go5" << std::endl;
			for (int i = 0; i <= length; i++)
			{
				//std::cout << "go5a " << i << " " << length << std::endl;
				x++;
				theTestCord = (iterArray[i])->up;
				//std::cout << "testaab: " << &(iterArray[0]) << " " << &xIt <<std::endl;
				if(theTestCord){
					//std::cout << "FACTIVATE" << std::endl;
					theTestCord->pointer->activate();
					if(cordNumber != -1){
						cordNumber = i; // so we only do this once
						yIt=theTestCord->pointer->yConnector;
						xIt=theTestCord->pointer->xConnector;
					}
				}
				else if(find(y,x,yIt,xIt)){
					//std::cout << "FINDA" << std::endl;
					(iterArray[i])->up = &(*xIt); //coordinates connect
					xIt->down = &(*iterArray[i]); //coordinates connect
					xIt->pointer->down = (iterArray[i])->pointer; // update up/down map
					(iterArray[i])->pointer->up = xIt->pointer;
					xIt->pointer->activate();
				}
				else{
					//std::cout << "INSERTA" << std::endl;
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
					//std::cout << "garch1 " <<  (iterArray[0])->pointer << " " << 0 <<  " " << (iterArray[0])->pointer->up << std::endl;
					currCord = {y,x,madeMap,NULL,&(*iterArray[i])}; // Sorry
					//std::cout << "garch2 " <<  (iterArray[0])->pointer << " " << 0 <<  " " << (iterArray[0])->pointer->up << std::endl;
					////std::cout << "checka " << &(*xIt) << " " << y << " YYY" << std::endl;
					//std::cout << "god1 " << (iterArray[0])->pointer << " " << 0 <<  " " << (iterArray[0])->pointer->up << std::endl;
					//std::cout << "test1: " << &(iterArray[0]) << " " << &xIt <<std::endl;
					
					//std::cout << "REALLY: " << y << std::endl;
					//std::cout << "god2 " << (iterArray[1])->pointer << " " << 1 <<  " " << (iterArray[1])->pointer->up << std::endl;
					//std::cout << "god3 " << (iterArray[2])->pointer << " " << 2 <<  " " << (iterArray[2])->pointer->up << std::endl;
					insertCoordinateRelative(yIt,xIt,currCord);
					//std::cout << "god1a " << (iterArray[0])->pointer << " " << 0 <<  " " << (iterArray[0])->pointer->up << std::endl;
					//std::cout << "test1a: " << &(iterArray[0]) << " " << &xIt << std::endl;
					//std::cout << "god2a " << (iterArray[1])->pointer << " " << 1 <<  " " << (iterArray[1])->pointer->up << std::endl;
					//std::cout << "god3a " << (iterArray[2])->pointer << " " << 2 <<  " " << (iterArray[2])->pointer->up << std::endl;
					xIt->pointer->xConnector = xIt; // Connect to self, enforce loop
					xIt->pointer->yConnector = yIt;
					//std::cout << "garch3 " <<  (iterArray[0])->pointer << " " << 0 <<  " " << (iterArray[0])->pointer->up << std::endl;
					//std::cout << "checka " << &(*xIt) << std::endl;
					(iterArray[i])->up = &(*xIt); //coordinates connect
					xIt->pointer->down = (iterArray[i])->pointer; // update up/down map
					(iterArray[i])->pointer->up = xIt->pointer;
					//std::cout << "garch4 " << (iterArray[0])->pointer << " " << 0 <<  " " << xIt->pointer << std::endl;
				}
				if(x!=startCord && !theTestCord){ // left/right. left is gauranteed to be something, so...
					//std::cout << "garch5 " << (iterArray[0])->pointer << " " << 0 <<  " " << (iterArray[0])->pointer->up << std::endl;
					(iterArray[i-1])->pointer->up->right = (iterArray[i])->pointer->up;
					(iterArray[i])->pointer->up->left = (iterArray[i-1])->pointer->up;
				}
			}
			//std::cout << "goa1" << std::endl;
			current = current->up; // we transfer over.
		}
		else if (calcY){
			//std::cout << "go2" << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				//std::cout << "YBC: " << (currCord).y << std::endl;
				currCord = *(currCord.up); // GO UP TO DEACTIVATE
				//std::cout << "YBC: " << (currCord).y << std::endl;
			}
			
			currCord.pointer->deactivate();
			
			spareX = currCord.pointer->xConnector;
			xIt = spareX;
			for (int i = 0; i < mapViewRadius; i++)
			{
				xIt--;
				xIt->pointer->deactivate();
				spareX++;
				spareX->pointer->deactivate();
			}
			// now we set up list
			//std::cout << "go4" << std::endl;
			//std::cout << "YBB: " << (currCord).y << std::endl;
			currCord = *(current->xConnector);
			//std::cout << "YAB: " << (currCord).y << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				//std::cout << "YB: " << (currCord).y << std::endl;
				currCord = *(currCord.down); // GO DOWN TO FIND/SEARCH/ACTIVATE
				//std::cout << "YA: " << (currCord).y << std::endl;
			}
			iterArray[mapViewRadius] = (currCord.pointer->xConnector);
			spareX = iterArray[mapViewRadius];	
			yIt = currCord.pointer->yConnector;
			xIt = spareX;
			for (int i = 1; i <= mapViewRadius; i++)
			{
				xIt--;
				spareX++;
				iterArray[mapViewRadius-i] = ((xIt));
				iterArray[mapViewRadius+i] = ((spareX));
			}
			y = current->y + mapViewRadius + 1;
			startCord = current->x - mapViewRadius;
			x = startCord - 1; // keep this in place for now
			//std::cout << "go5 " << y << std::endl;
			for (int i = 0; i <= length; i++)
			{
				//std::cout << "go5a" << std::endl;
				x++;
				theTestCord = (iterArray[i])->down;
				//std::cout << iterArray[i]->y << std::endl;
				if(theTestCord){
					//std::cout << "FACTIVATE" << std::endl;
					theTestCord->pointer->activate();
					if(cordNumber != -1){
						cordNumber = i; // so we only do this once
						yIt=theTestCord->pointer->yConnector;
						xIt=theTestCord->pointer->xConnector;
					}
				}
				else if(find(y,x,yIt,xIt)){
					//std::cout << "FINDA" << std::endl;
					(iterArray[i])->down = &(*xIt); //coordinates connect
					xIt->up = &(*iterArray[i]); //coordinates connect
					xIt->pointer->up = (iterArray[i])->pointer; // update up/down map
					(iterArray[i])->pointer->down = xIt->pointer;
					xIt->pointer->activate();
				}
				else{
					//std::cout << "INSERTA" << std::endl;
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
					currCord = {y,x,madeMap,&(*iterArray[i]),NULL}; // Sorry
					//std::cout << "checka " << &(*xIt) << " " << y << " YYY" << std::endl;
					insertCoordinateRelative(yIt,xIt,currCord);
					xIt->pointer->xConnector = xIt; // Connect to self, enforce loop
					xIt->pointer->yConnector = yIt;
					//std::cout << "checka " << &(*xIt) << std::endl;
					(iterArray[i])->down = &(*xIt); //coordinates connect
					xIt->pointer->up = (iterArray[i])->pointer; // update up/down map
					(iterArray[i])->pointer->down = xIt->pointer;
				}
				if(x!=startCord && !theTestCord){ // left/right. left is gauranteed to be something, so...
					//std::cout << "goe" << std::endl;
					(iterArray[i-1])->pointer->down->right = (iterArray[i])->pointer->down;
					(iterArray[i])->pointer->down->left = (iterArray[i-1])->pointer->down;
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
		madeMap = current; // We'll use this as temp this time.
		map* testMap;
		if(calcX>0){
			//std::cout << "go3" << std::endl;
			//std::cout << "bugFinder y: " << madeMap->y << " x: " << madeMap->x << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->left; // GO LEFT TO DEACTIVATE
				//std::cout << "bugFinder y: " << madeMap->y << " x: " << madeMap->x << std::endl;
			}
			//std::cout << "WENTBa" << std::endl;
			madeMap->deactivate();
			spareCord = *(madeMap->xConnector);
			//std::cout << "cord y: " << spareCord.y << " x: " << spareCord.x << std::endl;
			currCord = spareCord;
			//std::cout << "WENTBas" << std::endl;
			for (int i = 0; i < mapViewRadius; i++)
			{
				spareCord = *(spareCord.up);
				spareCord.pointer->deactivate();
				//std::cout << "cord y: " << spareCord.y << " x: " << spareCord.x << std::endl;
				currCord = *(currCord.down);
				currCord.pointer->deactivate();
				//std::cout << "cord y: " << currCord.y << " x: " << currCord.x << std::endl;
			}
			// now we set up list
			madeMap = current;
			//std::cout << "WENTBc" << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->right;  // GO RIGHT TO FIND/SEARCH/ACTIVATE
			}
			mapArray[mapViewRadius] = madeMap;
			spareCord = *(madeMap->xConnector);
			currCord = spareCord;
			//std::cout << "WENTBd" << std::endl;
			for (int i = 1; i <= mapViewRadius; i++)
			{
				spareCord = *spareCord.up;
				currCord = *currCord.down;
				mapArray[mapViewRadius-i] = spareCord.pointer;
				mapArray[mapViewRadius+i] = currCord.pointer;
			}
			x = current->x + mapViewRadius + 1;
			startCord = current->y - mapViewRadius;
			y = startCord - 1; // keep this in place for now
			for (int i = 0; i <= length; i++)
			{
				//std::cout << "WENTBe" << std::endl;
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
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
					currCord = {y,x,madeMap,NULL,NULL}; // We don't use this anyways anymore.
					insertCoordinateRelative(yIt,xIt,currCord);
					////std::cout << "GROGLEEEY " <<std::prev(yIt->end())->xConnector->x << std::endl;
					xIt->pointer->xConnector = xIt;
					xIt->pointer->yConnector = yIt;
					testMap = xIt->pointer;
					mapArray[i]->right = testMap; //coordinates connect
					testMap->left = mapArray[i];
				}
				//std::cout << "teertsaa y: " << mapArray[i]->right->y << " x: " << mapArray[i]->right->x << std::endl;
				if(y!=startCord){ // left/right. left is gauranteed to be something, so...
					mapArray[i-1]->right->down = mapArray[i]->right;
					mapArray[i]->right->up = mapArray[i-1]->right; 
					//std::cout << "WENTBer" << std::endl;
					mapArray[i-1]->right->xConnector->down = &(*(mapArray[i]->right->xConnector));
					//std::cout << "WENTBerr" << std::endl;
					mapArray[i]->right->xConnector->up = &(*(mapArray[i-1]->right->xConnector));
					//std::cout << "ERDUM " << mapArray[i]->left << std::endl;
				}
			}
			current = current->right; // we transfer over.
		}
		else if (calcX){
			//std::cout << "go4" << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				//std::cout << "WENTCaaa " << madeMap->right << std::endl;
				madeMap = madeMap->right; // GO RIGHT TO DEACTIVATE
			}
			//std::cout << "WENTCa" << std::endl;
			madeMap->deactivate();
			//std::cout << "WENTCb " << &(madeMap->xConnector) << std::endl;
			//std::cout << "WENTCba " << madeMap->xConnector->pointer << std::endl;
			spareCord = *(madeMap->xConnector);
			//std::cout << "WENTCc" << std::endl;
			currCord = spareCord;
			//std::cout << "WENT1" << std::endl;
			for (int i = 0; i < mapViewRadius; i++)
			{
				//std::cout << "a " << spareCord.up << std::endl;
				spareCord = *(spareCord.up);
				//std::cout << "b " << spareCord.pointer << std::endl;
				spareCord.pointer->deactivate();
				//std::cout << "c " << currCord.down << std::endl;
				currCord = *(currCord.down);
				//std::cout << "d" << std::endl;
				currCord.pointer->deactivate();
			}
			// now we set up list
			madeMap = current;
			//std::cout << "WENT2" << std::endl;
			for (int i = 0; i < mapViewRadius; i++){
				madeMap = madeMap->left;  // GO RIGHT TO FIND/SEARCH/ACTIVATE
			}
			mapArray[mapViewRadius] = madeMap;
			spareCord = *(madeMap->xConnector);
			//std::cout << "ALPHA Y: " << spareCord.y << " X: " << spareCord.x << std::endl;
			currCord = spareCord;
			//std::cout << "WENT3" << std::endl;
			for (int i = 1; i <= mapViewRadius; i++)
			{
				spareCord = *spareCord.up;
				//std::cout << "ALPHA Y: " << spareCord.y << " X: " << spareCord.x << std::endl;
				currCord = *currCord.down;
				//std::cout << "ALPHAB Y: " << currCord.y << " X: " << currCord.x << std::endl;
				mapArray[mapViewRadius-i] = spareCord.pointer;
				mapArray[mapViewRadius+i] = currCord.pointer;
			}
			x = current->x - mapViewRadius - 1;
			startCord = current->y - mapViewRadius;
			y = startCord - 1; // keep this in place for now
			//std::cout << "WENT4" << std::endl;
			for (int i = 0;  i <= length; i++)
			{
				y++;
				//std::cout << "WENT4er " << mapArray[i] << std::endl;
				testMap = mapArray[i]->left;
				//std::cout << "WENT4g" << std::endl;
				yIt=mapArray[i]->yConnector; // Because now we're RIGHT beside it.
				xIt=mapArray[i]->xConnector;
				if(testMap){
					//std::cout << "WENT4A" << std::endl;
					testMap->activate();
				}
				else if(find(y,x,yIt,xIt)){
					//std::cout << "WENT4B" << std::endl;
					testMap = xIt->pointer;
					mapArray[i]->left = testMap; //coordinates connect
					testMap->right = mapArray[i];
				}
				else{
					//std::cout << "WENT4C" << std::endl;
					madeMap = new map(seed,y,x,push,mapSide,tileSide,battlefieldSide,diagonal,debug);
					currCord = {y,x,madeMap,NULL,NULL}; // We don't use this anyways anymore.
					insertCoordinateRelative(yIt,xIt,currCord);
					xIt->pointer->xConnector = xIt;
					xIt->pointer->yConnector = yIt;
					testMap = xIt->pointer;
					mapArray[i]->left = testMap; //coordinates connect
					testMap->right = mapArray[i];
				}
				//std::cout << "teertsbb y: " << mapArray[i]->right->y << " x: " << mapArray[i]->right->x << std::endl;
				if(y!=startCord){ // left/right. left is gauranteed to be something, so...
					//std::cout << "GR8: Y: " << mapArray[i]->y << " X: " << mapArray[i]->x << std::endl;
					//std::cout << "GR8(-1): Y: " << mapArray[i-1]->y << " X: " << mapArray[i-1]->x << std::endl;
					mapArray[i-1]->left->down = mapArray[i]->left;
					mapArray[i]->left->up = mapArray[i-1]->left; 
					mapArray[i-1]->left->xConnector->down = &(*(mapArray[i]->left->xConnector));
					mapArray[i]->left->xConnector->up = &(*(mapArray[i-1]->left->xConnector));
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
	std::list<std::list<coordinate>>::iterator yy = cordMap.begin();
	std::list<coordinate>::iterator xx;
	std::list<std::list<coordinate>>::iterator yyEnd = prev(cordMap.end());
	std::list<coordinate>::iterator xxEnd;
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
			delete xx->pointer;
		}
		yy->clear();
	}
	cordMap.clear();
	if(debug){
		std::cout << "DONE DELETING PLAYERSPACE " << this << std::endl;
	}
}

// Precondition: You're on a valid tile.
unsigned int playerSpace::view(float heightOffset, int playerHeight, int mapView, bool circle, bool borders, bool playerSee, bool wallMode, std::vector<int>& viewMap, std::vector<int>* optimizeArray, std::vector<int>& memoryMap,int specialTiles, bool InvisibleAboveCustom, bool checkAll, bool debug){
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
				std::cout << "ester: " << wy << " " << mapSide <<std::endl;
				worldYOffset = wy/mapSide; // We determine how many worldspaces to left
				wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
				if(wy == mapSide){
					wy = 0;
					worldYOffset++;
				}
				
				////std::cout << "ALERT= " << ex << " " << mapSide << std::endl;
				worldXOffset = ex/mapSide;
				////std::cout << "ALERTD= " << worldXOffset << std::endl;
				ex -=(worldXOffset*mapSide);
				if(ex == mapSide){
					ex = 0;
					worldXOffset++;
				}
				////std::cout << usedMap->down << std::endl;
				////std::cout << usedMap->up << std::endl;
				////std::cout << usedMap->left << std::endl;
				////std::cout << usedMap->right << std::endl;
				std::cout << "worldY " << worldYOffset <<std::endl;
				while(worldYOffset){
					if(worldYOffset>0){
						////std::cout << "DIDd " << worldYOffset << " " << usedMap<< " " <<usedMap->down << " " << usedMap->up << " " << usedMap->left << " " << usedMap->right << std::endl;
						usedMap = usedMap->down;
						worldYOffset--;
					}
					else if(worldYOffset<0){
						////std::cout << "DIDu" << std::endl;
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
				viewMap.push_back(usedMap->heightMap[(wy*tileSideB)+ex]);
				memoryMap.push_back(usedMap->regionMemoryMap[(wy*tileSideB)+ex]);
				continue;
			}
			else{
				
				regionYOffset = wy/tileSide;
				////std::cout << "AGO1 " << wy << std::endl;
				wy-=(regionYOffset*tileSide);
				////std::cout << "AGO1 " << wy << std::endl;
				if(wy == tileSide){
					wy = 0;
					regionYOffset++;
				}
				regionXOffset = ex/tileSide;
				ex -=(regionXOffset*tileSide);
				if(ex == tileSide){
					ex = 0;
					regionXOffset++;
				}
				////std::cout<<regionXOffset<<" "<<regionYOffset<<" "<<tileSide<<std::endl;
				regionYOffset+=playerRegionY;
				regionXOffset+=playerRegionX; // get the regions
				worldYOffset = regionYOffset/mapSide; // We determine how many worldspaces to right
				regionYOffset-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
				if(regionYOffset == mapSide){
					regionYOffset = 0;
					worldYOffset++;
				}
				worldXOffset = (regionXOffset)/mapSide;
				regionXOffset -=(worldXOffset*mapSide);
				if(regionXOffset == mapSide){
					regionXOffset = 0;
					worldXOffset++;
				}
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
				viewMap.push_back(usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]);
				memoryMap.push_back(usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMemoryMap[(wy*tileSide)+ex]);
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
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, a, 0,debug);
			////std::cout << "SECOND " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, a, viewTileWidth-1,debug);
			////std::cout << "THIRD " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, 0, a,debug);
			////std::cout << "FOURTH " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth, playerHeight,viewTileWidth-1, a,debug);
		}
		////std::cout << "----END AROUND----" << std::endl;
		for(int y = 1; y < viewTileWidth-1; y++)
		{
			for (int x = 1; x < viewTileWidth-1; x++)
			{
				if(boolMap[(y*viewTileWidth)+x] != 1 || checkAll){ // This will save a function call, more efficient than in viewLine function check.
					viewLine(viewTileWidth,boolMap,heightOffset,viewMap,memoryMap,halfTileWidth,halfTileWidth,playerHeight, y, x,debug);
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
							worldYOffset = wy/mapSide; // We determine how many worldspaces to right
							wy-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							if(wy == mapSide){
								wy = 0;
								worldYOffset++;
							}
							worldXOffset = ex/mapSide;
							ex -=(worldXOffset*mapSide);
							if(ex == mapSide){
								ex = 0;
								worldXOffset++;
							}
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
							usedMap->regionMemoryMap[(wy*mapSide)+ex] = 1;
							////std::cout << "GI HERE " << theMap.bigMap[worldYOffset * worldSide + worldXOffset].regionMemoryMap[(wy*tileSide)+ex]<< std::endl;
							if(trigger){
								memoryMap[indexB] = usedMap->heightMap[(wy*mapSide)+ex]+1;
								continue;
							}
							memoryMap[indexB] = 0;
							continue;
					}
					else{
							regionYOffset = wy/tileSide;
							wy-=(regionYOffset*tileSide);
							if(wy == tileSide){
								wy = 0;
								regionYOffset++;
							}
							regionXOffset = ex/tileSide;
							ex -=(regionXOffset*tileSide);
							if(ex == tileSide){
								ex = 0;
								regionXOffset++;
							}
							regionYOffset+=playerRegionY;
							regionXOffset+=playerRegionX; // get the regions
							worldYOffset = regionYOffset/mapSide; // We determine how many worldspaces to
							regionYOffset-=(worldYOffset*mapSide); // Bring it back to index for appropiate region
							if(regionYOffset == mapSide){
								regionYOffset = 0;
								worldYOffset++;
							}
							worldXOffset = regionXOffset/mapSide;
							regionXOffset -=(worldXOffset*mapSide);
							if(regionXOffset == mapSide){
								regionXOffset = 0;
								worldXOffset++;
							}
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
							usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMemoryMap[(wy*tileSide)+ex] = 1;
							if(trigger){
								memoryMap[indexB] = usedMap->regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]+1;
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
