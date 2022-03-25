#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SDL.h>
#include <string>
#include <vector>

class Gameplay{
    private:
        std::string **board_state;
        int winif = 5;
        int row, col;
    //  SDL_Renderer* renderer;

    public:
        std::string state = "X";
        int board_height = 12;
        int board_width = 12;
        int width;
        int height;
        /*Gameplay(SDL_Renderer* _renderer){
            renderer = _renderer;
        };*/
        //Gameplay();
        void update(SDL_Renderer* renderer);
        void draw_board(SDL_Renderer* renderer);
        void createboardstate();
        void getcoordinate();
        void draw_X(SDL_Renderer* renderer, int col, int row);
        int  draw_O(SDL_Renderer* renderer, int col, int row);
        std::string check_win();

};

#endif

