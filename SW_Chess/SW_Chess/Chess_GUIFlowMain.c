#include "Chess_GuiFlowMain.h"
#include "Chess_gameUtils.h"
#include "ChessGUI_FlowOnePlayer.h"
#include "ChessGUI_FlowTwoPlayers.h"


int GUIMain() 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	//this game pointer will be updated along the game, here and in the game&settings windows 
	chessGame* game = createChessGame(6, ONE_PLAYER, WHITES, 2); //default args
	if (game == NULL)
		destroyChessGame(game);

	ChessWindow* currentWindow = createWindow(CHESS_MAIN_WINDOW, SDL_WINDOW_OPENGL, game);
	if (currentWindow == NULL)
	{
        printf("ERROR: unable to create window: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}
	
	currentWindow->game = game;

	currentWindow->drawWindow(currentWindow);
	WINDOW_TYPE prev = CHESS_MAIN_WINDOW; //default, just for error cases

	SDL_Event event;
	WINDOW_EVENT windowEvent;
	while (1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			break;

		windowEvent = currentWindow->handleEventWindow(currentWindow, &event);
		
		switch (windowEvent)
		{

		case CHESS_EMPTY_WINDOWEVENT:
			break;
		
		case CHESS_ERROR_WINDOWEVENT:
			//quit ? somthing else? look for it in the PDF !!!!!!!!!!!!!!!!!!!!!!!!!
			break;

		case CHESS_STARTGAME_WINDOWEVENT: 
			currentWindow = swapWindows(currentWindow, CHESS_GAME_WINDOW, game);
			break;

		case CHESS_RESTART_WINDOWEVENT:
			initChessBoard(game);
			spArrayListDestroy(game->historyArray);
			game->historyArray = spArrayListCreate(6);
			game->currentPlayer = WHITES;
			currentWindow = swapWindows(currentWindow, CHESS_GAME_WINDOW, game);
			break;
		
		case CHESS_HOME_WINDOWEVENT:
			destroyChessGame(game);
			game = createChessGame(6, ONE_PLAYER, WHITES, 2);
			currentWindow = swapWindows(currentWindow, CHESS_MAIN_WINDOW, game);
			break;
		
		case CHESS_SETTINGS_WINDOWEVENT:
			currentWindow = swapWindows(currentWindow, CHESS_SETTINGS_WINDOW, game);
			prev = CHESS_MAIN_WINDOW;
			break;
		
		case CHESS_LOAD_WINDOWEVENT:
			currentWindow = swapWindows(currentWindow, CHESS_GAME_WINDOW, game);
			break;

		case CHESS_LOAD_SCREEN_WINDOWEVENT:
			prev = currentWindow->type;
			currentWindow = swapWindows(currentWindow, CHESS_LOAD_WINDOW, game);
			break;
		
		case CHESS_BACK_WINDOWEVENT:
			currentWindow = swapWindows(currentWindow, prev, game);
			break;
		
		case CHESS_QUIT_WINDOWEVENT:
			destroyWindow(currentWindow);
			SDL_Quit();
			return 0;
		}
	}

	destroyChessGame(game);
	destroyWindow(currentWindow);
	SDL_Quit();
	return 0;
}




