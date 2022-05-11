#ifndef COMPUTER_H
#define COMPUTER_H
#include<iostream>
#include<algorithm>
#include "gameplay.h"

class Computer : public Gameplay {
    private:
        std::pair <int,int> copylastmove = {0,0};
    public:
      void run_computer(SDL_Renderer* &renderer, bool &play, bool &mainmenu, bool &haschoosemap, bool &playagain);
      int minimax(bool is_computerturn, int alpha, int beta, int depth);
      int heuristic_val();
      void find_bestmove();
      void handleSmallState(SDL_Renderer* &renderer, int STATE_POSY);
      void handleBigState(SDL_Renderer* &renderer, int STATE_POSY);
};


#endif
