#include "gameplay.h"
#include <SDL.h>
#include <iostream>

void Gameplay::draw_board(SDL_Renderer* &renderer){
     SDL_SetRenderDrawColor(renderer, 255, 255 , 255 ,0);
     SDL_RenderClear(renderer);
     for (int i = 1; i <= board_height ; i++)
        for (int j = 1; j <= board_width ; j++){
                        SDL_Rect rect;
                        rect.x = (j)*width;
                        rect.y = i*height;
                        rect.w = width;
                        rect.h = height;
                        SDL_SetRenderDrawColor(renderer, 0, 0 , 0, 255);
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
    for (int i = 1; i <= board_height; i++)
        for (int j = 1; j <= board_width; j++){
            board_state[i][j] = "empty";
        }
}
void Gameplay::getcoordinate() {
    int x,y;
    SDL_GetMouseState( &x, &y);
    bool fine = false;
    for (int i = 1; i <= board_height+1 ; i++){
        for (int j = 1; j <= board_width+1 ; j++){
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
void Gameplay::draw_X(SDL_Renderer* &renderer, int col, int row){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0 ,255);
    SDL_RenderDrawLine(renderer,col*width,row*height,(col+1)*width,(row+1)*height);
    SDL_RenderDrawLine(renderer,(col+1)*width,row*height,col*width,(row+1)*height);
    SDL_RenderPresent(renderer);
}
int  Gameplay::draw_O(SDL_Renderer* &renderer, int col, int row){
    int x = (2*col+1)*width/2;
    int y = (2*row+1)*height/2;
    int radius = width/2;
    int offsetx, offsety, d;
            int status;
            offsetx = 0;
            offsety = radius;
            d = radius -1;
            status = 0;

            while (offsety >= offsetx) {
                status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
                status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
                status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
                status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
                status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
                status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
                status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
                status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

                if (status < 0) {
                    status = -1;
                    break;
                }

                if (d >= 2*offsetx) {
                    d -= 2*offsetx + 1;
                    offsetx +=1;
                }
                else if (d < 2 * (radius - offsety)) {
                    d += 2 * offsety - 1;
                    offsety -= 1;
                }
                else {
                    d += 2 * (offsety - offsetx - 1);
                    offsety -= 1;
                    offsetx += 1;
                }
            }
                SDL_RenderPresent(renderer);

        return status;

}
std::string Gameplay::check_win(){
    //check horizontal
    for (int i = 1; i <= board_height; i++)
        for (int j = 2; j <= board_width; j++){
            if (board_state[i][j] == "empty") continue;
            if (board_state[i][j] == board_state[i][j-1]){
                int cnt = 2;
                for (int t = j+1; t <= board_width; t++){
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
     for (int j = 1; j <= board_width; j++)
        for (int i = 2; i <= board_height; i++){
            if (board_state[i][j] == "empty") continue;
            if (board_state[i][j] == board_state[i-1][j]){
                int cnt = 2;
                for (int t = i+1; t <= board_height; t++){
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
    //check diagonal'
    int cnt = 1;
    for (int j = 1; j <= board_width; j++)
        for (int t = 1; t+1 <= board_height && t+j <= board_width; t++){
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
    for (int j = 2; j <= board_height; j++)
        for (int t = 1; t+j <= board_height && t+1 <= board_width; t++){
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
    for (int j = board_width; j >= 1; j--)
        for (int t = 1; t+1 <= board_height && j-t >= 1; t++){
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
    for (int j = 2; j <= board_height; j++)
        for (int t = 1; t+j <= board_height && board_width-t >= 1; t++){
            if (board_state[t+j][board_width-t] == "empty") {
                    cnt = 1;
                    continue;
            }
            if (board_state[t+j][board_width-t] == board_state[t+j-1][board_width-t+1]) cnt++;
                else cnt = 1;
            if (cnt == winif){
                if (board_state[t+j][board_width-t] == "X") return "Player 1 win";
                    else return "Player 2 win";
            }
        }
    for (int i = 1 ; i <= board_height; i++)
        for (int j = 1; j <= board_width; j++){
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

