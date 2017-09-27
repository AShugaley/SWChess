#ifndef CHESSGUI_UTILS_H_
#define CHESSGUI_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "ChessGUI_Window.h"
#include "Chess_GUIFlowMain.h"
#include "Chess_def.h"
#include "Chess_gameUtils.h"


#define STALEMATE  0
#define CHECK      1
#define CHECKMATE  2


/*
 * Updates the visibility and location of the GUI pieces, according to the gameBoard (the
 * chars array)
 *
 * returns nothing
*/
void setBoardPieces(ChessWindow* src, chessGameWindow* data);

/*
 * Does a move in a GUI screen - calls the relevant function in gameUtils and then
 * updates the GUI board accordingly.
 *
 * returns nothing
 */
bool GUIMove(ChessWindow* src, Widget* currentwidget, SDL_Event* event, chessGameWindow* data);

/*
 * Does a move in a GUI screen - calls the relevant function in gameUtils and then
 * updates the GUI board accordingly.
 *
 * returns nothing
 */
ChessWindow* swapWindows(ChessWindow* oldWindow, WINDOW_TYPE type, chessGame* game);

/*
 * A function used to create the GUI windows 
 * @paramm WINDOW_TYPE - the window that we need
 *
 * returns the window
 */
ChessWindow* createWindow(WINDOW_TYPE wintype, Uint32 winMode, chessGame* game);

/*
 * Initilazies the GUIboard part of the chessGame* struct
 * updates src.
 */
void initGameGUIBoard(chessGame* game);

/*
 * Draws the GUI game board, accoring to the current position of the figures in 
 * the chessGame* struct
 *
 * updates the chessGameWindow*, returns nothing.
 */
void drawGameBoard(chessGameWindow* win, chessGame* game);

/*
 * Submits a user move and updates the chessGame* struct accordingly
 *
 * updates the chessGameWindow* & chessGame*  
 * returns false on failure to set this move (e.g. if it is not valid)
 */
bool updateConsoleBoardIfValid(int x, int y, chessGame* game, Widget* currentWidget);

/*
 * Updates a position of a figure on the board.
 *
 * Returns nothing
 */
void widgetUpdates(Widget* src, int x, int y, int row, int coll);

/*
 * Updates a position of a figure on the board.
 *
 * Returns nothing
 */
void setButtonPlace(int* newX, int* newY, chessGame* game, int locX, int locY, Widget* src);

/*
 * Checks for check/checkmate/tie, and acts accordingly:
 * either presents a message (check) or presents a message and terminates the game
 *
 * Returns an index of the outcome
 */
int checkGuiGameEnd(ChessWindow* src);

/*
 * Implements the undo command in GUI, using the relevant functions from chessUtils
 *
 * updates the board, returns nothing
 */
void undoGui(chessGame* src);



#endif
