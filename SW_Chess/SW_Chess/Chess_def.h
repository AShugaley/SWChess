#ifndef CHESS_DEF_H
#define CHESS_DEF_H


#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>

#define BOARD_SIZE 8

typedef enum ui_mode {
    CONSOLE,
    GUI,
} UI_MODE;


typedef enum game_mode {
    ONE_PLAYER,
    TWO_PLAYERS,
} GAME_MODE_PLAYER;

typedef enum game_status {
    GAME_OVER_P1_WINS,
    GAME_OVER_P2_WINS,
    GAME_OVER_TIE,
    GAME_CHECK,
    GAME_CHECKMATE,
    GAME_RESTART,
    EMPTY,
} GAME_STATUS;


typedef enum color {
    WHITES,
    BLACKS,
} PLAYER_COLOR;

typedef enum chessGameMessage{
    CHESS_GAME_INVALID_MOVE,
    CHESS_GAME_INVALID_ARGUMENT,
    CHESS_GAME_INVALID_POSITION,
    CHESS_GAME_NO_HISTORY,
    CHESS_GAME_SUCCESS,
} CHESS_GAME_MESSAGE;


typedef struct sp_array_list_node {
    int current_pos_row;
    int current_pos_col;
    int prev_pos_row;
    int prev_pos_col;
    char prev_pos_fig;
} SPArrayListNode;


typedef struct sp_array_list_t {
    SPArrayListNode* elements;
    int actualSize;
    int maxSize;
} SPArrayList;


typedef struct chess_game {
    char gameBoard[BOARD_SIZE][BOARD_SIZE];
	SDL_Rect gameGUIBoard[BOARD_SIZE][BOARD_SIZE]; 
    GAME_MODE_PLAYER gameMode;
    int difficulty;
    PLAYER_COLOR currentPlayer;
    PLAYER_COLOR humanPlayerColor;
    SPArrayList *historyArray;
    int MovesCounter;
    UI_MODE uiMode;
} chessGame;

typedef struct moves_array {
    int moves[64][4];
    
} movesArray;


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
