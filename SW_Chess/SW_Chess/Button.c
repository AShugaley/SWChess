#include <stdlib.h>
#include "Button.h"
#include "SPCommon.h"


//You need a create function:
Widget* createButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* image, WIDGET_TYPE type)
{
	if (windowRender == NULL || location == NULL || image == NULL ) 
	{
		return NULL ;
	}
	//Allocate data
	Widget* res = (Widget*) malloc(sizeof(Widget));
	Button* data = (Button*) malloc(sizeof(Button));
	SDL_Surface* loadingSurface = SDL_LoadBMP(image); //We use the surface as a temp var;
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,loadingSurface);
	if (res == NULL || data == NULL || loadingSurface == NULL || buttonTexture == NULL) 
	{
		free(res);
		free(data);
		SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
		SDL_DestroyTexture(buttonTexture); ////It is safe to pass NULL
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
	data->buttonTexture = buttonTexture;
	data->location = spCopyRect(location);
	data->windowRenderer = windowRender;

	res->destroyWidget = destroyButton;
	res->drawWidget = drawButton;
	res->handleEvent = handleButtonEvent;
	res->data = data;
	res->widget_type = type;
	res->isActive = false;
	if (type == CHESS_LOADER_INSIDE_BUTTON || type== CHESS_UNDO_BUTTON)
		res->isActivateLegal = false;
	else
		res->isActivateLegal = true; 
	return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyButton(Widget* src) 
{
	if (src == NULL ) 
		return;

	Button* castData = (Button*) src->data;
	free(castData->location);
	SDL_DestroyTexture(castData->buttonTexture);
	free(castData);
	free(src);
}


void updateButtonTexture(Widget* src, const char* image)
{
	if (src == NULL || image == NULL)
		return;
	Button* castedData = (Button*)src->data;
	SDL_Rect rect = { .x = castedData->location->x,.y = castedData->location->y,.h = castedData->location->h,.w = castedData->location->w };
	SDL_Surface* currentImage = SDL_LoadBMP(image); //We use the surface as a temp var;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(castedData->windowRenderer, currentImage);
	if (currentImage == NULL || texture == NULL)
	{
			SDL_FreeSurface(currentImage); //It is safe to pass NULL
			SDL_DestroyTexture(texture);
			return;
	}
	castedData->buttonTexture = texture;
	SDL_FreeSurface(currentImage);
	if (SDL_RenderCopy(castedData->windowRenderer, castedData->buttonTexture, NULL, &rect) != 0)
	{
		printf("ERROR: unable to render the new texture: %s\n", SDL_GetError());
		return;
	}
}


void updateButtonLocation(Widget* src, int x, int y)
{
	if (src == NULL)
		return;
	Button* castedData = (Button*)src->data;
	castedData->location->x = x;
	castedData->location->y = y; 
}


void handleButtonEvent(Widget* src, SDL_Event* event)
{
	if (src == NULL || event == NULL ) 
	{
		return; //Better to return an error value
	}
	WIDGET_TYPE buttonType = src->widget_type;

	Button* castData = (Button*) src->data;

	//press the mouse
	if (event->type == SDL_MOUSEBUTTONDOWN  && event->button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (src->isVisible && SDL_PointInRect(&point, castData->location))
		{
			switch (buttonType)
			{
			case CHESS_EMPTY_BUTTON:
				break;
			case CHESS_NEWGAME_BUTTON:
			case CHESS_START_BUTTON:
				updateButtonTexture(src, "./start_pressed.bmp");
				break;
			case CHESS_QUIT_BUTTON:
				updateButtonTexture(src, "./exit_pressed.bmp");
				break;
			case CHESS_LOAD_BUTTON:
			case CHESS_LOADER_INSIDE_BUTTON:
				if(src->isActivateLegal)
					updateButtonTexture(src, "./load_pressed.bmp");
				break;
			case CHESS_BACK_BUTTON:
				updateButtonTexture(src, "./back_pressed.bmp");
				break;
			case CHESS_UNDO_BUTTON:
				if (src->isActivateLegal)
					updateButtonTexture(src, "./undo_pressed.bmp");
				break;
			case CHESS_NEXT_BUTTON:
				updateButtonTexture(src, "./next_pressed.bmp");
				break;
			case CHESS_ONEPLAYER_BUTTON:
				updateButtonTexture(src, "./button_base.bmp");
				break;
			case CHESS_TWOPLAYERS_BUTTON:
				updateButtonTexture(src, "./button_base.bmp");
				break;
			case CHESS_WHITE_BUTTON:
				updateButtonTexture(src, "./button_base.bmp");
				break;
			case CHESS_BLACK_BUTTON:
				updateButtonTexture(src, "./button_base.bmp");
				break;
		/*	case CHESS_SLOT1_BUTTON:
			{
				if (src->isActivateLegal)
					updateButtonTexture(src, "./load_pressed.bmp");
				break;
			}
			add the other slots !!!!!!!!!!!!!!!!!!!!!!!*/
			
			}
			src->isActive = true;
		}
		else
			return;
	}
	

	//release the mouse 
	if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) //if there was a click
	{
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, castData->location)) //if the click was inside the button 
		{
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title",
		//		"We did it", NULL);
		//
			src->isActive = false;

		}
		else
			return;
	}
}


void drawButton(Widget* src)
{
	if (src == NULL ) {
		return;
	}
	Button* castData = (Button*) src->data;
	SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,castData->location);
}
