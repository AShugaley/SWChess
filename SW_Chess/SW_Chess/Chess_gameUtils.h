//
//  Chess_gameUtils.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_gameUtils_h
#define Chess_gameUtils_h
#include <stdio.h>


#include "Chess_gameUtilsAux.h"
#include "Chess_ArrayList.h"

#include <stdbool.h>
//#include "Chess_ArrayList.h"

/**
 * Creates a new chess game with the following params: historySize, mode (1 or 2 players)
 * humanColor, difficulty. The last two are always defined by not used in 2 player mode.
 * CurrentPlayer defaults to WHITES. 
 * The also draws the initial board and sets it
 *
 * @return a chess game
 */
chessGame* createChessGame(int historySize, GAME_MODE_PLAYER mode, PLAYER_COLOR humanColor, int difficulty); //D

/**
 * Copies a chess game
 *
 * @return a chess game
 */
chessGame* copyChessGame(chessGame* src); //D Not Tested


/**
 * Frees the memory used by the chess game
 *
 * returns nothing
 */
void destroyChessGame(chessGame* src); // D Not Tested

/**
 * Sets move <x,y> -> <v,w>
 * Checks if it is a legal move, updates the board.
 *
 * @return message representing the result of the command (sucess, invalid move etc)
 */
CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D Not Tested

/**
 * Checks if move <x,y> -> <v,w> is legal (accoring to chess rules)
 *
 * @return true if yes, no otherwise
 */
bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D


/**
 * Undoes the previous move.
 *
 * @return message representing the result of the command (sucess, invalid move etc)
 */
CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src, bool shouldPrint); //NT

/**
 * Checks if the figure located at <x,y> has any legal moves
 *
 * @return true/false
 */
bool hasValidMove(chessGame* src, int row, int col); // D kinda tested

/**
 * Prints the board as specified in the guidelines
 *
 * @returns nothing
 */
CHESS_GAME_MESSAGE chessConsolePrintBoard(chessGame* src); // D tested

/**
 * Checks if there's a check. 
 * i.e. finds the king of the current player, and checks if it is threated by any opponent figure.
 *
 * @return true/false
 */
bool isCheck(chessGame* src); // D tested

/**
 * Findes all legal moves for figure located at <x,y>.
 *
 * @return a two demensional array representing all moved
 */
movesArray* allPossibleMoves(chessGame* src, int row, int col); //D Not Tested

/**
 * Checks if there's a checkmate.
 * i.e. finds the king of the current player, and checks if it is threated by any opponent figure and has no legal moves
 *
 * @return true/false
 */
bool isCheckmate(chessGame* src); // D Not Tested

/**
 * Checks for a tie situation in chess
 * i.e. finds all the figures of the current player, and verifies that they have no legal moves.
 * but the king it NOT is threated by any opponent figure
 *
 * @return true/false
 */
bool isStalemate(chessGame* src); // D Not Tested

/**
 * Saves the game to a file specified in the filename
 *
 * @return success/failure
 */
bool saveGame(chessGame* src, const char* filename);

/**
 * Prints all possible moves by figure at <x,y>, in the requested format.
 *
 * returns nothing
 */
void get_moves(chessGame* src, int row, int col);

/**
 * Returns a string with the name of the current player.
 *
 * @return "white" if WHITES and "black" otherwise
 */
char* getCurrentPlayerStringName(chessGame* src);

/**
 * Checks if there's a check/checkmate/tie. 
 * If yes, prints and/or terminates the game
 *
 * returns nothing
 */
void checkGameEnd(chessGame* src);

/**
 * terminates the game, freeing all memory resources.
 *
 * returns nothing
 */
void terminateGame(chessGame* src);



#endif /* Chess_gameUtils_h */
