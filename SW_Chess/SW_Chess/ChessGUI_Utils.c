#include "ChessGUI_Utils.h"
#include "ChessGUI_MainWindow.h"
#include "ChessGUI_GameWindow.h"
#include "ChessGUI_LoadWindow.h"
#include "ChessGUI_SettingsWindow.h"
#include "Button.h"
#include "Chess_FlowOnePlayer.h"

ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode, chessGame* game)
{
	ChessWindow* res = NULL;
	if (wintype == CHESS_LOAD_WINDOW)
		res = createLoadWindow(winMode, game);
	else if (wintype == CHESS_MAIN_WINDOW)
		res = createMainWindow(winMode, game);
	else if (wintype == CHESS_GAME_WINDOW)
		res = createGameWindow(winMode, game);
	else if (wintype == CHESS_SETTINGS_WINDOW)
		res = createSettingsWindow(winMode, game);
//	res->prevWindow = NULL;
	return res;
}


ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type, chessGame* game)
{
//	chessGame* newGame = copyChessGame(game);
	destroyWindow(oldWindow);
	ChessWindow* newWindow = NULL;
	newWindow = createWindow(type, SDL_WINDOW_OPENGL, game);
	//game = newGame; //update our main game pointer
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
//	int leftUpCornerX = 800;
//	int leftUpCornerY = 520;
	int leftDownCornerX = 380;
	int leftDownCornerY = 520;
	int width = 60;
	int height = 60;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			SDL_Rect currentRect = { .x = (j * width)  + leftDownCornerX
									,.y = -(i * height) + leftDownCornerY
									,.h = 60
									,.w = 60 };
			game->gameGUIBoard[i][j] = currentRect;
		}
	}
	
}


void drawGameBoard(chessGameWindow* win, chessGame* game)
{
	SDL_Surface* loadingSurface;
	SDL_Texture* squareTexture;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			
			if (SDL_RenderDrawRect(win->windowRenderer, &game->gameGUIBoard[i][j]) < 0)
				printf("ERROR: unable to draw rect: %s\n", SDL_GetError());
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
			{
				loadingSurface = SDL_LoadBMP("./white_sq.bmp"); //We use the surface as a temp var;
				squareTexture =  SDL_CreateTextureFromSurface(win->windowRenderer, loadingSurface);
				//SDL_SetRenderDrawColor(win->windowRenderer, 0, 255, 0, 255);
			}
			else
			{
				loadingSurface = SDL_LoadBMP("./black_sq.bmp"); //We use the surface as a temp var;
				squareTexture =  SDL_CreateTextureFromSurface(win->windowRenderer, loadingSurface);
			}
						
			if (loadingSurface == NULL || squareTexture == NULL)
			{
				SDL_FreeSurface(loadingSurface); 
				SDL_DestroyTexture(squareTexture);
			}
			else if (SDL_RenderCopy(win->windowRenderer, squareTexture, NULL, &game->gameGUIBoard[i][j]) != 0)
			{
				printf("ERROR: unable to draw the square texture: %s\n", SDL_GetError());
				return;
			}
		}
	}
}
	

bool updateConsoleBoardIfValid(int x, int y, chessGame* game, Widget* currentWidget)
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
				if (setChessMove(game, currentWidget->row, currentWidget->coll, i, j, true, true))
					return true;  
				return false;
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
				return;
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

void widgetUpdates(Widget* src, int x, int y, int row, int coll)
{
	src->isVisible = true;
	updateButtonLocation(src, x, y);
	src->row = row;
	src->coll = coll;
}

void setBoardPieces(ChessWindow* src, chessGameWindow* data)
{
	int kStart=-1, kEnd=-1, kInc=-1;

	for (int s = 6; s <= 37; s++)
		data->widgets[s]->isVisible = false;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (src->game->gameBoard[i][j])
			{
			case PAWN_WHITE:
				kStart = PAWN_WHITE1;
				kEnd   = PAWN_BLACK8-1;
				kInc   = 2;
				break;
			case PAWN_BLACK:
				kStart = PAWN_BLACK1;
				kEnd =   PAWN_BLACK8;
				kInc = 2;
				break;
			case BISHOP_WHITE:
				kStart = BISHOP_WHITE1;
				kEnd = BISHOP_WHITE2;
				kInc = 1;
				break;
			case BISHOP_BLACK:
				kStart = BISHOP_BLACK1;
				kEnd = BISHOP_BLACK2;
				kInc = 1;
				break;
			case ROOK_WHITE:
				kStart = ROOK_WHITE1;
				kEnd =   ROOK_WHITE2;
				kInc = 1;
				break;
			case ROOK_BLACK:
				kStart = ROOK_BLACK1;
				kEnd =   ROOK_BLACK2;
				kInc = 1;
				break;
			case KNIGHT_WHITE:
				kStart = KNIGHT_WHITE1;
				kEnd =   KNIGHT_WHITE2;
				kInc = 1;
				break;
			case KNIGHT_BLACK:
				kStart = KNIGHT_BLACK1;
				kEnd = KNIGHT_BLACK2;
				kInc = 1;
				break;
			case QUEEN_WHITE:
				kStart = QUEEN_WHITE1;
				kEnd = QUEEN_WHITE1;
				kInc = 1;
				break;
			case QUEEN_BLACK:
				kStart = QUEEN_BLACK1;
				kEnd = QUEEN_BLACK1;
				kInc = 1;
				break;
			case KING_WHITE:
				kStart = KING_WHITE1;
				kEnd = KING_WHITE1;
				kInc = 1;
				break;
			case KING_BLACK:
				kStart = KING_BLACK1;
				kEnd = KING_BLACK1;
				kInc = 1;
				break;
			case '_':
				kStart = -1;
				break;
			default:
				kStart = -1;
				break;
			}
			if (kStart == -1)
				continue;
			for (int k = kStart; k <= kEnd; k = k + kInc)
			{
				if (!data->widgets[k]->isVisible)
				{
					widgetUpdates(data->widgets[k],
						src->game->gameGUIBoard[i][j].x, src->game->gameGUIBoard[i][j].y,
						i, j);
					data->widgets[k]->isVisible = true;
					break;
				}
			}
		}
	}
}

bool GUIMove(ChessWindow* src, Widget* currentwidget, SDL_Event* event, chessGameWindow* data)
{
	int newX, newY;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	/*there was a GUI move. we get here- 
	doing the console move and also validate the move
	after that we update the gui screen to see the finished move*/
	//check valid move + update location - origin (if move is not valid) or event (mouse current location)
	
	if (updateConsoleBoardIfValid(mouseX, mouseY, src->game, currentwidget))
	{
		setButtonPlace(&newX, &newY, src->game, event->button.x, event->button.y, currentwidget);
		updateButtonLocation(currentwidget, newX, newY);
		//setBoardPieces(src, data);
		return true;
	}
	else
	{
		updateButtonLocation(currentwidget
			, src->game->gameGUIBoard[currentwidget->row][currentwidget->coll].x
			, src->game->gameGUIBoard[currentwidget->row][currentwidget->coll].y);
		return false;
	}
		

}

//void GUICompMove(ChessWindow* src, chessGameWindow* data)
//{
	//compMove(src->game);
//	//setBoardPieces(src, data);
//
//}


int checkGuiGameEnd(ChessWindow* src)
{
	char* message = "";
	char* buttonName = "";
	int res = -1;
	int buttonid;

	if (isStalemate(src->game))
	{
		message = "Stalemate! Game Is Over,\n Hope you had fun,\n Alex&Mor";
		buttonName = "exit";
		res = STALEMATE;
	}
	else if (isCheckmate(src->game))
	{
		message = "Checkmate! Game Is Over,\n Hope you had fun,\n Alex&Mor";
		buttonName = "exit";
		res = CHECKMATE;
	}
	else if (isCheck(src->game))
	{
		message = "Check! Press the button to continue";
		buttonName = "continue";
		res = CHECK;
	}

	if (res == -1)
		return res;

	/////////////////end of game message box////////////////// 
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,   0,    buttonName },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
		  /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{ 0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{ 0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL,
		"Chess!",
		message,
		SDL_arraysize(buttons),
		buttons,
		&colorScheme
	};

	
	if (res != -1) //game is over (or check)
	{
		if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		{
			printf("ERROR: error displaying message box: %s\n", SDL_GetError()); //quit ? 
			return -1;
		}
		else if (buttonid == 0) // exit/continue
		{
			return res;
		}
	}
	return res;
}


void undoGui(chessGame* src)
{
	SPArrayListNode* move = spArrayListGetLast(src->historyArray);
	spArrayListRemoveLast(src->historyArray);
	src->gameBoard[move->prev_pos_row][move->prev_pos_col] = move->moving_figure;
	src->gameBoard[move->current_pos_row][move->current_pos_col] = move->prev_pos_fig;
	switchCurrentPlayer(src);
}
