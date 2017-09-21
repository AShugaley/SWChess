#include <stdlib.h>
#include "ChessGUI_LoadWindow.h"
#include "Button.h"


static const load_width = 550;
static const load_height = 700;

//create buttons
Widget** createLoadWindowWidgets(SDL_Renderer* renderer)
{
	if (renderer == NULL) {
		return NULL;
	}
	Widget** widgets = malloc(sizeof(Widget*) * 7);
	if (widgets == NULL)
	{
		return NULL;
	}

	SDL_Rect loadGame = { .x = 300,.y = 500, .h = 72, .w = 180 };
	SDL_Rect back     = { .x = 70, .y = 500, .h = 72, .w = 180 };
	SDL_Rect slot1    =	{ .x = 200,.y = 150,.h = 72,.w = 180 };
	SDL_Rect slot2	  = { .x = 200,.y = 150,.h = 72,.w = 180 };
	SDL_Rect slot3    = { .x = 200,.y = 250,.h = 72,.w = 180 };
	SDL_Rect slot4    = { .x = 200,.y = 350,.h = 72,.w = 180 };
	SDL_Rect slot5    = { .x = 200,.y = 450,.h = 72,.w = 180 };


	widgets[0] = createButton(renderer, &loadGame,  "./load_inactive.bmp", CHESS_LOAD_BUTTON);
	widgets[1] = createButton(renderer, &back,	    "./back_active.bmp"  , CHESS_BACK_BUTTON);
	widgets[2] = createButton(renderer, &slot1,     "./... "             , CHESS_SLOT1_BUTTON);
	widgets[3] = createButton(renderer, &slot2,     "./... "             , CHESS_SLOT2_BUTTON);
	widgets[4] = createButton(renderer, &slot3,     "./... "             , CHESS_SLOT3_BUTTON);
	widgets[5] = createButton(renderer, &slot4,     "./... "             , CHESS_SLOT4_BUTTON);
	widgets[6] = createButton(renderer, &slot5,     "./... "             , CHESS_SLOT5_BUTTON);


	for (int i = 0; i < 7; i++)
	{
		if (widgets[i] == NULL)
		{
			for (int j = 0; j < 7; j++)
			{
				destroyWidget(widgets[j]);
			}
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}


ChessWindow* createLoadWindow(Uint32 winMode)
{
	ChessWindow* res = malloc(sizeof(ChessWindow));
	chessLoadWindow* data = malloc(sizeof(chessLoadWindow));
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, load_width, load_height, winMode);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	chessGame* game = createChessGame(6, ONE_PLAYER, WHITES, 2);

	Widget** widgets = createLoadWindowWidgets(renderer);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL || game == NULL)
	{
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window);	  //NULL safe
		destroyChessGame(game);

		return NULL;
	}
	data->widgets = widgets;
	data->numOfWidgets = 7; 
	data->window = window;
	data->windowRenderer = renderer;

	for (int i = 0; i < data->numOfWidgets; i++)
	{
		data->widgets[i]->isDragLegal = false;

	}

	res->data = (void*)data;
	res->destroyWindow = destroyLoadWindow;
	res->drawWindow = drawLoadWindow;
	res->handleEventWindow = handleEventLoadWindow;
	res->type = CHESS_LOAD_WINDOW;
	res->game = game;

	return res;
}


void destroyLoadWindow(ChessWindow* src)
{
	if (src == NULL) {
		return;
	}
	chessLoadWindow* data = (chessLoadWindow*)src->data;
	for (int i = 0; i < data->numOfWidgets; i++)   
	{
		destroyWidget(data->widgets[i]);
	}
	free(data->widgets);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}


void drawLoadWindow(ChessWindow* src)
{
	if (src == NULL) {
		return;
	}
	chessLoadWindow* data = (chessLoadWindow*)src->data;
	SDL_RenderClear(data->windowRenderer);
	
	//draw background
	SDL_Surface* surf = SDL_LoadBMP("./load_background.bmp");
	SDL_Texture * background = SDL_CreateTextureFromSurface(data->windowRenderer, surf);
	if (surf == NULL || background == NULL)
	{
		free(surf);
		SDL_DestroyTexture(background);
		return;
	}
	SDL_FreeSurface(surf);
	if (SDL_SetTextureBlendMode(background, SDL_BLENDMODE_NONE) != 0)
	{
		printf("ERROR: unable to blend background texture: %s\n", SDL_GetError());
	}
	SDL_RenderCopy(data->windowRenderer, background, NULL, NULL);
	SDL_DestroyTexture(background);
	
	//Draw window
	for (int i=0; i < data->numOfWidgets; i++) ////////////////////numofwidgets check
	{
		if (data->widgets[i]->isVisible)
			data->widgets[i]->drawWidget(data->widgets[i]);
	}

	SDL_RenderPresent(data->windowRenderer);
}


WINDOW_EVENT handleEventLoadWindow(ChessWindow* src, SDL_Event* event)
{
	if (src == NULL || event == NULL) {
		return CHESS_EMPTY_WINDOWEVENT;
	}
	chessLoadWindow* windata = (chessLoadWindow*)src->data;

	WINDOW_EVENT eventType = CHESS_EMPTY_WINDOWEVENT;
	//WIDGET_TYPE widgetType;
	for (int i = 0; i<windata->numOfWidgets; i = ((i + 1) % windata->numOfWidgets))
	{
		windata->widgets[i]->handleEvent(windata->widgets[i], event);
		if (windata->widgets[i]->isActive)
		{
			switch (windata->widgets[i]->widget_type)
			{
			case CHESS_EMPTY_BUTTON:
			{
				eventType = CHESS_EMPTY_WINDOWEVENT;
				break;
			}
			case CHESS_BACK_BUTTON:
			{
				eventType = CHESS_BACK_WINDOWEVENT;
				break;
			}
			case CHESS_LOADER_INSIDE_BUTTON:
			{
				if (!(windata->widgets[i]->isActivateLegal))
					eventType = CHESS_EMPTY_WINDOWEVENT;
				else
					eventType = CHESS_LOAD_WINDOWEVENT;
				break;
			}
			default:
			{
				eventType = CHESS_EMPTY_WINDOWEVENT;
				break;
			}
			}
		}
		
		
		//		case CHESS_SLOT1_BUTTON:
		//		{
		//			eventType = ;
		//			break;
		//		}
		//		case CHESS_SLOT2_BUTTON:
		//		{
		//			eventType = ;
		//			break;
		//		}
		//		case CHESS_SLOT3_BUTTON:
		//		{

		//		}
		//		case CHESS_SLOT4_BUTTON:
		//		{

		//		}
		//		case CHESS_SLOT5_BUTTON:
		//		{

		//		}
		//		default:
		//		{
		//			eventType = CHESS_EMPTY_WINDOWEVENT;
		//			break;
		//		}
		//		}
		//	}
	}
	return eventType;
}
