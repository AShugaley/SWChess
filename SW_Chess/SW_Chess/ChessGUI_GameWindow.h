#ifndef CHESSGUI_GAMEWINDOW_H_
#define CHESSGUI_GAMEWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>


typedef struct chess_gameWindow chessGameWindow;
struct chess_gameWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;
};

ChessWindow* createGameWindow(Uint32 winMode);
void destroyGameWindow(ChessWindow* src);
void drawGameWindow(ChessWindow* src);
WINDOW_EVENT handleEventGameWindow(ChessWindow* src, SDL_Event* event);
#endif



