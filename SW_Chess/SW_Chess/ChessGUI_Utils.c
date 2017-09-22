#include "ChessGUI_Utils.h"
#include "ChessGUI_MainWindow.h"
#include "ChessGUI_GameWindow.h"
#include "ChessGUI_LoadWindow.h"
#include "ChessGUI_SettingsWindow.h"


ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode)
{
	ChessWindow* res = NULL;
	if (wintype == CHESS_LOAD_WINDOW)
		res = createLoadWindow(winMode);
	else if (wintype == CHESS_MAIN_WINDOW)
		res = createMainWindow(winMode);
	else if (wintype == CHESS_GAME_WINDOW)
		res = createGameWindow(winMode);
	else if (wintype == CHESS_SETTINGS_WINDOW)
		res = createSettingsWindow(winMode);
	res->prevWindow = NULL;
	return res;
}


ChessWindow* copyWindow(ChessWindow* src)
{
	ChessWindow* res = NULL;

	res = createWindow(src->type, SDL_WINDOW_HIDDEN);


	///////how to copy the above ????? 
	//res->data = src->data;//////////////////////////////////
	//res->destroyWindow = src->destroyWindow;
	//res->drawWindow = src->drawWindow;
	//res->handleEventWindow = src->handleEventWindow;
	//res->type = src->type;

	return res;
}




ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type)
{
	destroyWindow(oldWindow);
	ChessWindow* newWindow = NULL;
	newWindow = createWindow(type, SDL_WINDOW_OPENGL);
	
	if (newWindow == NULL)
	{
		SDL_Quit();
		return NULL;
	}
	newWindow->drawWindow(newWindow);
	return newWindow;
}

void initGameGUIBoard(chessGame* game)
{
	int leftUpCornerX = 300;
	int leftUpCornerY = 90;
	int width = 60;
	int height = 60;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			SDL_Rect currentRect = { .x = (j * width)  + leftUpCornerX
									,.y = (i * height) + leftUpCornerY
									,.h = 60
									,.w = 60 };
			game->gameGUIBoard[i][j] = currentRect;
		}
	}
	
}

void drawGameBoard(chessGameWindow* win, chessGame* game)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			
			if (SDL_RenderDrawRect(win->windowRenderer, &game->gameGUIBoard[i][j]) < 0)
				printf("ERROR: unable to draw rect: %s\n", SDL_GetError());
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
				SDL_SetRenderDrawColor(win->windowRenderer, 0, 255, 0, 255);
			else
				SDL_SetRenderDrawColor(win->windowRenderer, 0, 0, 255, 255);
			if (SDL_RenderFillRect(win->windowRenderer, &game->gameGUIBoard[i][j]) < 0)
				printf("ERROR: unable to fill rect: %s\n", SDL_GetError());
			
		}
	}
}
	

bool isValidPlace(int x, int y, chessGame* game)
{
	SDL_Point point;
	point.x = x;
	point.y = y;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (SDL_PointInRect(&point, &(game->gameGUIBoard[i][j])))
			{

				return true; ///for now 
				//if valid -true
				//else- false //invalid rect
			}
		}
	}
	return false;  //not in the board 
}

void setButtonPlace(int* newX, int* newY, chessGame* game, int locX, int locY, Widget* src)
{
	SDL_Point point;
	point.x = locX;
	point.y = locY;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (SDL_PointInRect(&point, &(game->gameGUIBoard[i][j])))
			{
				*newX = game->gameGUIBoard[i][j].x;
				*newY = game->gameGUIBoard[i][j].y;
				src->row = i;
				src->coll = j;
			}
		}
	}
}
	/*
rect origin = button location;
drag&drop - mouse_motion => piece.i += event.motion.xrel , j+=y.rel (update button location)
mouse_up-> 
for(i)
for (j)
if pointinrect(button->location, src[i][j])
	button location.x = scr[i].x
	.y =.y 
else
	button location = origin 
}*/
