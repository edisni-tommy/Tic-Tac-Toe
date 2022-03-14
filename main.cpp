#include <stdio.h>
#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

bool init(SDL_Window* gWindow, SDL_Renderer* &renderer)
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1,
                                          SDL_RENDERER_ACCELERATED |
                                          SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL){
                printf("SDL_CreateRenderer Error : %s\n", SDL_GetError() );
                success = false;
			}
		}
	}

	return success;
}
void draw_X(SDL_Renderer *renderer,int width, int height,int col, int row){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0 ,255);
    SDL_RenderDrawLine(renderer,col*width,row*height,(col+1)*width,(row+1)*height);
    SDL_RenderDrawLine(renderer,(col+1)*width,row*height,col*width,(row+1)*height);
    SDL_RenderPresent(renderer);

}
int draw_O(SDL_Renderer *renderer, int x, int y, int radius){
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
int check_win(std::string **board_state,int board_height,int board_width, int winif){
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
                        if (board_state[i][j] == "X") return 1;
                            else return 2;
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
                        if (board_state[i][j] == "X") return 1;
                            else return 2;
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
                if (board_state[t+1][t+j] == "X") return 1;
                    else return 2;
            }
        }
    cnt = 1;
    for (int j = 2; j <= board_height; j++)
        for (int t = 1; t+j <= board_height && t+2 <= board_width; t++){
            if (board_state[t+j][t+2] == "empty") {
                    cnt = 1;
                    continue;
            }
            if (board_state[t+j][2+t] == board_state[t+j-1][t+1]) cnt++;
                else cnt = 1;
            if (cnt == winif){
                if (board_state[t+j][t+2] == "X") return 1;
                    else return 2;
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
                if (board_state[t+1][j-t] == "X") return 1;
                    else return 2;
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
                if (board_state[t+j][board_width-t] == "X") return 1;
                    else return 2;
            }
        }
    return 0;

}
int main( int argc, char* args[] )
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer *renderer =  NULL;
    int board_height = 12;
    int board_width = 12;
    int winif = 5;
    int width = SCREEN_WIDTH/(board_width+2);
    int height = SCREEN_HEIGHT/(board_height+2);
    std::string **board_state;
    board_state = new std::string *[16];
    for (int i = 1; i <= 15; i++)
        board_state[i] = new std::string [16];
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 15; j++){
            board_state[i][j] = "empty";
        }
	if( !init(gWindow,renderer))
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
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
            std::string state = "X";
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

                            int x,y,row,col;
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
                            if (state == "X"){
                                if (board_state[row][col] != "empty") continue;
                                draw_X(renderer,width,height,col,row);
                                board_state[row][col] = state;
                                state = "O";
                            }
                                else {
                                    if (board_state[row][col] != "empty") continue;
                                    draw_O(renderer,(2*col+1)*width/2,(2*row+1)*height/2,width/2);
                                    board_state[row][col] = state;
                                    state = "X";
                                }
                              if (check_win(board_state,board_height,board_width,5) != 0){
                                SDL_DestroyWindow(gWindow);
                                SDL_Quit();
                                std::cout << "End game";
                            }

                    }
				}
			}

	}
	SDL_DestroyWindow(gWindow);
	SDL_Quit();

	return 0;
}
