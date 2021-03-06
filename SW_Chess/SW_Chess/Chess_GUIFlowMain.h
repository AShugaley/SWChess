#ifndef CHESS_GUIFLOWMAIN_H_
#define CHESS_GUIFLOWMAIN_H_

#include <stdio.h>
#include "ChessGUI_MainWindow.h"
#include "ChessGUI_GameWindow.h"
#include "ChessGUI_LoadWindow.h"
#include "ChessGUI_SettingsWindow.h"
#include "ChessGUI_Utils.h"
#include <SDL.h>
#include <SDL_video.h>

/**
 * Initializes the GUI setup for the game - opens the main screen. 
 * 
 * returns nothing
 **/
int GUIMain();


#endif
