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
#include "Chess_ArrayList.h"

#define BOARD_SIZE 8

typedef enum ui_mode {
    CONSOLE,
    GUI
} UI_MODE;

typedef enum game_mode {
    ONE_PLAYER_WHITES,
    ONE_PLAYER_BLACK,
    TWO_PLAYERS,
} GAME_MODE;

typedef enum current_player {
    WHITES,
    BLACKS,
} CURRENT_PLAYER;

typedef enum chessGameMessage{
    CHESS_GAME_INVALID_MOVE,
    CHESS_GAME_INVALID_ARGUMENT,
    CHESS_GAME_NO_HISTORY,
    CHESS_GAME_SUCCESS,
} CHESS_GAME_MESSAGE;

typedef struct chess_game {
    char gameBoard[BOARD_SIZE][BOARD_SIZE];
    GAME_MODE gameMode;
    CURRENT_PLAYER currentPlayer;
    SPArrayList *historyArray;
    int currentMove;
    UI_MODE uiMode;
} chessGame;




chessGame* createChessGame(int historySize, GAME_MODE mode); //D

chessGame* copyChessGame(chessGame* src); //D

void destroyChessGame(chessGame* src); // D

CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D

bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D

CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src); //NT

bool hasValidMove(chessGame* src, int row, int col); // D

CHESS_GAME_MESSAGE chessConsolePrintBoard(chessGame* src); // D

bool isCheck(chessGame* src); // D

bool isCheckmate(chessGame* src); // D

bool isStalemate(chessGame* src); // D




#endif /* Chess_gameUtils_h */
