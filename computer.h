#ifndef COMPUTER_H
#define COMPUTER_H
#include<iostream>
#include<algorithm>
#include "gameplay.h"

class Computer : public Gameplay {
    private:
    public:
      void run_computer(SDL_Renderer* &renderer, bool &quit);
      int minimax(bool is_computerturn, int alpha, int beta, int depth);
      int heuristic_val();
      bool check_insideboard(int _row, int _col);
      void find_bestmove();

};


#endif
