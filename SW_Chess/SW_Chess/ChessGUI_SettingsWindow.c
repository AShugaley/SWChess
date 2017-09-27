#include <stdlib.h>
#include "ChessGUI_SettingsWindow.h"
#include "Button.h"
#include "Chess_gameUtils.h"


static const int settings_height = 700;
static const int settings_width = 550;

//this is for the widget array places, for the handle event section 
#define BACK 0 
#define NEXT 1
#define START 2
#define ONEP 3
#define TWOP 4
#define NOOB 5
#define EASY 6
#define MODERATE 7
#define HARD 8
#define WHITE 9
#define BLACK 10
#define EXPERT 11


Widget** createSettingsWindowWidgets(SDL_Renderer* renderer)
{
	if (!renderer)
		return NULL;

	Widget** widgets = malloc(sizeof(Widget*) * 12);
	if (!widgets)
		return NULL;
	
	memset(widgets, 0, 12);

	SDL_Rect back =		{ .x = 70 ,.y = 500,.h = 72,.w = 180 };
	SDL_Rect next =		{ .x = 300, .y = 500,.h = 72,.w = 180 };
	SDL_Rect start =	{ .x = 300, .y = 500,.h = 72,.w = 180 };
	
	SDL_Rect onep = { .x = 70 ,.y = 200,.h = 72,.w = 180 };
	SDL_Rect twop = { .x = 300,.y = 200,.h = 72,.w = 180 };

	SDL_Rect noob =     { .x = 190 ,.y = 40, .h = 72,.w = 180 };
	SDL_Rect easy =     { .x = 190 ,.y = 132,.h = 72,.w = 180 };
	SDL_Rect moderate = { .x = 190 ,.y = 224,.h = 72,.w = 180 };
	SDL_Rect hard =     { .x = 190 ,.y = 316,.h = 72,.w = 180 };
	SDL_Rect expert =   { .x = 190 ,.y = 408,.h = 72,.w = 180 };
	 
	SDL_Rect white = { .x = 100 , .y = 120,.h = 195,.w = 97 };
	SDL_Rect black = { .x = 350  ,.y = 120,.h = 195,.w = 97 };

	widgets[0] = createButton(renderer, &back,  "./back_active.bmp", CHESS_BACK_BUTTON);
	widgets[1] = createButton(renderer, &next,  "./next_unactive.bmp", CHESS_NEXT_BUTTON);
	widgets[2] = createButton(renderer, &start, "./start_nonactive.bmp", CHESS_START_BUTTON);
	
	widgets[3] = createButton(renderer, &onep, "./onep_active.bmp", CHESS_ONEPLAYER_BUTTON);
	widgets[4] = createButton(renderer, &twop, "./twop_active.bmp", CHESS_TWOPLAYERS_BUTTON);

	widgets[5] = createButton(renderer, &noob,     "./noob_active.bmp"	  , CHESS_NOOB_BUTTON);
	widgets[6] = createButton(renderer, &easy,	   "./easy_active.bmp"	  , CHESS_EASY_BUTTON);
	widgets[7] = createButton(renderer, &moderate, "./moderate_active.bmp", CHESS_MODERATE_BUTTON);
	widgets[8] = createButton(renderer, &hard,     "./hard_active.bmp"	  , CHESS_HARD_BUTTON);

	widgets[9] =  createButton(renderer, &white,  "./white_active.bmp"  , CHESS_WHITE_BUTTON);
	widgets[10] = createButton(renderer, &black,  "./black_active.bmp"  , CHESS_BLACK_BUTTON);
	widgets[11] = createButton(renderer, &expert, "./expert_active.bmp" , CHESS_EXPERT_BUTTON);

	for (int i = 0; i < 12; i++)
	{
		if (!widgets[i])
		{
			printf("ERROR SDL: unable to create the window's buttons\n");
			for (int j = 0; j < 12; j++)
			{
				if (widgets[j])
					destroyWidget(widgets[j]);
			}
			free(widgets);
			return NULL;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		widgets[i]->isVisible = false;
		widgets[i]->isActive = false;
		widgets[i]->isDragLegal = false;
		widgets[i]->isMoving = false;
		widgets[i]->endOfDrag = false;
		widgets[i]->isActivateLegal = true;
		if((i==1) || (i==2)) //next & start buttons 
			widgets[i]->isActivateLegal = false;
	}

	return widgets;
}


ChessWindow* createSettingsWindow(Uint32 winMode, chessGame* game)
{
	if (!game)
		return NULL;

	ChessWindow* res = malloc(sizeof(ChessWindow));
	if (!res)
		return NULL;
	chessSettingsWindow* data = malloc(sizeof(chessSettingsWindow));
	if (!data)
	{
		free(res);
		return NULL;
	}
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,settings_width,settings_height, winMode);
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

	Widget** widgets = createSettingsWindowWidgets(renderer);
	if (!widgets)
	{
		printf("ERROR: unable to create window's buttons: %s\n", SDL_GetError());
		free(res);
		free(data);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window);	  //NULL safe
		return NULL;
	}
	 
	data->Widgets = widgets;
	data->numOfWidgets = 12;
	data->setType = CHESS_MODE_SET;
	data->window = window;
	data->windowRenderer = renderer;
		
	data->Widgets[NEXT]->isVisible = true;
	data->Widgets[BACK]->isVisible = true;
	data->Widgets[ONEP]->isVisible = true;
	data->Widgets[TWOP]->isVisible = true;

	res->data = (void*)data;
	res->destroyWindow = destroySettingsWindow;
	res->drawWindow = drawSettingsWindow;
	res->handleEventWindow = handleEventSettingsWindow;
	res->type = CHESS_SETTINGS_WINDOW;
	res->game = game;
	return res;
}


void destroySettingsWindow(ChessWindow* src)
{
	if (!src)
		return;

	chessSettingsWindow* data = (chessSettingsWindow*)src->data;
	for (int i = 0; i < data->numOfWidgets; i++)
	{
		destroyWidget(data->Widgets[i]);
	}
	free(data->Widgets);

	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}


void drawSettingsWindow(ChessWindow* src)
{
	if (!src)
		return;
	
	chessSettingsWindow* data = (chessSettingsWindow*)src->data;

	///////////////////////////draw background///////////////////////////
	SDL_Surface* surf = SDL_LoadBMP("./load_background.bmp");
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

	///////////////////////////draw the widgets///////////////////////////
	for (int i = 0; i < data->numOfWidgets; i++) 
	{
		if (data->Widgets[i]->isVisible)
			data->Widgets[i]->drawWidget(data->Widgets[i]);
		if ((data->Widgets[i]->isVisible) && (data->Widgets[i]->widget_type == CHESS_NEXT_BUTTON)
			&&(data->Widgets[i]->isActivateLegal))
			updateButtonTexture(data->Widgets[i], "./next_active.bmp");
		if ((data->Widgets[i]->isVisible) && (data->Widgets[i]->widget_type == CHESS_START_BUTTON)
			&& (data->Widgets[i]->isActivateLegal))
			updateButtonTexture(data->Widgets[i], "./start_active.bmp");
	}
	
	SDL_Delay(50);
	SDL_RenderPresent(data->windowRenderer);
}


WINDOW_EVENT handleEventSettingsWindow(ChessWindow* src, SDL_Event* event)
{
	if ((!src) || (!event))
		return CHESS_EMPTY_WINDOWEVENT;

	chessSettingsWindow* windata = (chessSettingsWindow*)src->data;

	while (1)
	{
	begin:
		while (SDL_PollEvent(event))
		{
			if (!((event->type == SDL_MOUSEBUTTONDOWN)  && (event->button.button == SDL_BUTTON_LEFT)) &&
				!((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT)))
				goto begin;

			for (int i = 0; i<windata->numOfWidgets; i++)
			{
				windata->Widgets[i]->handleEvent(windata->Widgets[i], event);
				SDL_RenderPresent(windata->windowRenderer);
				if ((windata->Widgets[i]->isActive) && (windata->Widgets[i]->isActivateLegal))
				{
					switch (windata->Widgets[i]->widget_type)
					{
					case CHESS_EMPTY_BUTTON:
						return CHESS_EMPTY_WINDOWEVENT;

					case CHESS_START_BUTTON:
						windata->Widgets[i]->isActive = false;
						return CHESS_STARTGAME_WINDOWEVENT;

					case CHESS_BACK_BUTTON:
						windata->Widgets[i]->isActive = false;
						updateButtonTexture(windata->Widgets[i], "./back_pressed.bmp");
						return CHESS_HOME_WINDOWEVENT;

					case CHESS_NEXT_BUTTON:
						windata->Widgets[i]->isActive = false;
						SDL_DestroyRenderer(windata->windowRenderer);
						free(windata->Widgets);

						windata->windowRenderer = SDL_CreateRenderer(windata->window, -1, SDL_RENDERER_ACCELERATED);
						if (!windata->windowRenderer)
						{
							printf("ERROR: unable to create a renderer: %s\n", SDL_GetError());
							return CHESS_EMPTY_WINDOWEVENT;
						}

						windata->Widgets = createSettingsWindowWidgets(windata->windowRenderer);
						if (!windata->Widgets)
						{
							printf("ERROR: unable to create window's buttons: %s\n", SDL_GetError());
							return CHESS_EMPTY_WINDOWEVENT;
						}

						if (windata->setType == CHESS_MODE_SET)
						{
							windata->setType = CHESS_DIFFICULTY_SET;
							for (int j = 0; j < windata->numOfWidgets; j++)
								windata->Widgets[j]->isVisible = false;
							windata->Widgets[BACK]->isVisible = true;
							windata->Widgets[NEXT]->isVisible = true;
							windata->Widgets[NOOB]->isVisible = true;
							windata->Widgets[EASY]->isVisible = true;
							windata->Widgets[MODERATE]->isVisible = true;
							windata->Widgets[HARD]->isVisible = true;
							windata->Widgets[EXPERT]->isVisible = true;

						}
						else if (windata->setType == CHESS_DIFFICULTY_SET)
						{
							windata->setType = CHESS_COLOR_SET;
							for (int j = 0; j < windata->numOfWidgets; j++)
								windata->Widgets[j]->isVisible = false;
							windata->Widgets[BACK]->isVisible = true;
							windata->Widgets[START]->isVisible = true;
							windata->Widgets[WHITE]->isVisible = true;
							windata->Widgets[BLACK]->isVisible = true;
							updateButtonTexture(windata->Widgets[START], "./start_nonactive.bmp");
							windata->Widgets[START]->isActivateLegal = false;
						}
						src->data = (void*)windata; 
						break;

					case CHESS_ONEPLAYER_BUTTON:
						updateButtonTexture(windata->Widgets[TWOP], "./twop_active.bmp");
						updateButtonTexture(windata->Widgets[NEXT], "./next_active.bmp");
						windata->Widgets[NEXT]->isActivateLegal = true;
						windata->Widgets[NEXT]->isVisible = true;
						windata->Widgets[START]->isVisible = false;
						src->game->gameMode = ONE_PLAYER;
						src->game->currentPlayer = WHITES;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_TWOPLAYERS_BUTTON:
						updateButtonTexture(windata->Widgets[ONEP], "./onep_active.bmp");
						windata->Widgets[NEXT]->isVisible = false;
						windata->Widgets[START]->isVisible = true;
						windata->Widgets[START]->isActivateLegal = true;
						src->game->gameMode = TWO_PLAYERS;
						src->game->currentPlayer = WHITES;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_NOOB_BUTTON:
						updateButtonTexture(windata->Widgets[EASY],		"./easy_active.bmp");	
						updateButtonTexture(windata->Widgets[MODERATE], "./moderate_active.bmp");
						updateButtonTexture(windata->Widgets[HARD],		"./hard_active.bmp");
						updateButtonTexture(windata->Widgets[EXPERT], "./expert_active.bmp");
						windata->Widgets[i]->isActive = false;		 
						if (!windata->Widgets[NEXT]->isActivateLegal)
						{
							updateButtonTexture(windata->Widgets[NEXT], "./next_active.bmp");
							windata->Widgets[NEXT]->isActivateLegal = true;
						}
						src->game->difficulty = 1; 
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_EASY_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB],     "./noob_active.bmp"); 
						updateButtonTexture(windata->Widgets[MODERATE], "./moderate_active.bmp");
						updateButtonTexture(windata->Widgets[HARD],     "./hard_active.bmp");
						updateButtonTexture(windata->Widgets[EXPERT], "./expert_active.bmp");

						windata->Widgets[i]->isActive = false;
						if (!windata->Widgets[NEXT]->isActivateLegal)
						{
							updateButtonTexture(windata->Widgets[NEXT], "./next_active.bmp");
							windata->Widgets[NEXT]->isActivateLegal = true;
						}
						src->game->difficulty = 2;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_MODERATE_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB], "./noob_active.bmp"); 
						updateButtonTexture(windata->Widgets[EASY], "./easy_active.bmp");
						updateButtonTexture(windata->Widgets[HARD], "./hard_active.bmp");
						updateButtonTexture(windata->Widgets[EXPERT], "./expert_active.bmp");

						windata->Widgets[i]->isActive = false;
						if (!windata->Widgets[NEXT]->isActivateLegal)
						{
							updateButtonTexture(windata->Widgets[NEXT], "./next_active.bmp");
							windata->Widgets[NEXT]->isActivateLegal = true;
						}
						src->game->difficulty = 3;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_HARD_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB],     "./noob_active.bmp"); 
						updateButtonTexture(windata->Widgets[EASY],     "./easy_active.bmp");
						updateButtonTexture(windata->Widgets[MODERATE], "./moderate_active.bmp");
						updateButtonTexture(windata->Widgets[EXPERT],   "./expert_active.bmp");

						windata->Widgets[i]->isActive = false;
						if (!windata->Widgets[NEXT]->isActivateLegal)
						{
							updateButtonTexture(windata->Widgets[NEXT], "./next_active.bmp");
							windata->Widgets[NEXT]->isActivateLegal = true;
						}
						src->game->difficulty = 4;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_EXPERT_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB], "./noob_active.bmp");
						updateButtonTexture(windata->Widgets[EASY], "./easy_active.bmp");
						updateButtonTexture(windata->Widgets[MODERATE], "./moderate_active.bmp");
						updateButtonTexture(windata->Widgets[HARD], "./hard_active.bmp");
						windata->Widgets[i]->isActive = false;
						if (!windata->Widgets[NEXT]->isActivateLegal)
						{
							updateButtonTexture(windata->Widgets[NEXT], "./next_active.bmp");
							windata->Widgets[NEXT]->isActivateLegal = true;
						}
						src->game->difficulty = 5;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_WHITE_BUTTON:
						updateButtonTexture(windata->Widgets[BLACK], "./black_active.bmp");
						windata->Widgets[i]->isActive = false;
						if (!(windata->Widgets[START]->isActivateLegal))
						{
							updateButtonTexture(windata->Widgets[START], "./start_active.bmp");
							windata->Widgets[START]->isActivateLegal = true;
						}
						src->game->humanPlayerColor = WHITES;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_BLACK_BUTTON:
						updateButtonTexture(windata->Widgets[WHITE], "./white_active.bmp");
						windata->Widgets[i]->isActive = false;
						if (!windata->Widgets[START]->isActivateLegal)
						{
							updateButtonTexture(windata->Widgets[START], "./start_active.bmp");
							windata->Widgets[START]->isActivateLegal = true;
						}
						src->game->humanPlayerColor = BLACKS;
						windata->Widgets[i]->isActive = false;
						break;

					default:
						return CHESS_EMPTY_WINDOWEVENT;
					}

					drawSettingsWindow(src);
					goto begin;
				}
			}
		}
	}
	
	return CHESS_EMPTY_WINDOWEVENT;
}


