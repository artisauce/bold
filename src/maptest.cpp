#include "playerSpace.hpp"
#include "SDL.h"
#include "SDL_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

//Starts up SDL and creates window
bool init();

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// This shows nice printout of map. It's nice.
void displayStuff(int sider, std::vector<int>& map, int maxHeight, int specialTiles){
	// Clears screen
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer );
	SDL_Rect fillRect;
	// We want to calculate these only once.
	int tileWidth = SCREEN_WIDTH/sider;
	int tileWidthM = (SCREEN_WIDTH/sider) -1;
	int tileHeight = SCREEN_HEIGHT/sider;
	int tileHeightM = (SCREEN_HEIGHT/sider) -1;
	int startX = (SCREEN_WIDTH/2)-((tileWidth*sider)/2);
	int startY = (SCREEN_HEIGHT/2)-((tileHeight*sider)/2);
	int index;
	for(int y = 0;y<sider;y++){
		for(int x = 0;x<sider;x++){
			index = (y*sider) + x;
			fillRect = {startX+(tileWidth*x), startY+(tileHeight*y), tileWidthM, tileHeightM};
			if(map[index] > 0){
			//RGBA
				if(map[index]<=maxHeight){
		       	 		SDL_SetRenderDrawColor( gRenderer, 
								(int)(255.0*sqrt(((float)map[index])/(float)maxHeight)), 
								255, 
								(int)(255.0*((float)(map[index])/(float)maxHeight)), 
								255 ); // Set to variable degree of GREEEEN
				}
				else {
					SDL_SetRenderDrawColor( gRenderer, 255.0, 255.0, 255.0, 255 ); // Snow white
				}
			}
			else if(map[index] == 0){ // BLUUUEEEE
		       	 SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 255 ); 
			}
			else if(map[index] == (-specialTiles)-1){ /// Purple. That's you.
		       	 SDL_SetRenderDrawColor( gRenderer, 255, 0, 255, 255 ); 
			}
			else {	// Black. That's everything else.
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
			}
			// Fill in with color.
		       	SDL_RenderFillRect( gRenderer, &fillRect );
		}
	}
	//Update screenos
	SDL_RenderPresent( gRenderer );
}

// This shows nice printout of map. It's nice.
void displayStuffOptimized(int sider, std::vector<int>& map, int maxHeight, std::vector<int>& optimizeArray,
	std::vector<int>& memoryMap,int specialTiles){
	// Clears screen
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer );
	SDL_Rect fillRect;
	// We want to calculate these only once.
	int tileWidth = SCREEN_WIDTH/sider;
	int tileWidthM = (SCREEN_WIDTH/sider) -1;
	int tileHeight = SCREEN_HEIGHT/sider;
	int tileHeightM = (SCREEN_HEIGHT/sider) -1;
	int startX = (SCREEN_WIDTH/2)-((tileWidth*sider)/2);
	int startY = (SCREEN_HEIGHT/2)-((tileHeight*sider)/2);
	int index;
	int optimizeIndex = 0;
	int red;
	int green;
	int blue;
	int grayscale;
	for(int y = 0;y<sider;y++){
		for(int x = optimizeArray[optimizeIndex++];x<sider;x++){ //http://www.embedded.com/design/programming-languages-and-tools/4410601/Pre-increment-or-post-increment-in-C-C-
			index = (y*sider) + x;
			//std::cout << y << ": " << map[index] << std::endl;
			if(map[index] == -4){
				break;
			}
			fillRect = {startX+(tileWidth*x), startY+(tileHeight*y), tileWidthM, tileHeightM};
			if(map[index] > 0){
			//RGBA
				if(map[index]<=maxHeight){
					red =  (int)(255.0*sqrt(((float)map[index])/(float)maxHeight));
					green = 255;
					blue = (int)(255.0*sqrt(((float)map[index])/(float)maxHeight));
		       	 		SDL_SetRenderDrawColor( gRenderer, 
								red, 
								green, 
								blue, 
								255 ); // Set to variable degree of GREEEEN
				}
				else {
					SDL_SetRenderDrawColor( gRenderer, 255.0, 255.0, 255.0, 255 ); // Snow white
				}
			}
			else if(map[index] == 0){ // BLUUUEEEE
		       	 SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 255 ); 
			}
			else if(map[index] == (-specialTiles)-1) { /// Purple. That's you.
		       	 SDL_SetRenderDrawColor( gRenderer, 255, 0, 255, 255 ); 
			}
			else if(memoryMap.size() && memoryMap[index]){ // pro short circuit l33t get rekt
				if(memoryMap[index] == 1){
					SDL_SetRenderDrawColor( gRenderer, 0, 0, 255*0.5, 255 ); 
				}
				else{
					// Grayscale channals: red = 30%, green = 59%, blue = 11%
					// And we scale brightness down a bit just because.
					red =  (int)(255.0*sqrt(((float)(memoryMap[index]-1))/(float)maxHeight));
					green = 255.0;
					blue = (int)(255.0*sqrt(((float)(memoryMap[index]-1))/(float)maxHeight));
					//grayscale = (red+green+blue)*0.5;
					SDL_SetRenderDrawColor( gRenderer, 
									red*0.5, 
									green*0.5, 
									blue*0.5, 
									255 ); // Set to variable degree of GREEEEN
				}

			}
			else if(map[index] == -2) { /// Above ground invisible. That's you.
		       	 SDL_SetRenderDrawColor( gRenderer, 89, 169, 215, 255 ); 
			}
			else {	// Black. That's everything else. We need this because of black between tile display.
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
			}
			// Fill in with color.
		       	SDL_RenderFillRect( gRenderer, &fillRect );
		}
	}
	//Update screenos
	SDL_RenderPresent( gRenderer );
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "MAP MOVE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

int main( int argc, char* args[] )
{
	std::ios::sync_with_stdio(false); // This allows fast output for the move demo.
    srand(time(NULL));
	// Constants.
    bool debug = false;
    bool diagonal = true;
    double pushCoefficient = 0.1;
    size_t mapSide = 64;
    size_t tileSide = 16;
    size_t battlefieldSide = 32;
    std::vector<std::string> tileSet;
    tileSet.push_back("@"); // as -4. Player
    tileSet.push_back("~"); // as -5. Ground
    tileSet.push_back("T"); // as -6. Tree
	int specialTiles = 4; // -1 (empty/hidden space) -2 (alternate hidden space), -3 (circleInvsi) ,-4 (skipline)
	int viewRadius = 35;
	//this seed needs investigating: 6829467
    playerSpace playSpace(rand(), viewRadius, pushCoefficient, mapSide, tileSide, battlefieldSide,  diagonal, debug);
	
	//playerSpace(unsigned int seedInput, int playerViewRadius, const double pushInput, size_t mapSideInput, 
	//size_t tileSideInput, size_t battlefieldSideInput, const bool diagonalInput, const bool debugInput)
    if(debug){
        std::cout << "--- EVERYTHING HAS BEEN MADE --- " << std::endl;
    }
    std::vector<int> viewer;
	// More constants.
    unsigned int sider;
	 playSpace.playerRegionX = mapSide/2;
	playSpace.playerRegionY = mapSide/2;
	playSpace.playerTileX = tileSide/2;
	playSpace.playerTileY = tileSide/2;
	playSpace.travel(0, 0, rand());
	 //playSpace.playerTileX = 11;
	//playSpace.playerTileY = 11;
	//int viewRadius = 9;
	float heightOffset = 0.5; // Ideal?
	int mapView = 1;
	bool seeAboveInvisible = false;
	bool circleView = false;
	bool mapDebug = false;
	bool flyMode = false;
	bool checkRadius = false;
	bool checkAll = true; // See notes in viewline.
	bool memoryMode = false; // See what you saw before.
	int calcHeight; // For calculating height.
	std::vector<int> optimizeArray;
	std::vector<int> memoryMap;
	std::cout << "Got here" << std::endl;
    	viewer.clear(); // Clear print console map.
	optimizeArray.clear(); // Clears optimization
	memoryMap.clear();
	//playerSpace::view(float heightOffset, int playerHeight, int mapView, bool circle, bool borders, bool playerSee, bool wallMode, std::vector<int>& viewMap, std::vector<int>* optimizeArray, std::vector<int>& memoryMap,int specialTiles, bool InvisibleAboveCustom, bool checkAll, bool debug){
	sider = playSpace.view(heightOffset,mapView,circleView,false,true,true,viewer,&optimizeArray,memoryMap,specialTiles,
	seeAboveInvisible,checkAll,mapDebug); // Sider is length.
	
	std::cout << "Got through" << std::endl;
 //    std::cout << " VECTOR MAP " << std::endl;
 //    printMapVector(viewer,sider,tileSet);
 //    std::cout << " FULL MAP " << std::endl;
 //    printMap(newMap.bigMap[0].heightMap,mapSide,tileSet);
	// // Top, should be barren snowland/rocky.
	// battlefield newBattle(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)+(mapSide/2)]),tileSide/2,tileSide/2);
	// printMap(newBattle.battleMap,battlefieldSide,tileSet);
	// // A bit from the peak, less trees.
	// battlefield newBattleTwo(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)+(mapSide/2)+2]),tileSide/2,tileSide/2);
	// printMap(newBattleTwo.battleMap,battlefieldSide,tileSet);
	// // On the mainland, most trees.
	
	//battlefield newBattleThree(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)+(mapSide/4)]),tileSide/2,tileSide/2,specialTiles);
	//printMap(newBattleThree.battleMap,battlefieldSide,tileSet,specialTiles);

	// // Ocean. Should be nothing.
	// battlefield newBattleFour(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)]),tileSide/2,tileSide/2);
	// printMap(newBattleFour.battleMap,battlefieldSide,tileSet);
	// //Start up SDL and create window
	int yMode = 0;
	int xMode = 0;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
			printf( "Initialized!\n" );
			displayStuffOptimized(sider,viewer,8,optimizeArray,memoryMap,specialTiles); // For initial present
			//Main loop flag
			bool quit = false;
			bool updateScreen = false;
			int playerMove = 1;
			//Event handler
			SDL_Event e;
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
						std::cout<<"QUIT"<<std::endl;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						updateScreen = true;
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							std::cout << "UP" << std::endl;
							yMode=-1;
							break;

							case SDLK_DOWN:
							std::cout << "DOWN" << std::endl;
							yMode=1;
							break;

							case SDLK_LEFT:
							std::cout << "LEFT" << std::endl;
							xMode=-1;
							break;

							case SDLK_RIGHT:
							std::cout << "RIGHT" << std::endl;
							xMode=1;
							break;

							// KEYPAD MOVEMENT
							case SDLK_KP_9:
							std::cout << "UP-RIGHT" << std::endl;
							xMode=1;
							yMode=-1;
							break;

							case SDLK_KP_8:
							std::cout << "UP" << std::endl;
							yMode=-1;
							break;

							case SDLK_KP_7:
							std::cout << "UP-LEFT" << std::endl;
							yMode=-1;
							xMode=-1;
							break;


							case SDLK_KP_6:
							std::cout << "RIGHT" << std::endl;
							xMode=1;
							break;

							case SDLK_KP_4:
							std::cout << "LEFT" << std::endl;
							xMode=-1;
							break;

							case SDLK_KP_3:
							std::cout << "DOWN-RIGHT" << std::endl;
							xMode=1;
							yMode=1;
							break;

							case SDLK_KP_2:
							std::cout << "DOWN" << std::endl;
							yMode=1;
							break;

							case SDLK_KP_1:
							std::cout << "DOWN-LEFT" << std::endl;
							yMode=1;
							xMode=-1;
							break;

							case SDLK_m: // Toggle map
							mapView = (mapView+1)%3;
							std::cout << "mapView: " << mapView << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_s: // Toggle custom see above invisible
							seeAboveInvisible=!seeAboveInvisible;
							std::cout << "seeAboveInvisible: " << seeAboveInvisible << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_r: // Toggle custom see above invisible
							circleView=!circleView;
							std::cout << "circleView: " << circleView << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_f: // Toggle custom see above invisible
							playSpace.flyMode=(playSpace.flyMode+1)%3;
							std::cout << "flyMode: " << playSpace.flyMode << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_e: // Toggle map debug. Should probably turn off see above invisible first.
							mapDebug=!mapDebug;
							std::cout << "mapDebug: " << mapDebug << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_q: // Toggle checkAll. See viewline func
							checkAll=!checkAll;
							std::cout << "checkAll: " << checkAll << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_z: // Toggle checkAll. See viewline func
							memoryMode=!memoryMode;
							std::cout << "memoryMode: " << memoryMode << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_MINUS: // Decrease view
							checkRadius = true;
							playSpace.tileViewRadius--;
							playSpace.regionViewRadius--;
							std::cout << "regionViewRadius: " << playSpace.regionViewRadius << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_EQUALS: // Increase view
							checkRadius = true;
							playSpace.tileViewRadius++;
							playSpace.regionViewRadius++;
							std::cout << "regionViewRadius: " << playSpace.regionViewRadius << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_RIGHTBRACKET: // Increase view height from base
							heightOffset += 0.1;
							std::cout << "heightOffset: " << heightOffset << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_LEFTBRACKET: // Decrease view height from base
							heightOffset -= 0.1;
							std::cout << "heightOffset: " << heightOffset << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_PERIOD: // Toggle checkAll. See viewline func
							playSpace.playerZ++;
							std::cout << "playerZ: " << playSpace.playerZ << std::endl;
							SDL_Delay(250);
							break;

							case SDLK_COMMA: // Toggle checkAll. See viewline func
							playSpace.playerZ--;
							std::cout << "playerZ: " << playSpace.playerZ << std::endl;
							SDL_Delay(250);
							break;

							default:
							updateScreen = false;
							break;
						}
						if(updateScreen){
							// Move Y
							playSpace.travel(yMode, xMode, mapView);
							yMode = 0;
							xMode = 0;
							// Done move.
							std::cout << "PlayerZ: " << playSpace.playerZ << std::endl;
							std::cout << "tileY: " << playSpace.playerTileY << " tileX: " << playSpace.playerTileX << std::endl;
							std::cout << "regionY: " << playSpace.playerRegionY << " regionX: " << playSpace.playerRegionX << std::endl;
							std::cout << "worldY: " << playSpace.current->y << " worldX: " << playSpace.current->x << std::endl;
							std::cout << "Currseed: " << playSpace.current->seed << std::endl;
							if(checkRadius){
								playSpace.adjustView();
								checkRadius=false;
							}
							//for (int i = 0; i < playSpace.mapSide*playSpace.mapSide; ++i){
							//	for (int e = 0; e < playSpace.tileSide*playSpace.tileSide; ++e)
							//	{
							//		bronze.push_back(playSpace.current->regionMap[i].tileMap[e]);
							//	}
							//}
							//if(gold.size() != 0){
							//	for (int i = 0; i < (playSpace.mapSide*playSpace.mapSide)*(playSpace.tileSide*playSpace.tileSide); i++){
							//		if(bronze[i] != gold[i]){
							//			std::cout <<"====== "<<  i << " ========" << std::endl;
							//		}
							//	}
							//}
							////std::cout << gold.size() << " " << bronze.size() << std::endl;
							//gold.clear();
							//gold = bronze;
							//std::cout << gold.size() << " " << bronze.size() << std::endl;
							//bronze.clear();
							//std::cout << gold.size() << " " << bronze.size() << std::endl;
							viewer.clear(); // Clear print console map.
							optimizeArray.clear(); // Clears optimization
							memoryMap.clear();
							//std::cout << "ERROR?" << std::endl;
							sider = playSpace.view(heightOffset,mapView,circleView,false,true,true, viewer,&optimizeArray,memoryMap,specialTiles,seeAboveInvisible,checkAll,mapDebug); // Sider is length.
							/*
							for(int r = 0; r <= (playSpace.mapSide)*playSpace.mapSide; r++){
								if(r%playSpace.mapSide == 0){
									std::cout << std::endl;
								}
								if(r/playSpace.mapSide == playSpace.playerRegionY && r%playSpace.mapSide == playSpace.playerRegionX){
									std::cout << "@";
								}
								else
								std::cout << playSpace.current->heightMap[r];
							}
							*/
							//printMapVector(viewer,sider,tileSet); // This for console.
							if(!memoryMode){
								memoryMap.clear();
							}
								displayStuffOptimized(sider,viewer,8,optimizeArray,memoryMap,specialTiles); // This for graphocs.

						}
					}
				}

				//Apply the current image
				//SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
	}

	//Free resources and close SDL
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return 0;
}

// TODO:
// Have battlefields stored in tiles after a battle to re-use, as battles can impact terrain. (!)
// Viewline changes - double/triple line check.
