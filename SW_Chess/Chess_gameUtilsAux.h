//
//  Chess_gameUtilsAux.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_gameUtilsAux_h
#define Chess_gameUtilsAux_h
#include "Chess_gameUtils.h"
#include <stdio.h>

#define PAWN_WHITE 'm'
#define PAWN_BLACK 'M'

#define BISHOP_WHITE 'b'
#define BISHOP_BLACK 'B'

#define ROOK_WHITE 'r'
#define ROOK_BLACK 'R'

#define KNIGHT_WHITE 'n'
#define KNIGHT_BLACK 'N'

#define QUEEN_WHITE 'q'
#define QUEEN_BLACK 'Q'

#define KING_WHITE 'k'
#define KING_BLACK 'K'

#define EMPTY_BOARD_POS ' '


bool isValidDestenetion(CURRENT_PLAYER player, char figure);
bool isOpponentPosition(CURRENT_PLAYER player, char figure);
bool isValidBoardPosition(prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
bool isValidPawnMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);
bool isValidBishopMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);
bool isValidRookMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);
bool isValidKnightMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);
bool isValidQueenMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);
bool isValidKingMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);
bool isBlackFigure(char figure);
bool isWhiteFigure(char figure);
void switchCurrentPlayer(chessGame* src);
bool isUnderPressure(chessGame* src, int row, int col);



#endif /* Chess_gameUtilsAux_h */
