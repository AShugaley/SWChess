//
//  Chess_gameUtilsAux.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_gameUtilsAux_h
#define Chess_gameUtilsAux_h
#include <stdbool.h>
#include <stdlib.h>
#include "Chess_def.h"
#include "Chess_ArrayList.h"


/**
 * Sets the board of the given chess game to the default starting position
 * (as specified in chess rules).
 *
 * @param src   - the source game.
 * returnes nothing
 */
void initChessBoard(chessGame* src);

/**
 * checks if a given board position is a valid destenation for a player to set his figure in.
 * i.e. - either an empty field or an opponent position
 * 
 * @param player - the playet for whom we are checking (WHITES/BLACKES
 * @param figure - the position on the board we are checking (can be either a figure or an empty field).
 * @return true if valid destenetion, false otherwise
 */
bool isValidDestenetion(PLAYER_COLOR player, char figure);


/**
 * checks if a given board position is an opponent figure
 *
 * @param player - the playet for whom we are checking (WHITES/BLACKES
 * @param figure - the position on the board we are checking (can be either a figure or an empty field).
 * @return true if figure is an opponent figure, false otherwise
 */
bool isOpponentPosition(PLAYER_COLOR player, char figure);

/**
 * checks if a set of 4 ints (two pairs) represent two valid positions on board
 * in other words, all 4 ints should be >=0 and <8
 *
 * @return true if yes, false otherwise
 */
bool isValidBoardPosition(int prev_pos_row, int prev_pos_col, int  next_pos_row, int next_pos_col);

/**
 * checks if the move <x,y> -> <w,v> is a valid PAWN move.
 *
 * params - 4 ints that represent the pevious position <x,y> and the next position <w,v)
 * @return true if yes, false otherwise
 */
bool isValidPawnMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

/**
 * checks if the move <x,y> -> <w,v> is a valid BISHOP move.
 *
 * params - 4 ints that represent the pevious position <x,y> and the next position <w,v)
 * @return true if yes, false otherwise
 */
bool isValidBishopMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

/**
 * checks if the move <x,y> -> <w,v> is a valid ROOK move.
 *
 * params - 4 ints that represent the pevious position <x,y> and the next position <w,v)
 * @return true if yes, false otherwise
 */
bool isValidRookMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

/**
 * checks if the move <x,y> -> <w,v> is a valid KNIGHT move.
 *
 * params - 4 ints that represent the pevious position <x,y> and the next position <w,v)
 * @return true if yes, false otherwise
 */
bool isValidKnightMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

/**
 * checks if the move <x,y> -> <w,v> is a valid QUEEN move.
 *
 * params - 4 ints that represent the pevious position <x,y> and the next position <w,v)
 * @return true if yes, false otherwise
 */
bool isValidQueenMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

/**
 * checks if the move <x,y> -> <w,v> is a valid KING move.
 *
 * params - 4 ints that represent the pevious position <x,y> and the next position <w,v)
 * @return true if yes, false otherwise
 */
bool isValidKingMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

/**
 * checks if a certain char represents a black figure (as defined by the guidelines)
 *
 * @param figure - a char that represents a position on board
 * @return true if figure represents a black figure, false otherwise
 */
bool isBlackFigure(char figure);

/**
 * checks if a certain char represents a white figure (as defined by the guidelines)
 *
 * @param figure - a char that represents a position on board
 * @return true if figure represents a white figure, false otherwise
 */
bool isWhiteFigure(char figure);

/**
 * switches the current player (white -> balack) or (black -> white)
 *
 * @param src - a chess game
 * returns nothing
 */
void switchCurrentPlayer(chessGame* src);

/**
 * checks in figure located at <row,col> is threatened by any other opponent figure
 *
 * @param src - a chess game
 * @param row - x
 @ @param col - y
 * returns true if the figure is threatened, false otherwise
 */
bool isUnderPressure(chessGame* src, int row, int col);

/**
 * Returnes the char representation for column number
 * e.g. 0->A, 3->D etc
 */
char getColumnChar(int col);

/**
 * Returnes the int representation for column number
 * e.g. A->0, D->3 etc
 */
char getIntFromColumnChar(char col);

#endif /* Chess_gameUtilsAux_h */
