#include <stdlib.h>
#include "ChessGUI_LoadWindow.h"
#include "Button.h"


static const load_width = 550;
static const load_height = 700;
int chosenSlot;

#define LOAD 0 
#define BACK 1
#define SLOT1 2
#define SLOT2 3
#define SLOT3 4
#define SLOT4 5
#define SLOT5 6


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

	SDL_Rect loadGame = { .x = 300,.y = 550, .h = 72, .w = 180 };
	SDL_Rect back     = { .x = 70, .y = 550, .h = 72, .w = 180 };
	SDL_Rect slot1    =	{ .x = 200,.y = 50,.h = 72,.w = 180 };
	SDL_Rect slot2	  = { .x = 200,.y = 150,.h = 72,.w = 180 };
	SDL_Rect slot3    = { .x = 200,.y = 250,.h = 72,.w = 180 };
	SDL_Rect slot4    = { .x = 200,.y = 350,.h = 72,.w = 180 };
	SDL_Rect slot5    = { .x = 200,.y = 450,.h = 72,.w = 180 };


	widgets[0] = createButton(renderer, &loadGame,  "./load_inactive.bmp", CHESS_LOADER_INSIDE_BUTTON);
	widgets[1] = createButton(renderer, &back,	    "./back_active.bmp"  , CHESS_BACK_BUTTON);
	widgets[2] = createButton(renderer, &slot1,     "./slot1_active.bmp " , CHESS_SLOT1_BUTTON);
	widgets[3] = createButton(renderer, &slot2,     "./slot2_active.bmp " , CHESS_SLOT2_BUTTON);
	widgets[4] = createButton(renderer, &slot3,     "./slot3_active.bmp " , CHESS_SLOT3_BUTTON);
	widgets[5] = createButton(renderer, &slot4,     "./slot4_active.bmp " , CHESS_SLOT4_BUTTON);
	widgets[6] = createButton(renderer, &slot5,     "./slot5_active.bmp " , CHESS_SLOT5_BUTTON);


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


ChessWindow* createLoadWindow(Uint32 winMode, chessGame* game)
{
	ChessWindow* res = malloc(sizeof(ChessWindow));
	chessLoadWindow* data = malloc(sizeof(chessLoadWindow));
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, load_width, load_height, winMode);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//chessGame* game = createChessGame(6, ONE_PLAYER, WHITES, 2);

	Widget** widgets = createLoadWindowWidgets(renderer);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL )
	{
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window);	  //NULL safe
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
	data->widgets[LOAD]->isActivateLegal = false;

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
	if (checkIfPathIsLegal(SAVE_SLOT_1)){ data->widgets[2]->isVisible = true; }  else{ data->widgets[2]->isVisible = false; }
	if (checkIfPathIsLegal(SAVE_SLOT_2)){ data->widgets[3]->isVisible = true; }  else{ data->widgets[3]->isVisible = false; }
	if (checkIfPathIsLegal(SAVE_SLOT_3)){ data->widgets[4]->isVisible = true; }  else{ data->widgets[4]->isVisible = false; }
	if (checkIfPathIsLegal(SAVE_SLOT_4)){ data->widgets[5]->isVisible = true; }  else{ data->widgets[5]->isVisible = false; }
	if (checkIfPathIsLegal(SAVE_SLOT_5)){ data->widgets[6]->isVisible = true; }  else{ data->widgets[6]->isVisible = false; }


	for (int i=0; i < data->numOfWidgets; i++)
	{
		if (data->widgets[i]->isVisible)
			data->widgets[i]->drawWidget(data->widgets[i]);
		if ((data->widgets[i]->isVisible) && (data->widgets[i]->widget_type == CHESS_LOADER_INSIDE_BUTTON)
			&& (data->widgets[i]->isActivateLegal))
			updateButtonTexture(data->widgets[i], "./load_active.bmp");
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



	while (1)
	{
begin:
		while (SDL_PollEvent(event))
		{
			if (!(event->type == SDL_MOUSEBUTTONDOWN  && event->button.button == SDL_BUTTON_LEFT) &&
				!(event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT))
				goto begin;
			for (int i = 0; i < windata->numOfWidgets; i++)
			{
				//	bool refresh = false; 
				windata->widgets[i]->handleEvent(windata->widgets[i], event);
				SDL_RenderPresent(windata->windowRenderer);
				if (windata->widgets[i]->isActive && windata->widgets[i]->isActivateLegal)
				{
					switch (windata->widgets[i]->widget_type)
					{
					case CHESS_EMPTY_BUTTON:
						return CHESS_EMPTY_WINDOWEVENT;
					
					case CHESS_BACK_BUTTON:
						windata->widgets[i]->isActive = false;
						return CHESS_BACK_WINDOWEVENT;
					
					case CHESS_LOADER_INSIDE_BUTTON:
						windata->widgets[i]->isActive = false;
						if (chosenSlot == 1) 
							loadGameInPlace(SAVE_SLOT_1, src->game);
						
						if (chosenSlot == 2) 
							loadGameInPlace(SAVE_SLOT_2, src->game);
						
						if (chosenSlot == 3) 
							loadGameInPlace(SAVE_SLOT_3, src->game);
						
						if (chosenSlot == 4) 
							loadGameInPlace(SAVE_SLOT_4, src->game);
						
						if (chosenSlot == 5) 
							loadGameInPlace(SAVE_SLOT_5, src->game);
						
						return CHESS_LOAD_WINDOWEVENT;
					
					case CHESS_SLOT1_BUTTON:
						chosenSlot = 1;
						updateButtonTexture(windata->widgets[SLOT2], "./slot2_active.bmp");
						updateButtonTexture(windata->widgets[SLOT3], "./slot3_active.bmp");
						updateButtonTexture(windata->widgets[SLOT4], "./slot4_active.bmp");
						updateButtonTexture(windata->widgets[SLOT5], "./slot5_active.bmp");
						windata->widgets[LOAD]->isActivateLegal = true;
						windata->widgets[i]->isActive = false;
						break;
					
					case CHESS_SLOT2_BUTTON:
						chosenSlot = 2;
						updateButtonTexture(windata->widgets[SLOT1], "./slot1_active.bmp");
						updateButtonTexture(windata->widgets[SLOT3], "./slot3_active.bmp");
						updateButtonTexture(windata->widgets[SLOT4], "./slot4_active.bmp");
						updateButtonTexture(windata->widgets[SLOT5], "./slot5_active.bmp");
						windata->widgets[LOAD]->isActivateLegal = true;
						windata->widgets[i]->isActive = false;
						break;
					
					case CHESS_SLOT3_BUTTON:
						chosenSlot = 3;
						updateButtonTexture(windata->widgets[SLOT1], "./slot1_active.bmp");
						updateButtonTexture(windata->widgets[SLOT2], "./slot2_active.bmp");
						updateButtonTexture(windata->widgets[SLOT4], "./slot4_active.bmp");
						updateButtonTexture(windata->widgets[SLOT5], "./slot5_active.bmp");
						windata->widgets[LOAD]->isActivateLegal = true;
						windata->widgets[i]->isActive = false;
						break;
					
					case CHESS_SLOT4_BUTTON:
						chosenSlot = 4;
						updateButtonTexture(windata->widgets[SLOT2], "./slot2_active.bmp");
						updateButtonTexture(windata->widgets[SLOT3], "./slot3_active.bmp");
						updateButtonTexture(windata->widgets[SLOT1], "./slot1_active.bmp");
						updateButtonTexture(windata->widgets[SLOT5], "./slot5_active.bmp");
						windata->widgets[LOAD]->isActivateLegal = true;
						windata->widgets[i]->isActive = false;
						break;
					
					case CHESS_SLOT5_BUTTON:
						chosenSlot = 5;
						updateButtonTexture(windata->widgets[SLOT2], "./slot2_active.bmp");
						updateButtonTexture(windata->widgets[SLOT3], "./slot3_active.bmp");
						updateButtonTexture(windata->widgets[SLOT4], "./slot4_active.bmp");
						updateButtonTexture(windata->widgets[SLOT1], "./slot1_active.bmp");
						windata->widgets[LOAD]->isActivateLegal = true;
						windata->widgets[i]->isActive = false;
						break;
					}
					
					drawLoadWindow(src);
					goto begin;
				}
			}
		}
	}
		
		
	return eventType;
}
