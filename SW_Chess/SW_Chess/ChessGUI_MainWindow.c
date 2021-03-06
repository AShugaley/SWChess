#include <stdlib.h>
#include "ChessGUI_MainWindow.h"
#include "Button.h"

static const int width = 450;
static const int height = 700; 

//Helper function to create buttons in the simple window;
Widget** createMainWindowWidgets(SDL_Renderer* renderer) 
{
	if (!renderer)
		return NULL;

	Widget** widgets = malloc(sizeof(Widget*) * 3);
	if (!widgets) 
		return NULL;

	//memset(widgets, 0, 3); 

	SDL_Rect newGame =	{ .x = 125, .y = 70, .h = 80, .w = 200 };
	SDL_Rect loadGame = { .x = 125, .y = 190, .h = 80, .w = 200 };
	SDL_Rect quit =		{ .x = 125, .y = 310, .h = 80, .w = 200 };

	widgets[0] = createButton(renderer, &newGame,		"./start_active.bmp", CHESS_NEWGAME_BUTTON);
	widgets[1] = createButton(renderer, &loadGame,		"./load_active.bmp" , CHESS_LOAD_BUTTON);
	widgets[2] = createButton(renderer, &quit,			"./exit_active.bmp" , CHESS_QUIT_BUTTON);

	for (int i = 0; i < 3; i++)
	{
		if (!widgets[i])
		{
			printf("here0, %d ", i);
			printf("ERROR SDL: unable to create the window's buttons\n");
			for (int j = 0; j < 3; j++)
			{
				if (widgets[j])
					destroyWidget(widgets[j]);
			}
			free(widgets);
			return NULL;
		}
	}

	return widgets;
}


ChessWindow* createMainWindow(Uint32 winMode, chessGame* game)
{
	if (!game)
		return NULL;

	ChessWindow* res = malloc(sizeof(ChessWindow));
	if (!res)
		return NULL;
	chessMainWindow* data = malloc(sizeof(chessMainWindow));
	if (!data)
	{
		free(res);
		return NULL;
	}

	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, winMode);
	if (!window)
	{
		printf("ERROR: unable to create a window: %s\n", SDL_GetError());
		free(res);
		free(data);
		return NULL;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		printf("ERROR: unable to create a renderer: %s\n", SDL_GetError());
		free(res);
		free(data);
		SDL_DestroyWindow(window);	  //NULL safe
		return NULL;
	}
	Widget** widgets = createMainWindowWidgets(renderer);
	if (!widgets)
	{
		printf("ERROR: unable to create window's buttons: %s\n", SDL_GetError());
		free(res);
		free(data);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window);	  //NULL safe
		return NULL;
	}
	
	data->widgets = widgets;
	data->numOfWidgets = 3;
	data->window = window;
	data->windowRenderer = renderer;

	for (int i = 0; i < data->numOfWidgets; i++)
	{
		data->widgets[i]->isDragLegal = false;
		data->widgets[i]->isVisible = true;
		data->widgets[i]->isActivateLegal = true;
		data->widgets[i]->isActive = false;
		data->widgets[i]->isMoving = false;
		data->widgets[i]->endOfDrag = false;
	}

	res->data = (void*) data;
	res->destroyWindow = destroyMainWindow;
	res->drawWindow = drawMainWindow;
	res->handleEventWindow = handleEventMainWindow;
	res->type = CHESS_MAIN_WINDOW;
	res->game = game;

	return res;
}


void destroyMainWindow(ChessWindow* src) 
{
	if (!src)
		return;

	chessMainWindow* data = (chessMainWindow*) src->data;
	for (int i = 0;  i < data->numOfWidgets; i++) 
	{
		destroyWidget(data->widgets[i]);
	}
	free(data->widgets);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}


void drawMainWindow(ChessWindow* src)
{
	if (!src)
		return;

	chessMainWindow* data = (chessMainWindow*) src->data;
	SDL_RenderClear(data->windowRenderer);

	//draw background
	SDL_Surface* surf = SDL_LoadBMP("./main_background.bmp");
	if (!surf)
	{
		printf("ERROR: unable to load BMP file: %s\n", SDL_GetError());
		return;
	}
	SDL_Texture * background = SDL_CreateTextureFromSurface(data->windowRenderer, surf);
	if (!background)
	{
		SDL_FreeSurface(surf);
		printf("ERROR: unable to create a background: %s\n", SDL_GetError());
		return;
	}
	
	SDL_FreeSurface(surf);
	if (SDL_SetTextureBlendMode(background, SDL_BLENDMODE_NONE) != 0)
	{
		printf("ERROR: unable to blend background texture: %s\n", SDL_GetError());
	}

	if (SDL_RenderCopy(data->windowRenderer, background, NULL, NULL) != 0)
	{
		printf("ERROR: unable to render texture: %s\n", SDL_GetError());
	}

	SDL_DestroyTexture(background);
	
	//Draw window
	for (int i = 0; i < data->numOfWidgets; i++) 
	{
		if (data->widgets[i]->isVisible)
		{
			data->widgets[i]->drawWidget(data->widgets[i]);

		}
	}
	SDL_RenderPresent(data->windowRenderer);
}


WINDOW_EVENT handleEventMainWindow(ChessWindow* src, SDL_Event* event)
{
	if ((!src) || (!event))
		return CHESS_EMPTY_WINDOWEVENT;
	
	chessMainWindow* windata = (chessMainWindow*)src->data;

	if (!((event->type == SDL_MOUSEBUTTONDOWN)  && (event->button.button == SDL_BUTTON_LEFT)) &&
		!((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT)))
		return CHESS_EMPTY_WINDOWEVENT;
	
	for(int i=0; i<windata->numOfWidgets; i++)
	{
		windata->widgets[i]->handleEvent(windata->widgets[i], event);
		SDL_RenderPresent(windata->windowRenderer);

		if (windata->widgets[i]->isActive)
		{
			switch (windata->widgets[i]->widget_type)
			{
			case CHESS_EMPTY_BUTTON:
				return CHESS_EMPTY_WINDOWEVENT;
			case CHESS_NEWGAME_BUTTON:
				windata->widgets[i]->isActive = false;
			    return CHESS_SETTINGS_WINDOWEVENT;
			case CHESS_LOAD_BUTTON:
				windata->widgets[i]->isActive = false;
				return CHESS_LOAD_SCREEN_WINDOWEVENT;
			case CHESS_QUIT_BUTTON:
				windata->widgets[i]->isActive = false;
				return CHESS_QUIT_WINDOWEVENT;
			default:
				return CHESS_EMPTY_WINDOWEVENT;
			}
		}	
	}
	return CHESS_EMPTY_WINDOWEVENT;
}
