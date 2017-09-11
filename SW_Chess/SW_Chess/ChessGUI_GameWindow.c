#include <stdlib.h>
#include "ChessGUI_GameWindow.h"
#include "Button.h"
#include "ChessGUI_Utils.h"
#include "Chess_gameUtils.h"

////I think I don't need it here.. late at night cheak tomorrow !! 
//#define PAWN_WHITE 
//#define PAWN_BLACK 
//
//#define BISHOP_WHITE
//#define BISHOP_BLACK
//
//#define ROOK_WHITE 
//#define ROOK_BLACK 
//
//#define KNIGHT_WHITE
//#define KNIGHT_BLACK
//
//#define QUEEN_WHITE 
//#define QUEEN_BLACK 
//
//#define KING_WHITE
//#define KING_BLACK


static const game_width = 900;
static const game_height = 700;

//Helper function to create buttons in the simple window;
Widget** createGameWindowWidgets(SDL_Renderer* renderer, ChessWindow* window)
{	
	if (renderer == NULL) 
	{
		return NULL;
	}
	Widget** widgets = malloc(sizeof(Widget*) * 38);
	if (widgets == NULL) 
	{
		return NULL;
	}
	//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_Rect restart =  { .x = 50,.y = 50, .h = 72,.w = 180 };
	SDL_Rect save    =  { .x = 50,.y = 142,.h = 72,.w = 180 };
	SDL_Rect load	 =  { .x = 50,.y = 234,.h = 72,.w = 180 };
	SDL_Rect undo	 =  { .x = 50,.y = 326,.h = 72,.w = 180 };
	SDL_Rect home	 =  { .x = 50,.y = 418,.h = 72,.w = 180 };
	SDL_Rect exit	 =  { .x = 50,.y = 510,.h = 72,.w = 180 };
	
	
	SDL_Rect rookWhite =	{.x = window->game->gameGUIBoard[0][0].x,.y = window->game->gameGUIBoard[0][0].y,
							 .h = window->game->gameGUIBoard[0][0].h,.w = window->game->gameGUIBoard[0][0].w };

	SDL_Rect knightWhite =  {.x = window->game->gameGUIBoard[0][1].x,.y = window->game->gameGUIBoard[0][1].y,
							 .h = window->game->gameGUIBoard[0][1].h,.w = window->game->gameGUIBoard[0][1].w };

	SDL_Rect bishopWhite =  {.x = window->game->gameGUIBoard[0][2].x,.y = window->game->gameGUIBoard[0][2].y,
							 .h = window->game->gameGUIBoard[0][2].h,.w = window->game->gameGUIBoard[0][2].w };

	SDL_Rect queenWhite =   {.x = window->game->gameGUIBoard[0][3].x,.y = window->game->gameGUIBoard[0][3].y,
							 .h = window->game->gameGUIBoard[0][3].h,.w = window->game->gameGUIBoard[0][3].w };

	SDL_Rect kingWhite =    {.x = window->game->gameGUIBoard[0][4].x,.y = window->game->gameGUIBoard[0][4].y,
						     .h = window->game->gameGUIBoard[0][4].h,.w = window->game->gameGUIBoard[0][4].w };

	SDL_Rect bishopWhite2 =  {.x = window->game->gameGUIBoard[0][5].x,.y = window->game->gameGUIBoard[0][5].y,
							  .h = window->game->gameGUIBoard[0][5].h,.w = window->game->gameGUIBoard[0][5].w };

	SDL_Rect knightWhite2 =  {.x = window->game->gameGUIBoard[0][6].x,.y = window->game->gameGUIBoard[0][6].y,
							  .h = window->game->gameGUIBoard[0][6].h,.w = window->game->gameGUIBoard[0][6].w };

	SDL_Rect rookWhite2 =    {.x = window->game->gameGUIBoard[0][7].x,.y = window->game->gameGUIBoard[0][7].y,
							  .h = window->game->gameGUIBoard[0][7].h,.w = window->game->gameGUIBoard[0][7].w };


	SDL_Rect rookBlack =    {.x = window->game->gameGUIBoard[7][0].x,.y = window->game->gameGUIBoard[7][0].y,
							 .h = window->game->gameGUIBoard[7][0].h,.w = window->game->gameGUIBoard[7][0].w };
															 
	SDL_Rect knightBlack =  {.x = window->game->gameGUIBoard[7][1].x,.y = window->game->gameGUIBoard[7][1].y,
							 .h = window->game->gameGUIBoard[7][1].h,.w = window->game->gameGUIBoard[7][1].w };
															 
	SDL_Rect bishopBlack =  {.x = window->game->gameGUIBoard[7][2].x,.y = window->game->gameGUIBoard[7][2].y,
							 .h = window->game->gameGUIBoard[7][2].h,.w = window->game->gameGUIBoard[7][2].w };
															 
	SDL_Rect queenBlack =   {.x = window->game->gameGUIBoard[7][3].x,.y = window->game->gameGUIBoard[7][3].y,
							 .h = window->game->gameGUIBoard[7][3].h,.w = window->game->gameGUIBoard[7][3].w };
															 
	SDL_Rect kingBlack   =  {.x = window->game->gameGUIBoard[7][4].x,.y = window->game->gameGUIBoard[7][4].y,
							 .h = window->game->gameGUIBoard[7][4].h,.w = window->game->gameGUIBoard[7][4].w };
															 
	SDL_Rect bishopBlack2 = {.x = window->game->gameGUIBoard[7][5].x,.y = window->game->gameGUIBoard[7][5].y,
							 .h = window->game->gameGUIBoard[7][5].h,.w = window->game->gameGUIBoard[7][5].w };
															 
	SDL_Rect knightBlack2 = {.x = window->game->gameGUIBoard[7][6].x,.y = window->game->gameGUIBoard[7][6].y,
							 .h = window->game->gameGUIBoard[7][6].h,.w = window->game->gameGUIBoard[7][6].w };

	SDL_Rect rookBlack2 =   {.x = window->game->gameGUIBoard[7][7].x,.y = window->game->gameGUIBoard[7][7].y,
							 .h = window->game->gameGUIBoard[7][7].h,.w = window->game->gameGUIBoard[7][7].w };


	widgets[0]  = createButton(renderer, &restart,     "./button_base.bmp", CHESS_RESTART_BUTTON);
	widgets[1]  = createButton(renderer, &save,	       "./button_base.bmp", CHESS_SAVE_BUTTON);
	widgets[2]  = createButton(renderer, &load,	       "./button_base.bmp", CHESS_LOAD_BUTTON);
	widgets[3]  = createButton(renderer, &undo,        "./button_base.bmp", CHESS_UNDO_BUTTON);
	widgets[4]  = createButton(renderer, &home,        "./button_base.bmp", CHESS_HOME_BUTTON);
	widgets[5]  = createButton(renderer, &exit,        "./button_base.bmp", CHESS_QUIT_BUTTON);
	
	widgets[6] = createButton(renderer, &bishopWhite, "./button_base.bmp", CHESS_BISHOP_WHITE);
	widgets[7] = createButton(renderer, &bishopWhite2, "./button_base.bmp", CHESS_BISHOP_WHITE);

	widgets[8] = createButton(renderer, &bishopBlack, "./button_base.bmp", CHESS_BISHOP_BLACK);
	widgets[9] = createButton(renderer, &bishopBlack2, "./button_base.bmp", CHESS_BISHOP_BLACK);

	widgets[10] = createButton(renderer, &rookWhite, "./button_base.bmp",  CHESS_ROOK_WHITE);
	widgets[11] = createButton(renderer, &rookWhite2, "./button_base.bmp", CHESS_ROOK_WHITE);

	widgets[12] = createButton(renderer, &rookBlack, "./button_base.bmp",  CHESS_ROOK_BLACK);
	widgets[13] = createButton(renderer, &rookBlack2, "./button_base.bmp", CHESS_ROOK_BLACK);

	widgets[14] = createButton(renderer, &knightWhite, "./button_base.bmp",  CHESS_KNIGHT_WHITE);
	widgets[15] = createButton(renderer, &knightWhite2, "./button_base.bmp", CHESS_KNIGHT_WHITE);

	widgets[16] = createButton(renderer, &knightBlack, "./button_base.bmp",  CHESS_KNIGHT_BLACK);
	widgets[17] = createButton(renderer, &knightBlack2, "./button_base.bmp", CHESS_KNIGHT_BLACK);

	widgets[18] = createButton(renderer, &queenWhite, "./button_base.bmp", CHESS_QUEEN_WHITE);
	widgets[19] = createButton(renderer, &queenBlack, "./button_base.bmp", CHESS_QUEEN_BLACK);
	widgets[20] = createButton(renderer, &kingWhite, "./button_base.bmp", CHESS_KING_WHITE);
	widgets[21] = createButton(renderer, &kingBlack, "./button_base.bmp", CHESS_KING_BLACK);
	
	int place = 22;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		SDL_Rect pawnWhite =  {.x = window->game->gameGUIBoard[1][i].x,.y = window->game->gameGUIBoard[1][i].y,
							   .h = window->game->gameGUIBoard[0][0].h,.w = window->game->gameGUIBoard[0][0].w };
		SDL_Rect pawnBlack =  {.x = window->game->gameGUIBoard[6][i].x,.y = window->game->gameGUIBoard[6][i].y,
							   .h = window->game->gameGUIBoard[0][0].h,.w = window->game->gameGUIBoard[0][0].w };
		widgets[place]   = createButton(renderer, &pawnWhite, "./button_base.bmp", CHESS_PAWN_WHITE);
		widgets[place+1] = createButton(renderer, &pawnBlack, "./button_base.bmp", CHESS_PAWN_BLACK);
		place++;
	}
	
	
	for (int i = 0; i < 38; i++)
	{
		if (widgets[i] == NULL)
		{
			for (int j = 0; j < 38; j++)
			{
				destroyWidget(widgets[j]);
			}
			free(widgets);
			return NULL;
		}
	}
	
	return widgets;
}


ChessWindow* createGameWindow(Uint32 winMode)
{
	ChessWindow* res = malloc(sizeof(ChessWindow));
	chessGameWindow* data = malloc(sizeof(chessGameWindow));
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game_width, game_height, winMode);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	res->game = createChessGame(6, ONE_PLAYER, WHITES, 2);
	Widget** widgets = createGameWindowWidgets(renderer, res);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL)
	{
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	data->widgets = widgets;
	data->numOfWidgets = 38;
	data->window = window;
	data->windowRenderer = renderer;
	for(int j = 0; j < data->numOfWidgets; j++)
	{
		widgets[j]->isVisible = true; 
	}

	res->data = (void*)data;
	res->destroyWindow = destroyGameWindow;
	res->drawWindow = drawGameWindow;
	res->handleEventWindow = handleEventGameWindow;
	res->type = CHESS_GAME_WINDOW;
	return res;
}


void destroyGameWindow(ChessWindow* src) 
{
	if (src == NULL)
	{
		return;
	}
	chessGameWindow* data = (chessGameWindow*)src->data;
	for (int i=0; i < data->numOfWidgets; i++)
	{
		destroyWidget(data->widgets[i]);
	}
	free(data->widgets);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}


void drawGameWindow(ChessWindow* src) 
{
	if (src == NULL) 
	{
		return;
	}
	chessGameWindow* data = (chessGameWindow*)src->data;
	SDL_RenderClear(data->windowRenderer);

	//send to drawgame in utils - draw the board 
	drawGameBoard(data, src->game);

	//draw background
	SDL_Surface* surf = SDL_LoadBMP("./main_background.bmp");
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

	//Draw widgets
	for (int i = 0; i < data->numOfWidgets; i++)
	{
		if (data->widgets[i]->isVisible)
			data->widgets[i]->drawWidget(data->widgets[i]);
	}

	SDL_RenderPresent(data->windowRenderer);
}


WINDOW_EVENT handleEventGameWindow(ChessWindow* src, SDL_Event* event) 
{
	if (src == NULL || event == NULL) 
	{
		return CHESS_EMPTY_WINDOWEVENT;
	}
	chessGameWindow* windata = (chessGameWindow*)src->data;
	WINDOW_EVENT eventType = CHESS_EMPTY_WINDOWEVENT;
	for (int i = 0; i<windata->numOfWidgets; i++) //the complex loop , after fixing in setting - copy to this loop
	{
		windata->widgets[i]->handleEvent(windata->widgets[i], event);
		SDL_RenderPresent(windata->windowRenderer);
		if (windata->widgets[i]->isActive)
		{
			switch (windata->widgets[i]->widget_type)
			{
			case CHESS_EMPTY_BUTTON:
				return CHESS_EMPTY_WINDOWEVENT;
			case CHESS_RESTART_BUTTON: // think about it 
				return CHESS_STARTGAME_WINDOWEVENT;
			case CHESS_SAVE_BUTTON:
				return CHESS_SAVE_WINDOWEVENT;
			case CHESS_LOAD_BUTTON:
				return CHESS_LOAD_WINDOWEVENT;
			case CHESS_UNDO_BUTTON:
				//taking care here? or in main? i think here 
				break;
			case CHESS_HOME_BUTTON:
				return CHESS_HOME_WINDOWEVENT;
			case CHESS_QUIT_BUTTON:
				return CHESS_QUIT_WINDOWEVENT;
			
			//later on... 
			/*case CHESS_PAWN_WHITE:
				//check valid move ... 
			//and so on */
			default:
			{
				eventType = CHESS_EMPTY_WINDOWEVENT;
				break;
			}
			}
		}
		
	}
	return eventType;
}


