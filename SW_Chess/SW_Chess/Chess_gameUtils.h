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




chessGame* createChessGame(int historySize, GAME_MODE mode);

chessGame* copyChessGame(chessGame* src);

void destroyChessGame(chessGame* src);

CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);

CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src);

bool hasValidMove(chessGame* src, int row, int col);

void chessConsolePrintBoard(chessGame* src);

bool isCheck(chessGame* src);

bool isCheckmate(chessGame* src);


bool isStalemate(chessGame* src);




#endif /* Chess_gameUtils_h */
