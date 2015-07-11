#include "Chip8.h"

//Using SDL and standard IO
#include "SDL2/SDL.h"
#include <stdio.h>

//Screen dimension constants
const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;
const int SCALING_FACTOR = 10;


const int SCREEN_WIDTH = CHIP8_WIDTH*SCALING_FACTOR;
const int SCREEN_HEIGHT = CHIP8_HEIGHT*SCALING_FACTOR;

Chip8 chip8;

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;


void setupGraphics() {
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } 
	else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
		else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            SDL_Delay( 2000 );
		   	//Destroy window
            SDL_DestroyWindow( window );

            //Quit SDL subsystems
            SDL_Quit();
        }
	}

}

int main(int argc, char **argv) 
{
	setupGraphics();
	//setupInput
	//
	//
	//Potentially this, but hopefully all in constructor.
	//chip8.initialize();
	//TODO decide on seperation of file handling from 
	//buffer handling chip8.loadGame("pong");

	//TODO add loop into workflow.
	//for(;;)
	//{
		chip8.emulateCycle();

		//If draw flag set, update screen.
		if (chip8.getDrawFlag()){
			//TODO drawGraphics();
		}

		// Store key press state.
		chip8.setKeys();
	//}
	return 0;
}

