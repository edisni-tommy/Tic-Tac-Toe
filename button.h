#ifndef BUTTON_H_
#define BUTTON_H_

#include "LTexture.h"
#include "variable.h"

class Button
{
public:
	ButtonSprite currentSprite;

	Button();

	Button(int x, int y);

	void SetPosition(int x, int y);

	bool IsInside(SDL_Event *e, int gbutton_width, int gbutton_height);

	void render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);

    void handlePlayWithComputer();
private:
	SDL_Point position;
};

#endif
