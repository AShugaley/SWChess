//
//  Chess_def.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_def_h
#define Chess_def_h

#define BOARD_SIZE 8

typedef enum ui_mode {
    CONSOLE,
    GUI
} UI_MODE;


typedef enum game_mode {
    ONE_PLAYER_WHITES,
    ONE_PLAYER_BLACKS,
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
    int difficulty;
    CURRENT_PLAYER currentPlayer;
    //  SPArrayList *historyArray;
    int currentMove;
    UI_MODE uiMode;
} chessGame;

typedef struct moves_array {
    int moves[64][4];
    
} movesArray;




#include <stdio.h>
#include <stdbool.h>


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

#define EMPTY_BOARD_POS '_'

#endif /* Chess_def_h */
