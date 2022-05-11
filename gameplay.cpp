#include "gameplay.h"
#define player1State "X"
#define player2State "Y"

const int dx[] = {-1 , -1 , -1 , 0 };
const int dy[] = {-1 ,  0 ,  1 , 1 };

void Gameplay::free(){
    for (int i = 0; i <= 17; i++) delete board_state[i];
    delete board_state;
    lastmove = {0,0};
    delete HitSound;
    delete UltiButtons;
}
void Gameplay::draw_board(SDL_Renderer* &renderer){
     SDL_SetRenderDrawColor(renderer, 255, 255 , 255 , -2);
     SDL_RenderClear(renderer);
     for (int i = 1; i <= boardSize ; i++)
        for (int j = 1; j <= boardSize ; j++){
                        SDL_Rect rect;
                        rect.x = (j)*width;
                        rect.y = i*height;
                        rect.w = width;
                        rect.h = height;
                        SDL_SetRenderDrawColor(renderer, 40, 56 , 76 , -2);
                        SDL_RenderFillRect(renderer, &rect);
                        SDL_SetRenderDrawColor(renderer, 231 ,236 ,237 , 0);
                        SDL_RenderDrawRect(renderer, &rect);

        }
    SDL_RenderPresent(renderer);
}
void Gameplay::createboardstate(){
    board_state = new std::string *[18];
    for (int i = 0; i <= 17; i++)
    board_state[i] = new std::string [18];
    for (int i = 0; i <= 17; i++)
        for (int j = 0; j <= 17; j++){
            board_state[i][j] = "block";
        }
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++){
            board_state[i][j] = "empty";
        }
}
void Gameplay::getcoordinate() {
    int x,y;
    SDL_GetMouseState( &x, &y);
    bool fine = false;
    for (int i = 1; i <= boardSize+1 ; i++){
        for (int j = 1; j <= boardSize+1 ; j++){
            if (j*width > x && i*height > y){
                row = i-1;
                col = j-1;
                fine = true;
                break;
            }
        }
        if (fine) break;
     }
}
void Gameplay::draw_X(SDL_Renderer* &renderer, int col , int row){
    if (loadMedia(renderer, "pictures/x.png")){
        SDL_Rect dstrect;
        dstrect.h = height-height/3;
        dstrect.w = width-width/3;
        dstrect.x = col*height+height/6;
        dstrect.y = row*width+width/6;
        SDL_RenderCopy(renderer,gTexture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        Mix_PlayChannel(-1,HitSound,0);
    };
};
void Gameplay::draw_O(SDL_Renderer* &renderer, int col, int row){
    if (loadMedia(renderer, "pictures/o.png")){
        SDL_Rect dstrect;
        dstrect.h = height-height/3;
        dstrect.w = width-width/3;
        dstrect.x = col*height+height/6;
        dstrect.y = row*width+width/6;
        SDL_RenderCopy(renderer,gTexture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        Mix_PlayChannel(-1,HitSound,0);
    };
}
void Gameplay::highlightbox(SDL_Renderer* &renderer, int _col, int _row){
    SDL_Rect dsrect{_col*height,_row*width,width,height};
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderFillRect(renderer,&dsrect);
    SDL_SetRenderDrawColor(renderer,95,211,163,77);
    SDL_RenderFillRect(renderer,&dsrect);
    SDL_SetRenderDrawColor(renderer,231,236,237,0);
    SDL_RenderDrawRect(renderer,&dsrect);
}
void Gameplay::unhighlightbox(SDL_Renderer* &renderer, int _col, int _row){
    SDL_Rect dsrect{_col*height,_row*width,width,height};
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderFillRect(renderer,&dsrect);
    SDL_SetRenderDrawColor(renderer,40,56,76,-2);
    SDL_RenderFillRect(renderer,&dsrect);
    SDL_SetRenderDrawColor(renderer,231,236,237,0);
    SDL_RenderDrawRect(renderer,&dsrect);
    if (state == "X") draw_O(renderer,_col,_row);
        else draw_X(renderer,_col,_row);
}
std::string Gameplay::check_win(){
    if (board_state[lastmove.first][lastmove.second] == "empty") return "In game";
    for (int i = 0; i <= 3; i++){
        int cntscore = 1;
        for (int j = 1; j <= winif-1; j++){
            if (!check_insideboard(lastmove.first+j*dx[i],lastmove.second+j*dy[i])) break;
                else
                    {if (board_state[lastmove.first+j*dx[i]][lastmove.second+j*dy[i]] == board_state[lastmove.first][lastmove.second]) cntscore++;
                            else break;
                    }
        }
        for (int j = 1; j <= winif-1; j++){
            if (!check_insideboard(lastmove.first-j*dx[i],lastmove.second-j*dy[i])) break;
                else
                    {if (board_state[lastmove.first-j*dx[i]][lastmove.second-j*dy[i]] == board_state[lastmove.first][lastmove.second]) cntscore++;
                            else break;
                    }
        }
        if (cntscore == winif){
            if (board_state[lastmove.first][lastmove.second] == "X") return "Player 1 win";
                else return "Player 2 win";
        }
   }
   for (int i = 0 ; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++)
            if (board_state[i][j] == "empty") return "In game";
   return "Tie";
}
void Gameplay::drawEndLine(SDL_Renderer* &renderer){
    for (int i = 0; i <= 3; i++){
        int cntscore = 1;
        for (int j = 1; j <= winif-1; j++){
            if (!check_insideboard(lastmove.first+j*dx[i],lastmove.second+j*dy[i])) break;
                else
                    {if (board_state[lastmove.first+j*dx[i]][lastmove.second+j*dy[i]] == board_state[lastmove.first][lastmove.second]) cntscore++;
                            else break;
                    }
        }
        for (int j = 1; j <= winif-1; j++){
            if (!check_insideboard(lastmove.first-j*dx[i],lastmove.second-j*dy[i])) break;
                else
                    {if (board_state[lastmove.first-j*dx[i]][lastmove.second-j*dy[i]] == board_state[lastmove.first][lastmove.second]) cntscore++;
                            else break;
                    }
        }
            if (cntscore == winif){
                highlightbox(renderer,lastmove.second,lastmove.first);
                if (board_state[lastmove.first][lastmove.second] == "X") draw_X(renderer,lastmove.second,lastmove.first);
                    else draw_O(renderer,lastmove.second,lastmove.first);
                for (int j = 1; j <= winif-1; j++){
                    if (!check_insideboard(lastmove.first+j*dx[i],lastmove.second+j*dy[i])) break;
                        else
                            {
                                if (board_state[lastmove.first+j*dx[i]][lastmove.second+j*dy[i]] ==
                                    board_state[lastmove.first][lastmove.second]){
                                        highlightbox(renderer,lastmove.second+j*dy[i],lastmove.first+j*dx[i]);
                                        if (board_state[lastmove.first][lastmove.second] == "X") draw_X(renderer,lastmove.second+j*dy[i],lastmove.first+j*dx[i]);
                                            else draw_O(renderer,lastmove.second+j*dy[i],lastmove.first+j*dx[i]);
                                    }
                                    else break;
                            }
                }
                for (int j = 1; j <= winif-1; j++){
                    if (!check_insideboard(lastmove.first-j*dx[i],lastmove.second-j*dy[i])) break;
                        else
                            {
                                if (board_state[lastmove.first-j*dx[i]][lastmove.second-j*dy[i]] ==
                                 board_state[lastmove.first][lastmove.second]){
                                        highlightbox(renderer,lastmove.second-j*dy[i],lastmove.first-j*dx[i]);
                                        if (board_state[lastmove.first][lastmove.second] == "X") draw_X(renderer,lastmove.second-j*dy[i],lastmove.first-j*dx[i]);
                                            else draw_O(renderer,lastmove.second-j*dy[i],lastmove.first-j*dx[i]);
                                    }
                                    else break;
                            }
                }

            }
   }
}
void Gameplay::update(SDL_Renderer* &renderer){
    if (!check_insideboard(row,col) || board_state[row][col] != "empty") return;
    if (state == "X"){
      if (board_state[row][col] == "empty"){
            SDL_Rect dsrect = {lastmove.second*width, lastmove.first*height,width,height};
            if (lastmove.first != 0){
                unhighlightbox(renderer,lastmove.second,lastmove.first);
            }
            highlightbox(renderer,col,row);
            draw_X(renderer,col,row);
            board_state[row][col] = state;
            state = "O";
            lastmove.first = row;
            lastmove.second = col;
        }
    }
         else {
            if (board_state[row][col] == "empty"){
                SDL_Rect dsrect = {lastmove.second*width, lastmove.first*height,width,height};
                if (lastmove.first != 0){
                    unhighlightbox(renderer,lastmove.second,lastmove.first);
                }
                highlightbox(renderer,col,row);
                draw_O(renderer,col,row);
                board_state[row][col] = state;
                state = "X";
                lastmove.first = row;
                lastmove.second = col;
            }
        }
}
void Gameplay::runvshuman(SDL_Renderer* &renderer, bool &play, bool &mainmenu, bool &haschoosemap, bool &playagain){
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
    Player1.SetPosition(PLAYER1_POSX,STATE_POSY);
    Tie.SetPosition(TIE_POSX,STATE_POSY);
    Player2.SetPosition(PLAYER2_POSX,STATE_POSY);
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
    HitSound = Mix_LoadWAV("sounds/HitSound.wav");
    UltiButtons = Mix_LoadWAV("sounds/UltiButton");
    SDL_Event e;
    handleresult(renderer,RES_POSY);
    handleHomeButton(&e,renderer,play,mainmenu,haschoosemap);
    handleReplayButton(&e,renderer,playagain);
    if (boardSize > 5) handleSmallState(renderer,STATE_POSY);
        else handleBigState(renderer,STATE_POSY);
    bool endgame = false;
    while (play)
    {

        //Handle events on queue

        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                play = false;
            }

            handleHomeButton(&e,renderer,play,mainmenu,haschoosemap);
            if (!play) break;
            handleReplayButton(&e,renderer,playagain);
            if (playagain){
                play = false;
                break;
            }
            if (boardSize > 5) handleSmallState(renderer,STATE_POSY);
                else handleBigState(renderer,STATE_POSY);
            if (e.type == SDL_MOUSEBUTTONDOWN){
              getcoordinate();
              update(renderer);
              if (check_win() == "Player 1 win"){
                drawEndLine(renderer);
                cntwin++;
                handleresult(renderer,RES_POSY);
                free();
                endgame = true;
                play = false;
                state = "O";
                break;
            }
                else if (check_win() == "Player 2 win"){
                    drawEndLine(renderer);
                    cntlose++;
                    handleresult(renderer,RES_POSY);
                    free();
                    endgame = true;
                    play = false;
                    state = "X";
                    break;
                }
                    else if (check_win() == "Tie"){
                        cntdraw++;
                        handleresult(renderer,RES_POSY);
                        free();
                        endgame = true;
                        play = false;
                        break;
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
void Gameplay::setGameData(int _height, int _width){
    boardSize = _height;
    boardSize = _width;
    height = SCREEN_HEIGHT/(boardSize+2);
    width = SCREEN_WIDTH/(boardSize+2);
    if (boardSize == 3) winif = 3;
        else if (boardSize == 5) winif = 4;
            else winif = 5;
}
void Gameplay::handleHomeButton(SDL_Event* e, SDL_Renderer* &renderer, bool &play, bool &mainmenu, bool &haschoosemap){
    if (Home.IsInside(e,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT)){
        switch (e->type){
            case SDL_MOUSEMOTION:
            {
                SDL_Rect srRect{0,0,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT};
                Home.render(&srRect,renderer,UltiButton);
                SDL_RenderPresent(renderer);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                Mix_PlayChannel(-1,UltiButtons,0);
                free();
                cntwin = cntdraw = cntlose = 0;
                play = false;
                mainmenu = true;
                haschoosemap = false;
                state = "X";
                break;
            }
        }
    }
        else{
            SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
            SDL_Rect dsRect{HOME_BUTTON_POSX,HOME_BUTTON_POSY,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT};
            SDL_RenderFillRect(renderer,&dsRect);
            SDL_Rect srRect{ULTI_BUTTON_WIDTH+3,0,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT};
            Home.render(&srRect,renderer,UltiButton);
            SDL_RenderPresent(renderer);
        }
}
void Gameplay::handleReplayButton(SDL_Event* e,SDL_Renderer* &renderer, bool &playagain){
    if (Replay.IsInside(e,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT)){
        switch (e->type){
            case SDL_MOUSEMOTION:
            {
                SDL_Rect srRect{0,ULTI_BUTTON_HEIGHT,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT};
                Replay.render(&srRect,renderer,UltiButton);
                SDL_RenderPresent(renderer);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                Mix_PlayChannel(-1,UltiButtons,0);
                playagain = true;
                break;
            }
        }
    }
         else{
            SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
            SDL_Rect dsRect{REPLAY_BUTTON_POSX,REPLAY_BUTTON_POSY,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT};
            SDL_RenderFillRect(renderer,&dsRect);
            SDL_Rect srRect{ULTI_BUTTON_WIDTH+2,ULTI_BUTTON_HEIGHT,ULTI_BUTTON_WIDTH,ULTI_BUTTON_HEIGHT};
            Replay.render(&srRect,renderer,UltiButton);
            SDL_RenderPresent(renderer);
        }
}
void Gameplay::handleSmallState(SDL_Renderer* &renderer, int &STATE_POSY){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_Rect dsRect{PLAYER1_POSX,STATE_POSY,SMALL_PLAYER1_WIDTH,SMALL_STATE_HEIGHT};
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = PLAYER2_POSX;
    dsRect.w = SMALL_PLAYER2_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = DRAW_POSX;
    dsRect.w = SMALL_TIE_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    if (state != player1State){
        SDL_Rect srRect{0,44,SMALL_PLAYER1_WIDTH,SMALL_STATE_HEIGHT};
        Player1.render(&srRect,renderer,HandleState);
        srRect = {104,59,SMALL_PLAYER2_WIDTH,SMALL_STATE_HEIGHT};
        Player2.render(&srRect,renderer,HandleState);
        srRect = {0,30,SMALL_TIE_WIDTH,SMALL_STATE_HEIGHT};
        Tie.render(&srRect,renderer,HandleState);
        SDL_RenderPresent(renderer);
    }
        else {
            SDL_Rect srRect{104,45,SMALL_PLAYER1_WIDTH,SMALL_STATE_HEIGHT};
            Player1.render(&srRect,renderer,HandleState);
            srRect = {0,57,SMALL_PLAYER2_WIDTH,SMALL_STATE_HEIGHT};
            Player2.render(&srRect,renderer,HandleState);
            srRect = {0,30,SMALL_TIE_WIDTH,SMALL_STATE_HEIGHT};
            Tie.render(&srRect,renderer,HandleState);
            SDL_RenderPresent(renderer);

        }
}
void Gameplay::handleBigState(SDL_Renderer* &renderer, int &STATE_POSY){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_Rect dsRect{PLAYER1_POSX,STATE_POSY,BIG_PLAYER1_WIDTH,BIG_STATE_HEIGHT};
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = PLAYER2_POSX;
    dsRect.w = BIG_PLAYER2_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = DRAW_POSX;
    dsRect.w = BIG_TIE_WIDTH;
    SDL_RenderFillRect(renderer,&dsRect);
    if (state != player1State){
        SDL_Rect srRect{0,49,BIG_PLAYER1_WIDTH,BIG_STATE_HEIGHT};
        Player1.render(&srRect,renderer,HandleState);
        srRect = {150,66,BIG_PLAYER2_WIDTH,BIG_STATE_HEIGHT};
        Player2.render(&srRect,renderer,HandleState);
        srRect = {0,34,BIG_TIE_WIDTH,BIG_STATE_HEIGHT};
        Tie.render(&srRect,renderer,HandleState);
        SDL_RenderPresent(renderer);
    }
        else {
            SDL_Rect srRect{150,49,BIG_PLAYER1_WIDTH,BIG_STATE_HEIGHT};
            Player1.render(&srRect,renderer,HandleState);
            srRect = {0,66,BIG_PLAYER2_WIDTH,BIG_STATE_HEIGHT};
            Player2.render(&srRect,renderer,HandleState);
            srRect = {0,34,BIG_TIE_WIDTH,BIG_STATE_HEIGHT};
            Tie.render(&srRect,renderer,HandleState);
            SDL_RenderPresent(renderer);

        }
}
void Gameplay::handleresult(SDL_Renderer* &renderer, int &RES_POSY){
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_Rect dsRect{WIN_POSX,RES_POSY,SMALL_NUMBER_WIDTH,SMALL_NUMBER_HEIGHT};
    if (boardSize <= 5){
        dsRect.w = BIG_NUMBER_WIDTH;
        dsRect.h = BIG_NUMBER_HEIGHT;
        dsRect.x += 3;
    }
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = DRAW_POSX;
    if (boardSize <= 5) dsRect.x += 3;
    SDL_RenderFillRect(renderer,&dsRect);
    dsRect.x = LOSE_POSX;
    if (boardSize <= 5) dsRect.x += 3;
    SDL_RenderFillRect(renderer,&dsRect);
    if (boardSize > 5){
        SDL_Rect srRect{cntwin*SMALL_NUMBER_WIDTH,71,SMALL_NUMBER_WIDTH,SMALL_NUMBER_HEIGHT};
        cntWin.render(&srRect,renderer,HandleState);
        srRect = {cntdraw*SMALL_NUMBER_WIDTH,71,SMALL_NUMBER_WIDTH,SMALL_NUMBER_HEIGHT};
        cntDraw.render(&srRect,renderer,HandleState);
        srRect = {cntlose*SMALL_NUMBER_WIDTH,71,SMALL_NUMBER_WIDTH,SMALL_NUMBER_HEIGHT};
        cntLose.render(&srRect,renderer,HandleState);
    }
        else {
            SDL_Rect srRect{cntwin*(BIG_NUMBER_WIDTH-0.5),86,BIG_NUMBER_WIDTH,BIG_NUMBER_HEIGHT};
            cntWin.render(&srRect,renderer,HandleState);
            srRect = {cntdraw*(BIG_NUMBER_WIDTH-0.5),86,BIG_NUMBER_WIDTH,BIG_NUMBER_HEIGHT};
            cntDraw.render(&srRect,renderer,HandleState);
            srRect = {cntlose*(BIG_NUMBER_WIDTH-0.5),86,BIG_NUMBER_WIDTH,BIG_BUTTON_HEIGHT};
            cntLose.render(&srRect,renderer,HandleState);
        }
    SDL_RenderPresent(renderer);
}
bool Gameplay::check_insideboard(int _row, int _col){
    if (_row < 1 || _col < 1) return false;
    if (_row > boardSize || _col > boardSize) return false;
    return true;
}
