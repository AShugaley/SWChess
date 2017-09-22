#ifndef SPMiniMax_h
#define SPMiniMax_h

#include <stdio.h>
#include "Chess_gameUtilsAux.h"
#include "SPMiniMax.h"
#include "Chess_gameUtils.h"


/**
 * SP_MiniMax summary:
 *
 * A container that includes the various functions of the minimax algorithem, used by the AI in order
 * to play the chess game.
 *
 * suggestMove    - A function that given a chess game suggests the best possible move
 * comFunc        - Computes the MinMax algoritem scoring function.
 * initMinmaxTree - Initiates the MiniMax tree
 * minmaxTree     - The minimax tree internal calls
 * maxFunc        - Maximum of two ints
 * minFunc        - Minimum of two ints
 *
 */

/**
 * Receives a ChessGame and a difficulry level (the depth of the minmax algoritem), and creates the call
 * of the minmax tree, calculating the best move (given the depth).
 *
 * @return SPArrayListNode representing a touple of ((x,y)->(v,w)) - suggested move.
 */
SPArrayListNode* suggestMove(chessGame* src, int depth);

/**
 * Computes the MinMax algoritem scoring function. 
 * King = 200
 * Queen = 9
 * Rook = 5
 * Bishop = 3
 * Knight = 3
 * Rook = 1
 *
 * The function is computed for both White and Black players (two seperate values - white and black)
 *
 * @return int (whiteValue - blackValue)
 */
int comFunc(chessGame* currentGame);

/**
 * Inities the minmax Tree. 
 * First, determins the current player (white/black), and then starts a branch for every 
 * valid move that can be done by this player. The simple system is do move -> branch -> undo move (repeat
 * until there are no more moves to check).
 *
 * @return SPArrayListNode representing a touple of ((x,y)->(v,w)) - suggested move.
 */
SPArrayListNode* initMinmaxTree(chessGame* currentGame, int depth);

/**
 * The main part of the MinMax algoritem.
 * Determins if this is a terminal node (depth = 0 || gameOver), if yes computes function
 * if no, determins all posible moves (for the current player), and checks them one by one\
 * do move -> branch -> undo move
 *
 * @return int representing the best scoring function in this move.
 */
int minmaxTree(chessGame* currentGame, int depth, int alpha, int beta);

/**
 * Determins the larger value of two ints: a if a>=b else b
 *
 * @return a if a>=b else b
 */
int maxFunc(int a, int b);

/**
 * Determins the smaller value of two ints: a if a>=b else b
 *
 * @return a if a<=b else b
 */
int minFunc(int a, int b);



#endif /* SPMiniMax_h */
