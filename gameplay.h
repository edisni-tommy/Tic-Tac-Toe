#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SDL.h>
#include <string>
#include <vector>

class Gameplay{
    protected:
        std::string **board_state;
        int row=5, col=5;
        int winif = 5;

    public:
        std::string state = "X";
        int board_height = 9;
        int board_width = 9;
        int width;
        int height;
        void get_boardsize(int boardheight, int boardwidth, int win_if){
            board_height = boardheight;
            board_width = boardwidth;
            winif = win_if;
        }
        void update(SDL_Renderer* &renderer);
        void draw_board(SDL_Renderer* &renderer);
        void createboardstate();
        void getcoordinate();
        void draw_X(SDL_Renderer* &renderer, int col, int row);
        int  draw_O(SDL_Renderer* &renderer, int col, int row);
        std::string check_win();

};

#endif

