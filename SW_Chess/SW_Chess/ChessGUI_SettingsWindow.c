#include <stdlib.h>
#include "ChessGUI_SettingsWindow.h"
#include "Button.h"
#include "Chess_gameUtils.h"


static const settings_width = 550;
static const settings_height = 700;

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
	if (renderer == NULL)
	{
		return NULL;
	}

	Widget** widgets = malloc(sizeof(Widget*) * 12);
	
	if (widgets == NULL)
	{
		return NULL;
	}
	
	SDL_Rect back =		{ .x = 70 ,.y = 500,.h = 72,.w = 180 };
	SDL_Rect next =		{ .x = 300, .y = 500,.h = 72,.w = 180 };
	SDL_Rect start =	{ .x = 300, .y = 500,.h = 72,.w = 180 };
	
	SDL_Rect onep = { .x = 70 ,.y = 200,.h = 72,.w = 180 };
	SDL_Rect twop = { .x = 300,.y = 200,.h = 72,.w = 180 };

	SDL_Rect noob =     { .x = 190 ,.y = 50, .h = 72,.w = 180 };
	SDL_Rect easy =     { .x = 190 ,.y = 142,.h = 72,.w = 180 };
	SDL_Rect moderate = { .x = 190 ,.y = 234,.h = 72,.w = 180 };
	SDL_Rect hard =     { .x = 190 ,.y = 326,.h = 72,.w = 180 };
	SDL_Rect expert =   { .x = 190 ,.y = 418,.h = 72,.w = 180 };

	 
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

	widgets[9] =  createButton(renderer, &white, "./white_active.bmp", CHESS_WHITE_BUTTON);
	widgets[10] = createButton(renderer, &black, "./black_active.bmp", CHESS_BLACK_BUTTON);
	widgets[11] = createButton(renderer, &expert, "./expert_active.bmp", CHESS_EXPERT_BUTTON);


	for (int i = 0; i < 12; i++)
	{
		if (widgets[i] == NULL)
		{
			for (int j = 0; j < 12; j++)
			{
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

	}

	return widgets;
}


ChessWindow* createSettingsWindow(Uint32 winMode, chessGame* game)
{
	ChessWindow* res = malloc(sizeof(ChessWindow));
	chessSettingsWindow* data = malloc(sizeof(chessSettingsWindow));
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,settings_width,settings_height, winMode);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//chessGame* game = createChessGame(6, ONE_PLAYER, WHITES, 2);

	Widget** widgets =		 createSettingsWindowWidgets(renderer);

	if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL)// || game == NULL)
	{
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		//destroyChessGame(game);

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
	if (src == NULL)
	{
		return;
	}
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
	if (src == NULL)
		return;
	
	chessSettingsWindow* data = (chessSettingsWindow*)src->data;

	//SDL_SetRenderDrawColor(data->windowRenderer, 255,255, 255, 0);
	//SDL_FillRect(NULL, NULL, 0x000000);
	//SDL_RenderClear(data->windowRenderer);
	
	///////////////////////////draw background///////////////////////////
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
	if (src == NULL || event == NULL)
	{
		return CHESS_EMPTY_WINDOWEVENT;
	}
	chessSettingsWindow* windata = (chessSettingsWindow*)src->data;
	WINDOW_EVENT eventType = CHESS_EMPTY_WINDOWEVENT;
	//int i=0;


	while (1)
	{
	//	SDL_WaitEvent(&event);
begin:
		while (SDL_PollEvent(event))
		{
			if (!(event->type == SDL_MOUSEBUTTONDOWN  && event->button.button == SDL_BUTTON_LEFT) &&
				!(event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT))
				goto begin;

			for (int i = 0; i<windata->numOfWidgets; i++)//=((i+1) % windata->numOfWidgets))
			{
				//	bool refresh = false; 
				windata->Widgets[i]->handleEvent(windata->Widgets[i], event);
				SDL_RenderPresent(windata->windowRenderer);
				if (windata->Widgets[i]->isActive && windata->Widgets[i]->isActivateLegal)//windata->widgets[i]->data->isPressed)
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
						windata->Widgets = createSettingsWindowWidgets(windata->windowRenderer);
						if (windata->windowRenderer == NULL || windata->Widgets == NULL)
						{
							free(windata->Widgets);
							SDL_DestroyRenderer(windata->windowRenderer);
							return CHESS_EMPTY_WINDOWEVENT;		//return CHESS_ERROR_EVENT ???????????????????
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
						src->game->gameMode = TWO_PLAYERS;
						src->game->currentPlayer = WHITES;
						windata->Widgets[i]->isActive = false;
						break;

					case CHESS_NOOB_BUTTON:
						updateButtonTexture(windata->Widgets[EASY],		"./easy_active.bmp");	
						updateButtonTexture(windata->Widgets[MODERATE], "./moderate_active.bmp");
						updateButtonTexture(windata->Widgets[HARD],		"./hard_active.bmp");
						updateButtonTexture(windata->Widgets[EXPERT], "./expert_active.bmp");

						windata->Widgets[i]->isActive = false;		///////////////////////////////check this 
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
						eventType = CHESS_EMPTY_WINDOWEVENT;
						break;
					}
					drawSettingsWindow(src);

				}
			}

			break;
		}
		}
		
	
	return eventType;
}


