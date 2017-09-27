#ifndef BUTTON_H_
#define BUTTON_H_
#include <stdio.h>
#include <stdbool.h>
#include "Widget.h" //A button is a widget also

/* a contanier that holds functions used to create and manage SDL buttons used in the game */

typedef struct simplebutton_t Button;
struct simplebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
};

/* creates a SDL button */
Widget* createButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* image, WIDGET_TYPE type);

/* destroy all data Associate with a button: */
void destroyButton(Widget*);

/* handeles various SDL button events */
void handleButtonEvent(Widget* src, SDL_Event* event);

/* draws the button events */
void drawButton(Widget* src);

/* updates the button outlay */
void updateButtonTexture(Widget* src, const char* image);

/* updates the button location on a window */
void updateButtonLocation(Widget* src, int x, int y);

#endif
