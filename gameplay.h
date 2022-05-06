#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
#include "LTexture.h"

class Gameplay: public LTexture{
    protected:
        std::string **board_state;
        int row, col;
        int winif;
        int boardSize;
        int width;
        int height;
        std::string state = "X";
    public:
        void update(SDL_Renderer* &renderer);
        void draw_board(SDL_Renderer* &renderer);
        void createboardstate();
        void getcoordinate();
        void draw_X(SDL_Renderer* &renderer, int col, int row);
        void draw_O(SDL_Renderer* &renderer, int col, int row);
        std::string check_win();
        void run_vshuman(SDL_Renderer* &renderer, bool &quit);
        void setGameData(int _height, int _width);

};



#endif

