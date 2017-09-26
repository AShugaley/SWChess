#ifndef CHESSGUI_SETTINGSWINDOW_H_
#define CHESSGUI_SETTINGSWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>


typedef enum {
	CHESS_EMPTYSET,
	CHESS_MODE_SET,
	CHESS_DIFFICULTY_SET,
	CHESS_COLOR_SET,
} SETTING_TYPE;

typedef struct chess_settingsWindow chessSettingsWindow;
struct chess_settingsWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Widget** Widgets;
	int numOfWidgets;
	SETTING_TYPE setType;
};

ChessWindow* createSettingsWindow(Uint32 winMode, chessGame* game);
void destroySettingsWindow(ChessWindow* src);
void drawSettingsWindow(ChessWindow* src);
WINDOW_EVENT handleEventSettingsWindow(ChessWindow* src, SDL_Event* event);


#endif



