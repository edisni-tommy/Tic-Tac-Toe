#include "gameplay.h"
#include <iostream>
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
    };
}
std::string Gameplay::check_win(){
    //check horizontal
    for (int i = 1; i <= boardSize; i++)
        for (int j = 2; j <= boardSize; j++){
            if (board_state[i][j] == "empty") continue;
            if (board_state[i][j] == board_state[i][j-1]){
                int cnt = 2;
                for (int t = j+1; t <= boardSize; t++){
                    if (board_state[i][t] == board_state[i][j]) cnt++;
                        else {
                            j = t;
                            break;
                        }
                    if (cnt == winif){
                        if (board_state[i][j] == "X") return "Player 1 win";
                            else return "Player 2 win";
                    }
                }
            }
        }
     // check vertical
     for (int j = 1; j <= boardSize; j++)
        for (int i = 2; i <= boardSize; i++){
            if (board_state[i][j] == "empty") continue;
            if (board_state[i][j] == board_state[i-1][j]){
                int cnt = 2;
                for (int t = i+1; t <= boardSize; t++){
                    if (board_state[t][j] == board_state[i][j]) cnt++;
                        else {
                          i = t;
                          break;
                        }
                    if (cnt == winif){
                        if (board_state[i][j] == "X") return "Player 1 win";
                            else return "Player 2 win";
                    }
                }
            }
        }
    //check diagonal

    int cnt = 1;
    for (int j = 1; j <= boardSize; j++){
        for (int t = 1; t+1 <= boardSize && t+j <= boardSize; t++){
            if (board_state[t+1][t+j] == "empty") {
                    cnt = 1;
                    continue;
            }
            if (board_state[t+1][t+j] == board_state[t][t+j-1]) cnt++;
                else cnt = 1;
            if (cnt == winif){
                if (board_state[t+1][t+j] == "X") return "Player 1 win";
                    else return "Player 2 win";
            }
        }
        cnt = 1;
    }
    cnt = 1;
    for (int j = 2; j <= boardSize; j++){
        for (int t = 1; t+j <= boardSize && t+1 <= boardSize; t++){
            if (board_state[t+j][t+1] == "empty") {
                    cnt = 1;
                    continue;
            }
            if (board_state[t+j][t+1] == board_state[t+j-1][t]) cnt++;
                else cnt = 1;
            if (cnt == winif){
                if (board_state[t+j][t+1] == "X") return "Player 1 win";
                    else return "Player 2 win";
            }
        }
        cnt = 1;
    }
    cnt = 1;
    for (int j = boardSize; j >= 1; j--){
        for (int t = 1; t+1 <= boardSize && j-t >= 1; t++){
            if (board_state[t+1][j-t] == "empty") {
                    cnt = 1;
                    continue;
            }
            if (board_state[t+1][j-t] == board_state[t][j-t+1]) cnt++;
                else cnt = 1;
            if (cnt == winif){
                if (board_state[t+1][j-t] == "X") return "Player 1 win";
                    else return "Player 2 win";
            }
        }
        cnt = 1;
    }
    cnt = 1;
    for (int j = 2; j <= boardSize; j++){
        for (int t = 1; t+j <= boardSize && boardSize-t >= 1; t++){
            if (board_state[t+j][boardSize-t] == "empty") {
                    cnt = 1;
                    continue;
            }
            if (board_state[t+j][boardSize-t] == board_state[t+j-1][boardSize-t+1]) cnt++;
                else cnt = 1;
            if (cnt == winif){
                if (board_state[t+j][boardSize-t] == "X") return "Player 1 win";
                    else return "Player 2 win";
            }
        }
        cnt = 1;
    }
    for (int i = 1 ; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++){
            if (board_state[i][j] == "empty") return "In game";
        }
    return "Tie";
}
void Gameplay::update(SDL_Renderer* &renderer){
    if (state == "X"){
      if (board_state[row][col] == "empty"){
            draw_X(renderer,col,row);
            board_state[row][col] = state;
            state = "O";
        }
    }
         else {
            if (board_state[row][col] == "empty"){
                draw_O(renderer,col,row);
                board_state[row][col] = state;
                state = "X";
            }
        }
}
void Gameplay::run_vshuman(SDL_Renderer* &renderer, bool &quit){
    draw_board(renderer);
    createboardstate();
    SDL_Event e;
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
                else if (e.type == SDL_MOUSEBUTTONDOWN){
                      getcoordinate();
                      update(renderer);
                      if (check_win() == "Player 1 win"){
                        std::cout << "Player 1 win";
                        quit = true;
                        //restart game..
                    }
                        else if (check_win() == "Player 2 win"){
                            std::cout << "Player 2 win";
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
void Gameplay::setGameData(int _height, int _width){
    boardSize = _height;
    boardSize = _width;
    height = SCREEN_HEIGHT/(boardSize+2);
    width = SCREEN_WIDTH/(boardSize+2);
    if (boardSize == 3) winif = 3;
        else if (boardSize == 5) winif = 4;
            else winif = 5;
}
