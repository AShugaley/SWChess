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

#include <stdbool.h>
//#include "Chess_ArrayList.h"


chessGame* createChessGame(int historySize, GAME_MODE_PLAYER mode, int difficulty); //D

chessGame* copyChessGame(chessGame* src); //D Not Tested

void destroyChessGame(chessGame* src); // D Not Tested

CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D Not Tested

bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D

CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src); //NT

bool hasValidMove(chessGame* src, int row, int col); // D kinda tested

CHESS_GAME_MESSAGE chessConsolePrintBoard(chessGame* src); // D tested

bool isCheck(chessGame* src); // D tested

movesArray* allPossibleMoves(chessGame* src, int row, int col); //D Not Tested

bool isCheckmate(chessGame* src); // D Not Tested

bool isStalemate(chessGame* src); // D Not Tested

bool saveGame(chessGame* src, const char* filename);

void get_moves(chessGame* src, int row, int col);

char* getCurrentPlayerStringName(chessGame* src);

#endif /* Chess_gameUtils_h */
