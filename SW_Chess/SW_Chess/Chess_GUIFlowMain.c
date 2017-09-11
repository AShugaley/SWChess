#include "Chess_GuiFlowMain.h"


int GUIMain() 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	ChessWindow* currentWindow = createWindow(CHESS_MAIN_WINDOW, SDL_WINDOW_OPENGL);


	if (currentWindow == NULL)
	{
		SDL_Quit();
		return 0;
	}

	currentWindow->drawWindow(currentWindow);

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
		
		case CHESS_STARTGAME_WINDOWEVENT:
		{

		}
		case CHESS_RESTART_WINDOWEVENT:
		{
			////create game window 
			/*destroyWindow(mainWindow);
			mainWindow = NULL;

			gameWindow = createGameWindow();
			if (gameWindow == NULL)
			{
			SDL_Quit();
			return 0;
			}
			gameWindow->drawWindow(gameWindow);*/

			//want to save the previous settings
			int prevdiff = currentWindow->game->difficulty;
			GAME_MODE_PLAYER prevmode = currentWindow->game->gameMode;
			PLAYER_COLOR prevcolor = currentWindow->game->humanPlayerColor;
			
			currentWindow = swapWindows(currentWindow, CHESS_GAME_WINDOW);

			currentWindow->game->difficulty = prevdiff;
			currentWindow->game->gameMode = prevmode;
			currentWindow->game->humanPlayerColor = prevcolor;

		//	currentWindow->game = createChessGame(6, ONE_PLAYER, WHITES, 2); //default args
			break;

		}
		case CHESS_HOME_WINDOWEVENT:
		{
			currentWindow = swapWindows(currentWindow, CHESS_MAIN_WINDOW);
			currentWindow->prevWindow = NULL;
			break;
		}
		case CHESS_SETTINGS_WINDOWEVENT:
		{
			currentWindow = swapWindows(currentWindow, CHESS_SETTINGS_WINDOW);
		//need to work on it
			//currentWindow->prevWindow = createWindow(CHESS_MAIN_WINDOW, SDL_WINDOW_HIDDEN);
			break;
		}
		case CHESS_LOAD_WINDOWEVENT:
		{
			ChessWindow* prev = copyWindow(currentWindow);
			currentWindow = swapWindows(currentWindow, CHESS_LOAD_WINDOW);
			currentWindow->prevWindow = prev;
			//currentWindow = NULL;
			break;

			//else if (loadWindow)
			//{
			//	//create the chosen game window 
			//}
			//else if (gameWindow)
			//{
			//	ChessWindow* prev = copyWindow(gameWindow);
			//	loadWindow = swapWindows(gameWindow, CHESS_LOAD_WINDOW);
			//	loadWindow->prevWindow = prev;
			//	gameWindow = NULL;
			//	break;
			//}
		}
		case CHESS_BACK_WINDOWEVENT:
		{
			//ChessWindow* prev = copyWindow(currentWindow);
			currentWindow = swapWindows(currentWindow, currentWindow->prevWindow->type);
			//currentWindow->prevWindow = prev;
			//currentWindow = NULL;
			break;
		}
		case CHESS_QUIT_WINDOWEVENT:
		{
			if (currentWindow->type == CHESS_MAIN_WINDOW)
			{
				destroyWindow(currentWindow);
			}
			else if (currentWindow->type == CHESS_GAME_WINDOW)
			{
				const SDL_MessageBoxButtonData buttons[] = {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,   0,    "yes" },/* .flags, .buttonid, .text */
					{ 0,										 1,     "no" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,   2, "cancel" },
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
					SDL_MESSAGEBOX_INFORMATION, /* .flags */
					NULL, /* .window */
					"Chess!", /* .title */
					"Do you want to save changes?", /* .message */
					SDL_arraysize(buttons), /* .numbuttons */
					buttons, /* .buttons */
					&colorScheme /* .colorScheme */
				};
				int buttonid;
				if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
					SDL_Log("error displaying message box");
					return 1;
				}
				else if (buttonid == 0) // yes
				{
					windowEvent = CHESS_SAVE_WINDOWEVENT;
					break;
				}
				else if (buttonid == 2) // cancel
					break;
			}

			SDL_Quit();
			return 0;
		}
		}
	}
	destroyWindow(currentWindow);
	SDL_Quit();
	return 0;
}


/*
window :
widgets = the pieces
the window acts as usual
when dropping a piece it will return the mouse location



GUI flow -
what I alrready wrote + update the game 


*/