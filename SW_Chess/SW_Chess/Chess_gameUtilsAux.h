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

void initChessBoard(chessGame* src);
bool isValidDestenetion(CURRENT_PLAYER player, char figure);
bool isOpponentPosition(CURRENT_PLAYER player, char figure);
bool isValidBoardPosition(int prev_pos_row, int prev_pos_col,int  next_pos_row, int next_pos_col);
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
char getColumnChar(int col);


#endif /* Chess_gameUtilsAux_h */
