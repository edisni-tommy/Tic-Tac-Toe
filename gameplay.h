#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "button.h"
#include <SDL_mixer.h>

class Gameplay: public LTexture{
    protected:
        std::string **board_state;
        int row, col;
        int winif;
        int boardSize;
        int width;
        int height;
        int cntwin = 0;
        int cntdraw = 0;
        int cntlose = 0;
        std::pair <int,int> lastmove = {0,0};
        std::string state = "X";
        LTexture UltiButton;
        LTexture HandleState;
        LTexture gNum;
        Button Home, Replay;
        Button Player1, Player2, Tie;
        Button cntWin, cntDraw, cntLose;
        Mix_Chunk* HitSound = NULL;
        Mix_Chunk* UltiButtons = NULL;
    public:
        void free();
        void update(SDL_Renderer* &renderer);
        void draw_board(SDL_Renderer* &renderer);
        void createboardstate();
        void getcoordinate();
        void highlightbox (SDL_Renderer* &renderer, int _row, int _col);
        void unhighlightbox (SDL_Renderer* &renderer, int _row, int _col);
        void draw_X(SDL_Renderer* &renderer, int col, int row);
        void draw_O(SDL_Renderer* &renderer, int col, int row);
        std::string check_win();
        void drawEndLine(SDL_Renderer* &renderer);
        void runvshuman(SDL_Renderer* &renderer, bool &play,bool &mainmenu, bool &haschoosemap, bool &playagain, bool &sound);
        void setGameData(int _height, int _width);
        void handleHomeButton(SDL_Event* e, SDL_Renderer* &renderer, bool &play, bool &mainmenu, bool &haschoosemap);
        void handleReplayButton(SDL_Event* e,SDL_Renderer* &renderer, bool &playagain);
        virtual void handleSmallState(SDL_Renderer* &renderer, int &STATE_POSY);
        virtual void handleBigState(SDL_Renderer* &renderer, int &STATE_POSY);
        void handleresult(SDL_Renderer* &renderer, int &RES_POSSY);
        bool check_insideboard(int _row, int _col);
};



#endif

