#ifndef CHESSGUI_MAINWINDOW_H_
#define CHESSGUI_MAINWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>
#include "Chess_gameUtils.h"


typedef struct chess_mainWindow chessMainWindow;
struct chess_mainWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;
};

ChessWindow* createMainWindow(Uint32 winMode);
void destroyMainWindow(ChessWindow* src);
void drawMainWindow(ChessWindow* src);
WINDOW_EVENT handleEventMainWindow(ChessWindow* src, SDL_Event* event);
#endif
