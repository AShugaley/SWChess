#ifndef CHESSGUI_GAMEWINDOW_H_
#define CHESSGUI_GAMEWINDOW_H_
#include "ChessGUI_Window.h"
#include "Widget.h"
#include <stdio.h>

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

ChessWindow* createGameWindow(Uint32 winMode, chessGame* game);
void destroyGameWindow(ChessWindow* src);
void drawGameWindow(ChessWindow* src);
WINDOW_EVENT handleEventGameWindow(ChessWindow* src, SDL_Event* event);

#endif



