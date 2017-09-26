#ifndef CHESSGUI_UTILS_H_
#define CHESSGUI_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "ChessGUI_Window.h"
#include "Chess_GUIFlowMain.h"
#include "Chess_def.h"
#include "Chess_gameUtils.h"

//mine


#define STALEMATE  0
#define CHECK      1
#define CHECKMATE  2



/*
update the visibility and location of the GUI pieces, according to the gameBoard (the
chars array)
*/
void setBoardPieces(ChessWindow* src, chessGameWindow* data);
bool GUIMove(ChessWindow* src, Widget* currentwidget, SDL_Event* event, chessGameWindow* data);
ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type, chessGame* game);
//ChessWindow* copyWindow(ChessWindow* src);
ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode, chessGame* game);
void initGameGUIBoard(chessGame* game);
void drawGameBoard(chessGameWindow* win, chessGame* game);
bool updateConsoleBoardIfValid(int x, int y, chessGame* game, Widget* currentWidget);
void widgetUpdates(Widget* src, int x, int y, int row, int coll);
void setButtonPlace(int* newX, int* newY, chessGame* game, int locX, int locY, Widget* src);
//void GUICompMove(ChessWindow* src, chessGameWindow* data);
int checkGuiGameEnd(ChessWindow* src);
void undoGui(chessGame* src);



#endif