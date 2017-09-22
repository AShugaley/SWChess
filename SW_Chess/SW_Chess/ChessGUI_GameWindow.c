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
	SDL_Rect restart =  { .x = 80,.y = 70, .h = 72,.w = 180 };
	SDL_Rect save    =  { .x = 80,.y = 162,.h = 72,.w = 180 };
	SDL_Rect load	 =  { .x = 80,.y = 254,.h = 72,.w = 180 };
	SDL_Rect undo	 =  { .x = 80,.y = 346,.h = 72,.w = 180 };
	SDL_Rect home	 =  { .x = 80,.y = 438,.h = 72,.w = 180 };
	SDL_Rect exit	 =  { .x = 80,.y = 530,.h = 72,.w = 180 };
	
	
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

	widgets[0]  = createButton(renderer, &restart,     "./restart_active.bmp", CHESS_RESTART_BUTTON);
	widgets[1]  = createButton(renderer, &save,	       "./save_active.bmp", CHESS_SAVE_BUTTON);
	widgets[2]  = createButton(renderer, &load,	       "./load_active.bmp", CHESS_LOAD_BUTTON);
	widgets[3]  = createButton(renderer, &undo,        "./undo_nonactive.bmp", CHESS_UNDO_BUTTON);
	widgets[4]  = createButton(renderer, &home,        "./home_active.bmp", CHESS_HOME_BUTTON);
	widgets[5]  = createButton(renderer, &exit,        "./exit_active.bmp", CHESS_QUIT_BUTTON);
	
	widgets[6] = createButton(renderer, &bishopWhite,  "./bishop_white_active.bmp", CHESS_BISHOP_WHITE_BUTTON);
	widgets[7] = createButton(renderer, &bishopWhite2, "./bishop_white_active.bmp", CHESS_BISHOP_WHITE_BUTTON);

	widgets[6]->row =  0;
	widgets[6]->coll = 2;
	widgets[7]->row =  0;
	widgets[7]->coll = 5;

	widgets[8] = createButton(renderer, &bishopBlack,  "./bishop_black_active.bmp", CHESS_BISHOP_BLACK_BUTTON);
	widgets[9] = createButton(renderer, &bishopBlack2, "./bishop_black_active.bmp", CHESS_BISHOP_BLACK_BUTTON);
	
	widgets[8]->row = 7;
	widgets[8]->coll = 2;
	widgets[9]->row = 7;
	widgets[9]->coll = 5;
	
	widgets[10] = createButton(renderer, &rookWhite,  "./rook_white_active.bmp",  CHESS_ROOK_WHITE_BUTTON);
	widgets[11] = createButton(renderer, &rookWhite2, "./rook_white_active.bmp", CHESS_ROOK_WHITE_BUTTON);
	
	widgets[10]->row = 0;
	widgets[10]->coll = 0;
	widgets[11]->row = 0;
	widgets[11]->coll = 7;

	widgets[12] = createButton(renderer, &rookBlack,  "./rook_black_active.bmp",  CHESS_ROOK_BLACK_BUTTON);
	widgets[13] = createButton(renderer, &rookBlack2, "./rook_black_active.bmp", CHESS_ROOK_BLACK_BUTTON);

	widgets[12]->coll = 0;
	widgets[12]->row = 7;
	widgets[13]->row = 7;
	widgets[13]->coll = 7;

	widgets[14] = createButton(renderer, &knightWhite,  "./knight_white_active.bmp",  CHESS_KNIGHT_WHITE_BUTTON);
	widgets[15] = createButton(renderer, &knightWhite2, "./knight_white_active.bmp", CHESS_KNIGHT_WHITE_BUTTON);

	widgets[14]->row = 0;
	widgets[14]->coll = 1;
	widgets[15]->row = 0;
	widgets[15]->coll = 6;

	widgets[16] = createButton(renderer, &knightBlack,  "./knight_black_active.bmp",  CHESS_KNIGHT_BLACK_BUTTON);
	widgets[17] = createButton(renderer, &knightBlack2, "./knight_black_active.bmp", CHESS_KNIGHT_BLACK_BUTTON);

	widgets[16]->row = 7;
	widgets[16]->coll = 1;
	widgets[17]->row = 7;
	widgets[17]->coll = 6;

	widgets[18] = createButton(renderer, &queenWhite, "./queen_white_active.bmp", CHESS_QUEEN_WHITE_BUTTON);
	widgets[19] = createButton(renderer, &queenBlack, "./queen_black_active.bmp", CHESS_QUEEN_BLACK_BUTTON);
	widgets[20] = createButton(renderer, &kingWhite,  "./king_white_active.bmp", CHESS_KING_WHITE_BUTTON);
	widgets[21] = createButton(renderer, &kingBlack,  "./king_black_active.bmp", CHESS_KING_BLACK_BUTTON);

	widgets[18]->row = 0;
	widgets[18]->coll = 3;
	widgets[19]->row = 7;
	widgets[19]->coll = 3;
	widgets[20]->row = 0;
	widgets[20]->coll = 4;
	widgets[21]->row = 7;
	widgets[21]->coll = 4;
	
	int place = 22;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		SDL_Rect pawnWhite =  {.x = window->game->gameGUIBoard[1][i].x,.y = window->game->gameGUIBoard[1][i].y,
							   .h = window->game->gameGUIBoard[1][i].h,.w = window->game->gameGUIBoard[1][i].w };
		SDL_Rect pawnBlack =  {.x = window->game->gameGUIBoard[6][i].x,.y = window->game->gameGUIBoard[6][i].y,
							   .h = window->game->gameGUIBoard[6][i].h,.w = window->game->gameGUIBoard[6][i].w };
		widgets[place]   = createButton(renderer, &pawnWhite, "./pawn_white_active.bmp", CHESS_PAWN_WHITE_BUTTON);
		widgets[place]->row = 1;
		widgets[place]->coll = i;
		
		widgets[place+1] = createButton(renderer, &pawnBlack, "./pawn_black_active.bmp", CHESS_PAWN_BLACK_BUTTON);
		widgets[place+1]->row = 6;
		widgets[place+1]->coll = i;
		
		place+=2;
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
	
	for (int i = 0; i < 38; i++)
	{
		if(i<6)
			widgets[i]->isDragLegal = false;
		else
			widgets[i]->isDragLegal = true;
		widgets[i]->isMoving = false;
		widgets[i]->endOfDrag = false; 
	}

	return widgets;
}


ChessWindow* createGameWindow(Uint32 winMode)
{
	ChessWindow* res = malloc(sizeof(ChessWindow));
	chessGameWindow* data = malloc(sizeof(chessGameWindow));
	SDL_Window* window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game_width, game_height, winMode);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	chessGame* game = createChessGame(6, ONE_PLAYER, WHITES, 2);
	if (game == NULL)
	{
		destroyChessGame(game);
		return NULL;
	}
	res->game = game;
	Widget** widgets = createGameWindowWidgets(renderer, res);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL || widgets == NULL)
	{
		free(res);
		free(data);
		free(widgets);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
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
		return;
	
	chessGameWindow* data = (chessGameWindow*)src->data;
	SDL_RenderClear(data->windowRenderer);

	

	//draw background
	SDL_Surface* surf = SDL_LoadBMP("./game_background.bmp");
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
	
	//send to drawgame in utils - draw the board 
	drawGameBoard(data, src->game);
	
	//Draw widgets
	for (int i = 0; i < data->numOfWidgets; i++)
	{
		if (data->widgets[i]->isVisible)
			data->widgets[i]->drawWidget(data->widgets[i]);
		if ((data->widgets[i]->isVisible) && (data->widgets[i]->widget_type == CHESS_UNDO_BUTTON)
			&& (data->widgets[i]->isActivateLegal))
			updateButtonTexture(data->widgets[3], "./undo_active.bmp"); //index 3 is undo button in the array 
	}

	
	

	SDL_RenderPresent(data->windowRenderer);
}

int time = 0;

WINDOW_EVENT handleEventGameWindow(ChessWindow* src, SDL_Event* event) 
{
	if (src == NULL || event == NULL) 
	{
		return CHESS_EMPTY_WINDOWEVENT;
	}
	int newX, newY;
	int mouseX, mouseY;
	Button* buttonCast;
	chessGameWindow* windata = (chessGameWindow*)src->data;
	WINDOW_EVENT eventType = CHESS_EMPTY_WINDOWEVENT;
	
	SDL_Rect loc = { .x = event->button.x,.y = event->button.y,.h = 72,.w = 180 };
	while (1)
	{
		while (SDL_PollEvent(event))
		{
			for (int i = 0; i < windata->numOfWidgets; i++) 
			{
				windata->widgets[i]->handleEvent(windata->widgets[i], event);
				SDL_RenderPresent(windata->windowRenderer);
				if (windata->widgets[i]->isActive && windata->widgets[i]->isActivateLegal)
				{
					buttonCast = (Button*)(windata->widgets[i]->data);
					switch (windata->widgets[i]->widget_type)
					{
					case CHESS_EMPTY_BUTTON:
						return CHESS_EMPTY_WINDOWEVENT;
					case CHESS_RESTART_BUTTON: // think about it 
						return CHESS_STARTGAME_WINDOWEVENT;
					case CHESS_SAVE_BUTTON:
						return CHESS_SAVE_WINDOWEVENT;
					case CHESS_LOAD_BUTTON:
						return CHESS_LOAD_SCREEN_WINDOWEVENT;
					case CHESS_UNDO_BUTTON:
						//taking care here? or in main? i think here 
						break;
					case CHESS_HOME_BUTTON:
						return CHESS_HOME_WINDOWEVENT;
					case CHESS_QUIT_BUTTON:
						return CHESS_QUIT_WINDOWEVENT;
					
					case CHESS_PAWN_BLACK_BUTTON:
					case CHESS_PAWN_WHITE_BUTTON:
					case CHESS_BISHOP_BLACK_BUTTON:
					case CHESS_BISHOP_WHITE_BUTTON:
					case CHESS_KNIGHT_BLACK_BUTTON:
					case CHESS_KNIGHT_WHITE_BUTTON:
					case CHESS_ROOK_BLACK_BUTTON:
					case CHESS_ROOK_WHITE_BUTTON:
					case CHESS_QUEEN_BLACK_BUTTON:
					case CHESS_QUEEN_WHITE_BUTTON:
					case CHESS_KING_WHITE_BUTTON:
					case CHESS_KING_BLACK_BUTTON:
						/////bonus - start writing 
						/*SDL_SetRenderDrawColor(windata->windowRenderer, 100,10, 150, 255);
						if (SDL_RenderFillRect(windata->windowRenderer, &src->game->gameGUIBoard[4][5]) < 0)
							printf("ERROR: unable to fill rect: %s\n", SDL_GetError());
						SDL_RenderPresent(windata->windowRenderer);*/

						/////////just in case - 
							////SDL_GetMouseState
							//SDL_SetRenderDrawColor(windata->windowRenderer, 255, 255, 255, 255);
							//SDL_RenderDrawRect(windata->windowRenderer, &loc);
						//	updateButtonLocation(windata->widgets[i], event->motion.x, event->motion.y);
							//i = i - 1;
							//SDL_SetRenderDrawColor(windata->windowRenderer, 255, 0, 255, 255);
							//SDL_RenderDrawRect(windata->windowRenderer, &loc);
							//SDL_Delay(16);
							//if (time > 100)
						   //{
							//	time = 0;
							//	SDL_RenderPresent(windata->windowRenderer);
//
							//}
						//}
						if (windata->widgets[i]->endOfDrag)
						{
							windata->widgets[3]->isActivateLegal = true;

							SDL_GetMouseState(&mouseX, &mouseY);
							//check valid move + update location - origin or event 
							if (isValidPlace(mouseX, mouseY, src->game))
							{
								setButtonPlace(&newX, &newY, src->game, event->button.x, event->button.y, windata->widgets[i]);
								updateButtonLocation(windata->widgets[i], newX, newY);
							}
							else
								updateButtonLocation(windata->widgets[i]
								  , src->game->gameGUIBoard[windata->widgets[i]->row][windata->widgets[i]->coll].x
								  , src->game->gameGUIBoard[windata->widgets[i]->row][windata->widgets[i]->coll].y);
							windata->widgets[i]->endOfDrag = false;
							windata->widgets[i]->isActive = false;
						}
					
					//	time++;
						break;

					default:
						eventType = CHESS_EMPTY_WINDOWEVENT;
						break;
					}
				
					drawGameWindow(src);

				
				}
			}
			break;
		}
	}
	return eventType;
}


