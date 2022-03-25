#ifndef _INITIALIZE_
#define _INITIALIZE_
#include "gameplay.h"
#include <SDL.h>
#include <iostream>
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

bool init(SDL_Window* gWindow, SDL_Renderer* &renderer)
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1,
                                          SDL_RENDERER_ACCELERATED |
                                          SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL){
                printf("SDL_CreateRenderer Error : %s\n", SDL_GetError() );
                success = false;
			}
		}
	}

	return success;
}

void run(SDL_Renderer* &renderer, bool &quit){
    //Gameplay Gameplay(renderer);
    Gameplay Gameplay;
    Gameplay.width = SCREEN_WIDTH/(Gameplay.board_width+2);
    Gameplay.height = SCREEN_HEIGHT/(Gameplay.board_height+2);
    Gameplay.draw_board(renderer);
    Gameplay.createboardstate();
    SDL_Event e;
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
                else if (e.type == SDL_MOUSEBUTTONDOWN){
                      Gameplay.getcoordinate();
                      Gameplay.update(renderer);
                      if (Gameplay.check_win() == "Player 1 win"){
                        std::cout << "Player 1 win";
                        //restart game..
                    }
                        else if (Gameplay.check_win() == "Player 2 win"){
                            std::cout << "Player 2 win";
                            //restart game or sth
                        }
                            else if (Gameplay.check_win() == "Tie"){
                                std::cout << "Tie";
                                //restart or not
                            }
            }
        }
    }


}

#endif


