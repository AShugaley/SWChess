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
 * King = 100
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
int simpleUtilityFunction(chessGame* currentGame);

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
double minmaxTree(chessGame* currentGame, int depth, double alpha, double beta);

/**
 * Determins the larger value of two ints: a if a>=b else b
 *
 * @return a if a>=b else b
 */
double maxFunc(double a, double b);

/**
 * Determins the smaller value of two ints: a if a>=b else b
 *
 * @return a if a<=b else b
 */
double minFunc(double a, double b);


/**
 * Computes the MinMax algoritem scoring function. The basis is:
 * King = 100
 * Queen = 9
 * Rook = 5
 * Bishop = 3
 * Knight = 3
 * Rook = 1
 *
 *
 *
 * If expert difficulty is turned on, we add a few other variables:
 * 0.5 points (or -0.5 for black player) for isolated/blocked/doubled pawns
 * A score between 0 and 0.35 for each pawn, depending on how cental it is located.
 * A slight (less than 0.001) random score, in order to choose different moves given otherwise equal factors 
 *
 * The function is computed for both White and Black players (two seperate values - white and black)
 *
 * @return double (whiteValue - blackValue)
 */
double utilityFunction(chessGame* src);

#endif /* SPMiniMax_h */
