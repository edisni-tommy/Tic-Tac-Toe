#include "computer.h"
#include <algorithm>
#include <cmath>
#include "button.h"
#define computer_state "X"
#define player_state "O"

const int dx[] = {-1 , -1 , -1 , 0 };
const int dy[] = {-1 ,  0 ,  1 , 1 };
const int GoodMoveScore = 6;

int Computer::minimax (bool is_computerturn, int alpha, int beta, int depth){
    int score = 0, bestscore = 0;
    if (check_win() == "Player 1 win") return 1e8+depth;
        else if (check_win() == "Player 2 win") return -1e8+depth;
            else if (check_win() == "Tie") return 0;
    if (depth == 1) return heuristic_val();
    if (is_computerturn){
        bestscore = -1e8;
        for (int i = 1; i <= boardSize; i++)
            for (int j = 1; j <= boardSize; j++){
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
            for (int i = 1; i <= boardSize; i++)
                for (int j = 1; j <= boardSize; j++){
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
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++){
            if (board_state[i][j] == "X" ){
                int numblock = 0;
                int curval = 0;
                for (int t = 0; t <= 3; t++){
                    int cntline = 1, cntscore = GoodMoveScore;
                    for (int r = 1; r <= int((winif+1)/2); r++){
                        if (!check_insideboard(i+r*dx[t],j+r*dy[t]) || board_state[i+r*dx[t]][j+r*dy[t]] == "O"){
                            numblock++;
                            break;
                        }
                            else if (board_state[i+r*dx[t]][j+r*dy[t]] == "X"){
                                cntline++;
                                if (board_state[i+(r-1)*dx[t]][j+(r-1)*dy[t]] == "X") cntscore += GoodMoveScore;
                                    else {
                                        if(cntscore % GoodMoveScore == 0)  cntscore += GoodMoveScore/2;
                                    }
                            }
                                else cntline++;
                    }
                    for (int r = 1; r <= int((winif+1)/2); r++){
                        if (!check_insideboard(i-r*dx[t],j-r*dy[t]) || board_state[i-r*dx[t]][j-r*dy[t]] == "O"){
                            numblock++;
                            break;
                        }
                            else if (board_state[i-r*dx[t]][j-r*dy[t]] == "X"){
                                cntline++;
                                if (board_state[i-(r-1)*dx[t]][j-(r-1)*dy[t]] == "X") cntscore += GoodMoveScore;
                                    else {
                                        if(cntscore % GoodMoveScore == 0) cntscore += GoodMoveScore/2;
                                    }
                            }
                                else cntline++;
                    }
                    if (cntline >= winif){
                        if (cntscore == winif*GoodMoveScore-GoodMoveScore && numblock == 0) cntscore += 216*216;
                            else if ((cntscore >= winif*GoodMoveScore-3*GoodMoveScore/2) ||
                                     (cntscore == (winif-2)*GoodMoveScore && numblock == 0)) cntscore+=216;
                                else if (numblock == 0) cntscore *= 2;
                                    else if (numblock == 2) continue;
                        if (cntscore >= 6*3 && curval >= 12) curval *= cntscore;
                            else curval += (cntscore + (cntline - winif));
                        }
                    }
                val += curval;

            }
               else if (board_state[i][j] == "O"){
                    int numblock = 0, curval = 0 ;
                    for (int t = 0; t <= 3; t++){
                        int cntline = 1, cntscore = GoodMoveScore;
                        for (int r = 1; r <=  int((winif+1)/2); r++){
                            if (!check_insideboard(i+r*dx[t],j+r*dy[t]) || board_state[i+r*dx[t]][j+r*dy[t]] == "X"){
                                numblock++;
                                break;
                            }
                                else if (board_state[i+r*dx[t]][j+r*dy[t]] == "O"){
                                    cntline++;
                                    if (board_state[i+(r-1)*dx[t]][j+(r-1)*dy[t]] == "O") cntscore += GoodMoveScore;
                                        else {
                                            if(cntscore % 10 == 0) cntscore += GoodMoveScore/2;
                                        }
                                }
                                    else cntline++;
                        }
                        for (int r = 1; r <=  int((winif+1)/2); r++){
                            if (!check_insideboard(i-r*dx[t],j-r*dy[t]) || board_state[i-r*dx[t]][j-r*dy[t]] == "X"){
                                if (r == 3) numblock++;
                                break;
                            }
                                else if (board_state[i-r*dx[t]][j-r*dy[t]] == "O"){
                                    cntline++;
                                    if (board_state[i-(r-1)*dx[t]][j-(r-1)*dy[t]] == "O") cntscore += GoodMoveScore;
                                        else {
                                           if(cntscore % 10 == 0) cntscore += GoodMoveScore/2;
                                        }
                                }
                                    else cntline++;
                        }
                        if (cntline >= winif){
                              if (cntscore == (winif-1)*GoodMoveScore && numblock <= 1) cntscore += 216*216*216;
                                else if ((cntscore >= winif*GoodMoveScore-3*GoodMoveScore/2) ||
                                         (cntscore == (winif-2)*GoodMoveScore && numblock == 0)) cntscore += 216;
                                    else if (numblock == 0) cntscore *= 2;
                                        else if (numblock == 2) continue;
                             if (curval >= 6*3 && cntscore >= 12) curval *= cntscore;
                                else curval += (cntscore + (cntline - winif));
                        }
                    }
                    val -= curval;
               }
        }
    return val;
}

bool Computer::check_insideboard(int _row, int _col){
    if (_row < 1 || _col < 1) return false;
    if (_row > boardSize || _col > boardSize) return false;
    return true;
}
void Computer::find_bestmove(){
    int score = 0, bestscore = -1e8, depth;
    if (winif == 3) depth = 9;
        else if (winif == 4) depth = 6;
            else {
                if (boardSize == 9 ) depth = 4;
                    else depth = 3;
            }
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++){
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
    /*
    Button Home(HOME_BUTTON_POSX,HOME_BUTTON_POSY);
    Button Replay(REPLAY_BUTTON_POSX,REPLAY_BUTTON_POSY);
    LTexture UltiButton;
    UltiButton.loadMedia(renderer,"pictures/UltiButton.png");*/
    if (winif > 3){
        col = (boardSize+1)/2;
        row = (boardSize+1)/2;
        update(renderer);
    }
    //bool hasinteract = false;
    while (!quit){
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
