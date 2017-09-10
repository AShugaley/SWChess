#ifndef CHESSGUI_UTILS_H_
#define CHESSGUI_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "ChessGUI_Window.h"
#include "Chess_GUIFlowMain.h"
#include "Chess_def.h"

ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type);
ChessWindow* copyWindow(ChessWindow* src);
ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode);
void drawGameBoard(chessGameWindow* win, chessGame* game);



#endif