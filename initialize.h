#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "computer.h"
#include "button.h"
#include <stdio.h>
#include <iostream>
#include <SDL_mixer.h>


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
                        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                        {
                            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
            Button THRxTHR(THRxTHR_POSX,THRxTHR_POSY);
            Button FIVExFIVE(FIVExFIVE_POSX,FIVExFIVE_POSY);
            Button NINExNINE(NINExNINE_POSX,NINExNINE_POSY);
            Button TWELVExTWELVE(TWELVExTWELVE_POSX,TWELVExTWELVE_POSY);
            Button Back(BACK_BUTTON_POSX,BACK_BUTTON_POSY);
            LTexture MenuButtons;
            MenuButtons.loadMedia(renderer,"pictures/menubutton.png");
            LTexture PlayButtons;
            PlayButtons.loadMedia(renderer,"pictures/Playbutton.png");
            LTexture MapSizes;
            MapSizes.loadMedia(renderer,"pictures/Mapsize.png");
            Mix_Chunk *Select = NULL;
            Select = Mix_LoadWAV("sounds/SelectButton.wav");
            Computer Computer;
            Gameplay Gameplay;
            if (Select == NULL) printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            bool play = false;
            bool computer_on = true;
            bool mainmenu = true;
            bool haschooseMap = false;
            bool hasinteract = false;
            bool playagain = false;
            while (!quit){
                while (mainmenu){
                    SDL_Event e;
                    while (SDL_PollEvent(&e) != 0){
                        if (e.type == SDL_QUIT){
                            quit = true;
                            mainmenu = true;
                        }
                        if (PlayWithComputer.IsInside(&e,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEMOTION:
                                    {
                                    if (!hasinteract){
                                    SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,0,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithComputer.render(&srRect,renderer,MenuButtons);
                                    SDL_RenderPresent(renderer);
                                    hasinteract = true;
                                    }
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                {
                                    Mix_PlayChannel(-1,Select,0);
                                    hasinteract = false;
                                    play = true;
                                    mainmenu = false;
                                    computer_on = true;
                                    break;

                                }
                            }
                        }
                        else if (PlayWithHuman.IsInside(&e,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type)
                            {
                                case SDL_MOUSEMOTION:
                                    {
                                    if (!hasinteract){
                                    SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,COMMON_BUTTON_HEIGHT,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithHuman.render(&srRect,renderer,MenuButtons);
                                    SDL_RenderPresent(renderer);
                                    hasinteract = true;
                                    }
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        hasinteract = false;
                                        play = true;
                                        mainmenu = false;
                                        computer_on = false;
                                        break;
                                    }
                            }
                        }
                        else if (Settings.IsInside(&e,SETTING_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type)
                            {
                                case SDL_MOUSEMOTION:
                                    {
                                    if (!hasinteract){
                                    SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,COMMON_BUTTON_HEIGHT*2,SETTING_WIDTH,COMMON_BUTTON_HEIGHT};
                                    Settings.render(&srRect,renderer,MenuButtons);
                                    SDL_RenderPresent(renderer);
                                    hasinteract = true;
                                    }
                                    }
                                    break;
                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                    Mix_PlayChannel(-1,Select,0);
                                    break;
                                    }
                            }
                        }
                        else if (EXIT.IsInside(&e,EXIT_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEMOTION:
                                    {
                                    if (!hasinteract){
                                    SDL_Rect srRect{COMMON_SOURCE_RECT_POSX,COMMON_BUTTON_HEIGHT*3,EXIT_WIDTH,COMMON_BUTTON_HEIGHT};
                                    EXIT.render(&srRect,renderer,MenuButtons);
                                    SDL_RenderPresent(renderer);
                                    hasinteract = true;
                                    }
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                    mainmenu = false;
                                    quit = true;
                                    break;
                            }

                        }
                            else {
                                    hasinteract = false;
                                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                    SDL_RenderClear(renderer);
                                    SDL_SetRenderDrawColor(renderer, 33, 40, 69, 4);
                                    SDL_RenderClear(renderer);
                                    SDL_RenderCopy(renderer,MainMenu.gTexture,NULL,NULL);
                                    SDL_RenderPresent(renderer);

                            }
                        }
                    }

                while (play){
                    SDL_Event e;
                    while (SDL_PollEvent(&e) != 0){
                        if (e.type == SDL_QUIT){
                            quit = true;
                            play = false;
                        }
                        if (!haschooseMap){
                            if (THRxTHR.IsInside(&e,THRxTHR_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        if (!hasinteract){
                                            SDL_Rect srRect{0,0,THRxTHR_WIDTH,BIG_BUTTON_HEIGHT};
                                            THRxTHR.render(&srRect,renderer,MapSizes);
                                            SDL_RenderPresent(renderer);
                                            hasinteract = true;
                                        }

                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        SDL_Delay(10);
                                        if (computer_on) Computer.setGameData(3,3);
                                            else Gameplay.setGameData(3,3);
                                        haschooseMap = true;
                                        break;
                                    }
                                }
                            }
                            else if (FIVExFIVE.IsInside(&e,FIVExFIVE_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        if (!hasinteract){
                                        SDL_Rect srRect{0,BIG_BUTTON_HEIGHT,FIVExFIVE_WIDTH,BIG_BUTTON_HEIGHT};
                                        FIVExFIVE.render(&srRect,renderer,MapSizes);
                                        SDL_RenderPresent(renderer);
                                        hasinteract = true;
                                        }
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        SDL_Delay(10);
                                        if (computer_on) Computer.setGameData(5,5);
                                            else Gameplay.setGameData(5,5);
                                        haschooseMap = true;
                                        break;
                                    }
                                }
                            }
                            else if (NINExNINE.IsInside(&e,NINExNINE_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        if (!hasinteract){
                                        SDL_Rect srRect{0,BIG_BUTTON_HEIGHT*2,NINExNINE_WIDTH,BIG_BUTTON_HEIGHT};
                                        NINExNINE.render(&srRect,renderer,MapSizes);
                                        SDL_RenderPresent(renderer);
                                        hasinteract = true;
                                        }
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        SDL_Delay(10);
                                        if (computer_on) Computer.setGameData(9,9);
                                            else Gameplay.setGameData(9,9);
                                        haschooseMap = true;
                                        break;
                                    }
                                }
                            }
                            else if (TWELVExTWELVE.IsInside(&e,TWELVExTWELVE_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        if (!hasinteract){
                                        SDL_Rect srRect{0,BIG_BUTTON_HEIGHT*3,TWELVExTWELVE_WIDTH,BIG_BUTTON_HEIGHT};
                                        TWELVExTWELVE.render(&srRect,renderer,MapSizes);
                                        SDL_RenderPresent(renderer);
                                        hasinteract = true;
                                        }
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        SDL_Delay(10);
                                        if (computer_on) Computer.setGameData(12,12);
                                            else Gameplay.setGameData(12,12);
                                        haschooseMap = true;
                                        break;
                                    }
                                }
                            }
                            else if (Back.IsInside(&e,BACK_BUTTON_WIDTH,BACK_BUTTON_HEIGHT)){
                                switch (e.type){
                                case SDL_MOUSEMOTION:
                                    {
                                        if (!hasinteract){
                                            SDL_Rect srRect{srBACK_BUTTON_POSX,srBACK_BUTTON_POSY,BACK_BUTTON_WIDTH,BACK_BUTTON_HEIGHT};
                                            Back.render(&srRect,renderer,MapSizes);
                                            SDL_RenderPresent(renderer);
                                            hasinteract = true;
                                        }
                                        break;
                                    }

                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        mainmenu = true;
                                        play = false;
                                        break;
                                    }
                                }
                            }
                            else {
                                hasinteract = false;
                                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear(renderer);
                                SDL_SetRenderDrawColor(renderer, 33, 40, 69, 4);
                                SDL_RenderClear(renderer);
                                SDL_RenderCopy(renderer,PlayButtons.gTexture,NULL,NULL);
                                SDL_RenderPresent(renderer);
                            }

                        }
                            else {
                                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear(renderer);
                                if (computer_on) Computer.run_computer(renderer,play,mainmenu,haschooseMap,playagain);
                                    else Gameplay.runvshuman(renderer,play,mainmenu,haschooseMap,playagain);

                        }
                    }
                }
                if (playagain){
                    playagain = false;
                    play = true;
                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear(renderer);
                    if (computer_on) Computer.run_computer(renderer,play,mainmenu,haschooseMap,playagain);
                        else Gameplay.runvshuman(renderer,play,mainmenu,haschooseMap,playagain);
                }
                if (!play && !mainmenu && !playagain) quit = true;

          }
        }

}

#endif


