#ifndef CHESSGUI_UTILS_H_
#define CHESSGUI_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "ChessGUI_Window.h"
#include "Chess_GUIFlowMain.h"
#include "Chess_def.h"

ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type, chessGame* game);
//ChessWindow* copyWindow(ChessWindow* src);
ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode, chessGame* game);
void initGameGUIBoard(chessGame* game);
void drawGameBoard(chessGameWindow* win, chessGame* game);
bool isValidPlace(int x, int y, chessGame* game);
void setButtonPlace(int* newX, int* newY, chessGame* game, int locX, int locY, Widget* src);



#endif