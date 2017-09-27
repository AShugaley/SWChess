#ifndef CHESSGUI_GAMEWINDOW_H_
#define CHESSGUI_GAMEWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>


/**
 * ChessGUI_GameWindow.h summary:
 *
 * A container that inculdes all the functions needed in order to create and manage the Game
 * game screen (i.e. the actual board screen, where the game is held).
 *
 * createMainWindow       - Create a new GameWindow structure.
 * destroyMainWindow      - Destroies the window element
 * drawMainWindow         - Draws the visual elements of the window
 * handleEventMainWindow  - Handles user events.
 **/



/* defining a figureIndex, in order to simplfy searching in arrays later on */
#define BISHOP_WHITE1 6
#define BISHOP_WHITE2 7

#define BISHOP_BLACK1  8
#define BISHOP_BLACK2  9

#define ROOK_WHITE1   10
#define ROOK_WHITE2  11

#define ROOK_BLACK1   12
#define ROOK_BLACK2  13

#define KNIGHT_WHITE1   14
#define KNIGHT_WHITE2   15

#define KNIGHT_BLACK1    16
#define KNIGHT_BLACK2    17

#define QUEEN_WHITE1 18
#define QUEEN_BLACK1 19

#define KING_WHITE1 20
#define KING_BLACK1 21


#define PAWN_WHITE1 22
#define PAWN_BLACK1 23

#define PAWN_WHITE2 24
#define PAWN_BLACK2 25

#define PAWN_WHITE3 26
#define PAWN_BLACK3 27

#define PAWN_WHITE4 28
#define PAWN_BLACK4 29

#define PAWN_WHITE5 30
#define PAWN_BLACK5 31

#define PAWN_WHITE6 32
#define PAWN_BLACK6 33

#define PAWN_WHITE7 34
#define PAWN_BLACK7 35

#define PAWN_WHITE8 36
#define PAWN_BLACK8 37


typedef struct chess_gameWindow chessGameWindow;
struct chess_gameWindow {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;
};

/**
 * Creats a new SDL window, for the game screen.
 * @param game - the current chess game
 *
 * returns a window
 */
ChessWindow* createGameWindow(Uint32 winMode, chessGame* game);

/**
 * Destroies a gameWindow window, incl all the mem allocations.
 *
 * returns nothing
 */
void destroyGameWindow(ChessWindow* src);

/**
 * Draws the visual elements, including the buttons and widgets on a gameWindow window.
 *
 * returns nothing
 */
void drawGameWindow(ChessWindow* src);

/**
 * Handeles user events on the gameWindow
 *
 * returns enum - event type
 */
WINDOW_EVENT handleEventGameWindow(ChessWindow* src, SDL_Event* event);

#endif



