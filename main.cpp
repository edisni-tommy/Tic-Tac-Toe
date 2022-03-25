#include <stdio.h>
#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include "initialize.h"


int main( int argc, char* args[] ){
    SDL_Window* gWindow = NULL;
    SDL_Renderer* renderer = NULL;
	if(!init(gWindow,renderer))
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	    bool quit = false;
	    while (!quit){
            run(renderer, quit);
        }
	}
    SDL_DestroyWindow(gWindow);
	SDL_Quit();
	return 0;
}
