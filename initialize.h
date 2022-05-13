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
                        if( TTF_Init() == -1 )
                        {
                            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                            success = false;
                        }
                    }
		}
	}

	return success;
}


void run(SDL_Renderer* &renderer, bool &quit){
    LTexture MainMenu;
    if (!MainMenu.loadMedia(renderer, "pictures/menu 1.png")){
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
            Button QuitSetting(QUIT_SETTING_POSX,QUIT_SETTING_POSY);
            Button Sound(SOUND_POSX,SOUND_POSY);
            Button Music(MUSIC_POSX,MUSIC_POSY);
            LTexture MenuButtons;
            LTexture ChooseMap;
            LTexture ChooseMapButton;
            LTexture Setting;
            LTexture SettingOpt;
            MenuButtons.loadMedia(renderer,"pictures/menubutton1.png");
            ChooseMapButton.loadMedia(renderer,"pictures/choosemapbutton.png");
            ChooseMap.loadMedia(renderer,"pictures/choosemap.png");
            Setting.loadMedia(renderer,"pictures/Setting.png");
            SettingOpt.loadMedia(renderer,"pictures/SettingOp.png");
            Mix_Chunk *Select = NULL;
            Select = Mix_LoadWAV("sounds/SelectButton.wav");
            Mix_Music* gMusic = NULL;
            gMusic = Mix_LoadMUS("sounds/Music.wav");
            Mix_PlayMusic(gMusic,10);
            Computer Computer;
            Gameplay Gameplay;
            if (Select == NULL) printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
            bool play = false;
            bool computer_on = true;
            bool mainmenu = true;
            bool haschooseMap = false;
            bool playagain = false;
            bool setting = false;
            bool music = true;
            bool sound = true;
            while (!quit){
                while (mainmenu){
                    SDL_Event e;
                    while (SDL_PollEvent(&e) != 0){
                        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,MainMenu.gTexture,NULL,NULL);
                        if (e.type == SDL_QUIT){
                            quit = true;
                            mainmenu = false;;
                        }
                        if (PlayWithComputer.IsInside(&e,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEMOTION:
                                    {
                                    SDL_Rect srRect{420,121,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithComputer.render(&srRect,renderer,MenuButtons);
                                    //SDL_RenderPresent(renderer);
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                {
                                    Mix_PlayChannel(-1,Select,0);
                                    play = true;
                                    mainmenu = false;
                                    computer_on = true;
                                    break;

                                }
                            }
                        }
                            else {
                                    SDL_Rect srRect{17,120,PLAY_WITH_COMPUTER_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithComputer.render(&srRect,renderer,MenuButtons);
                        }
                        if (PlayWithHuman.IsInside(&e,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type)
                            {
                                case SDL_MOUSEMOTION:
                                    {
                                    SDL_Rect srRect{439,47,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithHuman.render(&srRect,renderer,MenuButtons);
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        play = true;
                                        mainmenu = false;
                                        computer_on = false;
                                        break;
                                    }
                            }
                        }
                            else {
                                    SDL_Rect srRect{36,46,PLAY_WITH_HUMAN_WIDTH,COMMON_BUTTON_HEIGHT};
                                    PlayWithHuman.render(&srRect,renderer,MenuButtons);
                            }

                        if (Settings.IsInside(&e,SETTING_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type)
                            {
                                case SDL_MOUSEMOTION:
                                    {
                                    SDL_Rect srRect{528,198,SETTING_WIDTH,COMMON_BUTTON_HEIGHT};
                                    Settings.render(&srRect,renderer,MenuButtons);
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                    Mix_PlayChannel(-1,Select,0);
                                    mainmenu = false;
                                    setting = true;
                                    break;
                                    }
                            }
                        }
                            else {
                                SDL_Rect srRect{125,197,SETTING_WIDTH,COMMON_BUTTON_HEIGHT};
                                Settings.render(&srRect,renderer,MenuButtons);
                            }
                          if (EXIT.IsInside(&e,EXIT_WIDTH,COMMON_BUTTON_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEMOTION:
                                    {
                                    SDL_Rect srRect{560,272,EXIT_WIDTH,COMMON_BUTTON_HEIGHT};
                                    EXIT.render(&srRect,renderer,MenuButtons);
                                    break;
                                    }
                                case SDL_MOUSEBUTTONDOWN:
                                    mainmenu = false;
                                    quit = true;
                                    break;
                            }
                        }
                                else {
                                    SDL_Rect srRect{157,270,EXIT_WIDTH,COMMON_BUTTON_HEIGHT};
                                    EXIT.render(&srRect,renderer,MenuButtons);
                                }

                                SDL_RenderPresent(renderer);
                        }
                    }
                while (setting){
                    SDL_Event e;
                    while (SDL_PollEvent(&e) != 0){
                        if (e.type == SDL_QUIT){
                            setting = false;
                            quit = true;
                        }
                        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,Setting.gTexture,NULL,NULL);
                        if (sound){
                            SDL_Rect srRect{0,0,281,35};
                            SettingOpt.Render(170,320,renderer,&srRect);
                        }
                            else {
                                SDL_Rect srRect{0,83,281,35};
                                SettingOpt.Render(170,320,renderer,&srRect);
                            }
                        if (music){
                            SDL_Rect srRect{0,41,263,34};
                            SettingOpt.Render(175,484,renderer,&srRect);
                        }
                            else {
                                SDL_Rect srRect{0,124,263,34};
                                SettingOpt.Render(175,484,renderer,&srRect);
                            }
                        SDL_RenderPresent(renderer);
                        if (Sound.IsInside(&e,SOUND_WIDTH,SOUND_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        if (sound){
                                                sound = false;
                                                Select = NULL;
                                        }
                                            else {
                                                sound = true;
                                                Select = Mix_LoadWAV("sounds/SelectButton.wav");
                                            }
                                    break;
                                    }
                            }
                        }

                        if (Music.IsInside(&e,MUSIC_WIDTH,MUSIC_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEBUTTONDOWN:
                                {
                                    Mix_PlayChannel(-1,Select,0);
                                    if (music){
                                        music = false;
                                        Mix_PauseMusic();
                                    }
                                        else{
                                            music = true;
                                            Mix_ResumeMusic();
                                        }
                                }
                            }
                                break;
                        }
                        if (QuitSetting.IsInside(&e,BACK_BUTTON_WIDTH,BACK_BUTTON_HEIGHT)){
                            switch(e.type){
                                case SDL_MOUSEBUTTONDOWN:
                                {
                                    Mix_PlayChannel(-1,Select,0);
                                    setting = false;
                                    mainmenu = true;
                                    break;
                                }
                            }
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
                            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer,ChooseMap.gTexture,NULL,NULL);
                            SDL_Rect srRect{26,18,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                            THRxTHR.render(&srRect,renderer,ChooseMapButton);
                            srRect = {234,18,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                            FIVExFIVE.render(&srRect,renderer,ChooseMapButton);
                            if (THRxTHR.IsInside(&e,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        SDL_Rect srRect{478,18,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                                        THRxTHR.render(&srRect,renderer,ChooseMapButton);
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
                          if (FIVExFIVE.IsInside(&e,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        SDL_Rect srRect{686,18,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                                        FIVExFIVE.render(&srRect,renderer,ChooseMapButton);
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
                          if (NINExNINE.IsInside(&e,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        SDL_Rect srRect{478,168,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                                        NINExNINE.render(&srRect,renderer,ChooseMapButton);
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
                                else {
                                    SDL_Rect srRect{26,168,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                                    NINExNINE.render(&srRect,renderer,ChooseMapButton);
                                }
                          if (TWELVExTWELVE.IsInside(&e,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT)){
                                switch (e.type){
                                    case SDL_MOUSEMOTION:
                                    {
                                        SDL_Rect srRect{686,168,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                                        TWELVExTWELVE.render(&srRect,renderer,ChooseMapButton);
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
                                else {
                                    SDL_Rect srRect{234,168,BIG_BUTTON_WIDTH,BIG_BUTTON_HEIGHT};
                                    TWELVExTWELVE.render(&srRect,renderer,ChooseMapButton);
                                }

                          if (Back.IsInside(&e,BACK_BUTTON_WIDTH,BACK_BUTTON_HEIGHT)){
                            switch (e.type){
                                case SDL_MOUSEBUTTONDOWN:
                                    {
                                        Mix_PlayChannel(-1,Select,0);
                                        mainmenu = true;
                                        play = false;
                                        break;
                                    }
                                }
                            }
                            SDL_RenderPresent(renderer);
                        }
                            else {
                                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear(renderer);
                                if (computer_on) Computer.run_computer(renderer,play,mainmenu,haschooseMap,playagain,sound);
                                    else Gameplay.runvshuman(renderer,play,mainmenu,haschooseMap,playagain,sound);

                        }
                    }
                }
                if (playagain){
                    playagain = false;
                    play = true;
                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear(renderer);
                    if (computer_on) Computer.run_computer(renderer,play,mainmenu,haschooseMap,playagain,sound);
                        else Gameplay.runvshuman(renderer,play,mainmenu,haschooseMap,playagain,sound);
                }
                if (!play && !mainmenu && !playagain) quit = true;

          }
        }

}

#endif


