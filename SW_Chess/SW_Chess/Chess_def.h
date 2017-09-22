#ifndef CHESS_DEF_H
#define CHESS_DEF_H


#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>

#define BOARD_SIZE 8

/**
 * Chess_def summary:
 *
 * A container that includes many different structures, enums and constants that are used by different
 * parts of the chess game. No functions are included here, this way, this file can be included in most 
 * other headers, and provides a simple system to hold different declarations.
 */



/**
 * A type used to distinguish console and GUI mode
 */
typedef enum ui_mode {
    CONSOLE,
    GUI,
} UI_MODE;


/**
 * A type used to distinguish game modes
 */
typedef enum game_mode {
    ONE_PLAYER,
    TWO_PLAYERS,
} GAME_MODE_PLAYER;

/**
 * A type used to game status (is it over and how)
 */
typedef enum game_status {
    GAME_OVER_P1_WINS,
    GAME_OVER_P2_WINS,
    GAME_OVER_TIE,
    GAME_CHECK,
    GAME_CHECKMATE,
    GAME_RESTART,
    EMPTY,
} GAME_STATUS;


/**
 * A type that represents the two colors of chess
 */
typedef enum color {
    WHITES,
    BLACKS,
} PLAYER_COLOR;

/**
 * A type that represents the possible outcomes when making a chess move
 */
typedef enum chessGameMessage{
    CHESS_GAME_INVALID_MOVE,
    CHESS_GAME_INVALID_ARGUMENT,
    CHESS_GAME_INVALID_POSITION,
    CHESS_GAME_NO_HISTORY,
    CHESS_GAME_SUCCESS,
    CHESS_GAME_CROWNING,
} CHESS_GAME_MESSAGE;


/**
 * A type that represents the node of the array list. This is also used to pass moves between functions
 */
typedef struct sp_array_list_node {
    int current_pos_row;
    int current_pos_col;
    int prev_pos_row;
    int prev_pos_col;
    char prev_pos_fig;
    char moving_figure;
} SPArrayListNode;


/**
 * A type that represents the array list that contains chess moves
 */
typedef struct sp_array_list_t {
    SPArrayListNode* elements;
    int actualSize;
    int maxSize;
} SPArrayList;


/**
 * A type that represents the chess game
 *
 * gameBoard - the board
 * gameMode - one/two players
 * difficulty,currentPlayer,humanPlayerColor - obvious
 * historyArray - previous moves
 * UI_MODE - GUI/console
 * gameGUIBoard - the GUI board.
 *
 *
 
 */
typedef struct chess_game {
    char gameBoard[BOARD_SIZE][BOARD_SIZE];
	SDL_Rect gameGUIBoard[BOARD_SIZE][BOARD_SIZE];
    GAME_MODE_PLAYER gameMode;
    int difficulty;
    PLAYER_COLOR currentPlayer;
    PLAYER_COLOR humanPlayerColor;
    SPArrayList *historyArray;
    UI_MODE uiMode;
    
    

    
} chessGame;


/**
 * Defenitions of chess figure representations in console mode
 */
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
