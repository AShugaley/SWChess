#ifndef CHESSGUI_MAINWINDOW_H_
#define CHESSGUI_MAINWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>
#include "Chess_gameUtils.h"


/**
 * ChessGUI_MaindWindow.h summary:
 *
 * A container that inculdes all the functions needed in order to create and manage the main
 * game screen (i.e. the initial screen a player sees when opening the game).
 *
 * createMainWindow       - Create a new MainWindow structure.
 * destroyMainWindow      - Destroies the window element
 * drawMainWindow         - Draws the visual elements of the window
 * handleEventMainWindow  - Handles user events.
 **/


typedef struct chess_mainWindow chessMainWindow;
struct chess_mainWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;
};


/**
 * Creats a new SDL window, for the main screen.
 * @param game - the current chess game
 *
 * returns a window
 */
ChessWindow* createMainWindow(Uint32 winMode, chessGame* game);

/**
 * Destroies a mainWindow window, incl all the mem allocations.
 *
 * returns nothing
 */
void destroyMainWindow(ChessWindow* src);

/**
 * Draws the visual elements, including the buttons and widgets on a mainWindow window.
 *
 * returns nothing
 */
void drawMainWindow(ChessWindow* src);

/**
 * Handeles user events on the mainWindow
 *
 * returns enum - event type
 */
WINDOW_EVENT handleEventMainWindow(ChessWindow* src, SDL_Event* event);
#endif
