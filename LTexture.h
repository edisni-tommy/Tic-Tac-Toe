#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>



class LTexture{
    protected:
        int pHeight;
        int pWidth;
    public :
        SDL_Texture* gTexture = NULL;
        void free(){
            if (gTexture != NULL){
                SDL_DestroyTexture(gTexture);
                gTexture = NULL;
                pHeight = 0;
                pWidth = 0;
            }
        }
        SDL_Texture* loadTexture(SDL_Renderer* &renderer, std::string path ){
            free();
            //The final texture
            SDL_Texture* newTexture = NULL;

            //Load image at specified path
            SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
            if( loadedSurface == NULL )
            {
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
            }
            else
            {
                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
                if( newTexture == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }
                    else {
                        pHeight = loadedSurface->h;
                        pWidth = loadedSurface->w;
                    }

                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
            }

            return newTexture;
        }
        bool loadMedia(SDL_Renderer* &renderer, std::string path)
        {
            //Loading success flag
            bool success = true;

            //Load PNG texture
            gTexture = loadTexture(renderer, path);
            if( gTexture == NULL )
            {
                printf( "Failed to load texture image!\n" );
                success = false;
            }

            return success;
        }
        void Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip){
            SDL_Rect renderSpace = { x, y, pWidth, pHeight };

            if (clip != nullptr)
            {
                renderSpace.w = clip->w;
                renderSpace.h = clip->h;
            }
            SDL_RenderCopy(renderer, gTexture, clip, &renderSpace);
        }
};


#endif
