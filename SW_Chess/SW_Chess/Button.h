#ifndef BUTTON_H_
#define BUTTON_H_
#include <stdio.h>
#include <stdbool.h>
#include "Widget.h" //A button is a widget also


typedef struct simplebutton_t Button;
struct simplebutton_t{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
	SDL_Rect* location;
};

//You need a create function:
Widget* createButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* image, WIDGET_TYPE type);

//You need this function in order to destroy all data Associate with a button:
void destroyButton(Widget*);
void handleButtonEvent(Widget* src, SDL_Event* event);
void drawButton(Widget* src);
void updateButtonTexture(Widget* src, const char* image);
void updateButtonLocation(Widget* src, int x, int y);

#endif
