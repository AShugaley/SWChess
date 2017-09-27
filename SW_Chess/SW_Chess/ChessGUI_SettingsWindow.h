#ifndef CHESSGUI_SETTINGSWINDOW_H_
#define CHESSGUI_SETTINGSWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>

/**
 * ChessGUI_SettingsWindow.h summary:
 *
 * A container that inculdes all the functions needed in order to create and manage the settings
 * game screen (i.e. the screen where a player changes the setup of the next game).
 *
 * createSettingsWindow       - Create a new settingsWindow structure.
 * destroySettingsWindow      - Destroies the window element
 * drawSettingsWindow         - Draws the visual elements of the window
 * handleEventSettingsWindow  - Handles user events.
 **/

/* enum represting the different settings */
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


/**
 * Creats a new SDL window, for the settings screen.
 * @param game - the current chess game
 *
 * returns a window
 */
ChessWindow* createSettingsWindow(Uint32 winMode, chessGame* game);

/**
 * Destroies a settingsgame window, incl all the mem allocations.
 *
 * returns nothing
 */
void destroySettingsWindow(ChessWindow* src);

/**
 * Destroies a settingsgame window, incl all the mem allocations.
 *
 * returns nothing
 */
void drawSettingsWindow(ChessWindow* src);

/**
 * Destroies a settingsgame window, incl all the mem allocations.
 *
 * returns nothing
 */
WINDOW_EVENT handleEventSettingsWindow(ChessWindow* src, SDL_Event* event);


#endif



