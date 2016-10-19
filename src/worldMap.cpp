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
unsigned int view(	map& theMap,  int regionY, int regionX, 
					 int tileY, int tileX, // Why int's? Because we'll want to still display even in negatives,
								// top/left/topleft from the map. Don't worry about it too much.
					int viewRadius, bool mapView, bool circle, bool borders, bool playerSee, bool wallMode, std::vector<int>& viewMap){
	// why there's problems: angles, viewing from a platau, you wouldn't be able to see below, from side, you would.
	// view up: algorithm that's efficient. returns angles, compares. see notes in THE book.
	int viewTileWidth = (viewRadius*2)+1;
	int tileSide = theMap.tileSide;
	int mapSide = theMap.mapSide;
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
	for (int y = -(viewTileWidth/2); y <= (viewTileWidth/2); y++)
	{
		for (int x = -(viewTileWidth/2); x <= (viewTileWidth/2); x++)
		{
			if(circle){
				float A = (float)x+(float)tileX;
				float B = (float)y+(float)tileY;
				if(A < tileX){
					A++;
				}
				if(B < tileY){
					B++;
				}
				B = B - centerPixelY; // Rogue bug: Found out these were swapped.
				A = A - centerPixelX; // See? Takes hours just to finds these...
				float difference = (A*A)+(B*B);
				if(difference > (viewRadius*viewRadius)){
					//std::cout << "G" << std::endl;
					if(x>=0){
						viewMap.push_back(-2);
					}
					else{
						viewMap.push_back(-1);
					}
					continue;
					//std::cout << "GO" << std::endl;
				}
			}
			if(borders){
				if( ((y+tileY)%tileSide) == 0 || ((x+tileX)%tileSide) == 0){
					viewMap.push_back(-1);
					continue;
				}
			}
			int wy = y+tileY;
			int ex = x+tileX;
			int regionYOffset = 0;
			int regionXOffset = 0;
			if(mapView){
				if(wy<0 || wy >= tileSide || ex < 0 || ex >= tileSide){
					viewMap.push_back(0);
					continue;
				}
				viewMap.push_back(theMap.heightMap[(wy*tileSide)+ex]);
				continue;
			}
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
			regionXOffset+=regionX;
			if(regionXOffset<0 || regionYOffset<0 || regionXOffset >= mapSide || regionYOffset >=mapSide){
				//std::cout << "GO" << std::endl;
				viewMap.push_back(0);
				continue;
			}
			//if(theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] > 9){
				//std::cout << theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex] << std::endl;
				//std::cout << "---- SIDE: " << tileSide << " X: " << x << " Y: " << y << " EX: "<< ex << " WY: " << wy << std::endl;
			//}
			viewMap.push_back(theMap.regionMap[(regionYOffset*mapSide) + regionXOffset].tileMap[(wy*tileSide)+ex]);

		}
	}
	bool boolMap[viewTileWidth*viewTileWidth];
	int middle = (viewTileWidth/2);
	if(wallMode && !borders){ // for the time being, it's incompatible with borders
		for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
		{
			boolMap[i] = false;
		}
		boolMap[(middle*viewTileWidth)+middle] = true;
		for(int a = 0; a < viewTileWidth; a++)
		{
			// Getting most of them with this is a good, efficient idea and method.
			viewLine(viewTileWidth,boolMap,viewMap,middle,middle, a, 0);
			viewLine(viewTileWidth,boolMap,viewMap,middle,middle, a, viewTileWidth-1);
			viewLine(viewTileWidth,boolMap,viewMap,middle,middle, 0, a);
			viewLine(viewTileWidth,boolMap,viewMap,middle,middle, viewTileWidth-1, a);
		}
		for(int y = 1; y < viewTileWidth-1; y++)
		{
			for (int x = 1; x < viewTileWidth-1; x++)
			{
				if(!boolMap[(y*viewTileWidth)+x]){ // This will save a function call, more efficient than in viewLine function check.
					viewLine(viewTileWidth,boolMap,viewMap,middle,middle, y, x);
				}
				//std::cout << y << " " << x << std::endl;
			}
		}
		for (int i = 0; i < viewTileWidth*viewTileWidth; i++)
		{
			if(!boolMap[i]){ // Time to implement
					viewMap[i] = -1;
			}
		}
	}
	if(playerSee){
		viewMap[(middle*viewTileWidth)+middle] = -3;
	}
	return viewTileWidth;
}
