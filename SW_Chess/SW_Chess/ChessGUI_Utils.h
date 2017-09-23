#ifndef CHESSGUI_UTILS_H_
#define CHESSGUI_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "ChessGUI_Window.h"
#include "Chess_GUIFlowMain.h"
#include "Chess_def.h"
#include "Chess_gameUtils.h"

void setBoardPieces(ChessWindow* src, chessGameWindow* data);
void GUIMove(ChessWindow* src, Widget* currentwidget, SDL_Event* event);
ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type, chessGame* game);
//ChessWindow* copyWindow(ChessWindow* src);
ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode, chessGame* game);
void initGameGUIBoard(chessGame* game);
void drawGameBoard(chessGameWindow* win, chessGame* game);
bool updateConsoleBoardIfValid(int x, int y, chessGame* game, Widget* currentWidget);
void widgetUpdates(Widget* src, int x, int y, int row, int coll);
void setButtonPlace(int* newX, int* newY, chessGame* game, int locX, int locY, Widget* src);



#endif