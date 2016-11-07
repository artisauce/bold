#include "worldMap.hpp"
worldMap::worldMap(unsigned int seedInput, const double pushInput, size_t worldMapSideInput, size_t mapSideInput, 
	size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput):
	seed(seedInput),
	push(pushInput),
	worldMapSide(worldMapSideInput),
	mapSide(mapSideInput),
	tileSide(tileSideInput),
	battlefieldSide(battlefieldSideInput),
	diagonal(diagonalInput),
	debug(debugInput)
{
	if(debug){
    	std::cout << "CREATING WORLDMAP " << this << std::endl; 
    }
	srand(seed);
	seedMap = new int[worldMapSide*worldMapSide];
	bigMap.reserve(worldMapSide*worldMapSide);
	for (int i = 0; i < worldMapSide*worldMapSide; ++i)
	{
		seedMap[i] = rand();
	}
    for (int i = 0; i < worldMapSide*worldMapSide; ++i)
	{
		bigMap.push_back(map(seedMap[i],this,((int)(i/worldMapSide)),i%worldMapSide)); 
		if(debug){
			std::cout << "WORLDMAP " << this << ": #" << i << " MAP CREATED: " << &(bigMap[i]) << std::endl; 
		}
	}
	if(debug){
    	std::cout << "CREATED WORLDMAP " << this << std::endl; 
    }
}

worldMap::~worldMap(){
	if(debug){
		std::cout << "DELETING WORLDMAP " << this << std::endl;
	}
	delete[] seedMap;
	bigMap = std::vector<map>();
	if(debug){
		std::cout << "DONE DELETING WORLDMAP " << this << std::endl;
	}
}

// Precondition: You're on a valid tile.
unsigned int view(worldMap& theMap, int worldY, int worldX,  int regionY, int regionX, 
					 int tileY, int tileX, // Why int's? Because we'll want to still display even in negatives,
								// top/left/topleft from the map. Don't worry about it too much.
					int viewRadius, float heightOffset, int playerHeight, bool mapView, bool circle, bool borders, bool playerSee, bool wallMode, std::vector<int>& viewMap, std::vector<int>* optimizeArray, int specialTiles, bool InvisibleAboveCustom, bool checkAll, bool debug){
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
					viewMap.push_back(-3);
					continue;
					//std::cout << "GO" << std::endl;
				}
			}
			if(borders){
				if( ((y+tileY)%tileSide) == 0 || ((x+tileX)%tileSide) == 0){
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
					viewMap.push_back(0);
					continue;
				}
				//std::cout << theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex] << std::endl;
				viewMap.push_back(theMap.bigMap[worldYOffset * worldSide + worldXOffset].heightMap[(wy*tileSide)+ex]);
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
						viewMap.push_back(0);
						continue;
					}
					viewMap.push_back(theMap.bigMap[worldYOffset*worldSide + worldXOffset].regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]);
			}
			//if(theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] > 9){
				//std::cout << theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] << std::endl;
				//std::cout << "---- SIDE: " << tileSide << " X: " << x << " Y: " << y << " EX: "<< ex << " WY: " << wy << std::endl;
			//}
		}
	}
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
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,halfTileWidth,halfTileWidth,playerHeight, a, 0,debug);
			//std::cout << "SECOND " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,halfTileWidth,halfTileWidth,playerHeight, a, viewTileWidth-1,debug);
			//std::cout << "THIRD " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,halfTileWidth,halfTileWidth,playerHeight, 0, a,debug);
			//std::cout << "FOURTH " << std::endl;
			viewLine(viewTileWidth,boolMap,heightOffset,viewMap,halfTileWidth,halfTileWidth, playerHeight,viewTileWidth-1, a,debug);
		}
		//std::cout << "----END AROUND----" << std::endl;
		for(int y = 1; y < viewTileWidth-1; y++)
		{
			for (int x = 1; x < viewTileWidth-1; x++)
			{
				if(boolMap[(y*viewTileWidth)+x] != 1 || checkAll){ // This will save a function call, more efficient than in viewLine function check.
					viewLine(viewTileWidth,boolMap,heightOffset,viewMap,halfTileWidth,halfTileWidth,playerHeight, y, x,debug);
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
	if(optimizeArray != NULL){
		int lastX;
		int firstX;
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
	if(playerSee){
		viewMap[(halfTileWidth*viewTileWidth)+halfTileWidth] = (-specialTiles)-1;
	}
	return viewTileWidth;
}
