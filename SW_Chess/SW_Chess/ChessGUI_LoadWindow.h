#ifndef CHESSGUI_LOADWINDOW_H_
#define CHESSGUI_LOADWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>
#include "Chess_gameUtils.h"

/**
 * ChessGUI_LoadWindow.h summary:
 *
 * A container that inculdes all the functions needed in order to create and manage the load
 * game screen (i.e. the screen where a player may chose a previously saved game).
 *
 * createLoadWindow       - Create a new loadWindow structure.
 * destroyLoadWindow      - Destroies the window element
 * drawLoadWindow         - Draws the visual elements of the window
 * handleEventLoadWindow  - Handles user events.
 **/

typedef struct chess_LoadWindow chessLoadWindow;
struct chess_LoadWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	Widget** widgets;
	int numOfWidgets;
};

/**
 * Creats a new SDL window, for the load screen.
 * @param game - the current chess game
 * 
 * returns a window
 */
ChessWindow* createLoadWindow(Uint32 winMode, chessGame* game);

/**
 * Destroies a loadgame window, incl all the mem allocations.
 *
 * returns nothing
 */
void destroyLoadWindow(ChessWindow* src);

/**
 * Draws the visual elements, including the buttons and widgets on a loadgame window.
 *
 * returns nothing
 */
void drawLoadWindow(ChessWindow* src);

/**
 * Handeles user events on the loadWindow
 *
 * returns enum - event type
 */
WINDOW_EVENT handleEventLoadWindow(ChessWindow* src, SDL_Event* event);
#endif
