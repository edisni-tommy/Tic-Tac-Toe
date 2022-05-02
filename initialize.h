#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "computer.h"
#include "button.h"
#include <stdio.h>
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
                else
                    {
                        //Initialize renderer color
                        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                        //Initialize PNG loading
                        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
                        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
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


void run(SDL_Renderer* &renderer, bool &quit){
    LTexture MainMenu;
    if (!MainMenu.loadMedia(renderer, "pictures/menu.png")){
        printf( "Failed to load media!\n" );
    }
        else {
            SDL_SetRenderDrawColor(renderer, 33, 40, 69, 4);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,MainMenu.gTexture,NULL,NULL);
            SDL_RenderPresent(renderer);
            Button PlayWithComputer(PLAY_WITH_COMPUTER_POSX,PLAY_WITH_COMPUTER_POSY);
            Button PlayWithHuman(PLAY_WITH_HUMAN_POSX,PLAY_WITH_HUMAN_POSY);
            Button Settings(SETTINGS_POSX,SETTINGS_POSY);
            Button EXIT(EXIT_POSX,EXIT_POSY);
            LTexture MenuButtons;
            MenuButtons.loadMedia(renderer,"pictures/menubutton.png");
            SDL_Event e;
            while (!quit){
                    while (SDL_PollEvent(&e) != 0){
                        if (e.type == SDL_QUIT){
                            quit = true;
                        }
                        if (PlayWithComputer.IsInside(&e,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEMOTION:
                                    {
                                    SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,0,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithComputer.render(&srRect,renderer,MenuButtons);
                                    SDL_RenderPresent(renderer);
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                {
                                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                    SDL_RenderClear(renderer);
                                    Computer Computer;
                                    Computer.width = SCREEN_WIDTH/(Computer.board_width+2);
                                    Computer.height = SCREEN_HEIGHT/(Computer.board_height+2);
                                    Computer.run_computer(renderer,quit);
                                    break;

                                }
                            }

                        }
                            else if (PlayWithHuman.IsInside(&e,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT)){
                                switch (e.type)
                                {
                                    case SDL_MOUSEMOTION:
                                        {
                                        SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,COMMON_BUTTON_HEIGHT,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT};
                                        PlayWithHuman.render(&srRect,renderer,MenuButtons);
                                        SDL_RenderPresent(renderer);
                                        break;
                                        }
                                    case SDL_MOUSEBUTTONDOWN:
                                        {
                                            Gameplay Gameplay;
                                            Gameplay.width = SCREEN_WIDTH/(Gameplay.board_width+2);
                                            Gameplay.height = SCREEN_HEIGHT/(Gameplay.board_height+2);
                                            Gameplay.run_vshuman(renderer,quit);
                                            break;
                                        }
                                }


                            }
                                else if (Settings.IsInside(&e,SETTING_WIDTH,COMMON_BUTTON_HEIGHT)){
                                    switch (e.type)
                                    {
                                        case SDL_MOUSEMOTION:
                                            SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,COMMON_BUTTON_HEIGHT*2,SETTING_WIDTH,COMMON_BUTTON_HEIGHT};
                                            Settings.render(&srRect,renderer,MenuButtons);
                                            SDL_RenderPresent(renderer);
                                            break;
                                    }
                                }
                                    else if (EXIT.IsInside(&e,EXIT_WIDTH,COMMON_BUTTON_HEIGHT)){
                                        switch (e.type){
                                            case SDL_MOUSEMOTION:
                                                {
                                                SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,COMMON_BUTTON_HEIGHT*3,EXIT_WIDTH,COMMON_BUTTON_HEIGHT};
                                                EXIT.render(&srRect,renderer,MenuButtons);
                                                SDL_RenderPresent(renderer);
                                                break;
                                                }
                                            case SDL_MOUSEBUTTONDOWN:
                                                quit = true;
                                                break;
                                        }

                                    }
                                        else {
                                                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                                SDL_RenderClear(renderer);
                                                SDL_SetRenderDrawColor(renderer, 33, 40, 69, 4);
                                                SDL_RenderClear(renderer);
                                                SDL_RenderCopy(renderer,MainMenu.gTexture,NULL,NULL);
                                                SDL_RenderPresent(renderer);

                                        }
                    }
            }
          }

}

#endif


