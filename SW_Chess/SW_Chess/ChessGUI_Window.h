
#ifndef CHESSGUI_WINDOW_H_
#define CHESSGUI_WINDOW_H_

#include <SDL.h>
#include <SDL_video.h>

#include <stdbool.h>
#include "Chess_def.h"

/**
 * ChessGUI_Window.h summary:
 *
 * A container that inculdes various basic SDL functions and definitions used in the specific windowTypes .h files
 *
 **/


/* enum represting the different user event types */
typedef enum {
	CHESS_EMPTY_WINDOWEVENT,
	CHESS_STARTGAME_WINDOWEVENT,
	CHESS_RESTART_WINDOWEVENT,
	CHESS_SETTINGS_WINDOWEVENT,
	CHESS_LOAD_WINDOWEVENT,
	CHESS_LOAD_SCREEN_WINDOWEVENT,
	CHESS_BACK_WINDOWEVENT,
	CHESS_HOME_WINDOWEVENT,
	CHESS_QUIT_WINDOWEVENT,
	CHESS_SAVE_WINDOWEVENT,
	CHESS_DONT_SAVE_WINDOWEVENT,
	CHESS_CANCEL_WINDOWEVENT,
	CHESS_SAVE_HOME_WINDOWEVENT,
	CHESS_SAVE_QUIT_WINDOWEVENT,
} WINDOW_EVENT;

/* enum represting the different window types */
typedef enum {
	CHESS_MAIN_WINDOW,
	CHESS_GAME_WINDOW,
	CHESS_LOAD_WINDOW,
	CHESS_SETTINGS_WINDOW,
} WINDOW_TYPE;


typedef struct spwindow_t ChessWindow;
struct spwindow_t {
	void* data;
	void (*drawWindow)(ChessWindow* );
	WINDOW_EVENT (*handleEventWindow)(ChessWindow* , SDL_Event*);
	void (*destroyWindow)(ChessWindow* );
	WINDOW_TYPE type;
	chessGame* game;
};

/* destroies a SDL window */
void destroyWindow(ChessWindow* src);


#endif
