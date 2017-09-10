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
#define EAZY 6
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
	widgets[6] = createButton(renderer, &eazy, "./button_base.bmp", CHESS_EAZY_BUTTON);
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
	//set isVisible 



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
	SDL_RenderClear(data->windowRenderer);
	
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
	
	for (int i = 0; i < data->numOfWidgets; i++) //draw only next and back buttons
	{
		if(data->Widgets[i]->isVisible)
			data->Widgets[i]->drawWidget(data->Widgets[i]);
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
	int i=0;
	for (int i = 0; i<windata->numOfWidgets; i=((i+1)% windata->numOfWidgets))
	{
		windata->Widgets[i]->handleEvent(windata->Widgets[i], event);
		if (windata->Widgets[i]->isActive)//windata->widgets[i]->data->isPressed)
		{
			switch (windata->Widgets[i]->widget_type)
			{
			case CHESS_EMPTY_BUTTON:
			{
				eventType = CHESS_EMPTY_WINDOWEVENT;
				break;
			}
			case CHESS_START_BUTTON:
			{
				return CHESS_STARTGAME_WINDOWEVENT;
			}
			case CHESS_BACK_BUTTON:
			{
				return CHESS_HOME_WINDOWEVENT;
				//break;
			}
			case CHESS_NEXT_BUTTON:
			{
				//need to take care of the isVisible here (for example : next ->visible, start->not visible ... ) 
				if (windata->setType == CHESS_MODE_SET)
				{
					windata->setType = CHESS_DIFFICULTY_SET;
					windata->Widgets[BACK]->isVisible = true; 
					//and so on ... 

					drawSettingsWindow(src);
				}
				else if (windata->setType == CHESS_DIFFICULTY_SET)
				{
					windata->setType = CHESS_COLOR_SET;

					//set isVisible 

					drawSettingsWindow(src);
				}
				break;
			}
			
			default:
			{
				eventType = CHESS_EMPTY_WINDOWEVENT;
				break;
			}
			}
		}
	}

	//case CHESS_ONEPLAYER_BUTTON:
	//{
	//	//coloring the button + replace next with start button + change setType + drawWindow + 
	//}
	return eventType;
}


