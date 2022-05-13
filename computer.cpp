#include "computer.h"

#define computer_state "X"
#define player_state "O"

const int dx[] = {-1 , -1 , -1 , 0 };
const int dy[] = {-1 ,  0 ,  1 , 1 };
const int GoodMoveScore = 4;

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
                        lastmove.first = i;
                        lastmove.second = j;
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
                        lastmove.first = i;
                        lastmove.second = j;
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
                int curval = 1;
                for (int t = 0; t <= 3; t++){
                    int numblock = 0, blockend = 0, numempty = 0;
                    int cntline = 1, cntscore = GoodMoveScore;
                    for (int r = 1; r <= int((winif+1)/2); r++){
                        if (!check_insideboard(i+r*dx[t],j+r*dy[t]) || board_state[i+r*dx[t]][j+r*dy[t]] == "O"){
                            numblock++;
                            if (r == int((winif+1)/2)) blockend++;
                            break;
                        }
                            else if (board_state[i+r*dx[t]][j+r*dy[t]] == "X"){
                                cntline++;
                                if (board_state[i+(r-1)*dx[t]][j+(r-1)*dy[t]] == "X" ) cntscore += GoodMoveScore;
                                    else cntscore += GoodMoveScore/2;
                                }
                                    else {
                                        numempty++;
                                        cntline++;
                                    }
                    }
                    if (numempty >= 2) blockend++;
                    numempty = 0;
                    for (int r = 1; r <= int((winif+1)/2); r++){
                        if (!check_insideboard(i-r*dx[t],j-r*dy[t]) || board_state[i-r*dx[t]][j-r*dy[t]] == "O"){
                            numblock++;
                            if (r == int((winif+1)/2)) blockend++;
                            break;
                        }
                            else if (board_state[i-r*dx[t]][j-r*dy[t]] == "X"){
                                cntline++;
                                if (board_state[i-(r-1)*dx[t]][j-(r-1)*dy[t]] == "X") cntscore += GoodMoveScore;
                                    else cntscore += GoodMoveScore/2;
                            }
                                else {
                                    numempty++;
                                    cntline++;
                                }
                    }
                    if (numempty >=2 ) blockend++;
                    if (cntline >= winif){
                        if ((cntscore == winif*GoodMoveScore-GoodMoveScore) &&
                            (numblock == 0 || ( numblock == 1 && blockend == 1))) cntscore = 1e5;
                            else if ((cntscore >= winif*GoodMoveScore-3*GoodMoveScore/2) ||
                                     (cntscore == (winif-2)*GoodMoveScore && numblock == 0) ||
                                     (cntscore == (winif-2)*GoodMoveScore && numblock == 1 && blockend <= 2)) cntscore=1e3;
                                else if (numblock == 0) cntscore *= 2;
                                    else if (numblock == 2) continue;
                       if (curval >= 1e3 && cntscore >= 1e3) curval += 2*cntscore;
                            else curval += cntscore;
                        }
                    }
                val += curval;

            }
               else if (board_state[i][j] == "O"){
                    int curval = 1;
                    for (int t = 0; t <= 3; t++){
                        int numblock = 0, blockend = 0, numempty = 0;
                        int cntline = 1, cntscore = GoodMoveScore;
                        for (int r = 1; r <=  int((winif+1)/2); r++){
                            if (!check_insideboard(i+r*dx[t],j+r*dy[t]) || board_state[i+r*dx[t]][j+r*dy[t]] == "X"){
                                numblock++;
                                if (r == int((winif+1)/2)) blockend++;
                                break;
                            }
                                else if (board_state[i+r*dx[t]][j+r*dy[t]] == "O"){
                                    cntline++;
                                    if (board_state[i+(r-1)*dx[t]][j+(r-1)*dy[t]] == "O") cntscore += GoodMoveScore;
                                        else {
                                            cntscore += GoodMoveScore/2;
                                        }
                                }
                                    else {
                                        numempty++;
                                        cntline++;
                                    }
                        }
                        if (numempty >= 2) blockend++;
                        numempty = 0;
                        for (int r = 1; r <=  int((winif+1)/2); r++){
                            if (!check_insideboard(i-r*dx[t],j-r*dy[t]) || board_state[i-r*dx[t]][j-r*dy[t]] == "X"){
                                numblock++;
                                if (r == int((winif+1)/2)) blockend++;
                                break;
                            }
                                else if (board_state[i-r*dx[t]][j-r*dy[t]] == "O"){
                                    cntline++;
                                    if (board_state[i-(r-1)*dx[t]][j-(r-1)*dy[t]] == "O") cntscore += GoodMoveScore;
                                        else {
                                           cntscore += GoodMoveScore/2;
                                        }
                                }
                                    else {
                                        numempty++;
                                        cntline++;
                                    }
                        }
                        if (numempty >= 2) blockend++;
                        if (cntline >= winif){
                            if ((cntscore == winif*GoodMoveScore-GoodMoveScore) &&
                                (numblock == 0 || (numblock == 1 && blockend == 1))) cntscore = 1e6;
                                else if ((cntscore >= winif*GoodMoveScore-3*GoodMoveScore/2) ||
                                         (cntscore == (winif-2)*GoodMoveScore && numblock == 0) ||
                                         (cntscore == (winif-2)*GoodMoveScore && numblock == 1 && blockend <= 2)) cntscore=1e4;
                                    else if (numblock == 0) cntscore *= 2;
                                        else if (numblock == 2) continue;
                            if (curval >= 1e3 && cntscore >= 1e3) curval += 3*cntscore;
                                else curval += cntscore*2;
                            }
                    }
                    val -= curval;
               }
        }
    return val;
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
                lastmove.first = i;
                lastmove.second = j;
                score = minimax(false,-1e8,1e8,depth-1);
                board_state[i][j] = "empty";
                if (score > bestscore){
                    bestscore = score;
                   // std::cout << "bestscore: " << i <<" "<< j <<" "<< bestscore << '\n';
                    row = i;
                    col = j;
                }

            }
    }
}

void Computer::run_computer(SDL_Renderer* &renderer, bool &play, bool &mainmenu, bool &haschoosemap, bool &playagain, bool &sound){
    draw_board(renderer);
    createboardstate();
    UltiButton.loadMedia(renderer,"pictures/UltiButton.png");
    if (boardSize > 5) HandleState.loadMedia(renderer,"pictures/State.png");
        else HandleState.loadMedia(renderer,"pictures/State1.png");
    Home.SetPosition(HOME_BUTTON_POSX,HOME_BUTTON_POSY);
    Replay.SetPosition(REPLAY_BUTTON_POSX,REPLAY_BUTTON_POSY);
    int STATE_POSY = SCREEN_HEIGHT-height-5;
    if (boardSize == 9) STATE_POSY += 7 ;
        else if (boardSize == 5) STATE_POSY += 12;
            else if (boardSize == 3) STATE_POSY += 23;
    Player1.SetPosition(PLAYER1_POSX-10,STATE_POSY);
    Tie.SetPosition(TIE_POSX,STATE_POSY);
    Player2.SetPosition(PLAYER2_POSX-5,STATE_POSY);
    int RES_POSY = STATE_POSY+SMALL_STATE_HEIGHT+8;
    if (boardSize > 5){
        cntWin.SetPosition(WIN_POSX,RES_POSY);
        cntDraw.SetPosition(DRAW_POSX,RES_POSY);
        cntLose.SetPosition(LOSE_POSX,RES_POSY);
    }
        else {
            cntWin.SetPosition(WIN_POSX+3,RES_POSY);
            cntDraw.SetPosition(DRAW_POSX+3,RES_POSY);
            cntLose.SetPosition(LOSE_POSX+3,RES_POSY);
        }
    if (sound){
        HitSound = Mix_LoadWAV("sounds/HitSound.wav");
        UltiButtons = Mix_LoadWAV("sounds/UltiButton.wav");
    }

    if (winif > 3 && state == computer_state){
        col = (boardSize+1)/2;
        row = (boardSize+1)/2;
        update(renderer);
        lastmove = {row,col};
        copylastmove = {row,col};
    }
    SDL_Event e;

    handleresult(renderer,RES_POSY);
    handleHomeButton(&e,renderer,play,mainmenu,haschoosemap);
    handleReplayButton(&e,renderer,playagain);
    if (boardSize > 5) handleSmallState(renderer,STATE_POSY);
        else handleBigState(renderer,STATE_POSY);
    bool endgame = false;
    while (play){
        //Handle events on queue
        if (boardSize > 5) handleSmallState(renderer,STATE_POSY);
            else handleBigState(renderer,STATE_POSY);
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                play = false;
            }
                else {
                    handleHomeButton(&e,renderer,play,mainmenu,haschoosemap);
                    if (!play){
                      copylastmove = {0,0};
                      break;
                    }
                    handleReplayButton(&e,renderer,playagain);

                    if (playagain){
                        copylastmove = {0,0};
                        play = false;
                        break;
                    }
                    if (state == "X"){
                        find_bestmove();
                        lastmove = copylastmove;
                        if (winif == 4 && lastmove.first == 3 && lastmove.second == 3 ){
                            row = 2;
                            col = 2;
                        }
                        //std::cout << row << '\n' << col << '\n';
                        copylastmove = {row,col};
                        update(renderer);
                        if (check_win() == "Player 1 win"){
                            cntwin++;
                            drawEndLine(renderer);
                            handleresult(renderer,RES_POSY);
                            free();
                            copylastmove = {0,0};
                            endgame = true;
                            play = false;
                            break;
                        }
                            else if (check_win() == "Tie"){
                                cntdraw++;
                                handleresult(renderer,RES_POSY);
                                free();
                                copylastmove = {0,0};
                                endgame = true;
                                play = false;
                                break;
                            }
                    }
                        else if (e.type == SDL_MOUSEBUTTONDOWN){
                            getcoordinate();
                            if (board_state[row][col] == "empty"){
                                lastmove = copylastmove;
                                copylastmove = {row,col};
                            }
                            update(renderer);
                            if (check_win() == "Player 2 win"){
                                cntlose++;
                                drawEndLine(renderer);
                                handleresult(renderer,RES_POSY);
                                free();
                                copylastmove = {0,0};
                                endgame = true;
                                play = false;
                                break;
                            }
                                else if (check_win() == "Tie"){
                                    cntdraw++;
                                    handleresult(renderer,RES_POSY);
                                    free();
                                    copylastmove = {0,0};
                                    endgame = true;
                                    play = false;
                                    break;
                                }
                        }
            }
        }
    }
    while (endgame){
          while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                endgame = false;
            }
            handleHomeButton(&e,renderer,play,mainmenu,haschoosemap);
            if (mainmenu){
                endgame = false;
                break;
            }
            handleReplayButton(&e,renderer,playagain);
            if (playagain){
                    copylastmove = {0,0};
                    endgame = false;
                    break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                int x,y;
                SDL_GetMouseState(&x,&y);
                if (x >= width && x <= (boardSize+1)*width
                    && y >= height && y <=(boardSize+1)*height){
                        endgame = false;
                        playagain = true;
                }
            }

        }
    }
}

void Computer::handleSmallState(SDL_Renderer* &renderer, int STATE_POSY){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_Rect dsRect{PLAYER1_POSX-10,STATE_POSY,SMALL_COMPUTER_WIDTH,SMALL_STATE_HEIGHT};
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = PLAYER2_POSX-5;
    dsRect.w = SMALL_PLAYER_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = DRAW_POSX;
    dsRect.w = SMALL_TIE_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    if (state != computer_state){
        SDL_Rect srRect{0,3,SMALL_COMPUTER_WIDTH,SMALL_STATE_HEIGHT};
        Player1.render(&srRect,renderer,HandleState);
        srRect = {104,17,SMALL_PLAYER_WIDTH,SMALL_STATE_HEIGHT};
        Player2.render(&srRect,renderer,HandleState);
        srRect = {0,30,SMALL_TIE_WIDTH,SMALL_STATE_HEIGHT};
        Tie.render(&srRect,renderer,HandleState);
        SDL_RenderPresent(renderer);
    }
        else {
            SDL_Rect srRect{104,3,SMALL_COMPUTER_WIDTH,SMALL_STATE_HEIGHT};
            Player1.render(&srRect,renderer,HandleState);
            srRect = {0,17,SMALL_PLAYER_WIDTH,SMALL_STATE_HEIGHT};
            Player2.render(&srRect,renderer,HandleState);
            srRect = {0,30,SMALL_TIE_WIDTH,SMALL_STATE_HEIGHT};
            Tie.render(&srRect,renderer,HandleState);
            SDL_RenderPresent(renderer);

        }
}
void Computer::handleBigState(SDL_Renderer* &renderer, int STATE_POSY){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_Rect dsRect{PLAYER1_POSX-10,STATE_POSY,BIG_COMPUTER_WIDTH,BIG_STATE_HEIGHT};
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = PLAYER2_POSX-5;
    dsRect.w = BIG_PLAYER_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = DRAW_POSX;
    dsRect.w = BIG_TIE_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    if (state != computer_state){
        SDL_Rect srRect{0,3,BIG_COMPUTER_WIDTH,BIG_STATE_HEIGHT};
        Player1.render(&srRect,renderer,HandleState);
        srRect = {150,17,BIG_PLAYER_WIDTH,BIG_STATE_HEIGHT};
        Player2.render(&srRect,renderer,HandleState);
        srRect = {0,34,BIG_TIE_WIDTH,BIG_STATE_HEIGHT};
        Tie.render(&srRect,renderer,HandleState);
        SDL_RenderPresent(renderer);
    }
        else {
            SDL_Rect srRect{150,3,BIG_COMPUTER_WIDTH,BIG_STATE_HEIGHT};
            Player1.render(&srRect,renderer,HandleState);
            srRect = {0,17,BIG_PLAYER_WIDTH,BIG_STATE_HEIGHT};
            Player2.render(&srRect,renderer,HandleState);
            srRect = {0,34,BIG_TIE_WIDTH,BIG_STATE_HEIGHT};
            Tie.render(&srRect,renderer,HandleState);
            SDL_RenderPresent(renderer);

        }
}
