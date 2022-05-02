#include "computer.h"
#include <algorithm>
#include <cmath>
#define computer_state "X"
#define player_state "O"
const int dx[] = {-1 , -1 , -1 , 0 };
const int dy[] = {-1 ,  0 ,  1 , 1 };

int Computer::minimax (bool is_computerturn, int alpha, int beta, int depth){
    int score = 0, bestscore = 0;
    if (check_win() == "Player 1 win") return 1e8+depth;
        else if (check_win() == "Player 2 win") return -1e8+depth;
            else if (check_win() == "Tie") return 0;
    if (depth == 1) return heuristic_val();
    if (is_computerturn){
        bestscore = -1e8;
        for (int i = 1; i <= board_height; i++)
            for (int j = 1; j <= board_width; j++){
                    if (board_state[i][j] == "empty"){
                        board_state[i][j] = computer_state;
                        score = minimax(false, alpha, beta, depth-1);
                        bestscore =  std::max(score, bestscore);
                        alpha = std::max(alpha, bestscore);
                        board_state[i][j] = "empty";
                        if (beta <= alpha) return bestscore;

                    }
        }
       return bestscore;
    }
        else{
            bestscore = 1e8;
            for (int i = 1; i <= board_height; i++)
                for (int j = 1; j <= board_width; j++){
                    if (board_state[i][j] == "empty"){
                        board_state[i][j] = player_state;
                        score = minimax(true, alpha, beta, depth-1);
                        bestscore = std::min(score, bestscore);
                        board_state[i][j] = "empty";
                        beta = std::min(beta,bestscore);
                        if (beta <= alpha) return bestscore;
                    }
                }
            return bestscore;
        }
}

int Computer::heuristic_val(){
    int val = 0;
    for (int i = 1; i <= board_height; i++)
        for (int j = 1; j <= board_width; j++){
            if (board_state[i][j] == "X" ){
                int curval = 0;
                // check lines through board_state[i][j]
                int numblock = 0;
                for (int t = 0; t <= 3; t++){
                    int cntline = 1, cntx = 10;
                    for (int r = 1; r <= 3; r++){
                        if (!check_insideboard(i+r*dx[t],j+r*dy[t]) || board_state[i+r*dx[t]][j+r*dy[t]] == "O"){
                            if (r == 3) numblock++;
                            break;
                        }
                            else if (board_state[i+r*dx[t]][j+r*dy[t]] == "X"){
                                cntline++;
                                if (board_state[i+(r-1)*dx[t]][j+(r-1)*dy[t]] == "X") cntx += 10;
                                    else cntx += 5;
                            }
                                else cntline++;
                    }
                    if (cntline < 3) continue;
                        else cntline = 3;

                    for (int r = 1; r <= 3; r++){
                        if (!check_insideboard(i-r*dx[t],j-r*dy[t]) || board_state[i-r*dx[t]][j-r*dy[t]] == "O"){
                            if (r == 3) numblock++;
                            break;
                        }
                            else if (board_state[i-r*dx[t]][j-r*dy[t]] == "X"){
                                cntline++;
                                if (board_state[i-(r-1)*dx[t]][j-(r-1)*dy[t]] == "X") cntx += 10;
                                    else cntx += 5;
                            }
                                else cntline++;
                    }
                    if (cntline >= winif){
                        if (cntx == 40 && numblock < 2) cntx += 1e6;
                            else if (cntx >= 35 || (cntx == 30 && numblock == 0)) cntx+=1e4;
                                else if (numblock == 0) cntx *= 2;
                                    else if (numblock == 2) continue;
                      //  if (curval >= 60)
                        curval += (cntx + (cntline - winif));
                        }
                    }
                    val += curval;

            }
               else if (board_state[i][j] == "O"){
                    int curval = 0;
                // check lines through board_state[i][j]
                    int numblock = 0;
                    for (int t = 0; t <= 3; t++){
                        int cntline = 1, cnto = 10;
                        for (int r = 1; r <= 3; r++){
                            if (!check_insideboard(i+r*dx[t],j+r*dy[t]) || board_state[i+r*dx[t]][j+r*dy[t]] == "X"){
                                if (r == 3) numblock++;
                                break;
                            }
                                else if (board_state[i+r*dx[t]][j+r*dy[t]] == "O"){
                                    cntline++;
                                    if (board_state[i+(r-1)*dx[t]][j+(r-1)*dy[t]] == "O") cnto += 10;
                                        else cnto += 5;
                                }
                                    else cntline++;
                        }
                        if (cntline < 3) continue;
                            else cntline = 3;
                        for (int r = 1; r <= 3; r++){
                            if (!check_insideboard(i-r*dx[t],j-r*dy[t]) || board_state[i-r*dx[t]][j-r*dy[t]] == "X"){
                                if (r == 3) numblock++;
                                break;
                            }
                                else if (board_state[i-r*dx[t]][j-r*dy[t]] == "O"){
                                    cntline++;
                                    if (board_state[i-(r-1)*dx[t]][j-(r-1)*dy[t]] == "O") cnto += 10;
                                        else cnto += 5;
                                }
                                    else cntline++;
                        }
                        if (cntline >= winif){
                              if (cnto == 40 && numblock < 2) cnto += 1e7;
                                else if (cnto >= 35 || (cnto == 30 && numblock == 0)) cnto += 1e5;
                                    else if (numblock == 0) cnto *= 2;
                                        else if (numblock == 2) continue;
                            curval += (cnto + (cntline - winif));
                        }
                    }
                    val -= curval;
               }
        }
    return val;
}

bool Computer::check_insideboard(int _row, int _col){
    if (_row < 1 || _col < 1) return false;
    if (_row > board_height || _col > board_width) return false;
    return true;
}
void Computer::find_bestmove(){
    int score = 0, bestscore = -1e8, depth;
    if (winif == 3) depth = 9;
        else depth = 4;
    for (int i = 1; i <= board_height; i++)
        for (int j = 1; j <= board_width; j++){
            if (board_state[i][j] == "empty"){
                board_state[i][j] = computer_state;
                score = minimax(false,-1e8,1e8,depth-1);
                board_state[i][j] = "empty";
                if (score > bestscore){
                    bestscore = score;
                    std::cout << "bestscore: " << i <<" "<< j <<" "<< bestscore << '\n';
                    row = i;
                    col = j;
                }

            }
    }
}

void Computer::run_computer(SDL_Renderer* &renderer, bool &quit){
    draw_board(renderer);
    createboardstate();
    SDL_Event e;
    //make_firstmove
    update(renderer);
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
                else if (state == "X"){
                    find_bestmove();
                    std::cout << row << '\n' << col << '\n';
                    update(renderer);
                  //  testboardstate();
                    if (check_win() == "Player 1 win"){
                        std::cout << "Computer win";
                        quit = true;
                        //restart game..
                    }
                        else if (check_win() == "Tie"){
                            std::cout << "Tie";
                        }
                }
                    else if (e.type == SDL_MOUSEBUTTONDOWN){
                        getcoordinate();
                        update(renderer);
                        if (check_win() == "Player 2 win"){
                            std::cout << "Player win";
                            quit = true;
                            //restart game or sth
                        }
                            else if (check_win() == "Tie"){
                                std::cout << "Tie";
                                quit = true;
                                //restart or not
                            }
            }
        }
    }
}
