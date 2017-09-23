
#ifndef CHESSGUI_WINDOW_H_
#define CHESSGUI_WINDOW_H_
#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include "Chess_def.h"


typedef enum {
	CHESS_EMPTY_WINDOWEVENT,
	CHESS_ERROR_WINDOWEVENT,
	CHESS_STARTGAME_WINDOWEVENT,
	CHESS_RESTART_WINDOWEVENT,
	CHESS_SETTINGS_WINDOWEVENT,
	CHESS_LOAD_WINDOWEVENT,
	CHESS_LOAD_SCREEN_WINDOWEVENT,
	CHESS_BACK_WINDOWEVENT,
	CHESS_HOME_WINDOWEVENT,
	CHESS_QUIT_WINDOWEVENT,
	CHESS_SAVE_WINDOWEVENT,
	CHESS_SAVE_HOME_WINDOWEVENT,
} WINDOW_EVENT;


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
	//void (*handleEventWindow)(ChessWindow*, SDL_Event*);
	WINDOW_EVENT (*handleEventWindow)(ChessWindow* , SDL_Event*);
	void (*destroyWindow)(ChessWindow* );
	WINDOW_TYPE type;
	chessGame* game;
};

//NULL safe FUNCTION
void destroyWindow(ChessWindow* src);


#endif