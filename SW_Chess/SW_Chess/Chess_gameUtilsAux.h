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
 * Chess_gameUtilsAux summary:
 *
 * A container that includes a vrriety of various auxillary chess functions, that are used by the actual game
 * functions that appear at gameUtils.h. This is done both to break an otherwise long file into two, and to provide
 * better modularity to the game.
 *
 *
 *
 * initChessBoard          - Draws a standart Chess Board (i.e. according to classic rules)
 * isValidDestenetion      - Checks if a given filed can be filled by a gived player's figure.
 * isOpponentPosition      - Checks if a certain field is filled by an opponent figure.
 * isValidBoardPosition    - Checks if a touple ((x,y) -> (v,w)) represents two valid chess positions (i.e
 * all for ints are between 0 and 7.
 * isValidPawnMove         - Checks if a touple ((x,y) -> (v,w)) represents a valid pawn move
 * isValidBishopMove       - Checks if a touple ((x,y) -> (v,w)) represents a valid bishop move
 * isValidRookMove         - Checks if a touple ((x,y) -> (v,w)) represents a valid rook move
 * isValidKnightMove       - Checks if a touple ((x,y) -> (v,w)) represents a valid knight move
 * isValidQueenMove        - Checks if a touple ((x,y) -> (v,w)) represents a valid queen move
 * isValidKingMove         - Checks if a touple ((x,y) -> (v,w)) represents a valid king move
 * isWhiteFigure           - Checks if a given char represnts a white figure
 * isBlackFigure           - Checks if a given char represnts a black figure
 * switchCurrentPlayer     - Switches current player
 * isUnderPressure         - Checks if a given field is threatend by the opponent
 * getColumnChar           - Switches between int and char column represnatation
 * getIntFromColumnChar    - Switches between char and int column represnatation
 * checkAvoided            - Checks we do a move ((x,y) -> (v,w)), we do not create a check for the owner of <x,y> figure
 */




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



/**
 * Given a set of (x,y) -> (v,w)
 * 
 * Verifyes that we do not create a check (for the owner of <x,y> figure) if we submit the move.
 * Does not verify that the input is legal (i.e represents a valid position, two figures of opponents and so on)
 *
 * Returns true if check isn't created, false otherwise
 */
bool checkAvoided(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);


#endif /* Chess_gameUtilsAux_h */
