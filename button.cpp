#include "Button.h"

Button::Button()
{
	position.x = 0;
	position.y = 0;

}

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

}

void Button::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(SDL_Event *e, int gbutton_width, int gbutton_height)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int button_width, button_height;
		button_width = gbutton_width;
        button_height = gbutton_height;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
            else if (x > position.x + button_width)
            {
                inside = false;
            }
                else if (y < position.y)
                {
                    inside = false;
                }
                    else if (y > position.y + button_height)
                    {
                        inside = false;
                    }
		return inside;
	}
	return false;
}

void Button::render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip);
}

