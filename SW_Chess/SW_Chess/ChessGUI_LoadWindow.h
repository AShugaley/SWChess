#ifndef CHESSGUI_LOADWINDOW_H_
#define CHESSGUI_LOADWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>
#include "Chess_gameUtils.h"


typedef struct chess_LoadWindow chessLoadWindow;
struct chess_LoadWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Widget** widgets;
	int numOfWidgets;
	//add activeSlot - the chosen slot (for the buttons textures) 
	//add legal slots - array of the slots to present (? )
};

ChessWindow* createLoadWindow(Uint32 winMode, chessGame* game);
void destroyLoadWindow(ChessWindow* src);
void drawLoadWindow(ChessWindow* src);
WINDOW_EVENT handleEventLoadWindow(ChessWindow* src, SDL_Event* event);
#endif
