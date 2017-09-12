#include <stdlib.h>
#include "ChessGUI_SettingsWindow.h"
#include "Button.h"

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

Widget** createSettingsWindowConstWidgets(SDL_Renderer* renderer)
{
	if (renderer == NULL)
	{
		return NULL;
	}

	Widget** widgets = malloc(sizeof(Widget*) * 11);
	
	if (widgets == NULL)
	{
		return NULL;
	}
	
	SDL_Rect back =		{ .x = 70 ,.y = 500,.h = 72,.w = 180 };
	SDL_Rect next =		{ .x = 300, .y = 500,.h = 72,.w = 180 };
	SDL_Rect start =	{ .x = 300, .y = 500,.h = 72,.w = 180 };
	
	SDL_Rect onep = { .x = 70 ,.y = 200,.h = 72,.w = 180 };
	SDL_Rect twop = { .x = 300,.y = 200,.h = 72,.w = 180 };

	SDL_Rect noob = { .x = 150 ,.y = 150,.h = 72,.w = 180 };
	SDL_Rect eazy = { .x = 150 ,.y = 242,.h = 72,.w = 180 };
	SDL_Rect moderate = { .x = 150 ,.y = 334,.h = 72,.w = 180 };
	SDL_Rect hard = { .x = 150 ,.y = 426,.h = 72,.w = 180 };
	
	SDL_Rect white = { .x = 300 ,.y = 200,.h = 70,.w = 70 };
	SDL_Rect black = { .x = 70  ,.y = 200,.h = 70,.w = 70 };

	widgets[0] = createButton(renderer, &back,  "./back_active.bmp", CHESS_BACK_BUTTON);
	widgets[1] = createButton(renderer, &next,  "./next_active.bmp", CHESS_NEXT_BUTTON);
	widgets[2] = createButton(renderer, &start, "./button_base.bmp", CHESS_START_BUTTON);
	
	widgets[3] = createButton(renderer, &onep, "./button_base.bmp", CHESS_ONEPLAYER_BUTTON);
	widgets[4] = createButton(renderer, &twop, "./button_base.bmp", CHESS_TWOPLAYERS_BUTTON);

	widgets[5] = createButton(renderer, &noob, "./button_base.bmp", CHESS_NOOB_BUTTON);
	widgets[6] = createButton(renderer, &eazy, "./button_base.bmp", CHESS_EASY_BUTTON);
	widgets[7] = createButton(renderer, &moderate, "./button_base.bmp", CHESS_MODERATE_BUTTON);
	widgets[8] = createButton(renderer, &hard, "./button_base.bmp", CHESS_HARD_BUTTON);

	widgets[9] =  createButton(renderer, &white, "./button_base.bmp", CHESS_WHITE_BUTTON);
	widgets[10] = createButton(renderer, &black, "./button_base.bmp", CHESS_BLACK_BUTTON);

	for (int i = 0; i < 11; i++)
	{
		if (widgets[i] == NULL)
		{
			for (int j = 0; j < 11; j++)
			{
				destroyWidget(widgets[j]);
			}
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}


ChessWindow* createSettingsWindow(Uint32 winMode)
{
	ChessWindow* res = malloc(sizeof(ChessWindow));
	chessSettingsWindow* data = malloc(sizeof(chessSettingsWindow));
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,settings_width,settings_height, winMode);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Widget** widgets =		 createSettingsWindowConstWidgets(renderer);

	if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL)
	{
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	data->Widgets = widgets;
	data->numOfWidgets = 11;
	data->setType = CHESS_MODE_SET;
	data->window = window;
	data->windowRenderer = renderer;
	
	for (int i = 0; i < data->numOfWidgets; i++)
	{
		data->Widgets[i]->isVisible = false;
		data->Widgets[i]->isActive  = false; 
	}
	data->Widgets[NEXT]->isVisible = true;
	data->Widgets[BACK]->isVisible = true;
	data->Widgets[ONEP]->isVisible = true;
	data->Widgets[TWOP]->isVisible = true;

	res->data = (void*)data;
	res->destroyWindow = destroySettingsWindow;
	res->drawWindow = drawSettingsWindow;
	res->handleEventWindow = handleEventSettingsWindow;
	res->type = CHESS_SETTINGS_WINDOW;
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

	SDL_SetRenderDrawColor(data->windowRenderer, 255, 0, 0, 255);
	SDL_FillRect(NULL, NULL, 0x000000);
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

	///////////////draw the widgets 

	for (int i = 0; i < data->numOfWidgets; i++) //draw only next and back buttons
	{
		if (data->Widgets[i]->isVisible)
			data->Widgets[i]->drawWidget(data->Widgets[i]);
		if ((data->Widgets[i]->isVisible) && (data->Widgets[i]->widget_type == CHESS_NEXT_BUTTON))
			updateButtonTexture(data->Widgets[i], "./next_active.bmp");
		if ((data->Widgets[i]->isVisible) && data->Widgets[i]->widget_type == CHESS_START_BUTTON)
		updateButtonTexture(data->Widgets[i], "./start_active.bmp");
	}
	
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
		while (SDL_PollEvent(event))
		{
			for (int i = 0; i<windata->numOfWidgets; i++)//=((i+1) % windata->numOfWidgets))
			{
				/*SDL_RenderClear(windata->windowRenderer);
				drawSettingsWindow(src);
				while (SDL_PollEvent != 0)
				if (event == quit)
				SDL_Quit;
				SDL_RenderPresent(windata->windowRenderer);
				*/
				bool refresh = false; 
				windata->Widgets[i]->handleEvent(windata->Widgets[i], event);
				if (windata->Widgets[i]->isActive)//windata->widgets[i]->data->isPressed)
				{
					switch (windata->Widgets[i]->widget_type)
					{
					case CHESS_EMPTY_BUTTON:
						return CHESS_EMPTY_WINDOWEVENT;

					case CHESS_START_BUTTON:
						return CHESS_STARTGAME_WINDOWEVENT;

					case CHESS_BACK_BUTTON:
						return CHESS_HOME_WINDOWEVENT;

					case CHESS_NEXT_BUTTON:
						if (windata->setType == CHESS_MODE_SET)
						{
							windata->setType = CHESS_DIFFICULTY_SET;
							for (int j = 0; j < windata->numOfWidgets; j++)
								windata->Widgets[i]->isVisible = false;
							windata->Widgets[BACK]->isVisible = true;
							windata->Widgets[NEXT]->isVisible = true;
							windata->Widgets[NOOB]->isVisible = true;
							windata->Widgets[EASY]->isVisible = true;
							windata->Widgets[MODERATE]->isVisible = true;
							windata->Widgets[HARD]->isVisible = true;
							//SDL_FillRect(NULL, NULL, 0x000000);
							
							
						}
						else if (windata->setType == CHESS_DIFFICULTY_SET)
						{
							windata->setType = CHESS_COLOR_SET;
							for (int j = 0; j < windata->numOfWidgets; j++)
								windata->Widgets[i]->isVisible = false;
							windata->Widgets[BACK]->isVisible = true;
							windata->Widgets[START]->isVisible = true;
							windata->Widgets[WHITE]->isVisible = true;
							windata->Widgets[BLACK]->isVisible = true;
							//drawSettingsWindow(src);
						}
						//SDL_RenderClear(windata->windowRenderer);
						////windata->Widgets[i]->isActive = false;
						////i = -1;
						//SDL_Surface* surf = SDL_LoadBMP("./load_background.bmp");
						//SDL_Texture * background = SDL_CreateTextureFromSurface(windata->windowRenderer, surf);
						//if (surf == NULL || background == NULL)
						//{
						//	free(surf);
						//	SDL_DestroyTexture(background);
						//	return;
						//}
						//SDL_FreeSurface(surf);
						//if (SDL_SetTextureBlendMode(background, SDL_BLENDMODE_MOD) != 0)
						//{
						//	printf("ERROR: unable to blend background texture: %s\n", SDL_GetError());
						//}
						//SDL_RenderCopy(windata->windowRenderer, background, NULL, NULL);
						//SDL_DestroyTexture(background);
						//SDL_RenderClear(windata->windowRenderer);
						drawSettingsWindow(src);
						//SDL_RenderPresent(windata->windowRenderer);
						
						refresh = true;
						break;

					case CHESS_ONEPLAYER_BUTTON:
						updateButtonTexture(windata->Widgets[TWOP], "./twoPlayer_active.bmp");
						windata->Widgets[NEXT]->isVisible = true;
						windata->Widgets[START]->isVisible = false;
						//windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

					case CHESS_TWOPLAYERS_BUTTON:
						updateButtonTexture(windata->Widgets[ONEP], "./onePlayer_active.bmp");
						windata->Widgets[NEXT]->isVisible = false;
						windata->Widgets[START]->isVisible = true;
						windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

						//if I pressed "noob" and then "easy" I want the noob button to go back to the active texture, 
						//and not pressed texture 

					case CHESS_NOOB_BUTTON:
						updateButtonTexture(windata->Widgets[EASY], "./button_base.bmp");	//the active texture 
						updateButtonTexture(windata->Widgets[MODERATE], "./button_base.bmp");
						updateButtonTexture(windata->Widgets[HARD], "./button_base.bmp");
						windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

					case CHESS_EASY_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB], "./button_base.bmp");//the active texture 
						updateButtonTexture(windata->Widgets[MODERATE], "./button_base.bmp");
						updateButtonTexture(windata->Widgets[HARD], "./button_base.bmp");
						windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

					case CHESS_MODERATE_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB], "./button_base.bmp");//the active texture 
						updateButtonTexture(windata->Widgets[EASY], "./button_base.bmp");
						updateButtonTexture(windata->Widgets[HARD], "./button_base.bmp");
						windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

					case CHESS_HARD_BUTTON:
						updateButtonTexture(windata->Widgets[NOOB], "./button_base.bmp");//the active texture 
						updateButtonTexture(windata->Widgets[EASY], "./button_base.bmp");
						updateButtonTexture(windata->Widgets[MODERATE], "./button_base.bmp");
						windata->Widgets[i]->isActive = false;
						//	drawSettingsWindow(src);
						break;

					case CHESS_WHITE_BUTTON:
						updateButtonTexture(windata->Widgets[BLACK], "./button_base.bmp");//the active texture
						windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

					case CHESS_BLACK_BUTTON:
						updateButtonTexture(windata->Widgets[WHITE], "./button_base.bmp");//the active texture
						windata->Widgets[i]->isActive = false;
						//drawSettingsWindow(src);
						break;

					default:
						eventType = CHESS_EMPTY_WINDOWEVENT;
						break;
					}
				}
				if(refresh)
					break;

			}

			break;
		}
		}
		
	
	return eventType;
}


