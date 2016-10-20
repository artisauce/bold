#include "worldMap.hpp"
#include <SDL2/SDL.h>
// Current compile: clang maptest.cpp worldMap.cpp map.cpp tile.cpp toolkit.cpp battleField.cpp -lm -lstdc++ -std=c++11

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

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
		gWindow = SDL_CreateWindow( "MAP MOVE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 0, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
	}

	return success;
}

int main( int argc, char* args[] )
{
	std::ios::sync_with_stdio(false); // This allows fast output for the move demo.
    srand(time(NULL));
    bool debug = false;
    bool diagonal = true;
    double pushCoefficient = 0.1;
    size_t worldMapSide = 2;
    size_t mapSide = 50;
    size_t tileSide = 16;
    size_t battlefieldSide = 64;
    std::vector<std::string> tileSet;
    tileSet.push_back("@"); // as -3. Player
    tileSet.push_back("~"); // as -4. Ground
    tileSet.push_back("T"); // as -5. Tree
    worldMap newMap(rand(), pushCoefficient, worldMapSide, mapSide, tileSide, battlefieldSide,  diagonal, debug);
    if(debug){
        std::cout << "--- EVERYTHING HAS BEEN MADE --- " << std::endl;
    }
    std::vector<int> viewer;
    unsigned int sider;
	 int playerXRegion = 25;
	int playerYRegion = 25;
	 int playerXTile = 11;
	int playerYTile = 11;
	int viewRadius = 42;
	unsigned int mapView = false;
    sider = view(newMap.bigMap[0],playerYRegion,playerXRegion,playerYTile,playerXTile,viewRadius,mapView,true,false,true,false,viewer);
    std::cout << " VECTOR MAP " << std::endl;
    printMapVector(viewer,sider,tileSet);
    std::cout << " FULL MAP " << std::endl;
    printMap(newMap.bigMap[0].heightMap,mapSide,tileSet);
	// Top, should be barren snowland/rocky.
	battlefield newBattle(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)+(mapSide/2)]),tileSide/2,tileSide/2);
	printMap(newBattle.battleMap,battlefieldSide,tileSet);
	// A bit from the peak, less trees.
	battlefield newBattleTwo(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)+(mapSide/2)+2]),tileSide/2,tileSide/2);
	printMap(newBattleTwo.battleMap,battlefieldSide,tileSet);
	// On the mainland, most trees.
	battlefield newBattleThree(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)+(mapSide/4)]),tileSide/2,tileSide/2);
	printMap(newBattleThree.battleMap,battlefieldSide,tileSet);
	// Ocean. Should be nothing.
	battlefield newBattleFour(&(newMap.bigMap[0].regionMap[((mapSide/2)*mapSide)]),tileSide/2,tileSide/2);
	printMap(newBattleFour.battleMap,battlefieldSide,tileSet);
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
			//Main loop flag
			bool quit = false;

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
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							if(!playerYTile){
								playerYRegion--;
								playerYTile = tileSide-1;
							}	
							else{
								playerYTile--;
							}
							break;

							case SDLK_DOWN:
							if(playerYTile==tileSide-1){
								playerYRegion++;
								playerYTile = 0;
							}	
							else{
								playerYTile++;
							}
							break;

							case SDLK_LEFT:
							if(!playerXTile){
								playerXRegion--;
								playerXTile = tileSide-1;
							}	
							else{
								playerXTile--;
							}
							break;

							case SDLK_RIGHT:
							if(playerXTile==tileSide-1){
								playerXRegion++;
								playerXTile = 0;
							}	
							else{
								playerXTile++;
							}
							break;

							case SDLK_m:
							mapView=!mapView;
							SDL_Delay(500);
							break;

							default:
							break;
						}
						viewer.clear();
						sider = view(newMap.bigMap[0], playerYRegion, playerXRegion, playerYTile, playerXTile, viewRadius,mapView,true,false,true,true,viewer);
						printMapVector(viewer,sider,tileSet);
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
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

// TODO:
// Have battlefields stored in tiles after a battle to re-use, as battles can impact terrain. (!)
